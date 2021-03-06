﻿#pragma once

#include <FK/TriTexture.h>
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
		::FK::fk_TriTexture * GetP(void);

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

		//! 初期化メソッド
		/*!
		 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
		 */
		void Init(void);

		//! テクスチャ座標設定メソッド1
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

		//! テクスチャ座標設定メソッド2
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

		//! テクスチャ座標取得メソッド
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

		//! 頂点位置ベクトル設定メソッド1
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

		//! 頂点位置ベクトル設定メソッド2
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

		//! 頂点位置ベクトル取得メソッド
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
