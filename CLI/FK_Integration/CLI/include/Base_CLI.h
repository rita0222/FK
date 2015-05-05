// Base_CLI.h

#pragma once

#include <FK/Base.h>

namespace FK_CLI {
	using namespace System;

	//! リテラル管理クラス
	/*!
	 *	このクラスは、FK 内で用いるリテラル(固定値)を管理します。
	 */
	public ref class FK {
	public:
		literal double PI = _FK_PI_DEFINE_;		//!< 円周率
		literal double EPS = _FK_EPS_DEFINE_;	//!< 数値演算用誤差値
	};

	//! FK の各クラスの基盤となる基本クラス
	/*!
	 *	このクラスは、FKのユーザが利用する大半のクラスの基底クラスとなっています。
	 */
	public ref class fk_BaseObject {
	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		bool dFlg;
		::fk_BaseObject *pBase;
		//! コンストラクタ
		fk_BaseObject(bool);

		//! デストラクタ
		~fk_BaseObject();

		//! ファイナライザ
		!fk_BaseObject();
#endif
	};
}


