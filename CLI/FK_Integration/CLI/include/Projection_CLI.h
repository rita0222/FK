/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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

﻿// Shape_CLI.h

#pragma once

#include <FK/Projection.h>

namespace FK_CLI
{
	using namespace System;

	//! 投影法を表す列挙型
	public enum class fk_ProjectMode {
		NONE_PROJ_MODE,		//!< 指定なし
		PERSPECTIVE_MODE,	//!< 対称透視投影法
		FRUSTUM_MODE,		//!< 一般透視投影法
		ORTHO_MODE			//!< 平行投影法
	};

	//! 投影法の基底クラス
	/*!
	 *	このクラスは、各種投影法の基底クラスです。
	 *	クラス自体の実質的な機能はありません。
	 *
	 *	\sa fk_Perspective, fk_Frustum, fk_Ortho, fk_DisplayLink
	 */
	public ref class fk_ProjectBase {
	internal:
		bool dFlg;
		::fk_ProjectBase *pProj;

		::fk_ProjectBase * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_ProjectBase(bool argNewFlg);
		fk_ProjectBase();
		~fk_ProjectBase();
		!fk_ProjectBase();
#endif
		
		//! 投影法参照プロパティ
		/*!
		 *	インスタンスがどの投影法かを参照します。
		 */
		property fk_ProjectMode Mode {
			fk_ProjectMode get();
		}
	};

	//! 対称透視投影法を制御するクラス
	/*!
	 *	このクラスは、対称透視投影法の設定を制御する機能を提供します。
	 *	本クラスで対称透視投影に対する様々な値を設定し、
	 *	fk_DisplayLink::Projection プロパティを用いてシーンに設定することで、
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
	public ref class fk_Perspective : fk_ProjectBase {
	internal:
		::fk_Perspective * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Perspective(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	初期値として、視野角を \f$ \frac{2}{9}\pi \f$,
		 *	クリッピングの近距離面距離を 1, 遠距離面距離を 6000 とする
		 *	投影を設定します。
		 */
		fk_Perspective();

		//! コンストラクタ2
		/*!
		 *	コンストラクタで、初期値を設定することが可能です。
		 *
		 *	\param[in]	fovy	視野角を設定します。単位は弧度法(ラジアン)です。
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		fk_Perspective(double fovy, double near, double far);

		//! デストラクタ
		~fk_Perspective();

		//! ファイナライザ
		!fk_Perspective();

		//! 視野角プロパティ
		/*!
		 *	視野角の設定や参照を行います。単位は弧度法(ラジアン)です。
		 */
		property double Fovy {
			void set(double);
			double get();
		}
		
		//! クリッピング近距離面距離プロパティ
		/*!
		 *	クリッピング近距離面への距離の設定や参照を行います。
		 */
		property double Near {
			void set(double);
			double get();
		}

		//! クリッピング遠距離面距離プロパティ
		/*!
		 *	クリッピング遠距離面への距離の設定や参照を行います。
		 */
		property double Far {
			void set(double);
			double get();
		}

		//! 一括設定関数
		/*!
		 *	視野角、クリッピング面距離を一括して設定します。
		 *
		 *	\param[in]	fovy	視野角。単位は弧度法(ラジアン)です。
		 *	\param[in]	near	クリッピング近距離面への距離
		 *	\param[in]	far		クリッピング遠距離面への距離
		 */
		void SetAll(double fovy, double near, double far);
	};

	//! 一般透視投影を制御するクラス
	/*!
	 *	このクラスは、一般透視投影法の設定を制御する機能を提供します。
	 *	本クラスで一般透視投影に対する様々な値を設定し、
	 *	fk_DisplayLink::Projection プロパティを用いてシーンに設定することで、
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
	public ref class fk_Frustum : fk_ProjectBase {
	internal:
		::fk_Frustum * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Frustum(bool argNewFlg);
#endif
		//! コンストラクタ1
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
		fk_Frustum(double left, double right,
				   double bottom, double top,
				   double near, double far);

		//! コンストラクタ2
		/*!
		 *	fk_Frustum::fk_Frustum(double, double, double, double, double, double) にて
		 *	(-10, 10, -10, 10, 1, 6000) と設定した場合の初期値が生成されます。
		 */
		fk_Frustum();

		//! デストラクタ
		~fk_Frustum();

		//! ファイナライザ
		!fk_Frustum();

		//! 視錐台左側符号付き距離プロパティ
		/*!
		 *	視錐台近接面への左側符号付き距離の設定や参照を行います。
		 */
		property double Left {
			void set(double);
			double get();
		}

		//! 視錐台右側符号付き距離プロパティ
		/*!
		 *	視錐台近接面への右側符号付き距離の設定や参照を行います。
		 */
		property double Right {
			void set(double);
			double get();
		}

		//! 視錐台下側符号付き距離プロパティ
		/*!
		 *	視錐台近接面への下側符号付き距離の設定や参照を行います。
		 */
		property double Bottom {
			void set(double);
			double get();
		}

		//! 視錐台上側符号付き距離プロパティ
		/*!
		 *	視錐台近接面への上側符号付き距離の設定や参照を行います。
		 */
		property double Top {
			void set(double);
			double get();
		}

		//! クリッピング近距離面距離プロパティ
		/*!
		 *	クリッピング近距離面への距離の設定や参照を行います。
		 */
		property double Near {
			void set(double);
			double get();
		}

		//! クリッピング遠距離面距離プロパティ
		/*!
		 *	クリッピング遠距離面への距離の設定や参照を行います。
		 */
		property double Far {
			void set(double);
			double get();
		}

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
		void SetAll(double left, double right, double bottom,
					double top, double near, double far);
	};

	//! 平行投影法を制御するクラス
	/*!
	 *	このクラスは、平行投影法(正投影法とも呼ばれます)の設定を制御する機能を提供します。
	 *	本クラスで平行投影に対する様々な値を設定し、
	 *	fk_DisplayLink::Projection プロパティを用いてシーンに設定することで、
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
	public ref class fk_Ortho : fk_ProjectBase {
	internal:
		::fk_Ortho * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Ortho(bool argNewFlg);
#endif

		//! コンストラクタ1
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
		fk_Ortho(double left, double right,
				 double bottom, double top,
				 double near, double far);

		//! コンストラクタ2
		/*!
		 *	fk_Ortho::fk_Ortho(double, double, double, double, double, double) において、
		 *	(-500, 500, -500, 500, 0, 10000) と設定した場合の初期値が生成されます。
		 */
		fk_Ortho();

		//! デストラクタ
		~fk_Ortho();

		//! ファイナライザ
		!fk_Ortho();

		//! クリッピング左側面距離プロパティ
		/*!
		 *	視線ベクトルからクリッピング左側面への距離の設定や参照を行います。
		 */
		property double Left {
			void set(double);
			double get();
		}

		//! クリッピング左側面距離プロパティ
		/*!
		 *	視線ベクトルからクリッピング右側面への距離の設定や参照を行います。
		 */
		property double Right {
			void set(double);
			double get();
		}

		//! クリッピング左側面距離プロパティ
		/*!
		 *	視線ベクトルからクリッピング下側面への距離の設定や参照を行います。
		 */
		property double Bottom {
			void set(double);
			double get();
		}

		//! クリッピング左側面距離プロパティ
		/*!
		 *	視線ベクトルからクリッピング上側面への距離の設定や参照を行います。
		 */
		property double Top {
			void set(double);
			double get();
		}

		//! クリッピング近距離距離プロパティ
		/*!
		 *	カメラからクリッピング近距離面への距離の設定や参照を行います。
		 */
		property double Near {
			void set(double);
			double get();
		}

		//! クリッピング遠距離距離プロパティ
		/*!
		 *	カメラからクリッピング遠距離面への距離の設定や参照を行います。
		 */
		property double Far {
			void set(double);
			double get();
		}

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
		void SetAll(double left, double right, double bottom,
					double top, double near, double far);
	};
}
