#define FK_DEF_SIZETYPE
#include <FK/MotionCharactor.h>
#include <FK/Error.H>
#include <regex>

using namespace std;
using namespace FK;

map<string, shared_ptr<fk_Shape>> fk_Performer::_s_shapeCache;
map<string, shared_ptr<fk_Image>> fk_Performer::_s_imageCache;
//map<fk_BaseObject *, int> fk_Performer::countCache;

static vector<string> fk_StrSplit(const string &argStr, const string &argToken)
{
	vector<string> retStrArray;
	string::size_type curPos = 0, nextPos = 0;

	while(nextPos != string::npos) {
		nextPos = argStr.find(argToken, curPos);
		retStrArray.push_back(argStr.substr(curPos, nextPos-curPos));
		curPos = nextPos+1;
	}

	return retStrArray;
}

fk_Performer::Member::Member(void)
{
	return;
}

fk_Performer::fk_Performer(void) : _m(make_unique<Member>())
{
	init();
	return;
}

fk_Performer::~fk_Performer(void)
{
	return;
}

bool fk_Performer::cloneCharactor(fk_Performer *argOrg)
{
	init();

	_m->mesh = argOrg->_m->mesh;
	_m->matPalette = argOrg->_m->matPalette;
	_m->matTable = argOrg->_m->matTable;
	_m->texImage = argOrg->_m->texImage;
	_m->texName = argOrg->_m->texName;
	_m->texTable = argOrg->_m->texTable;
	_m->mqoName = argOrg->_m->mqoName;
	_m->objNum = argOrg->_m->objNum;
	_m->objName = argOrg->_m->objName;
	_m->parentTable = argOrg->_m->parentTable;
	_m->parentConnect = argOrg->_m->parentConnect;

	_m->keyFrameData  = argOrg->_m->keyFrameData;
	_m->nowFrame = argOrg->_m->nowFrame;
	_m->maxFrame = argOrg->_m->maxFrame;
	_m->visibleInfo = argOrg->_m->visibleInfo;
	_m->draw_mode = argOrg->_m->draw_mode;

	_m->prevPlayMotionID = argOrg->_m->prevPlayMotionID;
	_m->loopCnt = argOrg->_m->loopCnt;

	_m->jointModel.clear();
	_m->objModel.clear();
	for(_st i = 0; i < _st(_m->objNum); i++) {
		_m->jointModel.push_back(make_unique<fk_Model>());
		_m->objModel.push_back(make_unique<fk_Model>());
		fk_Model *jointModel = _m->jointModel.back().get();
		fk_Model *objModel = _m->objModel.back().get();
		if(i > 0) {
			objModel->setShape(_m->mesh[i-1].lock().get());
			objModel->setMaterial(_m->matPalette[_st(_m->matTable[i-1])]);
			objModel->setSmoothMode(true);
		}
		objModel->glMoveTo(argOrg->_m->objModel[i]->getPosition());
		objModel->glAngle(argOrg->_m->objModel[i]->getAngle());
		objModel->setScale(argOrg->_m->objModel[i]->getScale());
		objModel->setScale(argOrg->_m->objModel[i]->getScale(fk_Axis::X),
						   argOrg->_m->objModel[i]->getScale(fk_Axis::Y),
						   argOrg->_m->objModel[i]->getScale(fk_Axis::Z));
		jointModel->glMoveTo(argOrg->_m->jointModel[i]->getPosition());
		jointModel->glAngle(argOrg->_m->jointModel[i]->getAngle());
		jointModel->setScale(argOrg->_m->jointModel[i]->getScale());
		jointModel->setScale(argOrg->_m->jointModel[i]->getScale(fk_Axis::X),
							 argOrg->_m->jointModel[i]->getScale(fk_Axis::Y),
							 argOrg->_m->jointModel[i]->getScale(fk_Axis::Z));
	}
	if(_m->parentConnect) {
		for(auto ite = _m->parentTable.begin(); ite != _m->parentTable.end(); ite++) {
			fk_Model *child = _m->jointModel[_st(ite->first)].get();
			fk_Model *parent = _m->jointModel[_st(ite->second)].get();
			child->setParent(parent, false);
		}
		for(_st i = 0; i < _st(_m->objNum); i++) {
			_m->objModel[i]->setParent(_m->jointModel[i].get(), false);
		}
		_m->jointModel[0]->setParent(&_m->absParent, false);
	}
	_m->absParent.glMoveTo(argOrg->_m->absParent.getPosition());
	_m->absParent.glAngle(argOrg->_m->absParent.getAngle());
	_m->absParent.setScale(argOrg->_m->absParent.getScale());
	_m->absParent.setScale(argOrg->_m->absParent.getScale(fk_Axis::X),
						   argOrg->_m->absParent.getScale(fk_Axis::Y),
						   argOrg->_m->absParent.getScale(fk_Axis::Z));

	return true;
}

void fk_Performer::init()
{
	_m->objModel.clear();
	_m->jointModel.clear();
	_m->mesh.clear();
	_m->texImage.clear();

	_m->objName.clear();
	_m->texName.clear();
	_m->texTable.clear();
	_m->matTable.clear();
	_m->matPalette.clear();

	_m->parentTable.clear();
	_m->keyFrameData.clear();

	_m->mqoName.clear();
	_m->objNum = 0;
	_m->parentConnect = false;

	_m->visibleInfo.clear();

	// モーション複数化対応
	_m->nowFrame.clear();
	_m->maxFrame.clear();

	_m->prevPlayMotionID = 0;
	_m->loopCnt = 0;

	return;
}

// MQO ファイルからオブジェクト名を列挙する
bool fk_Performer::EnumObjectName(const string &argFileName)
{
	ifstream in_file(argFileName);

	if(!in_file.is_open()) return false;

	vector<string> readBuf(1);
	for(_st i = 0; getline(in_file, readBuf.at(i)); ++i) {
		readBuf.push_back("");
	}

	// マテリアル情報の抽出
	for(_st i = 0; i < readBuf.size(); i++) {
		if(readBuf[i].find("Material") != string::npos) {
			i++;
			while(readBuf[i].find("}") == string::npos) {
				vector<string> lineStr = fk_StrSplit(readBuf[i], " ");
				for(_st j = 0; j < lineStr.size(); j++) {
					if(lineStr[j].find("col(") == string::npos) continue;
					// base color
					fk_Color tmpCol;
					tmpCol.set(stof(lineStr[j].substr(4, 5)),
							   stof(lineStr[j+1]),
							   stof(lineStr[j+2]),
							   stof(lineStr[j+3].substr(0, 5))
					);

					float tmpParam[5];
					// dif
					tmpParam[0] = stof(lineStr[j+4].substr(4, 5));
					// amb
					tmpParam[1] = stof(lineStr[j+5].substr(4, 5));
					// emi
					tmpParam[2] = stof(lineStr[j+6].substr(4, 5));
					// spe
					tmpParam[3] = stof(lineStr[j+7].substr(4, 5));
					// power
					tmpParam[4] = stof(lineStr[j+8].substr(6, 4));
					// set
					fk_Material tmpMat;

					tmpMat.setDiffuse(tmpCol.getR()*tmpParam[0],
									  tmpCol.getG()*tmpParam[0],
									  tmpCol.getB()*tmpParam[0]);
					tmpMat.setAmbient(tmpCol.getR()*tmpParam[1],
									  tmpCol.getG()*tmpParam[1],
									  tmpCol.getB()*tmpParam[1]);
					tmpMat.setEmission(tmpCol.getR()*tmpParam[2],
									   tmpCol.getG()*tmpParam[2],
									   tmpCol.getB()*tmpParam[2]);
					tmpMat.setSpecular(tmpCol.getR()*tmpParam[3],
									   tmpCol.getG()*tmpParam[3],
									   tmpCol.getB()*tmpParam[3]);
					tmpMat.setShininess(tmpParam[4]);

					_m->matPalette.push_back(tmpMat);

					if(j+9 >= lineStr.size()) {
						_m->texTable.push_back(-1);
						break;
					}

					auto openPos = lineStr[j+9].find("tex(");
					if(openPos == string::npos) break;
					auto closePos = lineStr[j+9].find_last_of('\"');
					if(closePos == string::npos) break;

					bool tmpFlag = false;
					for(_st k = 0; k < _m->texName.size(); k++) {
						if(_m->texName[k] == lineStr[j+9].substr(openPos+5, closePos-openPos-5)) {
							_m->texTable.push_back(int(k));
							tmpFlag = true;
							break;
						}
					}
					if(!tmpFlag) {
						_m->texName.push_back(lineStr[j+9].substr(openPos+5, closePos-openPos-5));
						_m->texTable.push_back(int(_m->texName.size()-1));
					}
				}
				i++;
			}
			break;
		}
	}

	// オブジェクト名の列挙]
	_m->objName.push_back("<base>");
	for(_st i = 0; i < readBuf.size(); i++) {
		auto openPos = readBuf[i].find("Object \"");
		if(openPos != string::npos) {
			auto closePos = readBuf[i].find_last_of('\"');
			if(closePos == string::npos) return false;
			_m->objName.push_back(readBuf[i].substr(openPos+8, closePos-openPos-8));
			while(true) {
				i++;
				// マテリアル指定の抽出
				if(readBuf[i].find("M(") != string::npos) {
					// UV 指定のないオブジェクトも読めるように
					string::size_type	tmpPos = readBuf[i].find(")", readBuf[i].find("M(")+1);

					if(tmpPos == string::npos) return false;

					string intStr = readBuf[i].substr(readBuf[i].find("M(")+2,
													  tmpPos-readBuf[i].find("M(")-2);
					_m->matTable.push_back(stoi(intStr));
					break;
				}
			}
		}
	}

	return true;
}

bool fk_Performer::IsPNG(string argName)
{
	return (argName.rfind(".png") != string::npos ||
			argName.rfind(".PNG") != string::npos ||
			argName.rfind(".Png") != string::npos);
}

bool fk_Performer::ReadPNG(fk_Image *argImage, string argName)
{
	if(!argImage->readPNG(argName)) {
		Error::Put("Texture File(" + argName + ") Read Error.");
		init();
		return false;
	}
	return true;
}

bool fk_Performer::IsJPG(string argName)
{
	return (argName.rfind(".jpg") != string::npos ||
			argName.rfind(".JPG") != string::npos ||
			argName.rfind(".Jpg") != string::npos ||
			argName.rfind(".jpeg") != string::npos ||
			argName.rfind(".JPEG") != string::npos ||
			argName.rfind(".Jpeg") != string::npos);
}

bool fk_Performer::ReadJPG(fk_Image *argImage, string argName)
{
	if(!argImage->readJPG(argName)) {
		Error::Put("Texture File(" + argName + ") Read Error.");
		init();
		return false;
	}
	return true;
}

bool fk_Performer::ReadBMP(fk_Image *argImage, string argName)
{
	if(!argImage->readBMP(argName)) {
		Error::Put("Texture File(" + argName + ") Read Error.");
		init();
		return false;
	}
	return true;
}

bool fk_Performer::AlphaChannel(fk_Image *argImage, string argName)
{
	fk_Image alphaChannel;

	if(!alphaChannel.readBMP(argName.substr(0, argName.size() - 4) + "_a.bmp")) return false;
	for(int y = 0; y < alphaChannel.getHeight(); y++) {
		for(int x = 0; x < alphaChannel.getWidth(); x++) {
			argImage->setA(x, y, alphaChannel.getR(x, y));
		}
	}
	return true;
}

// MQO ファイルから形状とテクスチャを読み込む
bool fk_Performer::loadObjectData(const string &argFileName)
{
	init();

	// オブジェクトの読み込み
	if(!EnumObjectName(argFileName)) {
		Error::Put("Enum Object Error.");
		init();
		return false;
	}
	_m->objNum = int(_m->objName.size());

	_m->jointModel.clear();
	_m->objModel.clear();
	_m->mesh.clear();
	_m->texImage.clear();

	string texPath = argFileName.substr(0, argFileName.find_last_of('/')+1);
	_m->mqoName = argFileName.substr(argFileName.find_last_of('/')+1, string::npos);

	_m->visibleInfo.resize(_st(_m->objNum));

	// テクスチャロード
	for(_st i = 0; i < _m->texName.size(); i++) {
		string fileName = texPath + _m->texName[i];

		// まだキャッシュ中にデータがない
		if(_s_imageCache.find(fileName) == _s_imageCache.end()) {
			shared_ptr<fk_Image> ptr(new fk_Image);
			_s_imageCache.emplace(fileName, ptr);
			//reverseCache[texImage[i]] = texPath+_m->texName[i];
			//countCache[texImage[i]] = 1;
			fk_Image *image = _s_imageCache[texPath + _m->texName[i]].get();

			// PNG 対応
			if(IsPNG(fileName)) {
				if(!ReadPNG(image, fileName)) return false;
			} else if(IsJPG(fileName)) {
				if(!ReadJPG(image, fileName)) return false;
			} else if(image->readBMP(fileName)) {
				AlphaChannel(image, fileName);
			} else {
				Error::Put("Texture File(" + fileName + ") Read Error.");
				init();
				return false;
			}
		}
		_m->texImage.push_back(_s_imageCache[fileName]);
		
	}

	// 形状ロード
	for(_st i = 0; i < _st(_m->objNum); i++) {
		_m->jointModel.push_back(make_unique<fk_Model>());
		_m->objModel.push_back(make_unique<fk_Model>());
		if(i == 0) {
			_m->visibleInfo[0] = true;
			continue;
		}

		string objName = argFileName + _m->objName[i];
		fk_Model *objModel = _m->objModel.back().get();

		if(_s_shapeCache.find(objName) != _s_shapeCache.end()) {
			_m->mesh.push_back(_s_shapeCache[objName]);
			//countCache[mesh[i-1]]++;

		} else {
			int mTable = _m->texTable[_st(_m->matTable[i-1])];
			if(mTable != -1) {
				shared_ptr<fk_Shape> ptr(new fk_IFSTexture);
				_s_shapeCache.emplace(objName, ptr);
				fk_IFSTexture *ifsTex =
					dynamic_cast<fk_IFSTexture *>(_s_shapeCache[objName].get());

				fk_Image *image = _m->texImage[_st(mTable)].lock().get();
				ifsTex->setImage(image);
				ifsTex->setTexRendMode(fk_TexRendMode::SMOOTH);
				if(ifsTex->readMQOFile(argFileName, _m->objName[i]) == false) {
					Error::Put("MQO File Read Error.");
					init();
					return false;
				}
			} else {
				shared_ptr<fk_Shape> ptr(new fk_IndexFaceSet);
				_s_shapeCache.emplace(objName, ptr);
				fk_IndexFaceSet *ifSet =
					dynamic_cast<fk_IndexFaceSet *>(_s_shapeCache[objName].get());
					
				if(ifSet->readMQOFile(argFileName, _m->objName[i]) == false) {
					Error::Put("MQO File Read Error.");
					init();
					return false;
				}
			}
			_m->mesh.push_back(_s_shapeCache[objName]);
			//reverseCache[mesh[i-1]] = argFileName + _m->objName[i];
			//countCache[mesh[i-1]] = 1;
		}

		objModel->setShape(_m->mesh[i-1].lock().get());
		objModel->setMaterial(_m->matPalette[_st(_m->matTable[i-1])]);
		objModel->setSmoothMode(true);

		_m->parentTable[int(i)] = 0;
		_m->visibleInfo[i] = true;
	}

	return true;
}

// FKC ファイルから親子関係と接続位置情報を読み込む
bool fk_Performer::loadJointData(const string &argFileName)
{
	ifstream in_file(argFileName);

	// オープン正否判定
	if(!in_file.is_open()) return false;

	// ヘッダチェック
	string lineStr;
	if(!getline(in_file, lineStr)) return false;
	if(lineStr.find("FKC_HEADER_0.2") == string::npos) return false;

	// 親子関係列挙ブロック探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[ENUM PARENT TABLE BEGIN]") == string::npos);

	vector<string> arraySplit;

	// 親子関係読み込み
	_m->parentTable.clear();
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[ENUM PARENT TABLE END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 2) return false;
		_m->parentTable[stoi(arraySplit[0])] = stoi(arraySplit[1]);
	}

	// 接続位置情報探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[ENUM JOINT POSITION BEGIN]") == string::npos);

	// 接続位置情報読み込み
	_st objIndex = 0;
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[ENUM JOINT POSITION END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 3) return false;
		_m->jointModel[_st(objIndex)]->glMoveTo(stof(arraySplit[0]),
												stof(arraySplit[1]),
												stof(arraySplit[2]));
		objIndex++;
		if(objIndex >= _st(_m->objNum)) break;
	}

	jointToPoser();

	return true;
}

// FKM ファイルからモーションデータを読み込む
bool fk_Performer::loadMotionData(const string &argFileName)
{
	ifstream in_file(argFileName);

	// モーション複数化対応
	vector<fk_PerformerMotion> tmpMotionArray(_st(_m->objNum));

	// オープン正否判定
	if(!in_file.is_open()) return false;

	// ヘッダチェック
	string lineStr;
	if(!getline(in_file, lineStr)) return false;
	if(lineStr.find("FKM_HEADER_0.31") != string::npos) {
		in_file.close();
		return LoadMotionDataEulerScale(argFileName);
	} else if(lineStr.find("FKM_HEADER_0.3") != string::npos) {
		in_file.close();
		return LoadMotionDataEuler(argFileName);
	} else if(lineStr.find("FKM_HEADER_0.2") == string::npos) {
		return false;
	}

	// 親オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[PARENT OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 親オブジェクトキーフレーム読み込み
	tmpMotionArray[0].init();
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[PARENT OBJECT KEYFRAME DATA END]") != string::npos) break;
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 9) return false;
		tmpMotionArray[0].pushKeyFrame(
			fk_Quaternion(stof(arraySplit[0]),
						  stof(arraySplit[1]),
						  stof(arraySplit[2]),
						  stof(arraySplit[3])),
			fk_Vector(stof(arraySplit[4]),
					  stof(arraySplit[5]),
					  stof(arraySplit[6])),
			stoi(arraySplit[7]), (fk_MotionInterType)stoi(arraySplit[8])
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	_st objIndex = 0;
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= _st(_m->objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 9) return false;
		tmpMotionArray[objIndex].pushKeyFrame(
			fk_Quaternion(stof(arraySplit[0]),
						  stof(arraySplit[1]),
						  stof(arraySplit[2]),
						  stof(arraySplit[3])),
			fk_Vector(stof(arraySplit[4]),
					  stof(arraySplit[5]),
					  stof(arraySplit[6])),
			stoi(arraySplit[7]),
			(fk_MotionInterType)stoi(arraySplit[8])
		);
	}

	// モーション複数化対応
	_m->keyFrameData.push_back(tmpMotionArray);
	_m->nowFrame.push_back(0);
	int totalFrame = 0;
	for(_st i = 0; i < _st(_m->objNum); i++) {
		int curFrame = _m->keyFrameData.back().at(i).getTotalFrameNum();
		if(totalFrame < curFrame) totalFrame = curFrame;
	}
	_m->maxFrame.push_back(totalFrame);

	return true;
}

// FKM ファイルからモーションデータを読み込む(オイラー角版)
bool fk_Performer::LoadMotionDataEuler(const string &argFileName)
{
	ifstream in_file(argFileName);

	// モーション複数化対応
	//int	totalFrame = 0;
	vector<fk_PerformerMotion>	tmpMotionArray(_st(_m->objNum));

	// オープン正否判定
	if(!in_file.is_open()) {
		Error::Put("ファイルが開けません。");
		return false;
	}

	// ヘッダチェック
	string lineStr;
	if(!getline(in_file, lineStr)) {
		Error::Put("ファイルが途中で終わっています。");
		return false;
	}
	if(lineStr.find("FKM_HEADER_0.3") == string::npos) {
		Error::Put("違う種類のファイルを読み込もうとしました。");
		return false;
	}

	// 親オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[PARENT OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	fk_Quaternion tmpQ;
	// 親オブジェクトキーフレーム読み込み
	tmpMotionArray[0].init();
	while(true) {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[PARENT OBJECT KEYFRAME DATA END]") != string::npos) break;
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 8) {
			Error::Put("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(stof(arraySplit[0]),
					   stof(arraySplit[1]),
					   stof(arraySplit[2]));

		tmpMotionArray[0].pushKeyFrame(
			tmpQ,
			fk_Vector(stof(arraySplit[3]),
					  stof(arraySplit[4]),
					  stof(arraySplit[5])),
			stoi(arraySplit[6]),
			fk_MotionInterType(stoi(arraySplit[7]))
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	_st objIndex = 0;
	while(true) {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= _st(_m->objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 8) {
			Error::Put("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(stof(arraySplit[0]),
					   stof(arraySplit[1]),
					   stof(arraySplit[2]));
		tmpMotionArray[objIndex].pushKeyFrame(
			tmpQ,
			fk_Vector(stof(arraySplit[3]),
					  stof(arraySplit[4]),
					  stof(arraySplit[5])),
			stoi(arraySplit[6]),
			fk_MotionInterType(stoi(arraySplit[7]))
		);
	}

	// モーション複数化対応
	_m->keyFrameData.push_back(tmpMotionArray);
	_m->nowFrame.push_back(0);
	int totalFrame = 0;
	for(_st i = 0; i < _st(_m->objNum); i++) {
		int curFrame = _m->keyFrameData.back().at(i).getTotalFrameNum();
		if(totalFrame < curFrame) totalFrame = curFrame;
	}
	_m->maxFrame.push_back(totalFrame);

	return true;
}

// FKM ファイルからモーションデータを読み込む(スケール対応版)
bool fk_Performer::LoadMotionDataEulerScale(const string &argFileName)
{
	ifstream			in_file(argFileName);
	/*
	string				lineStr;
	vector<string>		arraySplit;
	_st					objIndex = 0;
	fk_Quaternion		tmpQ;
	*/

	// モーション複数化対応
	//int	totalFrame = 0;
	vector<fk_PerformerMotion> tmpMotionArray(_st(_m->objNum));

	// オープン正否判定
	if(!in_file.is_open()) {
		Error::Put("ファイルが開けません。");
		return false;
	}

	// ヘッダチェック
	string lineStr;
	if(!getline(in_file, lineStr)) {
		Error::Put("ファイルが途中で終わっています。");
		return false;
	}
	if(lineStr.find("FKM_HEADER_0.31") == string::npos) {
		Error::Put("違う種類のファイルを読み込もうとしました。");
		return false;
	}

	// 親オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[PARENT OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	fk_Quaternion tmpQ;

	// 親オブジェクトキーフレーム読み込み
	tmpMotionArray[0].init();
	while(true) {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[PARENT OBJECT KEYFRAME DATA END]") != string::npos) break;
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 11) {
			Error::Put("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(stof(arraySplit[0]),
					   stof(arraySplit[1]),
					   stof(arraySplit[2]));
		tmpMotionArray[0].pushKeyFrame(
			tmpQ,
			fk_Vector(stof(arraySplit[3]),
					  stof(arraySplit[4]),
					  stof(arraySplit[5])),
			fk_Vector(stof(arraySplit[8]),
					  stof(arraySplit[9]),
					  stof(arraySplit[10])),
			stoi(arraySplit[6]),
			(fk_MotionInterType)stoi(arraySplit[7])
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	_st objIndex = 0;
	while(true) {
		if(!getline(in_file, lineStr)) {
			Error::Put("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= _st(_m->objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		vector<string> arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 11) {
			Error::Put("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(stof(arraySplit[0]), stof(arraySplit[1]), stof(arraySplit[2]));
		tmpMotionArray[objIndex].pushKeyFrame(
			tmpQ,
			fk_Vector(stof(arraySplit[3]), stof(arraySplit[4]), stof(arraySplit[5])),
			fk_Vector(stof(arraySplit[8]), stof(arraySplit[9]), stof(arraySplit[10])),
			stoi(arraySplit[6]), fk_MotionInterType(stoi(arraySplit[7]))
		);
	}

	// モーション複数化対応
	_m->keyFrameData.push_back(tmpMotionArray);
	_m->nowFrame.push_back(0);
	int totalFrame = 0;
	for(_st i = 0; i < _st(_m->objNum); i++) {
		int curFrame = _m->keyFrameData.back().at(i).getTotalFrameNum();
		if(totalFrame < curFrame) totalFrame = curFrame;
	}
	_m->maxFrame.push_back(totalFrame);

	return true;
}

void fk_Performer::entryScene(fk_Scene *argScene)
{
	for(_st i = 0; i < _st(_m->objNum); i++) {
		argScene->entryModel(_m->objModel[i].get());
	}

	return;
}

void fk_Performer::removeScene(fk_Scene *argScene)
{
	for(_st i = 0; i < _st(_m->objNum); i++) {
		argScene->removeModel(_m->objModel[i].get());
	}

	return;

}

void fk_Performer::setDrawMode(bool argMode)
{
	if(!argMode) {
		_m->draw_mode = fk_Draw::LINE;
		for(_st i = 1; i < _st(_m->objNum); i++) {
			if(_m->texTable[_st(_m->matTable[i-1])] != -1) {
				fk_IFSTexture *ifsTex = dynamic_cast<fk_IFSTexture *>(_m->mesh[i-1].lock().get());
				_m->objModel[i]->setShape(ifsTex->getIFS());
			}
			_m->objModel[i]->setDrawMode(_m->draw_mode);
		}
	} else {
		for(_st i = 1; i < _st(_m->objNum); i++) {
			_m->objModel[i]->setShape(_m->mesh[i-1].lock().get());
		}
	}

	return;
}

fk_Model * fk_Performer::getBaseModel(void)
{
	return &_m->absParent;
}

int fk_Performer::getObjectNum(void)
{
	return _m->objNum;
}

fk_Model * fk_Performer::getObjectModel(int argID)
{
	if(argID < 0 || argID >= _m->objNum) return nullptr;
	return _m->objModel[_st(argID)].get();
}

fk_Model * fk_Performer::getJointModel(int argID)
{
	if(argID < 0 || argID >= _m->objNum) return nullptr;
	return _m->jointModel[_st(argID)].get();
}

void fk_Performer::jointToPoser(void)
{
	if(_m->parentConnect) return;
	if(_m->objNum == 0) return;

	for(auto ite = _m->parentTable.begin(); ite != _m->parentTable.end(); ite++) {
		fk_Model *parent = _m->jointModel[_st(ite->second)].get();
		_m->jointModel[_st(ite->first)]->setParent(parent, true);
	}

	for(_st i = 0; i < _st(_m->objNum); i++) {
		_m->objModel[i]->setParent(_m->jointModel[i].get(), true);
	}

	_m->jointModel[0]->setParent(&_m->absParent, false);

	_m->parentConnect = true;

	return;
}

int fk_Performer::getNowFrame(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(_m->keyFrameData.size())) return -1;
	return _m->nowFrame[_st(argMotionID)];
}

int fk_Performer::getTotalFrame(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(_m->keyFrameData.size())) return -1;
	return _m->maxFrame[_st(argMotionID)];
}

void fk_Performer::setNowFrame(int argMotionID, int argFrame)
{
	if(argMotionID < 0 || argMotionID >= int(_m->keyFrameData.size())) return;
	if(argFrame < 0 || _m->maxFrame[_st(argMotionID)] < argFrame) return;
	_m->nowFrame[_st(argMotionID)] = argFrame;
}

bool fk_Performer::isMotionFinished(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(_m->keyFrameData.size())) return false;
	if(_m->nowFrame[_st(argMotionID)] >= _m->maxFrame[_st(argMotionID)]) return true;
	else return false;
}

int fk_Performer::getLoopCount(void)
{
	return _m->loopCnt;
}

bool fk_Performer::playMotion(int argMotionID)
{
	_st motionID = _st(argMotionID);

	if(argMotionID < 0 || motionID >= _m->keyFrameData.size()) return false;

	// 長さのないモーションを再生しようとした場合
	if(_m->maxFrame[motionID] == 0) return false;

	// 前フレと違うモーションを再生する場合は最初から
	if(_m->prevPlayMotionID != argMotionID) {
		_m->nowFrame[_st(_m->prevPlayMotionID)] = 0;
		_m->nowFrame[motionID] = 0;
		_m->loopCnt = 0;
	}

	// ループ時の処理
	if(_m->nowFrame[motionID] > _m->maxFrame[motionID]) {
		_m->nowFrame[motionID] = 0;
		_m->loopCnt++;
	}
	// 再生
	_m->nowFrame[motionID]++;

	for(_st i = 0; i < _st(_m->objNum); i++) {
		int ret = _m->keyFrameData[motionID][i].setFrameState(_m->nowFrame[motionID],
															  _m->jointModel[i].get());
		if(i == 0) continue;
		if(ret == 1) {
			if(!_m->visibleInfo[i]) {
				if(_m->draw_mode == fk_Draw::LINE) {
					_m->objModel[i]->setDrawMode(_m->draw_mode);
				} else {
					_m->objModel[i]->setShape(_m->mesh[i-1].lock().get());
				}
			}
			_m->visibleInfo[i] = true;
		} else if(ret == -1) {
			if(_m->visibleInfo[i]) {
				_m->objModel[i]->setDrawMode(fk_Draw::NONE);
			}
			_m->visibleInfo[i] = false;
		}
	}
	_m->prevPlayMotionID = argMotionID;

	return true;
}

void fk_Performer::stillMotion(int argMotionID, int argFrame)
{
	if(argMotionID < 0 || argMotionID >= int(_m->keyFrameData.size())) return;
	if(argFrame < 0 || _m->maxFrame[_st(argMotionID)] < argFrame) return;

	for(_st i = 0; i < _st(_m->objNum); i++) {
		int ret = _m->keyFrameData[_st(argMotionID)][i].setFrameState(argFrame,
																	  _m->jointModel[i].get());
		if(i == 0) continue;
		if(ret == 1) {
			if(!_m->visibleInfo[i]) {
				if(_m->draw_mode == fk_Draw::LINE) {
					_m->objModel[i]->setDrawMode(_m->draw_mode);
				} else {
					_m->objModel[i]->setShape(_m->mesh[i-1].lock().get());
				}
			}
			_m->visibleInfo[i] = true;
		} else if(ret == -1) {
			if(_m->visibleInfo[i]) {
				_m->objModel[i]->setDrawMode(fk_Draw::NONE);
			}
			_m->visibleInfo[i] = false;
		}
	}

	return;
}

// カメラとしてセットする
void fk_Performer::setAsCamera(fk_Scene *argScn)
{
	init();
	_m->objNum = 2;
	_m->visibleInfo.resize(_st(_m->objNum));

	_m->jointModel.push_back(make_unique<fk_Model>());
	_m->objModel.push_back(make_unique<fk_Model>());
	_m->objName.push_back("<target>");

	_m->jointModel.push_back(make_unique<fk_Model>());
	_m->objModel.push_back(make_unique<fk_Model>());
	_m->objName.push_back("<camera>");

	shared_ptr<fk_Shape> ptr(nullptr);
	_m->mesh.push_back(ptr);

	_m->parentTable[1] = 0;

	jointToPoser();

	argScn->entryCamera(_m->jointModel[1].get());

	return;
}

void fk_Performer::SetFinalizeMode(void)
{
	_st i;

	for(i = 0; i < _m->jointModel.size(); i++) {
		_m->jointModel[i]->SetTreeDelMode(false);
	}

	for(i = 0; i < _m->objModel.size(); i++) {
		_m->objModel[i]->SetTreeDelMode(false);
	}

	_m->absParent.SetTreeDelMode(false);
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
