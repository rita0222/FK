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
#ifndef __FK_GRAPHICS_ENGINE_HEADER__
#define __FK_GRAPHICS_ENGINE_HEADER__

// for FK Header.
#include <FK/Base.h>
#include <FK/D3D/D3D.h>
#include <FK/OpenGL.h>
#include <FK/PickData.h>
#include <FK/Matrix.h>
#include <FK/Image.h>

class fk_PointDraw;
class fk_LineDraw;
class fk_FaceDraw;
class fk_TextureDraw;
class fk_DisplayLink;
class fk_ProjectBase;
class fk_Scene;
class fk_Plane;
class fk_Color;

/*
enum fk_SnapProcMode {
	FK_SNAP_D3D_WINDOW,
	FK_SNAP_D3D_FULL,
	FK_SNAP_WIN32_GDI
};
*/

class fk_GraphicsEngine {

 private:

	// ★★★★★ Direct3D オブジェクト
	LPDIRECT3DDEVICE9		ref_lpD3DDEV;

	LPDIRECT3DSWAPCHAIN9	m_lpD3DSC;
	D3DPRESENT_PARAMETERS	m_d3dpp;
	HWND					m_hWnd;

	LPD3DXMATRIXSTACK		modelStack, viewStack, projStack;

	fk_PointDraw		*pointDraw;
	fk_LineDraw			*lineDraw;
	fk_FaceDraw			*faceDraw;
	fk_TextureDraw		*textureDraw;

	unsigned int		winID;
	fk_DisplayLink		*curDLink;
	int					dLinkStatus;
	int					dLinkID;
	int					wSize;
	int					hSize;
	unsigned int		selectBuf[FK_PICKDATAMAX*5];	// GLuint
	bool				arrayState;
	bool				resizeFlag;
	bool				textureMode;

	std::vector<fk_Model *>	modelArray;

	fk_Matrix			viewMat;
	int					viewArray[4];	// GLint


	void				DrawObjs(bool);
	void				DrawModel(fk_Model *, bool, bool);
	void				RecalcModelView(bool = false);						// Pick 時は OpenGL を使用
	void				RecalcInhModelView(const fk_Model *, bool = false);	// Pick 時は OpenGL を使用
	void				CurrentDispLinkDraw(void);
	bool				DefineLight(void);
	void				LoadModelMatrix(fk_Model *, bool = false);			// Pick 時は OpenGL を使用

	void				DrawShapeObj(fk_Model *, bool, bool);

	void				SetViewPort(void);
	void				SetProjection(const fk_ProjectBase *);
	void				SetDefaultProjection(void);

	void				ApplySceneParameter(bool);

	void				InitFogStatus(fk_Scene *);

	bool				IsInsideWindow(void);

	unsigned long		GetNow(void);

	void				ViewMatCalc(fk_Matrix *);

	bool				GetViewLinePos(double, double,
									   fk_Vector *, fk_Vector *);

	void				CheckDepthBufferSize(void);
	bool				InitGL4Pick(void);
	void				SetPickProjection(const fk_ProjectBase *);
	void				SetDefaultPickProjection(void);


  public:
	fk_GraphicsEngine(void);
	~fk_GraphicsEngine();

	HRESULT				InitD3D(HWND, bool = true);

	void				Init(int, int);

	void				SetScene(fk_Scene *);
	void				ResizeWindow(int, int);


	bool				GetProjectPosition(double, double,
										   fk_Plane *, fk_Vector *);
	bool				GetProjectPosition(double, double,
										   double, fk_Vector *);
	bool				GetWindowPosition(fk_Vector, fk_Vector *);
	void				GetPickData(fk_PickData *, int, int, int);

	/*
	void				SetOGLPointerMode(bool);
	bool				GetOGLPointerMode(void);

	void				SetOGLTextureBindMode(bool);
	bool				GetOGLTextureBindMode(void);
	*/

	bool				SnapImage(std::string, fk_ImageType = FK_IMAGE_BMP, fk_SnapProcMode = FK_SNAP_D3D_WINDOW);
	bool				SnapImage(fk_Image *, fk_SnapProcMode = FK_SNAP_D3D_WINDOW);

	void				ClearTextureMemory(void);
	unsigned long		GetUsingTextureMemory(void);
	// void				OpenGLInit(void);
	void				D3DStateInit(void);

	void				SetPickViewPort(int, int, int);
	void				Draw(bool);

	void				Flip(void);
};

LPDIRECT3DDEVICE9 GetD3DDevice(void);

#endif /* !__FK_GRAPHICS_ENGINE_HEADER__ */
