// RectTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"

namespace FK_CLI
{
	//! 矩形テクスチャを生成、管理するクラス
	/*!
	 *	このクラスは、矩形型のテクスチャを制御する機能を提供します。
	 *	テクスチャを表示する方法としては、最も簡単なクラスとなります。
	 *
	 *	テクスチャ画像を表示する最低限の手順は、以下の通りです。
	 *	-# 画像を入力する。
	 *	-# fk_RectTexture::TextureSize プロパティへの設定によって、大きさを設定する。
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
	public ref class fk_RectTexture : fk_Texture {
	internal:
		::fk_RectTexture * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_RectTexture(bool argNewFlg);
#endif
		//! コンストラクタ1
		fk_RectTexture();

		//! コンストラクタ2
		/*!
		 *	\param[in]	image
		 *		テクスチャ画像。省略するか null を代入した場合は、
		 *	   	テクスチャ画像を初期状態では生成しません。
		 */
		fk_RectTexture(fk_Image^ image);

		//! デストラクタ
		~fk_RectTexture();

		//! ファイナライザ
		!fk_RectTexture();

		//! テクスチャサイズプロパティ
		/*!
		 *	矩形テクスチャの大きさの参照・設定を行います。
		 *
		 *	\sa fk_TexCoord
		 */
		property fk_TexCoord^ TextureSize {
			void set(fk_TexCoord^);
			fk_TexCoord^ get();
		}

		//! リピートモードプロパティ
		/*!
		 *	リピートモードの参照・設定を行います。
		 *	true であればリピートモードを有効とし、
		 *	false であれば無効とします。
		 *
		 *	リピートモードを有効にすると、画像が縦横に行列上に並んでいる状態になります。
		 *	並ぶ枚数については、 fk_RectTexture::RepeatParam プロパティで設定します。
		 *
		 *	リピートモードを利用する場合、画像の横幅、縦幅いずれも
		 *	\f$ 2^n \f$ (n は整数) で表される数値でなければならないという条件があります。
		 *	(横幅と縦幅は一致している必要はありません。)
		 *	この条件を満たさなかった場合の動作は保証されません。
		 *	また、リピートモードを有効とした場合、 SetTextureCoord() による
		 *	画像の切り出しも無効となります。
		 *
		 *	\sa RepeatParam
		 */
		property bool RepeatMode {
			void set(bool);
			bool get();
		}

		//! リピートモード枚数プロパティ
		/*!
		 *	リピートモードでの、縦方向と横方向に並べる枚数を設定します。
		 *	リピートモードについては fk_RectTexture::RepeatMode の説明を参照して下さい。
		 *
		 *	なお、枚数は正であれば整数である必要はありません。
		 *	その場合は、右端と上端の画像が途中で切れます。
		 *
		 *	\sa RepeatMode
		 */
		property fk_TexCoord^ RepeatParam {
			void set(fk_TexCoord^);
			fk_TexCoord^ get();
		}
		
		//! 初期化関数
		/*!
		 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
		 */
		void			Init(void);

		//! 部分抽出設定関数1
		/*!
		 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
		 *	領域指定はテクスチャ座標系を用います。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	なお、 fk_RectTexture::RepeatMode でリピートモードを有効とした場合、
		 *	この部分抽出の設定は無効となります。
		 *
		 *	\param[in]	sX	抽出左下部分の x 成分
		 *	\param[in]	sY	抽出左下部分の y 成分
		 *	\param[in]	eX	抽出右上部分の x 成分
		 *	\param[in]	eY	抽出右上部分の y 成分
		 */
		void			SetTextureCoord(double sX, double sY, double eX, double eY);

		//! 部分抽出設定関数2
		/*!
		 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
		 *	領域指定はテクスチャ座標系を用います。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	なお、 fk_RectTexture::RepeatMode でリピートモードを有効とした場合、
		 *	この部分抽出の設定は無効となります。
		 *
		 *	\param[in]	S	抽出左下部分のテクスチャ座標
		 *	\param[in]	E	抽出右上部分のテクスチャ座標
		 */
		void			SetTextureCoord(fk_TexCoord^ S, fk_TexCoord^ E);

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
		 *	\sa SetTextureCoord()
		 */
		fk_TexCoord^	GetTextureCoord(int ID);
	};
}
