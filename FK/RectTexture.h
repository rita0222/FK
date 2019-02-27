#ifndef	__FK_RECT_TEXTURE_HEADER__
#define	__FK_RECT_TEXTURE_HEADER__

#include <FK/Texture.h>

namespace FK {

	//! 矩形テクスチャを生成、管理するクラス
	/*!
	 *	このクラスは、矩形型のテクスチャを制御する機能を提供します。
	 *	テクスチャを表示する方法としては、最も簡単なクラスとなります。
	 *
	 *	テクスチャ画像を表示する最低限の手順は、以下の通りです。
	 *	-# 画像を入力する。
	 *	-# setTextureSize() 関数で大きさを設定する。
	 *	-# fk_Model に登録する。
	 *	.
	 *	あとは、他の形状クラスと同様です。
	 *
	 *	矩形の配置は、モデルの方向ベクトルに垂直となり、
	 *	画像の中心とモデルの中心が一致するように配置されます。
	 *	また、画像の表側はモデルの後方
	 *	(初期状態では +z 方向) 側から見た場合に見えるという点に注意して下さい。
	 *
	 *	\sa fk_Texture, fk_TriTexture, fk_MeshTexture, fk_IFSTexture
	 */

	class fk_RectTexture : public fk_Texture {

		friend class		fk_TextureDraw;

	public:

		//! コンストラクタ
		/*!
		 *	\param[in]	image
		 *		テクスチャ画像。省略するか nullptr を代入した場合は、
		 *	   	テクスチャ画像を初期状態では生成しません。
		 */
		fk_RectTexture(fk_Image *image = nullptr);

		//! デストラクタ
		virtual ~fk_RectTexture();

		//! 初期化関数
		/*!
		 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
		 */
		void				init(void);

		//! テクスチャサイズ設定関数
		/*!
		 *	矩形テクスチャの大きさを設定します。
		 *
		 *	\param[in]	w		横幅
		 *	\param[in]	h		縦幅
		 *
		 *	\return
		 *		横幅、縦幅のいずれかで 0 以下の値が入力されていた場合、
		 *		false を返します。設定に成功した場合は true を返します。
		 */
		bool				setTextureSize(double w, double h);

		//! テクスチャサイズ参照関数
		/*!
		 *	矩形テクスチャの大きさを取得します。
		 *
		 *	\return		矩形テクスチャの大きさ
		 */
		fk_TexCoord			getTextureSize(void);

		//! リピートモード設定関数
		/*!
		 *	リピートモードの設定を行います。
		 *	リピートモードを有効にすると、画像が縦横に行列上に並んでいる状態になります。
		 *	並ぶ枚数については、 setRepeatParam() 関数で設定します。
		 *
		 *	リピートモードを利用する場合、画像の横幅、縦幅いずれも
		 *	\f$ 2^n \f$ (n は整数) で表される数値でなければならないという条件があります。
		 *	(横幅と縦幅は一致している必要はありません。)
		 *	この条件を満たさなかった場合の動作は保証されません。
		 *	また、リピートモードを有効とした場合、 setTextureCoord() による
		 *	画像の切り出しも無効となります。
		 *
		 *	\param[in]	mode
		 *		true であればリピートモードを有効とし、
		 *		false であれば無効とします。
		 *
		 *	\sa setRepeatParam()
		 */
		void				setRepeatMode(bool mode);

		//! リピートモード参照関数
		/*!
		 *	現在のリピートモードの状態を取得します。
		 *
		 *	\return
		 *		true であればリピートモードが有効であることを意味します。
		 *		false であれば無効であることを意味します。
		 *
		 *	\sa setRepeatMode()
		 */
		bool				getRepeatMode(void);

		//! リピートモード枚数設定関数
		/*!
		 *	リピートモードでの、縦方向と横方向に並べる枚数を設定します。
		 *	リピートモードについては setRepeatMode() の説明を参照して下さい。
		 *
		 *	なお、枚数は正であれば整数である必要はありません。
		 *	その場合は、右端と上端の画像が途中で切れます。
		 *
		 *	\param[in]	wNum		横方法の枚数
		 *	\param[in]	hNum		縦方向の枚数
		 *
		 *	\sa setRepeatMode()
		 */
		void				setRepeatParam(double wNum, double hNum);

		//! リピートモード枚数参照関数
		/*!
		 *	リピートモードの、各方向の枚数を取得します。
		 *
		 *	\return		各方向の枚数
		 *
		 *	\sa setRepeatParam()
		 */
		fk_TexCoord			getRepeatParam(void);

		//! 部分抽出設定関数1
		/*!
		 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
		 *	領域指定はテクスチャ座標系を用います。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	なお、 setRepeatMode() でリピートモードを有効とした場合、
		 *	この部分抽出の設定は無効となります。
		 *
		 *	\param[in]	sX	抽出左下部分の x 成分
		 *	\param[in]	sY	抽出左下部分の y 成分
		 *	\param[in]	eX	抽出右上部分の x 成分
		 *	\param[in]	eY	抽出右上部分の y 成分
		 */
		void				setTextureCoord(double sX, double sY,
											double eX, double eY);

		//! 部分抽出設定関数2
		/*!
		 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
		 *	領域指定はテクスチャ座標系を用います。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	なお、 setRepeatMode() でリピートモードを有効とした場合、
		 *	この部分抽出の設定は無効となります。
		 *
		 *	\param[in]	S	抽出左下部分のテクスチャ座標
		 *	\param[in]	E	抽出右上部分のテクスチャ座標
		 */
		void				setTextureCoord(const fk_TexCoord &S,
											const fk_TexCoord &E);

		//! 部分抽出参照関数
		/*!
		 *	setTextureCoord() 関数によって部分抽出領域を設定した場合、
		 *	その領域のテクスチャ座標を取得します。
		 *
		 *	\param[in]	ID
		 *		0 であれば左下部のテクスチャ座標を、
		 *		1 であれば右上部のテクスチャ座標を返します。
		 *		それ以外の値を入力した場合は、常に (0, 0) を返します。
		 *
		 *	\return		左上部、または右上部のテクスチャ座標
		 *
		 *	\sa setTextureCoord()
		 */
		fk_TexCoord			getTextureCoord(int ID);

	private:

		fk_TexCoord			texSize;
		bool				repeatFlag;
		fk_TexCoord			repeatParam;
		fk_TexCoord			rectSE[2];
		bool				modifyFlg;
		
		void				RectInit(void);

		void				SizeUpdate();
		void				NormalUpdate();
		void				TexCoordUpdate();
		
		//void				MakeDrawRectFunc(void);
	};
}

#endif	// !__FK_RECT_TEXTURE_HEADER__

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
