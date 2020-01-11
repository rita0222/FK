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
#define FK_DEF_SIZETYPE
#include <FK/MotionCharactor.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

map<string, fk_Shape *>			fk_Performer::shapeCache;
map<string, fk_Image *>			fk_Performer::imageCache;
map<fk_BaseObject *, int>		fk_Performer::countCache;
map<fk_BaseObject *, string>	fk_Performer::reverseCache;

typedef string::size_type st;

static vector<string> fk_StrSplit(const string &argStr, const string &argToken)
{
	vector<string>		retStrArray;
	string::size_type	curPos = 0, nextPos = 0;

	while(nextPos != string::npos) {
		nextPos = argStr.find(argToken, curPos);
		retStrArray.push_back(argStr.substr(curPos, nextPos-curPos));
		curPos = nextPos+1;
	}

	return retStrArray;
}

fk_Performer::fk_Performer(void)
{
	init();

	return;
}

fk_Performer::~fk_Performer(void)
{
	init();
}

bool fk_Performer::cloneCharactor(fk_Performer *argOrg)
{
	init();

	mesh          = argOrg->mesh;
	for(st i = 0; i < mesh.size(); i++) {
		countCache[mesh[i]]++;
	}
	matPalette    = argOrg->matPalette;
	matTable      = argOrg->matTable;
	texImage      = argOrg->texImage;
	for(st i = 0; i < texImage.size(); i++) {
		countCache[texImage[i]]++;
	}
	texName       = argOrg->texName;
	texTable      = argOrg->texTable;
	mqoName       = argOrg->mqoName;
	objNum        = argOrg->objNum;
	objName       = argOrg->objName;
	parentTable   = argOrg->parentTable;
	parentConnect = argOrg->parentConnect;

	keyFrameData  = argOrg->keyFrameData;
	nowFrame      = argOrg->nowFrame;
	maxFrame      = argOrg->maxFrame;
	visibleInfo   = argOrg->visibleInfo;
	draw_mode     = argOrg->draw_mode;

	prevPlayMotionID = argOrg->prevPlayMotionID;
	loopCnt          = argOrg->loopCnt;

	jointModel.resize(st(objNum));
	objModel.resize(st(objNum));
	for(st i = 0; i < st(objNum); i++) {
		jointModel[i] = new fk_Model;
		objModel[i] = new fk_Model;
		if(i > 0) {
			objModel[i]->setShape(mesh[i-1]);
			objModel[i]->setMaterial(matPalette[st(matTable[i-1])]);
			objModel[i]->setSmoothMode(true);
		}
		objModel[i]->glMoveTo(argOrg->objModel[i]->getPosition());
		objModel[i]->glAngle(argOrg->objModel[i]->getAngle());
		objModel[i]->setScale(argOrg->objModel[i]->getScale());
		objModel[i]->setScale(argOrg->objModel[i]->getScale(fk_Axis::X),
								argOrg->objModel[i]->getScale(fk_Axis::Y),
								argOrg->objModel[i]->getScale(fk_Axis::Z));
		jointModel[i]->glMoveTo(argOrg->jointModel[i]->getPosition());
		jointModel[i]->glAngle(argOrg->jointModel[i]->getAngle());
		jointModel[i]->setScale(argOrg->jointModel[i]->getScale());
		jointModel[i]->setScale(argOrg->jointModel[i]->getScale(fk_Axis::X),
								argOrg->jointModel[i]->getScale(fk_Axis::Y),
								argOrg->jointModel[i]->getScale(fk_Axis::Z));
	}
	if(parentConnect) {
		for(auto ite = parentTable.begin(); ite != parentTable.end(); ite++) {
			jointModel[st(ite->first)]->setParent(jointModel[st(ite->second)], false);
		}
		for(st i = 0; i < st(objNum); i++) {
			objModel[i]->setParent(jointModel[i], false);
		}
		jointModel[0]->setParent(&absParent, false);
	}
	absParent.glMoveTo(argOrg->absParent.getPosition());
	absParent.glAngle(argOrg->absParent.getAngle());
	absParent.setScale(argOrg->absParent.getScale());
	absParent.setScale(argOrg->absParent.getScale(fk_Axis::X),
						argOrg->absParent.getScale(fk_Axis::Y),
						argOrg->absParent.getScale(fk_Axis::Z));

	return true;
}

void fk_Performer::init()
{
	for(st i = 0; i < objModel.size(); i++) {
		delete objModel[i];
	}
	objModel.clear();
	for(st i = 0; i < jointModel.size(); i++) {
		delete jointModel[i];
	}
	jointModel.clear();

	for(st i = 0; i < mesh.size(); i++) {
		countCache[mesh[i]]--;
		if(countCache[mesh[i]] == 0) {
			if(mesh[i]->getObjectType() == fk_Type::IFSTEXTURE) {
				delete (fk_IFSTexture *)mesh[i];
			} else if(mesh[i]->getObjectType() == fk_Type::INDEXFACESET) {
				delete (fk_IndexFaceSet *)mesh[i];
			} else {
				delete mesh[i];
			}
			shapeCache.erase(reverseCache.find(mesh[i])->second);
			reverseCache.erase(mesh[i]);
			countCache.erase(mesh[i]);
		}
	}
	mesh.clear();
	for(unsigned int i = 0; i < texImage.size(); i++) {
		countCache[texImage[i]]--;
		if(countCache[texImage[i]] == 0) {
			delete texImage[i];
			imageCache.erase(reverseCache.find(texImage[i])->second);
			reverseCache.erase(texImage[i]);
			countCache.erase(texImage[i]);
		}
	}
	texImage.clear();

	objName.clear();
	texName.clear();
	texTable.clear();
	matTable.clear();
	matPalette.clear();

	parentTable.clear();
	keyFrameData.clear();

	mqoName.clear();
	objNum = 0;
	parentConnect = false;

	visibleInfo.clear();

	// モーション複数化対応
	nowFrame.clear();
	maxFrame.clear();

	prevPlayMotionID = 0;
	loopCnt = 0;

	return;
}

// MQO ファイルからオブジェクト名を列挙する
bool fk_Performer::EnumObjectName(const string &argFileName)
{
	ifstream			in_file(argFileName.c_str());
	vector<string>		readBuf(1), lineStr;
	string::size_type	openPos, closePos;
	st					i = 0, j = 0, k = 0;
	fk_Material			tmpMat;
	fk_Color			tmpCol;
	float				tmpParam[5];
	bool				tmpFlag;

	if(!in_file.is_open()) return false;

	while(getline(in_file, readBuf.at(i))) {
		i++;
		readBuf.push_back("");
	}

	// マテリアル情報の抽出
	for(i = 0; i < readBuf.size(); i++) {
		if(readBuf[i].find("Material") != string::npos) {
			i++;
			while(readBuf[i].find("}") == string::npos) {
				lineStr = fk_StrSplit(readBuf[i], " ");
				for(j = 0; j < lineStr.size(); j++) {
					if(lineStr[j].find("col(") == string::npos) continue;
					// base color
					tmpCol.set(atof(lineStr[j].substr(4, 5).c_str()),
						atof(lineStr[j+1].c_str()),
						atof(lineStr[j+2].c_str()),
						atof(lineStr[j+3].substr(0, 5).c_str())
					);
					// dif
					tmpParam[0] = (float)atof(lineStr[j+4].substr(4, 5).c_str());
					// amb
					tmpParam[1] = (float)atof(lineStr[j+5].substr(4, 5).c_str());
					// emi
					tmpParam[2] = (float)atof(lineStr[j+6].substr(4, 5).c_str());
					// spe
					tmpParam[3] = (float)atof(lineStr[j+7].substr(4, 5).c_str());
					// power
					tmpParam[4] = (float)atof(lineStr[j+8].substr(6, 4).c_str());
					// set
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

					matPalette.push_back(tmpMat);

					if(j+9 >= lineStr.size()) {
						texTable.push_back(-1);
						break;
					}

					openPos = lineStr[j+9].find("tex(");
					if(openPos == string::npos) break;
					closePos = lineStr[j+9].find_last_of('\"');
					if(closePos == string::npos) break;

					tmpFlag = false;
					for(k = 0; k < texName.size(); k++) {
						if(texName[k] == lineStr[j+9].substr(openPos+5, closePos-openPos-5)) {
							texTable.push_back(int(k));
							tmpFlag = true;
							break;
						}
					}
					if(!tmpFlag) {
						texName.push_back(lineStr[j+9].substr(openPos+5, closePos-openPos-5));
						texTable.push_back(int(texName.size()-1));
					}
				}
				i++;
			}
			break;
		}
	}

	// オブジェクト名の列挙]
	objName.push_back("<base>");
	for(i = 0; i < readBuf.size(); i++) {
		openPos = readBuf[i].find("Object \"");
		if(openPos != string::npos) {
			closePos = readBuf[i].find_last_of('\"');
			if(closePos == string::npos) return false;
			objName.push_back(readBuf[i].substr(openPos+8, closePos-openPos-8));
			while(true) {
				i++;
				// マテリアル指定の抽出
				if(readBuf[i].find("M(") != string::npos) {
					// UV 指定のないオブジェクトも読めるように
					string::size_type	tmpPos = readBuf[i].find(")", readBuf[i].find("M(")+1);

					if(tmpPos == string::npos) return false;

					string	intStr = readBuf[i].substr(readBuf[i].find("M(")+2, tmpPos-readBuf[i].find("M(")-2);
					matTable.push_back(atoi(intStr.c_str()));
					break;
				}
			}
		}
	}

	return true;
}

// MQO ファイルから形状とテクスチャを読み込む
bool fk_Performer::loadObjectData(const string &argFileName)
{
	string		texPath, putStr;
	fk_Image	alphaChannel;

	init();

	// オブジェクトの読み込み
	if(!EnumObjectName(argFileName)) {
		fk_PutError("Enum Object Error.");
		init();
		return false;
	}
	objNum = int(objName.size());

	jointModel.resize(st(objNum));
	objModel.resize(st(objNum));
	mesh.resize(st(objNum-1));
	texImage.resize(texName.size());

	texPath = argFileName.substr(0, argFileName.find_last_of('/')+1);
	mqoName = argFileName.substr(argFileName.find_last_of('/')+1, string::npos);

	visibleInfo.resize(st(objNum));

	// テクスチャロード
	for(unsigned int i = 0; i < texName.size(); i++) {
		if(imageCache.count(texPath+texName[i]) > 0) {
			texImage[i] = imageCache[texPath+texName[i]];
			countCache[texImage[i]]++;
		} else {
			texImage[i] = new fk_Image;
			imageCache[texPath+texName[i]] = texImage[i];
			reverseCache[texImage[i]] = texPath+texName[i];
			countCache[texImage[i]] = 1;

			// PNG 対応
			if(texName[i].rfind(".png") != string::npos ||
			   texName[i].rfind(".PNG") != string::npos ||
			   texName[i].rfind(".Png") != string::npos) {
				if(!texImage[i]->readPNG(texPath+texName[i])) {
					putStr = "Texture File(" + texPath + texName[i] + ") Read Error.";
					fk_PutError(putStr);
					init();
					return false;
				}
			} else if(texName[i].rfind(".jpg") != string::npos ||
					  texName[i].rfind(".JPG") != string::npos ||
					  texName[i].rfind(".Jpg") != string::npos ||
					  texName[i].rfind(".jpeg") != string::npos ||
					  texName[i].rfind(".JPEG") != string::npos ||
					  texName[i].rfind(".Jpeg") != string::npos) {
				if(!texImage[i]->readJPG(texPath+texName[i])) {
					putStr = "Texture File(" + texPath + texName[i] + ") Read Error.";
					fk_PutError(putStr);
					init();
					return false;
				}
			} else if(texImage[i]->readBMP(texPath+texName[i])) {
				if(alphaChannel.readBMP(texPath+texName[i].substr(0, texName[i].size()-4)+"_a.bmp")) {
					for(int y = 0; y < alphaChannel.getHeight(); y++) {
						for(int x = 0; x < alphaChannel.getWidth(); x++) {
							texImage[i]->setA(x, y, alphaChannel.getR(x, y));
						}
					}
				}
			} else {
				putStr = "Texture File(" + texPath + texName[i] + ") Read Error.";
				fk_PutError(putStr);
				init();
				return false;
			}
		}
	}

	// 形状ロード
	for(st i = 0; i < st(objNum); i++) {
		jointModel[i] = new fk_Model;
		objModel[i] = new fk_Model;
		if(i > 0) {
			if(shapeCache.count(argFileName+objName[i]) > 0) {
				mesh[i-1] = shapeCache[argFileName+objName[i]];
				countCache[mesh[i-1]]++;
			} else {
				if(texTable[st(matTable[i-1])] != -1) {
					mesh[i-1] = new fk_IFSTexture;
					((fk_IFSTexture *)mesh[i-1])->setImage(texImage[st(texTable[st(matTable[i-1])])]);
					((fk_IFSTexture *)mesh[i-1])->setTexRendMode(fk_TexRendMode::SMOOTH);

					if(!((fk_IFSTexture *)mesh[i-1])->readMQOFile(argFileName, objName[i])) {
						fk_PutError("MQO File Read Error.");
						init();
						return false;
					}
				} else {
					mesh[i-1] = new fk_IndexFaceSet;
					if(!((fk_IndexFaceSet *)mesh[i-1])->readMQOFile(argFileName, objName[i])) {
						fk_PutError("MQO File Read Error.");
						init();
						return false;
					}
				}
				shapeCache[argFileName+objName[i]] = mesh[i-1];
				reverseCache[mesh[i-1]] = argFileName+objName[i];
				countCache[mesh[i-1]] = 1;
			}

			objModel[i]->setShape(mesh[i-1]);
			objModel[i]->setMaterial(matPalette[st(matTable[i-1])]);
			objModel[i]->setSmoothMode(true);

			parentTable[int(i)] = 0;
		}
		visibleInfo[i] = true;
	}

	return true;
}

// FKC ファイルから親子関係と接続位置情報を読み込む
bool fk_Performer::loadJointData(const string &argFileName)
{
	ifstream			in_file(argFileName.c_str());
	string				lineStr;
	vector<string>		arraySplit, readBuf(1);
	st					objIndex = 0;

	// オープン正否判定
	if(!in_file.is_open()) return false;

	// ヘッダチェック
	if(!getline(in_file, lineStr)) return false;
	if(lineStr.find("FKC_HEADER_0.2") == string::npos) return false;

	// 親子関係列挙ブロック探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[ENUM PARENT TABLE BEGIN]") == string::npos);

	// 親子関係読み込み
	parentTable.clear();
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[ENUM PARENT TABLE END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 2) return false;
		parentTable[atoi(arraySplit[0].c_str())] = atoi(arraySplit[1].c_str());
	}

	// 接続位置情報探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[ENUM JOINT POSITION BEGIN]") == string::npos);

	// 接続位置情報読み込み
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[ENUM JOINT POSITION END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 3) return false;
		jointModel[st(objIndex)]->glMoveTo(atof(arraySplit[0].c_str()),
										   atof(arraySplit[1].c_str()),
										   atof(arraySplit[2].c_str()));
		objIndex++;
		if(objIndex >= st(objNum)) break;
	}

	jointToPoser();

	return true;
}

// FKM ファイルからモーションデータを読み込む
bool fk_Performer::loadMotionData(const string &argFileName)
{
	ifstream			in_file(argFileName.c_str());
	string				lineStr;
	vector<string>		arraySplit, readBuf(1);
	st					objIndex = 0;

	// モーション複数化対応
	int	totalFrame = 0;
	vector<fk_PerformerMotion>	tmpMotionArray;
	tmpMotionArray.resize(st(objNum));

	// オープン正否判定
	if(!in_file.is_open()) return false;

	// ヘッダチェック
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
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 9) return false;
		tmpMotionArray[0].pushKeyFrame(
			fk_Quaternion(atof(arraySplit[0].c_str()),
						  atof(arraySplit[1].c_str()),
						  atof(arraySplit[2].c_str()),
						  atof(arraySplit[3].c_str())),
			fk_Vector(atof(arraySplit[4].c_str()),
					  atof(arraySplit[5].c_str()),
					  atof(arraySplit[6].c_str())),
			atoi(arraySplit[7].c_str()), (fk_MotionInterType)atoi(arraySplit[8].c_str())
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) return false;
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	while(true) {
		getline(in_file, lineStr);
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= st(objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 9) return false;
		tmpMotionArray[objIndex].pushKeyFrame(
			fk_Quaternion(atof(arraySplit[0].c_str()),
						  atof(arraySplit[1].c_str()),
						  atof(arraySplit[2].c_str()),
						  atof(arraySplit[3].c_str())),
			fk_Vector(atof(arraySplit[4].c_str()),
					  atof(arraySplit[5].c_str()),
					  atof(arraySplit[6].c_str())),
			atoi(arraySplit[7].c_str()),
			(fk_MotionInterType)atoi(arraySplit[8].c_str())
		);
	}

	// モーション複数化対応
	keyFrameData.push_back(tmpMotionArray);
	nowFrame.push_back(0);
	totalFrame = 0;
	for(st i = 0; i < st(objNum); i++) {
		if(totalFrame < keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum()) {
			totalFrame =  keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum();
		}
	}
	maxFrame.push_back(totalFrame);

	return true;
}

// FKM ファイルからモーションデータを読み込む(オイラー角版)
bool fk_Performer::LoadMotionDataEuler(const string &argFileName)
{
	ifstream			in_file(argFileName.c_str());
	string				lineStr;
	vector<string>		arraySplit;
	st					objIndex = 0;
	fk_Quaternion		tmpQ;

	// モーション複数化対応
	int	totalFrame = 0;
	vector<fk_PerformerMotion>	tmpMotionArray;
	tmpMotionArray.resize(st(objNum));

	// オープン正否判定
	if(!in_file.is_open()) {
		fk_PutError("ファイルが開けません。");
		return false;
	}

	// ヘッダチェック
	if(!getline(in_file, lineStr)) {
		fk_PutError("ファイルが途中で終わっています。");
		return false;
	}
	if(lineStr.find("FKM_HEADER_0.3") == string::npos) {
		fk_PutError("違う種類のファイルを読み込もうとしました。");
		return false;
	}

	// 親オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[PARENT OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 親オブジェクトキーフレーム読み込み
	tmpMotionArray[0].init();
	while(true) {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[PARENT OBJECT KEYFRAME DATA END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 8) {
			fk_PutError("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(atof(arraySplit[0].c_str()), atof(arraySplit[1].c_str()), atof(arraySplit[2].c_str()));
		tmpMotionArray[0].pushKeyFrame(
			tmpQ,
			fk_Vector(atof(arraySplit[3].c_str()), atof(arraySplit[4].c_str()), atof(arraySplit[5].c_str())),
			atoi(arraySplit[6].c_str()), (fk_MotionInterType)atoi(arraySplit[7].c_str())
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	while(true) {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= st(objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 8) {
			fk_PutError("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(atof(arraySplit[0].c_str()), atof(arraySplit[1].c_str()), atof(arraySplit[2].c_str()));
		tmpMotionArray[objIndex].pushKeyFrame(
			tmpQ,
			fk_Vector(atof(arraySplit[3].c_str()), atof(arraySplit[4].c_str()), atof(arraySplit[5].c_str())),
			atoi(arraySplit[6].c_str()), (fk_MotionInterType)atoi(arraySplit[7].c_str())
		);
	}

	// モーション複数化対応
	keyFrameData.push_back(tmpMotionArray);
	nowFrame.push_back(0);
	totalFrame = 0;
	for(st i = 0; i < st(objNum); i++) {
		if(totalFrame < keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum()) {
			totalFrame =  keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum();
		}
	}
	maxFrame.push_back(totalFrame);

	return true;
}

// FKM ファイルからモーションデータを読み込む(スケール対応版)
bool fk_Performer::LoadMotionDataEulerScale(const string &argFileName)
{
	ifstream			in_file(argFileName.c_str());
	string				lineStr;
	vector<string>		arraySplit;
	st					objIndex = 0;
	fk_Quaternion		tmpQ;

	// モーション複数化対応
	int	totalFrame = 0;
	vector<fk_PerformerMotion>	tmpMotionArray;
	tmpMotionArray.resize(st(objNum));

	// オープン正否判定
	if(!in_file.is_open()) {
		fk_PutError("ファイルが開けません。");
		return false;
	}

	// ヘッダチェック
	if(!getline(in_file, lineStr)) {
		fk_PutError("ファイルが途中で終わっています。");
		return false;
	}
	if(lineStr.find("FKM_HEADER_0.31") == string::npos) {
		fk_PutError("違う種類のファイルを読み込もうとしました。");
		return false;
	}

	// 親オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[PARENT OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 親オブジェクトキーフレーム読み込み
	tmpMotionArray[0].init();
	while(true) {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[PARENT OBJECT KEYFRAME DATA END]") != string::npos) break;
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 11) {
			fk_PutError("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(atof(arraySplit[0].c_str()), atof(arraySplit[1].c_str()), atof(arraySplit[2].c_str()));
		tmpMotionArray[0].pushKeyFrame(
			tmpQ,
			fk_Vector(atof(arraySplit[3].c_str()), atof(arraySplit[4].c_str()), atof(arraySplit[5].c_str())),
			fk_Vector(atof(arraySplit[8].c_str()), atof(arraySplit[9].c_str()), atof(arraySplit[10].c_str())),
			atoi(arraySplit[6].c_str()), (fk_MotionInterType)atoi(arraySplit[7].c_str())
		);
	}

	// 子オブジェクトキーフレームブロック探索
	do {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
	} while(lineStr.find("[CHILD OBJECT KEYFRAME DATA BEGIN]") == string::npos);

	// 子オブジェクトキーフレーム読み込み
	while(true) {
		if(!getline(in_file, lineStr)) {
			fk_PutError("ファイルが途中で終わっています。");
			return false;
		}
		if(lineStr.find("[CHILD OBJECT KEYFRAME DATA END]") != string::npos) break;
		if(lineStr.find("BEGIN") != string::npos) {
			objIndex++;
			if(objIndex >= st(objNum)) break;
			tmpMotionArray[objIndex].init();
			continue;
		} else if(lineStr.find("END") != string::npos) {
			continue;
		}
		arraySplit = fk_StrSplit(lineStr, ",");
		if(arraySplit.size() < 11) {
			fk_PutError("データの形式が想定と異なります。");
			return false;
		}
		tmpQ.makeEuler(atof(arraySplit[0].c_str()), atof(arraySplit[1].c_str()), atof(arraySplit[2].c_str()));
		tmpMotionArray[objIndex].pushKeyFrame(
			tmpQ,
			fk_Vector(atof(arraySplit[3].c_str()), atof(arraySplit[4].c_str()), atof(arraySplit[5].c_str())),
			fk_Vector(atof(arraySplit[8].c_str()), atof(arraySplit[9].c_str()), atof(arraySplit[10].c_str())),
			atoi(arraySplit[6].c_str()), (fk_MotionInterType)atoi(arraySplit[7].c_str())
		);
	}

	// モーション複数化対応
	keyFrameData.push_back(tmpMotionArray);
	nowFrame.push_back(0);
	totalFrame = 0;
	for(st i = 0; i < st(objNum); i++) {
		if(totalFrame < keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum()) {
			totalFrame =  keyFrameData[keyFrameData.size()-1][i].getTotalFrameNum();
		}
	}
	maxFrame.push_back(totalFrame);

	return true;
}

void fk_Performer::entryScene(fk_Scene *argScene)
{
	for(st i = 0; i < st(objNum); i++) {
		argScene->entryModel(objModel[i]);
	}

	return;
}

void fk_Performer::removeScene(fk_Scene *argScene)
{
	for(st i = 0; i < st(objNum); i++) {
		argScene->removeModel(objModel[i]);
	}

	return;

}

void fk_Performer::setDrawMode(bool argMode)
{
	if(!argMode) {
		draw_mode = fk_Draw::LINE;
		for(st i = 1; i < st(objNum); i++) {
			if(texTable[st(matTable[i-1])] != -1) {
				objModel[i]->setShape(((fk_IFSTexture *)mesh[i-1])->getIFS());
			}
			objModel[i]->setDrawMode(draw_mode);
		}
	} else {
		for(st i = 1; i < st(objNum); i++) {
			objModel[i]->setShape(mesh[i-1]);
		}
	}

	return;
}

fk_Model * fk_Performer::getBaseModel(void)
{
	return &absParent;
}

int fk_Performer::getObjectNum(void)
{
	return objNum;
}

fk_Model * fk_Performer::getObjectModel(int argID)
{
	if(argID < 0 || argID >= objNum) return nullptr;
	return objModel[st(argID)];
}

fk_Model * fk_Performer::getJointModel(int argID)
{
	if(argID < 0 || argID >= objNum) return nullptr;
	return jointModel[st(argID)];
}

void fk_Performer::jointToPoser(void)
{
	if(parentConnect) return;
	if(objNum == 0) return;

	for(auto ite = parentTable.begin(); ite != parentTable.end(); ite++) {
		jointModel[st(ite->first)]->setParent(jointModel[st(ite->second)], true);
	}

	for(st i = 0; i < st(objNum); i++) {
		objModel[i]->setParent(jointModel[i], true);
	}

	jointModel[0]->setParent(&absParent, false);

	parentConnect = true;

	return;
}

int fk_Performer::getNowFrame(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(keyFrameData.size())) return -1;
	return nowFrame[st(argMotionID)];
}

int fk_Performer::getTotalFrame(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(keyFrameData.size())) return -1;
	return maxFrame[st(argMotionID)];
}

void fk_Performer::setNowFrame(int argMotionID, int argFrame)
{
	if(argMotionID < 0 || argMotionID >= int(keyFrameData.size())) return;
	if(argFrame < 0 || maxFrame[st(argMotionID)] < argFrame) return;
	nowFrame[st(argMotionID)] = argFrame;
}

bool fk_Performer::isMotionFinished(int argMotionID)
{
	if(argMotionID < 0 || argMotionID >= int(keyFrameData.size())) return false;
	if(nowFrame[st(argMotionID)] >= maxFrame[st(argMotionID)]) return true;
	else return false;
}

int fk_Performer::getLoopCount(void)
{
	return loopCnt;
}

bool fk_Performer::playMotion(int argMotionID)
{
	st		motionID = st(argMotionID);

	if(argMotionID < 0 || motionID >= keyFrameData.size()) return false;

	// 長さのないモーションを再生しようとした場合
	if(maxFrame[motionID] == 0) return false;

	// 前フレと違うモーションを再生する場合は最初から
	if(prevPlayMotionID != argMotionID) {
		nowFrame[st(prevPlayMotionID)] = 0;
		nowFrame[motionID] = 0;
		loopCnt = 0;
	}

	// ループ時の処理
	if(nowFrame[motionID] > maxFrame[motionID]) {
		nowFrame[motionID] = 0;
		loopCnt++;
	}
	// 再生
	nowFrame[motionID]++;

	for(st i = 0; i < st(objNum); i++) {
		int ret = keyFrameData[motionID][i].setFrameState(nowFrame[motionID], jointModel[i]);
		if(i == 0) continue;
		if(ret == 1) {
			if(!visibleInfo[i]) {
				if(draw_mode == fk_Draw::LINE) {
					objModel[i]->setDrawMode(draw_mode);
				} else {
					objModel[i]->setShape(mesh[i-1]);
				}
			}
			visibleInfo[i] = true;
		} else if(ret == -1) {
			if(visibleInfo[i]) {
				objModel[i]->setDrawMode(fk_Draw::NONE);
			}
			visibleInfo[i] = false;
		}
	}
	prevPlayMotionID = argMotionID;

	return true;
}

void fk_Performer::stillMotion(int argMotionID, int argFrame)
{
	if(argMotionID < 0 || argMotionID >= int(keyFrameData.size())) return;
	if(argFrame < 0 || maxFrame[st(argMotionID)] < argFrame) return;

	for(st i = 0; i < st(objNum); i++) {
		int ret = keyFrameData[st(argMotionID)][i].setFrameState(argFrame, jointModel[i]);
		if(i == 0) continue;
		if(ret == 1) {
			if(!visibleInfo[i]) {
				if(draw_mode == fk_Draw::LINE) {
					objModel[i]->setDrawMode(draw_mode);
				} else {
					objModel[i]->setShape(mesh[i-1]);
				}
			}
			visibleInfo[i] = true;
		} else if(ret == -1) {
			if(visibleInfo[i]) {
				objModel[i]->setDrawMode(fk_Draw::NONE);
			}
			visibleInfo[i] = false;
		}
	}

	return;
}

// カメラとしてセットする
void fk_Performer::setAsCamera(fk_Scene *argScn)
{
	init();
	objNum = 2;
	visibleInfo.resize(st(objNum));

	jointModel.push_back(new fk_Model);
	objModel.push_back(new fk_Model);
	objName.push_back("<target>");

	jointModel.push_back(new fk_Model);
	objModel.push_back(new fk_Model);
	objName.push_back("<camera>");

	mesh.push_back(nullptr);

	parentTable[1] = 0;

	jointToPoser();

	argScn->entryCamera(jointModel[1]);

	return;
}

void fk_Performer::SetFinalizeMode(void)
{
	_st i;

	for(i = 0; i < jointModel.size(); i++) {
		jointModel[i]->SetTreeDelMode(false);
	}

	for(i = 0; i < objModel.size(); i++) {
		objModel[i]->SetTreeDelMode(false);
	}

	absParent.SetTreeDelMode(false);
}

