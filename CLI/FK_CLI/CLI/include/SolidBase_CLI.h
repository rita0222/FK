// Modify_CLI.h

#pragma once

#include <FK/SolidBase.h>
#include "Modify_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;
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
		 *	MakeIFSet(IEnumerable< IEnumerable<int>^ >^, IEnumerable<fk_Vector^>^, int);
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
		void MakeIFSet(int faceNum, int polyNum,
					   IEnumerable<int>^ IFSet,
					   int vertexNum,
					   IEnumerable<fk_Vector^>^ posArray,
					   int order);

		//! 任意形状生成関数1-2
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *	この関数形式の場合、全ての面が同じ角数である必要があります。
		 *	角数の異なる面が混在する形状を作成したい場合は、
		 *	MakeIFSet(IEnumerable< IEnumerable<int>^ >^, IEnumerable<fk_Vector^>^, int)
		 *	を利用して下さい。
		 *
		 *	本関数は、
		 *	MakeIFSet(int, int, IEnumerable<int>^, int, IEnumerable<fk_Vector^>^, int) において、
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
		void MakeIFSet(int faceNum, int polyNum,
					   IEnumerable<int>^ IFSet,
					   int vertexNum,
					   IEnumerable<fk_Vector^>^ posArray);

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
		void MakeIFSet(IEnumerable< IEnumerable<int>^ >^ faceArray,
					   IEnumerable<fk_Vector^>^ posArray,
					   int order);

		//! 任意形状生成関数2-2
		/*!
		 *	与えられたIFSデータから、形状を生成します。
		 *	本関数は、
		 *	MakeIFSet(IEnumerable< IEnumerable<int>^ >^, IEnumerable<fk_Vector^>^, int) において、
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
		void MakeIFSet(IEnumerable< IEnumerable<int>^ >^ faceArray,
					   IEnumerable<fk_Vector^>^ posArray);
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
