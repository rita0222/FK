﻿#ifndef __FK_TRACKBALL_HEADER__
#define __FK_TRACKBALL_HEADER__

#include <FK/Window.h>
#include <FK/Model.h>
#include <FK/Vector.h>
#include <FK/Angle.h>
#include <FL/Fl.H>

namespace FK {
	
	//! マウスによる視点操作クラス
	/*!	
	 *	このクラスは、マウスでの自由な視点操作を提供します。
	 *	本クラスの機能は fk_AppWindow 内で用いられており、
	 *	fk_AppWindow を利用する場合は本クラスを直接利用する必要はありません。
	 *	fk_Window を利用する場合で、
	 *	fk_AppWindow と同様のカメラ制御を行いたい場合に利用して下さい。
	 *
	 *	このクラスによって実現できる機能は以下の通りです。
	 *	- 右マウスボタンでドラッグ操作を行うと、オービット操作を行うことができます。
	 *		オービット操作とは、カメラが注視点を中心に回転することです。
	 *	- 中マウスボタン (近年の大抵のマウスではホイールを押し込むことを意味します)
	 *		でドラッグ操作を行うと、注視点とカメラ自体が操作に沿って移動します。
	 *	- ホイール操作を行うと、カメラのズームイン・アウトが行えます。
	 *	.
	 *	上記の操作は全て update() を行うことにより自動的に処理します。
	 *	利用者は、シーンの再描画と共に本クラスインスタンスの update()
	 *	呼ぶだけでよく、その他の処理は必要ありません。
	 *
	 *	\sa fk_Window, fk_AppWindow
	 */
	class fk_TrackBall {
#ifndef FK_DOXYGEN_USER_PROCESS
		class Member {
		public:
			fk_Window *fk_win;							// FKウィンドウ
			fk_Model *camera;							// カメラ
			fk_Vector lookPos;							// ３人称視点注視点
			// 操作に使用するマウスボタン
			//fk_MouseButton lookButton, moveButton;

			// 画面外にカーソルが出た場合の判定の有無
			bool overCheck;

			// エコーの有無
			//bool bEcho;

			int nowX, nowY, oldX, oldY;				// ウィンドウ上座標
			//int echoX, echoY;
			bool lookClick, distClick, moveClick;	// 1ループ前のクリックを記憶

			Member(fk_Window *, fk_Model *);
		};
#endif

	public:
		
		//! コンストラクタ
		/*!
		 *	\param[in]	win		カメラ制御を行うウィンドウ
		 *	\param[in]	camera	カメラ用モデル。後から setCamera() で変更が可能です。
		 */
		fk_TrackBall(fk_Window *win, fk_Model *camera = nullptr);

		//! カメラモデル設定関数
		/*!
		 *	制御用のカメラモデルを設定します。
		 *
		 *	\param[in]	camera	カメラ用モデル
		 */
		void setCamera(fk_Model *camera);

		//! カメラ設定有無参照関数
		/*!
		 *	カメラモデル設定の有無を参照します。
		 *
		 *	\return カメラが設定されている場合 true を、
		 *		設定されていない場合 false を返します。
		 */
		bool isSetCamera(void);

		//! カメラ注視点変更関数
		/*!
		 *	設定されているカメラモデルの注視点を変更します。
		 *
		 *	\param[in]	pos		注視点位置ベクトル
		 */
		
		void setLookTo(fk_Vector pos);

		//! 状態更新関数
		/*!
		 *	現在のデバイスの状態を検出し、カメラの位置・方向情報を更新します。
		 *	基本的な本クラスの利用方法は、シーン再描画と共に本関数を呼ぶだけであり、
		 *	他にすることはほとんどありません。
		 */
		void update(void);

	private:
		std::unique_ptr<Member> _m;
		
		static constexpr double DIVPOS = 10.0; // カーソル移動量
		static constexpr double DIVLOOK = 200.0; // カーソル処理量比率指定
		static constexpr double DIVDIST = 1.0; // ３人称視点制御カーソル移動量:処理量比率指定

		void ControlLookTo(void);
		void ControlLookToDist(void);
		void ControlLookToMove(void);
	};

	//using fkut_TrackBall = fk_TrackBall;


}

#endif //!__FK_TRACKBALL_HEADER__

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
