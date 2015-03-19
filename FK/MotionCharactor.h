/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_MOTIONCHARACTOR_HEADER__
#define __FK_MOTIONCHARACTOR_HEADER__

#include <FK/Shape.h>
#include <FK/IFSTexture.h>
#include <FK/Scene.h>
#include <FK/MotionData.H>
#include <map>
#include <deque>

//! FK Performer キャラクターランタイムクラス
/*!
 *	このクラスは、FK Performer で作成したキャラクターやオブジェクトの表示、
 *	モーション再生などを行う機能を提供します。
 *
 *	FK Performer は、メタセコイアで作成した MQO 形式の形状モデルを読み込み、
 *	キーフレームアニメーションを作成することができるツールです。
 *	ツールやデータの仕様に関する詳細は、次の URL を参照してください。
 *	http://www2.teu.ac.jp/aqua/~rita/FKP/
 *
 *	本クラスにおいて、各関節は階層構造的に接続されることになり、
 *	内部的にはそれぞれに対応する fk_Model 型のインスタンスを保持します。
 *	最も上位となるモデルは getBaseModel() によって得られるインスタンスです。
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

class fk_Performer {
private:
	std::vector<fk_Model *>			jointModel;
	std::vector<fk_Shape *>			mesh;
	std::vector<fk_Model *>			objModel;

	std::vector<fk_Material>		matPalette;
	std::vector<int>				matTable;
	std::vector<fk_Image *>			texImage;
	std::vector<std::string>		texName;
	std::vector<int>				texTable;

	std::string						mqoName;
	int								objNum;
	std::vector<std::string>		objName;
	std::map<int, int>				parentTable;
	bool							parentConnect;

	std::vector<std::vector<fk_PerformerMotion> >	keyFrameData;
	std::vector<int>								nowFrame, maxFrame;

	std::deque<bool>	visibleInfo;
	fk_DrawMode			draw_mode;

	int			prevPlayMotionID, loopCnt;

	fk_Model	absParent;

	void init(void);
	bool EnumObjectName(const std::string &);

	// オイラー角版
	bool LoadMotionDataEuler(const std::string &);
	// スケール対応版
	bool LoadMotionDataEulerScale(const std::string &);

	static std::map<std::string, fk_Shape *>		shapeCache;
	static std::map<std::string, fk_Image *>		imageCache;
	static std::map<fk_BaseObject *, int>			countCache;
	static std::map<fk_BaseObject *, std::string>	reverseCache;

public:
	//! コンストラクタ
	fk_Performer(void);
	//! デストラクタ
	~fk_Performer(void);

	//! キャラクタークローン関数
	/*!
	 *	異なるインスタンス間に、キャラクターのデータをクローンします。
	 *
	 *	\param[in]	perf		コピー元インスタンスのポインタ。
	 *
	 *	\return
	 *		クローン成功時に true を、失敗時に false を返します。
	 */
	bool cloneCharactor(fk_Performer *perf);

	//! \name データ入力関数
	//@{

	//! MQO オブジェクト読み込み関数
	/*!
	 *	メタセコイアの形状モデル(MQOデータ)を読み込みます。
	 *
	 *	\param[in]	filename	形状モデルファイル名。
	 *
	 *	\return
	 *		成功時に true、失敗時に false を返します。
	 */
	bool loadObjectData(const std::string &filename);

	//! FKC ジョイント読み込み関数
	/*!
	 *	FK Performer による関節セットアップデータ(FKCデータ)を読み込みます。
	 *
	 *	\param[in]	filename	間接セットアップデータファイル名。
	 *
	 *	\return
	 *		成功時に true、失敗時に false を返します。
	 */
	bool loadJointData(const std::string &filename);

	//! FKM モーション読み込み関数
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
	bool loadMotionData(const std::string &filename);

	//@}

	//! \name シーン登録制御関数
	//@{

	//! シーン登録関数
	/*!
	 *	キャラクターをシーンに登録します。
	 *	既にシーンに登録されていた場合は変化はありません。
	 *
	 *	\param[in]	scene	登録するシーンのポインタ。
	 *
	 *	\sa removeScene()
	 */
	void entryScene(fk_Scene *scene);

	//! シーン登録解除関数
	/*!
	 *	キャラクターのシーン登録を解除します。
	 *	シーンに登録されていなかった場合は変化はありません。
	 *
	 *	\param[in]	scene	登録解除するシーンのポインタ。
	 *
	 *	\sa entryScene()
	 */
	void removeScene(fk_Scene *scene);

	//@}

	//! \name 各種オブジェクト取得関数
	//@{

	//! オブジェクト数取得関数
	/*!
	 *	そのキャラクターのオブジェクト数(関節数)を返します。\<base\> の分も含みます。
	 *
	 *	\return		オブジェクト数(関節数)
	 */
	int getObjectNum(void);

	//! ベースモデル取得関数
	/*!
	 *	そのキャラクターの全体的な位置・姿勢を制御するモデルのインスタンスを取得します。
	 *	この getBaseModel() で制御できるのは、FK Performer 中での \<base\> ではなく、
	 *	\<base\> を子とした更に上位の親モデルです。あえて二重構造にしてあります。
	 *	\<base\> を直接制御したい場合は getJointModel()
	 *	関数で引数に 0 を代入して使ってください。
	 *
	 *	\return
	 *		ベースモデルインスタンスのポインタ
	 *
	 *	\sa getObjectModel(), getJointModel()
	 */
	fk_Model * getBaseModel(void);

	//! オブジェクトモデル取得関数
	/*!
	 *	引数で指定した関節番号の fk_Model へポインタを返します。
	 *	オブジェクトモデルとは、実際に表示する形状がセットされているインスタンスを指します。
	 *	関節番号の順番は、Performer で読み込んだ時にリストに表示される順です。
	 *	0 が \<base\> に対応し、以降順番通りに 1,2,3... と割り振られます。
	 *	関節ごとの位置や姿勢を知りたいときに使えます。
	 *
	 *	\param[in]	id		関節番号
	 *
	 *	\return
	 *		関節番号に対応するオブジェクトモデルインスタンスのポインタ。
	 *		無効な関節番号を指定した場合は nullptr が返ります。
	 *
	 *	\sa getBaseModel(), getJointModel()
	 */
	fk_Model * getObjectModel(int id);

	//! ジョイントモデル取得関数
	/*!
	 *	引数で指定した関節番号の fk_Model へポインタを返します。
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
	 *		関節番号に対応するジョイントモデルインスタンスのポインタ。
	 *		無効な関節番号を指定した場合は nullptr が返ります。
	 *
	 *	\sa getBaseModel(), getObjectModel()
	 */
	fk_Model * getJointModel(int id);

	//@}

	//! \name モーション再生制御関数
	//@{

	//! モーション再生位置取得関数
	/*!
	 *	引数で指定したモーション番号が、現在何フレーム目まで進んでいるかを返します。
	 *
	 *	\param[in]	id	モーション番号
	 *
	 *	\return
	 *		現在のフレーム番号。
	 *		無効なモーション番号を指定した場合は -1 が返ります。
	 */
	int getNowFrame(int id);

	//! モーションのトータルフレーム数取得関数
	/*!
	 *	引数で指定したモーション番号のトータルフレーム数を返します。
	 *
	 *	\param[in]	id	モーション番号
	 *
	 *	\return
	 *		指定したモーションの総フレーム数。
	 *		無効なモーション番号を指定した場合は -1 が返ります。
	 */
	int getTotalFrame(int id);

	//! モーション再生関数
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
	bool playMotion(int id);

	//! 姿勢制御付きフレーム頭出し関数
	/*!
	 *	指定したモーションの、指定したフレームの姿勢を強制的に取らせます。
	 *	今再生しているモーションを強制的に巻き戻す場合などに便利です。
	 *	無効なモーション番号、及びフレーム数を指定した場合は何もしません。
	 *
	 *	\param[in]	motionID	モーション番号
	 *	\param[in]	frameID		フレーム番号
	 */
	void stillMotion(int motionID, int frameID);

	//! 姿勢制御無しフレーム頭出し関数
	/*!
	 *	指定したモーションの再生位置を、指定したフレームにセットしますが、
	 *	実際にはその姿勢は取らせません。裏でこっそり巻き戻しておく場合に使えます。
	 *	無効なモーション番号、及びフレーム数を指定した場合は何もしません。
	 *
	 *	\param[in]	motionID	モーション番号
	 *	\param[in]	frameID		フレーム番号
	 */
	void setNowFrame(int motionID, int frameID);

	//! モーション再生終了状態取得関数
	/*!
	 *	指定したモーション番号が、終端まで到達しているかどうかをチェックします。
	 *
	 *	\param[in]	id		モーション番号
	 *
	 *	\return
	 *		終端に到達していたら true、していなかったら false が返ります。
	 */
	bool isMotionFinished(int id);

	//! モーションのループ回数取得関数
	/*!
	 *	現在再生しているモーションが、何回ループしているかを返します。
	 *
	 *	\return
	 *		ループ回数
	 */
	int getLoopCount(void);

	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	void jointToPoser(void);
	void setAsCamera(fk_Scene *);
	void setDrawMode(bool);
	void setMarkerShape(fk_Shape *);

	void SetFinalizeMode(void);
#endif
};

typedef fk_Performer fkut_Performer;

#endif //!__FK_MOTIONCHARACTOR_HEADER__
