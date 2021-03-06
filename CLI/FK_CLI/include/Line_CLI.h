﻿#pragma once

#include <FK/Line.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	//! 有向線分を生成、管理するクラス
	/*!
	 *	このクラスは、形状として有向線分を制御する機能を提供します。
	 *	1つのインスタンスで、複数の有向線分の制御が可能です。
	 *	特に断りがない場合、「線分」は有向線分のことを指すものとします。
	 *
	 *	本クラスの実質的な意義は、 fk_Solid が持つ汎用的な形状操作機能のうち、
	 *	線分を生成、管理することに特化していることです。
	 *	基底クラスの機能を利用することは可能ですが、
	 *	位相操作を伴う変形をした場合、
	 *	本クラスのメソッドが正しく動作しない可能性があります。
	 *
	 *	\sa	fk_Solid, fk_Model, fk_Shape
	 */
	public ref class fk_Line : fk_Shape {
	internal:
		::FK::fk_Line * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Line(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_Line();

		//! デストラクタ
		~fk_Line();

		//! ファイナライザ
		!fk_Line();

		//! 全消去メソッド
		/*!
		 *	すべてのデータを消去します。
		 */
		void	AllClear(void);

		//! 単独線分追加メソッド1
		/*!
		 *	線分を追加します。
		 *	
		 *	\param[in]	array
		 *		端点位置ベクトルの配列。
		 *		array[0] に始点、array[1] に終点となるように配置してください。
		 */
		void PushLine(IEnumerable<fk_Vector^>^ array);

		//! 単独線分追加メソッド2
		/*!
		 *	線分を追加します。
		 *	
		 *	\param[in]	startPos		始点位置ベクトル
		 *	\param[in]	endPos			終点位置ベクトル
		 */
		void PushLine(fk_Vector^ startPos, fk_Vector^ endPos);

		//! 線分端点位置変更メソッド
		/*!
		 *	線分の端点位置を変更します。
		 *
		 *	\param[in]	lineID
		 *		制御する線分ID。線分IDは、最初に生成したものが0で、
		 *		以降生成順に 1 ずつ増加したものになります。
		 *		存在しない線分 ID を指定した場合は何も起こりません。
		 *
		 *	\param[in]	startPos		始点位置ベクトル
		 *	\param[in]	endPos			終点位置ベクトル
		 *
		 *	\return
		 *		端点位置の設定がなされれば true、
		 *		そうでない場合は false を返します。
		 */
		bool ChangeLine(int lineID, fk_Vector^ startPos, fk_Vector^ endPos);

		//! 単独線分端点位置設定メソッド
		/*!
		 *	このメソッドは、現在の線分本数によって挙動が異なります。
		 *	- 線分が生成されていない場合、vertexID の値は無視され、
		 *		pos を両端点とする縮退した線分が生成されます。
		 *	- 線分が1本のみの場合は、その線分の端点位置を pos に変更します。
		 *		vertexID が 0 の場合始点、1 の場合終点を変更します。
		 *		vertexID がその他の値だった場合は、何も起こりません。
		 *	- 線分が2本以上あった場合は、何も起こりません。
		 *
		 *	\param[in]	vertexID	端点ID。(線分が1本のときのみ有効)
		 *	\param[in]	pos			端点の位置ベクトル
		 *
		 *	\return
		 *		なんらかの形で端点位置の設定がなされれば true、
		 *		そうでない場合は false を返します。
		 */
		bool SetVertex(int vertexID, fk_Vector^ pos);

		//! 任意線分端点位置設定メソッド
		/*!
		 *	生成されている任意の線分の端点位置を変更します。
		 *
		 *	\param[in]		lineID
		 *		制御する線分ID。線分IDは、最初に生成したものが0で、
		 *		以降生成順に 1 ずつ増加したものになります。
		 *		存在しない線分 ID を指定した場合は何も起こりません。
		 *
		 *	\param[in]		vertexID
		 *		始点の場合 0、終点の場合 1 を入力します。
		 *		その他の値を指定した場合は何も起こりません。
		 *
		 *	\param[in]		pos		端点の位置ベクトル
		 *
		 *	\return
		 *		端点位置の設定がなされれば true、
		 *		そうでない場合は false を返します。
		 */
		bool SetVertex(int lineID, int vertexID, fk_Vector^ pos);

		//! 単独線分生成メソッド
		/*!
		 *	1本の線分を生成します。
		 *	入力する fk_Vector 型の配列は、長さが 2 以上でなければなりません。
		 *	このメソッドを呼んだ場合、既にあった線分はすべて破棄されます。
		 *
		 *	\param[in]	array
		 *		fk_Vector 型の配列。array[0] が始点、array[1] が終点となります。
		 */
		void SetVertex(IEnumerable<fk_Vector^>^ array);
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
