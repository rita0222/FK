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



#ifndef __FK_GRAPHICS_ENGINE_HEADER__
#define __FK_GRAPHICS_ENGINE_HEADER__

#include <FK/Base.h>
#include <FK/OpenGL.H>
#include <FK/Matrix.h>
#include <FK/Image.h>
#include <FK/DList.h>
#include <FK/FrameTexture.h>

namespace FK {
	class fk_Scene;
	class fk_Plane;
	class fk_PointDraw;
	class fk_LineDraw;
	class fk_FaceDraw;
	class fk_TextureDraw;
	class fk_BezCurveDraw;
	class fk_SurfaceDraw;

	class fk_GraphicsEngine {

	public:
		fk_GraphicsEngine(void);
		virtual ~fk_GraphicsEngine();

		void Init(int, int);

		void SetScene(fk_Scene *);
		void ResizeWindow(int, int);

		std::tuple<bool, fk_Vector> GetProjectPosition(double, double, fk_Plane &);
		std::tuple<bool, fk_Vector> GetProjectPosition(double, double, double);
		std::tuple<bool, fk_Vector> GetWindowPosition(fk_Vector &);
		//void GetPickData(fk_PickData *, int, int, int);

		bool SnapImage(fk_Image *, fk_SnapProcMode = fk_SnapProcMode::FRONT);

		void OpenGLInit(void);

		void SetPickViewPort(int, int, int);
		void Draw(void);

		void BindWindow(fk_ShaderBinder *);
u		//void StereoDrawPrep(fk_StereoChannel);
		//void StereoDrawMain(fk_StereoChannel);

	private:

		static fk_PointDraw *pointDraw;
		static fk_LineDraw *lineDraw;
		static fk_FaceDraw *faceDraw;
		static fk_TextureDraw *textureDraw;
		static fk_BezCurveDraw *bezCurveLineDraw;
		static fk_BezCurveDraw *bezCurvePointDraw;
		static fk_SurfaceDraw *surfaceDraw;
		static fk_SurfaceDraw *surfacePointDraw;
		static fk_SurfaceDraw *surfaceLineDraw;

		unsigned int winID;
		fk_DisplayLink *curDLink;
		int dLinkStatus;
		int dLinkID;
		int wSize;
		int hSize;
		bool resizeFlag;
		fk_BlendFactor srcFactor, dstFactor;
		bool depthRead, depthWrite;

		std::vector<fk_Model *> modelArray;

		fk_ProjectBase *curProj;
		GLint viewArray[4];

		std::vector<fk_ImType> snapBuffer;

		fk_Perspective defProj;

		fk_Model boundaryModel;

		bool FBOMode;
		fk_FrameTexture *colorTex;
		fk_FrameTexture *depthTex;
		GLuint rectVAO, fboHandle;
		fk_ShaderBinder *FBOShader;
		
		void DrawObjs(void);
		void DrawModel(fk_Model *);
		void CurrentDispLinkDraw(void);

		void DrawShapeObj(fk_Model *);
		void DrawBoundaryLine(fk_Model *);

		void SetViewPort(void);
		void SetProjection(fk_ProjectBase *);
		//void SetDefaultProjection(void);

		void ApplySceneParameter(bool);

		void InitFogStatus(fk_Scene *);

		bool IsInsideWindow(void);

		unsigned long GetNow(void);

		//void ViewMatCalc(fk_Matrix *);

		std::tuple<fk_Vector, fk_Vector> GetViewLinePos(double, double);

		//void SetStereoViewPort(fk_StereoChannel);
		//void RecalcStereoModelView(fk_StereoChannel);
		//void DrawStereoObjs(bool);

		void SetBlendMode(fk_Model *model);
		void SetDepthMode(fk_DepthMode mode);

		void SetupFBO(void);
		void PreFBODraw(void);
		void PostFBODraw(void);
	};
}

#endif /* !__FK_GRAPHICS_ENGINE_HEADER__ */
