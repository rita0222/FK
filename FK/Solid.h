/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_SOLID_HEADER__
#define __FK_SOLID_HEADER__

#include <FK/SolidBase.h>
#include <FK/FileBase.h>

class fk_DataBase;

//! 半稜線構造 (Half-Edge Structure) による任意形状を生成、管理するクラス
/*!
 *	このクラスは、半稜線構造 (Half-Edge Structure)
 *	による任意形状を制御する機能を提供します。
 *
 *	fk_Solid は様々な機能を持つ形状制御用クラスです。
 *	fk_Solid 型のインスタンスが利用を想定している機能は、
 *	実際には多くの基底クラスにて定義されています。
 *	fk_Solid で直接定義されている関数は、
 *	ほとんどが様々な3次元形状用ファイルフォーマットに対応した入出力機能となります。
 *	その他、以下のようなような機能はそれぞれのクラスのマニュアルを参照して下さい。
 *	- 位相に対する基本的な参照機能は、 fk_DataAccess を参照して下さい。
 *	- 形状の高度な参照に関する機能は、
 *		fk_ReferenceL1, fk_ReferenceL2, fk_ReferenceL3 を参照して下さい。
 *	- 形状の基本操作である「オイラー操作」に関する機能は、
 *		fk_Operation を参照して下さい。
 *	- 形状の高度な操作については、 fk_Modify を参照して下さい。
 *	- インデックスフェースセットデータからの生成については、
 *		fk_SolidBase を参照して下さい。
 *	- マテリアルの位相別設定に関する機能は、 fk_Shape を参照して下さい。
 *	- 位相や形状に対しての独自属性設定に関する機能は、 fk_Attribute を参照して下さい。
 *	.
 *
 *	3次元形状データファイルの入出力については、以下の形式をサポートしています。
 *	- 入力
 *		- VRML 形式
 *		- STL 形式
 *		- SMF 形式
 *		- HRC 形式
 *		- RDS (Ray Dream Studio) 形式
 *		- DXF 形式
 *		- MQO (Metasequoia) 形式
 *		- D3DX (DirectX) 形式
 *		- 独自形式
 *		.
 *	- 出力
 *		- VRML 形式
 *		- STL 形式
 *		- DXF 形式
 *		- MQO (Metasequoia) 形式
 *	   	- 独自形式
 *		.
 *	.
 *	任意の形状を表現するクラスとして、 fk_Solid の他に fk_IndexFaceSet があります。
 *	fk_IndexFaceSet は、 fk_Solid と比較して高速な描画が行えるという長所があります。
 *	しかしその一方で、
 *	fk_IndexFaceSet は面が3角形か4角形のみ(そして混在は不可)という制限があります。
 *	また、位相変化を伴う変形には対応していません。
 *	より高度な形状表現や位相変化を伴う変形を利用する場合は fk_Solid を利用して下さい。
 *
 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model,
 *		fk_ReferenceL1, fk_ReferenceL2, fk_ReferenceL3, fk_DataAccess,
 *		fk_Operation, fk_Modify, fk_SolidBase,
 *		fk_Shape, fk_Attribute
 *
 */

class fk_Solid : public fk_SolidBase {
 private:

	fk_DataBase			*SolidDB;
	fk_Palette			localPal;

 public:

	//! コンストラクタ
	fk_Solid(void);

	//! デストラクタ
	virtual ~fk_Solid();

	//! 形状初期化関数
	/*!
	 *	インスタンスに設定されている形状と独自属性を全て消去し、
	 *	データの初期化を行います。
	 *
	 *	\param[in]	matFlg
	 *		true の場合、インスタンス中に設定されていたマテリアルに関する情報も
	 *		合わせて消去します。false の場合、マテリアル情報は存続させます。
	 */
	void				allClear(bool matFlg = true);

	//! 空形状状態参照関数
	/*!
	 *	形状情報が空かどうかを参照します。
	 *
	 *	\return		形状情報が空の場合 true を、そうでない場合は false を返します。
	 */
	bool				isEmpty(void);

	//! 形状コピー関数
	/*!
	 *	引数として与えられたインスタンス中の形状をコピーします。
	 *	各種属性およびマテリアル情報は写しません。
	 *
	 *	\param[in]		solid		複写元インスタンス
	 */
	void				cloneShape(fk_Solid *solid);

	//! 形状同値比較関数
	/*!
	 *	引数として与えられたインスタンス中の形状と、同じ状態かどうかを比較します。
	 *	ここでいう「同じ」とは、全ての位相要素の ID も一致している状態を指します。
	 *	幾何的には同一であるが位相要素の ID が異なるケースでは「同じ」とは判断しません。
	 *
	 *	\param[in]		solid		比較インスタンス
	 *
	 *	\return		同じであれば true を、異なれば false を返します。
	 */
	bool				compareShape(fk_Solid *solid);

	//! \name ファイル入力関数
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

	//! SRFファイル入力関数
	/*!
	 *	SRF形式のファイルからデータを入力します。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readSRFFile(std::string fileName);

	//! VRML ファイル入力関数
	/*!
	 *	VRML形式のファイルからデータを入力します。
	 *	VRMLでは、形状を表す様々なノードがありますが、
	 *	本関数が対応しているのは「IndexedFaceSet」ノードに記述された形状のみです。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	materialFlg
	 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
	 *		false の場合は、マテリアル情報を無視します。
	 *	\param[in]	solidFlg
	 *		true の場合、位相の隣接関係を最適化します。
	 *		ただし、結果として入力に失敗する場合があります。
	 *		false の場合は隣接関係を最適化せず、
	 *		入力データのままインデックスフェースセットを構築します。
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 *
	 *	\note
	 *	VRML形式は、1994年に策定された通称「VRML1.0」と、
	 *	1997年に策定された「VRML97」の2種類があり、
	 *	VRML97は「VRML2.0」とも呼ばれます。
	 *	本関数では入力フォーマットとして VRML97 を想定しています。
	 *	\note
	 *	VRMLは文法解釈、特にセパレータの扱い方についてはあまり厳密になっておらず、
	 *	様々なデータによって異なる解釈がなされているようです。
	 *	そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
	 */
	bool				readVRMLFile(std::string fileName,
									 bool materialFlg = true,
									 bool solidFlg = true);

	//! STL ファイル入力関数
	/*!
	 *	STL形式のファイルからデータを入力します。
	 *	対応しているのは面データのみです。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	solidFlg
	 *		true の場合、位相の隣接関係を最適化します。
	 *		ただし、結果として入力に失敗する場合があります。
	 *		false の場合は隣接関係を最適化せず、
	 *		すべての面が独立した状態として形状を構築します。
	 *	\param[in]	tolerance
	 *		solidFlg で true を指定した場合、
	 *		頂点同士が同一かどうかを判断するための距離許容誤差を指定します。
	 *		solidFlg が false であった場合、この値は無視されます。
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readSTLFile(std::string fileName,
									bool solidFlg = true,
									double tolerance = 1.0e-08);

	//! HRCファイル入力関数
	/*!
	 *	HRC形式のファイルからデータを入力します。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readHRCFile(std::string fileName);

	//! RDSファイル入力関数
	/*!
	 *	RDS (Ray Dream Studio) 形式のファイルからデータを入力します。
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
	bool				readRDSFile(std::string fileName,
									bool solidFlg = true);

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
	bool				readDXFFile(std::string fileName,
									bool solidFlg = true);

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
	 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
	 *		false の場合は、マテリアル情報を無視します。
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readMQOFile(std::string fileName,
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
	 *	\param[in]	objName		オブジェクト名
	 *	\param[in]	materialID
	 *		MQOデータではマテリアルを複数設定することができ、
	 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
	 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
	 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
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
	 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
	 *		false の場合は、マテリアル情報を無視します。
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readMQOFile(std::string fileName,
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
	 *	fk_Solid クラスではなく fk_IFSTexture クラスを利用して下さい。
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
	 *	fk_Solid クラスではなく fk_IFSTexture クラスを利用して下さい。
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
	 *	\param[in]	solidFlg
	 *		true の場合、位相の隣接関係を最適化します。
	 *		ただし、結果として入力に失敗する場合があります。
	 *		false の場合は隣接関係を最適化せず、
	 *		すべての面が独立した状態として形状を構築します。
	 *	\param[in]	materialID
	 *		D3DXデータではマテリアルを複数設定することができ、
	 *		各ポリゴンに対してどのマテリアルを割り振るかのIDが設定されています。
	 *		この引数にマテリアルIDを指定すると、そのIDを持つポリゴンのみを読み込みます。
	 *		materialID に -1 を入力した場合は、すべてのポリゴンを読み込みます。
	 *
	 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
	 *
	 *	\sa fk_IFSTexture::readD3DXFile()
	 */
	bool				readD3DXFile(std::string fileName,
									 std::string objName,
									 int materialID,
									 bool solidFlg = true);

	//! 独自形式ファイル入力関数
	/*!
	 *	独自形式のファイルからデータを入力します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	sizeMode
	 *		旧バージョンとの互換性のために存在する引数です。
	 *		通常は true とするか、省略して下さい。
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				readData(std::string fileName,
								 bool sizeMode = true);
	//@}

	//! \name ファイル出力関数
	//@{
	//! VRML ファイル出力関数1
	/*!
	 *	VRML (VRML2.0) 形式で形状データを出力します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	material
	 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
	 *		nullptr を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
	 *	\param[in]	triFlg
	 *		仮想関数からの継承のために存在する引数で、処理には一切影響しません。
	 *
	 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				writeVRMLFile(std::string fileName,
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
	 *	\param[in]	time
	 *		CoordinateInterpolator における時間配列 (key) を入力します。
	 *	\param[in]	pos
	 *		CoordinateInterpolator における位置ベクトル配列 (keyValue) を入力します。
	 *	\param[in]	material
	 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
	 *		nullptr を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
	 *	\param[in]	triFlg
	 *		仮想関数からの継承のために存在する引数で、処理には一切影響しません。
	 *
	 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				writeVRMLFile(std::string fileName,
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
	bool				writeSTLFile(std::string fileName);

	//! DXF ファイル出力関数
	/*!
	 *	DXF 形式で形状データを出力します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	triFlg
	 *		面情報を3角形として出力したい場合は、true を代入します。
	 *		false の場合、3角形面を2点が重複している4角形面として出力します。
	 *
	 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				writeDXFFile(std::string fileName,
									 bool triFlg = false);

	//! MQO ファイル出力関数
	/*!
	 *	MQO 形式で形状データを出力します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *
	 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				writeMQOFile(std::string fileName);

	//! 独自形式ファイル出力関数
	/*!
	 *	独自形式で形状データを出力します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *	\param[in]	mode			フォーマットモード
	 *
	 *	\return		成功すれば true を、失敗すれば false を返します。
	 */
	bool				writeData(std::string fileName,
								  fk_DataFormatMode mode = FK_BINARY_FILE);
	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	bool				AllCheck(void);
	void				PrintMat(std::string = "");
#endif

};

#endif // !__FK_SOLID_HEADER__
