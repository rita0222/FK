// TextImage_CLI.h

#pragma once

#include <FK/TextImage.h>
#include "Image_CLI.h"
#include "UniCode_CLI.h"

namespace FK_CLI {

	//! 文字列板の文字列配置を表す列挙型
	public enum class fk_TextAlign {
		LEFT,		//!< 左寄せ
		CENTER,		//!< 中寄せ
		RIGHT		//!< 右寄せ
	};

	//! 文字列板の文字送りモードを表す列挙型
	public enum class fk_TextSendingMode {
		ALL,		//!< 全体一括
		CHAR,		//!< 文字単位
		LINE		//!< 行単位
	};

	//! 文字列板を管理するクラス
	/*!
	 *	このクラスは、文字列板を制御する機能を提供します。
	 *
	 *  本クラスは fk_Image の派生クラスであり、本質的には画像を意味します。
	 *	通常の画像に対し、文字列を表示することに特化したクラスです。
	 *	このクラスを用いて作成した文字列を矩形テクスチャとすることで、
	 *	シーン上にメッセージを表示することができます。
	 *	実質的には通常の矩形テクスチャとなりますので、
	 *	単純に画面に文字を表示するだけではなく、
	 *	3次元空間中に自由に配置することができます。
	 *
	 *	文字列画像生成に際しては、複数行を一枚の画像中に表示することができます。
	 *	その際、左寄り、中寄り、右寄りといったアライメントや、
	 *	画像端からのマージンなども細かく設定することができます。
	 *
	 *	また、本クラスの特徴的な機能として「文字送り」があります。
	 *	これは、初期状態として全ての文字が表示されていない状態にしておき、
	 *	一文字ずつ、あるいは一行ずつ順番に表示していくという機能です。
	 *
	 *	本クラスを用いる場合、以下の順番で処理を進める必要があります。
	 *		-# フォント情報の入力 (InitFont())
	 *		-# 描画色、配置などの各種設定
	 *		-# 文字列の入力
	 *		.
	 *	これは、実際の画像生成を文字列データ入力の段階で行うため、
	 *	それ以外の設定を事前にしておかなければならないためです。
	 *	詳細はユーザーズマニュアルの「文字列板」の項目を参照して下さい。
	 *
	 *	なお、文字列板はその性質上、常に画面上で最前面に表示しておきたい場合が多くあります。
	 *	これは、シーン登録においてオーバーレイモデルとして登録することで容易に実現できます。
	 *	詳細は fk_DisplayLink::EntryOverlayModel() の解説を参照して下さい。
	 *
	 *	\sa fk_Image, fk_UniStr, fk_RectTexture, fk_Scene, fk_SpriteModel
	 */
	public ref class fk_TextImage : fk_Image {
	internal:
		::fk_TextImage * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_TextImage(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_TextImage();

		//! デストラクタ
		~fk_TextImage();

		//! ファイナライザ
		!fk_TextImage();

		//! フォント解像度プロパティ
		/*!
		 *	フォントの解像度の参照・設定を行います。
		 *	解像度を高くするほど高精細な画像となりますが、
		 *	画像サイズが大きくなるため描画時の負担が高くなっていきます。
		 *	デフォルトでは 48 に設定されています。
		 *
		 *	\note
		 *		機能的には fk_TextImage::PTSize とほとんど同義になりますが、
		 *		フォントによっては解像度が高い場合とサイズが大きい場合では
		 *		異なった描画結果となることがあります。
		 *
		 *	\sa PTSize
		 */
		property int DPI {
			int get();
			void set(int);
		}

		//! フォントサイズプロパティ
		/*!
		 *	フォントのサイズの参照・設定を行います。
		 *	サイズを大きくするほど高精細な画像となりますが、
		 *	画像サイズが大きくなるため描画時の負担が高くなっていきます。
		 *	デフォルトでは 48 に設定されています。
		 *
		 *	\note
		 *		機能的には fk_TextImage::DPI とほとんど同義になりますが、
		 *		フォントによっては解像度が高い場合とサイズが大きい場合では
		 *		異なった描画結果となることがあります。
		 *
		 *	\sa DPI
		 */
		property int PTSize {
			int get();
			void set(int);
		}

		//! 太さ値プロパティ
		/*!
		 *	文字の太さを数値に応じて太くします。
		 *	高い値であるほど、線が太くなっていきます。
		 *	デフォルトは 1 となっています。
		 *	太さの度合いについては、解像度やフォントサイズに依存するので、
		 *	それぞれと合わせて調整する必要があります。
		 *
		 *	\param[in]	str		太さ値
		 *
		 *	\sa DPI, PTSize
		 */
		property int BoldStrength {
			int get();
			void set(int);
		}

		//! 影付け効果プロパティ
		/*!
		 *	表示文字に対し、影付け効果有無の参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *	デフォルトでは無効となっています。
		 *
		 *	\sa ShadowOffset, ShadowColor
		 */
		property bool ShadowMode {
			bool get();
			void set(bool);
		}

		//! 影付けずらし幅プロパティ
		/*!
		 *	影付け効果の際、影のずらし幅を設定します。
		 *
		 *	x 成分は横方向のずれを設定します。単位はピクセルです。
		 *	正の値で右方向、負の値で左方向にずらします。
		 *
		 *	y 成分は縦方向のずれを設定します。単位はピクセルです。
		 *	正の値で下方向、負の値で上方向にずらします。
		 *
		 *	\sa ShadowMode, ShadowColor, fk_Dimension
		 */
		property fk_Dimension^ ShadowOffset {
			fk_Dimension^ get();
			void set(fk_Dimension^);
		}

		//! 影付け色プロパティ
		/*!
		 *	影付け効果の際の、影の色の参照・設定を行います。透過色設定も有効となります。
		 *
		 *	\sa ShadowMode, ShadowOffset, fk_Color
		 */
		property fk_Color^ ShadowColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! 文字色プロパティ
		/*!
		 *	文字色の参照・設定を行います。透過色設定も有効となります。
		 *
		 *	\sa BackColor, SmoothMode
		 */
		property fk_Color^ ForeColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! 背景色プロパティ
		/*!
		 *	背景色の参照・設定を行います。透過色設定も有効となります。
		 *
		 *	\sa ForeColor, SmoothMode
		 */
		property fk_Color^ BackColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! アンチエイリアシング効果プロパティ
		/*!
		 *	表示文字に対し、アンチエイリアシング効果の有無の参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *
		 *	この設定を有効とした場合、
		 *	表示の際に文字色と背景色の中間色も描画に利用されるようになります。
		 *	逆に無効とした場合、描画の際には文字色と背景色以外は利用されなくなります。
		 *	デフォルトでは有効となっています。
		 *
		 *	\sa ForeColor, BackColor
		 */
		property bool SmoothMode {
			bool get();
			void set(bool);
		}

		//! 等幅表示プロパティ
		/*!
		 * 	文字の等幅表示効果の参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *	デフォルトでは無効となっています。
		 *
		 *	設定を有効とした場合、半角全角問わず全ての文字を等幅で表示します。
		 *	なお、 fk_TextImage::CharSkip によって設定する文字間幅は等幅においても有効となります。
		 *
		 *	\note
		 *		fk_TextImage::MonospaceSize によって文字幅を設定しないと、
		 *		文字幅が 0 として表示されてしまうため、何も表示されていない状況となります。
		 *
		 *	\sa MonospaceSize, CharSkip
		 */
		property bool MonospaceMode {
			bool get();
			void set(bool);
		}

		//! 等幅表示文字幅プロパティ
		/*!
		 *	等幅表示の際の文字幅の参照・設定を行います。単位はピクセルとなります。
		 *	デフォルトでは 0 が設定されています。
		 *
		 *	\note
		 *		等幅表示は、 fk_TextImage::MonospaceMode
		 *		で設定を有効としなければ等幅表示とはなりません。
		 *
		 *	\sa MonospaceMode, CharSkip
		 */
		property int MonospaceSize {
			int get();
			void set(int);
		}

		//! 文字間幅プロパティ
		/*!
		 *	文字同士の横方向の空白幅の参照・設定を行います。
		 *	単位はピクセルとなります。
		 *	デフォルトは 0 に設定されています。
		 *
		 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
		 *	つまり、解像度やフォントサイズが大きい場合、
		 *	空白を作るには大きな値が必要となります。
		 *	従って、解像度やフォントサイズを変更した場合には、
		 *	この値も再度調整する必要があります。
		 *
		 *	\sa LineSkip, SpaceLineSkip, SetOffset(),
		 *		DPI, PTSize, MonospaceMode, MonospaceSize
		 */
		property int CharSkip {
			int get();
			void set(int);
		}
		
		//! 行間幅プロパティ
		/*!
		 * 	行同士の縦方向の空白幅の参照・設定を行います。
		 *	単位はピクセルとなります。
		 *	デフォルトは 0 に設定されています。
		 *
		 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
		 *	つまり、解像度やフォントサイズが大きい場合、
		 *	空白を作るには大きな値が必要となります。
		 *	従って、解像度やフォントサイズを変更した場合には、
		 *	この値も再度調整する必要があります。
		 *
		 *	\sa CharSkip, SpaceLineSkip, SetOffset(), DPI, PTSize
		 */
		property int LineSkip {
			int get();
			void set(int);
		}

		//! 空行縦幅プロパティ
		/*!
		 *	文字列中に空行が入っていた場合の、その縦幅を設定します。
		 *	単位はピクセルとなります。
		 *	この値が 0 である場合、空行は結果的に省略されることになります。
		 *
		 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
		 *	つまり、解像度やフォントサイズが大きい場合、
		 *	空白を作るには大きな値が必要となります。
		 *	従って、解像度やフォントサイズを変更した場合には、
		 *	この値も再度調整する必要があります。
		 *
		 *	\sa CharSkip, LineSkip, SetOffset(), DPI, PTSize
		 */
		property int SpaceLineSkip {
			int get();
			void set(int);
		}

		//! 文字列寄せ方向(アライメント)プロパティ
		/*!
		 *	文字列を表示する際の、文字寄せ方向(アライメント)の参照・設定を行います。
		 *
		 *	複数行に渡る文字列の場合で、各行の横幅が異なる場合や、
		 *	fk_TextImage::MinLineWidth によって画像の横幅をあらかじめ設定した場合などは、
		 *	行の横幅が画像の横幅に満たない状況が生じます。
		 *	このような行に対し、本メソッドでどちら側に寄るのかを設定します。
		 *	デフォルトは fk_Align.LEFT 、つまり左寄せとなっています。
		 *
		 *	\sa fk_TextAlign, MinLineWidth
		 */
		property fk_TextAlign Align {
			fk_TextAlign get();
			void set(fk_TextAlign);
		}

		//! 画像最小横幅プロパティ
		/*!
		 *	生成される文字列板画像の横幅の最小値の参照・設定を行います。
		 *	単位はピクセルとなります。
		 *	デフォルトは 0 に設定されています。
		 *
		 *	通常、文字列板として生成される画像の横幅は、
		 *	入力した文字列に依存します。
		 *	行の文字数が多ければ幅は広がり、逆に少ない場合は狭まります。
		 *	このような異なる画像を同じテクスチャ画像として連続に表示した場合、
		 *	一文字の横幅が画像によって変動してしまうという現象が生じます。
		 *	これは、あまり見栄えが良いとは言えません。
		 * 	そのような場合、本メソッドを用いて十分な横幅を予め確保しておきます。
		 *	そうすることで、文字列はアライメントに従って適切に配置され、
		 *	文字の幅も画像によって変わることはありません。
		 *
		 *	ただし、ここで設定した横幅を超える幅を持つ行が発生した場合、
		 *	画像の幅はその行による幅に設定されることになります。
		 *
		 *	\sa Align
		 */
		property int MinLineWidth {
			int get();
			void set(int);
		}

		//! 行数プロパティ
		/*!
		 *	入力した文字列の行数を参照します。
		 *
		 *	\sa LoadUniStr(), LoadStrFile()
		 */
		property int LineNum {
			int get();
		}
		
		//! 文字数プロパティ
		/*!
		 *	入力した文字列の文字数を参照します。
		 *
		 *	\sa LineNum, GetLineCharNum(), LoadUniStr(), LoadStrFile()
		 */
		property int AllCharNum {
			int get();
		}

		//! 最大横幅プロパティ
		/*!
		 *	入力した文字列のうち、最も横幅が広い行の横幅を参照します。
		 *	単位はピクセルとなります。
		 *
		 *	画像の横幅を直接取得するには、 fk_Image::Size を利用して下さい。
		 *	
		 *	\sa MaxLineHeight, MinLineWidth, GetLineWidth()
		 */
		property int MaxLineWidth {
			int get();
		}

		//! 最大縦幅プロパティ
		/*!
		 *	入力した文字列のうち、最も縦幅が広い行の縦幅を参照します。
		 *	単位はピクセルとなります。
		 *
		 *	画像全体の縦幅を取得するには、 fk_Image::Size を利用して下さい。
		 *
		 *	\note
		 *		TrueType 形式のフォント、特に半角英数字については、
		 *		横幅、縦幅共に文字によって異なります。
		 *		結果として、行の縦幅も構成される文字によって異なってくることになります。
		 *
		 *	\sa MaxLineWidth, GetLineHeight()
		 */
		property int MaxLineHeight {
			int get();
		}

		//! 文字送りモードプロパティ
		/*!
		 *	文字送りのモードの参照・設定を行います。
		 *
		 *	「文字送り」とは、読み込んだ文字列を最初は表示せず、
		 *	一文字ずつ、あるいは一行ずつ徐々に表示していく機能のことです。
		 *	文字送りを有効とした場合、
		 *	Send() を呼び出すごとに一文字ずつ、あるいは一行ずつが表示されていきます。
		 *	一度表示した文字列については、
		 *	Clear() を呼び出すことで初期状態
		 *	(文字が表示されていない状態)に戻すことができます。
		 *
		 *	本メソッドは、文字列を LoadUniStr() や
		 *	LoadStrFile() で入力する前に設定しておくことが可能です。
		 *	また、入力後に動的に変更することも可能です。
		 *
		 *	値として、以下のものが設定可能です。
		 *
		 *		- fk_TextSendingMode.CHAR: 一文字ずつ送るモード。
		 *		- fk_TextSendingMode.LINE: 一行ずつ送るモード。
		 *		- fk_TextSendingMode.ALL: 文字送りを無効とするモード。
		 *
		 *	\sa Send(), Finish(), Clear()
		 */
		property fk_TextSendingMode SendingMode {
			fk_TextSendingMode get();
			void set(fk_TextSendingMode);
		}

		//! キャッシュ機能制御プロパティ
		/*!
		 *	このメソッドは、フォントデータのキャッシュの制御を参照・設定します。
		 *	true であれば有効、false であれば無効とします。
		 *	デフォルトでは無効となっています。
		 *
		 *	文字列の画像を生成する際には、
		 *	入力されたフォントデータからビットマップとしての
		 *	画像情報に変換するという処理がなされます。
		 *	同じ文字に対してこの処理を行うことは、計算時間の点で無駄となります。
		 *	そこで、 fk_TextImage には一度得た画像情報を保存しておき、
		 *	同じ文字が登場した際には再利用するという機能があります。
		 *	これが「キャッシュ機能」です。
		 *	特に数字やアルファベット、平仮名などは再利用する頻度が高いため、
		 *	本機能を有効とすることで処理が高速となる利点があります。
		 *
		 *	一方、キャッシュ機能はメモリの利用量が増えることを意味します。
		 *	高い解像度やフォントサイズを用いている場合は、
		 *	キャッシュのメモリ利用量も膨大となっていきますので、
		 *	場合によっては処理速度がむしろ低下することもありえます。
		 *
		 *	ここで利用されるキャッシュデータは、
		 *	インスタンス毎ではなくシステム全体で共有されます。
		 *	従って、異なるインスタンスで読み込んだ文字に関しても
		 *	キャッシュ効果が働くことになります。
		 *
		 *	\sa ClearCache()
		 */
		static property bool CacheMode {
			bool get();
			void set(bool);
		}
		
		//! \name フォント関連メソッド
		//@{

		//! フォント情報入力メソッド
		/*!
		 *	フォントの入力を行います。
		 *	ここで指定するものは TrueType 形式のフォントファイルとなります。
		 *	通常は「ttf」あるいは「ttc」という拡張子のファイルとなっています。
		 *
		 *	なお、このメソッドは LoadUniStr() や LoadStrFile()
		 *	などの文字列入力よりも先に行っておく必要があります。
		 *
		 *	\param[in]	fontFileName	フォントファイル名
		 *
		 *	\return
		 *		フォントの設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\attention
		 *		各種 OS に付属しているフォントファイルや、
		 *		商用のフォントファイルの中には、
		 *		ライセンス上再配布が禁止されているものがあります。
		 *		プログラムの配布時には必ずライセンスの確認を行ってください。
		 */
		bool	InitFont(String^ fontFileName);
		//@}

		//! \name 文字配置事前設定関連メソッド
		//@{
		
		//! オフセット設定メソッド
		/*!
		 *	文字が実際に表示されている部分と、画面の縁までの幅を設定します。
		 *	単位はピクセルとなります。
		 *	デフォルトでは、全て 0 に設定されています。
		 *
		 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
		 *	つまり、解像度やフォントサイズが大きい場合、
		 *	空白を作るには大きな値が必要となります。
		 *	従って、解像度やフォントサイズを変更した場合には、
		 *	この値も再度調整する必要があります。
		 *
		 *	\param[in]	up		上幅
		 *	\param[in]	down	下幅
		 *	\param[in]	left	左幅
		 *	\param[in]	right	右幅
		 *
		 *	\sa CharSkip, LineSkip, SpaceLineSkip, DPI, PTSize
		 */
		void	SetOffset(int up, int down, int left, int right);

		//! オフセット上幅参照メソッド
		/*!
		 *	文字が実際に表示されている部分のうち、上側の縁までの幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\return		上幅
		 *
		 *	\sa SetOffset()
		 */
		int		GetUpOffset(void);

		//! オフセット下幅参照メソッド
		/*!
		 *	文字が実際に表示されている部分のうち、下側の縁までの幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\return		下幅
		 *
		 *	\sa SetOffset()
		 */
		int		GetDownOffset(void);

		//! オフセット左幅参照メソッド
		/*!
		 *	文字が実際に表示されている部分のうち、左側の縁までの幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\return		左幅
		 *
		 *	\sa SetOffset()
		 */
		int		GetLeftOffset(void);

		//! オフセット右幅参照メソッド
		/*!
		 *	文字が実際に表示されている部分のうち、右側の縁までの幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\return		右幅
		 *
		 *	\sa SetOffset()
		 */
		int		GetRightOffset(void);
		//@}

		//! \name 文字列入力メソッド
		//@{

		//! 文字列データ入力メソッド
		/*!
		 *	fk_UniStr 型のインスタンスに格納されている文字列を入力します。
		 *
		 *	文字列板画像は、
		 *	このメソッドかまたは LoadStrFile() が呼ばれた時点で生成されます。
		 *	従って、色や配置などの設定は本メソッドを呼ぶ前に行わなければなりません。
		 *
		 *	既に本メソッドを実行したインスタンスに対し、改めて本メソッドを実行することは可能です。
		 *	その場合は、新たな文字列と設定に基づき、文字列板画像を再構築します。
		 *
		 *	\param[in]	str		文字列が格納されているインスタンス
		 *
		 *	\return		文字列板生成に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa LoadStrFile()
		 */
		bool	LoadUniStr(fk_UniStr^ str);

		//! 文字列データファイル入力メソッド1
		/*!
		 *	テキストファイルに入っている文字列を入力します。
		 *
		 *	文字列板画像は、
		 *	このメソッドかまたは LoadUniStr() が呼ばれた時点で生成されます。
		 *	従って、色や配置などの設定は本メソッドを呼ぶ前に行わなければなりません。
		 *
		 *	既に本メソッドを実行したインスタンスに対し、改めて本メソッドを実行することは可能です。
		 *	その場合は、新たな文字列と設定に基づき、文字列板画像を再構築します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\return		文字列板生成に成功すれば true を、失敗すれば false を返します。
		 */
		bool	LoadStrFile(String^ fileName, fk_StringCode code);

		//! 文字列データファイル入力メソッド2
		/*!
		 *	テキストファイルに入っている文字列を入力します。
		 *	なお、文字コードは UTF-16 であることを前提としています。
		 *	その他の文字コードで入力したい場合は
		 *	LoadStrFile(String^, fk_StringCode) を利用して下さい。
		 *
		 *	文字列板画像は、
		 *	このメソッドかまたは LoadUniStr() が呼ばれた時点で生成されます。
		 *	従って、色や配置などの設定は本メソッドを呼ぶ前に行わなければなりません。
		 *
		 *	既に本メソッドを実行したインスタンスに対し、改めて本メソッドを実行することは可能です。
		 *	その場合は、新たな文字列と設定に基づき、文字列板画像を再構築します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return		文字列板生成に成功すれば true を、失敗すれば false を返します。
		 */
		bool	LoadStrFile(String^ fileName);

		//! 行中文字数参照メソッド
		/*!
		 *	入力した文字列中の、指定した行の文字数を取得します。
		 *
		 *	\param[in]	num		行番号。最初の行は 0 となります。
		 *
		 *	\return		文字数
		 *
		 *	\sa LineNum, AllCharNum, LoadUniStr(), LoadStrFile()
		 */
		int		GetLineCharNum(int num);

		//! 行横幅参照メソッド
		/*!
		 *	入力した文字列中の、指定した行の横幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\param[in]	num		行番号。最初の行は 0 となります。
		 *
		 *	\return		横幅
		 *
		 *	\sa GetLineHeight(), MaxLineWidth
		 */
		int		GetLineWidth(int num);

		//! 行縦幅参照メソッド
		/*!
		 *	入力した文字列中の、指定した行の縦幅を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\note
		 *		TrueType 形式のフォント、特に半角英数字については、
		 *		横幅、縦幅共に文字によって異なります。
		 *		結果として、行の縦幅も構成される文字によって異なってくることになります。
		 *
		 *	\param[in]	num		行番号。最初の行は 0 となります。
		 *
		 *	\return		縦幅
		 *
		 *	\sa GetLineWidth(), MaxLineHeight
		 */
		int		GetLineHeight(int num);

		//! 行開始位置 x 成分取得メソッド
		/*!
		 *	入力した文字列中の、
		 *	指定した行の開始位置(文字列左下部分)の x 成分を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\param[in]	num		行番号。最初の行は 0 となります。
		 *
		 *	\return		行左下部分の x 成分
		 *
		 *	\sa GetLineStartYPos()
		 */
		int		GetLineStartXPos(int num);

		//! 行開始位置 y 成分取得メソッド
		/*!
		 *	入力した文字列中の、
		 *	指定した行の開始位置(文字列左下部分)の y 成分を取得します。
		 *	単位はピクセルとなります。
		 *
		 *	\param[in]	num		行番号。最初の行は 0 となります。
		 *
		 *	\return		行左下部分の y 成分
		 *
		 *	\sa GetLineStartXPos()
		 */
		int		GetLineStartYPos(int num);

		//@}

		//! \name 文字送り関連メソッド
		//@{

		//! 文字送り実行メソッド
		/*!
		 *	fk_TextImage::SendingMode プロパティで指定したモードに従い、
		 *	文字送りを行います。
		 *
		 *	\return
		 *		文字送りが行われたら true を返します。
		 *		既に全ての文字が表示されていた状態で本メソッドを呼び出した場合は、
		 *		false を返します。
		 *
		 *	\sa SendingMode, Finish(), Clear()
		 */
		bool	Send(void);

		//! 文字送り完了メソッド
		/*!
		 *	文字送りが有効である場合に、
		 *	まだ表示されていない文字を全て表示させます。
		 *
		 *	\return
		 *		本メソッドを呼び出した時点で、まだ表示されていない文字があり、
		 *		新たに表示された文字が存在した場合には true を返します。
		 *		呼び出した時点で既に全ての文字が表示されており、
		 *		新たに表示された文字が存在しなかった場合には false を返します。
		 *
		 *	\sa SendingMode, Send(), Clear()
		 */
		bool	Finish(void);

		//! 文字送り初期化メソッド
		/*!
		 *	文字送りが有効である場合に、
		 *	全ての文字を初期状態、つまり非表示の状態に戻します。
		 *
		 *	\return
		 *		本メソッドを呼び出した時点で、既に表示されていた文字があり、
		 *		なんらかの文字が消去された場合には true を返します。
		 *		呼び出した時点で文字が表示されておらず、
		 *		結果的に非表示となった文字が存在しなかった場合には false を返します。
		 *
		 *	\sa SendingMode, Send(), Finish()
		 */
		bool	Clear(void);
		//@}

		//! \name キャッシュ関連メソッド
		//@{

		//! キャッシュ初期化メソッド
		/*!
		 *	キャッシュ機能が有効である場合に、
		 *	これまでのキャッシュデータをすべて消去します。
		 *
		 *	\sa CacheMode
		 */
		static void	ClearCache(void);
		//@}
	};
}

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
