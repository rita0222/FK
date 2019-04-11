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
#include "Quaternion_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Quaternion::fk_Quaternion()
	{
		pQuat = new ::FK::fk_Quaternion();
	}

	fk_Quaternion::fk_Quaternion(double argS, double argX, double argY, double argZ)
	{
		pQuat = new ::FK::fk_Quaternion(argS, argX, argY, argZ);
	}

	fk_Quaternion::fk_Quaternion(double argS, fk_Vector^ argV)
	{
		if(!argV) {
			pQuat = new ::FK::fk_Quaternion(argS, 0.0, 0.0, 0.0);
		} else {
			pQuat = new ::FK::fk_Quaternion(argS, argV->x_, argV->y_, argV->z_);
		}
	}

	fk_Quaternion::fk_Quaternion(fk_Quaternion^ argQ)
	{
		pQuat = new ::FK::fk_Quaternion(*(argQ->pQuat));
	}

	fk_Quaternion::fk_Quaternion(::FK::fk_Quaternion *argQ)
	{
		pQuat = new ::FK::fk_Quaternion(argQ->s, argQ->v);
	}

	fk_Quaternion::fk_Quaternion(::FK::fk_Quaternion argQ)
	{
		pQuat = new ::FK::fk_Quaternion(argQ.s, argQ.v);
	}

	// デストラクタ
	fk_Quaternion::~fk_Quaternion()
	{
		this->!fk_Quaternion();
	}

	// ファイナライザ
	fk_Quaternion::!fk_Quaternion()
	{
		delete pQuat;
	}

	double fk_Quaternion::s::get()
	{
		return pQuat->s;
	}

	void fk_Quaternion::s::set(double value)
	{
		pQuat->s = value;
	}

	double fk_Quaternion::x::get()
	{
		return pQuat->v.x;
	}

	void fk_Quaternion::x::set(double value)
	{
		pQuat->v.x = value;
	}

	double fk_Quaternion::y::get()
	{
		return pQuat->v.y;
	}

	void fk_Quaternion::y::set(double value)
	{
		pQuat->v.y = value;
	}

	double fk_Quaternion::z::get()
	{
		return pQuat->v.z;
	}

	void fk_Quaternion::z::set(double value)
	{
		pQuat->v.z = value;
	}

	fk_Vector^ fk_Quaternion::v::get()
	{
		return gcnew fk_Vector(pQuat->v);
	}

	void fk_Quaternion::v::set(fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->v = argV;
	}

	void fk_Quaternion::Euler::set(fk_Angle^ argA)
	{
		if(!argA) return;
		pQuat->makeEuler(argA);
	}
	
	fk_Angle^ fk_Quaternion::Euler::get(void)
	{
		return gcnew fk_Angle(pQuat->getEuler());
	}

	double fk_Quaternion::Norm::get(void)
	{
		return pQuat->norm();
	}
	
	double fk_Quaternion::Abs::get(void)
	{
		return pQuat->abs();
	}

	fk_Matrix^ fk_Quaternion::Matrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = pQuat->conv();
		return M;
	}

	fk_Quaternion^ fk_Quaternion::operator-(fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = -(*argQ->pQuat);
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator~(fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ~(*argQ->pQuat);
		return Q;
	}

	//////////////////// 二項演算子
	fk_Quaternion^ fk_Quaternion::operator*(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = (*argQ1->pQuat) * (*argQ2->pQuat);
		return Q;
	}
		
	fk_Quaternion^ fk_Quaternion::operator+(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ1->pQuat + *argQ2->pQuat;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator-(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ1->pQuat - *argQ2->pQuat;
		return Q;
	}
			
	fk_Quaternion^ fk_Quaternion::operator*(fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat * argD;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator*(double argD, fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat * argD;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator/(fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat / argD;
		return Q;
	}

	fk_Vector^ fk_Quaternion::operator*(fk_Quaternion^ argQ, fk_Vector^ argV)
	{
		if(!argQ || !argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector((*argQ->pQuat) * argV);
		return V;
	}
		
	double fk_Quaternion::operator^(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return 0.0;
		return (*argQ1->pQuat ^ *argQ2->pQuat);
	}

	//////////////////// 代入演算子
	void fk_Quaternion::operator *= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat *= *argQ2->pQuat;
	}


	void fk_Quaternion::operator *= (fk_Quaternion^ argQ1, double argD)
	{
		if(!argQ1) return;
		*argQ1->pQuat *= argD;
	}

	void fk_Quaternion::operator /= (fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return;
		*argQ->pQuat /= argD;
	}


	void fk_Quaternion::operator += (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat += *argQ2->pQuat;
	}

	void fk_Quaternion::operator -= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat -= *argQ2->pQuat;
	}

	bool fk_Quaternion::Equals(fk_Quaternion^ argQ)
	{
		if(!argQ) false;
		return (*argQ->pQuat == *pQuat);
	}

	bool fk_Quaternion::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Quaternion^ V = static_cast<fk_Quaternion^>(argObj);
			return (*V->pQuat == *pQuat);
		}
		return false;
	}

	String^	fk_Quaternion::ToString()
	{
		string	tmpBuf;
		tmpBuf = "Q: " + to_string(pQuat->s) + ", ";
		tmpBuf += to_string(pQuat->v.x) + ", ";
		tmpBuf += to_string(pQuat->v.y) + ", ";
		tmpBuf += to_string(pQuat->v.z);
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Quaternion::Init(void)
	{
		pQuat->init();
	}
	
	void fk_Quaternion::Set(double argS, double argX, double argY, double argZ)
	{
		pQuat->set(argS, argX, argY, argZ);
	}
	
	void fk_Quaternion::Set(double argS, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->set(argS, argV);
	}
	
	void fk_Quaternion::SetRotate(double argT, double argX, double argY, double argZ)
	{
		pQuat->setRotate(argT, argX, argY, argZ);
	}
	
	void fk_Quaternion::SetRotate(double argT, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->setRotate(argT, argV);
	}

	bool fk_Quaternion::Normalize(void)
	{
		return pQuat->normalize();
	}
	
	void fk_Quaternion::Conj(void)
	{
		pQuat->conj();
	}
	
	bool fk_Quaternion::Inverse(void)
	{
		return pQuat->inverse();
	}
	
	fk_Quaternion^ fk_Quaternion::GetInverse(void)
	{
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *pQuat;
		Q->Inverse();
		return Q;
	}
}


