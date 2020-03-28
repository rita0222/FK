#include "Shape_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	using namespace System::Collections::Generic;

	::FK::fk_Shape * fk_Shape::GetP(void)
	{
		return (::FK::fk_Shape *)(pBase);
	}

	fk_Shape::fk_Shape(bool argNewFlg) : fk_Attribute(false)
	{
		if (argNewFlg == true) pBase = new ::FK::fk_Shape();
	}

	fk_Shape::~fk_Shape()
	{
		this->!fk_Shape();
	}

	fk_Shape::!fk_Shape()
	{
		if (pBase == nullptr) return;
		if (dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_RealShapeType^ fk_Shape::RealShapeType::get(void)
	{
		fk_RealShapeType^ type = gcnew fk_RealShapeType();

		switch (GetP()->getRealShapeType()) {
		case ::FK::fk_RealShapeType::IFS:
			type = fk_RealShapeType::IFS;
			break;

		case ::FK::fk_RealShapeType::SOLID:
			type = fk_RealShapeType::SOLID;
			break;

		case ::FK::fk_RealShapeType::TEXTURE:
			type = fk_RealShapeType::TEXTURE;
			break;

		case ::FK::fk_RealShapeType::POINT:
			type = fk_RealShapeType::POINT;
			break;

		case ::FK::fk_RealShapeType::LIGHT:
			type = fk_RealShapeType::LIGHT;
			break;

		case ::FK::fk_RealShapeType::OTHER:
			type = fk_RealShapeType::OTHER;
			break;

		default:
			break;
		}
		return type;
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<int>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 1 || argDim > 4) return;
		vector<int> array;
		for each (int x in argArray) array.push_back(x);
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<float>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 1 || argDim > 4) return;
		vector<float> array;
		for each (float x in argArray) array.push_back(x);
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<double>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 1 || argDim > 4) return;
		vector<float> array;
		for each (double x in argArray) array.push_back(float(x));
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<fk_Vector^>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 1 || argDim > 4) return;
		vector<float> array;
		for each (fk_Vector^ v in argArray) {
			array.push_back(float(v->x));
			if (argDim == 1) continue;
			array.push_back(float(v->y));
			if (argDim == 2) continue;
			array.push_back(float(v->z));
			if (argDim == 4) array.push_back(0.0f);
		}
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<fk_TexCoord^>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 2 || argDim > 4) return;
		vector<float> array;
		for each (fk_TexCoord^ v in argArray) {
			array.push_back(float(v->x));
			if (argDim == 1) continue;
			array.push_back(float(v->y));
			if (argDim == 2) continue;
			array.push_back(0.0f);
			if (argDim == 4) array.push_back(0.0f);
		}
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
	}

	void fk_Shape::SetShaderAttribute(String^ argName, int argDim, IEnumerable<fk_HVector^>^ argArray)
	{
		if (argName == nullptr || argArray == nullptr || argDim < 2 || argDim > 4) return;
		vector<float> array;
		for each (fk_HVector^ v in argArray) {
			array.push_back(float(v->x));
			if (argDim == 1) continue;
			array.push_back(float(v->y));
			if (argDim == 2) continue;
			array.push_back(float(v->z));
			if (argDim == 4) array.push_back(float(v->w));
		}
		GetP()->setShaderAttribute(marshal_as<string>(argName), argDim, &array, true);
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
