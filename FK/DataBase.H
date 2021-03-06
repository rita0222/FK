﻿#ifndef __FK_DATABASE_HEADER__
#define __FK_DATABASE_HEADER__

#include <FK/IDAdmin.H>
#include <vector>

namespace FK {
	class fk_Vertex;
	class fk_Half;
	class fk_Edge;
	class fk_Loop;

	class fk_DataBase {

		friend class fk_DataAccess;
		friend class fk_IFSetHandle;

		class Member {
		public:
			fk_IDAdmin vAdmin;
			fk_IDAdmin hAdmin;
			fk_IDAdmin eAdmin;
			fk_IDAdmin lAdmin;

			std::vector<fk_Vertex> vSet;
			std::vector<fk_Half> hSet;
			std::vector<fk_Edge> eSet;
			std::vector<fk_Loop> lSet;

			Member(void);
		};

	public:
		
		fk_DataBase(void);		// コンストラクタ
		virtual ~fk_DataBase();	// デストラクタ

		void AllClear(void);
		void CloneData(fk_DataBase *);
		bool Compare(fk_DataBase *);

		bool ExistVertex(fk_Vertex *) const;
		bool ExistVertex(int) const;
		bool ExistHalf(fk_Half *) const;
		bool ExistHalf(int) const;
		bool ExistEdge(fk_Edge *) const;
		bool ExistEdge(int) const;
		bool ExistLoop(fk_Loop *) const;
		bool ExistLoop(int) const;

		fk_Vertex * GetVData(int);
		fk_Half * GetHData(int);
		fk_Edge * GetEData(int);
		fk_Loop * GetLData(int);

		fk_Vertex * GetNextV(fk_Vertex *);
		fk_Half * GetNextH(fk_Half *);
		fk_Edge * GetNextE(fk_Edge *);
		fk_Loop * GetNextL(fk_Loop *);

		fk_Vertex * GetLastV(void);
		fk_Half * GetLastH(void);
		fk_Edge * GetLastE(void);
		fk_Loop * GetLastL(void);

		int GetVNum(void) const;
		int GetHNum(void) const;
		int GetENum(void) const;
		int GetLNum(void) const;

		void VPrint(int = FK_UNDEFINED) const;
		void HPrint(int = FK_UNDEFINED) const;
		void EPrint(int = FK_UNDEFINED) const;
		void LPrint(int = FK_UNDEFINED) const;

		void AllPrint(void) const;

		bool VCheck(int = FK_UNDEFINED) const;
		bool HCheck(int = FK_UNDEFINED) const;
		bool ECheck(int = FK_UNDEFINED) const;
		bool LCheck(int = FK_UNDEFINED) const;

		bool AllCheck(void) const;

	private:

		std::unique_ptr<Member> _m;

		void ResizeData(fk_DataBase *);
		void ResizeData(int, int, int, int);
		void VSetClone(std::vector<fk_Vertex> *);
		void HSetClone(std::vector<fk_Half> *);
		void ESetClone(std::vector<fk_Edge> *);
		void LSetClone(std::vector<fk_Loop> *);

		bool VCompare(fk_DataBase *);
		bool HCompare(fk_DataBase *);
		bool ECompare(fk_DataBase *);
		bool LCompare(fk_DataBase *);

		fk_Vertex * GetNewVertex(void);
		fk_Vertex * GetNewVertex(int);
		fk_Half * GetNewHalf(void);
		fk_Half * GetNewHalf(int);
		fk_Edge * GetNewEdge(void);
		fk_Edge * GetNewEdge(int);
		fk_Loop * GetNewLoop(void);
		fk_Loop * GetNewLoop(int);

		bool DeleteVertex(int);
		bool DeleteHalf(int);
		bool DeleteEdge(int);
		bool DeleteLoop(int);
	};
}

#endif // !__FK_DATABASE_HEADER__

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
