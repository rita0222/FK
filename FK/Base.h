#ifndef __FK_BASE_HEADER__
#define __FK_BASE_HEADER__

#if defined(_MINGW_)
#ifdef hypot
#undef hypot
#endif
#endif

#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>

#if defined(WIN32)

#pragma warning(disable : 4786)
//#define snprintf _snprintf
//#define vsnprintf _vsnprintf

#endif	// !WIN32 || _CYGWIN_GCC_

#define FK_UNUSED(x)	(void)(x)

//! Fine Kernel Toolkit 名前空間
namespace FK {

	const int FK_MAJOR_VERSION = 4;
	const int FK_MINOR_VERSION = 1;
	const int FK_SUBMINOR_VERSION = 6;

#define _FK_UNDEFINED_DEFINE_ -1

	const int FK_UNDEFINED = _FK_UNDEFINED_DEFINE_;

	//! オブジェクトインスタンスのタイプを表す列挙型
	enum class fk_Type {
		BASEOBJECT,		//!<	fk_BaseObject 型
		MATRIXADMIN,	//!<	fk_MatrixAdmin 型
		MODEL,			//!<	fk_Model 型
		DISPLAYLINK,	//!<	fk_DisplayLink 型
		SCENE,			//!<	fk_Scene 型
		SHAPE,			//!<	fk_Shape 型
		POLYGON,		//!<	fk_Polygon 型
		LINE,			//!<	fk_Line 型
		POLYLINE,		//!<	fk_Polyline 型
		POINT,			//!<	fk_Point 型
		CIRCLE,			//!<	fk_Circle 型
		SPHERE,			//!<	fk_Sphere 型
		BLOCK,			//!<	fk_Block 型
		CLOSEDLINE,		//!<	fk_Closedline 型
		PRISM,			//!<	fk_Prism 型
		CAPSULE,		//!<	fk_Capsule 型
		CONE,			//!<	fk_Cone 型
		INDEXFACESET,	//!<	fk_IndexFaceSet 型
		LIGHT,			//!<	fk_Light 型
		CURVE,			//!<	fk_Curve 型
		BEZCURVE,		//!<	fk_BezCurve 型
		RBEZCURVE,		//!<	fk_RBezCurve 型
		BSPLCURVE,		//!<	fk_BSplCurve 型
		SURFACE,		//!<	fk_Surface 型
		BEZSURFACE,		//!<	fk_BezSurface 型
		GREGORY,		//!<	fk_Gregory 型
		IMAGE,			//!<	fk_Image 型
		FRAMEBUFFER,	//!<	fk_FrameBuffer 型
		TEXCOORD,		//!<	fk_TexCoord 型
		TEXTURE,		//!<	fk_Texture 型
		RECTTEXTURE,	//!<	fk_RectTexture 型
		TRITEXTURE,		//!<	fk_TriTexture 型
		MESHTEXTURE,	//!<	fk_MeshTexture 型
		IFSTEXTURE,		//!<	fk_IFSTexture 型
		ARTEXTURE,		//!<	fk_ARTexture 型
		UNICHAR,		//!<	fk_UniChar 型
		UNISTR,			//!<	fk_UniStr 型
		TEXTIMAGE,		//!<	fk_TextImage 型
		COLOR,			//!<	fk_Color 型
		MATERIAL,		//!<	fk_Material 型
		PALETTE,		//!<	fk_Palette 型
		PLANE,			//!<	fk_Plane 型
		WINDOW,			//!<	fk_Window 型
		PICKDATA,		//!<	fk_PickData 型
		PROJECTBASE,	//!<	fk_ProjectBase 型
		PERSPECTIVE,	//!<	fk_Perspective 型
		FRUSTUM,		//!<	fk_Frustum 型
		ORTHO,			//!<	fk_Ortho 型
		VERTEX,			//!<	fk_Vertex 型
		HALF,			//!<	fk_Half 型
		EDGE,			//!<	fk_Edge 型
		LOOP,			//!<	fk_Loop 型
		SOLID,			//!<	fk_Solid 型
		SHAPEVIEWER,	//!<	fk_ShapeViewer 型
		PARTICLE,		//!<	fk_Particle 型
		PARTICLESET,	//!<	fk_ParticleSet 型
		GRAPH,			//!<	fk_Graph 型
		GRAPHNODE,		//!<	fk_GraphNode 型
		GRAPHEDGE,		//!<	fk_GraphEdge 型
	};

	//! FK の各クラスの基盤となる基本クラス
	/*!
	 *	このクラスは、FKのユーザが利用する大半のクラスの基底クラスとなっています。
	 *	主に、インスタンスの型を管理するための機能を提供します。
	 *	\sa fk_Type
	 */
	class fk_BaseObject {

	public:
		//! コンストラクタ
		/*!
		 *	\param[in] type インスタンスのタイプ
		 */
		fk_BaseObject(fk_Type type = fk_Type::BASEOBJECT);

		//! タイプ取得関数
		/*!
		 *	インスタンスのタイプを取得します。
		 *	\return インスタンスのタイプ
		 */
		fk_Type	getObjectType(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS
		void			SetObjectType(const fk_Type type);
#endif

	private:
		fk_Type			ObjectType;

	};

#ifdef FK_DEF_STD_NAMESPACE
	using namespace std;
#endif

#ifdef FK_DEF_SIZETYPE
	using _st = std::vector<int>::size_type;
#endif

#ifndef FK_DOXYGEN_USER_PROCESS
	class fk_Noncopyable {
	private:
		void operator =(const fk_Noncopyable&) {};
		fk_Noncopyable(const fk_Noncopyable&) {};

	public:
		fk_Noncopyable(void) {};
	};
#endif

}

#endif /* !__FK_BASE_HEADER__ */

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
