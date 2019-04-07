#define FK_DEF_SIZETYPE
#include <FK/FK.h>

using namespace std;
using namespace FK;
using namespace FK::Material;

const int WIN_W = 800; // ウィンドウ横幅
const int WIN_H = 800; // ウィンドウ縦幅
const double SP_X = -(double(WIN_W/2) - 10.0);
const double SP_Y = double(WIN_H/2) - 10.0;

// 通常モデルのシェーダー設定
void ShaderSetup(fk_ShaderBinder *argBinder, fk_Model *argModel,
				 string argVP, string argFP)
{
	argModel->setSmoothMode(true);
	argBinder->getProgram()->loadVertexShader(argVP);
	argBinder->getProgram()->loadFragmentShader(argFP);
	if(argBinder->getProgram()->validate()) {
		argBinder->bindModel(argModel);
	} else {
		fk_Window::printf("Shader Error");
		fk_Window::putString(argBinder->getProgram()->getLastError());
	} 
}

void ModelSetup(fk_Model *argModel, fk_Material &argMat, fk_Vector argPos)
{
	argModel->setSmoothMode(true);
	argModel->setMaterial(argMat);
	argModel->glMoveTo(argPos);
}

int fID(int argI, int argJ, int divW)
{
	return (2 * (argI + divW * argJ));
}

int vID(int argI, int argJ, int divW)
{
	return (argI + (divW + 1) * argJ);
}

void CylMake(fk_IFSTexture *argIFS)
{
	int divW = 50;
	int divH = 20;
	double radius = 10.0;
	double height = 30.0;

	vector<int>	ifset(_st(divW * divH * 6));
	vector<fk_Vector> pos(_st((divW + 1) * (divH + 1)));

	for(int j = 0; j <= divH; j++) {
		double h1 = height * double(j)/double(divH);

		for(int i = 0; i <= divW; i++) {
			int id = vID(i, j, divW);
			double theta = FK_PI * 2.0 * double(i)/double(divW);
			double sin1 = sin(theta);
			double cos1 = cos(theta);
			pos[_st(id)] = fk_Vector(sin1 * radius, h1, cos1 * radius);
		}
	}

	for(int j = 0; j < divH; j++) {
		for(int i = 0; i < divW; i++) {
			int id_0 = vID(i, j, divW);
			int id_1 = vID(i+1, j, divW);
			int id_2 = vID(i+1, j+1, divW);
			int id_3 = vID(i, j+1, divW);
			_st faceOffset = _st(fID(i, j, divW) * 3);

			ifset[faceOffset + 0] = id_0;
			ifset[faceOffset + 1] = id_1;
			ifset[faceOffset + 2] = id_3;

			ifset[faceOffset + 3] = id_2;
			ifset[faceOffset + 4] = id_3;
			ifset[faceOffset + 5] = id_1;
		}
	}

	argIFS->getIFS()->makeIFSet(int(ifset.size())/3, 3, ifset.data(),
								int(pos.size()), pos.data());

	fk_TexCoord coord[4];
	for(int j = 0; j <= divH; j++) { // y方向
		for(int i = 0; i <= divW; i++) { // xz方向
			int id = fID(i, j, divW);
			double x1 = double(i)/double(divW);
			double x2 = double(i+1)/double(divW);
			double y1 = double(j)/double(divH);
			double y2 = double(j+1)/double(divH);

			coord[0].set(x1, y1);
			coord[1].set(x2, y1);
			coord[2].set(x2, y2);
			coord[3].set(x1, y2);

			argIFS->setTextureCoord(id, 0, coord[0]);
			argIFS->setTextureCoord(id, 1, coord[1]);
			argIFS->setTextureCoord(id, 2, coord[3]);
			argIFS->setTextureCoord(id+1, 0, coord[2]);
			argIFS->setTextureCoord(id+1, 1, coord[3]);
			argIFS->setTextureCoord(id+1, 2, coord[1]);
		}
	}
}

fk_TexCoord getScale(fk_Image *argImage, fk_TexCoord *argScale)
{
	auto spriteSizeDim = argImage->getImageSize();
	auto spriteBufDim = argImage->getBufferSize();
	fk_TexCoord sprScale(double(spriteSizeDim->w)/double(spriteBufDim->w),
						 double(spriteSizeDim->h)/double(spriteBufDim->h));
	fk_TexCoord prodScale(double(argScale->x * sprScale.x),
						  double(argScale->y * sprScale.y));
	return prodScale;
}
	
int main(int, char **)
{
	fk_System::setcwd();

	fk_AppWindow	window;
	fk_IFSTexture	ifsShape;
	fk_Model		ifsModel, lightModel, camera;
	fk_SpriteModel	sprite;
	fk_ShaderBinder binder;

	window.setSize(WIN_W, WIN_H);
	fk_InitMaterial();
	fk_SetErrorMode(FK_ERR_BROWSER_INTERACTIVE);

	if(ifsShape.readPNG("image/poe.png") == false) {
		fl_alert("tex load err");
	}

	ifsShape.setTexRendMode(FK_TEX_REND_SMOOTH);
	CylMake(&ifsShape);

	ifsModel.setShape(&ifsShape);
	ModelSetup(&ifsModel, White, fk_Vector(0.0, 0.0, 0.0));

	if(sprite.initFont("image/rm1b.ttf") == false) {
		fl_alert("Font Init Error");
	}
	sprite.setPositionLT(SP_X, SP_Y);
	fk_Image	*image = sprite.getImage();
	fk_RectTexture	texture(image);

	window.setBGColor(0.5f, 0.5f, 0.5f);
	window.setCameraModel(&camera);
	window.entry(&ifsModel);
	window.entry(&sprite);
	window.setTrackBallMode(true);
	window.showGuide();

	// 視点の位置と姿勢を設定
	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	// ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
	window.open();
	Fl::check();

	ShaderSetup(&binder, &ifsModel, "shader/multi_vp.glsl", "shader/multi_fp.glsl");

	auto parameter = binder.getParameter();
		
	// シェーダー内で fk_TexID[1] で参照できるように設定
	parameter->attachTexture(1, &texture);

	auto texSizeDim = ifsShape.getImageSize();
	auto texBufDim = ifsShape.getBufferSize();
	fk_TexCoord orgScale(double(texBufDim->w)/double(texSizeDim->w),
						 double(texBufDim->h)/double(texSizeDim->h));

	fk_TexCoord scaleCoord = getScale(image, &orgScale);
	vector<float>	scale = {scaleCoord.x, scaleCoord.y};
	parameter->setRegister("scale", &scale);
	for(int count = 0; window.update() == true; count++) {
		lightModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, 0.01);
		sprite.drawText(to_string(count), true);
		sprite.setPositionLT(SP_X, SP_Y);

		texture.setImage(image);
		scaleCoord = getScale(image, &orgScale);
		scale[0] = scaleCoord.x * 5.0f;
		scale[1] = scaleCoord.y * 5.0f;
		parameter->setRegister("scale", &scale);
	}

	return 0;
}
