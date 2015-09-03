// Line_CLI.h

#pragma once

#include <FK/Line.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
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
	 *	本クラスのメンバ関数が正しく動作しない可能性があります。
	 *
	 *	\sa	fk_Solid, fk_Model, fk_Shape
	 */
	public ref class fk_Line : fk_Solid {
	internal:
		::fk_Line * GetP(void);

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

		//! 単独線分追加関数1
		/*!
		 *	線分を追加します。
		 *	
		 *	\param[in]	array
		 *		端点位置ベクトルの配列。
		 *		array[0] に始点、array[1] に終点となるように配置してください。
		 */
		void PushLine(cli::array<fk_Vector^>^ array);

		//! 単独線分追加関数2
		/*!
		 *	線分を追加します。
		 *	
		 *	\param[in]	startPos		始点位置ベクトル
		 *	\param[in]	endPos			終点位置ベクトル
		 */
		void PushLine(fk_Vector^ startPos, fk_Vector^ endPos);

		//! 線分端点位置変更関数
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

		//! 単独線分端点位置設定関数
		/*!
		 *	この関数は、現在の線分本数によって挙動が異なります。
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

		//! 任意線分端点位置設定関数
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

		//! 単独線分生成関数
		/*!
		 *	1本の線分を生成します。
		 *	入力する fk_Vector 型の配列は、長さが 2 以上でなければなりません。
		 *	この関数を呼んだ場合、既にあった線分はすべて破棄されます。
		 *
		 *	\param[in]	array
		 *		fk_Vector 型の配列。array[0] が始点、array[1] が終点となります。
		 */
		void SetVertex(cli::array<fk_Vector^>^ array);
	};
}
