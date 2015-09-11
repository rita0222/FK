// BVHMotion_CLI.h

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
		::fk_BVHMotion *pMotion;
		::fk_BVHMotion * GetP(void);

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

		//! 初期化関数
		/*!
		 *	モーションデータを初期化します。
		 */
		void Init(void);

		//! BVH ファイル入力関数
		/*!
		 *	BVH 形式のファイルからモーションデータを読み込みます。
		 *
		 *	\param[in] fileName ファイル名
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool ReadBVHFile(String^ fileName);

		//! ノード数取得関数
		/*!
		 *	現在のモーションデータが持っているノード(ボーン)数を返します。
		 *
		 *	\return ノード数。モーションデータが未入力の場合は、0 を返します。
		 */
		int GetNodeNum(void);

		//! ノード名取得関数
		/*!
		 *	引数で指定したノードの名称を返します。
		 *
		 *	\param[in] index ノードのインデックス。0 からノード数-1 までの値をとります。
		 *
		 *	\return ノード名。インデックスが無効な値の場合は、空の文字列を返します。
		 */
		String^ GetNodeName(int index);

		//! ノードモデル取得関数1
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

		//! ノードモデル取得関数2
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

		//! モーション再生関数
		/*!
		 *	モーションを 1 フレーム分進め、各ノードの状態を更新します。
		 *	モーションの終端まで進んだら、先頭(0 フレーム目)に戻ります。
		 *
		 *	\return モーションを 1 フレーム進めた後のフレームカウント。
		 */
		int NextFrame(void);

		//! モーション状態セット関数
		/*!
		 *	各ノードの状態を、指定したフレームカウントのものに更新します。
		 *	モーションの現在位置も指定したフレームになります。
		 *
		 *	\param[in] frame
		 *		モーションのフレームカウント。
		 *		0 未満やモーションの長さ以上の値を指定した場合は、それぞれ上下限に丸められます。
		 */
		void SetFrameCount(int frame);

		//! アニメーション時間設定関数
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
