#ifndef __FK_PROJECTION_HEADER__
#define __FK_PROJECTION_HEADER__

#include <FK/Base.h>

namespace FK {
	//! 投影法を表す列挙型
	enum fk_ProjectMode {
		FK_NONE_PROJ_MODE,		//!< 指定なし
		FK_PERSPECTIVE_MODE,	//!< 対称透視投影法
		FK_FRUSTUM_MODE,		//!< 一般透視投影法
		FK_ORTHO_MODE			//!< 平行投影法
	};


	//! 投影法の基底クラス
	/*!
	 *	このクラスは、各種投影法の基底クラスです。
	 *	クラス自体の実質的な機能はありません。
	 *
	 *	\sa fk_Perspective, fk_Frustum, fk_Ortho, fk_DisplayLink
	 */

	class fk_ProjectBase : public fk_BaseObject {
	public:

		//! コンストラクタ
		fk_ProjectBase(fk_ProjectMode = FK_NONE_PROJ_MODE);

		//! デストラクタ
		virtual ~fk_ProjectBase();

		//! 投影法参照関数
		/*!
		 *	インスタンスがどの投影法かを参照します。
		 *
		 *	\return		投影法に対応する列挙型の値を返します。
		 */
		fk_ProjectMode	getMode(void) const;

	private:
		fk_ProjectMode	Mode;

	protected:

#ifndef FK_DOXYGEN_USER_PROCESS

		void			SetMode(fk_ProjectMode);

#endif

	};

	//! 対称透視投影法を制御するクラス
	/*!
	 *	このクラスは、対称透視投影法の設定を制御する機能を提供します。
	 *	本クラスで対称透視投影に対する様々な値を設定し、
	 *	fk_DisplayLink::setProjection() 関数を用いてシーンに設定することで、
	 *	シーン内の投影設定を行うことができます。
	 *
	 *	透視投影の特徴は、近くの物体は大きく、遠くの物体は小さく表示するという、
	 *	いわゆる遠近感を持つことです。
	 *	この投影法は、人間の目やカメラの持つ感覚と類似しているため、
	 *	アニメーションやビジュアルシミュレーションなどのような
	 *	リアルさが必要な場面でよく利用されています。
	 *	しかし、透視投影においては 3 次元空間中において平行な面や線が、
	 *	表示された場合に平行にはならないという現象がおきるため、
	 *	設計などには向いていません。
	 *	そのような場合は、 fk_Ortho による平行投影を用いた方がよいでしょう。
	 *
	 *	透視投影を用いる場合、本クラスによる「対称透視投影」と、
	 *	fk_Frustum クラスによる「一般透視投影」の2種類の投影法が存在します。
	 *	対称透視投影は、カメラ目線の先が描画画面の中心となることを前提とした投影であり、
	 *	通常はこちらを用いた方が簡便です。
	 *	カメラ目線が画面の中心にないような投影を作成する場合は、
	 *	fk_Frustum による一般透視投影を用いる必要があります。
	 *
	 *	設定は、3種類の値によって行います。
	 *	1つは「視野角」で、
	 *	これは画面最上部に向いたベクトルと最下部に向いたベクトルの角度です。
	 *	あとの2つは「クリップ距離」であり、この2つの距離の間にある物体が表示されます。
	 *	通常は、近い方を十分小さな値、遠い方を大きな値とすることで、
	 *	本来見えるはずの物体が全て見えるようにしておきます。
	 *	以下がその概念図です。
	 *	\image html Perspective.png "透視投影法"
	 *	\image latex Perspective.eps "透視投影法" width=10cm
	 *
	 *	\sa fk_Frustum, fk_Ortho, fk_DisplayLink
	 */

	class fk_Perspective : public fk_ProjectBase {
	public:

		//! コンストラクタ
		/*!
		 *	コンストラクタで、初期値を設定することが可能です。
		 *
		 *	\param[in]	fovy	視野角を設定します。単位は弧度法(ラジアン)です。
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		fk_Perspective(double fovy = 2.0*FK_PI/9.0,
					   double near = 1.0,
					   double far = 6000.0);

		//! デストラクタ
		virtual ~fk_Perspective();

		//! コピーコンストラクタ
		fk_Perspective(const fk_Perspective &);

		//! 単純代入演算子
		fk_Perspective & operator =(const fk_Perspective &);

		//! 視野角設定関数
		/*!
		 *	視野角を設定します。
		 *
		 *	\param[in]	fovy	視野角。単位は弧度法(ラジアン)です。
		 */
		void			setFovy(double fovy);

		//! クリッピング近距離面距離設定関数
		/*!
		 *	クリッピング近距離面への距離を設定します。
		 *
		 *	\param[in]	near	面への距離
		 */
		void			setNear(double near);

		//! クリッピング遠距離面距離設定関数
		/*!
		 *	クリッピング遠距離面への距離を設定します。
		 *
		 *	\param[in]	far		面への距離
		 */
		void			setFar(double far);

		//! 一括設定関数
		/*!
		 *	視野角、クリッピング面距離を一括して設定します。
		 *
		 *	\param[in]	fovy	視野角。単位は弧度法(ラジアン)です。
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		void			setAll(double fovy, double near, double far);

		//! 視野角参照関数
		/*!
		 *	視野角を参照します。
		 *
		 *	\return		視野角。単位は弧度法(ラジアン)です。
		 */
		double			getFovy(void) const;


		//! クリッピング近距離面距離参照関数
		/*!
		 *	クリッピング近距離面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getNear(void) const;

		//! クリッピング遠距離面距離参照関数
		/*!
		 *	クリッピング遠距離面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getFar(void) const;

	private:
		double			Fovy;
		double			Near, Far;
	};

	//! 一般透視投影を制御するクラス
	/*!
	 *	このクラスは、一般透視投影法の設定を制御する機能を提供します。
	 *	本クラスで一般透視投影に対する様々な値を設定し、
	 *	fk_DisplayLink::setProjection() 関数を用いてシーンに設定することで、
	 *	シーン内の投影設定を行うことができます。
	 *
	 *	透視投影の特徴は、近くの物体は大きく、遠くの物体は小さく表示するという、
	 *	いわゆる遠近感を持つことです。
	 *	この投影法は、人間の目やカメラの持つ感覚と類似しているため、
	 *	アニメーションやビジュアルシミュレーションなどのような
	 *	リアルさが必要な場面でよく利用されています。
	 *	しかし、透視投影においては 3 次元空間中において平行な面や線が、
	 *	表示された場合に平行にはならないという現象がおきるため、
	 *	設計などには向いていません。
	 *	そのような場合は、 fk_Ortho による平行投影を用いた方がよいでしょう。
	 *
	 *	透視投影を用いる場合、本クラスによる「一般透視投影」と、
	 *	fk_Perspective クラスによる「対称透視投影」の2種類の投影法が存在します。
	 *	対称透視投影は、カメラ目線の先が描画画面の中心となることを前提とした投影であり、
	 *	通常はこちらを用いた方が簡便です。
	 *	カメラ目線が画面の中心にないような投影を作成する場合は、
	 *	本クラスによる一般透視投影を用いる必要があります。
	 *
	 *	設定は、6種類の値によって行います。
	 *	最初の4つは、「視錐台」と呼ばれる描画対称領域の近接面における、
	 *	面とカメラベクトルの交点と各辺との距離となります。
	 *	あとの2つは「クリップ距離」であり、この2つの距離の間にある物体が表示されます。
	 *	通常は、近い方を十分小さな値、遠い方を大きな値とすることで、
	 *	本来見えるはずの物体が全て見えるようにしておきます。
	 *
	 *	\sa fk_Perspective, fk_Ortho, fk_DisplayLink
	 */

	class fk_Frustum : public fk_ProjectBase {
	public:
		//! コンストラクタ
		/*!
		 *	コンストラクタで、初期値を設定することが可能です。
		 *
		 *	\param[in]	left	視錐台の左側符号付き距離
		 *	\param[in]	right	視錐台の右側符号付き距離
		 *	\param[in]	bottom	視錐台の下側符号付き距離
		 *	\param[in]	top		視錐台の上側符号付き距離
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		fk_Frustum(double left = -10.0,
				   double right = 10.0,
				   double bottom = -10.0,
				   double top = 10.0,
				   double near = 1.0,
				   double far = 6000.0);

		//! デストラクタ
		virtual ~fk_Frustum();

		//! コピーコンストラクタ
		fk_Frustum(const fk_Frustum &);

		//! 単純代入演算子
		fk_Frustum & operator =(const fk_Frustum &);

		//! 視錐台左側符号付き距離設定関数
		/*!
		 *	視錐台近接面への左側符号付き距離を設定します。
		 *
		 *	\param[in]	left	符号付き距離
		 */
		void		setLeft(double left);

		//! 視錐台右側符号付き距離設定関数
		/*!
		 *	視錐台近接面への右側符号付き距離を設定します。
		 *
		 *	\param[in]	right	符号付き距離
		 */
		void		setRight(double right);

		//! 視錐台下側符号付き距離設定関数
		/*!
		 *	視錐台近接面への下側符号付き距離を設定します。
		 *
		 *	\param[in]	bottom	符号付き距離
		 */
		void		setBottom(double bottom);

		//! 視錐台上側符号付き距離設定関数
		/*!
		 *	視錐台近接面への上側符号付き距離を設定します。
		 *
		 *	\param[in]	top		符号付き距離
		 */
		void		setTop(double top);

		//! クリッピング近距離面距離設定関数
		/*!
		 *	クリッピング近距離面への距離を設定します。
		 *
		 *	\param[in]	near	面への距離
		 */
		void			setNear(double near);

		//! クリッピング遠距離面距離設定関数
		/*!
		 *	クリッピング遠距離面への距離を設定します。
		 *
		 *	\param[in]	far		面への距離
		 */
		void			setFar(double far);

		//! 一括設定関数
		/*!
		 *	視錐台の全ての値を一括して設定します。
		 *
		 *	\param[in]	left	視錐台の左側符号付き距離
		 *	\param[in]	right	視錐台の右側符号付き距離
		 *	\param[in]	bottom	視錐台の下側符号付き距離
		 *	\param[in]	top		視錐台の上側符号付き距離
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		void			setAll(double left,
							   double right,
							   double bottom,
							   double top,
							   double near,
							   double far);

		//! 視錐台左側符号付き距離取得関数
		/*!
		 *	視錐台近接面への左側符号付き距離を取得します。
		 *
		 *	\return		符号付き距離
		 */
		double			getLeft(void) const;

		//! 視錐台右側符号付き距離取得関数
		/*!
		 *	視錐台近接面への右側符号付き距離を取得します。
		 *
		 *	\return		符号付き距離
		 */
		double			getRight(void) const;

		//! 視錐台下側符号付き距離取得関数
		/*!
		 *	視錐台近接面への下側符号付き距離を取得します。
		 *
		 *	\return		符号付き距離
		 */
		double			getBottom(void) const;

		//! 視錐台上側符号付き距離取得関数
		/*!
		 *	視錐台近接面への上側符号付き距離を取得します。
		 *
		 *	\return		符号付き距離
		 */
		double			getTop(void) const;

		//! クリッピング近距離面距離取得関数
		/*!
		 *	クリッピング近距離面への距離を取得します。
		 *
		 *	\return		面への距離
		 */
		double			getNear(void) const;

		//! クリッピング遠距離面距離取得関数
		/*!
		 *	クリッピング遠距離面への距離を取得します。
		 *
		 *	\return		面への距離
		 */
		double			getFar(void) const;

	private:
		double		Left, Right, Bottom, Top, Near, Far;
	};

	//! 平行投影法を制御するクラス
	/*!
	 *	このクラスは、平行投影法(正投影法とも呼ばれます)の設定を制御する機能を提供します。
	 *	本クラスで平行投影に対する様々な値を設定し、
	 *	fk_DisplayLink::setProjection() 関数を用いてシーンに設定することで、
	 *	シーン内の投影設定を行うことができます。
	 *
	 *	平行投影の特徴は、カメラからの距離に関係なく常に同じ大きさで表示することです。
	 *	現象として、3次元空間中で平行な線や面は、表示画像においても平行となります。
	 *	そのため、設計などの用途には適しています。以下がその概念図です。
	 *	\image html Ortho.png "平行投影法"
	 *	\image latex Ortho.eps "平行投影法" width=10cm
	 *	しかし、人間の目やカメラなどによる感覚とは異なるため、
	 *	広い領域の表示の際には遠近感が損なわれ違和感を感じるものとなります。
	 *	そのような場合は、 fk_Perspective による透視投影を用いた方がよいでしょう。
	 *	
	 *	設定は、左右、上下、遠近の各面を表す距離を設定します。
	 *
	 *	\sa fk_Perspective, fk_DisplayLink
	 */

	class fk_Ortho : public fk_ProjectBase {
	public:

		//! コンストラクタ
		/*!
		 *	コンストラクタで、初期値を設定することが可能です。
		 *	下記の「面」は、全てクリッピング面を表します。
		 *
		 *	\param[in]	left	視線ベクトルから左側面への距離
		 *	\param[in]	right	視線ベクトルから右側面への距離
		 *	\param[in]	bottom	視線ベクトルから下側面への距離
		 *	\param[in]	top		視線ベクトルから上側面への距離
		 *	\param[in]	near	カメラから近距離面への距離
		 *	\param[in]	far		カメラから遠距離面への距離
		 */
		fk_Ortho(double left = -500.0, double right = 500.0,
				 double bottom = -500.0, double top = 500.0,
				 double near = 0.0, double far = 10000.0);

		//! デストラクタ
		virtual ~fk_Ortho();

		//! コピーコンストラクタ
		fk_Ortho(const fk_Ortho &);

		//! 単純代入演算子
		fk_Ortho & operator =(const fk_Ortho &);

		//! クリッピング左側面距離設定関数
		/*!
		 *	視線ベクトルからクリッピング左側面への距離を設定します。
		 *
		 *	\param[in]	left	距離
		 */
		void			setLeft(double left);

		//! クリッピング左側面距離設定関数
		/*!
		 *	視線ベクトルからクリッピング右側面への距離を設定します。
		 *
		 *	\param[in]	right	距離
		 */
		void			setRight(double right);

		//! クリッピング左側面距離設定関数
		/*!
		 *	視線ベクトルからクリッピング下側面への距離を設定します。
		 *
		 *	\param[in]	bottom	距離
		 */
		void			setBottom(double bottom);

		//! クリッピング左側面距離設定関数
		/*!
		 *	視線ベクトルからクリッピング上側面への距離を設定します。
		 *
		 *	\param[in]	top		距離
		 */
		void			setTop(double top);

		//! クリッピング近距離距離設定関数
		/*!
		 *	カメラからクリッピング近距離面への距離を設定します。
		 *
		 *	\param[in]	near	距離
		 */
		void			setNear(double near);

		//! クリッピング遠距離距離設定関数
		/*!
		 *	カメラからクリッピング遠距離面への距離を設定します。
		 *
		 *	\param[in]	far	距離
		 */
		void			setFar(double far);

		//! 一括設定関数
		/*!
		 *	各クリッピング面の距離を一括して設定します。
		 *	下記の「面」は、全てクリッピング面を表します。
		 *
		 *	\param[in]	left	視線ベクトルから左側面への距離
		 *	\param[in]	right	視線ベクトルから右側面への距離
		 *	\param[in]	bottom	視線ベクトルから下側面への距離
		 *	\param[in]	top		視線ベクトルから上側面への距離
		 *	\param[in]	near	カメラから近距離面への距離
		 *	\param[in]	far		カメラから遠距離面への距離
		 */
		void			setAll(double left, double right,
							   double bottom, double top,
							   double near, double far);

		//! クリッピング左側面距離参照関数
		/*!
		 *	視線ベクトルからクリッピング左側面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getLeft(void) const;

		//! クリッピング右側面距離参照関数
		/*!
		 *	視線ベクトルからクリッピング右側面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getRight(void) const;

		//! クリッピング下側面距離参照関数
		/*!
		 *	視線ベクトルからクリッピング下側面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getBottom(void) const;

		//! クリッピング上側面距離参照関数
		/*!
		 *	視線ベクトルからクリッピング上側面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getTop(void) const;

		//! クリッピング近距離距離参照関数
		/*!
		 *	カメラからクリッピング近距離面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getNear(void) const;

		//! クリッピング遠距離距離参照関数
		/*!
		 *	カメラからクリッピング遠距離面への距離を参照します。
		 *
		 *	\return		距離
		 */
		double			getFar(void) const;

	private:
		double			Left, Right;
		double			Bottom, Top;
		double			Near, Far;
	};
}
#endif // !__FK_PROJECTION_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
