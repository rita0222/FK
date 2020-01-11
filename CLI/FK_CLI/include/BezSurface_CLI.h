﻿/****************************************************************************
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
// BezSurface_CLI.h

#pragma once

#include <FK/BezSurface.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	//! Bezier曲面を生成、管理するクラス
	/*!
	 *	このクラスは、形状として Bezier 曲面を制御する機能を提供します。
	 *	初期状態はu,v両方で 3 次式で、制御点が全て原点にある状態となります。
	 *	現状では、2,3,4次式のいずれかのみしか生成できません。
	 */

	public ref class fk_BezSurface : fk_Shape {

	internal:
		::FK::fk_BezSurface * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_BezSurface(bool argNewFlg);
#endif
		
		//! コンストラクタ
		fk_BezSurface();

		//! デストラクタ
		~fk_BezSurface();

		//! ファイナライザ
		!fk_BezSurface();

		//! 次数プロパティ
		/*!
		 *	このプロパティは、曲面次数の設定や参照に使用します。
		 *	現状では、2,3,4のいずれかのみ以外は設定できません。
		 *	設定した場合、全ての制御点の位置ベクトルは原点になります。
		 */
		property int Degree {
			int get();
			void set(int value);
		}

		//! 分割数プロパティ
		/*!
		 *	このプロパティは、描画時分割数の設定や参照に使用します。
		 */
		property int Div {
			int get();
			void set(int value);
		}

		//! 初期化用メソッド
		/*!
		 *	このメソッドは、曲面を初期状態(3次式、全ての制御点が原点にある状態)にします。
		 */
		void Init(void);

		//! 制御点設定メソッド1
		/*!
		 *	曲面の制御点位置ベクトルを設定します。
		 *
		 *	\param[in] uID	設定する制御点の u方向 ID。先頭は 0 になります。
		 *	\param[in] vID	設定する制御点の v方向 ID。先頭は 0 になります。
		 *	\param[in] pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool SetCtrl(int uID, int vID, fk_Vector^ pos);

		//! 制御点参照メソッド
		/*!
		 *	曲面の制御点位置ベクトルを参照します。
		 *
		 *	\param[in]	uID	制御点のu方向ID
		 *	\param[in]	vID	制御点のv方向ID
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 */
		fk_Vector^ GetCtrl(int uID, int vID);

		//! 曲面点算出関数
		/*!
		 *	パラメータに対応する曲面上の点の位置ベクトルを返します。
		 *
		 *	\param[in]	u	曲面の u パラメータ
		 *	\param[in]	v	曲面の v パラメータ
		 *
		 *	\return 曲面上の点の位置ベクトル
		 */
		fk_Vector^ Pos(double u, double v);

		//! 曲面法線ベクトル算出メソッド
		/*!
		 *	曲面上の法線ベクトルを返します。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の法線ベクトル
		 */
		fk_Vector^ Norm(double u, double v);

		//! 曲面 u 方向偏微分ベクトル算出メソッド
		/*!
		 *	曲面上の u 方向偏微分ベクトルを返します。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の u 方向偏微分ベクトル
		 */
		fk_Vector^ UDeriv(double u, double v);

		//! 曲面 v 方向偏微分ベクトル算出メソッド
		/*!
		 *	曲面上の v 方向偏微分ベクトルを返します。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の v 方向偏微分ベクトル
		 */
		fk_Vector^ VDeriv(double u, double v);
	};
}
