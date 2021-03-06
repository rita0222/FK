﻿#pragma once

#include <FK/Plane.h>
#include "Vector_CLI.h"

namespace FK_CLI
{
	using namespace System;

	//! 幾何平面を管理するクラス
	/*!
	 *	このクラスは、空間中の平面に関する幾何的な算出を行う機能を提供します。
	 *	このクラスは fk_Polygon のような形状を生成するためのものではなく、
	 *	純粋に幾何計算を行うためのものです。具体的には、以下のような処理が可能です。
	 *	- 平面と原点、あるいは平面と任意点の距離算出
	 *	- 平面と直線の交点算出
	 *	- 平面同士、あるいは平面とベクトルとの平行、垂直判定
	 *
	 *	fk_Plane において、平面 P の表現は平面上の点 \f$ \mathbf{B} \f$ と、
	 *	平面上の平行でない2つの単位ベクトル \f$ \mathbf{U}, \mathbf{V} \f$ によって、
	 *	\f[
	 *		\mathbf{P}(u, v) = \mathbf{B} + u\mathbf{U} + v\mathbf{V}
	 *	\f]
	 *	という式でなされます。\f$u, v\f$ は実数パラメータです。
	 *	各メソッドの解説では、\f$\mathbf{B}\f$ を「基点ベクトル」、
	 *	\f$\mathbf{U}, \mathbf{V}\f$を「Uベクトル」「Vベクトル」とします。
	 *
	 *	なお、平面が関与しない幾何計算は fk_Math クラスに集約しているので、
	 *	そちらも参照して下さい。
	 *
	 *	\sa fk_Math
	 */

	public ref class fk_Plane {
	internal:
		::FK::fk_Plane *pPlane;

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Plane(::FK::fk_Plane *argP);
#endif
		//! コンストラクタ
		fk_Plane();

		//! コピーコンストラクタ
		fk_Plane(fk_Plane^ P);

		//! デストラクタ
		~fk_Plane();

		//! ファイナライザ
		!fk_Plane();

		//! 文字列出力メソッド
		/*!
		 *	現在の平面情報を文字列として出力します。
		 *
		 *	\return		平面情報の文字列
		 */
		String^ ToString() override;

		//! 基点ベクトルプロパティ
		/*!
		 *	基点ベクトルを取得します。
		 */
		property fk_Vector^ BasePos {
			fk_Vector^ get();
		}

		//! Uベクトルプロパティ
		/*!
		 *	Uベクトルを取得します。
		 */
		property fk_Vector^ UVec {
			fk_Vector^ get();
		}

		//! Vベクトルプロパティ
		/*!
		 *	Vベクトルを取得します。
		 */
		property fk_Vector^ VVec {
			fk_Vector^ get();
		}

		//! 法線ベクトルプロパティ
		/*!
		 *	法線ベクトルを取得します。
		 */
		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		//! 原点距離参照メソッド
		/*!
		 *	平面と原点との距離を取得します。
		 */
		property double Dist {
			double get();
		}


		//! 平面設定メソッド1
		/*!
		 *	平面上の1点と、平面の法線ベクトルを指定することにより、平面を設定します。
		 *	基点ベクトルは pos となり、UベクトルとVベクトルは自動的に算出されます。
		 *	法線ベクトルとして零ベクトルが入力された場合はエラーとなります。
		 *
		 *	\param[in]		pos		基点ベクトル
		 *	\param[in]		norm	法線ベクトル
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SetPosNormal(fk_Vector^ pos, fk_Vector^ norm);

		//! 平面設定メソッド2
		/*!
		 *	平面上の3点を指定することにより、平面を設定します。
		 *	基点ベクトルは pos1 となり、
		 *	Uベクトルは (pos2 - pos1)、
		 *	Vベクトルは (pos3 - pos1) をそれぞれ正規化したものとなります。
		 *	3点が同一直線上にある場合はエラーとなります。
		 *
		 *	\param[in]	pos1	基点ベクトル
		 *	\param[in]	pos2	平面上の点の位置ベクトル
		 *	\param[in]	pos3	平面上の点の位置ベクトル
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool		Set3Pos(fk_Vector^ pos1,
							fk_Vector^ pos2,
							fk_Vector^ pos3);

		//! 平面設定メソッド3
		/*!
		 *	平面上の1点と、平面の法線ベクトルに垂直な平行でない
		 *	2つのベクトルを指定することにより、平面を設定します。
		 *	引数の U, V がそれぞれ Uベクトル、Vベクトルとして設定されます。
		 *	U, V が平行であるか、少なくとも一方が零ベクトルであった場合エラーとなります。
		 *
		 *	\param[in]		pos		基点ベクトル
		 *	\param[in]		U		Uベクトル。単位ベクトルである必要はありません。
		 *	\param[in]		V		Vベクトル。単位ベクトルである必要はありません。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SetPosUVVec(fk_Vector ^pos,
								fk_Vector ^U,
								fk_Vector ^V);

		//! 任意点距離参照メソッド
		/*!
		 *	平面と任意の点との距離を取得します。
		 *
		 *	\param[in]		pos		任意の位置ベクトル
		 *
		 *	\return			距離
		 */
		double		GetDist(fk_Vector^ pos);

		//! u,v パラメータによる平面上点参照メソッド
		/*!
		 *	概要で述べた数式に従って、平面上点の位置ベクトルを算出します。
		 *
		 *	\param[in]		u		uパラメータ
		 *	\param[in]		v		vパラメータ
		 *
		 *	\return		平面上点の位置ベクトル
		 */
		fk_Vector^	GetPos(double u, double v);

		//! ベクトル平行判定メソッド
		/*!
		 *	任意のベクトルが平行であるかどうかを判定します。
		 *	V が零ベクトルであった場合は常に false を返します。
		 *
		 *	\param[in]	V	任意ベクトル
		 *
		 *	\return		平行であれば true を、平行でなければ false を返します。
		 */
		bool		IsParallel(fk_Vector^ V);

		// 平面平行判定メソッド
		/*!
		 *	別の任意の平面と平行であるかどうかを判定します。
		 *
		 *	\param[in]	P	任意平面
		 *
		 *	\return		平行であれば true を、平行でなければ false を返します。
		 */
		bool		IsParallel(fk_Plane^ P);

		//! ベクトル垂直判定メソッド
		/*!
		 *	任意のベクトルが垂直であるかどうかを判定します。
		 *	V が零ベクトルであった場合は常に false を返します。
		 *
		 *	\param[in]	V	任意ベクトル
		 *
		 *	\return		垂直であれば true を、垂直でなければ false を返します。
		 */
		bool		IsVertical(fk_Vector^ V);

		// 平面垂直判定メソッド
		/*!
		 *	別の任意の平面と垂直であるかどうかを判定します。
		 *
		 *	\param[in]	P	任意平面
		 *
		 *	\return		垂直であれば true を、垂直でなければ false を返します。
		 */
		bool		IsVertical(fk_Plane^ P);

		//! 交点位置ベクトル参照メソッド
		/*!
		 *	2点A, B を通る直線と平面との交点の位置ベクトルを取得します。
		 *	A,Bが同じ位置であった場合は、直線と平面が平行である場合、
		 *	エラーとなります。
		 *
		 *	\param[in]		A		直線上の1点
		 *	\param[in]		B		直線上の1点
		 *	\param[out]		pos		交点位置ベクトルが代入されます。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool		CalcCrossPos(fk_Vector^ A,
								 fk_Vector^ B,
								 fk_Vector^ pos);

		//! 交点直線パラメータ参照メソッド
		/*!
		 *	2点A, B を通る直線と平面との交点の、直線上でのパラメータを取得します。
		 *	直線式 \f$\mathbf{L}(t)\f$ は、以下のようなものであると想定します。
		 *	\f[
		 *		\mathbf{L}(t) = (1-t)\mathbf{A} + t\mathbf{B}
		 *	\f]
		 *	A,Bが同じ位置であった場合は、直線と平面が平行である場合、
		 *	エラーとなります。
		 *
		 *	\param[in]		A		直線上の1点
		 *	\param[in]		B		直線上の1点
		 *	\param[out]		t		交点の直線上でのパラメータが代入されます。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool		CalcCrossLineParam(fk_Vector^ A,
									   fk_Vector^ B,
									   double %t);

		//! 交点平面パラメータ参照メソッド
		/*!
		 *	2点A, B を通る直線と平面との交点の、平面上でのパラメータを取得します。
		 *	平面の式は概要のものと想定します。
		 *	A,Bが同じ位置であった場合は、直線と平面が平行である場合、
		 *	エラーとなります。
		 *	
		 *	\param[in]		A		直線上の1点
		 *	\param[in]		B		直線上の1点
		 *	\param[out]		u		交点の平面上でのuパラメータが代入されます。
		 *	\param[out]		v		交点の平面上でのvパラメータが代入されます。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool		CalcCrossPlaneParam(fk_Vector^ A,
										fk_Vector^ B,
										double %u, double %v);

		//! 交点情報参照メソッド
		/*!
		 *	2点A, B を通る直線と平面との交点の、直線上でのパラメータを取得します。
		 *	直線式 \f$\mathbf{L}(t)\f$は、以下のようなものであると想定します。
		 *	\f[
		 *		\mathbf{L}(t) = (1-t)\mathbf{A} + t\mathbf{B}
		 *	\f]
		 *	平面の式は概要のものと想定します。
		 *	A,Bが同じ位置であった場合は、直線と平面が平行である場合、
		 *	エラーとなります。
		 *
		 *	\param[in]		A		直線上の1点
		 *	\param[in]		B		直線上の1点
		 *	\param[out]		pos		交点位置ベクトルが代入されます。
		 *	\param[out]		t		交点の直線上でのパラメータが代入されます。
		 *	\param[out]		u		交点の平面上でのuパラメータが代入されます。
		 *	\param[out]		v		交点の平面上でのvパラメータが代入されます。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool		CalcCrossAll(fk_Vector^ A,
								 fk_Vector^ B,
								 fk_Vector^ pos,
								 double %t, double %u, double %v);

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
