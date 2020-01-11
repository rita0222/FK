/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
// Attribute_CLI.h

#pragma once

#include <FK/Attribute.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	//!	形状や位相要素の属性を付与、取得するクラス
	/*!
	 *	このクラスは、 fk_Block や fk_Solid などの形状を表すインスタンスや、
	 *	fk_Solid による形状中の各位相要素に対して属性を付与する機能を提供します。
	 *	属性はハッシュマップによるもので、キーとして int か string の 2 種、
	 *	値として int、double、string の 3 種を使用することができます。
	 */
	public ref class fk_Attribute : fk_BaseObject {
	internal:
		::FK::fk_Attribute * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Attribute(bool argNewFlg);
		~fk_Attribute();
		!fk_Attribute();
#endif
		
		//! \name 属性設定用メソッド
		///@{

		//! キーが int 型、値が int 型である属性設定メソッド
		/*!
		 *	キーを int 型、値を int 型とする属性を設定します。
		 *	
		 *	\param[in] key		キー。ただし、負数は受け付けません。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrII(), ExistAttrII(), DeleteAttrII()
		 */
		bool SetAttrII(int key, int value);

		//! キーが int 型、値が double 型である属性設定メソッド
		/*!
		 *	キーを int 型、値を double 型とする属性を設定します。
		 *	
		 *	\param[in] key 		キー。ただし、負数は受け付けません。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrID(), ExistAttrID(), DeleteAttrID()
		 */
		bool SetAttrID(int key, double value);

		//! キーが int 型、値が String 型である属性設定メソッド
		/*!
		 *	キーを int 型、値を String 型とする属性を設定します。
		 *
		 *	\param[in] key		キー。ただし、負数は受け付けません。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrIS(), ExistAttrIS(), DeleteAttrIS()
		 */
		bool SetAttrIS(int key, String^ value);

		//! キーが String 型、値が int 型である属性設定メソッド
		/*!
		 *	キーを String 型、値を int 型とする属性を設定します。
		 *	
		 *	\param[in] key		キー。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrSI(), ExistAttrSI(), DeleteAttrSI()
		 */
		bool SetAttrSI(String^ key, int value);

		//! キーが String 型、値が double 型である属性設定メソッド
		/*!
		 *	キーを String 型、値を double 型とする属性を設定します。
		 *	
		 *	\param[in] key		キー。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrSD(), ExistAttrSD(), DeleteAttrSD()
		 */
		bool SetAttrSD(String^ key, double value);

		//! キーが String 型、値が String 型である属性設定メソッド
		/*!
		 *	キーを String 型、値を String 型とする属性を設定します。
		 *	
		 *	\param[in] key		キー。
		 *	\param[in] value 	値。
		 *
		 *	\return
		 *		既にそのキーで属性が存在していた場合 true を、
		 *		存在していなかった場合は false を返します。
		 *
		 *	\sa GetAttrSS(), ExistAttrSS(), DeleteAttrSS()
		 */
		bool SetAttrSS(String ^key, String^ value);
		///@}

		//! \name 属性取得用メソッド
		///@{

		//! キーが int 型、値が int 型である属性参照メソッド
		/*!
		 *	キーが int 型、値が int 方である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0 を返します。
		 *
		 *	\sa SetAttrII(), ExistAttrII(), DeleteAttrII()
		 */
		int GetAttrII(int key);

		//! キーが int 型、値が double 型である属性参照メソッド
		/*!
		 *	キーが int 型、値が double 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0.0 を返します。
		 *
		 *	\sa SetAttrID(), ExistAttrID(), DeleteAttrID()
		 *
		 */
		double GetAttrID(int key);

		//! キーが int 型、値が String 型である属性参照メソッド
		/*!
		 *	キーが int 型、値が String 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、空文字列を返します。
		 *
		 *	\sa SetAttrIS(), ExistAttrIS(), DeleteAttrIS()
		 */
		String^ GetAttrIS(int key);

		//! キーが String 型、値が int 型である属性参照メソッド
		/*!
		 *	キーが String 型、値が int 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0 を返します。
		 *
		 *	\sa SetAttrSI(), ExistAttrSI(), DeleteAttrSI()
		 */
		int GetAttrSI(String^ key);

		//! キーが String 型、値が double 型である属性参照メソッド
		/*!
		 *	キーが String 型、値が double 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0.0 を返します。
		 *
		 *	\sa SetAttrSD(), ExistAttrSD(), DeleteAttrSD()
		 */
		double GetAttrSD(String^ key);

		//! キーが String 型、値が String 型である属性参照メソッド
		/*!
		 *	キーが String 型、値が String 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、空文字列を返します。
		 *
		 *	\sa SetAttrSS(), ExistAttrSS(), DeleteAttrSS()
		 */
		String^ GetAttrSS(String^ key);
		///@}
		
		//! \name 属性存在参照メソッド
		///@{

		//! キーが int 型、値が int 型である属性存在参照メソッド
		/*!
		 *	キーが int 型、値が int 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrII(), GetAttrII(), DeleteAttrII()
		 */
		bool ExistAttrII(int key);

		//! キーが int 型、値が double 型である属性存在参照メソッド
		/*!
		 *	キーが int 型、値が double 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrID(), GetAttrID(), DeleteAttrID()
		 */
		bool ExistAttrID(int key);

		//! キーが int 型、値が String 型である属性存在参照メソッド
		/*!
		 *	キーが int 型、値が String 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrIS(), GetAttrIS(), DeleteAttrIS()
		 */
		bool ExistAttrIS(int key);

		//! キーが String 型、値が int 型である属性存在参照メソッド
		/*!
		 *	キーが String 型、値が int 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrSI(), GetAttrSI(), DeleteAttrSI()
		 */
		bool ExistAttrSI(String^ key);

		//! キーが String 型、値が double 型である属性存在参照メソッド
		/*!
		 *	キーが String 型、値が double 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrSD(), GetAttrSD(), DeleteAttrSD()
		 */
		bool ExistAttrSD(String^ key);

		//! キーが String 型、値が String 型である属性存在参照メソッド
		/*!
		 *	キーが String 型、値が String 型である属性に対し、
		 *	指定したキーによる属性が既に存在しているかどうかを参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在している場合 true を、
		 *		存在しない場合 false を返します。
		 *
		 *	\sa SetAttrSS(), GetAttrSS(), DeleteAttrSS()
		 */
		bool ExistAttrSS(String^ key);

		///@}
		//! \name 属性消去メソッド
		///@{	

		//! キーが int 型、値が int 型である属性消去メソッド
		/*!
		 *	キーが int 型、値が int 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrII(), GetAttrII(), ExistAttrII()
		 */
		bool DeleteAttrII(int key);

		//! キーが int 型、値が double 型である属性消去メソッド
		/*!
		 *	キーが int 型、値が double 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrID(), GetAttrID(), ExistAttrID()
		 */
		bool DeleteAttrID(int key);

		//! キーが int 型、値が String 型である属性消去メソッド
		/*!
		 *	キーが int 型、値が String 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrIS(), GetAttrIS(), ExistAttrIS()
		 */
		bool DeleteAttrIS(int key);

		//! キーが String 型、値が int 型である属性消去メソッド
		/*!
		 *	キーが String 型、値が int 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrSI(), GetAttrSI(), ExistAttrSI()
		 */
		bool DeleteAttrSI(String^ key);

		//! キーが String 型、値が double 型である属性消去メソッド
		/*!
		 *	キーが String 型、値が double 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrSD(), GetAttrSD(), ExistAttrSD()
		 */
		bool DeleteAttrSD(String^ key);

		//! キーが String 型、値が String 型である属性消去メソッド
		/*!
		 *	キーが String 型、値が String 型である属性に対し、
		 *	指定されたキーの属性を消去します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return
		 *		もしその属性が存在していた場合 true を、
		 *		存在していなかった場合 false を返します。
		 *
		 *	\sa SetAttrSS(), GetAttrSS(), ExistAttrSS()
		 */
		bool DeleteAttrSS(String^ key);
		///@}
	};
}


