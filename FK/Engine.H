﻿#ifndef __FK_GRAPHICS_ENGINE_HEADER__
#define __FK_GRAPHICS_ENGINE_HEADER__

#include <FK/Base.h>
#include <FK/OpenGL.H>
#include <FK/Matrix.h>
#include <FK/Image.h>
#include <FK/Scene.h>
#include <FK/FrameBuffer.h>
#include <FK/RectTexture.h>

namespace FK {
	class fk_Scene;
	class fk_Plane;
	class fk_DrawBase;
	class fk_PointDraw;
	class fk_LineDraw;
	class fk_FaceDraw;
	class fk_TextureDraw;
	class fk_BezCurveDraw;
	class fk_SurfaceDraw;

	class fk_GraphicsEngine {

#ifndef FK_DOXYGEN_USER_PROCESS
		class Member {
		public:
			// エンジン用基本メンバー
			unsigned int drawCount;
			unsigned int winID;
			fk_Scene *curScene;
			int sceneStatus;
			int sceneID;
			int wSize;
			int hSize;
			bool resizeFlag;
			fk_BlendFactor srcFactor, dstFactor;
			bool depthRead, depthWrite;

			// 投影処理用メンバー
			fk_ProjectBase *curProj;
			GLint viewArray[4];

			// スナップイメージ用メンバー
			std::vector<fk_ImType> snapBuffer;

			// デフォルト投影
			fk_Perspective defProj;

			// 境界ボリューム描画用モデル
			fk_Model boundaryModel;

			// FBO用メンバー
			std::unique_ptr<fk_FrameBuffer> colorBuf;
			std::unique_ptr<fk_FrameBuffer> depthBuf;
			bool FBOMode, FBOWindowMode;
			GLuint rectVAO, fboHandle;
			fk_ShaderBinder *FBOShader;

			// 影用メンバー
			std::unique_ptr<fk_FrameBuffer> shadowBuf;
			GLuint shadowHandle;
			fk_ShadowMode shadowMode;
			bool shadowInitFlag, shadowSwitch;
			int shadowBufferID;
			double shadowSize;
			double shadowDistance;
			int shadowResolution;
			double shadowVisibility;
			double shadowBias;
			fk_Vector shadowVec;

			fk_Ortho shadowProj;
			fk_Model shadowCamera;
			fk_RectTexture shadowTexture;

			// 霧用メンバー
			fk_FogMode	fogMode;
			double fogStart, fogEnd, fogDensity;
			fk_Color fogColor;

			Member(bool);
		};
#endif

	public:
		fk_GraphicsEngine(bool);
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

		//void SetPickViewPort(int, int, int);
		unsigned int Draw(void);

		void BindWindow(fk_ShaderBinder *);

		void InitFrameBufferMode(void);

		fk_FrameBuffer * GetColorBuffer(void);
		fk_FrameBuffer * GetDepthBuffer(void);

		//void StereoDrawPrep(fk_StereoChannel);
		//void StereoDrawMain(fk_StereoChannel);

		fk_RectTexture * GetShadowTexture(void);
		void SetShadowTextureSize(int, int);

		void SetShadowVec(fk_Vector);
		void SetShadowResolution(int);
		void SetShadowAreaSize(double);
		void SetShadowDistance(double);
		void SetShadowVisibility(double);
		void SetShadowBias(double);

		bool AllTest(void);

	private:

		// DrawEngine static インスタンス群
		static std::unique_ptr<fk_PointDraw> pointDraw;
		static std::unique_ptr<fk_LineDraw> lineDraw;
		static std::unique_ptr<fk_FaceDraw> faceDraw;
		static std::unique_ptr<fk_TextureDraw> textureDraw;
		static std::unique_ptr<fk_BezCurveDraw> bezCurveLineDraw;
		static std::unique_ptr<fk_BezCurveDraw> bezCurvePointDraw;
		static std::unique_ptr<fk_SurfaceDraw> surfaceDraw;
		static std::unique_ptr<fk_SurfaceDraw> surfacePointDraw;
		static std::unique_ptr<fk_SurfaceDraw> surfaceLineDraw;

		static unsigned int generalID;
		static unsigned int engineNum;

		std::unique_ptr<Member> _m;

		void DrawShadow(void);
		void DrawWorld(void);
		
		void DrawObjs(void);
		void DrawModel(fk_Model *);
		void DrawShapeObj(fk_Model *);
		void DrawBoundaryLine(fk_Model *);

		void SetViewPort(void);
		void SetProjection(fk_ProjectBase *);

		void ApplySceneParameter(void);
		void InitFogStatus(fk_Scene *);

		std::tuple<fk_Vector, fk_Vector> GetViewLinePos(double, double);

		//void SetStereoViewPort(fk_StereoChannel);
		//void RecalcStereoModelView(fk_StereoChannel);
		//void DrawStereoObjs(bool);

		void SetBlendMode(fk_Model *model);
		void SetDepthMode(fk_DepthMode mode);

		void SetupFBO(void);
		void PreFBODraw(void);
		void PostFBODraw(void);
		void FBOWindowDraw(void);

		void ShadowInit(void);
		void AttachShadowBuffer(int);
		void PreShadowDraw(void);
		void PostShadowDraw(void);
		void CopyShadowStatus(void);

		int ShadowFixVal(int);
	};
}

#endif /* !__FK_GRAPHICS_ENGINE_HEADER__ */

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
