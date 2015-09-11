// IFSTexture_CLI.h

#pragma once

#include <FK/IFSTexture.h>
#include "Texture_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{

	//! IFSテクスチャを生成、管理するクラス
	/*!
	 *	このクラスは、「IFSテクスチャ」を制御する機能を提供します。
	 *	IFSテクスチャとは、多数の三角形テクスチャをひとまとめにした形状のことで、
	 *	実質的には fk_IndexFaceSet クラスに対してテクスチャを付加したものです。
	 *	このクラスの主な用途は、
	 *	他のモデラー等で作成した形状データファイルを読み込んで表示するというものです。
	 *	また、 fk_IndexFaceSet クラスと同様に形状のアニメーションを入力することも可能です。
	 *
	 *	なお、このクラスでテクスチャ付きの形状データを読み込む場合、
	 *	テクスチャデータは 1 個のファイルで構成されていなければならないという制限があります。
	 *
	 *	実際に利用する際には、まずテクスチャ画像データを設定する必要があります。
	 *	画像データの入力や生成については、 fk_Texture のマニュアルを参照して下さい。
	 *	形状データの入力と画像データの設定は、どちらが先であっても問題ありません。
	 *
	 *	本クラスと同様の機能を持つクラスとして、 fk_MeshTexture があります。
	 *	fk_MeshTexture クラスと比較した、
	 *	本クラスの長所と短所をまとめると以下のようになります。
	 *	- 長所
	 *		- 描画速度が速い。
	 *		- D3DXファイルの入力に対応している。
	 *	- 短所
	 *		- 3角形テクスチャの動的生成ができない。
	 *	.
	 *	ほとんどの用途においては fk_IFSTexture の方が有利と言えますが、
	 *	3角形テクスチャの動的生成を行いたい場合は
	 *	fk_MeshTexture の利用を検討する価値があると言えます。
	 *
	 *	\sa fk_IndexFaceSet, fk_Texture, fk_MeshTexture
	 */
	public ref class fk_IFSTexture : fk_Texture {
	internal:

		::fk_IFSTexture * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_IFSTexture(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	テクスチャデータを空の状態としてインスタンスを生成します。
		 */
		fk_IFSTexture();

		//! コンストラクタ2
		/*!
		 *	引数画像をテクスチャ画像とするインスタンスを生成します。
		 *
		 *	\param[in]	image  
		 *		テクスチャデータ。
		 *		null が代入された場合はテクスチャデータを空の状態として生成します。
		 */
		fk_IFSTexture(fk_Image^ image);

		//! デストラクタ
		~fk_IFSTexture();

		//! ファイナライザ
		!fk_IFSTexture();


		//! 形状データプロパティ
		/*!
		 *	fk_IFSTexture では、形状データとして
		 *	fk_IndexFaceSet クラスのインスタンスを保持しています。
		 *	このプロパティは、そのインスタンスを参照します。
		 *	ここで得たインスタンスに対して形状を操作することで、
		 *	fk_IFSTexture による形状の操作が可能となります。
		 */
		property fk_IndexFaceSet^ IFS {
			fk_IndexFaceSet^ get();
		}

		//! アニメーション時間プロパティ
		/*!
		 *	D3DX形式の入力や BVH データ設定によってアニメーションが設定されていた場合、
		 *	形状を指定した時間に対応する状態に設定します。
		 */
		property double AnimationTime {
			void set(double);
		}
		
		//! BVH データプロパティ
		/*!
		 *	入力した形状データに対し、
		 *	fk_BVHMotion によるのモーションデータを設定します。
		 */
		property fk_BVHMotion^ BVHMotion {
			void set(fk_BVHMotion^);
		}
		
		//! 法線連続性プロパティ
		/*!
		 *	入力する形状に対して法線連続性の参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *
		 *	法線連続性を有効にした場合、
		 *	形状全体に対してスムースシェーディングの効果を有効とします。
		 *	この場合は、各ポリゴン同士の境界がわかりづらくなります。
		 *	法線連続性を無効にした場合、
		 *	ポリゴン同士のスムースシェーディングは行いません。
		 *	そのため、各ポリゴン同士の描画が明確となります。
		 *
		 *	なお、本関数による設定はファイル入力よりも前に行う必要があります。
		 *	既に入力したデータに対しては適用されません。
		 */
		property bool ConnectMode {
			void set(bool);
			bool get();
		}

		//! 初期化関数
		/*!
		 *	テクスチャデータおよびテクスチャ座標のデータを全て破棄し、
		 *	初期化を行います。
		 */
		void Init(void);

		//! テクスチャ座標参照関数
		/*!
		 *	テクスチャ座標を参照します。
		 *
		 *	\param[in]	tID		三角形ID
		 *	\param[in]	vID		頂点ID
		 *
		 *	\return		テクスチャ座標
		 */
		fk_TexCoord^ GetTextureCoord(int tID, int vID);

		//! 形状コピー関数
		/*!
		 *	引数として与えられたインスタンス中の形状やテクスチャデータをコピーします。
		 *
		 *	\param[in]		ifsTex	複写元インスタンス
		 */
		void CloneShape(fk_IFSTexture^ ifsTex);

		//! テクスチャ座標設定関数
		/*!
		 *	テクスチャ座標を設定します。
		 *
		 *	\param[in]	tID		三角形ID
		 *	\param[in]	vID		頂点ID
		 *
		 *	\param[in]	coord	テクスチャ座標
		 */
		void SetTextureCoord(int tID, int vID, fk_TexCoord^ coord);

		//! MQOファイル入力関数1
		/*!
		 *	MQO形式のファイルからデータを入力します。
		 *	本関数で入力できるのは形状とテクスチャ座標データです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *	
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *	\param[in]	materialID
		 *		MQOデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
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
		 *	\sa fk_IFSTexture::readMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID, bool contFlg);

		//! MQOファイル入力関数2
		/*!
		 *	MQO形式のファイルからデータを入力します。
		 *	本関数で入力できるのは形状とテクスチャ座標データです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *	
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本関数は ReadMQOFile(String^, String^, int, bool) において、
		 * 	最後の引数を true にした場合と同義になります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *	\param[in]	materialID
		 *		MQOデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::readMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);

		//! MQOファイル入力関数3
		/*!
		 *	MQO形式のファイルからデータを入力します。
		 *	本関数で入力できるのは形状とテクスチャ座標データです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *	
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本関数は ReadMQOFile(String^, String^, int, bool) において、
		 * 	3番目の引数に -1 を、最後の引数を true にした場合と同義になります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::readMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName);

		//! DirectX (D3DX) ファイル入力関数1
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本関数で入力できるのは形状、テクスチャ座標データ、
		 *	そしてアニメーションデータです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名。
		 *		D3DX 形式では、オブジェクト名を省略することが許容されています。
		 *		そのような場合は、この引数に空文字列 ( "" ) を入れてください。
		 *		この場合、ファイル中で最初に存在するオブジェクトのデータを入力します。
		 *	\param[in]	materialID
		 *		D3DXデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
		 *	
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);

		//! DirectX (D3DX) ファイル入力関数1
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本関数で入力できるのは形状、テクスチャ座標データ、
		 *	そしてアニメーションデータです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本関数は ReadD3DXFile(String^, String^, int) において、
		 *	最後の引数を -1 にした場合と同義になります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名。
		 *		D3DX 形式では、オブジェクト名を省略することが許容されています。
		 *		そのような場合は、この引数に空文字列 ( "" ) を入れてください。
		 *		この場合、ファイル中で最初に存在するオブジェクトのデータを入力します。
		 *	
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName);

		//! 頂点移動関数1
		/*!
		 *	形状の頂点を移動します。 order は通常は 0 を入力してください。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	pos		移動位置ベクトル
		 *	\param[in]	order	全頂点ID のうち、もっとも最小の ID 番号
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool MoveVPosition(int vID, const fk_Vector^ pos, int order);

		//! 頂点移動関数2
		/*!
		 *	形状の頂点を移動します。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	pos		移動位置ベクトル
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool MoveVPosition(int vID, const fk_Vector^ pos);

		//! 頂点移動関数3
		/*!
		 *	形状の頂点を移動します。 order は通常は 0 を入力してください。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	x		移動位置ベクトルの x 成分
		 *	\param[in]	y		移動位置ベクトルの y 成分
		 *	\param[in]	z		移動位置ベクトルの z 成分
		 *	\param[in]	order	全頂点ID のうち、もっとも最小の ID 番号
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool MoveVPosition(int vID, double x, double y, double z, int order);

		//! 頂点移動関数4
		/*!
		 *	形状の頂点を移動します。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	x		移動位置ベクトルの x 成分
		 *	\param[in]	y		移動位置ベクトルの y 成分
		 *	\param[in]	z		移動位置ベクトルの z 成分
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool MoveVPosition(int vID, double x, double y, double z);
	};
}
