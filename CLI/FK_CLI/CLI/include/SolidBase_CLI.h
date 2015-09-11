// Modify_CLI.h

#pragma once

#include <FK/SolidBase.h>
#include "Modify_CLI.h"

namespace FK_CLI
{
	//! ソリッドモデル形状変換クラス
	/*!
	 *	このクラスは、 fk_Solid クラスのインスタンスにおいて、
	 *	インデックスフェースセットによるデータ(以下「IFSデータ」)
	 *	から形状を生成する機能を提供します。
	 *	IFSデータとは、位置ベクトルの配列からなる頂点データと、
	 *	頂点IDを格納した面データ集合の2つのデータから成る形状データです。
	 *
	 *	一般形状を表すクラスとして、 fk_Solid の他に fk_IndexFaceSet クラスがあります。
	 *	fk_IndexFaceSet クラスにも fk_IndexFaceSet::MakeIFSet() 関数によって、
	 *	IFS データから形状を生成することが可能です。
	 *	ただし、 fk_IndexFaceSet においては面が3角形か4角形のみ
	 *	(そして混在は不可)という制限があります。また、生成後の位相変化にも対応していません。
	 *	fk_Solid の場合、任意角数の多角形を混在して扱うことが可能であるため、
	 *	より表現力が高いと言えます。ただし、
	 *	fk_Solid は fk_IndexFaceSet と比較して描画速度は若干遅くなる、
	 *	メモリ使用量は若干増えるなどのデメリットがあります。
	 *
	 *	\sa fk_Solid, fk_IndexFaceSet
	 */
	public ref class fk_SolidBase : fk_Modify {
	internal:
		::fk_SolidBase * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_SolidBase(bool argNewFlg);
		~fk_SolidBase();
		!fk_SolidBase();
#endif

		//! 任意形状生成関数1-1
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *	この関数形式の場合、全ての面が同じ角数である必要があります。
		 *	角数の異なる面が混在する形状を作成したい場合は、
		 *	MakeIFSet(cli::array< cli::array<int>^ >^, cli::array<fk_Vector^>^, int)
		 *	を利用して下さい。
		 *
		 *	\param[in]	faceNum		面数
		 *
		 *	\param[in]	polyNum		面の角数。3以上の値を入力できます。
		 *
		 *	\param[in]	IFSet
		 *		インデックスフェースセット配列。
		 *		この配列は、各面を構成する頂点 ID を並べたものになります。
		 *		たとえば、頂点 ID が [0, 1, 2] と [2, 1, 3] という構成を持つ
		 *		2面からなる形状を生成する場合、int 型の配列に対して
		 *		[0, 1, 2, 2, 1, 3] という数値を入力しておきます。
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
		 *	\sa fk_IndexFaceSet::MakeIFSet()
		 */
		void MakeIFSet(int faceNum, int polyNum, cli::array<int>^ IFSet,
					   int vertexNum, cli::array<fk_Vector^>^ posArray, int order);

		//! 任意形状生成関数1-2
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *	この関数形式の場合、全ての面が同じ角数である必要があります。
		 *	角数の異なる面が混在する形状を作成したい場合は、
		 *	MakeIFSet(cli::array< cli::array<int>^ >^, cli::array<fk_Vector^>^, int)
		 *	を利用して下さい。
		 *
		 *	本関数は、
		 *	MakeIFSet(int, int, cli::array<int>^, int, cli::array<fk_Vector^>^, int) において、
		 *	第6引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	faceNum		面数
		 *
		 *	\param[in]	polyNum		面の角数。3以上の値を入力できます。
		 *
		 *	\param[in]	IFSet
		 *		インデックスフェースセット配列。
		 *		この配列は、各面を構成する頂点 ID を並べたものになります。
		 *		たとえば、頂点 ID が [0, 1, 2] と [2, 1, 3] という構成を持つ
		 *		2面からなる形状を生成する場合、int 型の配列に対して
		 *		[0, 1, 2, 2, 1, 3] という数値を入力しておきます。
		 *		結果的に、この配列の長さは面数と角数を掛けたもの以上である必要があります。
		 *		
		 *	\param[in]	vertexNum	頂点数
		 *
		 *	\param[in]	posArray
		 *		頂点位置ベクトルの配列。配列の長さは頂点数以上である必要があります。
		 *
		 *	\sa fk_IndexFaceSet::MakeIFSet()
		 */
		void MakeIFSet(int faceNum, int polyNum, cli::array<int>^ IFSet,
					   int vertexNum, cli::array<fk_Vector^>^ posArray);

		//! 任意形状生成関数2-1
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *
		 *	\param[in]	faceArray
		 *		面データ配列。この配列は「ジャグ配列」となっており、
		 *		頂点IDの1次元配列が一つの面の頂点IDの集合となります。
		 *		この「頂点IDの1次元配列」の配列とすることで、
		 *		形状全体の位相情報を表します。
		 *
		 *	\param[in]	posArray	頂点位置ベクトルデータ配列
		 *	\param[in]	order		最初の頂点IDを補正するオーダー。通常は省略して問題ありません。
		 */
		void MakeIFSet(cli::array< cli::array<int>^ >^ faceArray,
					   cli::array<fk_Vector^>^ posArray, int order);

		//! 任意形状生成関数2-2
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *	本関数は、 MakeIFSet(cli::array< cli::array<int>^ >^, cli::array<fk_Vector^>^, int) において、
		 *	第3引数の 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	faceArray
		 *		面データ配列。この配列は「ジャグ配列」となっており、
		 *		頂点IDの1次元配列が一つの面の頂点IDの集合となります。
		 *		この「頂点IDの1次元配列」の配列とすることで、
		 *		形状全体の位相情報を表します。
		 *
		 *	\param[in]	posArray	頂点位置ベクトルデータ配列
		 */
		void MakeIFSet(cli::array< cli::array<int>^ >^ faceArray,
					   cli::array<fk_Vector^>^ posArray);
	};
}
