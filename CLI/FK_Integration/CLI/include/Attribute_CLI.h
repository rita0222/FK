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
		 *	\param[in] key キー
		 *	\param[in] value 値
		 *
		 *	\return
		 *
		 *	\sa GetAttrII(), existAttrII(), deleteAttrII()
		 */
		bool SetAttrII(int key, int value);

		//! キーが int 型、値が double 型である属性設定関数
		/*!
		 *	\param[in] key キー
		 *	\param[in] value 値
		 */
		bool SetAttrID(int key, double value);

		//! キーが int 型、値が string 型である属性設定関数
		/*!
		 *	\param[in] key キー
		 *	\param[in] value 値
		 */
		bool SetAttrIS(int key, String^ value);

		//! キーが string 型、値が int 型である属性設定関数
		/*!
		 *	\param[in] key キー
		 *	\param[in] value 値
		 */

		bool SetAttrSI(String^ key, int value);

		//! キーが string 型、値が double 型である属性設定関数
		/*!
		 *	\param[in] key キー
		 *	\param[in] value 値
		 */

		bool SetAttrSD(String^ key, double value);

		//! キーが string 型、値が string 型である属性設定関数
		/*!
		 *	\param[in] key キー
		 *	\param[in] value 値
		 */

		bool SetAttrSS(String ^key, String^ value);
		//@}

		int GetAttrII(int key);
		double GetAttrID(int key);
		String^ GetAttrIS(int key);
		int GetAttrSI(String^ key);
		double GetAttrSD(String^ key);
		String^ GetAttrSS(String^ key);
		bool ExistAttrII(int key);
		bool ExistAttrID(int key);
		bool ExistAttrIS(int key);
		bool ExistAttrSI(String^ key);
		bool ExistAttrSD(String^ key);
		bool ExistAttrSS(String^ key);
		bool DeleteAttrII(int key);
		bool DeleteAttrID(int key);
		bool DeleteAttrIS(int key);
		bool DeleteAttrSI(String^ key);
		bool DeleteAttrSD(String^ key);
		bool DeleteAttrSS(String^ key);
	};
}
