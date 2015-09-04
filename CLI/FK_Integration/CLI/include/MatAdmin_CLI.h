// MatAdmin_CLI.h

#pragma once

#include <FK/MatAdmin.h>
#include "Base_CLI.h"
#include "Matrix_CLI.h"

namespace FK_CLI
{
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
	 *	グローバル座標系による制御関数は「Gl」というプレフィックスを持ち、
	 *	ローカル座標系による制御関数は「Lo」というプレフィックスを持ちます。
	 *	ほとんどの制御関数は「Gl」版と「Lo」版で同一の引数を持った関数が存在しています。
	 *	(例外は fk_Model::GlMoveTo() と GlVec() です。
	 *	これについてはそれぞれの関数の項で説明します。)
	 *
	 *	あるモデルのローカル座標系に対し、別のモデルを配置する「親子関係」については、
	 *	fk_Model を参照して下さい。
	 *
	 *	\sa fk_Model
	 */
	public ref class fk_MatrixAdmin : fk_BaseObject {
	internal:
		::fk_MatrixAdmin * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_MatrixAdmin::fk_MatrixAdmin(bool argNewFlg);
		fk_MatrixAdmin::~fk_MatrixAdmin();
		fk_MatrixAdmin::!fk_MatrixAdmin();
#endif

		//! 位置ベクトルプロパティ
		/*!
		 *	モデルの位置ベクトルを参照します。
		 *	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的な位置ベクトルとなります。
		 *	グローバル座標系での正確な位置ベクトルを取得したい場合は、
		 *	fk_Model::InhPosition を利用して下さい。
		 *
		 *	本プロパティは設定を行うことはできません。
		 *	位置指定は fk_Model::GlMoveTo() を利用してください。
		 *
		 *	\sa Vec, Upvec, Angle, fk_Model::InhPosition
		 */
		property fk_Vector^ Position {
			fk_Vector^ get();
		}

		//! 方向ベクトルプロパティ
		/*!
		 *	モデルの方向ベクトルを参照します。
		 * 	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的な方向ベクトルとなります。
		 *	グローバル座標系での正確な方向ベクトルを取得したい場合は、
		 *	fk_Model::InhVec を利用して下さい。
		 *
		 *	本プロパティは設定を行うことはできません。
		 *	方向指定は GlVec() を利用してください。
		 *
		 *	\sa Position, Upvec, Angle, fk_Model::InhVec
		 */
		property fk_Vector^ Vec {
			fk_Vector^ get();
		}

		//! アップベクトルプロパティ
		/*!
		 *	モデルのアップベクトルを参照します。
		 * 	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的なアップベクトルとなります。
		 *	グローバル座標系での正確なアップベクトルを取得したい場合は、
		 *	fk_Model::InhUpvec を利用して下さい。
		 *
		 *	本プロパティは設定を行うことはできません。
		 *	方向指定は GlUpvec() を利用してください。
		 *
		 *	\sa Position, Vec, Angle, fk_Model::InhUpvec
		 */
		property fk_Vector^ Upvec {
			fk_Vector^ get();
		}

		//! オイラー角取得関数
		/*!
		 *	モデルの姿勢をオイラー角で参照します。
		 *	親モデルが設定されている場合、
		 *	親モデルの座標系からの相対的なオイラー角となります。
		 *	グローバル座標系での正確なオイラー角を取得したい場合は、
		 *	fk_Model::InhAngle を利用して下さい。
		 *	オイラー角についての詳細は、 fk_Angle の説明を参照して下さい。
		 *
		 *	本プロパティは設定を行うことはできません。
		 *	オイラー角指定は GlAngle() を利用してください。
		 *
		 *	\sa Position, Vec, Upvec, fk_Model::InhAngle, fk_Angle
		 */
		property fk_Angle^ Angle {
			fk_Angle^ get();
		}

		//! 変換行列プロパティ
		/*!
		 *	モデルの位置と姿勢を表す変換行列を参照します。
		 *	ここで取得する変換行列は、
		 *	親モデルが存在する場合は親モデルに対する変換となります。
		 *	グローバル座標系での変換行列を取得したい場合は、
		 *	fk_Model::InhMatrix を利用して下さい。
		 *
		 *	\sa InvMatrix, fk_Model::InhMatrix, BaseMatrix
		 */
		property fk_Matrix^ Matrix {
			fk_Matrix^ get();
		}

		//! 逆変換行列プロパティ
		/*!
		 *	モデルの位置と姿勢を表す変換行列の、逆行列を参照します。
		 *	これは、 Matrix プロパティで得られる行列の逆行列となります。
		 *	ここで取得する逆変換行列は、
		 *	親モデルが存在する場合は親モデルに対する逆変換となります。
		 *	グローバル座標系での逆変換行列を取得したい場合は、
		 *	fk_Model::InhInvMatrix を利用して下さい。
		 *
		 *	\sa Matrix, fk_Model::InhInvMatrix
		 */
		property fk_Matrix^ InvMatrix {
			fk_Matrix^ get();
		}

		//! 移動・回転要素変換行列プロパティ
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列を参照します。
		 *	親モデルが存在する場合は親モデルに対する変換となります。
		 *	グローバル座標系での変換行列を取得したい場合は、
		 *	fk_Model::InhBaseMatrix を利用して下さい。
		 *
		 *	\sa Matrix, fk_Model::InhBaseMatrix
		 */
		property fk_Matrix^ BaseMatrix {
			fk_Matrix^ get();
		}

		//! 移動・回転要素逆変換行列プロパティ
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列の逆行列を参照します。
		 *	親モデルが存在する場合は親モデルに対する逆変換となります。
		 *	グローバル座標系での逆変換行列を取得したい場合は、
		 *	fk_Model::InhInvBaseMatrix を利用して下さい。
		 *
		 *	\sa InvMatrix, fk_Model::InhInvBaseMatrix,
		 */
		property fk_Matrix^ InvBaseMatrix {
			fk_Matrix^ get();
		}

		//! 拡大縮小状態判定プロパティ
		/*!
		 *	モデルの拡大・縮小状態を参照します。
		 *	拡大縮小倍率に 1 以外が設定されている場合 true、
		 *	されていない場合 false となります。
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
		 *		本プロパティの結果は false となります。
		 */
		property bool ScaleMode {
			bool get();
		}

		//! 全体倍率プロパティ
		/*!
		 *	モデル全体の拡大・縮小倍率の参照・設定を行います。
		 *
		 *	\sa SetScale(), PrdScale(), GetScale()
		 */
		property double Scale {
			double get();
			void set(double);
		}
		
		//! \name 拡大縮小関連関数
		//@{

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
		 *	\param[in]	axis		軸方向。fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa SetScale(double, double, double), Scale, PrdScale(), GetScale()
		 */
		bool SetScale(double scale, fk_Axis axis);

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
		 *
		 *	\sa SetScale(double, fk_Axis), Scale, PrdScale(), GetScale()
		 */
		bool SetScale(double x, double y, double z);

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
		 *
		 *	\sa PrdScale(double, fk_Axis), PrdScale(double, double, double),
		 *		Scale, SetScale(), GetScale()
		 */
		bool PrdScale(double scale);

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
		 *	\param[in]	axis		軸方向。fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa PrdScale(double), PrdScale(double, double, double),
		 *		Scale, SetScale(), GetScale()
		 */
		bool PrdScale(double scale, fk_Axis axis);

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
		 *
		 *	\sa PrdScale(double), PrdScale(double, fk_Axis),
		 *		Scale, SetScale(), GetScale()
		 */
		bool PrdScale(double x, double y, double z);

		//! 軸方向倍率取得関数
		/*!
		 *	モデルの特定軸方向拡大・縮小倍率を取得します。
		 *
		 *	\param[in]	axis		軸方向。fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\return		モデル軸方向倍率
		 *
		 *	\sa SetScale(double, fk_Axis), SetScale(double, double, double),
		 *		PrdScale(double, fk_Axis), PrdScale(double, double, double), Scale
		 */
		double GetScale(fk_Axis axis);
		//@}
		
		//! \name 姿勢制御関数
		//@{

		//! グローバル座標系注視点設定関数1
		/*!
		 *	モデルの方向ベクトルを、
		 *	グローバル座標系による位置 p に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	p を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		p		注視点位置ベクトル
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					現在のモデルの位置ベクトルと等しい場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa LoFocus(), GlVec(), GlUpvec(), GlAngle()
		 */
		bool GlFocus(fk_Vector^ p);

		//! グローバル座標系注視点設定関数2
		/*!
		 *	モデルの方向ベクトルを、
		 *	グローバル座標系による位置 (x, y, z) に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	(x, y, z) を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
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
		 *	\sa LoFocus(), GlVec(), GlUpvec(), GlAngle()
		 */
		bool GlFocus(double x, double y, double z);

		//! ローカル座標系注視点設定関数1
		/*!
		 *	モデルの方向ベクトルを、
		 * 	ローカル座標系による位置 p に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	p を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
		 *
		 *	\param[in]		p		注視点位置ベクトル
		 *
		 *	\return			与えられた注視点位置ベクトルが、
		 *					零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa GlFocus(), GlUpvec(), LoUpvec(), LoAngle()
		 */
		bool LoFocus(fk_Vector^ p);

		//! ローカル座標系注視点設定関数2
		/*!
		 *	モデルの方向ベクトルを、
		 * 	ローカル座標系による位置 (x, y, z) に向くように方向ベクトルを設定します。
		 *	モデルをカメラとして解釈すると、
		 *	(x, y, z) を注視点としてカメラを向けることになります。
		 *
		 *	なお、この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
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
		 *	\sa GlFocus(), GlUpvec(), LoUpvec(), LoAngle()
		 */
		bool LoFocus(double x, double y, double z);

		//! グローバル座標系方向ベクトル設定関数1
		/*!
		 *	モデルの方向ベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *
		 *	この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
		 *
		 *	\note
		 *		GlVec() 関数に対応するローカル座標系関数
		 *		「LoVec()」関数は存在しません。
		 *		これは、LoVec() 関数はその意味的に
		 *		LoFocus() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		v		方向ベクトル
		 *
		 *	\return			与えられた方向ベクトルが零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa GlFocus(), GlUpvec(), GlAngle(), LoFocus()
		 */
		bool GlVec(fk_Vector^ v);

		//! グローバル座標系方向ベクトル設定関数2
		/*!
		 *	モデルの方向ベクトルを、グローバル座標系において与えられたベクトルに設定します。
		 *	ベクトルは正規化されている必要はありませんが、
		 *	零ベクトルであってはなりません。
		 *
		 *	この関数を呼んだ時点でのアップベクトルの状態は規定されていません。
		 *	アップベクトルを含めた姿勢制御を行うため、
		 *	GlUpvec() などと併用しなければなりません。
		 *
		 *	\note
		 *		GlVec() 関数に対応するローカル座標系関数
		 *		「LoVec()」関数は存在しません。
		 *		これは、LoVec() 関数はその意味的に
		 *		LoFocus() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		x		方向ベクトルのx成分
		 *	\param[in]		y		方向ベクトルのx成分
		 *	\param[in]		z		方向ベクトルのx成分
		 *
		 *	\return			与えられた方向ベクトルが零ベクトルであった場合、
		 *					姿勢を変更せずに false を返します。
		 *					それ以外の場合、姿勢を変更し true を返します。
		 *
		 *	\sa GlFocus(), GlUpvec(), GlAngle(), LoFocus()
		 */
		bool GlVec(double x, double y, double z);

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
		 *	\sa GlFocus(), GlVec(), GlAngle(), LoUpvec()
		 */
		bool GlUpvec(fk_Vector^ v);

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
		 *	\sa GlFocus(), GlVec(), GlAngle(), LoUpvec()
		 */
		bool GlUpvec(double x, double y, double z);

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
		 *	\sa LoFocus(), LoAngle(), GlUpvec()
		 */
		bool LoUpvec(fk_Vector^ v);

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
		 *	\sa LoFocus(), LoAngle(), GlUpvec()
		 */
		bool LoUpvec(double x, double y, double z);

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
		 *	\sa LoAngle(), GlVec(), GlUpvec(), fk_Angle
		 */
		bool GlAngle(fk_Angle^ angle);

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
		 *	\sa LoAngle(), GlVec(), GlUpvec(), fk_Angle
		 */
		bool GlAngle(double h, double p, double b);

		//! ローカル座標系オイラー角設定関数1
		/*!
		 *	モデルの姿勢を、ローカル座標系におけるオイラー角で設定します。
		 *	オイラー角についての詳しい解説は fk_Angle を参照して下さい。
		 *
		 *	\param[in]		angle		姿勢を表すオイラー角
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlAngle(), LoFocus(), LoUpvec(), fk_Angle
		 */
		bool LoAngle(fk_Angle^ angle);

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
		 *	\sa GlAngle(), LoFocus(), LoUpvec(), fk_Angle
		 */
		bool LoAngle(double h, double p, double b);
		//@}
	};
}

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
