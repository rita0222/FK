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
#ifndef __FK_FRAMECONTROL_HEADER__
#define __FK_FRAMECONTROL_HEADER__

//#include <FK/Window.h>

#include <FK/Base.h>

#ifdef _MACOSX_
#define HAVE_USLEEP true
#define HAVE_UNISTD_H true
#include <unistd.h>
#endif

#ifdef WIN32
#include <Windows.h>
#include <mmsystem.h>
#endif


//! フレームレート制御クラス
/*!
 *	このクラスは、フレームレートのキープや計測などの機能を提供します。
 *	fk_Window にも同様の実装がありますが、それよりも高機能です。
 *	fk_AppWindow では内部実装としてこのクラスを利用しています。
 *	fk_Window を利用する場合でも、このクラスだけ単体で利用することが可能です。
 *
 *	\sa fk_Window
 */
class fk_FrameController {
private:
	//unsigned long m_dwLastFlipped;
	unsigned long nowTime;

	unsigned long m_dwLastMinitues;
	unsigned long m_dwFrameRate;
	unsigned long m_dwSkipRate;
	float m_fFrameTime;
	bool m_bDrawFlag;
	bool m_bFrameSkip;
		
	bool m_bInit;
	unsigned long m_dwFrameCount;
	unsigned long m_dwSkipCount;

	static void SleepOneMSec(void);

public:
	//! コンストラクタ
	fk_FrameController(unsigned long dwFps = 60, bool bFrameSkip = true);
	//! デストラクタ
	~fk_FrameController();

	//! フレームレート計測関数
	/*!
	 *	この関数をコールしてから、次にコールされるまでを 1 フレームとして扱い、
	 *	その処理時間を計測します。時間調整はせずに、最速で処理を返します。
	 *	ゲームのメインループ中で 1 度だけ呼ぶようにしてください。
	 *	timeRegular() とは排他的な関係になるので、両方を同時に利用することは避けてください。
	 */
	void measure(void);

	//! フレームレート指定関数
	/*!
	 *	timeRegular() で時間調整をする際に目標とするフレームレートを指定します。
	 *	デフォルトでは 60FPS になっています。
	 *	\param[in] time	キープしたいフレームレート。
	 */
	void setFPS(unsigned long time);

	//! フレームスキップモード設定関数
	/*!
	 *	setFPS() で設定したフレームレートを下回った場合に、
	 *	描画フラグでスキップを促すか否かを設定します。
	 *	デフォルトでは有効になっており、多くの場面ではその方が適切ですが、
	 *	あまりに過負荷なプログラムでは、画面が一切更新されずに応答不能に見える場合があります。
	 *	そのような場合は、一定時間が経過したら強制的に描画を行うように調整するのが良いでしょう。
	 *
	 *	\param[in] bFrameSkip
	 *		フレームスキップを有効にする場合は true を、無効にする場合は false を渡します。
	 */
	void setFrameSkipMode(bool bFrameSkip);

	//! 描画フラグ取得関数
	/*!
	 *	timeRegular() 使用時に、フレームレートに応じて、
	 *	描画するべきか、スキップするべきかを判定して返します。
	 *
	 *	\return 描画するべきタイミングなら true を、スキップするべきなら false を返します。
	 */
	bool getDrawFlag(void);

	//! フレームキープ基準点指定関数
	/*!
	 *	この関数をコールしてから、次にコールされるまでを 1 フレームとして扱い、
	 *	その間が setFPS() で指定したフレームレートになるよう時間調整を行います。
	 *	ゲームのメインループ中で 1 度だけ呼ぶようにしてください。
	 *	measure() とは排他的な関係になるので、両方を同時に利用することは避けてください。
	 */
	void timeRegular(void);

	//! スキップレート取得関数
	/*!
	 *	1 秒間に描画をスキップした回数を取得します。
	 *
	 *	\return スキップレート。
	 */
	unsigned long getSkipRate(void);

	//! フレームレート取得関数
	/*!
	 *	1 秒間に描画が行われている回数、いわゆる FPS(Frame Per Second) を取得します。
	 *
	 *	\return フレームレート。
	 */
	unsigned long getFrameRate(void);

	static unsigned long	getNow(void);

};

#endif // !__FK_FRAMECONTROL_HEADER__
