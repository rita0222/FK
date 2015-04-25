// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "MatAdmin_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
	//! 境界ボリュームのタイプを表す列挙型
	public enum class fk_BoundaryMode {
		SPHERE,		//!<	境界球
		AABB,		//!<	軸平行境界ボックス (Axis Aligned Bounding Box)
		OBB,		//!<	有向境界ボックス (Oriented Bounding Box)
		CAPSULE,	//!<	カプセル型
		NONE		//!<	未定義境界
	};

	//! 境界ボリュームを管理するクラス
	/*!
	 *	このクラスは、モデルの干渉判定や衝突判定を行うための
	 *	「境界ボリューム」を制御する機能を提供します。
	 *
	 *	「境界ボリューム」とは、モデルが干渉判定や衝突判定を行う際に、
	 *	処理を高速に行うための簡易的な形状を指します。
	 *	モデル同士の干渉・衝突判定は、
	 *	実際にはこの境界ボリューム同士の干渉状態や衝突を検出することになります。
	 *	干渉判定と衝突判定に関する詳細は fk_Model の概要を参照して下さい。
	 *
	 *	境界ボリュームには、現在は以下の4種類が提供されています。
	 *
	 *	- 境界球 \n
	 *		球形状による境界ボリュームです。
	 *		処理は最も高速ですが、本来の形状との誤差が大きくなることがあります。
	 *		現状では、衝突判定を行いたい場合はこの境界球を用いる必要があります。
	 *	- 軸平行境界ボックス (Axis Aligned Bounding Box, AABB) \n
	 *		直方体による境界ボリュームですが、
	 *		常に各面が座標軸と垂直であるという特性を持ちます。
	 *		境界球と比較すると元形状にフィッティングしやすく、
	 *		判定処理も OBB やカプセル型と比較して高速であるという特性を持ちます。
	 *		その反面、モデルが回転した場合に新たに大きさを再設定する必要があることや、
	 *		回転によって大きさが変化することなどから、
	 *		モデルが回転する場合には扱いづらい面があります。
	 *		モデルが方向ベクトルを変化させずに移動するような場合に適しています。
	 *	- 有向境界ボックス (Oriented Bounding Box, OBB) \n
	 *		AABB と同じく直方体による境界ボリュームですが、
	 *		こちらはモデルの回転に伴ってボックスの向きも追従します。
	 *		境界ボリュームの挙動が想定しやすく扱いやすい特性を持ちますが、
	 *		判定処理は全ての境界ボリューム中もっとも重く、
	 *		多くのモデルがある状態で多用するとかなり全体の処理が重くなる可能性があります。
	 *	- カプセル型 \n
	 *		境界が円柱側面と半球によって構成されている境界ボリュームです。
	 *		数学的には、線分から一定距離以内にある点の集合となります。
	 *		この線分を本マニュアルでは「中心軸」と呼称します。
	 *		中心軸両端点を設定することがやや面倒ですが、
	 *		長細いモデルにもフィットしやすく、判定処理も OBB より高速なので、
	 *		使い勝手のよい境界ボリュームです。
	 *
	 *	\sa fk_Model
	 */
	public ref class fk_Boundary : fk_MatrixAdmin {
	internal:
		::fk_Boundary * GetP(void);

	public:
		//! コンストラクタ
		fk_Boundary(bool);

		//! デストラクタ
		~fk_Boundary();

		//! ファイナライザ
		!fk_Boundary();
		
		//! 境界ボリューム選択プロパティ
		/*!
		 *	このプロパティは、
		 *	干渉判定にどの境界ボリュームを利用するかを指定、参照するものです。
		 *	本プロパティの設定は各境界ボリュームの設定とは独立しており、
		 *	プロパティ設定によってモードを変更しても、
		 *	各境界ボリュームの大きさ等の設定は初期化されません。
		 *
		 *	\note
		 *		本プロパティで選択が有効となるのは、現バージョンでは干渉判定のみです。
		 *		衝突判定については、本プロパティでの設定に関わらず境界球の設定が用いられます。
		 *
		 *	\sa fk_Model::IsInter()
		 */
		property fk_BoundaryMode BMode {
			fk_BoundaryMode get();
			void set(fk_BoundaryMode argMode);
		}			   

		//! 境界球半径プロパティ
		/*!
		 *	境界球半径の設定・参照を行います。
		 *	現在モデルに設定されている形状から、
		 *	自動的に境界球半径を設定したい場合は fk_Model::AdjustSphere() を用いて下さい。
		 *
		 *	\sa BMode, fk_Model::AdjustSphere()
		 */
		property double SphereRadius {
			double get();
			void set(double argRad);
		}			

		//! 軸平行境界ボックス (AABB) サイズプロパティ
		/*!
		 *	軸平行境界ボックス (AABB) のサイズを設定・参照します。
		 *	サイズの各成分はグローバル座標系に対応します。
		 *	自動的に AABB のサイズを設定したい場合は fk_Model::AdjustAABB() を用いて下さい。
		 *
		 *	\param[in]	size	AABBのサイズ
		 *
		 *	\sa BMode, fk_Model::AdjustAABB(), fk_Vector
		 */
		property fk_Vector^ AABB {
			fk_Vector^ get();
			void set(fk_Vector^ argSize);
		}

		//! 有向境界ボックス (OBB) サイズプロパティ
		/*!
		 *	有向境界ボックス (OBB) のサイズを設定・参照します。
		 *	サイズの各成分はモデルのローカル座標系に対応します。
		 *	自動的に OBB のサイズを設定したい場合は fk_Model::AdjustOBB() を用いて下さい。
		 *
		 *	\sa BMode, fk_Model::AdjustOBB(), fk_Vector
		 */
		property fk_Vector^ OBB {
			fk_Vector^ get();
			void set(fk_Vector^ argSize);
		}

		//! 境界ボリューム描画有無プロパティ
		/*!
		 *	境界ボリュームに対し、描画の有無を設定・参照します。
		 *
		 *	\sa BLineColor, BIntLineColor, BLineWidth
		 */
		property bool BDraw {
			bool get();
			void set(bool argMode);
		}

		//! 境界ボリューム非干渉描画色プロパティ
		/*!
		 *	境界ボリューム描画の際に、
		 *	非干渉状態である場合での線色の設定・参照を行います。
		 *
		 *	\sa	BIntLineColor, BDraw, fk_Model::IsInter(), fk_Model::InterMode, fk_Color
		 */
		property fk_Color^ BLineColor {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		//! 境界ボリューム干渉状態描画色プロパティ
		/*!
		 *	境界ボリューム描画の際に、
		 *	干渉状態である場合での線色の設定・参照を行います。
		 *
		 *	\note
		 *		この線色で描画される条件は、
		 *		fk_Model::InterMode による設定によって異なります。
		 *
		 *	\sa	BLineColor, BDraw, fk_Model::IsInter(), fk_Model::InterMode, fk_Color
		 */
		property fk_Color^ BIntLineColor {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		//!	境界ボリューム描画線幅プロパティ
		/*!
		 *	境界ボリューム描画の際での、線幅の設定・参照を行います。
		 *
		 *	\sa BDraw, BLineColor, BIntLineColor
		 */
		property double BLineWidth {
			double get();
			void set(double argW);
		}
		
		//! \name カプセル型制御関数
		//@{

		//! カプセル型設定関数
		/*!
		 *	カプセル型は、数学的には線分(中心軸)からある一定距離以内にある領域となります。
		 *	この関数は、中心軸の両端点と距離を設定することでカプセル型を規定するものです。
		 *	中心軸端点の位置ベクトルは、モデルのローカル座標系に対応します。
		 *	自動的にカプセル型のサイズを設定したい場合は fk_Model::AdjustCapsule() を用いて下さい。
		 *
		 *	\param[in]	startPos	中心軸端点(始点側)の位置ベクトル
		 *	\param[in]	endPos		中心軸端点(終点側)の位置ベクトル
		 *	\param[in]	radius		中心軸からの領域規定距離
		 *
		 *	\sa	GetCapsuleRadius(), GetCapsuleLength(), GetCapsuleStartPos(), GetCapsuleEndPos(),
		 *		BMode, fk_Model::AdjustCapsule()
		 */
		void SetCapsule(fk_Vector^ startPos, fk_Vector^ endPos, double radius);

		//! カプセル型領域規定距離取得関数
		/*!
		 *	現在設定されているカプセル型の領域規定距離を取得します。
		 *
		 *	\return		カプセル型の領域規定距離
		 *
		 *	\sa	SetCapsule(), fk_Model::AdjustCapsule()
		 */
		double GetCapsuleRadius(void);

		//! カプセル型中心軸長取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の長さを取得します。
		 *
		 *	\return		カプセル型の中心軸の長さ
		 *
		 *	\sa	SetCapsule(), fk_Model::AdjustCapsule()
		 */
		double GetCapsuleLength(void);

		//! カプセル型中心軸始点取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の始点位置ベクトルを取得します。
		 *
		 *	\return		カプセル型の中心軸の始点位置ベクトル
		 *
		 *	\sa	SetCapsule(), fk_Model::AdjustCapsule()
		 */
		fk_Vector^ GetCapsuleStartPos(void);

		//! カプセル型中心軸終点取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の終点位置ベクトルを取得します。
		 *
		 *	\return		カプセル型の中心軸の終点位置ベクトル
		 *
		 *	\sa	SetCapsule(), fk_Model::AdjustCapsule()
		 */
		fk_Vector^ GetCapsuleEndPos(void);
		//@}
	};
}
