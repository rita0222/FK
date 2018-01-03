#include <FK/ARDevice.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

typedef std::vector<int>::size_type st;

fk_ARPattern::fk_ARPattern(void)
{
	name.clear();
	model = nullptr;
	contFlg = false;
	return;
}

fk_ARPattern::~fk_ARPattern()
{
	return;
}

fk_ARDevice::fk_ARDevice(void)
{
	setConfigFile("");
	setCameraParamFile("");
	setPatternFile("");

	setThresh(100);
	setPatternWidth(80.0);
	setPatternCenter(0.0, 0.0);

	contFlag = false;
	startFlag = false;

	pat_array.clear();
	pat_map.clear();

	return;
}

fk_ARDevice::~fk_ARDevice()
{
	pat_array.clear();
	pat_map.clear();

	if(handle != nullptr) arPattDetach(handle);
	if(patHandle != nullptr) arPattDeleteHandle(patHandle);
	arVideoCapStop();
	if(handle3D != nullptr) ar3DDeleteHandle(&handle3D);
	if(handle != nullptr) arDeleteHandle(handle);
	arVideoClose();
	return;
}

int fk_ARDevice::GetID(int argID)
{
	auto ite = pat_map.find(argID);
	if(ite == pat_map.end()) {
		return CreatePattern(argID);
	}
	return (*ite).second;
}

int fk_ARDevice::CreatePattern(int argID)
{
	auto size = pat_array.size();
	pat_array.resize(size+1);
	pat_map[argID] = int(size);
	return int(size);
}

void fk_ARDevice::setConfigFile(string argFileName)
{
	vconf = argFileName;
	return;
}

void fk_ARDevice::setCameraParamFile(string argFileName)
{
	cparam_name = argFileName;
	return;
}

void fk_ARDevice::setThresh(int argThresh)
{
	thresh = argThresh;
	return;
}


void fk_ARDevice::setPatternFile(string argFileName)
{
	setPatternFile(0, argFileName);
	return;
}

void fk_ARDevice::setPatternFile(int argID, string argFileName)
{
	st		id = st(GetID(argID));

	pat_array[id].name = argFileName;
	return;
}

void fk_ARDevice::setPatternWidth(double argWidth)
{
	setPatternWidth(0, argWidth);
	return;
}

void fk_ARDevice::setPatternWidth(int argID, double argWidth)
{
	st		id = st(GetID(argID));

	pat_array[id].width = argWidth;
	return;
}

void fk_ARDevice::setPatternCenter(double argX, double argY)
{
	setPatternCenter(0, argX, argY);
	return;
}

void fk_ARDevice::setPatternCenter(int argID, double argX, double argY)
{
	st		id = st(GetID(argID));

	pat_array[id].center[0] = argX;
	pat_array[id].center[1] = argY;
	return;
}

void fk_ARDevice::setPatternModel(int argID, fk_Model *argModel)
{
	st		id = st(GetID(argID));

	pat_array[id].model = argModel;
	return;
}

bool fk_ARDevice::deviceInit(void)
{
	AR_PIXEL_FORMAT		pixelFormat;
	int					erNo;

	erNo = 1;
    if(arVideoOpen(const_cast<char *>(vconf.c_str())) < 0) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Video Open Error.");
		return false;
	}
	++erNo;

    if(arVideoGetSize(&videoXSize, &videoYSize) < 0) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Video Get Size Error.");
		return false;
	}
	++erNo;

	pixelFormat = arVideoGetPixelFormat();
	if(pixelFormat < 0) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Video Pixel Format Error,");
		return false;
	}
	++erNo;
	
    if(arParamLoad(cparam_name.c_str(), 1, &cparam) < 0) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Camera Parameter Load Error.");
		return false;
    }
	++erNo;
	
	arParamChangeSize(&cparam, videoXSize, videoYSize, &cparam);
	if((paramLT = arParamLTCreate(&cparam, AR_PARAM_LT_DEFAULT_OFFSET)) == nullptr) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "ParamLT Create Error.");
		return false;
	}
	++erNo;

	if((handle = arCreateHandle(paramLT)) == nullptr) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Create Handle Error.");
		return false;
	}
	++erNo;

	if(arSetPixelFormat(handle, pixelFormat) < 0) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Set Pixel Format Error.");
		return false;
	}
	++erNo;

	if((handle3D = ar3DCreateHandle(&cparam)) == nullptr) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "3D Handle Create Error.");
		return false;
	}
	++erNo;

	if((patHandle = arPattCreateHandle()) == nullptr) {
		fk_PutError("fk_ARDevice", "deviceInit", erNo, "Pattern Handle Create Error.");
		return false;
	}
	++erNo;

	for(st i = 0; i < pat_array.size(); ++i) {
		if((pat_array[i].id = arPattLoad(patHandle, pat_array[i].name.c_str())) < 0) {
			fk_PutError("fk_ARDevice", "deviceInit", erNo, "Pattern Load Error.");
			return false;
		}
	}
	++erNo;

	arPattAttach(handle, patHandle);

	CameraInit();
	return true;
}

void fk_ARDevice::CameraInit(void)
{
	CameraInit1();
	ConvARCMat(AR_GL_DEFAULT_CLIP_NEAR, AR_GL_DEFAULT_CLIP_FAR);
	arVideoCapStart();	
	return;
}

void fk_ARDevice::CameraInit1(void)
{
	int		count;

    for(count = 0; count < 4; count++ ) {
        cparam.mat[1][count] = (cparam.ysize-1)*(cparam.mat[2][count]) - cparam.mat[1][count];
    }
	
	return;
}

void fk_ARDevice::ConvARCMat(double argNear, double argFar)
{
    double   icpara[3][4];
    double   trans[3][4];
    double   p[3][3], q[4][4];
    int      j, k;
	
	int width = cparam.xsize;
	int height = cparam.ysize;
	
    if(arParamDecompMat(cparam.mat, icpara, trans) < 0) {
        fk_PutError("fk_ARDevice", "ConvARCMat", 1, "Parameter error.");
		return;
    }
	
    for( k = 0; k < 3; k++ ) {
        for( j = 0; j < 3; j++ ) {
            p[k][j] = icpara[k][j] / icpara[2][2];
        }
    }
    q[0][0] = (2.0 * p[0][0] / width);
    q[0][1] = (2.0 * p[0][1] / width);
    q[0][2] = ((2.0 * p[0][2] / width)  - 1.0);
    q[0][3] = 0.0;
	
    q[1][0] = 0.0;
    q[1][1] = (2.0 * p[1][1] / height);
    q[1][2] = ((2.0 * p[1][2] / height) - 1.0);
    q[1][3] = 0.0;
	
    q[2][0] = 0.0;
    q[2][1] = 0.0;
    q[2][2] = (argFar + argNear)/(argFar - argNear);
    q[2][3] = -2.0 * argFar * argNear / (argFar - argNear);
	
    q[3][0] = 0.0;
    q[3][1] = 0.0;
    q[3][2] = 1.0;
    q[3][3] = 0.0;
	
	// カメラ用射影変換行列cpara_mat算出
	for(k = 0; k < 4; k++){
		for(j = 0; j < 3; j++){
			cparam_mat.set(k, j, q[k][0] * trans[0][j]
						   + q[k][1] * trans[1][j]
						   + q[k][2] * trans[2][j]);
		}
		cparam_mat.set(k, 3, q[k][0] * trans[0][3]
					  + q[k][1] * trans[1][3]
					  + q[k][2] * trans[2][3]
					  + q[k][3]);
	}

	return;
	
}

void fk_ARDevice::SetARCam(fk_Model *argModel)
{
	ConvARModelR(cparam_mat, argModel);
	return;
}

void fk_ARDevice::ConvARModelR(fk_Matrix argMat, fk_Model *argModel)
{
	fk_Vector	DirVec(0.0,0.0,-1.0), UpVec(0.0,1.0,0.0);
	fk_Matrix	mat = argMat;

	for(int k = 0; k < 3; k++){
		mat.set(k,3,0.0);
	}
	DirVec = mat * DirVec;
	UpVec  = mat * UpVec;
	DirVec.x = -DirVec.x;
	UpVec.x = -UpVec.x;
	argModel->glVec(DirVec);
	argModel->glUpvec(UpVec);
	
	return;
}

void fk_ARDevice::ConvARModelT(fk_Matrix argMat, fk_Model *argModel)
{
	argModel->glMoveTo(-argMat[0][3], argMat[1][3], argMat[2][3]);
	return;
}

void fk_ARDevice::SetMarkerModel(int argID, fk_Model *model)
{
	fk_Matrix tmpMat;
	
    for(int k = 0; k < 3; k++ ) {
        for(int j = 0; j < 4; j++ ) {
			tmpMat.set(k, j, pat_array[st(argID)].transMat[k][j]);
		}
    }

	ConvARModelR(tmpMat, model);		// 回転成分適応
	ConvARModelT(tmpMat, model);		// 平行移動成分適応
	
	return;
}

fk_AR_Device_Status fk_ARDevice::update(fk_ARTexture *argVideoTex,
										fk_Model *argModel)
{
	if(pat_array.empty() == true) return FK_AR_NO_DETECT;

	pat_array[0].model = argModel;
	return update(argVideoTex);
}

fk_AR_Device_Status fk_ARDevice::update(fk_ARTexture *argVideoTex)
{
    ARUint8         *dataPtr;
    ARMarkerInfo    *marker_info;
    int             marker_num;
	bool			detectFlg;
	int				k;

    if((dataPtr = (ARUint8 *)arVideoGetImage()) == nullptr) {
        arUtilSleep(2);
        return FK_AR_IMAGE_NULL;
    }
	
    if(startFlag == false) {
		arUtilTimerReset();
		startFlag = true;
	}

	argVideoTex->setVideoBuf(dataPtr, videoXSize, videoYSize);

    if(arDetectMarker(handle, dataPtr) < 0) {
		return FK_AR_DETECT_ERROR;
    }
	
	detectFlg = false;
	if((marker_num = arGetMarkerNum(handle)) == 0) return FK_AR_NO_DETECT;
	marker_info = arGetMarker(handle);

	for(st i = 0; i < pat_array.size(); ++i) {
		k = -1;
		for(st j = 0; j < st(marker_num); j++) {
			if(pat_array[i].id == marker_info[j].id) {
				if(k == -1) {
					k = int(j);
				} else if(marker_info[k].cf < marker_info[j].cf) {
					k = int(j);
				}
			}
		}
		if(k == -1) {
			pat_array[i].contFlg = false;
			continue;
		}

		detectFlg = true;

		if(pat_array[i].contFlg == false) {
			arGetTransMatSquare(handle3D,
								&marker_info[k],
								pat_array[i].width,
								pat_array[i].transMat);
			pat_array[i].contFlg = true;
		} else {
			arGetTransMatSquareCont(handle3D,
									&marker_info[k],
									pat_array[i].transMat,
									pat_array[i].width,
									pat_array[i].transMat);
		}
		SetMarkerModel(int(i), pat_array[i].model);
	}

	return (detectFlg == true) ? FK_AR_DETECT : FK_AR_NO_DETECT;
}

void fk_ARDevice::makeProject(double argNear, double argFar,
							  fk_Frustum *argProj,
							  fk_ARTexture *argTex,
							  fk_Model *argVideo,
							  fk_Model *argCamera)
{
	double		xSize, ySize, xPos, yPos;
	double		w_plus, w_minus, left, right;
	double		h_plus, h_minus, bottom, top;
	double		scale;

	scale = argFar/argNear;
	xPos = yPos = 0.0;

	w_minus = 2.0*argNear/cparam_mat[0][0];
	w_plus = w_minus * cparam_mat[0][2];
	right = (w_plus + w_minus)/2.0;
	left = (w_plus - w_minus)/2.0;

	h_minus = 2.0*argNear/cparam_mat[1][1];
	h_plus = h_minus * cparam_mat[1][2];
	top = -(h_plus + h_minus)/2.0;
	bottom = -(h_plus - h_minus)/2.0;

	argProj->setAll(left, right, bottom, top, argNear, argFar+100.0);

	xSize = (right - left)*scale;
	ySize = (top - bottom)*scale;

	xPos = (left + right)/2.0;
	yPos = (bottom + top)/2.0;

	SetARCam(argCamera);

	argTex->setTextureSize(xSize, ySize);
	argVideo->glAngle(0.0, 0.0, FK_PI);
	argVideo->glMoveTo(xPos*scale, yPos*scale, -argFar);	
	argVideo->setParent(argCamera);
	argCamera->glVec(0.0, yPos*2.0, argNear);
	argCamera->glUpvec(0.0, -1.0, 0.0);

	return;
}

bool fk_ARDevice::getModelDetect(int argID)
{
	return pat_array[st(GetID(argID))].contFlg;
}
