#include <FK/ShaderParameter.h>
#include <FK/ShaderProgram.h>
#include <FK/Matrix.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

fk_ShaderParameter::fk_ShaderParameter(void) : lastAppliedId(0), prog(nullptr)
{
}

fk_ShaderParameter::~fk_ShaderParameter()
{
}

void fk_ShaderParameter::SetProgram(fk_ShaderProgram *argProg)
{
	prog = argProg;
}

string fk_ShaderParameter::getLastError(void)
{
	return lastError;
}

void fk_ShaderParameter::setRegister(string argName, float argValue, bool argBuildInMode)
{
	if(argBuildInMode == true && prog->GetUniformStatus(argName) == false) return;
	floatTable[argName] = argValue;
}

void fk_ShaderParameter::setRegister(string argName, vector<float> *argValue,
									 bool argBuildInMode)
{
	if(argBuildInMode == true && prog->GetUniformStatus(argName) == false) return;
	floatArrayTable[argName] = *argValue;
}

void fk_ShaderParameter::setRegister(string argName, int argValue, bool argBuildInMode)
{
	if(argBuildInMode == true && prog->GetUniformStatus(argName) == false) return;
	intTable[argName] = argValue;
}

void fk_ShaderParameter::setRegister(string argName, vector<int> *argValue, bool argBuildInMode)
{
	if(argBuildInMode == true && prog->GetUniformStatus(argName) == false) return;
	intArrayTable[argName] = *argValue;
}

void fk_ShaderParameter::setRegister(string argName, fk_Matrix *argValue, bool argBuildInMode)
{
	if(argBuildInMode == true && prog->GetUniformStatus(argName) == false) return;
	matrixTable[argName] = *argValue;
}

void fk_ShaderParameter::setRegister(string argName, fk_Vector *argValue, bool argBuildInMode)
{
	vector<float> tmp{float(argValue->x), float(argValue->y), float(argValue->z)};
	setRegister(argName, &tmp, argBuildInMode);
}

void fk_ShaderParameter::setRegister(string argName, fk_HVector *argValue, bool argBuildInMode)
{
	vector<float> tmp{float(argValue->x), float(argValue->y),
					  float(argValue->z), float(argValue->w)};
	setRegister(argName, &tmp, argBuildInMode);
}

bool fk_ShaderParameter::removeRegister(string argName)
{
	if (floatTable.erase(argName) > 0) return true;
	if (floatArrayTable.erase(argName) > 0) return true;
	if (intTable.erase(argName) > 0) return true;
	if (intArrayTable.erase(argName) > 0) return true;
	if (matrixTable.erase(argName) > 0) return true;
	return false;
}

void fk_ShaderParameter::reserveAttribute(string argName)
{
	if(attrTable.find(argName) == attrTable.end()) {
		attrTable[argName] = -1;
	}
}

map<string, int> * fk_ShaderParameter::getAttrTable(void)
{
	return &attrTable;
}

bool fk_ShaderParameter::attachTexture(int argUnit, fk_Texture *argTexture)
{
	if (argUnit < 0 || argUnit > 31) return false;
	textureTable[argUnit+1] = argTexture;
	return true;
}

bool fk_ShaderParameter::detachTexture(int argUnit)
{
	return ((textureTable.erase(argUnit) > 0) ? true : false);
}

void fk_ShaderParameter::clearTexture(void)
{
	textureTable.clear();
}

bool fk_ShaderParameter::Apply(GLuint argProgramID)
{
	bool result = true;

	if (lastAppliedId != argProgramID) {
		locationTable.clear();
		lastAppliedId = argProgramID;
	}

	lastError.clear();

	bool changed = false;
	for(auto pair : textureTable) {
		glActiveTexture(GL_TEXTURE0 + GLenum(pair.first));
		pair.second->BindTexture(false);
		changed = true;
	}

	if (changed) glActiveTexture(GL_TEXTURE0);

	for(auto pair : floatTable) {
		GLint location = GetLocation(argProgramID, pair.first);
		if (location >= 0) {
			glUniform1f(location, pair.second);
		} else {
			lastError += "ERROR: " + pair.first + " is not found.";
			result = false;
		}
	}

	for(auto pair : floatArrayTable) {
		GLint location = GetLocation(argProgramID, pair.first);
		if (location >= 0) {
			switch (pair.second.size()) {
			  case 1:
				glUniform1f(location, pair.second[0]);
				break;
			  case 2:
				glUniform2f(location, pair.second[0], pair.second[1]);
				break;
			  case 3:
				glUniform3f(location, pair.second[0], pair.second[1], pair.second[2]);
				break;
			  case 4:
				glUniform4f(location, pair.second[0], pair.second[1],
							pair.second[2], pair.second[3]);
				break;
			  default:
				result = false;
			}
		} else {
			lastError += "ERROR: " + pair.first + " is not found.";
			result = false;
		}
	}

	for(auto pair : intTable) {
		GLint location = GetLocation(argProgramID, pair.first);
		if (location >= 0) {
			glUniform1i(location, pair.second);
		} else {
			lastError += "ERROR: " + pair.first + " is not found.";
			result = false;
		}
	}

	for(auto pair : intArrayTable) {
		GLint location = GetLocation(argProgramID, pair.first);
		if (location >= 0) {
			switch (pair.second.size()) {
			  case 1:
				glUniform1i(location, pair.second[0]);
				break;
			  case 2:
				glUniform2i(location, pair.second[0], pair.second[1]);
				break;
			  case 3:
				glUniform3i(location, pair.second[0], pair.second[1], pair.second[2]);
				break;
			  case 4:
				glUniform4i(location, pair.second[0], pair.second[1],
							pair.second[2], pair.second[3]);
				break;
			  default:
				result = false;
			}
		} else {
			lastError += "ERROR: " + pair.first + " is not found.";
			result = false;
		}
	}

	for(auto pair : matrixTable) {
		GLint location = GetLocation(argProgramID, pair.first);
		if (location >= 0) {
			float *pArray = pair.second.GetBuffer();
			glUniformMatrix4fv(location, 1, GL_FALSE, pArray);
		} else {
			lastError += "ERROR: " + pair.first + " is not found.";
			result = false;
		}
	}

	return result;
}

GLint fk_ShaderParameter::GetLocation(GLuint argProgramID, string argName)
{
	if(locationTable.find(argName) != locationTable.end()) {
		return locationTable[argName];
	}

	GLint location = glGetUniformLocation(argProgramID, argName.c_str());
	if (location >= 0) locationTable[argName] = location;

	return location;
}

void fk_ShaderParameter::BindAttr(GLuint argID)
{
	GLuint locID = 0;

	for(auto itr = attrTable.begin(); itr != attrTable.end(); ++itr) {
		glBindAttribLocation(argID, locID, itr->first.c_str());
		itr->second = int(locID);
		locID++;
	}
}			

/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
