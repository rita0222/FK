#include "GenMatrix_CLI.h"

namespace FK_CLI {
	using namespace std;

	fk_GenMatrix::fk_GenMatrix()
	{
		pGMat = new ::FK::fk_GenMatrix();
	}

	fk_GenMatrix::fk_GenMatrix(int argDeg)
	{
		pGMat = new ::FK::fk_GenMatrix(argDeg);
	}

	fk_GenMatrix::~fk_GenMatrix()
	{
		this->!fk_GenMatrix();
	}

	fk_GenMatrix::!fk_GenMatrix()
	{
		delete pGMat;
	}

/*
	double fk_GenMatrix::m::get(int argI1, int argI2)
	{
		return pGMat->get(argI1, argI2);
	}

	void fk_GenMatrix::m::set(int argI1, int argI2, double argD)
	{
		pGMat->set(argI1, argI2, argD);
	}
*/

	double fk_GenMatrix::Get(int argI1, int argI2)
	{
		return pGMat->get(argI1, argI2);
	}

	void fk_GenMatrix::Set(int argI1, int argI2, double argD)
	{
		pGMat->set(argI1, argI2, argD);
	}

	void fk_GenMatrix::Degree::set(int argDeg)
	{
		pGMat->setDeg(argDeg);
	}

	int fk_GenMatrix::Degree::get(void)
	{
		return pGMat->getDeg();
	}

	bool fk_GenMatrix::Equals(fk_GenMatrix^ argM)
	{
		if(!argM) return false;
		return (*argM->pGMat == *pGMat);
	}

	bool fk_GenMatrix::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_GenMatrix^ M = static_cast<fk_GenMatrix^>(argObj);
			return (*M->pGMat == *pGMat);
		}
		return false;
	}

	String^	fk_GenMatrix::ToString()
	{
		string tmpBuf;
		int deg = pGMat->getDeg();

		tmpBuf += "GM = \n";
		for(int i = 0; i < deg; ++i) {
			tmpBuf += "\t";
			for(int j = 0; j < deg; j++) {
				tmpBuf += to_string(pGMat->get(i, j));
				if(j != deg - 1) tmpBuf += ", ";
			}
			tmpBuf += "\n";
		}
		return gcnew String(tmpBuf.c_str());
	}
				
	fk_GenVector^ fk_GenMatrix::operator*(fk_GenMatrix^ argM, fk_GenVector^ argV)
	{
		if(!argM || !argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argM->pGMat) * (*argV->pGVec);
		return V;
	}

	fk_GenMatrix^ fk_GenMatrix::operator*(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) * (*argM2->pGMat);
		return M;
	}

	fk_GenMatrix^ fk_GenMatrix::operator-(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) - (*argM2->pGMat);
		return M;
	}

	fk_GenMatrix^ fk_GenMatrix::operator+(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) + (*argM2->pGMat);
		return M;
	}

	void fk_GenMatrix::operator +=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat += *argM2->pGMat;
	}

	void fk_GenMatrix::operator -=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat -= *argM2->pGMat;
	}

	void fk_GenMatrix::operator *=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat *= *argM2->pGMat;
	}

	void fk_GenMatrix::operator *=(fk_GenVector^ argV, fk_GenMatrix^ argM)
	{
		if(!argV || !argM) return;
		*argV->pGVec *= *argM->pGMat;
	}

	void fk_GenMatrix::Init(bool argInitFlg)
	{
		pGMat->init(argInitFlg);
	}
	
	void fk_GenMatrix::Init(void)
	{
		pGMat->init();
	}
	
	bool fk_GenMatrix::Inverse(void)
	{
		return pGMat->inverse();
	}

	fk_GenMatrix^ fk_GenMatrix::GetInverse(void)
	{
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = !(*pGMat);
		return M;
	}
	
	void fk_GenMatrix::Negate(void)
	{
		pGMat->negate();
	}
	
	bool fk_GenMatrix::IsRegular(void)
	{
		return pGMat->isRegular();
	}
	
	bool fk_GenMatrix::IsSingular(void)
	{
		return pGMat->isSingular();
	}
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
