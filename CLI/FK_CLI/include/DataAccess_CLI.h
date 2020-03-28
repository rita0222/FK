#pragma once

#include <FK/DataAccess.h>
#include "Reference_CLI.h"

namespace FK_CLI
{
	//!	ソリッドモデル用位相要素アクセスクラス
	/*!
	 *	このクラスは、 fk_Solid での各位相要素を参照するための機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Edge, fk_Loop
	 */
	public ref class fk_DataAccess : fk_Reference {
	internal:
		::FK::fk_DataAccess * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_DataAccess(bool argNewFlg);
		~fk_DataAccess();
#endif

		//! 頂点数プロパティ
		/*!
		 *	現在の頂点数を参照します。
		 */
		property int VNum {
		int get();
	}

		//! 半稜線数プロパティ
		/*!
		 *	現在の半稜線数を参照します。
		 */
		property int HNum {
		int get();
	}

		//! 稜線数プロパティ
		/*!
		 *	現在の稜線数を参照します。
		 */
		property int ENum {
		int get();
	}

		//! ループ数プロパティ
		/*!
		 *	現在のループ数を参照します。
		 */
		property int LNum {
		int get();
	}
		
		//!	データベース設定チェックメソッド
		/*!
		 *	データベース設定の有無をチェックします。
		 *	通常、ユーザが利用することはありません。
		 *
		 *	\return 設定済みであれば true、未設定であれば false を返します。
		 */
		bool CheckDB(void);

		//! 位相状況チェックメソッド
		/*!
		 *	位相状態の整合状態をチェックします。
		 *
		 *	\return 整合していれば true、非整合状態であれば false を返します。
		 */
		bool CheckTopology(void);

		//! \name 位相要素存在判定
		///@{

		//! 頂点位相要素存在判定メソッド1
		/*!
		 *	fk_Vertex 型の頂点位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] vertex 頂点位相要素
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistVertex(fk_Vertex^ vertex);

		//! 頂点位相要素存在判定メソッド2
		/*!
		 *	fk_Vertex 型の頂点位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] ID 頂点位相要素のID
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistVertex(int ID);

		//! 半稜線位相要素存在判定メソッド1
		/*!
		 *	fk_Half 型の半稜線位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] half 半稜線位相要素
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistHalf(fk_Half^ half);

		//! 半稜線位相要素存在判定メソッド2
		/*!
		 *	fk_Half 型の半稜線位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] ID 半稜線位相要素のID
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistHalf(int ID);

		//! 稜線位相要素存在判定メソッド1
		/*!
		 *	fk_Edge 型の稜線位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] edge 稜線位相要素
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistEdge(fk_Edge^ edge);

		//! 稜線位相要素存在判定メソッド2
		/*!
		 *	fk_Edge 型の稜線位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] ID 稜線位相要素のID
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistEdge(int ID);

		//! ループ位相要素存在判定メソッド1
		/*!
		 *	fk_Loop 型のループ位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] loop ループ位相要素
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistLoop(fk_Loop^ loop);

		//! ループ位相要素存在判定メソッド2
		/*!
		 *	fk_Loop 型のループ位相要素が形状内に存在するかどうかを判定します。
		 *
		 *	\param[in] ID ループ位相要素のID
		 *
		 *	\return 存在すれば true、しなければ false を返します。
		 */
		bool ExistLoop(int ID);
		///@}

		//! \name 位相要素参照
		///@{

		//! 頂点位相要素参照メソッド
		/*!
		 *	fk_Vertex 型の頂点位相要素のポインタを取得します。
		 *
		 *	\param[in] ID 頂点位相要素のID
		 *
		 *	\return 存在すれば位相要素のポインタを返します。
		 *	存在しなかった場合は null を返します。
		 */
		fk_Vertex^ GetVData(int ID);

		//! 半稜線位相要素参照メソッド
		/*!
		 *	fk_Half 型の半稜線位相要素のポインタを取得します。
		 *
		 *	\param[in] ID 半稜線位相要素のID
		 *
		 *	\return 存在すれば位相要素のポインタを返します。
		 *	存在しなかった場合は null を返します。
		 */
		fk_Half^ GetHData(int ID);

		//! 稜線位相要素参照メソッド
		/*!
		 *	fk_Edge 型の稜線位相要素のポインタを取得します。
		 *
		 *	\param[in] ID 稜線位相要素のID
		 *
		 *	\return 存在すれば位相要素のポインタを返します。
		 *	存在しなかった場合は null を返します。
		 */
		fk_Edge^ GetEData(int ID);

		//! ループ位相要素参照メソッド
		/*!
		 *	fk_Loop 型のループ位相要素のポインタを取得します。
		 *
		 *	\param[in] ID ループ位相要素のID
		 *
		 *	\return 存在すれば位相要素のポインタを返します。
		 *	存在しなかった場合は null を返します。
		 */
		fk_Loop^ GetLData(int ID);

		//! 頂点位相要素逐次参照メソッド
		/*!
		 *	fk_Vertex 型の頂点位相要素において、
		 *	引数で与えられた頂点要素の次に大きな ID を持つ
		 *	位相要素を返します。
		 *
		 *	\param[in] vertex 頂点位相要素。
		 *		ここに null を代入した場合、
		 *		形状中で最も ID が小さな位相要素を返します。
		 *		これは、必ずしも最初に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return vertex の次に大きな ID を持つ位相要素を返します。
		 *		以下のいずれかを満たしている場合、null を返します。
		 *		- vertex が形状内頂点の中で最大の ID であった場合。
		 *		- 形状中に頂点が存在しない場合。
		 *		- vertex が形状中に存在する頂点位相要素ではなかった場合。
		 */
		fk_Vertex^ GetNextV(fk_Vertex^ vertex);

		//! 半稜線位相要素逐次参照メソッド
		/*!
		 *	fk_Half 型の半稜線位相要素において、
		 *	引数で与えられた半稜線要素の次に大きな ID を持つ
		 *	位相要素を返します。
		 *
		 *	\param[in] half 半稜線位相要素。
		 *		ここに null を代入した場合、
		 *		形状中で最も ID が小さな位相要素を返します。
		 *		これは、必ずしも最初に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return half の次に大きな ID を持つ位相要素を返します。
		 *		以下のいずれかを満たしている場合、null を返します。
		 *		- half が形状内半稜線の中で最大の ID であった場合。
		 *		- 形状中に半稜線が存在しない場合。
		 *		- half が形状中に存在する半稜線位相要素ではなかった場合。
		 */
		fk_Half^ GetNextH(fk_Half^ half);


		//! 稜線位相要素逐次参照メソッド
		/*!
		 *	fk_Edge 型の稜線位相要素において、
		 *	引数で与えられた頂点要素の次に大きな ID を持つ
		 *	位相要素を返します。
		 *
		 *	\param[in] edge 稜線位相要素。
		 *		ここに null を代入した場合、
		 *		形状中で最も ID が小さな位相要素を返します。
		 *		これは、必ずしも最初に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return edge の次に大きな ID を持つ位相要素を返します。
		 *		以下のいずれかを満たしている場合、null を返します。
		 *		- edge が形状内稜線の中で最大の ID であった場合。
		 *		- 形状中に稜線が存在しない場合。
		 *		- edge が形状中に存在する稜線位相要素ではなかった場合。
		 */
		fk_Edge^ GetNextE(fk_Edge^ edge);

		//! ループ位相要素逐次参照メソッド
		/*!
		 *	fk_Loop 型のループ位相要素において、
		 *	引数で与えられたループ要素の次に大きな ID を持つ
		 *	位相要素を返します。
		 *
		 *	\param[in] loop ループ位相要素。
		 *		ここに null を代入した場合、
		 *		形状中で最も ID が小さな位相要素を返します。
		 *		これは、必ずしも最初に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return loop の次に大きな ID を持つ位相要素を返します。
		 *		以下のいずれかを満たしている場合、null を返します。
		 *		- loop が形状内ループの中で最大の ID であった場合。
		 *		- 形状中にループが存在しない場合。
		 *		- loop が形状中に存在するループ位相要素ではなかった場合。
		 */
		fk_Loop^ GetNextL(fk_Loop^ loop);

		//! 頂点位相最終要素参照メソッド
		/*!
		 *	fk_Vertex 型の頂点位相要素において、
		 *	形状中で最も ID が大きな位相要素を返します。
		 *	これは、必ずしも最後に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return 最もIDが大きな位相要素。
		 *		形状中に頂点が存在しなかった場合は、null を返します。
		 */
		fk_Vertex^ GetLastV(void);

		//! 半稜線位相最終要素参照メソッド
		/*!
		 *	fk_Half 型の半稜線位相要素において、
		 *	形状中で最も ID が大きな位相要素を返します。
		 *	これは、必ずしも最後に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return 最もIDが大きな位相要素。
		 *		形状中に半稜線が存在しなかった場合は、null を返します。
		 */
		fk_Half^ GetLastH(void);

		//! 稜線位相最終要素参照メソッド
		/*!
		 *	fk_Edge 型の稜線位相要素において、
		 *	形状中で最も ID が大きな位相要素を返します。
		 *	これは、必ずしも最後に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return 最もIDが大きな位相要素。
		 *		形状中に稜線が存在しなかった場合は、null を返します。
		 */
		fk_Edge^ GetLastE(void);

		//! ループ位相最終要素参照メソッド
		/*!
		 *	fk_Loop 型の頂点位相要素において、
		 *	形状中で最も ID が大きな位相要素を返します。
		 *	これは、必ずしも最後に生成した位相要素とは限らないことに注意して下さい。
		 *
		 *	\return 最もIDが大きな位相要素。
		 *		形状中にループが存在しなかった場合は、null を返します。
		 */
		fk_Loop^ GetLastL(void);
		///@}

		//! \name 位相要素格納コンテナ取得
		///@{

		//! 頂点コンテナ取得メソッド
		/*!
		 *	形状中の頂点要素を全て格納した array 型コンテナを取得します。
		 *
		 *	\note
		 *		本メソッドで取得した情報は、
		 *		位相変化を伴う変形を行う前まで有効です。
		 *		位相変化を伴う変形を行った場合に、
		 *		本メソッドで取得した位相要素を参照した場合の挙動は保証されません。
		 *
		 *	\return		頂点位相要素を格納したコンテナ。
		 *		
		 *
		 *	\sa GetNextV(), VNum
		 */
		cli::array<fk_Vertex^>^ GetVertexArray(void);

		//! 半稜線コンテナ取得メソッド
		/*!
		 *	形状中の半稜線要素を全て格納した array 型コンテナを取得します。
		 *
		 *	\note
		 *		本メソッドで取得した情報は、
		 *		位相変化を伴う変形を行う前まで有効です。
		 *		位相変化を伴う変形を行った場合に、
		 *		本メソッドで取得した位相要素を参照した場合の挙動は保証されません。
		 *
		 *	\return		半稜線位相要素を格納したコンテナ。
		 *		
		 *	\sa GetNextH(), HNum
		 */
		cli::array<fk_Half^>^ GetHalfArray(void);

		//! 稜線コンテナ取得メソッド
		/*!
		 *	形状中の稜線要素を全て格納した array 型コンテナを取得します。
		 *
		 *	\note
		 *		本メソッドで取得した情報は、
		 *		位相変化を伴う変形を行う前まで有効です。
		 *		位相変化を伴う変形を行った場合に、
		 *		本メソッドで取得した位相要素を参照した場合の挙動は保証されません。
		 *
		 *	\return		稜線位相要素を格納したコンテナ。
		 *
		 *	\sa GetNextE(), ENum
		 */
		cli::array<fk_Edge^>^ GetEdgeArray(void);

		//! ループコンテナ取得メソッド
		/*!
		 *	形状中のループ要素を全て格納した array 型コンテナを取得します。
		 *
		 *	\note
		 *		本メソッドで取得した情報は、
		 *		位相変化を伴う変形を行う前まで有効です。
		 *		位相変化を伴う変形を行った場合に、
		 *		本メソッドで取得した位相要素を参照した場合の挙動は保証されません。
		 *
		 *	\return		ループ位相要素を格納したコンテナ。
		 *
		 *	\sa GetNextL(), LNum
		 */
		cli::array<fk_Loop^>^ GetLoopArray(void);
		///@}
	};
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
