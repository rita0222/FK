// IndexFace_CLI.h

#pragma once

#include <FK/IndexFace.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "BVHMotion_CLI.h"

namespace FK_CLI
{

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

		//! \name ファイル入出力関数
		//@{
		bool ReadSMFFile(String^ name);
		bool ReadVRMLFile(String^ name, bool materialFlg, bool solidFlg);
		bool ReadVRMLFile(String^ name, bool materialFlg);
		bool ReadVRMLFile(String^ name);
		bool ReadSTLFile(String^ name, bool solidFlg, double tolerance);
		bool ReadSTLFile(String^ name, bool solidFlg);
		bool ReadSTLFile(String^ name);
		bool ReadHRCFile(String^ name);
		bool ReadRDSFile(String^ name, bool solidFlg);
		bool ReadRDSFile(String^ name);
		bool ReadDXFFile(String^ name, bool solidFlg);
		bool ReadDXFFile(String^ name);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg, bool contFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, int materialID, bool solidFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, int materialID);
		bool ReadD3DXFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ pos);
		bool WriteSTLFile(String ^fileName);
		bool WriteDXFFile(String ^fileName, bool triFlg);
		bool WriteDXFFile(String ^fileName);
		bool WriteMQOFile(String^ fileName);
		//@}

		//! \name 形状情報参照関数
		//@{
		fk_Vector^ GetPosVec(int vertexID);
		array<int>^ GetFaceData(int faceID);
		int	GetFaceData(int faceID, int vertexNum);
		fk_Vector^ GetPNorm(int faceID, int order);
		fk_Vector^ GetPNorm(int faceID);
		fk_Vector^ GetVNorm(int vertexID, int order);
		fk_Vector^ GetVNorm(int vertexID);
		int GetElemMaterialID(int faceID);

		//@}
		
		//! \name 形状操作関数
		//@{
		
		bool MoveVPosition(int vertexID, fk_Vector^ pos, int order);
		bool MoveVPosition(int vertexID, fk_Vector^ pos);
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);
		bool MoveVPosition(int vertexID, double x, double y, double z);
		bool MoveVPosition(int vertexID, array<double>^ array, int order);
		bool MoveVPosition(int vertexID, array<double>^ array);
		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray, int order);
		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray);
		bool SetPNorm(int faceID, fk_Vector^ N, int order);
		bool SetPNorm(int faceID, fk_Vector^ N);
		bool SetVNorm(int vertexID, fk_Vector^ N, int order);
		bool SetVNorm(int vertexID, fk_Vector^ N);
		bool SetElemMaterialID(int faceID, int materialID);
		void Flush(void);

		//@}
		
		//! \name 直方体形状制御関数
		//@{
		void MakeBlock(double x, double y, double z);
		void SetBlockSize(double x, double y, double z);
		void SetBlockSize(double length, fk_Axis axis);
		void SetBlockScale(double scale);
		void SetBlockScale(double scale, fk_Axis axis);
		void SetBlockScale(double x, double y, double z);
		//@}

		//! \name 円形状制御関数
		//@{
		void MakeCircle(int div, double rad);
		void SetCircleRadius(double rad);
		void SetCircleDivide(int div);
		void SetCircleScale(double scale);
		//@}

		//! \name 球形状制御関数
		//@{
		void MakeSphere(int div, double rad);
		void SetSphereRadius(double rad);
		void SetSphereDivide(int div);
		void SetSphereScale(double scale);
		//@}

		//! \name 正多角柱(円柱)形状制御関数
		//@{
		void MakePrism(int div, double top, double bottom, double height);
		void SetPrismDivide(int div);
		void SetPrismTopRadius(double top);
		void SetPrismBottomRadius(double bottom);
		void SetPrismHeight(double height);
		//@}

		//! \name 正多角錐(円錐)形状制御関数
		//@{
		void MakeCone(int div, double rad, double height);
		void SetConeDivide(int div);
		void SetConeRadius(double rad);
		void SetConeHeight(double height);
		//@}

		//! \name カプセル型形状制御関数
		//@{
		void MakeCapsule(int div, double length, double rad);
		void SetCapsuleSize(double length, double rad);
		//@}

		//! \name 形状コピー操作関数
		//@{
		void PutSolid(fk_Solid^ solid);
		void CloneShape(fk_IndexFaceSet^ IFS);
		//@}
	};
}
