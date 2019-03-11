#ifndef __FK_ATTIRIBUTE_DATA_HEADER__
#define __FK_ATTIRIBUTE_DATA_HEADER__

#include <vector>
#include <string>

namespace FK {

	class fk_Attribute_Data {

	public:
		fk_Attribute_Data(void);
		virtual ~fk_Attribute_Data();

		void	AttrInit(void);

		// もしすでに要素が存在したら true を、そうでなければ false を返す。

		bool	ExistAttrII(const int) const;
		bool	ExistAttrID(const int) const;
		bool	ExistAttrIS(const int) const;
		bool	ExistAttrSI(const std::string) const;
		bool	ExistAttrSD(const std::string) const;
		bool	ExistAttrSS(const std::string) const;

		// 返り値は exist 系と同様。

		bool	SetAttrII(const int, const int);
		bool	SetAttrID(const int, const double);
		bool	SetAttrIS(const int, const std::string);
		bool	SetAttrSI(const std::string, const int);
		bool	SetAttrSD(const std::string, const double);
		bool	SetAttrSS(const std::string, const std::string);

		// 属性を得るための関数。

		int				GetAttrII(const int) const;
		double			GetAttrID(const int) const;
		std::string		GetAttrIS(const int) const;
		int				GetAttrSI(const std::string) const;
		double			GetAttrSD(const std::string) const;
		std::string		GetAttrSS(const std::string) const;

		// 属性を消去するための関数。

		bool	DeleteAttrII(const int);
		bool	DeleteAttrID(const int);
		bool	DeleteAttrIS(const int);
		bool	DeleteAttrSI(const std::string);
		bool	DeleteAttrSD(const std::string);
		bool	DeleteAttrSS(const std::string);

	private:
		std::vector<int>			*ItoIIndex;
		std::vector<int>			*ItoIValue;

		std::vector<int>			*ItoDIndex;
		std::vector<double>			*ItoDValue;

		std::vector<int>			*ItoSIndex;
		std::vector<std::string>	*ItoSValue;

		std::vector<std::string>	*StoIIndex;
		std::vector<int>			*StoIValue;

		std::vector<std::string>	*StoDIndex;
		std::vector<double>			*StoDValue;

		std::vector<std::string>	*StoSIndex;
		std::vector<std::string>	*StoSValue;

		int		GetIndexAttrII(const int) const;
		int		GetIndexAttrID(const int) const;
		int		GetIndexAttrIS(const int) const;
		int		GetIndexAttrSI(const std::string) const;
		int		GetIndexAttrSD(const std::string) const;
		int		GetIndexAttrSS(const std::string) const;

		int		CreateNewIndexI(std::vector<int> *, int);
		int		CreateNewIndexS(std::vector<std::string> *, std::string);
	};
}

#endif // !__FK_ATTRIBUTE_DATA_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
