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

		property fk_Vector^ Upvec {
			fk_Vector^ get();
		}

		property fk_Angle^ Angle {
			fk_Angle^ get();
		}

		property fk_Matrix^ Matrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InvMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ BaseMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InvBaseMatrix {
			fk_Matrix^ get();
		}

		property bool ScaleMode {
			bool get();
		}

		property double Scale {
			double get();
			void set(double);
		}
		
		bool SetScale(double scale, fk_Axis axis);
		bool SetScale(double x, double y, double z);
		bool PrdScale(double scale);
		bool PrdScale(double scale, fk_Axis axis);
		bool PrdScale(double x, double y, double z);
		double GetScale(fk_Axis axis);

		bool GlFocus(fk_Vector^ V);
		bool GlFocus(double x, double y, double z);
		bool LoFocus(fk_Vector^ V);
		bool LoFocus(double x, double y, double z);
		bool GlVec(fk_Vector^ V);
		bool GlVec(double x, double y, double z);
		bool GlUpvec(fk_Vector^ V);
		bool GlUpvec(double x, double y, double z);
		bool LoUpvec(fk_Vector^ V);
		bool LoUpvec(double x, double y, double z);
		bool GlAngle(fk_Angle^ angle);
		bool GlAngle(double head, double pitch, double bank);
		bool LoAngle(fk_Angle^ angle);
		bool LoAngle(double head, double pitch, double bank);
	};
}
