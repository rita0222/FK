#include <FK/ShaderProgram.h>
#include <FK/ShaderBinder.h>
#include <FK/Window.h>
#include <regex>

using namespace std;
using namespace FK;

string fk_ShaderProgram::vertexBuildIn;
string fk_ShaderProgram::geometryBuildIn;
string fk_ShaderProgram::fragmentBuildIn;
string fk_ShaderProgram::tessCtrlBuildIn;
string fk_ShaderProgram::tessEvalBuildIn;
string fk_ShaderProgram::fboBuildIn;
vector<fk_BuildInKey> fk_ShaderProgram::uniformStack;
vector<fk_BuildInKey> fk_ShaderProgram::attributeStack;

fk_ShaderProgram::Member::Member(void) :
	idProgram(0), idVertex(0), idFragment(0), idGeometry(0), idTessCtrl(0), idTessEval(0),
	parameter(nullptr), fboMode(false)
{
	return;
}

fk_ShaderProgram::fk_ShaderProgram(void) : _m(make_unique<Member>())
{
	if(uniformStack.empty() == true) {
		string uniformStr =
			#include "GLSL/Uniform.out"
			;
		MakeBuildInStack(&uniformStr, &uniformStack);
	}

	if(attributeStack.empty() == true)
	{
		string attributeStr =
			#include "GLSL/Attribute.out"
			;
		MakeBuildInStack(&attributeStr, &attributeStack);
	}
	
	if(vertexBuildIn.empty() == true) {
		vertexBuildIn +=
			#include "GLSL/Struct.out"
			;
	}

	if(geometryBuildIn.empty() == true) {
		geometryBuildIn +=
			#include "GLSL/Struct.out"
			;
	}

	if(fragmentBuildIn.empty() == true) {
		fragmentBuildIn +=
			#include "GLSL/Struct.out"
			;
		fragmentBuildIn +=
			#include "GLSL/Fragment.out"
			;
	}

	if(tessCtrlBuildIn.empty() == true) {
		tessCtrlBuildIn +=
			#include "GLSL/Struct.out"
			;
	}			

	if(tessEvalBuildIn.empty() == true) {
		tessEvalBuildIn +=
			#include "GLSL/Struct.out"
			;
	}			

	if(fboBuildIn.empty() == true) {
		fboBuildIn +=
			#include "GLSL/Struct.out"
			;
		fboBuildIn +=
			#include "GLSL/FBO_BuildIn.out"
			;
	}
	
	return;
}

fk_ShaderProgram::~fk_ShaderProgram()
{
	if(_m->idProgram != 0) DeleteProgram(_m->idProgram);
	if(_m->idVertex != 0) DeleteShader(_m->idVertex);
	if(_m->idGeometry != 0) DeleteShader(_m->idGeometry);
	if(_m->idFragment != 0) DeleteShader(_m->idFragment);
	if(_m->idTessCtrl != 0) DeleteShader(_m->idTessCtrl);
	if(_m->idTessEval != 0) DeleteShader(_m->idTessEval);

	return;
}

void fk_ShaderProgram::SetParameter(fk_ShaderParameter *argP)
{
	_m->parameter = argP;
}

void fk_ShaderProgram::SetFBOMode(bool argMode)
{
	_m->fboMode = argMode;
}

bool fk_ShaderProgram::GetUniformStatus(string argKey)
{
	if(_m->uniformStatus.find(argKey) == _m->uniformStatus.end()) return false;
	return _m->uniformStatus[argKey];
}

bool fk_ShaderProgram::GetAttributeStatus(string argKey)
{
	if(_m->attributeStatus.find(argKey) == _m->attributeStatus.end()) return false;
	return _m->attributeStatus[argKey];
}

bool fk_ShaderProgram::validate(void)
{
	if(vertexShaderSource.empty()) {
		_m->lastError = "ERROR: VertexShader is empty.";
		return false;
	}
	
	if(fragmentShaderSource.empty()) {
		_m->lastError = "ERROR: FragmentShader is empty.";
		return false;
	}

	if(_m->idVertex != 0) {
		DeleteShader(_m->idVertex);
		_m->idVertex = 0;
	}

	if(_m->idFragment != 0) {
		DeleteShader(_m->idFragment);
		_m->idFragment = 0;
	}

	if(_m->idGeometry != 0) {
		DeleteShader(_m->idGeometry);
		_m->idGeometry = 0;
	}

	if(_m->idTessCtrl != 0) {
		DeleteShader(_m->idTessCtrl);
		_m->idTessCtrl = 0;
	}

	if(_m->idTessEval != 0) {
		DeleteShader(_m->idTessEval);
		_m->idTessEval = 0;
	}

	if(fk_ShaderBinder::IsInitialized() == false) {
		if(fk_ShaderBinder::Initialize() == false) {
			_m->lastError = "ERROR: OpenGL Initalize Error.";
			return false;
		}
	}

	_m->idVertex = Compile(&vertexShaderSource, GL_VERTEX_SHADER);
	if(_m->idVertex == 0) {
		_m->lastError = "ERROR: VertexShader could not create.";
		return false;
	}

	if(UpdateLastError(_m->idVertex, "VertexShader")) return false;

	_m->idFragment = Compile(&fragmentShaderSource, GL_FRAGMENT_SHADER);
	if(_m->idFragment == 0) {
		_m->lastError = "ERROR: FragmentShader could not create.";
		return false;
	}
		
	if(UpdateLastError(_m->idFragment, "FragmentShader")) return false;

	if(geometryShaderSource.empty() == false) {
		_m->idGeometry = Compile(&geometryShaderSource, GL_GEOMETRY_SHADER);
		if(_m->idGeometry == 0) {
			_m->lastError = "ERROR: GeometryShader could not create.";
			return false;
		}
		if(UpdateLastError(_m->idGeometry, "GeometryShader")) return false;
	}

	if(tessCtrlShaderSource.empty() == false) {
		_m->idTessCtrl = Compile(&tessCtrlShaderSource, GL_TESS_CONTROL_SHADER);
		if(_m->idTessCtrl == 0) {
			_m->lastError = "ERROR: TessCtrlShader could not create.";
			return false;
		}
		if(UpdateLastError(_m->idTessCtrl, "TessControlShader")) return false;
	}

	if(tessEvalShaderSource.empty() == false) {
		_m->idTessEval = Compile(&tessEvalShaderSource, GL_TESS_EVALUATION_SHADER);
		if(_m->idTessEval == 0) {
			_m->lastError = "ERROR: TessEvalShader could not create.";
			return false;
		}
		if(UpdateLastError(_m->idTessEval, "TessEvalShader")) return false;
	}

	if(_m->idProgram != 0) {
		DeleteProgram(_m->idProgram);
		_m->idProgram = 0;
	}

	_m->idProgram = glCreateProgram();
	if(_m->idProgram == 0) {
		_m->lastError = "ERROR: Could not create program.";
		return false;
	}

	glAttachShader(_m->idProgram, _m->idVertex);
	glAttachShader(_m->idProgram, _m->idFragment);
	if(_m->idGeometry != 0) glAttachShader(_m->idProgram, _m->idGeometry);
	if(_m->idTessCtrl != 0) glAttachShader(_m->idProgram, _m->idTessCtrl);
	if(_m->idTessEval != 0) glAttachShader(_m->idProgram, _m->idTessEval);

	return true;
}

bool fk_ShaderProgram::loadVertexShader(string argFileName)
{
	ifstream		ifs(argFileName);
	if(ifs.fail()) return false;

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	vertexShaderSource = string(it, last);

	return true;
}

bool fk_ShaderProgram::loadFragmentShader(string argFileName)
{
	ifstream		ifs(argFileName);
	if(ifs.fail()) return false;

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	fragmentShaderSource = string(it, last);

	return true;
}

bool fk_ShaderProgram::loadGeometryShader(string argFileName)
{
	ifstream		ifs(argFileName);
	if(ifs.fail()) return false;

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	geometryShaderSource = string(it, last);

	return true;
}

bool fk_ShaderProgram::loadTessCtrlShader(string argFileName)
{
	ifstream		ifs(argFileName);
	if(ifs.fail()) return false;

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	tessCtrlShaderSource = string(it, last);

	return true;
}

bool fk_ShaderProgram::loadTessEvalShader(string argFileName)
{
	ifstream		ifs(argFileName);
	if(ifs.fail()) return false;

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	tessEvalShaderSource = string(it, last);

	return true;
}

GLuint fk_ShaderProgram::getProgramID(void)
{
	return _m->idProgram;
}

string fk_ShaderProgram::getLastError(void)
{
	return _m->lastError;
}

GLuint fk_ShaderProgram::Compile(string *argCode, GLuint argKind)
{
	GLuint id = glCreateShader(argKind);
	if(id == 0) return id;

	ReplaceBuildIn(argCode, argKind);
	
	const GLchar *str[1] = {argCode->c_str()};

	glShaderSource(id, 1, str, nullptr);
	glCompileShader(id);

	return id;
}

bool fk_ShaderProgram::link(void)
{
	_m->parameter->BindAttr(_m->idProgram);

	glLinkProgram(_m->idProgram);

	GLint linked = 0;
	glGetProgramiv(_m->idProgram, GL_LINK_STATUS, &linked);
	if(linked == GL_FALSE) {
		_m->lastError = "ERROR: Shader Link Failed.";
		return false;
	}

	return true;
}

bool fk_ShaderProgram::UpdateLastError(GLuint argShader, string argType)
{
	GLsizei bufSize;
	string tmpError;

	glGetShaderiv(argShader, GL_INFO_LOG_LENGTH, &bufSize);
	if (bufSize > 1) {
		GLchar *infoLog = (GLchar *)malloc(size_t(bufSize));
		if (infoLog != nullptr) {
			GLsizei length;
			glGetShaderInfoLog(argShader, bufSize, &length, infoLog);
			tmpError = infoLog;
			free(infoLog);

			regex lineRegex(R"((.*?)\n)");
			smatch lineMatch;
			auto ite = tmpError.cbegin();
			auto end = tmpError.cend();
			while(regex_search(ite, end, lineMatch, lineRegex)) {
				_m->lastError += argType + ":" + lineMatch.str();
				ite = lineMatch[0].second;
			}
		} else {
			_m->lastError = "ERROR: Could not allocate InfoLog buffer.";
		}

		if(_m->lastError.find("ERROR") != string::npos ||
		   _m->lastError.find("error") != string::npos) {
			return true;
		}
		return false;
	} else {
		_m->lastError.clear();
		return false;
	}
}

void fk_ShaderProgram::ReplaceBuildIn(string *argCode, GLuint argKind)
{
	string	incStr = "#FKBuildIn";
	string::size_type	pos = 0;
	string	buildIn;

	switch(argKind) {
	  case GL_VERTEX_SHADER:
		buildIn = vertexBuildIn;
		break;
		
	  case GL_GEOMETRY_SHADER:
		buildIn = geometryBuildIn;
		break;

	  case GL_FRAGMENT_SHADER:
		buildIn = (_m->fboMode == true) ? fboBuildIn : fragmentBuildIn;
		break;
		
	  case GL_TESS_CONTROL_SHADER:
		buildIn = tessCtrlBuildIn;
		break;

	  case GL_TESS_EVALUATION_SHADER:
		buildIn = tessEvalBuildIn;
		break;

	  default:
		return;
	}

	string tmpStr;
	for(auto pair : uniformStack) {
		if(argCode->find(pair.first) != string::npos) {
			_m->uniformStatus[pair.first] = true;
			tmpStr += pair.second;
		} else {
			if(_m->uniformStatus.find(pair.first) == _m->uniformStatus.end()) {
				_m->uniformStatus[pair.first] = false;
			}
		}
	}
	buildIn += tmpStr;

	tmpStr.clear();
	for(auto pair : attributeStack) {
		if(argCode->find(pair.first) != string::npos) {
			_m->attributeStatus[pair.first] = true;
			tmpStr += pair.second;
		} else {
			if(_m->attributeStatus.find(pair.first) == _m->attributeStatus.end()) {
				_m->attributeStatus[pair.first] = false;
			}
		}
	}
	buildIn += tmpStr;

	while((pos = argCode->find(incStr, pos)) != string::npos) {
		auto lineNum = count(argCode->begin(), argCode->begin() + int(pos), '\n');
		argCode->replace(pos, incStr.length(), buildIn);
		pos += buildIn.length();
		string addLine = "\n#line " + to_string(lineNum+1) + "\n";
		argCode->insert(pos, addLine);
		pos += addLine.length();
	}
	return;
}

void fk_ShaderProgram::DeleteShader(GLuint argID)
{
#ifndef FK_CLI_CODE
	glDeleteShader(argID);
#endif
}

void fk_ShaderProgram::DeleteProgram(GLuint argID)
{
#ifndef FK_CLI_CODE
	glDeleteProgram(argID);
#endif
}

void fk_ShaderProgram::MakeBuildInStack(string *argFile, vector<fk_BuildInKey> *argStack)

{
	regex lineRegex(R"((.*?)\n)");
	regex sepRegex(R"(^\s*(\w+)\s+(\w+)\s+(\w+)(\[.*\])?;\s*$)");
	smatch lineMatch, sepMatch;

	auto ite = argFile->cbegin();
	auto end = argFile->cend();

	while(regex_search(ite, end, lineMatch, lineRegex)) {
		string lineStr = lineMatch.str();
		if(regex_match(lineStr, sepMatch, sepRegex)) {
			argStack->push_back(fk_BuildInKey(sepMatch[3], lineStr));
		}
		ite = lineMatch[0].second;
	}
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
