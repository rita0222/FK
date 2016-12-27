#ifndef __FK_IFS_TEXTURE_HEADER__
#define __FK_IFS_TEXTURE_HEADER__

#include <FK/Texture.h>

namespace FK {

	class fk_IndexFaceSet;
	class fk_BVHMotion;

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

	class fk_IFSTexture : public fk_Texture {

		friend class			fk_TextureDraw;

	public:

		//! コンストラクタ
		/*!
		 *	引数によってテクスチャ画像を設定することが可能です。
		 *
		 *	\param[in]	image
		 *		テクスチャデータ。
		 *		省略されるか、nullptr が代入された場合はテクスチャデータを空の状態として生成します。
		 */
		fk_IFSTexture(fk_Image *image = nullptr);

		//! デストラクタ
		virtual ~fk_IFSTexture();

		//! 初期化関数
		/*!
		 *	テクスチャデータおよびテクスチャ座標のデータを全て破棄し、
		 *	初期化を行います。
		 */
		void					init(void);

		//! テクスチャ座標参照関数
		/*!
		 *	テクスチャ座標を参照します。
		 *
		 *	\param[in]	tID		三角形ID
		 *	\param[in]	vID		頂点ID
		 *
		 *	\return		テクスチャ座標
		 */
		fk_TexCoord				getTextureCoord(int tID, int vID);

		//! 形状データ参照関数
		/*!
		 *	fk_IFSTexture では、形状データとして
		 *	fk_IndexFaceSet クラスのインスタンスを保持しています。
		 *	この関数は、そのインスタンスのポインタを返します。
		 *	ここで得たインスタンスに対して形状を操作することで、
		 *	fk_IFSTexture による形状の操作が可能となります。
		 *
		 *	\return		fk_IndexFaceSet 型の形状データのポインタ
		 */
		fk_IndexFaceSet *		getIFS(void);

		//! 形状コピー関数
		/*!
		 *	引数として与えられたインスタンス中の形状やテクスチャデータをコピーします。
		 *
		 *	\param[in]		ifsTex	複写元インスタンス
		 */
		void				cloneShape(fk_IFSTexture *ifsTex);

		//! テクスチャ座標設定関数
		/*!
		 *	テクスチャ座標を設定します。
		 *
		 *	\param[in]	tID		三角形ID
		 *	\param[in]	vID		頂点ID
		 *
		 *	\param[in]	coord	テクスチャ座標
		 */
		void					setTextureCoord(int tID, int vID,
												fk_TexCoord &coord);

		//! MQOファイル入力関数
		/*!
		 *	MQO形式のファイルからデータを入力します。
		 *	この関数で入力できるのは形状とテクスチャ座標データです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *	
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
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
		 *	\sa readMQOData(), fk_IFSTexture::readMQOFile()
		 */
		bool					readMQOFile(std::string fileName,
											std::string objName,
											int materialID = -1,
											bool contFlg = true);

		//! MQOデータ入力関数
		/*!
		 *	MQO形式のデータを入力します。
		 *	この関数では、MQO形式のデータが既に
		 *	unsigned char 型の配列中に入力されていると仮定し、
		 *	readMQOFile() 関数と同様の処理を行います。
		 *
		 *	この関数で入力できるのは形状とテクスチャ座標データです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *	
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	buffer		データが格納されているバッファ
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
		 *	\return データ入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 * 	\sa readMQOFile(), fk_IndexFaceSet::readMQOData()
		 */
		bool					readMQOData(unsigned char *buffer,
											std::string objName,
											int materialID = -1,
											bool contFlg = true);

		//! DirectX (D3DX) ファイル入力関数
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	この関数で入力できるのは形状、テクスチャ座標データ、
		 *	そしてアニメーションデータです。
		 *	テクスチャ画像データは fk_Texture のメンバ関数によって、
		 *	別途入力する必要があります。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
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
		bool					readD3DXFile(std::string fileName,
											 std::string objName,
											 int materialID = -1);

		//! 法線連続性設定関数
		/*!
		 *	入力する形状に対して法線連続性の設定を行います。
		 *	法線連続性を有効にした場合、
		 *	形状全体に対してスムースシェーディングの効果を有効とします。
		 *	この場合は、各ポリゴン同士の境界がわかりづらくなります。
		 *	法線連続性を無効にした場合、
		 *	ポリゴン同士のスムースシェーディングは行いません。
		 *	そのため、各ポリゴン同士の描画が明確となります。
		 *
		 *	なお、この関数による設定はファイル入力よりも前に行う必要があります。
		 *	既に入力したデータに対しては適用されません。
		 *
		 *	\param[in]	connectFlg
		 *		true の場合、法線連続性が有効となります。false の場合は無効となります。
		 *
		 *	\sa getConnectMode()
		 */
		void					setConnectMode(bool connectFlg);

		//! 法線連続性設定関数
		/*!
		 *	法線連続性の設定を参照します。
		 *	法線連続性の詳細については、 setConnectMode() を参照して下さい。
		 *
		 *	\return true の場合、法線連続性が有効であることを意味します。
		 *		false の場合は無効であることを意味します。
		 *
		 *	\sa setConnectMode()
		 */
		bool					getConnectMode(void);

		//! 頂点移動関数1
		/*!
		 *	形状の頂点を移動します。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	pos		移動位置ベクトル
		 *	\param[in]	order	全頂点ID のうち、もっとも最小の ID 番号
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool					moveVPosition(int vID,
											  const fk_Vector &pos,
											  int order = 0);

		//! 頂点移動関数2
		/*!
		 *	形状の頂点を移動します。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	x		移動位置ベクトルの x 成分
		 *	\param[in]	y		移動位置ベクトルの y 成分
		 *	\param[in]	z		移動位置ベクトルの z 成分
		 *	\param[in]	order	全頂点ID のうち、もっとも最小の ID 番号
		 *
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool					moveVPosition(int vID,
											  double x,
											  double y,
											  double z,
											  int order = 0);

		//! 頂点移動関数3
		/*!
		 *	形状の頂点を移動します。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	pos		移動位置ベクトルを示す double 型配列の先頭アドレス。
		 *	\param[in]	order	全頂点ID のうち、もっとも最小の ID 番号
		 *	\return	頂点移動が成功したら true を、失敗したら false を返します。
		 */
		bool					moveVPosition(int vID,
											  double *pos,
											  int order = 0);

		//! アニメーション時間設定関数
		/*!
		 *	D3DX形式の入力や BVH データ設定によってアニメーションが設定されていた場合、
		 *	形状を指定した時間に対応する状態に設定します。
		 *
		 *	\param[in]	t		時間
		 */
		void					setAnimationTime(double t);

		//! BVH データ設定関数
		/*!
		 *	入力した形状データに対し、
		 *	fk_BVHMotion によるのモーションデータを設定します。
		 *
		 *	\param[in]	bvh		モーションデータ
		 */
		void					setBVHMotion(fk_BVHBase *bvh);

#ifndef FK_DOXYGEN_USER_PROCESS
		std::vector< std::vector<int> > * GetCommonList(void);
#endif
	   
	private:

		fk_IndexFaceSet						*ifs;
		std::vector<fk_TexCoord>			coordArray;
		std::vector< std::vector<int> >		commonList;
		bool								connectMode;

		void	SetConnectNormal(void);
	};
}

#endif // !__FK_IFS_TEXTURE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
