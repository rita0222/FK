#ifndef __FK_INDEXFACE_HEADER__
#define __FK_INDEXFACE_HEADER__

#include <FK/FVecArray.H>
#include <FK/ParserBase.H>
#include <FK/ParserData.h>
#include <list>

namespace FK {

	class fk_D3DXAnimation;
	class fk_BVHBase;
	class fk_Solid;

	//! インデックスフェースセットによる任意形状を生成、管理するクラス
	/*!
	 *	このクラスは、
	 *	「インデックスフェースセット」による任意形状を制御する機能を提供します。
	 *
	 *	fk_IndexFaceSet の主な用途は、3次元形状データファイルからデータを読み込み、
	 *	それを表示することです。以下のデータフォーマットをサポートしています。
	 *	- VRML 形式
	 *	- STL 形式
	 *	- SMF 形式
	 *	- HRC 形式
	 *	- RDS (Ray Dream Studio) 形式
	 *	- DXF 形式
	 *	- MQO (Metasequoia) 形式
	 *	- D3DX (DirectX) 形式
	 *
	 *	また、これらのデータファイル入力の他に、
	 *	頂点座標データとインデックスフェースデータから
	 *	形状を自前で生成することも可能です。
	 *	ただし、作成できる形状には制限があります。
	 *	この機能の詳細は makeIFSet() を参照して下さい。
	 *
	 *	入力した形状に対し、各頂点を移動してアニメーションを表現することが可能です。
	 *	この機能の詳細は moveVPosition() を参照して下さい。
	 *	位相変化を伴う変形は、 fk_IndexFaceSet では行うことができません。
	 *	位相変化を伴う変形を行うには、 fk_Solid クラスを用いてください。
	 *
	 *	D3DX 形式ではボーンアニメーションをサポートしていますが、
	 *	その再生を行うことも可能です。
	 *	この機能の詳細は setAnimationTime() を参照して下さい。
	 *	また、ボーンアニメーションデータのみのデータとして BVH 形式を入力し、
	 *	アニメーションをすることも可能になっています。
	 *	この機能の詳細は setBVHMotion() を参照して下さい。
	 *
	 *	任意の形状を表現するクラスとして、
	 *	fk_IndexFaceSet の他に fk_Solid があります。
	 *	fk_IndexFaceSet は、
	 *	fk_Solid と比較して高速な描画が行えるという長所があります。
	 *	しかしその一方で、
	 *	fk_IndexFaceSet は面が3角形か4角形のみ(そして混在は不可)
	 *	という制限があります。
	 *	また、位相変化を伴う変形には対応していません。
	 *	より高度な形状表現や位相変化を伴う変形を利用する場合は
	 *	fk_Solid を利用して下さい。
	 *
	 *	fk_IndexFaceSet 自体は、テクスチャ描画に対応していません。
	 *	テクスチャによる形状描画を行いたい場合は、
	 *	fk_IFSTexture クラスを用いて下さい。
	 *
	 *	\sa fk_IFSTexture, fk_Solid, fk_Shape, fk_Model,
	 *		fk_Block, fk_Circle, fk_Sphere, fk_Prism, fk_Cone, fk_Capsule
	 */

	class fk_IndexFaceSet : public fk_ParserData {

		friend class			fk_PointDraw;
		friend class			fk_LineDraw;
		friend class			fk_FaceDraw;
		friend class			fk_TextureDraw;
		friend class			fk_IFSTexture;

	public:

		//! コンストラクタ
		fk_IndexFaceSet(void);

		//! デストラクタ
		virtual ~fk_IndexFaceSet();


		//! 形状コピー関数
		/*!
		 *	引数として与えられたインスタンス中の形状をコピーします。
		 *	各種属性およびマテリアル情報は写しません。
		 *
		 *	\param[in]		ifs		複写元インスタンス
		 */
		void				cloneShape(fk_IndexFaceSet *ifs);

		//! \name ファイル・データ入力関数
		//@{
		//! SMFファイル入力関数
		/*!
		 *	SMF形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool				readSMFFile(std::string fileName);

		//! VRML ファイル入力関数
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本関数が対応しているのは「IndexedFaceSet」
		 *	ノードに記述された形状のみです。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	materialFlg
		 *		true の場合、
		 *		VRMLファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		入力データのままインデックスフェースセットを構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		VRML形式は、1994年に策定された通称「VRML1.0」と、
		 *		1997年に策定された「VRML97」の2種類があり、
		 *		VRML97は「VRML2.0」とも呼ばれます。
		 *		本関数では入力フォーマットとして VRML2.0 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、
		 *		特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool	readVRMLFile(std::string fileName, bool materialFlg = true, bool solidFlg = true);

		//! STL ファイル入力関数
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *	また、以下の条件に当てはまるデータは
		 *	fk_IndexFaceSet では入力できません。
		 *	- 5以上の角数である面が存在する。
		 *	- 3角形面と4角形面が混在している。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\param[in]	tolerance
		 *		solidFlg で true を指定した場合、
		 *		頂点同士が同一かどうかを判断するための距離許容誤差を指定します。
		 *		solidFlg が false であった場合、この値は無視されます。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool	readSTLFile(std::string fileName, bool solidFlg = true, double tolerance = 1.0e-08);

		//! HRCファイル入力関数
		/*!
		 *	HRC形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool	readHRCFile(std::string fileName);

		//! RDSファイル入力関数
		/*!
		 *	RDS (Ray Dream Studio) 形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool	readRDSFile(std::string fileName, bool solidFlg = true);

		//! DXFファイル入力関数
		/*!
		 *	DXF 形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool	readDXFFile(std::string fileName, bool solidFlg = true);

		//! MQOファイル入力関数1
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	この関数は、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *	\param[in]	contFlg
		 *		テクスチャ断絶の設定を指定します。これは、テクスチャ座標が不連続な箇所に対し、
		 *		形状の位相を断絶する操作を行うためのものです。
		 *		これを true にした場合は断裂操作が行われ、
		 *		テクスチャ座標が不連続な箇所が幾何的にも不連続となるように表示されます。
		 *		ほとんどの場合は、断裂操作を行った方が良好な描画結果となります。
		 *		ただし、断裂操作を行う際に新たな位相要素を生成するため、
		 *		本来のデータよりも頂点、稜線、面が若干増加する場合があります。
		 *		false にした場合は、断裂操作を行わずに通常のデータ通り読み込みます。
		 *	\param[in]	materialFlg
		 *		true の場合、MQOファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa readMQOData(), fk_IFSTexture::readMQOFile()
		 */
		bool	readMQOFile(std::string fileName,
							std::string objName,
							bool solidFlg = true,
							bool contFlg = true,
							bool materialFlg = false);

		//! MQOファイル入力関数2
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	この関数は、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\param[in]	materialID
		 *		MQOデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
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
		 *	\param[in]	materialFlg
		 *		true の場合、MQOファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa readMQOData(), fk_IFSTexture::readMQOFile()
		 */
		bool	readMQOFile(std::string fileName,
							std::string objName,
							int materialID,
							bool solidFlg = true,
							bool contFlg = true,
							bool materialFlg = false);

		//! MQOデータ入力関数1
		/*!
		 *	MQO形式のデータを入力します。
		 *	この関数では、MQO形式のデータが既に
		 *	unsigned char 型の配列中に入力されていると仮定し、
		 *	readMQOFile() 関数と同様の処理を行います。
		 *
		 *	この関数は、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	buffer		データが格納されているバッファ
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
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
		 *	\param[in]	materialFlg
		 *		true の場合、MQOデータ中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa readMQOFile(), fk_IFSTexture::readMQOData()
		 */
		bool	readMQOData(unsigned char *buffer,
							std::string objName,
							bool solidFlg = true,
							bool contFlg = true,
							bool materialFlg = false);

		//! MQOデータ入力関数2
		/*!
		 *	MQO形式のデータを入力します。
		 *	この関数では、MQO形式のデータが既に
		 *	unsigned char 型の配列中に入力されていると仮定し、
		 *	readMQOFile() 関数と同様の処理を行います。
		 *
		 *	この関数は、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	buffer		データが格納されているバッファ
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\param[in]	materialID
		 *		MQOデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
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
		 *	\param[in]	materialFlg
		 *		true の場合、MQOデータ中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa readMQOFile(), fk_IFSTexture::readMQOData()
		 */
		bool	readMQOData(unsigned char *buffer,
							std::string objName,
							int materialID,
							bool solidFlg = true,
							bool contFlg = true,
							bool materialFlg = false);

		//! DirectX (D3DX) ファイル入力関数1
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	この関数で入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名。
		 *		D3DX 形式では、オブジェクト名を省略することが許容されています。
		 *		そのような場合は、この引数に空文字列 ( "" ) を入れてください。
		 *		この場合、ファイル中で最初に存在するオブジェクトのデータを入力します。
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::readD3DXFile()
		 */
		bool				readD3DXFile(std::string fileName,
										 std::string objName,
										 bool solidFlg = true);

		//! DirectX (D3DX) ファイル入力関数2
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	この関数で入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名。
		 *		D3DX 形式では、オブジェクト名を省略することが許容されています。
		 *		そのような場合は、この引数に空文字列 ( "" ) を入れてください。
		 *		この場合、ファイル中で最初に存在するオブジェクトのデータを入力します。
		 *
		 *	\param[in]	materialID
		 *		D3DXデータではマテリアルを複数設定することができ、
		 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
		 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
		 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::readD3DXFile()
		 */
		bool	readD3DXFile(std::string fileName,
							 std::string objName,
							 int materialID,
							 bool solidFlg = true);

		//@}

		//! \name ファイル出力関数
		//@{
		//! VRML ファイル出力関数1
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	material
		 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
		 *		nullptr を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
		 *
		 *	\param[in]	triFlg
		 *		仮想関数からの継承のために存在する引数で、処理には一切影響しません。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool	writeVRMLFile(std::string fileName,
							  fk_Material *material = nullptr,
							  bool triFlg = false);

		//! VRML ファイル出力関数2
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *	この引数形式の場合は、
		 *	CoordinateInterpolator ノードを用いた
		 *	アニメーションデータを出力することが可能です。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	time
		 *		CoordinateInterpolator における時間配列 (key) を入力します。
		 *
		 *	\param[in]	pos
		 *		CoordinateInterpolator における位置ベクトル配列 (keyValue) を入力します。
		 *
		 *	\param[in]	material
		 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
		 *		nullptr を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
		 *
		 *	\param[in]	triFlg
		 *		仮想関数からの継承のために存在する引数で、処理には一切影響しません。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool	writeVRMLFile(std::string fileName,
							  std::vector<double> *time,
							  std::vector<fk_Vector> *pos,
							  fk_Material *material = nullptr,
							  bool triFlg = false);

		//! STL ファイル出力関数
		/*!
		 *	STL 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool	writeSTLFile(std::string fileName);

		//! DXF ファイル出力関数
		/*!
		 *	DXF 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	triFlg
		 *		面情報を3角形として出力したい場合は、true を代入します。
		 *		false の場合、3角形面を2点が重複している4角形面として出力します。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool	writeDXFFile(std::string fileName, bool triFlg = false);

		//! MQO ファイル出力関数
		/*!
		 *	MQO 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool	writeMQOFile(std::string fileName);
		//@}

		//! \name 形状情報参照関数
		//@{

		//! 頂点数参照関数
		/*!
		 *	形状データの頂点数を取得します。
		 *
		 *	\return		頂点数
		 */
		int		getPosSize(void);

		//! 稜線数参照関数
		/*!
		 *	形状データの稜線数を取得します。
		 *
		 *	\return		稜線数
		 */
		int		getEdgeSize(void);

		//! 面数参照関数
		/*!
		 *	形状データの面数を取得します。
		 *
		 *	\return		面数
		 */
		int		getFaceSize(void);

		//! 頂点位置ベクトル参照関数
		/*!
		 *	形状データ中の、頂点の位置ベクトルを取得します。
		 *
		 *	\param[in]	vertexID
		 *		頂点ID。一番最初の頂点IDは 0 になります。
		 *		最後の ID は頂点数から 1 を引いたものとなります。
		 *
		 *	\return		頂点の位置ベクトル
		 *
		 *	\sa moveVPosition()
		 */
		fk_Vector	getPosVec(int vertexID);

		//! 頂点 ID 配列参照関数
		/*!
		 *	面を構成する頂点 ID の配列を取得します。
		 *
		 *	\param[in]	faceID
		 *		面 ID。一番最初の面IDは 0 になります。
		 *		最後の ID は面数から 1 を引いたものとなります。
		 *
		 *	\return		頂点 ID 配列
		 */
		std::vector<int>	getFaceData(int faceID);

		//! 頂点 ID 参照関数
		/*!
		 *	面を構成する頂点 ID を取得します。
		 *
		 *	\param[in]	faceID
		 *		面 ID。一番最初の面IDは 0 になります。
		 *		最後の ID は面数から 1 を引いたものとなります。
		 *
		 *	\param[in]	vertexNum
		 *		面の中での頂点番号。
		 *		3角形であれば 0 から 2、
		 *		4角形であれば 0 から 3 のいずれかを入力すると、
		 *		格納されている頂点 ID を取得できます。
		 *
		 *	\return		頂点 ID
		 */
		int		getFaceData(int faceID, int vertexNum);


		//! 面法線ベクトル取得関数
		/*!
		 *	面の法線ベクトルを取得します。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\param[in]	order
		 *		最初の面IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return		面の法線ベクトル
		 *
		 *	\sa setFaceNorm(), getVertexNorm()
		 */
		fk_Vector	getFaceNorm(int faceID, int order = 0);

		//! 頂点法線ベクトル取得関数
		/*!
		 *	頂点の法線ベクトルを取得します。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return		頂点の法線ベクトル
		 *
		 *	\sa setVertexNorm(), getFaceNorm()
		 */
		fk_Vector	getVertexNorm(int vertexID, int order = 0);

		//@}

		//! \name 汎用形状操作関数
		//@{

		//! 頂点移動関数1
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 setVertexNorm() によって法線ベクトルが設定されていた場合や、
		 *	setFaceNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	この関数によって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	pos				移動先の位置ベクトル
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa getPosVec()
		 */
		bool	moveVPosition(int vertexID, const fk_Vector &pos, int order = 0);

		//! 頂点移動関数2
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 setVertexNorm() によって法線ベクトルが設定されていた場合や、
		 *	setFaceNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	この関数によって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *	\param[in]	x				移動先位置ベクトルの x 成分
		 *	\param[in]	y				移動先位置ベクトルの y 成分
		 *	\param[in]	z				移動先位置ベクトルの z 成分
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa getPosVec()
		 */
		bool	moveVPosition(int vertexID, double x, double y, double z, int order = 0);

		//! 頂点移動関数3
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 setVertexNorm() によって法線ベクトルが設定されていた場合や、
		 *	setFaceNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	この関数によって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	array
		 *		移動先位置ベクトルの各成分が入った double 型配列。
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa getPosVec()
		 */
		bool	moveVPosition(int vertexID, double *array, int order = 0);

		//! 任意形状生成関数1
		/*!
		 *	与えられたインデックスフェースセット情報から、形状を生成します。
		 *
		 *	\param[in]	faceNum		面数
		 *
		 *	\param[in]	polyNum
		 *		面の角数。現在、ここに入力できる数値は 3 か 4 のみです。
		 *
		 *	\param[in]	IFSet
		 *		インデックスフェースセット配列。
		 *		この配列は、各面を構成する頂点 ID を並べたものになります。
		 *		たとえば、頂点 ID が [0, 1, 2] と [2, 1, 3] という構成を持つ
		 *		2面からなる形状を生成する場合、
		 *		int 型の配列に対して [0, 1, 2, 2, 1, 3] という数値を入力しておきます。
		 *		4角形の場合も同様です。
		 *		結果的に、この配列の長さは面数と角数を掛けたもの以上である必要があります。
		 *
		 *	\param[in]	vertexNum	頂点数
		 *
		 *	\param[in]	posArray
		 *		頂点位置ベクトルの配列。配列の長さは頂点数以上である必要があります。
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\sa fk_Solid
		 */
		void	makeIFSet(int faceNum,
						  int polyNum,
						  int *IFSet,
						  int vertexNum,
						  fk_Vector *posArray,
						  int order = 0);

		//! 任意形状生成関数2
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *
		 *	\param[in]	faceArray
		 *		面データ配列。
		 *		IFSet を vector< vector<int> > 型、
		 *		polygon を vector<int> 型としたとき、
		 *		以下のようにして面データを生成していきます。
		 *
		 *			polygon.clear();
		 *			polygon.push_back(頂点ID1);
		 *			polygon.push_back(頂点ID2);
		 *				:
		 *			polygon.push_back(頂点IDn);
		 *			IFSet.push_back(polygon);
		 *
		 *	\param[in]	posArray	頂点位置ベクトルデータ配列
		 *	\param[in]	order		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 */
		void		makeIFSet(std::vector< std::vector<int> > *faceArray,
							  std::vector<fk_Vector> *posArray,
							  int order = 0);

		//! 面法線ベクトル設定関数
		/*!
		 *	面の法線ベクトルを設定します。
		 *
		 *	通常、面の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、この関数を用います。
		 *
		 *	なお、 moveVPosition() 関数によって面上の点が移動された場合、
		 *	設定した法線ベクトルは破棄されます。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\param[in]	norm
		 *		法線ベクトル。あらかじめ正規化しておく必要があります。
		 *		正規化されていない放線ベクトルを入力した場合、
		 *		動作が異常となる場合があります。
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa getFaceNorm(), setVertexNorm()
		 */
		bool	setFaceNorm(int faceID, const fk_Vector &norm, int order = 0);

		//! 頂点法線ベクトル設定関数
		/*!
		 *	頂点の法線ベクトルを設定します。
		 *
		 *	通常、頂点の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、この関数を用います。
		 *
		 *	なお、 moveVPosition() 関数によって頂点が移動された場合、
		 *	設定した法線ベクトルは破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	norm
		 *		法線ベクトル。あらかじめ正規化しておく必要があります。
		 *		正規化されていない放線ベクトルを入力した場合、
		 *		動作が異常となる場合があります。
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa getVertexNorm(), setFaceNorm()
		 */
		bool	setVertexNorm(int vertexID, const fk_Vector &norm, int order = 0);

		//! 法線ベクトル強制計算関数 
		/*!
		 *	fk_IndexFaceSet では、
		 *	面や頂点の法線ベクトルは形状生成した時点ではまだ算出しません。
		 *	描画時など、実際に法線ベクトルが必要となった場合に随時計算が行われます。
		 *	この仕様は、必ずしも法線ベクトルを必要としない状況において
		 *	計算量を削減する効果がありますが、
		 *	一方でアプリケーションの実行において不都合を生じる場合があります。
		 *	例えば、対象形状が初めてシーンに登録された時点で
		 *	画面が一瞬止まってしまうといった状況が想定されます。
		 *
		 *	この関数は、形状中のすべての面と頂点に対して法線ベクトルを強制的に算出します。
		 *	なお、 setFaceNorm() や setVertexNorm() で設定した法線ベクトルは全て破棄されます。
		 *
		 *	\sa getFaceNorm(), getVertexNorm(), setFaceNorm(), setVertexNorm()
		 */
		void	flush(void);

		//@}

		//! \name 直方体形状制御関数
		//@{
		//! 直方体生成関数
		/*!
		 *	直方体を生成します。
		 *
		 *	直方体は、原点の物体の中心が来るように配置されます。
		 *	従って、(x, y, z) という大きさで直方体を生成した場合、
		 *	各頂点の位置ベクトルは以下のようになります。
		 *	- (x/2, y/2, z/2)
		 *	- (-x/2, y/2, z/2)
		 *	- (-x/2, -y/2, z/2)
		 *	- (x/2, -y/2, z/2)
		 *	- (x/2, y/2, -z/2)
		 *	- (-x/2, y/2, -z/2)
		 *	- (-x/2, -y/2, -z/2)
		 *	- (x/2, -y/2, -z/2)
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa fk_Block
		 */
		void	makeBlock(double x, double y, double z);

		//! 直方体辺長変更関数
		/*!
		 *	makeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を一括して設定しなおします。
		 *	この関数は、 makeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa makeBlock(), fk_Block
		 */
		void	setBlockSize(double x, double y, double z);

		//! 直方体個別辺長設定関数
		/*!
		 *	makeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を個別に設定します。
		 *	この関数は、 makeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	length	辺長
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_X x方向
		 *		- fk_Y y方向
		 *		- fk_Z z方向
		 *
		 *	\sa makeBlock(), fk_Block
		 */
		void	setBlockSize(double length, fk_Axis axis);

		//! 直方体全体拡大縮小関数
		/*!
		 *	makeBlock() によって直方体を生成した後に、
		 *	直方体全体を指定された倍率で拡大・縮小します。
		 *	この関数は、 makeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa makeBlock(), fk_Block
		 */
		void	setBlockScale(double scale);

		//! 直方体軸方向拡大縮小関数
		/*!
		 *	makeBlock() によって直方体を生成した後に、
		 *	指定された軸方向についてのみ拡大・縮小します。
		 *	この関数は、 makeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_X x方向
		 *		- fk_Y y方向
		 *		- fk_Z z方向
		 *
		 *	\sa makeBlock(), fk_Block
		 */
		void	setBlockScale(double scale, fk_Axis axis);

		//! 直方体軸方向個別拡大縮小関数
		/*!
		 *	makeBlock() によって直方体を生成した後に、
		 *	各軸方向に対し個別の倍率で拡大・縮小します。
		 *	この関数は、 makeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の倍率
		 *	\param[in]	y	y方向の倍率
		 *	\param[in]	z	z方向の倍率
		 *
		 *	\sa makeBlock(), fk_Block
		 */
		void	setBlockScale(double x, double y, double z);
		//@}

		//! \name 円形状制御関数
		//@{
		//! 円形状生成関数
		/*!
		 *	円形状を生成します。
		 *
		 *	ここでの「円」は実際には正多角形を円に近似して扱っています。
		 *	多角形の角数は (分割数) * 4 となっています。
		 *	この多角形は、実質的には設定された半径の円に内接するものです。
		 *	円としての見栄えを良くするには分割数を大きめに設定すべきですが、
		 *	分割数の大きい円を大量に利用すると描画処理が遅くなるという問題が生じます。
		 *
		 *	初期状態では、中心を原点とし、
		 *	面の法線ベクトルが (0, 0, 1) となるように配置されます。
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div	分割数。実際には円弧全体をこの数値の 4 倍で分割します。
		 *	\param[in]	rad	半径
		 *
		 *	\sa fk_Circle
		 */
		void	makeCircle(int div, double rad);

		//! 円形状半径設定関数
		/*!
		 *	makeCircle() によって円形状を生成した後に、
		 *	半径を設定しなおします。
		 *	この関数は、 makeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa makeCircle(), fk_Circle
		 */
		void	setCircleRadius(double rad);

		//! 円形状分割数設定関数
		/*!
		 *	makeCircle() によって円形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	この関数は、 makeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa makeCircle(), fk_Circle
		 */
		void	setCircleDivide(int div);

		//! 円形状拡大縮小関数
		/*!
		 *	makeCircle() によって円形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	この関数は、 makeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa makeCircle(), fk_Circle
		 */
		void	setCircleScale(double scale);
		//@}

		//! \name 球形状制御関数
		//@{
		//! 球形状生成関数
		/*!
		 *	球形状を生成します。
		 *
		 *	実際には、球を近似する3角形面集合として表現されています。
		 *	3角形面の数は分割数を \f$ d \f$ とした場合 \f$ 8d(d-1) \f$ 枚となります。
		 *	分割数が高いほど球としての描画精度は高くなりますが、
		 *	面数も多くなるため描画速度が低下することになります。
		 *	特に多くのオブジェクトを同時に配置する場合は注意が必要です。
		 *
		 *	初期状態では、中心を原点とするように配置されます。
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *	
		 *	\param[in]	div	分割数
		 *	\param[in]	rad	半径
		 *
		 *	\sa fk_Sphere
		 */
		void	makeSphere(int div, double rad);

		//! 球形状半径設定関数
		/*!
		 *	makeSphere() によって球形状を生成した後に、
		 *	半径を設定しなおします。
		 *	この関数は、 makeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa makeSphere(), fk_Sphere
		 */
		void	setSphereRadius(double rad);

		//! 球形状分割数設定関数
		/*!
		 *	makeSphere() によって球形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	この関数は、 makeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa makeSphere(), fk_Sphere
		 */
		void	setSphereDivide(int div);

		//! 球形状拡大縮小関数
		/*!
		 *	makeSphere() によって球形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	この関数は、 makeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa makeSphere(), fk_Sphere
		 */
		void	setSphereScale(double scale);
		//@}

		//! \name 正多角柱(円柱)形状制御関数
		//@{
		//! 正多角柱(円柱)形状生成関数
		/*!
		 *	正多角柱(円柱)を生成します。
		 *
		 *	円柱は、分割数の多い正多角柱として生成します。
		 *	通常、分割数が 20 を超える程度でほとんど円柱と見分けがつかなくなります。
		 *	配置は、底面の中心が原点となり、
		 *	多角柱の上面が -z 方向、底面が +z 方向となります。
		 *
		 *	設定できる要素は角数、上面半径、底面半径、高さの4要素です。
		 *	上面と底面の半径とは、それぞれの面を構成する正多角形の外接円半径を指します。
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	top		上面半径
		 *	\param[in]	bottom	底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Prism
		 */
		void	makePrism(int div, double top, double bottom, double height);

		//! 正多角柱(円柱)角数設定関数
		/*!
		 *	makePrism() によって正多角柱(円柱)を生成した後に、
		 *	角数を設定しなおします。
		 *	この関数は、 makePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa makePrism(), fk_Prism
		 */
		void	setPrismDivide(int div);

		//! 正多角柱(円柱)上面半径設定関数
		/*!
		 *	makePrism() によって正多角柱(円柱)を生成した後に、
		 *	上面の外接円半径を設定しなおします。
		 *	この関数は、 makePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	top	上面半径
		 *
		 *	\sa makePrism(), fk_Prism
		 */
		void	setPrismTopRadius(double top);

		//! 正多角柱(円柱)角数設定関数
		/*!
		 *	makePrism() によって正多角柱(円柱)を生成した後に、
		 *	底面の外接円半径を設定しなおします。
		 *	この関数は、 makePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	bottom	底面半径
		 *
		 *	\sa makePrism(), fk_Prism
		 */
		void	setPrismBottomRadius(double bottom);

		//! 正多角柱(円柱)高さ設定関数
		/*!
		 *	makePrism() によって正多角柱(円柱)を生成した後に、
		 *	高さを設定しなおします。
		 *	この関数は、 makePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height	高さ
		 *
		 *	\sa makePrism(), fk_Prism
		 */
		void	setPrismHeight(double height);
		//@}

		//! \name 正多角錐(円錐)形状制御関数
		//@{
		//! 正多角錐(円錐)形状生成関数
		/*!
		 *	正多角錐(円錐)を生成します。
		 *
		 *	円錐は、分割数の多い正多角錐として生成します。
		 *	通常、分割数が 20 を超える程度でほとんど円錐と見分けがつかなくなります。
		 *	配置は、底面の中心が原点となり、
		 *	頂点 -z 方向、底面が +z 方向となります。
		 *
		 *	設定できる要素は角数、底面半径、高さの3要素です。
		 *	底面半径とは、面を構成する正多角形の外接円半径を指します。
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	rad		底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Cone
		 */
		void	makeCone(int div, double rad, double height);

		//! 正多角錐(円錐)角数設定関数
		/*!
		 *	makeCone() によって正多角錐(円錐)を生成した後に、
		 *	角数を設定しなおします。
		 *	この関数は、 makeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa makeCone(), fk_Cone
		 */
		void	setConeDivide(int div);

		//! 正多角錐(円錐)底面半径設定関数
		/*!
		 *	makeCone() によって正多角錐(円錐)を生成した後に、
		 *	底面外接円半径を設定しなおします。
		 *	この関数は、 makeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad		底面半径
		 *
		 *	\sa makeCone(), fk_Cone
		 */
		void	setConeRadius(double rad);

		//! 正多角錐(円錐)高さ設定関数
		/*!
		 *	makeCone() によって正多角錐(円錐)を生成した後に、
		 *	高さを設定しなおします。
		 *	この関数は、 makeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height		高さ
		 *
		 *	\sa makeCone(), fk_Cone
		 */
		void	setConeHeight(double height);
		//@}

		//! \name カプセル型形状制御関数
		//@{
		//! カプセル型形状生成関数
		/*!
		 *	カプセル型を生成します。
		 *	カプセル型は半径の等しい円柱側面と半球面によって構成されています。
		 *	数学的には、カプセル型の内部は1本の線分より一定距離以下の部分の集合であり、
		 *	その一定距離は前述の半径と等しくなります。この線分を「中心軸」と呼びます。
		 *	初期状態は中心軸の中点が原点に配置され、z軸方向と中心軸が平行となります。
		 *	設定できる要素は中心軸長、半径、分割数です。
		 *	実際のカプセル型の全長は「中心軸長 + (半径)*2」となります。
		 *
		 *	この関数を呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		分割数
		 *	\param[in]	len		中心軸長
		 *	\param[in]	rad		半径
		 *
		 *	\sa fk_Capsule
		 */
		void	makeCapsule(int div, double len, double rad);

		//! カプセル型形状寸法設定関数
		/*!
		 *	makeCapsule() によってカプセル型形状を生成した後に、
		 *	中心軸長と半径を再度設定します。
		 *	この関数は、 makeCapsule() によってカプセル型形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこの関数を呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	len		中心軸長
		 *	\param[in]	rad		半径
		 *
		 *	\sa makeCapsule(), fk_Capsule
		 */
		void	setCapsuleSize(double len, double rad);
		//@}

		//! \name その他
		//@{

		//! fk_Solid 出力関数
		/*!
		 *	fk_IndexFaceSet 型にある形状情報を、
		 *	fk_Solid 型のインスタンスにコピーします。
		 *	fk_Solid 側に格納されている形状情報や属性情報は破棄されます。
		 *	なお、マテリアル情報や法線ベクトル情報はコピーされません。
		 *
		 *	\param[in]	solid		fk_Solid 型インスタンスのアドレス
		 *
		 *	\sa fk_Solid
		 */
		void	putSolid(fk_Solid *solid);

		//! アニメーション時間設定関数
		/*!
		 *	D3DX形式からの入力や、
		 *	BVH情報からの入力によってアニメーションが設定されている場合、
		 *	この関数を用いることで形状状態を任意のアニメーション時間に設定することができます。
		 *
		 *	\param[in]	time		アニメーション時間
		 *
		 *	\sa readD3DXFile(), setBVHMotion(), fk_BVHMotion
		 */
		void	setAnimationTime(double time);

		//! BVHデータ設定関数
		/*!
		 *	形状に対し、BVH 形式によるアニメーションを設定します。
		 *
		 *	\param[in]	bvh	   	fk_BVHMotion 型インスタンスのアドレス
		 *
		 *	\sa setAnimationTime(), readD3DXFile(), fk_BVHMotion
		 */
		void	setBVHMotion(fk_BVHBase *bvh);
		//@}

#ifndef FK_DOXYGEN_USER_PROCESS

		bool	MakeMesh(std::vector<fk_Vector> *,
						 std::vector< std::vector<int> > *, bool = true);


		fk_D3DXAnimation *	GetAnimation(void);

		void	DataPrint(void);

		void	EdgeIBOSetup(void);
		void	FaceIBOSetup(void);

		int		getElemMaterialID(int);
		bool	setElemMaterialID(int, int);
		void	forceUpdateAttr(void);

		fk_Vector	getPNorm(int faceID, int order = 0);
		fk_Vector	getVNorm(int vertexID, int order = 0);
		bool	setPNorm(int faceID, const fk_Vector &norm, int order = 0);
		bool	setVNorm(int vertexID, const fk_Vector &norm, int order = 0);

		void	updateAttr(void);

#endif

	private:

		fk_FVecArray					vertexPosition;
		fk_FVecArray					timeOrgPosition;
		fk_FVecArray					vertexNormal;
		fk_FVecArray					faceNormal;
		std::vector<GLuint>				edgeIndex;
		std::vector<GLuint>				faceIndex;
		std::vector< std::vector<int> >	loopStack;
		//bool							modifyFlg;
		//bool							edgeModifyFlg;
		std::vector<int>				modifyList;
		fk_D3DXAnimation				*anim;

		bool							cloneFlg;
		std::list<fk_IndexFaceSet *>	cloneList;
		fk_IndexFaceSet					*orgIFS;

		// 編集があった場合に true, ない場合 false
		bool				edgeIndexFlg, faceIndexFlg;
		std::vector<char>	faceNormFlg;
		std::vector<char>	vertexNormFlg;

		GLuint				edgeIBO, faceIBO;

		void				InitFaceNorm(void);
		void				InitVertexNorm(void);

		void				ModifyFaceNorm(void);
		void				ModifyVertexNorm(void);

		void				MakeFaceNorm(int);

		void				ResetFaceFlg(void);
		void				ResetVertexFlg(void);

		fk_FVector			CalcTriNorm(GLuint *);
		fk_FVector			CalcPolyNorm(int, int *);
		void				MakeLoopTable(void);
		void				MakeEdgeSet(std::vector< std::vector<int> > *);

		void				Init(void);

		void				DeleteCloneLink(fk_IndexFaceSet *);

		void				MakeCapsuleVec(std::vector<fk_Vector> *, int, double, double);
		void				MakeCapsuleIFSet(std::vector< std::vector<int> > *, int);
	};
}

#endif // !__FK_INDEXFACE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
