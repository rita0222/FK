// MeshTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	//! メッシュテクスチャを生成、管理するクラス
	/*!
	 *	このクラスは、複数の3角形テクスチャを制御する機能を提供します。
	 *
	 *	メッシュテクスチャを生成するおおまかな手順は以下のようになります。
	 *	-# 画像を入力する。
	 *	-# 各頂点のテクスチャ座標を設定する。
	 *	-# 各頂点の3次元空間内の位置ベクトルを設定する。
	 *	.
	 *	空間上に各頂点を配置する際、頂点の順番が反時計回りになっている側が表面となります。
	 *	テクスチャ座標系の方は必ずしも反時計回りになっている必要はありませんが、
	 *	それが時計回りである場合は表示される画像が結果的に裏返ります。
	 *
	 *	本クラスでは、1つのインスタンスで複数枚の3角形テクスチャを扱うことができます。
	 *	(その分、 fk_TriTexture よりも利用方法はやや複雑になっています。)
	 *	同様の機能を持つクラスとして、 fk_IFSTexture があります。
	 *	fk_IFSTexture クラスと比較した、
	 *	本クラスの長所と短所をまとめると以下のようになります。
	 *	- 長所
	 *		- 3角形テクスチャの動的生成が可能である。
	 *	- 短所
	 *		- 描画速度は若干劣る。
	 *		- D3DXファイルの入力に対応していない。
	 *	.
	 *	総じて、3角形テクスチャの動的生成を想定する場合は fk_MeshTexture が有用です。
	 *	それ以外の用途では、 fk_IFSTexture の利用を検討する価値があると言えます。
	 *
	 *	\sa fk_Texture, fk_RectTexture, fk_TriTexture, fk_IFSTexture
	 */
	public ref class fk_MeshTexture : fk_Texture {
	internal:
		::fk_MeshTexture * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_MeshTexture(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	テクスチャ画像自体は初期状態では生成しません。
		 */
		fk_MeshTexture();

		//! コンストラクタ2
		/*!
		 *	\param[in]	image
		 *		テクスチャ画像。null を代入した場合は、
		 *	   	テクスチャ画像を初期状態では生成しません。
		 */
		fk_MeshTexture(fk_Image^ image);

		//! デストラクタ
		~fk_MeshTexture();

		//! ファイナライザ
		!fk_MeshTexture();

		//! 3角形面数プロパティ
		/*!
		 *	3角形テクスチャ面の枚数の参照・設定を行います。
		 *	枚数を変更しても、前に設定した面データは可能な限り保持します。
		 */
		property int TriNum {
			void set(int);
			int get();
		}

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
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
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
		bool SetTextureCoord(int tID, int vID, double x, double y);

		//! テクスチャ座標設定関数2
		/*!
		 *	頂点のテクスチャ座標を設定します。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	coord
		 *		テクスチャ座標。各成文は 0 以上 1 以下である必要があります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetTextureCoord(int tID, int vID, fk_TexCoord^ coord);

		//! テクスチャ座標配列設定関数
		/*!
		 *	各3角形テクスチャのテクスチャ座標を、配列によって設定します。
		 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
		 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	array
		 *		テクスチャ座標を表す配列を入力します。
		 *		配列の先頭3個分のデータが利用されます。
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetTriTextureCoord(int tID, cli::array<fk_TexCoord^>^ array);

		//! テクスチャ座標参照関数
		/*!
		 *	設定されているテクスチャ座標を取得します。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
		 *
		 *	\return		テクスチャ座標。取得に失敗した場合は常に (0, 0) を返します。
		 *
		 *	\sa SetTextureCoord(), SetTriTextureCoord()
		 */
		fk_TexCoord^ GetTextureCoord(int tID, int vID);

		//! 頂点位置ベクトル設定関数1
		/*!
		 *	頂点の空間中での位置ベクトルを設定します。
		 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	x	頂点位置ベクトルの x 成分
		 *	\param[in]	y	頂点位置ベクトルの y 成分
		 *	\param[in]	z	頂点位置ベクトルの z 成分
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetVertexPos(int tID, int vID, double x, double y, double z);

		//! 頂点位置ベクトル設定関数2
		/*!
		 *	頂点の空間中での位置ベクトルを設定します。
		 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
		 *		それ以外の値を入力した場合はエラーとなり、false を返します。
		 *
		 *	\param[in]	pos		頂点位置ベクトル
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetVertexPos(int tID, int vID, fk_Vector^ pos);

		//! 頂点位置ベクトル配列設定関数
		/*!
		 *	各3角形テクスチャの頂点位置ベクトルを、配列によって設定します。
		 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	array
		 *		頂点の位置ベクトルを表す配列を入力します。
		 *		配列の先頭3個分のデータが利用されます。
		 *
		 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool SetTriPos(int tID, cli::array<fk_Vector^>^ array);

		//! 頂点位置ベクトル参照関数
		/*!
		 *	設定されている頂点位置ベクトルを取得します。
		 *
		 *	\param[in]	tID
		 *		3角形面の ID を入力します。
		 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
		 *
		 *	\param[in]	vID
		 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
		 *
		 *	\return		頂点位置ベクトル。取得に失敗した場合は常に (0, 0, 0) を返します。
		 *
		 *	\sa SetTexturePos(), SetTriTexturePos()
		 */
		fk_Vector^ GetVertexPos(int tID, int vID);

		//! fk_IndexFaceSet インスタンスコピー関数
		/*!
		 *	現在の形状データを、
		 *	fk_IndexFaceSet 型のインスタンスにコピーします。
		 *
		 *	\param[in]	ifs		fk_IndexFaceSet 型インスタンスのアドレス。
		 */
		void PutIndexFaceSet(fk_IndexFaceSet^ ifs);

		//! MQOファイル入力関数1
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *	本関数が入力を行うのは形状データとテクスチャ座標であり、
		 *	画像データの入力は行いません。
		 *	画像データ入力は fk_Texture のメンバ関数等を用いて別途行ってください。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *	\param[in]	contFlg
		 *		テクスチャ断絶の設定を指定します。これは、テクスチャ座標が不連続な箇所に対し、
		 *		形状の位相を断絶する操作を行うためのものです。
		 *		これを true にした場合は断裂操作が行われ、
		 *		テクスチャ座標が不連続な箇所が幾何的にも不連続となるように表示されます。
		 *		ほとんどの場合は、断裂操作を行った方が良好な描画結果となります。
		 *		ただし、断裂操作を行う際に新たな位相要素を生成するため、
		 *		本来のデータよりも頂点、稜線、面が若干増加する場合があります。
		 *		false にした場合は、断裂操作を行わずに通常のデータ通り読み込みます。
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, bool contFlg);

		//! MQOファイル入力関数2
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *	本関数が入力を行うのは形状データとテクスチャ座標であり、
		 *	画像データの入力は行いません。
		 *	画像データ入力は fk_Texture のメンバ関数等を用いて別途行ってください。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本関数は ReadMQOFile(String^, String^, bool) において、
		 *	第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName);
	};
}
