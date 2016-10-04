#ifndef __FK_AUDIO_HEADER__
#define __FK_AUDIO_HEADER__

#ifndef OV_EXCLUDE_STATIC_CALLBACKS
#define OV_EXCLUDE_STATIC_CALLBACKS
#endif

#include <string>
#include <vector>

#include <FK/IDAdmin.H>
#include <FK/Vector.h>


const unsigned int FK_OV_BUFSIZE = 4096;
const unsigned int FK_OV_DEFAULT_QUEUE_SIZE = 64;

class fk_Model;
struct OggVorbis_File;

//! オーディオ基底クラス
/*!
 *	このクラスは、FKが提供するオーディオクラスの基底クラスとなっています。
 *	オーディオ全般で共通して利用するメンバ関数を実装しています。
 *	FKでは、オーディオシステムとして OpenAL を採用しています。
 *	Windows プラットフォームでこのクラスの派生クラスを利用する場合は、
 *	事前に OpenAL をインストールしておく必要があります。
 *	(Mac は OpenAL が標準で搭載されているため、事前準備は必要ありません。)
 *
 *	このクラスの派生クラスによるインスタンスは、
 *	音声再生を制御するための基本的な機能となる再生、
 *	停止、繰り返し再生、音量調整を制御できます。
 *
 *	加えて、サラウンド(立体音響)を利用することもできます。
 *	サラウンド機能においては、
 *	各音源自体の3次元空間での位置を fk_Model と同期を取ることで実現します。
 *	そのため、FK の 3D プログラムと高い親和性を持ちます。
 *	また、3Dグラフィックスにおける「カメラ」に相当するような、
 *	自分自身を指す言葉を「リスナー」と呼びます。
 *	リスナーも fk_Model と同期を取ることができます。
 *
 *	\sa fk_AudioStream, fk_AudioOggBuffer, fk_AudioWavBuffer, fk_Model
 */

class fk_AudioBase {
 private:

 protected:

#ifndef FK_DOXYGEN_USER_PROCESS

	double				refDist;
	fk_Vector			sourcePos;
	double				gain;
	static fk_Model		*listenerCamera;

	bool			startStatus, endStatus;
	double			loopStartTime, loopEndTime;
	int				format;
	int				rate;
	bool			loopMode;
	unsigned int	queueSize;
	int				source_id;
	unsigned int	source;

	bool			surround;
	fk_Model		*ref_model;

	void			InitSource(void);

	void			CreateID(void);
	void			EraseID(void);
	void			MakeOVInfo(OggVorbis_File *);

	static void		UpdateListener(void);

#endif // !FK_DOXYGEN_USER_PROCESS

 public:

	//! コンストラクタ
	fk_AudioBase(void);

	//! デストラクタ
	virtual ~fk_AudioBase();


	//! \name 再生制御関数
	//@{

	//! オーディオデータ読み込み関数
	/*!
	 *	データを開くための仮想関数です。
	 *	具体的な仕様は各派生クラスの open() を参照して下さい。
	 *
	 *	\param[in]	name	データ名称。
	 *
	 *	\return
	 *		成功すれば true を、失敗すれば false を返します。
	 *
	 *	\sa	fk_AudioStream::open(), fk_AudioOggBuffer::open(),
	 *		fk_AudioWavBuffer::open()
	 */
	virtual bool	open(const std::string &name) = 0;

	//! 再生開始可能状態取得関数
	/*!
	 *	データ入力やデバイスの初期化等の処理が終了し、
	 *	再生が可能な状態となっているかどうかを取得する関数です。
	 *
	 *	\note
	 *		本関数は、通常の利用においてはユーザが使用する必要はありません。
	 *
	 *	\return
	 *		再生可能状態であれば true を、
	 *		まだ再生の準備ができていない状態であれば false を返します。
	 */
	virtual bool	ready(void) = 0;

	//! 再生関数
	/*!
	 *	実際に音声の再生を行う関数です。
	 *	本関数は、再生を行いたい状況においては1秒に数回以上の割合で、
	 *	連続して実行する必要があります。
	 *
	 *	\return
	 *		音声再生が完了していない場合は true を、
	 *		完了している場合 false を返します。
	 */
	virtual bool	play(void) = 0;

	//! 再生位置取得関数
	/*!
	 *	現在の再生位置を返します。単位は秒です。
	 *	この関数が返す値は再生時間ではなく、
	 *	音源での始端からの時間となります。
	 *
	 *	\return
	 *		現時点での再生位置。
	 *
	 *	\sa seek()
	 */
	virtual double	tell(void) = 0;

	//! 再生位置頭出し関数
	/*!
	 *	現在の再生位置を変更します。単位は秒です。
	 *
	 *	\param[in]	time	再生位置。
	 *
	 *	\sa tell()
	 */
	virtual void	seek(double time) = 0;

	//! 停止関数
	/*!
	 *	音声の再生を停止し、再生位置も初期化します。
	 *	この後に play() を実行した場合、
	 *	停止位置ではなく始端(または指定した箇所)から再生されます。
	 *	一時停止を行いたい場合は pause() を利用して下さい。
	 *
	 *	\sa pause()
	 */
	virtual void	stop(void) = 0;

	//! オーディオデータ解放関数
	/*!
	 *	open() 等で確保したデータを解放します。
	 *
	 *	\sa open(), stop(), pause()
	 */
	virtual void	end(void) = 0;

	//! ポーズ関数
	/*!
	 *	音声再生の一時停止を行います。
	 *	この後に play() を実行した場合、
	 *	停止位置からの再生が始まります。
	 *	始端(または指定した箇所)からの再生を行いたい場合は
	 *	stop() を利用して下さい。
	 *
	 *	\sa play(), stop(), end()
	 */
	void			pause(void);

	//@}

	//! \name 音量制御関数
	//@{

	//! 音量設定関数
	/*!
	 *	音量(減衰率)を設定します。
	 *
	 *	\param[in]	gain
	 *		音量値。0 で無音、1 で最大音量となります。
	 *		0 未満または 1 を超過する値が指定された場合は、
	 *		音量の変化を行いません。
	 */
	void	setGain(double gain);

	//! 音量取得関数
	/*!
	 *	現在の音量値(減衰率)を取得します。
	 *
	 *	\return
	 *		現在の音量値を返します。無音で0、最大音量で1となります。
	 */
	double	getGain(void);

	//@}

	//! \name キューバッファ制御関数
	//@{

	//! キューバッファサイズ設定関数
	/*!
	 *	キューバッファのサイズを設定します。
	 *	デフォルトは 64 です。
	 *
	 *	\param[in]	size
	 *		キューバッファのサイズ。
	 */
	void	setQueueSize(int size);

	//! キューバッファサイズ取得関数
	/*!
	 *	現在のキューバッファサイズ設定値を取得します。
	 *
	 *	\return
	 *		キューバッファのサイズ。
	 */
	int		getQueueSize(void);
	//@}

	//! \name ループ再生制御関数
	//@{

	//! ループモード設定関数
	/*!
	 *	ループモードを設定します。
	 *	ループモードとは、音源の最後まで再生が終了した際に、
	 *	最初から再び再生を開始するかどうかを設定するためのモードです。
	 *	具体的には、再生が音源の最後となった時点での
	 *	play() の挙動が異なってきます。
	 *	ループモードが ON の場合、
	 *	再生位置が最初の時点に戻り音源の再生を行います。
	 *	OFF の場合 play() は再生を終了し、false を返します。
	 *
	 *	\param[in]	mode
	 *		true の場合はループモードを ON とします。
	 *		false の場合はループモードを OFF とします。
	 *	
	 *	\sa play(), setLoopArea()
	 */
	void	setLoopMode(bool mode);

	//! ループモード取得関数
	/*!
	 *	現在のループモードを取得します。
	 *
	 *	\return
	 *		ループモードが ON のとき true を、
	 *		OFF のとき false を返します。
	 *	
	 *	\sa setLoopMode()
	 */
	bool	getLoopMode(void);

	//! ループエリア設定関数
	/*!
	 *	ループモードが ON である場合に、繰り返す音源の時間帯を指定します。
	 *	デフォルトでは、開始時間は 0、終了時間は -1 に設定されており、
	 *	終了時間が開始時間より前に設定されている場合、
	 *	ループモードでの終端は音源の終端となります。
	 *
	 *	\param[in]	start	ループモードでの再生開始時間
	 *	\param[in]	end		ループモードでの再生終了時間
	 *
	 *	\sa setLoopMode(), play(), seek(), tell()
	 */
	void	setLoopArea(double start, double end);

	//! ループ開始点取得関数
	/*!
	 *	ループモードでの再生開始時間を取得します。
	 *
	 *	\return		再生開始時間
	 *
	 *	\sa setLoopMode(), setLoopArea(), getLoopEndTime()
	 */
	double	getLoopStartTime(void);

	//! ループ終了点取得関数
	/*!
	 *	ループモードでの再生終了時間を取得します。
	 *
	 *	\return		再生終了時間
	 *
	 *	\sa setLoopMode(), setLoopArea(), getLoopStartTime()
	 */
	double	getLoopEndTime(void);

	//@}

	//! \name サラウンド制御関数
	//@{

	//! サラウンド音源位置設定関数
	/*!
	 *	音源インスタンスの3次元位置を指定します。
	 *	setModel(fk_Model *), setModel(fk_Model &) による同期モデルの指定が行われた場合は、
	 *	同期モデル位置が優先されます。
	 *	デフォルトは原点です。
	 *
	 *	\param[in]	pos		音源位置。
	 *
	 *	\sa getPosition(), setModel(fk_Model *), setModel(fk_Model &)
	 */
	void			setPosition(const fk_Vector &pos);

	//! サラウンド音源座標取得関数
	/*!
	 *	音源インスタンスの3次元位置を取得します。
	 *
	 *	\return		音源位置。
	 *
	 *	\sa setPosition(), setModel(fk_Model *), setModel(fk_Model &)
	 */
	fk_Vector		getPosition(void);

	//! サラウンド音源同期モデル設定関数1
	/*!
	 *	音源インスタンスの3次元空間中での位置と同期するモデルを指定します。
	 *	ここで指定したモデルが移動することにより、
	 *	音源もサラウンド効果の中で移動します。
	 *
	 *	\param[in]	model
	 *		音源と同期するモデルインスタンスのポインタ。
	 *		同期を解除したい場合は nullptr を代入します。
	 *
	 *	\sa setPosition(), getPosition(), getModel(),
	 *		setListenerModel(fk_Model *), setListenerModel(fk_Model &)
	 */
	void			setModel(fk_Model *model);

	//! サラウンド音源同期モデル設定関数2
	/*!
	 *	音源インスタンスの3次元空間中での位置と同期するモデルを指定します。
	 *	ここで指定したモデルが移動することにより、
	 *	音源もサラウンド効果の中で移動します。
	 *
	 *	\param[in]	model
	 *		音源と同期するモデルインスタンス。
	 *
	 *	\sa setPosition(), getPosition(), getModel(),
	 *		setListenerModel(fk_Model *), setListenerModel(fk_Model &)
	 */
	void			setModel(fk_Model &model);

	//! サラウンド音源同期モデル取得関数
	/*!
	 *	現在音源に設定されている位置同期モデルを返します。
	 *
	 *	\return
	 *		音源位置同期モデルのポインタ。
	 *		同期モデルが設定されていなかった場合は nullptr を返します。
	 */
	fk_Model *		getModel(void);

	//! サラウンド音源有効距離設定関数
	/*!
	 *	3次元空間中で音源が届く距離を指定します。
	 *	サラウンド効果においては、
	 *	音源はリスナーから離れるほど出力音量が小さくなり、
	 *	ここで指定する距離より大きい場合に聞こえなくなります。
	 *
	 *	\param[in]	dist	有効距離
	 *
	 *	\sa getReferenceDist()
	 */
	void			setReferenceDist(double dist);

	//! サラウンド音源座有効距離取得関数
	/*!
	 *	3次元空間中で音源が届く距離として設定されている値を取得します。
	 *
	 *	\return
	 *		有効距離
	 *
	 *	\sa setReferenceDist()
	 */
	double			getReferenceDist(void);

	//! サラウンド効果状態設定関数
	/*!
	 *	このインスタンスのサラウンド効果を制御します。
	 *
	 *	\param[in]	mode
	 *		true の場合、サラウンド効果を有効とします。
	 *		false の場合は無効とします。
	 *
	 *	\note
	 *		音源のサラウンド効果を有効とするには、
	 *		音源自体は(ステレオではなく)モノラルである必要があります。
	 *
	 *	\sa getSurroundMode()
	 */
	void			setSurroundMode(bool mode);

	//! サラウンド効果状態取得関数
	/*!
	 *	このインスタンスのサラウンド効果の有無効を取得します。
	 *
	 *	\return
	 *		有効な場合 true を、無効な場合 false を返します。
	 *
	 *	\sa setSurroundMode()
	 */
	bool			getSurroundMode(void);

	//@}

	//! \name システム全体初期化・制御関数
	//@{

	//! オーディオシステム初期化関数
	/*!
	 *	オーディオシステムを利用する際の初期化を行います。
	 *	本関数はオーディオシステムを利用する際には必ず実行する必要があります。
	 *	しかし、この関数の実行には一定の時間を要する場合もあります。
	 * 	getInit() 関数を併用することで、頻繁な実行は避けるべきです。
	 *
	 *	\sa getInit()
	 */
	static bool		init(void);

	//! オーディオシステム初期化状態取得関数
	/*!
	 *	既に初期化を行っているかどうかを取得します。
	 *	初期化を行う init() 関数は、
	 *	環境によってはかなり長い実行時間となることもあるため、
	 *	事前に本関数によって既に初期化が行われているかどうか調査を行い、
	 *	初期化されていない場合にのみ初期化を行うように記述すべきです。
	 *
	 *	\sa init()
	 */
	static bool		getInit(void);

	//! プロセススリープ関数
	/*!
	 *	音声再生のため処理を、指定された時間だけ中断します。
	 *	単位は秒です。
	 *
	 *	この関数は、処理を短時間停止して
	 *	CPU の計算資源を別の処理に割くためのものであり、
	 *	再生を停止するためのものではありません。
	 *	再生を停止するには本関数ではなく stop() や
	 *	pause() を用いて下さい。
	 *
	 *	なお、本関数は static 関数となっており、
	 *	処理の停止はインスタンス全体に対して行われます。
	 *
	 *	\note
	 *		本関数は、通常の利用においてユーザが用いることは想定していません。
	 *
	 *	\param[in]	time	処理を停止する時間。
	 *
	 *	\sa stop(), end()
	 */
	static void		sleep(double time);

	//@}

	//! \name サラウンドリスナー制御関数
	//@{

	//! サラウンドリスナー同期モデル設定関数1
	/*!
	 *	リスナーの位置を制御するための、
	 *	同期モデルインスタンスを指定します。
	 *	デフォルトでは、リスナー位置は原点です。
	 *
	 *	なお、本クラスのリスナーは
	 *	オーディオ系クラスの全インスタンスで共通となっています。
	 *	そのため static 関数となっており、
	 *	クラスインスタンスを生成せずに指定することが可能です。
	 *
	 *	リスナーではなく、音源自身の位置を変更するには
	 *	setPosition() や setModel() を使用して下さい。
	 *
	 *	\param[in]	model	リスナーとなるモデルインスタンスへのポインタ。
	 *
	 *	\sa setPosition(), setModel()
	 */
	static void			setListenerModel(fk_Model *model);

	//! サラウンドリスナー同期モデル設定関数2
	/*!
	 *	リスナーの位置を制御するための、
	 *	同期モデルインスタンスを指定します。
	 *	デフォルトでは、リスナー位置は原点です。
	 *
	 *	なお、本クラスのリスナーは
	 *	オーディオ系クラスの全インスタンスで共通となっています。
	 *	そのため static 関数となっており、
	 *	クラスインスタンスを生成せずに指定することが可能です。
	 *
	 *	リスナーではなく、音源自身の位置を変更するには
	 *	setPosition() や setModel() を使用して下さい。
	 *
	 *	\param[in]	model	リスナーとなるモデルインスタンス。
	 *
	 *	\sa setPosition(), setModel()
	 */
	static void			setListenerModel(fk_Model &model);

	//! サラウンドリスナーモデル取得関数
	/*!
	 *	リスナーに指定したモデルインスタンスを取得します。
	 *
	 *	\return
	 *		リスナーモデルインスタンスのポインタ。
	 *
	 *	\sa setListenerModel(fk_Model *), setListenerModel(fk_Model &)
	 */
	static fk_Model *	getListenerModel(void);

	//@}
};

//! オーディオストリームクラス
/*!
 *	このクラスは、
 *	Ogg Vorbis 形式のファイルに格納された音声の、
 *	ストリーミング再生機能を提供します。
 *
 *	このクラスでの再生は、再生時にファイルの一部分のみを読み込み、
 *	再生が進む過程で逐次ファイルの読み込みを行います。
 *	従って、巨大なファイルの入力であってもメモリの使用量を節約できます。
 *	長尺でループするような、BGM などの音源に適しています。
 *
 *	一方、頻繁な停止と再生の繰り返し、
 *	seek() を頻繁に用いた再生位置の変更、
 *	即応性のある再生には対応できません。
 *	そのため効果音等には向いていません。
 *	効果音を制御するような用途としては、
 *	fk_AudioOggBuffer, fk_AudioWavBuffer が適しています。
 *
 *	なお、本クラスは fk_AudioBase クラスの派生クラスであり、
 *	音量やループ再生の制御、サラウンド効果の使用といった機能の利用については
 *	fk_AudioBase のメンバ関数を用いて行います。
 *
 *	\sa fk_AudioBase, fk_AudioOggBuffer, fk_AudioWavBuffer
 */

class fk_AudioStream : public fk_AudioBase {
private:
	OggVorbis_File	*vf;
	bool			ovOpenStatus;
	int				current;
	char			buffer[FK_OV_BUFSIZE];
	double			nowTime;

	void			StartQueue(bool);
	bool			PlayStream(void);
	void			UnQueue(bool);

public:

	//! コンストラクタ
	fk_AudioStream(void);
	//! デストラクタ
	virtual ~fk_AudioStream();

	//! オーディオデータ読み込み関数
	/*!
	 *	Ogg Vorbis 形式のファイルを指定することで、
	 *	音声データを読み込みます。
	 *
	 *	\note
	 *		サラウンド効果を有効とするためには、
	 *		音源はモノラルでなければなりません。
	 *
	 *	\param[in]	filename	ファイル名。
	 *
	 *	\return
	 *		入力に成功すれば true を、
	 *		失敗すれば false を返します。
	 */
	bool			open(const std::string &filename);

	//! 再生開始可能状態取得関数
	/*!
	 *	open() によってファイルから音声を入力した後、
	 *	再生可能な状態になっているかどうかを取得します。
	 *
	 *	\note
	 *		本関数は、通常の利用においてはユーザが使用する必要はありません。
	 *
	 *	\return
	 *		再生可能状態であれば true を、
	 *		まだ再生の準備ができていない状態であれば false を返します。
	 */
	bool			ready(void);

	//! 再生関数
	/*!
	 *	実際に音声の再生を行う関数です。
	 *	この関数は、再生を行いたい状況においては1秒に数回以上の割合で、
	 *	連続して実行する必要があります。
	 *	通常は、画面更新のためのメインループ中に一度ずつ実行します。
	 *
	 *	\return
	 *		音声再生が完了していない場合は true を、
	 *		完了している場合 false を返します。
	 */
	bool			play(void);

	//! 再生位置取得関数
	/*!
	 *	現在の再生位置を返します。単位は秒です。
	 *	この関数が返す値は再生時間ではなく、
	 *	音源での始端からの時間となります。
	 *
	 *	\return
	 *		現時点での再生位置。
	 *
	 *	\sa seek()
	 */
	double			tell(void);

	//! 再生位置頭出し関数
	/*!
	 *	現在の再生位置を変更します。単位は秒です。
	 *
	 *	\param[in]	time	再生位置。
	 *
	 *	\sa tell()
	 */
	void			seek(double time);

	//! 停止関数
	/*!
	 *	音声の再生を停止し、再生位置も初期化します。
	 *	この後に play() を実行した場合、
	 *	停止位置ではなく始端(または指定した箇所)から再生されます。
	 *	一時停止を行いたい場合は fk_AudioBase::pause() を利用して下さい。
	 *
	 *	\sa fk_AudioBase::pause()
	 */
	void			stop(void);

	//! オーディオデータ解放関数
	/*!
	 *	open() 等で確保したデータを解放します。
	 *
	 *	\sa open(), stop(), fk_AudioBase::pause()
	 */
	void			end(void);
};

//! Ogg Vorbis オーディオバッファクラス
/*!
 *	このクラスは、Ogg Vorbis 形式のファイルに格納された音声を、
 *	オンメモリで再生する機能を提供します。
 *
 *	このクラスは、ファイルを読み込む時点で全ての音声データをメモリ上に展開します。
 *	これにより、頻繁な再生と停止を繰り返したり、
 *	seek() を頻繁に用いて再生位置を変更するといった、
 *	即応性の高い再生を可能としています。
 *	短くて頻繁に再生と停止を繰り返すような、効果音などの音源に適しています。
 *	また、サラウンドにも対応しています。
 *
 *	しかしながら、全てのデータをメモリ上に展開するという仕様上、
 *	巨大な音声データを入力した場合にはかなりのメモリを使用してしまいます。
 *	長尺で単調に再生するような BGM 再生などの用途には向いていません。
 *	そのような用途を想定する場合は、 fk_AudioStream クラスを利用して下さい。
 *
 *	また、Wave 形式のファイルを再生したい場合は
 *	fk_AudioWavBuffer クラスを利用してください。
 *	本クラスとほぼ同一の機能を持ちます。
 *
 *	なお、本クラスは fk_AudioBase クラスの派生クラスであり、
 *	音量やループ再生の制御、サラウンド効果の使用といった機能の利用については
 *	fk_AudioBase のメンバ関数を用いて行います。
 *
 *	\sa fk_AudioBase, fk_AudioWavBuffer, fk_AudioStream
 */
class fk_AudioOggBuffer : public fk_AudioBase {
 protected:

#ifndef FK_DOXYGEN_USER_PROCESS

	unsigned int			current, length;
	std::vector<char>		buffer;
	std::vector<int>		chunkSize;
	std::vector<double>		chunkTime;


	void			ReadBuffer(OggVorbis_File *);
	void			StartQueue(bool);
	bool			PlayBuffer(void);
	void			UnQueue(bool);

#endif // !FK_DOXYGEN_USER_PROCESS

public:

	//! コンストラクタ
	fk_AudioOggBuffer(void);
	//! デストラクタ
	virtual ~fk_AudioOggBuffer();

	//! オーディオデータ読み込み関数
	/*!
	 *	Ogg Vorbis 形式のファイルを指定することで、
	 *	音声データを読み込みます。
	 *
	 *	\note
	 *		サラウンド効果を有効とするためには、
	 *		音源はモノラルでなければなりません。
	 *
	 *	\param[in]	filename	ファイル名。
	 *
	 *	\return
	 *		入力に成功すれば true を、
	 *		失敗すれば false を返します。
	 */
	bool			open(const std::string &filename);

	//! 再生開始可能状態取得関数
	/*!
	 *	open() によってファイルから音声を入力した後、
	 *	再生可能な状態になっているかどうかを取得します。
	 *
	 *	\note
	 *		本関数は、通常の利用においてはユーザが使用する必要はありません。
	 *
	 *	\return
	 *		再生可能状態であれば true を、
	 *		まだ再生の準備ができていない状態であれば false を返します。
	 */
	bool			ready(void);

	//! 再生関数
	/*!
	 *	実際に音声の再生を行う関数です。
	 *	この関数は、再生を行いたい状況においては1秒に数回以上の割合で、
	 *	連続して実行する必要があります。
	 *	通常は、画面更新のためのメインループ中に一度ずつ実行します。
	 *
	 *	\return
	 *		音声再生が完了していない場合は true を、
	 *		完了している場合 false を返します。
	 */
	bool			play(void);

	//! 再生位置取得関数
	/*!
	 *	現在の再生位置を返します。単位は秒です。
	 *	この関数が返す値は再生時間ではなく、
	 *	音源での始端からの時間となります。
	 *
	 *	\return
	 *		現時点での再生位置。
	 *
	 *	\sa seek()
	 */
	double			tell(void);

	//! 再生位置頭出し関数
	/*!
	 *	現在の再生位置を変更します。単位は秒です。
	 *
	 *	\param[in]	time	再生位置。
	 *
	 *	\sa tell()
	 */
	void			seek(double time);

	//! 停止関数
	/*!
	 *	音声の再生を停止し、再生位置も初期化します。
	 *	この後に play() を実行した場合、
	 *	停止位置ではなく始端(または指定した箇所)から再生されます。
	 *	一時停止を行いたい場合は fk_AudioBase::pause() を利用して下さい。
	 *
	 *	\sa fk_AudioBase::pause()
	 */
	void			stop(void);

	//! オーディオデータ解放関数
	/*!
	 *	open() 等で確保したデータを解放します。
	 *
	 *	\sa open(), stop(), fk_AudioBase::pause()
	 */
	void			end(void);
};

//! Wave オーディオバッファクラス
/*!
 *	このクラスは、Wave 形式のファイルに格納された音声を、
 *	オンメモリで再生する機能を提供します。
 *	このクラスは、ファイルを読み込む時点で全ての音声データをメモリ上に展開します。
 *	これにより、頻繁な再生と停止を繰り返したり、
 *	seek() を頻繁に用いて再生位置を変更するといった、
 *	即応性の高い再生を可能としています。
 *	短くて頻繁に再生と停止を繰り返すような、効果音などの音源に適しています。
 *	また、サラウンドにも対応しています。
 *
 *	しかしながら、全てのデータをメモリ上に展開するという仕様上、
 *	巨大な音声データを入力した場合にはかなりのメモリを使用してしまいます。
 *	長尺で単調に再生するような BGM 再生などの用途には向いていません。
 *	そのような用途を想定する場合は、 fk_AudioStream クラスを利用して下さい。
 *
 *	また、Ogg Vorbis 形式のファイルを再生したい場合は
 *	fk_AudioOggBuffer クラスを利用してください。
 *	本クラスとほぼ同一の機能を持ちます。
 *
 *	なお、本クラスは fk_AudioBase クラスの派生クラスであり、
 *	音量やループ再生の制御、サラウンド効果の使用といった機能の利用については
 *	fk_AudioBase のメンバ関数を用いて行います。
 *
 *	\sa fk_AudioBase, fk_AudioOggBuffer, fk_AudioStream
 */

class fk_AudioWavBuffer : public fk_AudioOggBuffer {
 private:

	int				ReadHeaderWav(std::ifstream &, int *, int *, unsigned int *, int *);
	bool			ReadBuffer(std::ifstream &, int, int, unsigned int, int);

public:

	//! コンストラクタ
	fk_AudioWavBuffer(void);
	//! デストラクタ
	virtual ~fk_AudioWavBuffer();

	//! オーディオデータ読み込み関数
	/*!
	 *	Wave 形式のファイルを指定することで、
	 *	音声データを読み込みます。
	 *
	 *	\note
	 *		サラウンド効果を有効とするためには、
	 *		音源はモノラルでなければなりません。
	 *
	 *	\param[in]	filename	ファイル名。
	 *
	 *	\return
	 *		入力に成功すれば true を、
	 *		失敗すれば false を返します。
	 */
	bool	open(const std::string &filename);
};

#endif // !__FK_AUDIO_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
