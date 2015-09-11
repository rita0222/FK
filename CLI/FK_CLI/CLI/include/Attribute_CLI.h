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
		::fk_Attribute * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Attribute(bool argNewFlg);
		~fk_Attribute();
		!fk_Attribute();
#endif
		
		//! \name 属性設定用関数
		//@{

		//! キーが int 型、値が int 型である属性設定関数
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

		//! キーが int 型、値が double 型である属性設定関数
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

		//! キーが int 型、値が std::string 型である属性設定関数
		/*!
		 *	キーを int 型、値を std::string 型とする属性を設定します。
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

		//! キーが std::string 型、値が int 型である属性設定関数
		/*!
		 *	キーを std::string 型、値を int 型とする属性を設定します。
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

		//! キーが std::string 型、値が double 型である属性設定関数
		/*!
		 *	キーを std::string 型、値を double 型とする属性を設定します。
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

		//! キーが std::string 型、値が std::string 型である属性設定関数
		/*!
		 *	キーを std::string 型、値を std::string 型とする属性を設定します。
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
		//@}

		//! \name 属性取得用関数
		//@{

		//! キーが int 型、値が int 型である属性参照関数
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

		//! キーが int 型、値が double 型である属性参照関数
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

		//! キーが int 型、値が std::string 型である属性参照関数
		/*!
		 *	キーが int 型、値が std::string 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、空文字列を返します。
		 *
		 *	\sa SetAttrIS(), ExistAttrIS(), DeleteAttrIS()
		 */
		String^ GetAttrIS(int key);

		//! キーが std::string 型、値が int 型である属性参照関数
		/*!
		 *	キーが std::string 型、値が int 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0 を返します。
		 *
		 *	\sa SetAttrSI(), ExistAttrSI(), DeleteAttrSI()
		 */
		int GetAttrSI(String^ key);

		//! キーが std::string 型、値が double 型である属性参照関数
		/*!
		 *	キーが std::string 型、値が double 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、0.0 を返します。
		 *
		 *	\sa SetAttrSD(), ExistAttrSD(), DeleteAttrSD()
		 */
		double GetAttrSD(String^ key);

		//! キーが std::string 型、値が std::string 型である属性参照関数
		/*!
		 *	キーが std::string 型、値が std::string 型である属性を参照します。
		 *
		 *	\param[in] key キー
		 *
		 *	\return 属性値。もしその属性が存在しなかった場合、空文字列を返します。
		 *
		 *	\sa SetAttrSS(), ExistAttrSS(), DeleteAttrSS()
		 */
		String^ GetAttrSS(String^ key);
		//@}
		
		//! \name 属性存在参照関数
		//@{
		//! キーが int 型、値が int 型である属性存在参照関数
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

		//! キーが int 型、値が double 型である属性存在参照関数
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

		//! キーが int 型、値が std::string 型である属性存在参照関数
		/*!
		 *	キーが int 型、値が std::string 型である属性に対し、
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

		//! キーが std::string 型、値が int 型である属性存在参照関数
		/*!
		 *	キーが std::string 型、値が int 型である属性に対し、
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

		//! キーが std::string 型、値が double 型である属性存在参照関数
		/*!
		 *	キーが std::string 型、値が double 型である属性に対し、
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

		//! キーが std::string 型、値が std::string 型である属性存在参照関数
		/*!
		 *	キーが std::string 型、値が std::string 型である属性に対し、
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

		//@}
		//! \name 属性消去関数
		//@{	
		//! キーが int 型、値が int 型である属性消去関数
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

		//! キーが int 型、値が double 型である属性消去関数
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

		//! キーが int 型、値が std::string 型である属性消去関数
		/*!
		 *	キーが int 型、値が std::string 型である属性に対し、
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

		//! キーが std::string 型、値が int 型である属性消去関数
		/*!
		 *	キーが std::string 型、値が int 型である属性に対し、
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

		//! キーが std::string 型、値が double 型である属性消去関数
		/*!
		 *	キーが std::string 型、値が double 型である属性に対し、
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

		//! キーが std::string 型、値が std::string 型である属性消去関数
		/*!
		 *	キーが std::string 型、値が std::string 型である属性に対し、
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
		//@}
	};
}
