// DList_CLI.h

#pragma once

#include <FK/DList.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Projection_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	//! 立体視出力を制御する際に用いる列挙型
	public enum class fk_StereoChannel {
		STEREO_LEFT,		//!< 右目側
		STEREO_RIGHT		//!< 左目側
	};

	//!	ディスプレイリストを制御するクラス
	/*!
	 *	このクラスは、ディスプレイリストを制御する機能を提供します。
	 *	ディスプレイリストとは、シーン中に表示するためのモデルを管理する仕組みです。
	 *	実際の利用時には、インスタンスは本クラスのものではなく
	 *	派生クラスの fk_Scene によるものを利用することになります。
	 *
	 *	ディスプレイリストに登録する要素は、以下のようなものがあります。
	 *		- 通常モデル:
	 *			3次元空間に表示するためのモデルです。
	 *		- オーバーレイモデル:
	 *			オーバーレイモデルとして登録したモデルは、
	 *			カメラからの前後に関係なく常に全体が表示されます。
	 *			オーバーレイモデルが複数登録されている場合は、
	 *			後に登録されたものほど前面に表示されます。
	 *		- カメラ:
	 *			シーンのカメラに当たるモデルです。
	 *			同時に登録できるモデルは1つだけですが、
	 *			どの時点でもモデルを変更することができます。
	 *		- 投影設定:
	 *			シーンを表示する際の投影設定です。
	 *			詳細は fk_Perspective, fk_Frustum, fk_Ortho の
	 *			各マニュアルを参照して下さい。
	 *
	 *	\sa fk_Scene, fk_Fog, fk_Model, fk_Perspective, , fk_Frustum, fk_Ortho
	 */
	public ref class fk_DisplayLink : fk_BaseObject {
	internal:
		List<fk_Model^>^ modelList;
		List<fk_Model^>^ overlayList;
		fk_Model^ _camera;
		fk_Model^ _lCamera;
		fk_Model^ _rCamera;
		fk_ProjectBase^ _proj;
		fk_ProjectBase^ _lProj;
		fk_ProjectBase^ _rProj;

		::fk_DisplayLink * GetP(void);
		void CameraUpdate(void);
		::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_DisplayLink(bool argNewFlg);
		~fk_DisplayLink();
		!fk_DisplayLink();
#endif

		//! カメラモデルプロパティ
		/*!
		 *	ディスプレイリストでのカメラモデルの設定・参照を行います。
		 *
		 *	\sa fk_Model
		 */
		property fk_Model^ Camera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}			

		//! 立体視用左眼カメラプロパティ
		/*!
		 *	立体視における左眼を表すカメラモデルの設定・参照を行います。
		 *
		 *	\sa fk_Model
		 */
		property fk_Model^ LeftCamera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}

		//! 立体視用右眼カメラプロパティ
		/*!
		 *	立体視における右眼を表すカメラモデルの設定・参照を行います。
		 *
		 *	\sa fk_Model
		 */
		property fk_Model^ RightCamera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}
		
		//! 投影設定プロパティ
		/*!
		 *	シーンにおける投影状態の設定・参照を行います。
		 *
		 *	\sa fk_Perspective, fk_Ortho, fk_Frustum
		 */
		property fk_ProjectBase^ Projection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}			

		//! 立体視用左眼投影プロパティ
		/*!
		 *	立体視における、左眼を表すカメラ投影状態の設定・参照を行います。
		 *
		 *	\sa fk_Perspective, fk_Ortho, fk_Frustum
		 */
		property fk_ProjectBase^ LeftProjection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}
		
		//! 立体視用右眼投影プロパティ
		/*!
		 *	立体視における、右眼を表すカメラ投影状態の設定・参照を行います。
		 *
		 *	\sa fk_Perspective, fk_Ortho, fk_Frustum
		 */
		property fk_ProjectBase^ RightProjection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}

		//! 立体視モード時のオーバーレイ描画モードプロパティ
		/*!
		 *	立体視モード時のオーバーレイ描画モデルに対する動作の設定・参照を行います。
		 *	一般的なゲームアプリケーションでは、3DCG をレンダリングした画面上に
		 *	2D の画像や文字などを情報として表示(いわゆる HUD 表示)しますが、
		 *	立体視を有効にした場合はそれらの表示にも視差が適用されます。
		 *	この動作は状況によっては望ましくない場合もあります。
		 *	このプロパティによって、オーバーレイ描画を行うモデルに対して視差を適用するか、
		 *	しないかを選択することができます。
		 *	HUD 表示はオーバーレイ描画によって実現することが多いため、
		 *	多くの場合はこのプロパティによる設定で十分制御が可能となるはずです。
		 *	デフォルトではオーバーレイ描画モデルにも視差を適用する設定(true)になっています。
		 *	true だった場合、オーバーレイ描画モデルの視差を有効にします。
		 *	false だった場合、オーバーレイ描画モデルの視差を無効にします。
		 */
		property bool StereoOverlayMode {
			bool get();
			void set(bool argMode);
		}
		
		//!	初期化関数
		/*!
		 *	ディスプレイリストに登録されていた全ての情報を解除します。
		 *	解除する対象は通常表示モデル、モデルオーバーレイモデル、
		 *	カメラ、投影設定です。
		 */
		void ClearDisplay(void);

		//! 立体視用設定情報初期化関数
		/*!
		 *	立体視モードで使用する設定情報を初期化します。
		 */
		void ClearStereo(void);

		//! 通常モデル登録関数
		/*!
		 *	通常モデルをディスプレイリストに登録します。
		 *
		 *	\param[in] model	登録モデルのアドレス
		 */
		void EntryModel(fk_Model ^model);

		//! 通常モデル解除関数
		/*!
		 *	ディスプレイリストに登録されている通常モデルに対し、
		 *	登録を解除します。
		 *	もし登録されていないモデルが指定された場合は、
		 *	特に何も起こりません。
		 *
		 *	\param[in] model	解除モデルのアドレス
		 */
		void RemoveModel(fk_Model ^model);

		//! 通常モデル全解除関数
		/*!
		 *	ディスプレイリストに登録されている全ての通常モデルに対し、
		 *	登録を解除します。
		 */
		void ClearModel(void);

		//! オーバーレイモデル登録関数
		/*!
		 *	オーバーレイモデルをディスプレイリストに登録します。
		 *	オーバーレイモデルは、後に登録したものほど前面に表示されるようになります。
		 *	もし既に登録されているモデルを再度登録した場合は、
		 *	一度解除したのちに改めて登録しなおすことと同義となります。
		 *
		 *	\param[in] model	登録モデルのアドレス
		 */
		void EntryOverlayModel(fk_Model ^model);


		//! オーバーレイモデル解除関数
		/*!
		 *	ディスプレイリストに登録されているオーバーレイモデルに対し、
		 *	登録を解除します。
		 *	もし登録されていないモデルが指定された場合は、
		 *	特に何も起こりません。
		 *
		 *	\param[in] model	解除モデルのアドレス
		 */
		void RemoveOverlayModel(fk_Model^ model);

		//! オーバーレイモデル全解除関数
		/*!
		 *	ディスプレイリストに登録されている全てのオーバーレイモデルに対し、
		 *	登録を解除します。
		 */
		void ClearOverlayModel(void);
	};
}
