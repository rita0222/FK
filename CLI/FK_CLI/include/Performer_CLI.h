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
// Performer_CLI.h

#pragma once

#include <FK/MotionCharactor.h>
#include "Scene_CLI.h"


namespace FK_CLI
{
	//! FK Performer キャラクターランタイムクラス
	/*!
	 *	このクラスは、FK Performer で作成したキャラクターやオブジェクトの表示、
	 *	モーション再生などを行う機能を提供します。
	 *
	 *	FK Performer は、メタセコイアで作成した MQO 形式の形状モデルを読み込み、
	 *	キーフレームアニメーションを作成することができるツールです。
	 *	ツールやデータの仕様に関する詳細は、次の URL を参照してください。
	 *	http://gamescience.jp/~rita/FKP/
	 *
	 *	本クラスにおいて、各関節は階層構造的に接続されることになり、
	 *	内部的にはそれぞれに対応する fk_Model 型のインスタンスを保持します。
	 *	最も上位となるモデルは GetBaseModel() によって得られるインスタンスです。
	 *	その一つ下位に \<base\> というモデルがあり、
	 *	全ての関節モデルはこの \<base\> の子モデル、あるいはそれらの子孫のモデルとなります。
	 *	FK における親子関係の詳細は fk_Model のマニュアルを参照して下さい。
	 *
	 *	本クラスでの「モーション」とは、実際には各オブジェクトモデルの移動動作を指します。
	 *	各モーションは経過時間ごとの配置状況が記録されており、
	 *	この経過時間を「フレーム」と呼びます。
	 *	さらに、フレームを1つずつ進めていくことを「再生」と呼びます。
	 *	この「再生」を画面更新と一緒に行っていくことによって、
	 *	FK Performer で作成した動作アニメーションを FK 内で実行することが可能となります。

	 *	FK Performer では、一つのモーションデータに複数のモーションを格納することが可能です。
	 *	各モーションには「モーション番号」という ID が割り振られ、最初のものが 0 となります。
	 *	先述した再生フレームは、各モーションごとに個別に管理されます。
	 *
	 *	\sa fk_Model, fk_Scene, fk_AppWindow
	 */
	public ref class fk_Performer {
	internal:
		::FK::fk_Performer *pMotion;
		bool dFlg;
		fk_Model^ baseModel;

		::FK::fk_Performer * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Performer(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_Performer();

		//! デストラクタ
		~fk_Performer();

		//! ファイナライザ
		!fk_Performer();

		//! オブジェクト数プロパティ
		/*!
		 *	そのキャラクターのオブジェクト数(関節数)を参照します。
		 *	\<base\> の分も含みます。
		 */
		property int ObjectNum {
			int get();
		}

		//! ループ回数プロパティ
		/*!
		 *	現在再生しているモーションが、何回ループしているかを返します。
		 */
		property int LoopCount {
			int get();
		}

		//! シーン登録プロパティ
		/*!
		 *	キャラクターをシーンに設定します。
		 *	既にシーンに登録されていた場合は変化はありません。
		 *	解除する場合は RemoveScene() を利用して下さい。
		 */
		property fk_Scene^ Scene {
			void set(fk_Scene^);
		}
		
		//! キャラクタークローンメソッド
		/*!
		 *	異なるインスタンス間に、キャラクターのデータをクローンします。
		 *
		 *	\param[in]	perf		コピー元インスタンス
		 *
		 *	\return
		 *		クローン成功時に true を、失敗時に false を返します。
		 */
		bool CloneCharactor(fk_Performer^ perf);

		//! \name データ入力メソッド
		//@{

		//! MQO オブジェクト読み込みメソッド
		/*!
		 *	メタセコイアの形状モデル(MQOデータ)を読み込みます。
		 *
		 *	\param[in]	filename	形状モデルファイル名。
		 *
		 *	\return
		 *		成功時に true、失敗時に false を返します。
		 */
		bool LoadObjectData(String^ filename);

		//! FKC ジョイント読み込みメソッド
		/*!
		 *	FK Performer による関節セットアップデータ(FKCデータ)を読み込みます。
		 *
		 *	\param[in]	filename	間接セットアップデータファイル名。
		 *
		 *	\return
		 *		成功時に true、失敗時に false を返します。
		 */
		bool LoadJointData(String^ filename);

		//! FKM モーション読み込みメソッド
		/*!
		 *	FK Performer によるモーションデータ(FKMデータ)を読み込みます。
		 *	複数のモーションを読み込みたい場合は、1つずつ順番に読み込みます。
		 *	読み込んだモーションには、最初に読み込んだものを
		 *	0 番とし、読み込む順番で 1 ずつ追加した ID が割り振られます。
		 *
		 *	\param[in]	filename	モーションデータファイル名。
		 *
		 *	\return
		 *		成功時に true、失敗時に false を返します。
		 */
		bool LoadMotionData(String^ filename);

		//@}

		//! \name シーン登録制御メソッド
		//@{

		//! シーン登録解除メソッド
		/*!
		 *	キャラクターのシーン登録を解除します。
		 *	シーンに登録されていなかった場合は変化はありません。
		 *	シーンへの登録は fk_Performer::Scene プロパティを利用して下さい。
		 *
		 *	\param[in]	scene	登録解除するシーン
		 *
		 *	\sa fk_Performer::Scene
		 */
		void RemoveScene(fk_Scene^ scene);

		//@}

		//! \name 各種オブジェクト取得メソッド
		//@{

		//! ベースモデル取得メソッド
		/*!
		 *	そのキャラクターの全体的な位置・姿勢を制御するモデルのインスタンスを取得します。
		 *	この GetBaseModel() で制御できるのは、FK Performer 中での \<base\> ではなく、
		 *	\<base\> を子とした更に上位の親モデルです。あえて二重構造にしてあります。
		 *	\<base\> を直接制御したい場合は GetJointModel()
		 *	メソッドで引数に 0 を代入して使ってください。
		 *
		 *	\return
		 *		ベースモデルインスタンス。
		 *
		 *	\sa GetObjectModel(), GetJointModel()
		 */
		fk_Model^ GetBaseModel(void);

		//! オブジェクトモデル取得メソッド
		/*!
		 *	引数で指定した関節番号の fk_Model のインスタンスを返します。
		 *	オブジェクトモデルとは、実際に表示する形状がセットされているインスタンスを指します。
		 *	関節番号の順番は、Performer で読み込んだ時にリストに表示される順です。
		 *	0 が \<base\> に対応し、以降順番通りに 1,2,3... と割り振られます。
		 *	関節ごとの位置や姿勢を知りたいときに使えます。
		 *
		 *	\param[in]	id		関節番号
		 *
		 *	\return
		 *		関節番号に対応するオブジェクトモデルインスタンス。
		 *		無効な関節番号を指定した場合は null が返ります。
		 *
		 *	\sa GetBaseModel(), GetJointModel()
		 */
		fk_Model^ GetObjectModel(int id);

		//! ジョイントモデル取得メソッド
		/*!
		 *	引数で指定した関節番号の fk_Model のインスタンスを返します。
		 *	ジョイントモデルとは、オブジェクトモデルをレイアウトするために利用している
		 *	形状を持たないインスタンスを指します。通常の場合は利用しませんが、
		 *	親子関係を辿ったり、座標系を可視化したりといった用途に用いると便利です。
		 *	関節番号の順番は、Performer で読み込んだ時にリストに表示される順です。
		 *	0 が \<base\> に対応し、以降順番通りに 1,2,3... と割り振られます。
		 *	関節ごとの位置や姿勢を知りたいときに使えます。
		 *
		 *	\param[in]	id		関節番号
		 *
		 *	\return
		 *		関節番号に対応するジョイントモデルインスタンス。
		 *		無効な関節番号を指定した場合は null が返ります。
		 *
		 *	\sa GetBaseModel(), GetObjectModel()
		 */
		fk_Model^ GetJointModel(int id);
		//@}

		//! \name モーション再生制御メソッド
		//@{

		//! モーション再生位置取得メソッド
		/*!
		 *	引数で指定したモーション番号が、現在何フレーム目まで進んでいるかを返します。
		 *
		 *	\param[in]	id	モーション番号
		 *
		 *	\return
		 *		現在のフレーム番号。
		 *		無効なモーション番号を指定した場合は -1 が返ります。
		 */
		int GetNowFrame(int id);

		//! モーションのトータルフレーム数取得メソッド
		/*!
		 *	引数で指定したモーション番号のトータルフレーム数を返します。
		 *
		 *	\param[in]	id	モーション番号
		 *
		 *	\return
		 *		指定したモーションの総フレーム数。
		 *		無効なモーション番号を指定した場合は -1 が返ります。
		 */
		int GetTotalFrame(int id);
	
		//! モーション再生メソッド
		/*!
		 *	引数で指定したモーション番号に対応するモーションの再生を行います。
		 *	終端まで到達した場合は、次の呼び出し時には自動的に先頭に巻き戻って再生します。
		 *
		 *	\param[in]	id	モーション番号
		 *
		 *	\return
		 *		正常に再生がおこなれた場合は true を返します。
		 *		モーションが読み込まれていない時に再生しようとした場合 false を返します。
		 *		無効なモーション番号を指定した場合も false を返します。
		 */
		bool PlayMotion(int id);

		//! 姿勢制御付きフレーム頭出しメソッド
		/*!
		 *	指定したモーションの、指定したフレームの姿勢を強制的に取らせます。
		 *	今再生しているモーションを強制的に巻き戻す場合などに便利です。
		 *	無効なモーション番号、及びフレーム数を指定した場合は何もしません。
		 *
		 *	\param[in]	motionID	モーション番号
		 *	\param[in]	frameID		フレーム番号
		 */
		void StillMotion(int motionID, int frameID);

		//! 姿勢制御無しフレーム頭出しメソッド
		/*!
		 *	指定したモーションの再生位置を、指定したフレームにセットしますが、
		 *	実際にはその姿勢は取らせません。裏でこっそり巻き戻しておく場合に使えます。
		 *	無効なモーション番号、及びフレーム数を指定した場合は何もしません。
		 *
		 *	\param[in]	motionID	モーション番号
		 *	\param[in]	frameID		フレーム番号
		 */
		void SetNowFrame(int motionID, int frameID);

		//! モーション再生終了状態取得メソッド
		/*!
		 *	指定したモーション番号が、終端まで到達しているかどうかをチェックします。
		 *
		 *	\param[in]	id		モーション番号
		 *
		 *	\return
		 *		終端に到達していたら true、していなかったら false が返ります。
		 */
		bool IsMotionFinished(int id);
		//@}
	};
}


