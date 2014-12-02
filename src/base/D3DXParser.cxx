/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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

#include <FK/D3DXParser.H>
#include <FK/D3DXData.H>
#include <FK/D3DXAnimation.H>
#include <FK/D3DXShapeParser.H>
#include <FK/IFSTexture.h>
#include <FK/Error.H>
#include <FK/Tree.h>

using namespace std;

fk_D3DXParser::fk_D3DXParser(void)
{
	ifsTexture = NULL;
	tree = new fk_Tree;
	shape = new fk_D3DXShapeParser;
	tree->clear("_D3DXParser_root");
	anim = NULL;

	return;
}

fk_D3DXParser::~fk_D3DXParser()
{
	delete shape;
	delete tree;
	return;
}

void fk_D3DXParser::SetIFSTexture(fk_IFSTexture *argTexture)
{
	ifsTexture = argTexture;
	SetMeshData(argTexture->getIFS());
	SetAnimation(argTexture->getIFS()->GetAnimation());
	return;
}

void fk_D3DXParser::SetAnimation(fk_D3DXAnimation *argAnim)
{
	anim = argAnim;
	anim->SetTree(tree);
	return;
}

bool fk_D3DXParser::ReadD3DXFile(const string &argFileName,
								 const string &argObjName,
								 int argMateID,
								 bool argSolidFlg,
								 bool *argAnimFlg)
{
	if(CheckFile(argFileName) == false) return false;
	if(ReadData(argFileName, argObjName, argMateID,
				argSolidFlg, argAnimFlg) == false) {
		return false;
	}

	return true;
}

bool fk_D3DXParser::CheckFile(const string &argFileName)
{
	ifstream	ifs(argFileName);
	string		str, word;
	int			bit;

	if(ifs.fail() == true) return false;
	getline(ifs, str);
	str += "\n";
	ifs.close();

	word = PopWord(&str);
	StringToLower(&word);
	if(word != "xof") return false;

	word = PopWord(&str);
	StringToLower(&word);
	if(IsInteger(word.substr(0, 4)) == false ||
	   word.substr(4, string::npos) != "txt") return false;

	word = PopWord(&str);
	if(IsInteger(word) == false) return false;

	bit = Str2Int(word);
	if(bit == 32 || bit == 64) return true;

	return false;
}

bool fk_D3DXParser::CheckOneLineProperty(const string *argLine)
{
	if(argLine->find("{") != string::npos &&
	   argLine->find("}") != string::npos) return true;
	return false;
}

fk_TreeData * fk_D3DXParser::GetProperty(fk_TreeData *argParent,
										 string *argLine)
{
	string					keys;
	fk_TreeData				*newData;
	fk_D3DXPropertyList		*propList = new fk_D3DXPropertyList;

	keys = argLine->substr(0, argLine->find("{"));
	TrimString(&keys);
	newData = tree->addNewChild(argParent, keys);
	propList->SetProperty(PopWord(&keys));
	propList->SetData(PopWord(&keys));
	newData->setObject(propList, true);
	return newData;
}

bool fk_D3DXParser::CheckMeshProperty(fk_TreeData *argData,
									  const string &argObjName)
{
	fk_D3DXPropertyList		*list;
	string					prop;
	fk_TreeData				*tmpData;

	list = static_cast<fk_D3DXPropertyList *>(argData->getObject());
	if(list == NULL) return false;

	prop = list->GetProperty();
	StringToLower(&prop);

	if(prop != "mesh") return false;

	if(argObjName.size() == 0) return true;

	for(tmpData = argData; tmpData != NULL; tmpData = tmpData->getParent()) {
		list = static_cast<fk_D3DXPropertyList *>(tmpData->getObject());
		if(list == NULL) continue;
		if(list->GetData() == argObjName) return true;
	}
	return false;
}

bool fk_D3DXParser::CheckProperty(fk_TreeData *argData,
								  const string &argName)
{
	fk_D3DXPropertyList		*list;
	string					prop, tmpName;

	list = static_cast<fk_D3DXPropertyList *>(argData->getObject());
	if(list == NULL) return false;

	prop = list->GetProperty();
	StringToLower(&prop);
	tmpName = argName;
	StringToLower(&tmpName);

	if(prop == tmpName) return true;
	return false;
}

bool fk_D3DXParser::ReadFrameMatrix(fk_TreeData *argData, ifstream &argIFS)
{
	int					i, j;
	string				word, lineList;
	fk_TreeData			*parent = argData->getParent();
	fk_D3DXPropertyList	*prop;

	if(parent == NULL) return false;
	prop = static_cast<fk_D3DXPropertyList *>(parent->getObject());
	if(prop == NULL) return false;

	word.clear();
	lineList.clear();

	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(GetWord(argIFS, ",;", &lineList, &word) == false) return false;
			TrimString(&word);
			if(IsNumeric(word) == false) return false;
			prop->SetFrameMatrixValue(j, i, Str2Double(word));
		}
	}

	return true;
}

bool fk_D3DXParser::ReadData(const string &argFileName,
							 const string &argObjName,
							 int argMateID,
							 bool argSolidFlg,
							 bool *argAnimFlg)
{
	ifstream		ifs(argFileName);
	string			line, keys, property, argument;
	fk_TreeData		*data, *meshTreeData, *animSetTreeData;
	bool			readFlg;		// 形状読み込み済みチェック
	bool			meshModeFlg;	// Mesh内外フラグ
	bool			skinWeightsFlg;	// skinWeight有無フラグ
	
	*argAnimFlg = false;

	if(ifs.fail()) return false;

	shape->Clear();

	data = tree->getRoot();
	readFlg = meshModeFlg = skinWeightsFlg = false;
	meshTreeData = animSetTreeData = NULL;

	while(getline(ifs, line)) {
		line += "\n";
		if(CheckOneLineProperty(&line) == true) {
			if(*argAnimFlg == true && anim != NULL) {
				anim->SetAnimationName(&line);
			}
			continue;
		}

		if(line.find("{") != string::npos) {
			data = GetProperty(data, &line);

			if(CheckProperty(data, "FrameTransformMatrix") == true) {
				if(ReadFrameMatrix(data, ifs) == false) {
					ifs.close();
					fk_PutError("fk_D3DXParser", "ReadData", 1);
					return false;
				}
			} else if(readFlg == false &&
			   CheckMeshProperty(data, argObjName) == true) {
				meshTreeData = data;
				readFlg = true;
				meshModeFlg = true;
				if(shape->ReadMeshData(data, ifs) == false) {
					ifs.close();
					fk_PutError("fk_D3DXParser", "ReadData", 2);
					return false;
				}
			} else if(meshModeFlg == true) {
				if(CheckProperty(data, "MeshTextureCoords") == true) {
					if(shape->ReadVectorData(ifs, FK_D3DX_T_MODE) == false) {
						ifs.close();
						fk_PutError("fk_D3DXParser", "ReadData", 3);
						return false;
					}
				} else if(CheckProperty(data, "MeshMaterialList") == true) {
					if(shape->ReadMaterialData(ifs) == false) {
						ifs.close();
						fk_PutError("fk_D3DXParser", "ReadData", 4);
						return false;
					}
				} else if(CheckProperty(data, "SkinWeights") == true) {
					if(anim != NULL) {
						if(anim->ReadSkinData(ifs) == false) {
							ifs.close();
							fk_PutError("fk_D3DXParser", "ReadData", 5);
							return false;
						}
					}
					skinWeightsFlg = true;
				}
			} else if(CheckProperty(data, "AnimationSet") == true) {
				*argAnimFlg = true;
				animSetTreeData = data;
			} else if(*argAnimFlg == true) {
				if(CheckProperty(data, "Animation") == true && anim != NULL) {
					anim->MakeNewAnimation();
				} else if(CheckProperty(data, "AnimationKey") == true &&
						  anim != NULL) {
					if(anim->ReadAnimationKey(ifs) == false) {
						ifs.close();
						fk_PutError("fk_D3DXParser", "ReadData", 6);
						return false;
					}
				}
			}
		}

		while(line.find("}") != string::npos) {
			if(data == meshTreeData) {
				meshModeFlg = false;
			} else if(data == animSetTreeData) {
				*argAnimFlg = false;
			}

			data = data->getParent();
			if(data == NULL) {
				ifs.close();
				fk_PutError("fk_D3DXParser", "ReadData", 7);
				return false;
			}
			line.erase(0, line.find("}")+1);
		}
	}

	ifs.close();
	
	if(readFlg == false) {
		fk_PutError("fk_D3DXParser", "ReadData", 8);
		return false;
	}

	if(anim != NULL) {
		anim->MakeAnimationData();
	}

	if(skinWeightsFlg == false) {
		anim->MakeDummySkinWeights(meshTreeData->getParent(),
								   shape->GetOrgVSize());
	}

	return MakeData(argMateID, argSolidFlg);
}

bool fk_D3DXParser::MakeData(int argMateID, bool argSolidFlg)
{
	shape->OptimizeData(argMateID);

	if(meshData != NULL) {
		if(shape->MakeMesh(meshData, argSolidFlg) == false) return false;
	}

	if(ifsTexture != NULL) {
		shape->SetIFSTexCoord(ifsTexture);
	}
	
	if(anim != NULL) {
		anim->MakeSkinMap(shape);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////

void fk_D3DXParser::print(void)
{
	tree->Print();
	shape->Print();

	return;
}
