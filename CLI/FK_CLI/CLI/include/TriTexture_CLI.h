// TriTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	//! 3角形テクスチャを生成、管理するクラス
	/*!
	 *	このクラスは、3角形のテクスチャを制御する機能を提供します。
	 *
	 *	3角形テクスチャを生成する大まかな手順は以下のようになります。
	 *	-# 画像を入力する。
	 *	-# 各頂点のテクスチャ座標を設定する。
	 *	-# 各頂点の3次元空間内の位置ベクトルを設定する。
	 *	.
	 *	空間上に各頂点を配置する際、頂点の順番が反時計回りになっている側が表面となります。
	 *	テクスチャ座標系の方は必ずしも反時計回りになっている必要はありませんが、
	 *	それが時計回りである場合は表示される画像が結果的に裏返ります。
	 *
	 *	本クラスでは、1つのインスタンスで制御できる3角形は1枚のみです。
	 *	複数枚の3角形を1つのインスタンスで制御したい場合は、
	 *	fk_MeshTexture クラスを用いた方がメモリ使用量や描画速度の効率が良くなります。
	 *	また、3角形ではなく矩形を扱いたい場合は fk_RectTexture クラスを利用して下さい。
	 *
	 *	\sa fk_Texture, fk_RectTexture, fk_MeshTexture, fk_IFSTexture
	 */
	public ref class fk_TriTexture : fk_Texture {
	internal:
		::fk_TriTexture * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_TriTexture(bool argNewFlg);
#endif

		//! コンストラクタ1
		/*!
		 *	テクスチャ画像が空の状態でインスタンスを生成します。
		 */
		fk_TriTexture();

		//! コンストラクタ2
		/*!
		 *	\param[in]	image
		 *		テクスチャ画像。省略するか null を代入した場合は、
		 *	   	テクスチャ画像を初期状態では生成しません。
		 */
		fk_TriTexture(fk_Image^ image);

		//! デストラクタ
		~fk_TriTexture();

		//! ファイナライザ
		!fk_TriTexture();

		//! 初期化関数
		/*!
		 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
		 */
		void Init(void);

		//! テクスチャ座標設定関数1
		/*!
		 *	頂点のテクスチャ座標を設定します。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	ID
		 *		頂点ID。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	x
		 *		テクスチャ座標の x 成分。0 以上 1 以下である必要があります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	y
		 *		テクスチャ座標の y 成分。0 以上 1 以下である必要があります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetTextureCoord(int ID, double x, double y);

		//! テクスチャ座標設定関数2
		/*!
		 *	頂点のテクスチャ座標を設定します。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	ID
		 *		頂点ID。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	coord
		 *		テクスチャ座標。各成文は 0 以上 1 以下である必要があります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetTextureCoord(int ID, fk_TexCoord^ coord);

		//! テクスチャ座標取得関数
		/*!
		 *	SetTextureCoord() で設定したテクスチャ座標を取得します。
		 *
		 *	\param[in]	ID		頂点ID。
		 *		0, 1, 2 のいずれか以外を指定した場合は、
		 *		常に (0, 0) を返します。
		 *
		 *	\return		IDに対応する頂点のテクスチャ座標
		 */
		fk_TexCoord^ GetTextureCoord(int ID);

		//! 頂点位置ベクトル設定関数1
		/*!
		 *	頂点の空間中での位置ベクトルを設定します。
		 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	ID
		 *		頂点ID。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	x	頂点位置ベクトルの x 成分
		 *	\param[in]	y	頂点位置ベクトルの y 成分
		 *	\param[in]	z	頂点位置ベクトルの z 成分
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetVertexPos(int ID, double x, double y, double z);

		//! 頂点位置ベクトル設定関数2
		/*!
		 *	頂点の空間中での位置ベクトルを設定します。
		 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	ID
		 *		頂点ID。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	pos		頂点位置ベクトル
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetVertexPos(int ID, fk_Vector^ pos);

		//! 頂点位置ベクトル取得関数
		/*!
		 *	SetTexturePos() で設定したテクスチャ座標を取得します。
		 *
		 *	\param[in]	ID		頂点ID。
		 *		0, 1, 2 のいずれか以外を指定した場合は、
		 *		常に (0, 0, 0) を返します。
		 *
		 *	\return		IDに対応する頂点の位置ベクトル
		 */
		fk_Vector^ GetVertexPos(int ID);
	};
}
