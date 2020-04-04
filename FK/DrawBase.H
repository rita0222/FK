#ifndef __FK_DRAW_BASE_HEADER__
#define __FK_DRAW_BASE_HEADER__

#include <FK/OpenGL.H>
#include <FK/Matrix.h>
#include <FK/Material.h>
#include <FK/Light.h>
#include <FK/Texture.h>
#include <FK/Scene.h>
#include <list>

namespace FK {

	enum class fk_DrawVS {
		MODEL = 0,
		ELEM,
		IFS,
		NUM
	};

	enum class fk_DrawFS {
		ORG = 0,
		IFS,
		SHADOW,
		NUM
	};
	
	class fk_Model;
	class fk_Shape;
	class fk_ShaderBinder;
	class fk_ShaderProgram;
	class fk_ShaderParameter;

	class fk_DrawBase {
	public:
		fk_DrawBase(void);
		virtual ~fk_DrawBase();

		static void SetProjectionMatrix(fk_Matrix *);
		static void SetCamera(fk_Model *);
		static void SetModel(fk_Model *);
		static void SetLight(std::list<fk_Model *> *, fk_LightType);
		virtual GLuint VAOSetup(fk_Shape *) = 0;
		static void SetShadowProjMatrix(fk_Matrix *);
		static void SetShadowCamera(fk_Model *);
		static void SetShadowParam(double, double);
		static void SetShadowMode(fk_ShadowMode);

		static const std::string projectionMatrixName;
		static const std::string viewMatrixName;
		static const std::string modelMatrixName;
		static const std::string modelViewMatrixName;
		static const std::string modelViewProjectionMatrixName;
		static const std::string normalModelMatrixName;
		static const std::string normalModelViewMatrixName;
		static const std::string cameraPositionName;

		static const std::string shadowMatrixName;
		static const std::string shadowBiasName;
		static const std::string shadowVisibilityName;

		static const std::string modelMaterialName;
		static const std::string diffuseName;
		static const std::string ambientName;
		static const std::string specularName;
		static const std::string shininessName;

		static const std::string parallelLightName;
 		static const std::string pointLightName;
 		static const std::string spotLightName;

		static const std::string parallelLightNumName;
		static const std::string pointLightNumName;
		static const std::string spotLightNumName;

		static const std::string lightPositionName;
		static const std::string lightVecName;
		static const std::string lightDiffuseName;
		static const std::string lightSpecularName;
		static const std::string lightSpotCutOffName;
		static const std::string lightSpotExponentName;
		static const std::string lightAttenuationName;
		
		static const std::string fragmentName;

		static const int MAXLIGHTNUM;

		void AttachShadowTexture(int, const std::string &, fk_Texture *);

	protected:
		static fk_Matrix	*projectionMatrix;
		static fk_Matrix	viewMatrix;
		static fk_Matrix	modelMatrix;
		static fk_Matrix	modelViewMatrix;
		static fk_Matrix	modelViewProjectionMatrix;
		static fk_Matrix	normalModelMatrix;
		static fk_Matrix	normalModelViewMatrix;
		static fk_Material	*modelMaterial;
		static fk_Vector	cameraPosition;

		static fk_ShadowMode shadowMode;
		static fk_Matrix	*shadowProjMatrix;
		static fk_Matrix	shadowViewMatrix;
		static fk_Matrix	shadowMatrix;
		static fk_Matrix	shadowBiasMatrix;
		static float		shadowBias;
		static float		shadowVisibility;

		static std::list<fk_Model *> *parallelLightList;
		static std::list<fk_Model *> *pointLightList;
		static std::list<fk_Model *> *spotLightList;

		fk_ShaderBinder	*drawShader, *shadowShader;
		fk_Texture *shadowTexture;
		bool defaultShaderFlag;
		std::vector<fk_ShaderBinder *> aliveShader;

		void SetParameter(fk_ShaderParameter *);

	private:

		void SetMatrixParam(fk_ShaderParameter *);
		void SetValueParam(fk_ShaderParameter *);
		void SetMaterialParam(fk_ShaderParameter *);
		void SetLightParam(fk_ShaderParameter *, fk_LightType);

		void InitBiasMatrix(void);
	};
}

#endif /* !__FK_DRAW_BASE_HEADER__ */

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
