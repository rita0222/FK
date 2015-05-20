// Solid_CLI.h

#pragma once

#include <FK/Solid.h>
#include "SolidBase_CLI.h"

namespace FK_CLI
{
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
	 *	- 形状の高度な参照に関する機能は、 fk_Reference を参照して下さい。
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
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model, fk_Reference, fk_DataAccess,
	 *		fk_Operation, fk_Modify, fk_SolidBase, fk_Shape, fk_Attribute
	 */
	public ref class fk_Solid : fk_SolidBase {
	internal:
		::fk_Solid * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Solid(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_Solid();

		//! デストラクタ
		~fk_Solid();

		//! ファイナライザ
		!fk_Solid();

		//! 形状初期化関数1
		/*!
		 *	インスタンスに設定されている形状と独自属性を全て消去し、
		 *	データの初期化を行います。
		 *
		 *	\param[in]	matFlg
		 *		true の場合、インスタンス中に設定されていたマテリアルに関する情報も
		 *		合わせて消去します。false の場合、マテリアル情報は存続させます。
		 */
		void AllClear(bool matFlg);

		//! 形状初期化関数2
		/*!
		 *	インスタンスに設定されている形状と独自属性を全て消去し、
		 *	データの初期化を行います。
		 *	本関数は AllClear(bool) において、引数に true を入力した場合と同義となります。
		 */
		void AllClear(void);

		//! 空形状状態参照関数
		/*!
		 *	形状情報が空かどうかを参照します。
		 *
		 *	\return		形状情報が空の場合 true を、そうでない場合は false を返します。
		 */
		bool IsEmpty(void);

		//! 形状コピー関数
		/*!
		 *	引数として与えられたインスタンス中の形状をコピーします。
		 *	各種属性およびマテリアル情報は写しません。
		 *
		 *	\param[in]		solid		複写元インスタンス
		 */
		void CloneShape(fk_Solid^ solid);

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
		bool CompareShape(fk_Solid^ solid);

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
		bool ReadSMFFile(String^ fileName);

		//! SRFファイル入力関数
		/*!
		 *	SRF形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadSRFFile(String^ fileName);

		//! VRML ファイル入力関数1
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本関数が対応しているのは「IndexedFaceSet」ノードに記述された形状のみです。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	materialFlg
		 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
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
		 *		本関数では入力フォーマットとして VRML97 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ fileName, bool materialFlg, bool solidFlg);

		//! VRML ファイル入力関数2
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本関数が対応しているのは「IndexedFaceSet」ノードに記述された形状のみです。
		 *
		 *	なお、本関数は ReadVRMLFile(String^, bool, bool) において、
		 *	第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	materialFlg
		 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		VRML形式は、1994年に策定された通称「VRML1.0」と、
		 *		1997年に策定された「VRML97」の2種類があり、
		 *		VRML97は「VRML2.0」とも呼ばれます。
		 *		本関数では入力フォーマットとして VRML97 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ fileName, bool materialFlg);

		//! VRML ファイル入力関数3
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本関数が対応しているのは「IndexedFaceSet」ノードに記述された形状のみです。
		 *
		 *	なお、本関数は ReadVRMLFile(String^, bool, bool) において、
		 *	第2引数に true、第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		VRML形式は、1994年に策定された通称「VRML1.0」と、
		 *		1997年に策定された「VRML97」の2種類があり、
		 *		VRML97は「VRML2.0」とも呼ばれます。
		 *		本関数では入力フォーマットとして VRML97 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ fileName);

		//! STL ファイル入力関数1
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
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
		bool ReadSTLFile(String^ fileName, bool solidFlg, double tolerance);

		//! STL ファイル入力関数2
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *
		 *	なお、本関数は ReadSTLFile(String^, bool, double) において、
		 *	第3引数に 1.0e-08 を入力した場合と同義となります。
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
		bool ReadSTLFile(String^ fileName, bool solidFlg);

		//! STL ファイル入力関数2
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *
		 *	なお、本関数は ReadSTLFile(String^, bool, double) において、
		 *	第2引数に true を、第3引数に 1.0e-08 を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadSTLFile(String^ fileName);

		//! HRCファイル入力関数
		/*!
		 *	HRC形式のファイルからデータを入力します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadHRCFile(String^ fileName);

		//! RDSファイル入力関数1
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
		bool ReadRDSFile(String^ fileName, bool solidFlg);

		//! RDSファイル入力関数2
		/*!
		 *	RDS (Ray Dream Studio) 形式のファイルからデータを入力します。
		 *	本関数は ReadRDSFile(String^, bool) 関数において、
		 *	第2引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadRDSFile(String^ fileName);

		//! DXFファイル入力関数1
		/*!
		 *	DXF 形式のファイルからデータを入力します。
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
		bool ReadDXFFile(String^ fileName, bool solidFlg);

		//! DXFファイル入力関数2
		/*!
		 *	DXF 形式のファイルからデータを入力します。
		 *	本関数は ReadDXFFile(String^, bool) 関数において、
		 *	第2引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadDXFFile(String^ fileName);

		//! MQOファイル入力関数1-1
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
		 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOファイル入力関数1-2
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
		 *	なお、本関数は ReadMQOFile(String^, bool, bool contFlg, bool) において、
		 *	第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);

		//! MQOファイル入力関数1-3
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
		 *	なお、本関数は ReadMQOFile(String^, String^, bool, bool, bool) において、
		 *	第4引数に true、第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg);

		//! MQOファイル入力関数1-4
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
		 *	なお、本関数は ReadMQOFile(String^, String^, bool, bool, bool) において、
		 *	第3引数に true、第4引数に true、第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName);

		//! MQOファイル入力関数2-1
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
		 *		true の場合、VRMLファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOファイル入力関数2-2
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
		 *	なお、本関数は ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第6引数に false を入力した場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg);

		//! MQOファイル入力関数2-3
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
		 *	なお、本関数は ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第5引数に true、第6引数に false を入力した場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID, bool solidFlg);

		//! MQOファイル入力関数2-4
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
		 *	なお、本関数は ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第4引数に true、第5引数に true、第6引数に false を入力した場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);

		//! DirectX (D3DX) ファイル入力関数1-1
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
		 *	\sa fk_IFSTexture::ReadD3DXFile()
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName, bool solidFlg);

		//! DirectX (D3DX) ファイル入力関数1-2
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
		 *	本関数は、 ReadD3DXFile(String^, String^, bool) において、
		 *	第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\param[in]	objName		オブジェクト名。
		 *		D3DX 形式では、オブジェクト名を省略することが許容されています。
		 *		そのような場合は、この引数に空文字列 ( "" ) を入れてください。
		 *		この場合、ファイル中で最初に存在するオブジェクトのデータを入力します。
		 *
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::ReadD3DXFile()
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName);

		//! DirectX (D3DX) ファイル入力関数2-1
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
		 *	\sa fk_IFSTexture::ReadD3DXFile()
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);

		//! DirectX (D3DX) ファイル入力関数2-2
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
		 *	本関数は、 ReadD3DXFile(String^, String^, int, bool) において、
		 *	第4引数に true を入力した場合と同義となります。
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
		 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fk_IFSTexture::ReadD3DXFile()
		 */
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos);
		bool WriteSTLFile(String^ fileName);
		bool WriteDXFFile(String^ fileName, bool triFlg);
		bool WriteDXFFile(String^ fileName);
		bool WriteMQOFile(String^ fileName);
	};
}
