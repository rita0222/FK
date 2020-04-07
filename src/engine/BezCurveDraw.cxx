#define FK_DEF_SIZETYPE
#include <FK/BezCurveDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_BezCurveDraw::fk_BezCurveDraw(fk_CurveDrawMode argMode)
{
	for(int i = 0; i < C_DRAW_NUM; ++i) {
		for(int j = 0; j < C_DEG_NUM; ++j) {
			for(int k = 0; k < C_SHADOW_NUM; ++k) {
				curveShader[i][j][k] = nullptr;
			}
		}
	}

	mode = argMode;
	return;
}

fk_BezCurveDraw::~fk_BezCurveDraw()
{
	for(int i = 0; i < C_DRAW_NUM; ++i) {
		for(int j = 0; j < C_DEG_NUM; ++j) {
			for(int k = 0; k < C_SHADOW_NUM; ++k) {
				delete curveShader[i][j][k];
			}
		}
	}

	return;
}

void fk_BezCurveDraw::DrawShapeCurve(fk_Model *argModel, bool argShadowSwitch)
{
	auto col = &(argModel->getCurveColor()->col);
	auto modelShader = argModel->getShader();
	auto type = argModel->getShape()->getObjectType();
	fk_BezCurve *bez = nullptr;
	fk_RBezCurve *rBez = nullptr;
	int degree = 0;

	if(type == fk_Type::BEZCURVE) {
		bez = dynamic_cast<fk_BezCurve *>(argModel->getShape());
		degree = bez->getDegree();
	}  else if(type == fk_Type::RBEZCURVE) {
		rBez = dynamic_cast<fk_RBezCurve *>(argModel->getShape());
		degree = rBez->getDegree();
	}

	if(modelShader != nullptr) {
		drawShader = modelShader;
		defaultShaderFlag = false;
		if(drawShader->IsSetup() == false) {
			ParamInit(drawShader->getProgram(), drawShader->getParameter());
		}
	} else {
		DefaultShaderSetup(type, degree, argShadowSwitch);
	}
	
	auto parameter = drawShader->getParameter();

	SetParameter(parameter);
	parameter->setRegister(fk_Shape::curveModelColorName, col, fk_Shape::curveModelColorName);

	if(type == fk_Type::BEZCURVE) {
		bez = dynamic_cast<fk_BezCurve *>(argModel->getShape());
		parameter->setRegister(fk_Shape::degreeName, bez->getDegree(), fk_Shape::degreeName);
	} else if(type == fk_Type::RBEZCURVE) {
		rBez = dynamic_cast<fk_RBezCurve *>(argModel->getShape());
		parameter->setRegister(fk_Shape::degreeName, rBez->getDegree(), fk_Shape::degreeName);
	} else {
		return;
	}

	drawShader->ProcPreShader();

	glEnable(GL_LINE_SMOOTH);

	Draw_Curve(argModel, parameter, argShadowSwitch);

	drawShader->ProcPostShader();
	return;
}

void fk_BezCurveDraw::DefaultShaderSetup(fk_Type argType, int argDegree, bool argShadowSwitch)
{
	fk_CurveDrawType typeID = (argType == fk_Type::BEZCURVE) ?
		fk_CurveDrawType::BEZ : fk_CurveDrawType::RBEZ;

	fk_CurveDrawDeg degID = fk_CurveDrawDeg::D2;

	switch(argDegree) {
	  case 3:
		degID = fk_CurveDrawDeg::D3;
		break;
	
	  case 4:
		degID = fk_CurveDrawDeg::D4;
		break;

	  default:
		break;
	}

	fk_CurveShadowType sID = (argShadowSwitch) ?
		fk_CurveShadowType::SHADOW : fk_CurveShadowType::ELEMENT;

	if(curveShader[int(typeID)][int(degID)][int(sID)] == nullptr) {
		ShaderInit(typeID, degID, sID);
	}
	drawShader = curveShader[int(typeID)][int(degID)][int(sID)];
	defaultShaderFlag = true;
	return;
}
	
void fk_BezCurveDraw::ShaderInit(fk_CurveDrawType argType,
								 fk_CurveDrawDeg argDeg,
								 fk_CurveShadowType argShadow)
{
	fk_ShaderBinder *shader = new fk_ShaderBinder();
	curveShader[int(argType)][int(argDeg)][int(argShadow)] = shader;

	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Curve/VS.out"
		;

	if(argShadow == fk_CurveShadowType::ELEMENT) {
		prog->fragmentShaderSource =
			#include "GLSL/Curve/FS_Elem.out"
			;
	} else {
		prog->fragmentShaderSource =
			#include "GLSL/Common/FS_Discard.out"
			;
	}		

	if(mode == fk_CurveDrawMode::LINE) {
		prog->tessEvalShaderSource =
			#include "GLSL/Curve/TE_Line.out"
			;
	} else {
		prog->tessEvalShaderSource =
			#include "GLSL/Curve/TE_Point.out"
			;
	}

	if(argType == fk_CurveDrawType::BEZ) {
		switch(argDeg) {
		  case fk_CurveDrawDeg::D2:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_Bez2.out"
				;
			break;

		  case fk_CurveDrawDeg::D3:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_Bez3.out"
				;
			break;

		  case fk_CurveDrawDeg::D4:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_Bez4.out"
				;
			break;

		  default:
			break;
		}
	} else {
		switch(argDeg) {
		  case fk_CurveDrawDeg::D2:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_RBez2.out"
				;
			break;

		  case fk_CurveDrawDeg::D3:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_RBez3.out"
				;
			break;

		  case fk_CurveDrawDeg::D4:
			prog->tessEvalShaderSource +=
				#include "GLSL/Curve/TE_RBez4.out"
				;
			break;

		  default:
			break;
		}
	}
	
	if(prog->validate() == false) {
		fk_PutError("fk_BezCurveDraw", "ShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	} else {
		fk_PutError(prog->vertexShaderSource);
		fk_PutError(prog->fragmentShaderSource);
		fk_PutError(prog->tessEvalShaderSource);
	}

	ParamInit(prog, param);
	return;
}

void fk_BezCurveDraw::ParamInit(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
{
	argParam->reserveAttribute(fk_Curve::ctrlPosName);
	glBindFragDataLocation(argProg->getProgramID(), 0, fragmentName.c_str());
	argProg->link();
}

GLuint fk_BezCurveDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetLineVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

void fk_BezCurveDraw::Draw_Curve(fk_Model *argModel, fk_ShaderParameter *argParam, bool argShadowSwitch)
{
	fk_Curve	*curve = dynamic_cast<fk_Curve *>(argModel->getShape());
	GLuint		vao = curve->GetLineVAO();
	GLfloat		tessOut[4] = {1.0f, float(curve->getDiv()), 1.0f, 1.0f};

	if(vao == 0) {
		vao = VAOSetup(curve);
	}
	glBindVertexArray(vao);
	curve->BindShaderBuffer(argParam->getAttrTable());
	glEnable(GL_LINE_SMOOTH);

	if(!argShadowSwitch) {
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, tessOut);
		glPatchParameteri(GL_PATCH_VERTICES, curve->getCtrlSize());
		glDrawArrays(GL_PATCHES, 0, curve->getCtrlSize());
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
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
