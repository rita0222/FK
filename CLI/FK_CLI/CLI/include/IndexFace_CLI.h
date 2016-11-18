// IndexFace_CLI.h

#pragma once

#include <FK/IndexFace.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "BVHMotion_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	ref class fk_Solid;
	//! インデックスフェースセットの内部データタイプを表す列挙型
	public enum class fk_IFType {
		NONE,			//!<	未定義
		TRIANGLES,		//!<	3角形集合
		QUADS,			//!<	4角形集合
		POLYGON			//!<	任意多角形集合
	};
			
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
	 *	この機能の詳細は MoveVPosition() を参照して下さい。
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
	public ref class fk_IndexFaceSet : fk_Shape {
	internal:
		::fk_IndexFaceSet * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_IndexFaceSet(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_IndexFaceSet();

		//! デストラクタ
		~fk_IndexFaceSet();

		//! ファイナライザ
		!fk_IndexFaceSet();

		//! 頂点数プロパティ
		/*!
		 *	形状データの頂点数を参照します。
		 */
		property int PosSize {
			int get();
		}

		//! 面数プロパティ
		/*!
		 *	形状データの面数を参照します。
		 */
		property int FaceSize {
			int get();
		}

		//! 面タイププロパティ
		/*!
		 *	形状データの面タイプを参照します。
		 */
		property fk_IFType^ FaceType {
			fk_IFType^ get();
		}

		//! アニメーション時間プロパティ
		/*!
		 *	D3DX形式からの入力や、
		 *	BVH情報からの入力によってアニメーションが設定されている場合、
		 *	このプロパティを用いることで形状状態を任意のアニメーション時間に設定することができます。
		 *
		 *	\sa ReadD3DXFile(), BVHMotion, fk_BVHMotion
		 */
		property double AnimationTime {
			void set(double);
		}
		
		//! BVHデータプロパティ
		/*!
		 *	形状に対し、BVH 形式によるアニメーションを設定します。
		 *
		 *	\sa AnimationTime, ReadD3DXFile(), fk_BVHMotion
		 */
		property fk_BVHMotion^ BVHMotion {
			void set(fk_BVHMotion^);
		}

		//! \name 形状ファイル・形状データ入力メソッド
		//@{

		//! SMFファイル入力メソッド
		/*!
		 *	SMF形式のファイルからデータを入力します。
		 *
		 *	\param[in]	name	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadSMFFile(String^ name);

		//! VRML ファイル入力メソッド1
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本メソッドが対応しているのは「IndexedFaceSet」
		 *	ノードに記述された形状のみです。
		 *
		 *	\param[in]	name		ファイル名
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
		 *		本メソッドでは入力フォーマットとして VRML2.0 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、
		 *		特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ name, bool materialFlg, bool solidFlg);

		//! VRML ファイル入力メソッド2
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本メソッドが対応しているのは「IndexedFaceSet」
		 *	ノードに記述された形状のみです。
		 *
		 *	なお、本メソッドは ReadVRMLFile(String^, bool, bool) において、
		 *	第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\param[in]	materialFlg
		 *		true の場合、
		 *		VRMLファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		VRML形式は、1994年に策定された通称「VRML1.0」と、
		 *		1997年に策定された「VRML97」の2種類があり、
		 *		VRML97は「VRML2.0」とも呼ばれます。
		 *		本メソッドでは入力フォーマットとして VRML2.0 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、
		 *		特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ name, bool materialFlg);

		//! VRML ファイル入力メソッド3
		/*!
		 *	VRML形式のファイルからデータを入力します。
		 *	VRMLでは、形状を表す様々なノードがありますが、
		 *	本メソッドが対応しているのは「IndexedFaceSet」
		 *	ノードに記述された形状のみです。
		 *
		 *	なお、本メソッドは ReadVRMLFile(String^, bool, bool) において、
		 *	第2引数と第3引数で共に true を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		VRML形式は、1994年に策定された通称「VRML1.0」と、
		 *		1997年に策定された「VRML97」の2種類があり、
		 *		VRML97は「VRML2.0」とも呼ばれます。
		 *		本メソッドでは入力フォーマットとして VRML2.0 を想定しています。
		 *
		 *	\note
		 *		VRMLは文法解釈、
		 *		特にセパレータの扱い方についてはあまり厳密になっておらず、
		 *		様々なデータによって異なる解釈がなされているようです。
		 *		そのため、構文解析がうまくいかずに入力失敗する場合がありえます。
		 */
		bool ReadVRMLFile(String^ name);

		//! STL ファイル入力メソッド1
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *	また、以下の条件に当てはまるデータは
		 *	fk_IndexFaceSet では入力できません。
		 *	- 5以上の角数である面が存在する。
		 *	- 3角形面と4角形面が混在している。
		 *
		 *	\param[in]	name		ファイル名
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
		bool ReadSTLFile(String^ name, bool solidFlg, double tolerance);

		//! STL ファイル入力メソッド2
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *	また、以下の条件に当てはまるデータは
		 *	fk_IndexFaceSet では入力できません。
		 *	- 5以上の角数である面が存在する。
		 *	- 3角形面と4角形面が混在している。
		 *
		 *	なお、本メソッドは ReadSTLFile(String^, bool, double) において、
		 *	第3引数に 1.0e-0.8 を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadSTLFile(String^ name, bool solidFlg);

		//! STL ファイル入力メソッド3
		/*!
		 *	STL形式のファイルからデータを入力します。
		 *	対応しているのは面データのみです。
		 *	また、以下の条件に当てはまるデータは
		 *	fk_IndexFaceSet では入力できません。
		 *	- 5以上の角数である面が存在する。
		 *	- 3角形面と4角形面が混在している。
		 *
		 *	なお、本メソッドは ReadSTLFile(String^, bool, double) において、
		 *	第2引数に true、第3引数に 1.0e-0.8 を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadSTLFile(String^ name);


		//! HRCファイル入力メソッド
		/*!
		 *	HRC形式のファイルからデータを入力します。
		 *
		 *	\param[in]	name	ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadHRCFile(String^ name);

		//! RDSファイル入力メソッド1
		/*!
		 *	RDS (Ray Dream Studio) 形式のファイルからデータを入力します。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadRDSFile(String^ name, bool solidFlg);

		//! RDSファイル入力メソッド2
		/*!
		 *	RDS (Ray Dream Studio) 形式のファイルからデータを入力します。
		 *	本メソッドは、 ReadRDSFile(String^, bool) において、
		 *	第2引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadRDSFile(String^ name);

		//! DXFファイル入力メソッド1
		/*!
		 *	DXF 形式のファイルからデータを入力します。
		 *
		 *	\param[in]	name		ファイル名
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadDXFFile(String^ name, bool solidFlg);

		
		//! DXFファイル入力メソッド1
		/*!
		 *	DXF 形式のファイルからデータを入力します。
		 *	本メソッドは、 ReadDXFFile(String^, bool) において、
		 *	第2引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	name		ファイル名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool ReadDXFFile(String^ name);

		//! MQOファイル入力メソッド1-1
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	\param[in]	fileName	ファイル名
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
		 *		true の場合、MQOファイル中で設定されているマテリアル情報を入力します。
		 *		false の場合は、マテリアル情報を無視します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOファイル入力メソッド1-2
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, bool, bool, bool) において、
		 *	第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
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
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);

		//! MQOファイル入力メソッド1-3
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, bool, bool, bool) において、
		 *	第4引数に true を、第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *	\param[in]	solidFlg
		 *		true の場合、位相の隣接関係を最適化します。
		 *		ただし、結果として入力に失敗する場合があります。
		 *		false の場合は隣接関係を最適化せず、
		 *		すべての面が独立した状態として形状を構築します。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg);

		//! MQOファイル入力メソッド1-4
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, bool, bool, bool) において、
		 *	第3引数に true を、第4引数に true を、第5引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName	ファイル名
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName);

		//! MQOファイル入力メソッド2-1
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
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
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOファイル入力メソッド2-2
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第6引数に false を入力している場合と同義となります。
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
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg);

		//! MQOファイル入力メソッド2-3
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第5引数に true を、第6引数に false を入力している場合と同義となります。
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
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg);

		//! MQOファイル入力メソッド2-4
		/*!
		 *	MQO 形式のファイルからデータを入力します。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOFile(String^, String^, int, bool, bool, bool) において、
		 *	第4引数に true を、第5引数に true を、第6引数に false を入力している場合と同義となります。
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
		 *
		 *	\sa ReadMQOData(), fk_IFSTexture::ReadMQOFile()
		 */
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);

		//! MQOデータ入力メソッド1-1
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
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
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOデータ入力メソッド1-2
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, bool, bool, bool) において、
		 *	第5引数に false を入力している場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName, bool solidFlg, bool contFlg);

		//! MQOデータ入力メソッド1-3
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, bool, bool, bool) において、
		 *	第4引数に true を、第5引数に false を入力している場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName, bool solidFlg);

		//! MQOデータ入力メソッド1-4
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, bool, bool, bool) において、
		 *	第3引数に true を、第4引数に true を、第5引数に false を入力している場合と同義となります。
		 *
		 *	\param[in]	buffer		データが格納されているバッファ
		 *
		 *	\param[in]	objName		オブジェクト名
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName);

		//! MQOデータ入力メソッド2-1
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
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
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName,
						 int materialID, bool solidFlg, bool contFlg, bool materialFlg);

		//! MQOデータ入力メソッド2-2
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, int, bool, bool, bool) において、
		 *	第6引数に false を入力している場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName,
						 int materialID, bool solidFlg, bool contFlg);

		//! MQOデータ入力メソッド2-3
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, int, bool, bool, bool) において、
		 *	第5引数に true を、第6引数に false を入力している場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName, int materialID, bool solidFlg);

		//! MQOデータ入力メソッド2-4
		/*!
		 *	MQO形式のデータを入力します。
		 *	本メソッドでは、MQO形式のデータが既に
		 *	Byte 型の配列中に入力されていると仮定し、
		 *	ReadMQOFile() メソッドと同様の処理を行います。
		 *
		 *	本メソッドは、テクスチャ用のデータの入力は行いません。
		 *	テクスチャデータも併せて表示を行いたい場合は、
		 *	fk_IFSTexture クラスを利用して下さい。
		 *
		 *	MQOデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadMQOData(IEnumerable<Byte>^, String^, int, bool, bool, bool) において、
		 *	第4引数に true を、第5引数に true を、第6引数に false を入力している場合と同義となります。
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
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa ReadMQOFile()
		 */
		bool ReadMQOData(IEnumerable<Byte>^ buffer, String^ objName, int materialID);

		//! DirectX (D3DX) ファイル入力メソッド1-1
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本メソッドで入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
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

		//! DirectX (D3DX) ファイル入力メソッド1-2
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本メソッドで入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadD3DXFile(String^, String^, bool) において、
		 *	第3引数に true を入力している場合と同義となります。
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

		//! DirectX (D3DX) ファイル入力メソッド2-1
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本メソッドで入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
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

		//! DirectX (D3DX) ファイル入力メソッド2-2
		/*!
		 *	DirectX 形式 (X 形式と呼ばれることもあります) のフォーマット
		 *	(以下、「D3DX形式」) であるファイルからデータを入力します。
		 *	本メソッドで入力できるのは形状データとアニメーションデータです。
		 *	テクスチャデータを入力したい場合は、
		 *	fk_IndexFaceSet クラスではなく fk_IFSTexture クラスを利用して下さい。
		 *
		 *	D3DXデータには「オブジェクト」という概念があり、
		 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
		 *	本メソッドでは、ファイル名とともにオブジェクト名を指定する必要があります。
		 *
		 *	なお、本メソッドは ReadD3DXFile(String^, String^, int, bool) において、
		 *	第4引数に true を入力している場合と同義となります。
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

		//@}

		//! \name 形状ファイル・形状データ出力メソッド
		//@{
		
		//! VRML ファイル出力メソッド1-1
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	material
		 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
		 *		null を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
		 *
		 *	\param[in]	triFlg
		 *		仮想メソッドからの継承のために存在する引数で、処理には一切影響しません。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);

		//! VRML ファイル出力メソッド1-2
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *
		 *	なお、本メソッドは WriteVRMLFile(String^, fk_Material^, bool) において、
		 *	第3引数に false を入力している場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	material
		 *		VRMLファイル中に「Material」ノードとしてマテリアル情報を保存します。
		 *		null を代入した場合は、VRMLファイル中に「Material」ノードを生成しません。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName, fk_Material^ material);

		//! VRML ファイル出力メソッド1-3
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *
		 *	なお、本メソッドは WriteVRMLFile(String^, fk_Material^, bool) において、
		 *	第2引数に null を、第3引数に false を入力している場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName);

		//! VRML ファイル出力メソッド2-1
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
		 *		仮想メソッドからの継承のために存在する引数で、処理には一切影響しません。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName, IEnumerable<double>^ time,
						   IEnumerable<fk_Vector^>^ pos, fk_Material^ material, bool triFlg);

		//! VRML ファイル出力メソッド2-2
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *	この引数形式の場合は、
		 *	CoordinateInterpolator ノードを用いた
		 *	アニメーションデータを出力することが可能です。
		 *
		 *	なお、本メソッドは
		 *	WriteVRMLFile(String^, IEnumerable<double>^,
		 *	IEnumerable<fk_Vector^>^, fk_Material^, bool) において、
		 *	第5引数に false を入力している場合と同義となります。
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
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName, IEnumerable<double>^ time,
						   IEnumerable<fk_Vector^>^ pos, fk_Material^ material);

		//! VRML ファイル出力メソッド2-3
		/*!
		 *	VRML (VRML2.0) 形式で形状データを出力します。
		 *	この引数形式の場合は、
		 *	CoordinateInterpolator ノードを用いた
		 *	アニメーションデータを出力することが可能です。
		 *
		 *	なお、本メソッドは
		 *	WriteVRMLFile(String^, IEnumerable<double>^,
		 *	IEnumerable<fk_Vector^>^, fk_Material^, bool) において、
		 *	第4引数に null を、第5引数に false を入力している場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\param[in]	time
		 *		CoordinateInterpolator における時間配列 (key) を入力します。
		 *
		 *	\param[in]	pos
		 *		CoordinateInterpolator における位置ベクトル配列 (keyValue) を入力します。
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteVRMLFile(String^ fileName, IEnumerable<double>^ time, IEnumerable<fk_Vector^>^ pos);

		//! STL ファイル出力メソッド
		/*!
		 *	STL 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteSTLFile(String^ fileName);

		//! DXF ファイル出力メソッド1
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
		bool WriteDXFFile(String^ fileName, bool triFlg);

		//! DXF ファイル出力メソッド1
		/*!
		 *	DXF 形式で形状データを出力します。
		 *
		 *	なお、本メソッドは WriteDXFFile(String^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteDXFFile(String^ fileName);

		//! MQO ファイル出力メソッド
		/*!
		 *	MQO 形式で形状データを出力します。
		 *
		 *	\param[in]	fileName		ファイル名
		 *
		 *	\return ファイルの出力に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool WriteMQOFile(String^ fileName);
		//@}

		//! \name 形状情報参照メソッド
		//@{

		//! 頂点位置ベクトル参照メソッド
		/*!
		 *	形状データ中の、頂点の位置ベクトルを取得します。
		 *
		 *	\param[in]	vertexID
		 *		頂点ID。一番最初の頂点IDは 0 になります。
		 *		最後の ID は頂点数から 1 を引いたものとなります。
		 *
		 *	\return		頂点の位置ベクトル
		 *
		 *	\sa MoveVPosition()
		 */
		fk_Vector^ GetPosVec(int vertexID);

		//! 頂点 ID 配列参照メソッド
		/*!
		 *	面を構成する頂点 ID の配列を取得します。
		 *
		 *	\param[in]	faceID
		 *		面 ID。一番最初の面IDは 0 になります。
		 *		最後の ID は面数から 1 を引いたものとなります。
		 *
		 *	\return		頂点 ID 配列
		 */
		cli::array<int>^ GetFaceData(int faceID);

		//! 頂点 ID 参照メソッド
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
		int	GetFaceData(int faceID, int vertexNum);

		//! 面法線ベクトル取得メソッド1
		/*!
		 *	面の法線ベクトルを取得します。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\param[in]	order
		 *		最初の面IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return		面の法線ベクトル
		 *
		 *	\sa SetPNorm(), GetVNorm()
		 */
		fk_Vector^ GetPNorm(int faceID, int order);

		//! 面法線ベクトル取得メソッド2
		/*!
		 *	面の法線ベクトルを取得します。
		 *
		 *	なお、本メソッドは GetPNorm(int, int) において、
		 *	第2引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\return		面の法線ベクトル
		 *
		 *	\sa SetPNorm(), GetVNorm()
		 */
		fk_Vector^ GetPNorm(int faceID);

		//! 頂点法線ベクトル取得メソッド1
		/*!
		 *	頂点の法線ベクトルを取得します。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return		頂点の法線ベクトル
		 *
		 *	\sa SetVNorm(), GetPNorm()
		 */
		fk_Vector^ GetVNorm(int vertexID, int order);

		//! 頂点法線ベクトル取得メソッド2
		/*!
		 *	頂点の法線ベクトルを取得します。
		 *
		 *	なお、本メソッドは GetVNorm(int, int) において、
		 *	第2引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\return		頂点の法線ベクトル
		 *
		 *	\sa SetVNorm(), GetPNorm()
		 */
		fk_Vector^ GetVNorm(int vertexID);

		//! マテリアルID取得メソッド
		/*!
		 *	面に対して個別に設定してあるマテリアル ID を取得します。
		 *	マテリアルの個別設定については
		 *	fk_Shape::SetMaterialMode() および
		 *	fk_Shape::SetPalette() を参照して下さい。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\return		マテリアルID
		 *
		 *	\sa SetElemMaterialID(), fk_Shape
		 */
		int GetElemMaterialID(int faceID);

		//@}
		
		//! \name 形状操作メソッド
		//@{
		
		//! 頂点移動メソッド1-1
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	pos				移動先の位置ベクトル
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, fk_Vector^ pos, int order);

		//! 頂点移動メソッド1-2
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	なお、本メソッドは MoveVPosition(int, fk_Vector^, int) において、
		 *	第3引数に 0 を入力した場合と同義になります。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *	\param[in]	pos				移動先の位置ベクトル
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, fk_Vector^ pos);

		
		//! 頂点移動メソッド2-1
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *	\param[in]	x				移動先位置ベクトルの x 成分
		 *	\param[in]	y				移動先位置ベクトルの y 成分
		 *	\param[in]	z				移動先位置ベクトルの z 成分
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);

		//! 頂点移動メソッド2-1
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	なお、本メソッドは MoveVPosition(int, double, double, double, int) において、
		 *	第5引数に 0 を入力した場合と同義になります。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *	\param[in]	x				移動先位置ベクトルの x 成分
		 *	\param[in]	y				移動先位置ベクトルの y 成分
		 *	\param[in]	z				移動先位置ベクトルの z 成分
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, double x, double y, double z);

		//! 頂点移動メソッド3-1
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	array
		 *		移動先位置ベクトルの各成分が入った double 型配列。
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, IEnumerable<double>^ array, int order);

		//! 頂点移動メソッド3-2
		/*!
		 *	指定された頂点を移動します。
		 *	なお、 SetVNorm() によって法線ベクトルが設定されていた場合や、
		 *	SetPNorm() によって周辺の面に放線ベクトルが設定されていた場合、
		 *	本メソッドによって破棄されます。
		 *
		 *	なお、本メソッドは MoveVPosition(int, IEnumerable<double>^, int) において、
		 *	第3引数に 0 を入力した場合と同義になります。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	array
		 *		移動先位置ベクトルの各成分が入った double 型配列。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPosVec()
		 */
		bool MoveVPosition(int vertexID, IEnumerable<double>^ array);

		//! 任意形状生成メソッド1
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
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\sa fk_Solid
		 */
		void MakeIFSet(int faceNum, int polyNum, IEnumerable<int>^ IFSet,
					   int vertexNum, IEnumerable<fk_Vector^>^ posArray, int order);

		//! 任意形状生成メソッド2
		/*!
		 *	与えられたインデックスフェースセット情報から、形状を生成します。
		 *
		 *	なお、本メソッドは MakeIFSet(int, int, IEnumerable<int>^, int, IEnumerable<fk_Vector^>^, int) において、
		 *	第6引数に 0 を入力した場合と同義となります。
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
		 *	\sa fk_Solid
		 */
		void MakeIFSet(int faceNum, int polyNum, IEnumerable<int>^ IFSet,
					   int vertexNum, IEnumerable<fk_Vector^>^ posArray);

		//! 面法線ベクトル設定メソッド1
		/*!
		 *	面の法線ベクトルを設定します。
		 *
		 *	通常、面の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、このメソッドを用います。
		 *
		 *	なお、 MoveVPosition() メソッドによって面上の点が移動された場合、
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
		 *	\sa GetPNorm(), SetVNorm()
		 */
		bool SetPNorm(int faceID, fk_Vector^ norm, int order);

		//! 面法線ベクトル設定メソッド2
		/*!
		 *	面の法線ベクトルを設定します。
		 *
		 *	通常、面の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、このメソッドを用います。
		 *
		 *	なお、 MoveVPosition() メソッドによって面上の点が移動された場合、
		 *	設定した法線ベクトルは破棄されます。
		 *
		 *	本メソッドは SetPNorm(int, fk_Vector^, int) において、
		 *	第3引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\param[in]	norm
		 *		法線ベクトル。あらかじめ正規化しておく必要があります。
		 *		正規化されていない放線ベクトルを入力した場合、
		 *		動作が異常となる場合があります。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetPNorm(), SetVNorm()
		 */
		bool SetPNorm(int faceID, fk_Vector^ norm);

		//! 頂点法線ベクトル設定メソッド1
		/*!
		 *	頂点の法線ベクトルを設定します。
		 *
		 *	通常、頂点の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、このメソッドを用います。
		 *
		 *	なお、 MoveVPosition() メソッドによって頂点が移動された場合、
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
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetVNorm(), SetPNorm()
		 */
		bool SetVNorm(int vertexID, fk_Vector^ norm, int order);

		//! 頂点法線ベクトル設定メソッド1
		/*!
		 *	頂点の法線ベクトルを設定します。
		 *
		 *	通常、頂点の法線ベクトルは自前で設定しなくても、
		 *	形状から自動的に算出されます。
		 *	しかし、バンプマッピングなどの技法を用いる場合など、
		 *	自前で計算した法線ベクトルを与える場合は、このメソッドを用います。
		 *
		 *	なお、 MoveVPosition() メソッドによって頂点が移動された場合、
		 *	設定した法線ベクトルは破棄されます。
		 *
		 *	本メソッドは SetVNorm(int, fk_Vector^, int) において、
		 *	第3引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	vertexID		頂点ID
		 *
		 *	\param[in]	norm
		 *		法線ベクトル。あらかじめ正規化しておく必要があります。
		 *		正規化されていない放線ベクトルを入力した場合、
		 *		動作が異常となる場合があります。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetVNorm(), SetPNorm()
		 */
		bool SetVNorm(int vertexID, fk_Vector^ norm);

		//! マテリアルID設定メソッド
		/*!
		 *	面に対してマテリアルIDを設定します。
		 *	マテリアルの個別設定については
		 *	fk_Shape::MaterialMode および
		 *	fk_Shape::SetPalette() を参照して下さい。
		 *
		 *	\param[in]	faceID		面ID
		 *
		 *	\param[in]	materialID	マテリアルID
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetElemMaterialID(), fk_Shape
		 */
		bool SetElemMaterialID(int faceID, int materialID);

		//! 法線ベクトル強制計算メソッド 
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
		 *	本メソッドは、形状中のすべての面と頂点に対して法線ベクトルを強制的に算出します。
		 *	なお、 SetPNorm() や SetVNorm() で設定した法線ベクトルは全て破棄されます。
		 *
		 *	\sa GetPNorm(), GetVNorm(), SetPNorm(), SetVNorm()
		 */
		void Flush(void);

		//@}
		
		//! \name 直方体形状制御メソッド
		//@{

		//! 直方体生成メソッド
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
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa fk_Block
		 */
		void MakeBlock(double x, double y, double z);

		//! 直方体辺長変更メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を一括して設定しなおします。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockSize(double x, double y, double z);

		//! 直方体個別辺長設定メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を個別に設定します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	length	辺長
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockSize(double length, fk_Axis axis);

		//! 直方体全体拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体全体を指定された倍率で拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double scale);

		//! 直方体軸方向拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	指定された軸方向についてのみ拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double scale, fk_Axis axis);

		//! 直方体軸方向個別拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	各軸方向に対し個別の倍率で拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の倍率
		 *	\param[in]	y	y方向の倍率
		 *	\param[in]	z	z方向の倍率
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double x, double y, double z);
		//@}

		//! \name 円形状制御メソッド
		//@{

		//! 円形状生成メソッド
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
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div	分割数。実際には円弧全体をこの数値の 4 倍で分割します。
		 *	\param[in]	rad	半径
		 *
		 *	\sa fk_Circle
		 */
		void MakeCircle(int div, double rad);

		//! 円形状半径設定メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	半径を設定しなおします。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleRadius(double rad);

		//! 円形状分割数設定メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleDivide(int div);

		//! 円形状拡大縮小メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleScale(double scale);
		//@}

		//! \name 球形状制御メソッド
		//@{

		//! 球形状生成メソッド
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
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *	
		 *	\param[in]	div	分割数
		 *	\param[in]	rad	半径
		 *
		 *	\sa fk_Sphere
		 */
		void MakeSphere(int div, double rad);

		//! 球形状半径設定メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	半径を設定しなおします。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereRadius(double rad);

		//! 球形状分割数設定メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereDivide(int div);

		//! 球形状拡大縮小メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereScale(double scale);
		//@}

		//! \name 正多角柱(円柱)形状制御メソッド
		//@{

		//! 正多角柱(円柱)形状生成メソッド
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
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	top		上面半径
		 *	\param[in]	bottom	底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Prism
		 */
		void MakePrism(int div, double top, double bottom, double height);


		//! 正多角柱(円柱)角数設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	角数を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismDivide(int div);

		//! 正多角柱(円柱)上面半径設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	上面の外接円半径を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	top	上面半径
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismTopRadius(double top);

		//! 正多角柱(円柱)角数設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	底面の外接円半径を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	bottom	底面半径
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismBottomRadius(double bottom);

		//! 正多角柱(円柱)高さ設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	高さを設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height	高さ
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismHeight(double height);
		//@}

		//! \name 正多角錐(円錐)形状制御メソッド
		//@{

		//! 正多角錐(円錐)形状生成メソッド
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
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	rad		底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Cone
		 */
		void MakeCone(int div, double rad, double height);

		//! 正多角錐(円錐)角数設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	角数を設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa MakeCone(), fk_Cone
		 */
		void SetConeDivide(int div);

		//! 正多角錐(円錐)底面半径設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	底面外接円半径を設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad		底面半径
		 *
		 *	\sa MakeCone(), fk_Cone
		 */
		void SetConeRadius(double rad);

		//! 正多角錐(円錐)高さ設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	高さを設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height		高さ
		 *
		 *	\sa MakeCone(), fk_Cone
		 */
		void SetConeHeight(double height);
		//@}

		//! \name カプセル型形状制御メソッド
		//@{

		//! カプセル型形状生成メソッド
		/*!
		 *	カプセル型を生成します。
		 *	カプセル型は半径の等しい円柱側面と半球面によって構成されています。
		 *	数学的には、カプセル型の内部は1本の線分より一定距離以下の部分の集合であり、
		 *	その一定距離は前述の半径と等しくなります。この線分を「中心軸」と呼びます。
		 *	初期状態は中心軸の中点が原点に配置され、z軸方向と中心軸が平行となります。
		 *	設定できる要素は中心軸長、半径、分割数です。
		 *	実際のカプセル型の全長は「中心軸長 + (半径)*2」となります。
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		分割数
		 *	\param[in]	len		中心軸長
		 *	\param[in]	rad		半径
		 *
		 *	\sa fk_Capsule
		 */
		void MakeCapsule(int div, double len, double rad);

		//! カプセル型形状寸法設定メソッド
		/*!
		 *	MakeCapsule() によってカプセル型形状を生成した後に、
		 *	中心軸長と半径を再度設定します。
		 *	このメソッドは、 MakeCapsule() によってカプセル型形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	len		中心軸長
		 *	\param[in]	rad		半径
		 *
		 *	\sa MakeCapsule(), fk_Capsule
		 */
		void SetCapsuleSize(double len, double rad);
		//@}

		//! \name 形状コピー操作メソッド
		//@{

		//! fk_Solid 出力メソッド
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
		void PutSolid(fk_Solid^ solid);

		//! 形状コピーメソッド
		/*!
		 *	引数として与えられたインスタンス中の形状をコピーします。
		 *	各種属性およびマテリアル情報は写しません。
		 *
		 *	\param[in]		ifs		複写元インスタンス
		 */
		void CloneShape(fk_IndexFaceSet^ ifs);
		//@}
	};
}

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
