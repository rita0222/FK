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
#ifndef __FK_MATADMIN_HEADER__
#define __FK_MATADMIN_HEADER__

#include <FK/Base.h>
#include <FK/Matrix.h>
#include <FK/Angle.h>

namespace FK {

	//! モデルの位置や姿勢を管理するクラス
	/*!
	 *	このクラスは fk_Model クラスの基底クラスで、
	 *	モデルの位置や姿勢の制御する機能を提供します。
	 *	これは、回転による指定や平行移動、任意位置指定など様々な方法があります。
	 *
	 *	このクラスの関数群を理解する上で欠かせない概念が
	 *	「グローバル座標系」と「ローカル座標系」です。
	 *	「グローバル座標系」とは、
	 *	シーン中に原点と x,y,z 各軸によって構成されている唯一の座標系です。
	 *	これに対し「ローカル座標系」とは、各モデルごとに存在する座標系であり、
	 *	モデルの中心を原点とし、前方向を -z 方向、上方向を +y 方向、
	 *	右方向を +x 方向とした座標系のことです。
	 *
	 *	グローバル座標系による指定では、
	 *	各モデルの位置や向いている方向などに依存しない動作となります。
	 *	例えば、-z 方向への平行移動を指示した場合は、
	 *	モデルがどちらを向いていても一律に -z 方向へ移動していきます。
	 *	感覚的には、モデルの制御を「東西南北」といった
	 *	絶対的な方角で指定すると考えればわかりやすいでしょう。
	 *
	 *	一方、ローカル座標系による指定では各モデルの位置や姿勢が重要となります。
	 *	同じように -z 方向への移動を指示した場合、
	 *	各モデルは現在モデルが向いている方向へ「前進」していくことになります。
	 *	+x 方向を向いているモデルは +x 方向へ、
	 *	-y 方向を向いているモデルは -y 方向へ移動していきます。
	 *	このように、ローカル座標系の指定は「前後左右」による指定と言えます。
	 *
	 *	このクラスのメンバ関数は、
	 *	グローバル座標系による制御関数は「gl」というプレフィックスを持ち、
	 *	ローカル座標系による制御関数は「lo」というプレフィックスを持ちます。
	 *	ほとんどの制御関数は「gl」版と「lo」版で同一の引数を持った関数が存在しています。
	 *	(例外は glMoveTo() と glVec() です。
	 *	これについてはそれぞれの関数の項で説明します。)
	 *
	 *	あるモデルのローカル座標系に対し、別のモデルを配置する「親子関係」については、
	 *	fk_Model を参照して下さい。
	 *
	 *	\sa fk_Model
	 */


	class fk_MatrixAdmin : public fk_BaseObject {

	public:

		//! コンストラクタ
		fk_MatrixAdmin(fk_Type = fk_Type::MATRIXADMIN);

		//! デストラクタ
		virtual ~fk_MatrixAdmin();

		//! \name 状態参照関数
		///@{

		//! 位置ベクトル取得関数
		/*!
		 *	モデルの位置ベクトルを取得します。
		 *	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的な位置ベクトルとなります。
		 *	グローバル座標系での正確な位置ベクトルを取得したい場合は、
		 *	fk_Model::getInhPosition() を利用して下さい。
		 *
		 *	\return		親モデル座標系での位置ベクトル
		 *
		 *	\sa getVec(), getUpvec(), getAngle(), fk_Model::getInhPosition()
		 */
		fk_Vector		getPosition(void) const;

		//! 方向ベクトル取得関数
		/*!
		 *	モデルの方向ベクトルを取得します。
		 * 	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的な方向ベクトルとなります。
		 *	グローバル座標系での正確な方向ベクトルを取得したい場合は、
		 *	fk_Model::getInhVec() を利用して下さい。
		 *
		 *	\return		親モデル座標系での方向ベクトル
		 *
		 *	\sa getPosition(), getUpvec(), getAngle(), fk_Model::getInhVec()
		 */
		fk_Vector		getVec(void) const;

		//! アップベクトル取得関数
		/*!
		 *	モデルのアップベクトルを取得します。
		 * 	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的なアップベクトルとなります。
		 *	グローバル座標系での正確なアップベクトルを取得したい場合は、
		 *	fk_Model::getInhUpvec() を利用して下さい。
		 *
		 *	\return		親モデル座標系でのアップベクトル
		 *
		 *	\sa getPosition(), getVec(), getAngle(), fk_Model::getInhUpvec()
		 */
		fk_Vector		getUpvec(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Vector		getUpVec(void) const;
#endif

		//! オイラー角取得関数
		/*!
		 *	モデルの姿勢をオイラー角で取得します。
		 *	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的なオイラー角となります。
		 *	グローバル座標系での正確なオイラー角を取得したい場合は、
		 *	fk_Model::getInhAngle() を利用して下さい。
		 *	オイラー角についての詳細は、 fk_Angle の説明を参照して下さい。
		 *
		 *	\return		モデルの姿勢オイラー角
		 *
		 *	\sa getPosition(), getVec(), getUpvec(), fk_Model::getInhAngle(), fk_Angle
		 */
		fk_Angle		getAngle(void) const;

		//! 変換行列取得関数
		/*!
		 *	モデルの位置と姿勢を表す変換行列を取得します。
		 *	ここで取得する変換行列は、
		 *	親モデルが存在する場合は親モデルに対する変換となります。
		 *	グローバル座標系での変換行列を取得したい場合は、
		 *	fk_Model::getInhMatrix() を利用して下さい。
		 *
		 *	\return		モデルの変換行列
		 *
		 *	\sa getInvMatrix(), fk_Model::getInhMatrix(), getBaseMatrix()
		 */
		fk_Matrix		getMatrix(void) const;

		//! 逆変換行列取得関数
		/*!
		 *	モデルの位置と姿勢を表す変換行列の、逆行列を取得します。
		 *	これは、 getMatrix() 関数で得られる行列の逆行列となります。
		 *	ここで取得する逆変換行列は、
		 *	親モデルが存在する場合は親モデルに対する逆変換となります。
		 *	グローバル座標系での逆変換行列を取得したい場合は、
		 *	fk_Model::getInhInvMatrix() を利用して下さい。
		 *
		 *	\return		モデルの逆変換行列
		 *
		 *	\sa getMatrix(), fk_Model::getInhInvMatrix()
		 */
		fk_Matrix		getInvMatrix(void) const;

		//! 移動・回転要素変換行列取得関数
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列を取得します。
		 *	親モデルが存在する場合は親モデルに対する変換となります。
		 *	グローバル座標系での変換行列を取得したい場合は、
		 *	fk_Model::getInhBaseMatrix() を利用して下さい。
		 *
		 *	\return		モデルの移動・回転要素変換行列
		 *
		 *	\sa getMatrix(), fk_Model::getInhBaseMatrix(), fk_OrthoMatrix
		 */
		fk_OrthoMatrix	getBaseMatrix(void) const;

		//! 移動・回転要素逆変換行列取得関数
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列の逆行列を取得します。
		 *	親モデルが存在する場合は親モデルに対する逆変換となります。
		 *	グローバル座標系での逆変換行列を取得したい場合は、
		 *	fk_Model::getInhInvBaseMatrix() を利用して下さい。
		 *
		 *	\return		モデルの移動・回転要素逆変換行列
		 *
		 *	\sa getInvMatrix(), fk_Model::getInhInvBaseMatrix(), fk_OrthoMatrix
		 */
		fk_OrthoMatrix	getInvBaseMatrix(void) const;

		///@}

		//! \name 拡大縮小関連関数
		///@{

		//! 全体絶対倍率設定関数
		/*!
		 *	モデル全体の拡大・縮小倍率を設定します。
		 *	倍率に 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	scale		倍率
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			setScale(const double scale);

		//! 軸方向絶対倍率設定関数
		/*!
		 *	モデルの、特定軸方向の拡大・縮小倍率を設定します。
		 *	倍率に 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	scale		倍率
		 *	\param[in]	axis		軸方向。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			setScale(const double scale, fk_Axis axis);

		//! 軸方向個別絶対倍率設定関数
		/*!
		 *	モデルの、各軸方向の拡大・縮小倍率を設定します。
		 *	各倍率のいずれかで 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	x			x方向の倍率
		 *	\param[in]	y			y方向の倍率
		 *	\param[in]	z			z方向の倍率
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			setScale(const double x, const double y, const double z);

		//! 全体相対倍率設定関数
		/*!
		 *	モデルの現在の全体拡大・縮小倍率に対し、引数で与えられた倍率を掛けます。
		 *	倍率に 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	scale		掛ける倍率
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			prdScale(const double scale);

		//! 軸方向相対倍率設定関数
		/*!
		 *	モデルの、特定軸方向の拡大・縮小倍率に対し、引数で与えられた倍率を掛けます。
		 *	倍率に 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	scale		掛ける倍率
		 *	\param[in]	axis		軸方向。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			prdScale(const double scale, fk_Axis axis);

		//! 軸方向個別相対倍率設定関数
		/*!
		 *	モデルの、各軸方向の拡大・縮小倍率に対し、引数で与えられた倍率を掛けます。
		 *	各倍率のいずれかで 0 を入力した場合、エラーとして倍率の変更を行いません。
		 *
		 *	\note
		 *		全体の倍率と、軸方向の倍率はそれぞれ別個に管理されています。
		 *		結果的なモデルの各軸方向への倍率は、全体倍率と軸方向倍率の積となります。
		 *
		 *	\param[in]	x			x方向へ掛ける倍率
		 *	\param[in]	y			y方向へ掛ける倍率
		 *	\param[in]	z			z方向へ掛ける倍率
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool			prdScale(const double x, const double y, const double z);

		//! 全体倍率取得関数
		/*!
		 *	モデルの全体拡大・縮小倍率を取得します。
		 *
		 *	\return		モデル全体倍率
		 */
		double			getScale(void) const;

		//! 軸方向倍率取得関数
		/*!
		 *	モデルの特定軸方向拡大・縮小倍率を取得します。
		 *
		 *	\param[in]	axis		軸方向。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\return		モデル軸方向倍率
		 */
		double			getScale(fk_Axis axis) const;

		//! 拡大縮小状態判定関数
		/*!
		 *	モデルの拡大・縮小状態を取得します。
		 *
		 *	モデルの拡大・縮小倍率が、
		 *	全体および軸方向のいずれかで 1 以外に設定されている場合、
		 *	モデルの拡大縮小が行われると解釈します。
		 *
		 *	\note
		 *		ここでの判定は、
		 *		単純に倍率数値が全て 1 であるかどうかで判断されます。
		 *		たとえば、全体倍率を 1/2 とし、
		 *		軸方向倍率を全て 2 に設定した場合、
		 *		結果としてモデルの拡大縮小は行われないことになりますが、
		 *		本関数の結果は false となります。
		 *
		 *	\return
		 *		拡大縮小倍率に 1 以外が設定されている場合 true を、
		 *		されていない場合 false を返します。
		 */
		bool			getScaleMode(void) const;

		///@}

		//! \name 回転制御関数
		///@{

		//! グローバル座標系座標軸回転関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、origin を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec_() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate_() を利用して下さい。
		 *
		 *	\param[in]		origin
		 *		グローバル座標系での回転軸上の点
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotateWithVec_(fk_Vector &, fk_Axis, double),
		 *		loRotate_(fk_Vector &, fk_Axis, double),
		 *		fk_Model::glRotate(fk_Vector, fk_Axis, double)
		 */
		bool	glRotate_(fk_Vector &origin, fk_Axis axis, double theta);

		//! グローバル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(orgX, orgY, orgZ) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec_() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate_() を利用して下さい。
		 *
		 *	\param[in]		orgX		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		グローバル座標系での回転軸上の点のz成分
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotateWithVec_(double, double, double, fk_Axis, double),
		 *		loRotate_(double, double, double, fk_Axis, double),
		 *		fk_Model::glRotate(double, double, double, fk_Axis, double)
		 */
		bool 	glRotate_(double orgX, double orgY, double orgZ,
						  fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec_() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate_() を利用して下さい。
		 *
		 *	\param[in]		A		回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B		回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(fk_Vector &, fk_Vector &, double),
		 *		loRotate_(fk_Vector &, fk_Vector &, double),
		 *		fk_Model::glRotate(fk_Vector, fk_Vector, double)
		 */
		bool 	glRotate_(fk_Vector &A, fk_Vector &B, double theta);

		//! グローバル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec_() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate_() を利用して下さい。
		 *
		 *	\param[in]		Ax		回転軸上の1点 A の x 成分
		 *	\param[in]		Ay		回転軸上の1点 A の y 成分
		 *	\param[in]		Az		回転軸上の1点 A の z 成分
		 *	\param[in]		Bx		回転軸上の1点 B の x 成分
		 *	\param[in]		By		回転軸上の1点 B の y 成分
		 *	\param[in]		Bz		回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(double, double, double, double, double, double, double),
		 *		loRotate_(double, double, double, double, double, double, double),
		 *		fk_Model::glRotate(double, double, double, double, double, double, double)
		 */
		bool	glRotate_(double Ax, double Ay, double Az,
						  double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec_() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate_() を利用して下さい。
		 *
		 *	\param[in]		origin
		 *		ローカル座標系での回転軸上の点
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate_(fk_Vector &, fk_Axis, double),
		 *		loRotateWithVec_(fk_Vector &, fk_Axis, double),
		 *		fk_Model::loRotate(fk_Vector, fk_Axis, double)
		 */
		bool	loRotate_(fk_Vector &origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (orgX, orgY, orgZ) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec_() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate_() を利用して下さい。
		 *
		 *	\param[in]		orgX		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		ローカル座標系での回転軸上の点のz成分
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate_(double, double, double, fk_Axis, double),
		 *		loRotateWithVec_(double, double, double, fk_Axis, double),
		 *		fk_Model::loRotate(double, double, double, fk_Axis, double)
		 */
		bool	loRotate_(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec_() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate_() を利用して下さい。
		 *
		 *	\param[in]		A
		 *		ローカル座標系における回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B
		 *		ローカル座標系における回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(fk_Vector &, fk_Vector &, double),
		 *		loRotate_(fk_Vector &, fk_Vector &, double),
		 *		fk_Model::loRotate(fk_Vector, fk_Vector, double),
		 */
		bool	loRotate_(fk_Vector &A, fk_Vector &B, double theta);

		//! ローカル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec_() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate_() を利用して下さい。
		 *
		 *	\param[in]		Ax
		 *		ローカル座標系における回転軸上の1点 A の x 成分
		 *	\param[in]		Ay
		 *		ローカル座標系における回転軸上の1点 A の y 成分
		 *	\param[in]		Az
		 *		ローカル座標系における回転軸上の1点 A の z 成分
		 *	\param[in]		Bx
		 *		ローカル座標系における回転軸上の1点 B の x 成分
		 *	\param[in]		By
		 *		ローカル座標系における回転軸上の1点 B の y 成分
		 *	\param[in]		Bz
		 *		ローカル座標系における回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(double, double, double, double, double, double, double),
		 *		loRotate_(double, double, double, double, double, double, double),
		 *		fk_Model::loRotate(double, double, double, double, double, double, double)
		 */
		bool	loRotate_(double Ax, double Ay, double Az,
						  double Bx, double By, double Bz, double theta);

		//! グローバル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、origin を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate_() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		origin		グローバル座標系での回転軸上の点
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate_(fk_Vector &, fk_Axis, double),
		 *		loRotateWithVec_(fk_Vector &, fk_Axis, double),
		 *		fk_Model::glRotateWithVec(fk_Vector, fk_Axis, double)
		 */
		bool	glRotateWithVec_(fk_Vector &origin, fk_Axis axis, double theta);

		//! グローバル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(orgX, orgY, orgZ) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate_() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		orgX		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		グローバル座標系での回転軸上の点のz成分
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate_(double, double, double, fk_Axis, double),
		 *		loRotateWithVec_(double, double, double, fk_Axis, double),
		 *		fk_Model::glRotateWithVec(double, double, double, fk_Axis, double)
		 */
		bool	glRotateWithVec_(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate_() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		A		回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B		回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotate_(fk_Vector &, fk_Vector &, double),
		 *		loRotateWithVec_(fk_Vector &, fk_Vector &, double),
		 *		fk_Model::glRotateWithVec(fk_Vector, fk_Vector, double)
		 */
		bool	glRotateWithVec_(fk_Vector &A, fk_Vector &B, double theta);
	
		//! グローバル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate_() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		Ax		回転軸上の1点 A の x 成分
		 *	\param[in]		Ay		回転軸上の1点 A の y 成分
		 *	\param[in]		Az		回転軸上の1点 A の z 成分
		 *	\param[in]		Bx		回転軸上の1点 B の x 成分
		 *	\param[in]		By		回転軸上の1点 B の y 成分
		 *	\param[in]		Bz		回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotate_(double, double, double, double, double, double, double),
		 *		loRotateWithVec_(double, double, double, double, double, double, double),
		 *		fk_Model::glRotateWithVec(double, double, double, double, double, double, double)
		 */
		bool	glRotateWithVec_(double Ax, double Ay, double Az,
								 double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate_() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		origin		ローカル座標系での回転軸上の点
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loRotate_(fk_Vector &, fk_Axis, double),
		 *		glRotateWithVec_(fk_Vector &, fk_Axis, double),
		 *		fk_Model::loRotateWithVec(fk_Vector, fk_Axis, double)
		 */
		bool	loRotateWithVec_(fk_Vector &origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (orgX, orgY, orgZ) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate_() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		orgX		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		ローカル座標系での回転軸上の点のz成分
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loRotate_(double, double, double, fk_Axis, double),
		 *		glRotateWithVec_(double, double, double, fk_Axis, double),
		 *		fk_Model::loRotateWithVec(double, double, double, fk_Axis, double)
		 */
		bool	loRotateWithVec_(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate_() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		A
		 *		ローカル座標系における回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B
		 *		ローカル座標系における回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(fk_Vector &, fk_Vector &, double)
		 *		loRotate_(fk_Vector &, fk_Vector &, double),
		 *		fk_Model::loRotateWithVec(fk_Vector, fk_Vector, double)
		 */
		bool	loRotateWithVec_(fk_Vector &A, fk_Vector &B, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate_() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec_() を利用して下さい。
		 *
		 *	\param[in]		Ax
		 *		ローカル座標系における回転軸上の1点 A の x 成分
		 *	\param[in]		Ay
		 *		ローカル座標系における回転軸上の1点 A の y 成分
		 *	\param[in]		Az
		 *		ローカル座標系における回転軸上の1点 A の z 成分
		 *	\param[in]		Bx
		 *		ローカル座標系における回転軸上の1点 B の x 成分
		 *	\param[in]		By
		 *		ローカル座標系における回転軸上の1点 B の y 成分
		 *	\param[in]		Bz
		 *		ローカル座標系における回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec_(double, double, double, double, double, double, double),
		 *		loRotate_(double, double, double, double, double, double, double),
		 *		fk_Model::loRotateWithVec(double, double, double, double, double, double, double)
		 */
		bool	loRotateWithVec_(double Ax, double Ay, double Az,
								 double Bx, double By, double Bz, double theta);
		///@}

		//! \name 位置制御関数
		///@{

		//! グローバル座標系平行移動関数1
		/*!
		 *	モデルを、クローバル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルで指定します。
		 *
		 *	ローカル座標系による平行移動量の指定を行いたい場合は、
		 *	loTranslate_() を利用して下さい。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loTranslate_(fk_Vector &), fk_Model::glTranslate(fk_Vector)
		 */
		bool	glTranslate_(fk_Vector &v);

		//! グローバル座標系平行移動関数2
		/*!
		 *	モデルを、クローバル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	ローカル座標系による平行移動量の指定を行いたい場合は、
		 *	loTranslate_() を利用して下さい。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loTranslate_(double, double, double),
		 *		fk_Model::glTranslate(double, double, double)
		 */
		bool	glTranslate_(double x, double y, double z);

		//! ローカル座標系平行移動関数1
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルで指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	glTranslate_() を利用して下さい。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate_(fk_Vector &), glMoveTo_(fk_Vector &),
		 *		fk_Model::loTranslate(fk_Vector)
		 */
		bool	loTranslate_(fk_Vector &v);

		//! ローカル座標系平行移動関数2
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	glTranslate_() を利用して下さい。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate_(double, double, double), glMoveTo_(double, double, double),
		 *		fk_Model::loTranslate(double, double, double)
		 */
		bool	loTranslate_(double x, double y, double z);

		//! グローバル座標系位置指定関数1
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルで指定します。
		 *
		 *	\note
		 *		glMoveTo_() 関数に対応するローカル座標系関数
		 *		「loMoveTo_()」関数は存在しません。
		 *		これは、loMoveTo_() 関数はその意味的に
		 *		loTranslate_() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		p		移動先位置ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate_(fk_Vector &), loTranslate_(fk_Vector &),
		 *		fk_Model::glMoveTo(fk_Vector)
		 */
		bool	glMoveTo_(fk_Vector &p);

		//! グローバル座標系位置指定関数2
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	\note
		 *		glMoveTo_() 関数に対応するローカル座標系関数
		 *		「loMoveTo_()」関数は存在しません。
		 *		これは、loMoveTo_() 関数はその意味的に
		 *		loTranslate_() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		x		移動先位置ベクトルのx成分
		 *	\param[in]		y		移動先位置ベクトルのy成分
		 *	\param[in]		z		移動先位置ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate_(double, double, double), loTranslate_(double, double, double),
		 *		fk_Model::glMoveTo(double, double, double)
		 */
		bool	glMoveTo_(double x, double y, double z);

		///@}

		//! \name 姿勢制御関数
		///@{

		//! グローバル座標系注視点設定関数1
		/*!
		 *	モデルの方向ベクトルを、
		 *	グローバル座標系による位置 p に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	p を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		p		注視点位置ベクトル
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					現在のモデルの位置ベクトルと等しい場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa loFocus(), glVec(), glUpvec(), glAngle()
		 */
		bool			glFocus(fk_Vector p);

		//! グローバル座標系注視点設定関数2
		/*!
		 *	モデルの方向ベクトルを、
		 *	グローバル座標系による位置 (x, y, z) に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	(x, y, z) を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		x		注視点位置ベクトルのx成分
		 *	\param[in]		y		注視点位置ベクトルのy成分
		 *	\param[in]		z		注視点位置ベクトルのz成分
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					現在のモデルの位置ベクトルと等しい場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa loFocus(), glVec(), glUpvec(), glAngle()
		 */
		bool			glFocus(double x, double y, double z);

		//! ローカル座標系注視点設定関数1
		/*!
		 *	モデルの方向ベクトルを、
		 * 	ローカル座標系による位置 p に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	p を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		p		注視点位置ベクトル
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glUpvec(), loUpvec(), loAngle()
		 */
		bool			loFocus(fk_Vector p);

		//! ローカル座標系注視点設定関数2
		/*!
		 *	モデルの方向ベクトルを、
		 * 	ローカル座標系による位置 (x, y, z) に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	(x, y, z) を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		x		注視点位置ベクトルのx成分
		 *	\param[in]		y		注視点位置ベクトルのy成分
		 *	\param[in]		z		注視点位置ベクトルのz成分
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glUpvec(), loUpvec(), loAngle()
		 */
		bool			loFocus(double x, double y, double z);

		//! グローバル座標系方向ベクトル設定関数1
		/*!
		 *	モデルの方向ベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *
		 *	この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\note
		 *		glVec() 関数に対応するローカル座標系関数
		 *		「loVec()」関数は存在しません。
		 *		これは、loVec() 関数はその意味的に
		 *		loFocus() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		v		方向ベクトル
		 *
		 *	\return			与えられた方向ベクトルが零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glUpvec(), glAngle(), loFocus()
		 */
		bool			glVec(fk_Vector v);

		//! グローバル座標系方向ベクトル設定関数2
		/*!
		 *	モデルの方向ベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *
		 *	この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	glUpvec() などと併用しなければなりません。
		 *
		 *	\note
		 *		glVec() 関数に対応するローカル座標系関数
		 *		「loVec()」関数は存在しません。
		 *		これは、loVec() 関数はその意味的に
		 *		loFocus() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		x		方向ベクトルのx成分
		 *	\param[in]		y		方向ベクトルのx成分
		 *	\param[in]		z		方向ベクトルのx成分
		 *
		 *	\return			与えられた方向ベクトルが零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glUpvec(), glAngle(), loFocus()
		 */
		bool			glVec(double x, double y, double z);

		//! グローバル座標系アップベクトル設定関数1
		/*!
		 *	モデルのアップベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *	また、方向ベクトルと平行であった場合もエラーとなります。
		 *
		 *	\param[in]		v		アップベクトル
		 *
		 *	\return			与えられたアップベクトルが零ベクトルであるか、
		 *					方向ベクトルと平行であった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glVec(), glAngle(), loUpvec()
		 */
		bool			glUpvec(fk_Vector v);

		//! グローバル座標系アップベクトル設定関数2
		/*!
		 *	モデルのアップベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *	また、方向ベクトルと平行であった場合もエラーとなります。
		 *
		 *	\param[in]		x		アップベクトルのx成分
		 *	\param[in]		y		アップベクトルのy成分
		 *	\param[in]		z		アップベクトルのz成分
		 *
		 *	\return			与えられたアップベクトルが零ベクトルであるか、
		 *					方向ベクトルと平行であった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa glFocus(), glVec(), glAngle(), loUpvec()
		 */
		bool			glUpvec(double x, double y, double z);

		//! ローカル座標系アップベクトル設定関数1
		/*!
		 *	モデルのアップベクトルを、ローカル座標系において与えられたベクトルに設定します。
		 *	本関数においては、z成分の値は意味をなしませんが、
		 *	実際には 0 以外の値であっても問題なく動作します。
		 *
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *	また、z軸方向のベクトルと平行であった場合もエラーとなります。
		 *
		 *	\param[in]		v		アップベクトル
		 *
		 *	\return			与えられたアップベクトルが零ベクトルであるか、
		 *					z軸ベクトルと平行であった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa loFocus(), loAngle(), glUpvec()
		 */
		bool			loUpvec(fk_Vector v);

		//! ローカル座標系アップベクトル設定関数2
		/*!
		 *	モデルのアップベクトルを、ローカル座標系において与えられたベクトルに設定します。
		 *	本関数においては、z成分の値は意味をなしませんが、
		 *	実際には 0 以外の値であっても問題なく動作します。
		 *
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *	また、z軸方向のベクトルと平行であった場合もエラーとなります。
		 *
		 *	\param[in]		x		アップベクトルのx成分
		 *	\param[in]		y		アップベクトルのy成分
		 *	\param[in]		z		アップベクトルのz成分
		 *
		 *	\return			与えられたアップベクトルが零ベクトルであるか、
		 *					z軸ベクトルと平行であった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa loFocus(), loAngle(), glUpvec()
		 */
		bool			loUpvec(double x, double y, double z);

		//! グローバル座標系オイラー角設定関数1
		/*!
		 *	モデルの姿勢を、グローバル座標系におけるオイラー角で設定します。
		 *	オイラー角はモデルの姿勢を一意に決定できるため、
		 *	姿勢を厳密に保存、再現する方法として利用できます。
		 *	オイラー角についての詳しい解説は fk_Angle を参照して下さい。
		 *
		 *	\param[in]		angle		姿勢を表すオイラー角
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loAngle(), glVec(), glUpvec(), fk_Angle
		 */
		bool			glAngle(fk_Angle angle);

		//! グローバル座標系オイラー角設定関数2
		/*!
		 *	モデルの姿勢を、グローバル座標系におけるオイラー角で設定します。
		 *	オイラー角はモデルの姿勢を一意に決定できるため、
		 *	姿勢を厳密に保存、再現する方法として利用できます。
		 *	オイラー角についての詳しい解説は fk_Angle を参照して下さい。
		 *
		 *	\param[in]		h		姿勢を表すオイラー角のヘディング角
		 *	\param[in]		p		姿勢を表すオイラー角のピッチ角
		 *	\param[in]		b		姿勢を表すオイラー角のバンク角
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loAngle(), glVec(), glUpvec(), fk_Angle
		 */
		bool			glAngle(double h, double p, double b);

		//! ローカル座標系オイラー角設定関数1
		/*!
		 *	モデルの姿勢を、ローカル座標系におけるオイラー角で設定します。
		 *	オイラー角についての詳しい解説は fk_Angle を参照して下さい。
		 *
		 *	\param[in]		angle		姿勢を表すオイラー角
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glAngle(), loFocus(), loUpvec(), fk_Angle
		 */
		bool			loAngle(fk_Angle angle);

		//! ローカル座標系オイラー角設定関数2
		/*!
		 *	モデルの姿勢を、ローカル座標系におけるオイラー角で設定します。
		 *	オイラー角についての詳しい解説は fk_Angle を参照して下さい。
		 *
		 *	\param[in]		h		姿勢を表すオイラー角のヘディング角
		 *	\param[in]		p		姿勢を表すオイラー角のピッチ角
		 *	\param[in]		b		姿勢を表すオイラー角のバンク角
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glAngle(), loFocus(), loUpvec(), fk_Angle
		 */
		bool			loAngle(double h, double p, double b);

		///@}

	protected:

#ifndef FK_DOXYGEN_USER_PROCESS

		fk_OrthoMatrix	OrthoMatrix;	// Model Base Matrix
		fk_HVector		Position;		// Model Position
		fk_HVector		Vec, UpVec;		// Model Vector & Up Vector
		fk_Angle		Angle;			// Model Angle (Heading Pitch Bank)
		double			Scale;			// Model Scale
		double			xScale, yScale, zScale;	// Axis Scale
		bool			ScaleMode;

		void			RotateLtoG(fk_Vector *, const fk_Vector *, const fk_Angle *) const;
		void			VectorToHeadPitch(fk_Angle *, const fk_Vector *) const;
		void			VectorToAngle(fk_Angle *, const fk_Vector *, const fk_Vector *) const;
		void			AngleToVector(fk_Vector *, fk_Vector *, const fk_Angle *) const;
		void			AddAngle(fk_Angle *, const fk_Angle *) const;
	
		void			AdjustAngleToVec(void);
		void			AdjustVecToAngle(void);

		void			UpdateMatrix(bool = true);

		fk_OrthoMatrix	OrthonormalMatrix(const fk_Vector &, const fk_Vector &, const double) const;
		void			SetScaleMode(void);

		void			GlRotate_(const fk_Vector &, const fk_Vector &, const double);
		void			LoRotate_(const fk_Vector &, const fk_Vector &, const double);
		void			GlRotateWithVec_(const fk_Vector &, const fk_Vector &, double);
		void			LoRotateWithVec_(const fk_Vector &, const fk_Vector &, double);
#endif
	};
}

#endif // !__FK_MATADMIN_HEADER__


