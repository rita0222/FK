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
#ifndef __FK_TIME_HEADER__
#define __FK_TIME_HEADER__

#include <chrono>

namespace FK {
	//! 時間管理用クラス
	/*!
	 *	このクラスは、様々な時間管理処理をおこなうための機能を提供します。
	 *	このクラスの役割は大きく以下の3種類があります。
	 *		- ラップタイム取得: \n
	 *			ストップウォッチのように、計測を開始してから経過した時間を取得します。
	 *		- プログラム稼働時間取得: \n
	 *			プログラムが開始してからの時間を取得します。
	 *		- スリープ: \n
	 *			プログラム(厳密にはこのクラスインスタンスを実行しているスレッド)を
	 *			一定時間停止します。
	 */

	class fk_Time {

	public:
		//! コンストラクタ
		fk_Time(void);

		//! デストラクタ
		~fk_Time();

		//! \name ラップタイム機能
		///@{

		//! 時間計測開始関数
		/*!
		 *	時間の計測を開始します。
		 *	この関数が呼ばれたのちに、 lapTime() を呼び出すことで、
		 *	計測開始からの時間を取得することができます。
		 *
		 *	stop() を呼び出すと時間経過を一旦止めることができますが、
		 *	累計時間はそのまま残ります。つまり、 start() と stop()
		 *	はストップウォッチの稼働と停止と同様の動作を行います。
		 *	累計時間をリセットしたい場合は init() を呼びます。
		 *
		 *	\sa stop(), init(), lapTime()
		 */
		void start(void);

		//! 時間計測一時停止関数
		/*!
		 *	時間の計測状態を一時的に停止します。
		 *	詳細は start() の解説を参照して下さい。
		 *
		 *	\sa start(), init(), lapTime()
		 */
		void stop(void);

		//! 累計時間初期化関数
		/*!
		 *	start(), stop() によって累計した時間を初期化します。
		 *	詳細は start() の解説を参照して下さい。
		 */
		void init(void);

		//! 経過時間取得関数
		/*!
		 *	start() が呼び出されてからの経過時間を取得します。
		 *	詳細は start() の解説を参照して下さい。
		 *	
		 *	\return 経過時間。単位は「秒」です。
		 */
		double lapTime(void);

		///@}

		//! \name プログラム稼働時間取得機能
		///@{

		//! プログラム稼働時間取得関数
		/*!
		 *	プログラムの稼働が開始されてから経過した実時間を取得します。
		 *	なお、本関数は static 関数なので、
		 *	fk_Time 型変数を作成しなくても直接以下のようにして呼び出すことができます。
		 *
		 *		double time = fk_Time::now();
		 *
		 *	\return 経過時間。単位は「秒」です。
		 */
		static double now(void);

		///@}

		//! \name スリープ機能
		///@{

		//! 秒単位スリープ関数
		/*!
		 *	この関数が呼び出されたスレッドを一時的に停止します。
		 *	他のスレッドは停止しません。
		 *
		 *	\param[in] time		停止時間。単位は「秒」です。
		 *
		 *	\sa usleep()
		 */
		static void sleep(double time);

		//! マイクロ秒単位スリープ関数
		/*!
		 *	この関数が呼び出されたスレッドを一時的に停止します。
		 *	他のスレッドは停止しません。
		 *
		 *	\param[in] time		停止時間。
		 *						単位は「マイクロ秒」、つまり100万分の1秒です。
		 *						usleep(1000000.0) は sleep(1.0) と同じ意味となります。
		 *
		 *	\sa sleep()
		 */

		static void usleep(double time);
		///@}

	private:

		std::chrono::system_clock::time_point stamp;
		double lap;
		bool runMode;
	};
}

#endif // !__FK_TIME_HEADER__


