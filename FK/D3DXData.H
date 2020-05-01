#ifndef __FK_D3DX_DATA_HEADER__
#define __FK_D3DX_DATA_HEADER__

#include <FK/Matrix.h>
#include <FK/Quaternion.h>
#include <FK/Tree.h>

namespace FK {

	class fk_D3DXFrameAnimation {

	public:
		fk_D3DXFrameAnimation(void);
		virtual ~fk_D3DXFrameAnimation();

		void SetName(const std::string &);
		std::string GetName(void);

		void SetRotKeyNum(int);
		void SetScaleKeyNum(int);
		void SetTransKeyNum(int);
		int GetRotKeyNum(void);
		int GetScaleKeyNum(void);
		int GetTransKeyNum(void);

		void SetRotKey(int, double);
		void SetScaleKey(int, double);
		void SetTransKey(int, double);
		double GetRotKey(int);
		double GetScaleKey(int);
		double GetTransKey(int);

		void SetRotData(int, const fk_Quaternion &);
		void SetScaleData(int, const fk_Vector &);
		void SetTransData(int, const fk_Vector &);
		fk_Quaternion GetRotData(int);
		fk_Vector GetScaleData(int);
		fk_Vector GetTransData(int);

		void SetTime(double);
		double GetStartTime(void);
		fk_Matrix GetFrameMatrix(void);

	private:
		std::unique_ptr<std::string> name;

		std::vector<double> rotKey;
		std::vector<double> scaleKey;
		std::vector<double> transKey;

		std::vector<std::unique_ptr<fk_Quaternion>> rotData;
		std::vector<std::unique_ptr<fk_Vector>> scaleData;
		std::vector<std::unique_ptr<fk_Vector>> transData;

		std::unique_ptr<fk_Matrix> frameMatrix;

		void LinearDiv(double, std::vector<double> *, int *, double *);
	};

	class fk_D3DXSkinData {
	private:
		std::unique_ptr<std::string> name;
		int vNum;
		std::vector<int> vArray;
		std::vector<double> wArray;

		std::unique_ptr<fk_Matrix> offsetMatrix;

	public:
		fk_D3DXSkinData(void);
		virtual ~fk_D3DXSkinData();

		void SetName(const std::string &);
		void SetNum(int);
		void SetVID(int, int);
		void SetVWeight(int, double);
		void SetOffsetMatrixValue(int, int, double);

		std::string GetName(void);
		int GetNum(void);
		int GetVID(int);
		double GetWeight(int);
		fk_Matrix GetOffsetMatrix(void);
	};

	class fk_D3DXFrame {
	public:
		fk_D3DXFrame(void);
		virtual ~fk_D3DXFrame();

		void SetName(const std::string &);
		std::string GetName(void);
		void SetSkin(fk_D3DXSkinData *);
		fk_D3DXSkinData * GetSkin(void);
		void SetAnimation(fk_D3DXFrameAnimation *);
		fk_D3DXFrameAnimation *	GetAnimation(void);
		void SetParentFrame(fk_D3DXFrame *);
		void SetInitMatrix(const fk_Matrix *);
		void SetUpMatrix(void);
		void SetTime(double);
		fk_Matrix * GetTotalMatrix(void);

	private:
		std::unique_ptr<std::string> name;
		fk_D3DXSkinData *skin;
		fk_D3DXFrameAnimation *anim;

		// Frame の初期行列
		std::unique_ptr<fk_Matrix> initMatrix;

		// 各ボーン固有のオフセット行列
		std::unique_ptr<fk_Matrix> offsetMatrix;

		// 親からの継承を反映したボーン行列
		std::unique_ptr<fk_Matrix> curMatrix;

		// ボーン行列 * オフセット行列
		std::unique_ptr<fk_Matrix> totalMatrix;

		// 親ボーン行列
		fk_Matrix *parentMatrix;
	};

	class fk_D3DXPropertyList : public fk_TreeBaseObject {
	public:
		fk_D3DXPropertyList(void);
		virtual ~fk_D3DXPropertyList();

		void SetProperty(const std::string &);
		std::string GetProperty(void);
		void SetData(const std::string &);
		std::string GetData(void);
		void SetFrameMatrixValue(int, int, double);
		fk_Matrix * GetFrameMatrix(void);
		void SetFrame(fk_D3DXFrame *);
		fk_D3DXFrame * GetFrame(void);

	private:
		bool matrixFlg;
		std::unique_ptr<fk_Matrix> frameMatrix;
		std::string property;
		std::string data;
		fk_D3DXFrame *frame;
	};
}

#endif

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
