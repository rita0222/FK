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
#ifndef __FK_HEAP_BASE_HEADER__
#define __FK_HEAP_BASE_HEADER__

#include <vector>

//! 重複要素に同一IDを与えるための汎用テンプレート
/*!
 *	このテンプレートは、重複要素を管理する機能を提供します。
 *	管理したいインスタンスを getID() 関数に代入したとき、
 *	既に同じ値を持つインスタンスが代入済みであった場合にはその ID を返します。
 *	初めて代入された値であった場合は、新しい ID を返します。
 *	内部ではヒープソートを用いているため、
 *	要素数が増加してもそれほど処理速度は低下しません。
 *
 *	対象となるクラスあるいは型においては、以下の条件を満たす必要があります。
 *	- 等号演算子「==」によって値の同一性比較ができる。
 *	- 不等号演算子「>」および「<」によって大小比較ができる。
 *	- 不等号において、a < b かつ b < c であるならば a < c であるという
 *		推移律が必ず成り立つ。逆方向も同様。
 *	- getID() 関数を用いる際、これまでに格納した全インスタンスが生存している。
 *	.
 *	\remarks
 *	本クラスは現在ベータ機能としての位置づけであり、
 *	ユーザーズマニュアルには記載されていません。
 *	また、今後のバージョンアップにおいて仕様が変更される可能性があります。
 */

typedef std::vector<int>::size_type		_fk_h_s;

//! 重複要素に同一IDを与えるための汎用テンプレート
/*!
 *	このテンプレートは、重複要素を管理する機能を提供します。
 *	管理したいインスタンスを getID() 関数に代入したとき、
 *	既に同じ値を持つインスタンスが代入済みであった場合にはその ID を返します。
 *	初めて代入された値であった場合は、新しい ID を返します。
 *	内部ではヒープソートを用いているため、
 *	要素数が増加してもそれほど処理速度は低下しません。
 *
 *	対象となるクラスあるいは型においては、以下の条件を満たす必要があります。
 *	- 等号演算子「==」によって値の同一性比較ができる。
 *	- 不等号演算子「>」および「<」によって大小比較ができる。
 *	- 不等号において、a < b かつ b < c であるならば a < c であるという
 *		推移律が必ず成り立つ。逆方向も同様。
 *	- getID() 関数を用いる際、これまでに格納した全インスタンスが生存している。
 *	.
 *	\remarks
 *	本クラスは現在ベータ機能としての位置づけであり、
 *	ユーザーズマニュアルには記載されていません。
 *	また、今後のバージョンアップにおいて仕様が変更される可能性があります。
 */

template<class TYPE> class fk_HeapBase {
 private:
	std::vector<TYPE *>		array;
	std::vector<int>		id;

	int Compare(TYPE *a, TYPE *b) {
		if(*a < *b) return -1;
		if(*a > *b) return 1;
		return 0;
	}

	int HeapData(TYPE *argData, int argS, int argE) {
		TYPE	*pData;
		int		comp;
		int		index;

		if(argE == -1) {
			pData = new TYPE();
			*pData = *argData;
			array.insert(array.begin(), pData);
			id.insert(id.begin(), 1);
			return 1;
		}

		if(argS == argE) {
			comp = Compare(argData, array[static_cast<_fk_h_s>(argS)]);
			if(comp == 0) {
				return id[static_cast<_fk_h_s>(argS)];
			}

			pData = new TYPE();
			*pData = *argData;
			if(comp == -1) {
				array.insert(array.begin()+argS, pData);
				id.insert(id.begin()+argS,
						  static_cast<int>(array.size()));
			} else {
				array.insert(array.begin()+argS+1, pData);
				id.insert(id.begin()+argS+1,
						  static_cast<int>(array.size()));
			}
			return static_cast<int>(array.size());
		}

		if(argE - argS == 1) {
			comp = Compare(argData,
						   array[static_cast<_fk_h_s>(argS)]);

			if(comp == 0) {
				return id[static_cast<_fk_h_s>(argS)];
			}

			if(comp == -1) {
				pData = new TYPE();
				*pData = *argData;
				array.insert(array.begin()+argS, pData);
				id.insert(id.begin()+argS,
						  static_cast<int>(array.size()));
				return static_cast<int>(array.size());
			}

			return HeapData(argData, argE, argE);
		}

		index = (argE-argS)/2 + argS;

		comp = Compare(argData, array[static_cast<_fk_h_s>(index)]);

		if(comp == 0) {
			return id[static_cast<_fk_h_s>(index)];
		}

		if(comp == -1) {
			return HeapData(argData, argS, index);
		}

		if(comp == 1) {
			return HeapData(argData, index, argE);
		}

		return 0;
	}

			
 public:
			
	//! コンストラクタ
	fk_HeapBase(void) { clear(); }

	//! デストラクタ
	virtual ~fk_HeapBase() { clear(); }

	//! 初期化関数
	/*!
	 *	これまで格納した情報を全て初期化します。
	 *	この関数を呼んだ場合、過去に格納したインスタンスは解放しても構いません。
	 */
	void clear(void);

	/*!
	 *	現時点での要素数を返します。
	 *	これは、これまで返された ID の最大値でもあります。
	 *	\return 要素数
	 */
	int getSize(void) {
		return static_cast<int>(array.size());
	}

	/*!
	 *	以下の条件で ID となる値を返します。
	 *	- はじめて値を格納する場合、
	 *		あるいは clear() を呼んではじめて値を格納する場合、
	 *		ID として 1 を返します。
	 *	- argV の値がこれまでに格納されたインスタンスの値と等しい場合、
	 *		そのインスタンスの ID を返します。
	 *	- argV がこれまでに格納されたどのインスタンスとも値が異なる場合、
	 *	   	新しい ID を返します。
	 *
	 *	\param[in] argV	比較対象インスタンスのアドレス
	 */
	int getID(TYPE *argV) {
		return HeapData(argV, 0, getSize()-1);
	}
};

template<class TYPE> void fk_HeapBase<TYPE>::clear(void) {
	for(unsigned int i = 0; i < array.size(); i++) {
		delete array[i];
	}

	array.clear();
	id.clear();
	return;
}

#endif // !__FK_HEAP_BASE_HEADER__

