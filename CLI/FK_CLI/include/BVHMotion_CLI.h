#pragma once

#include <FK/BVHMotion.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	//! BVH 形式のモーションデータを読み込み、保持するクラス
	/*!
	 *	このクラスは BVH 形式のモーションデータを読み込み、制御を行います。
	 *	主な用途は fk_IFSTexture クラスのインスタンスに対して Direct3D の X 形式を
	 *	読み込んだ際に、任意のモーションへと差し替える場合に使用します。
	 *	それ以外にも、このクラスのメンバ自体が fk_Model のツリー構造を保持しているため、
	 *	モーションの再生時刻を指定することでボーンの状態を再現することも可能です。
	 *	これを利用すれば、X 形式以外の形状要素を用いている場合でもモーションデータを
	 *	活用することができます。
	 *
	 *	\sa fk_IndexFaceSet, fk_IFSTexture, fk_Model
	 */
	public ref class fk_BVHMotion {
	internal:
		::FK::fk_BVHMotion *pMotion;
		::FK::fk_BVHMotion * GetP(void);

	public:
		//! コンストラクタ
		fk_BVHMotion();

		//! デストラクタ
		~fk_BVHMotion();

		//! ファイナライザ
		!fk_BVHMotion();

		//! モーション現在位置プロパティ
		/*!
		 *	モーション再生の現在位置を取得します。
		 */
		property int NowFrameCount {
			int get();
		}

		//! モーション長プロパティ
		/*!
		 *	モーションの長さをフレーム数で取得します。
		 */
		property int FrameLength {
			int get();
		}

		//! 1フレームの実時間プロパティ
		/*!
		 *	そのモーションデータにおける、1フレームの実時間を秒数で取得します。
		 */
		property double OneFrameTime {
			double get();
		}

		//! 初期化メソッド
		/*!
		 *	モーションデータを初期化します。
		 */
		void Init(void);

		//! BVH ファイル入力メソッド
		/*!
		 *	BVH 形式のファイルからモーションデータを読み込みます。
		 *
		 *	\param[in] fileName ファイル名
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool ReadBVHFile(String^ fileName);

		//! ノード数取得メソッド
		/*!
		 *	現在のモーションデータが持っているノード(ボーン)数を返します。
		 *
		 *	\return ノード数。モーションデータが未入力の場合は、0 を返します。
		 */
		int GetNodeNum(void);

		//! ノード名取得メソッド
		/*!
		 *	引数で指定したノードの名称を返します。
		 *
		 *	\param[in] index ノードのインデックス。0 からノード数-1 までの値をとります。
		 *
		 *	\return ノード名。インデックスが無効な値の場合は、空の文字列を返します。
		 */
		String^ GetNodeName(int index);

		//! ノードモデル取得メソッド1
		/*!
		 *	引数で指定したノードについて、その状態を保持している fk_Model のポインタを返します。
		 *
		 *	\param[in] index ノードのインデックス。0 からノード数-1 までの値をとります。
		 *
		 *	\return
		 *		ノードを表す fk_Model のポインタ。
		 *		インデックスが無効な値の場合は、null を返します。
		 */
		fk_Model^ GetNodeModel(int index);

		//! ノードモデル取得メソッド2
		/*!
		 *	引数で指定したノードについて、その状態を保持している fk_Model のポインタを返します。
		 *	ノードの名称を表す文字列で、対象ノードを指定します。
		 *
		 *	\param[in] nodeName ノードの名称。
		 *
		 *	\return
		 *		ノードを表す fk_Model のポインタ。
		 *		存在しないノード名を指定した場合は、null を返します。
		 */
		fk_Model^ GetNodeModel(String^ nodeName);

		//! モーション再生メソッド
		/*!
		 *	モーションを 1 フレーム分進め、各ノードの状態を更新します。
		 *	モーションの終端まで進んだら、先頭(0 フレーム目)に戻ります。
		 *
		 *	\return モーションを 1 フレーム進めた後のフレームカウント。
		 */
		int NextFrame(void);

		//! モーション状態セットメソッド
		/*!
		 *	各ノードの状態を、指定したフレームカウントのものに更新します。
		 *	モーションの現在位置も指定したフレームになります。
		 *
		 *	\param[in] frame
		 *		モーションのフレームカウント。
		 *		0 未満やモーションの長さ以上の値を指定した場合は、それぞれ上下限に丸められます。
		 */
		void SetFrameCount(int frame);

		//! アニメーション時間設定メソッド
		/*!
		 *	各ノードの状態を、秒で指定した時間に対応する状態に設定します。
		 *	モーションの現在位置は、指定した時間に直近のフレームになります。
		 *
		 *	\param[in] t 
		 *		時間。0.0 未満やモーションの長さ以上の値を指定した場合は、それぞれ上下限に丸められます。
		 */
		void SetAnimationTime(double t);
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
