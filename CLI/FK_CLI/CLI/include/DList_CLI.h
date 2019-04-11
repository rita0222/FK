/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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

		::FK::fk_DisplayLink * GetP(void);
		void CameraUpdate(void);
		::FK::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_DisplayLink(bool argNewFlg);
		~fk_DisplayLink();
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
		
		//!	初期化メソッド
		/*!
		 *	ディスプレイリストに登録されていた全ての情報を解除します。
		 *	解除する対象は通常表示モデル、モデルオーバーレイモデル、
		 *	カメラ、投影設定です。
		 */
		void ClearDisplay(void);

		//! 立体視用設定情報初期化メソッド
		/*!
		 *	立体視モードで使用する設定情報を初期化します。
		 */
		void ClearStereo(void);

		//! 通常モデル登録メソッド
		/*!
		 *	通常モデルをディスプレイリストに登録します。
		 *
		 *	\param[in] model	登録モデルのアドレス
		 */
		void EntryModel(fk_Model ^model);

		//! 通常モデル解除メソッド
		/*!
		 *	ディスプレイリストに登録されている通常モデルに対し、
		 *	登録を解除します。
		 *	もし登録されていないモデルが指定された場合は、
		 *	特に何も起こりません。
		 *
		 *	\param[in] model	解除モデルのアドレス
		 */
		void RemoveModel(fk_Model ^model);

		//! 通常モデル全解除メソッド
		/*!
		 *	ディスプレイリストに登録されている全ての通常モデルに対し、
		 *	登録を解除します。
		 */
		void ClearModel(void);

		//! オーバーレイモデル登録メソッド
		/*!
		 *	オーバーレイモデルをディスプレイリストに登録します。
		 *	オーバーレイモデルは、後に登録したものほど前面に表示されるようになります。
		 *	もし既に登録されているモデルを再度登録した場合は、
		 *	一度解除したのちに改めて登録しなおすことと同義となります。
		 *
		 *	\param[in] model	登録モデルのアドレス
		 */
		void EntryOverlayModel(fk_Model ^model);


		//! オーバーレイモデル解除メソッド
		/*!
		 *	ディスプレイリストに登録されているオーバーレイモデルに対し、
		 *	登録を解除します。
		 *	もし登録されていないモデルが指定された場合は、
		 *	特に何も起こりません。
		 *
		 *	\param[in] model	解除モデルのアドレス
		 */
		void RemoveOverlayModel(fk_Model^ model);

		//! オーバーレイモデル全解除メソッド
		/*!
		 *	ディスプレイリストに登録されている全てのオーバーレイモデルに対し、
		 *	登録を解除します。
		 */
		void ClearOverlayModel(void);
	};
}


