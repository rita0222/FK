#include "GenVector_CLI.h"

namespace FK_CLI {

	using namespace std;
		
	fk_GenVector::fk_GenVector()
	{
		pGVec = new ::FK::fk_GenVector();
	}

	fk_GenVector::fk_GenVector(int deg)
	{
		pGVec = new ::FK::fk_GenVector(deg);
	}

	fk_GenVector::fk_GenVector(::FK::fk_GenVector *argV)
	{
		pGVec = new ::FK::fk_GenVector(*argV);
	}

	fk_GenVector::fk_GenVector(IEnumerable<double>^ argArray)
	{
		vector<double>	pD;
		int				count = 0;

		IEnumerator<double>^ d = argArray->GetEnumerator();

		while (d->MoveNext()) {
			pD.push_back(d->Current);
			count++;
		}
		pGVec = new ::FK::fk_GenVector(count, &pD[0]);
	}

	fk_GenVector::fk_GenVector(fk_Vector^ argV)
	{
		if(!argV) {
			pGVec = new ::FK::fk_GenVector();
		} else {
			::FK::fk_Vector V(argV->x_, argV->y_, argV->z_);
			pGVec = new ::FK::fk_GenVector(V);
		}
	}

	fk_GenVector::fk_GenVector(fk_HVector^ argH)
	{
		if(!argH) {
			pGVec = new ::FK::fk_GenVector();
		} else {
			pGVec = new ::FK::fk_GenVector(::FK::fk_HVector(argH->x_, argH->y_, argH->z_, argH->w_));
		}
	}
		
	fk_GenVector::fk_GenVector(fk_GenVector^ argGV)
	{
		if(!argGV) {
			pGVec = new ::FK::fk_GenVector();
		} else {
			pGVec = new ::FK::fk_GenVector(*argGV->pGVec);
		}
	}

	fk_GenVector::~fk_GenVector()
	{
		this->!fk_GenVector();
	}

	fk_GenVector::!fk_GenVector()
	{
		delete pGVec;
	}

	bool fk_GenVector::Equals(fk_GenVector^ argGV)
	{
		if(!argGV) return false;
		return (*argGV->pGVec == *pGVec);
	}

	bool fk_GenVector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_GenVector^ GV = static_cast<fk_GenVector^>(argObj);
			return (*GV->pGVec == *pGVec);
		}
		return false;
	}

	//////////////////// 単項演算子
	fk_GenVector^ fk_GenVector::operator-(fk_GenVector^ argV)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = -(*argV->pGVec);
		return V;
	}

	double fk_GenVector::operator*(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return 0.0;
		return (*argV1->pGVec) * (*argV2->pGVec);
	}
		
	fk_GenVector^ fk_GenVector::operator+(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) + (*argV2->pGVec);
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator-(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) - (*argV2->pGVec);
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator*(fk_GenVector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec * argD;
		return V;
	}
						  
	fk_GenVector^ fk_GenVector::operator*(double argD, fk_GenVector^ argV)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec * argD;
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator/(fk_GenVector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec/argD;
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator ^(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) ^ (*argV2->pGVec);
		return V;
	}

	//代入演算子 
	void fk_GenVector::operator *=(fk_GenVector^ argV, double argD)
	{
		if(!argV) return;
		*argV->pGVec *= argD;
	}

	void fk_GenVector::operator /=(fk_GenVector^ argV, double argD)
	{
		if(!argV) return;
		*argV->pGVec /= argD;
	}

	void fk_GenVector::operator +=(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return;
		*argV1->pGVec += *argV2->pGVec;
	}

	void fk_GenVector::operator -=(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return;
		*argV1->pGVec -= *argV2->pGVec;
	}


	String^	fk_GenVector::ToString()
	{
		string tmpBuf;
		int size = pGVec->size();

		tmpBuf += "GV = ";
		for(int i = 0; i < size; ++i) {
			tmpBuf += to_string(pGVec->get(i));
			if(i != size-1) tmpBuf += ", ";
		}
		return gcnew String(tmpBuf.c_str());
	}

	void fk_GenVector::default::set(int argID, double argValue)
	{
		pGVec->set(argID, argValue);
	}
	
	double fk_GenVector::default::get(int argID)
	{
		return pGVec->get(argID);
	}

	void fk_GenVector::Size::set(int argDeg)
	{
		pGVec->resize(argDeg);
	}
	
	int fk_GenVector::Size::get(void)
	{
		return pGVec->size();
	}
	
	double fk_GenVector::Norm::get(void)
	{
		return pGVec->norm();
	}
	
	double fk_GenVector::Norm2::get(void)
	{
		return pGVec->norm2();
	}
	
	bool fk_GenVector::Normalize(void)
	{
		return pGVec->normalize();
	}
	
	void fk_GenVector::Init(bool argDegFlg)
	{
		pGVec->init(argDegFlg);
	}
	
	void fk_GenVector::Init(void)
	{
		pGVec->init();
	}
	
	bool fk_GenVector::IsZero(void)
	{
		return pGVec->isZero();
	}
	
	bool fk_GenVector::Replace(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pGVec);
	}
	
	bool fk_GenVector::Replace(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		::FK::fk_Vector V(argV->x_, argV->y_, argV->z_);
		return pGVec->replace(argS, V);
	}

	bool fk_GenVector::Replace(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		::FK::fk_HVector V(argV->x_, argV->y_, argV->z_, argV->w_);
		return pGVec->replace(argS, V);
	}

	bool fk_GenVector::Add(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pGVec);
	}

	bool fk_GenVector::Add(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		::FK::fk_Vector V(argV->x_, argV->y_, argV->z_);
		return pGVec->add(argS, V);
	}

	bool fk_GenVector::Add(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		::FK::fk_HVector V(argV->x_, argV->y_, argV->z_, argV->w_);
		return pGVec->add(argS, V);
	}

	bool fk_GenVector::Sub(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pGVec);
	}

	bool fk_GenVector::Sub(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		::FK::fk_Vector V(argV->x_, argV->y_, argV->z_);
		return pGVec->sub(argS, V);
	}

	bool fk_GenVector::Sub(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		::FK::fk_HVector V(argV->x_, argV->y_, argV->z_, argV->w_);
		return pGVec->sub(argS, V);
	}

	fk_GenVector^ fk_GenVector::Div(int argS, int argE)
	{
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = pGVec->div(argS, argE);
		return V;
	}
}

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
