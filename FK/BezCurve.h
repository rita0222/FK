/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_BEZCURVE_HEADER__
#define __FK_BEZCURVE_HEADER__

#include <FK/Curve.h>

//! Bezier曲線を生成、管理するクラス
/*!
 *	このクラスは、形状として Bezier 曲線を制御する機能を提供します。
 *	初期状態は 3 次式で、制御点が全て原点にある状態となります。
 *	現状では、2,3,4次式のいずれかのみしか生成できません。
 *	\remarks
 *	本クラスは現在ベータ機能としての位置づけであり、
 *	ユーザーズマニュアルには記載されていません。
 *	また、今後のバージョンアップにおいて仕様が変更される可能性があります。
 */

class fk_BezCurve : public fk_Curve {

	int						deg;
	std::vector<fk_Vector>	ctrlPos;

 public:

	//! コンストラクタ
	fk_BezCurve(void);

	//! デストラクタ
	virtual ~fk_BezCurve();

	//! 初期化用関数
	/*!
	 *	この関数は、曲線を初期状態(3次式、全ての制御点が原点にある状態)にします。
	 */
	void			init(void);

	//! 次数設定関数
	/*!
	 *	この関数は、曲線の次数を設定します。
	 *	現状では、2,3,4のいずれかのみ以外は設定できません。
	 *	次数が増加した場合は、これまで保持されていた制御点位置ベクトルは保持され、
	 *	新たな制御点は原点に配置されます。
	 *	次数が減少した場合は、末尾の制御点が消失しますが、
	 *	存続している制御点の位置ベクトルは保持されます。
	 *
	 *	\param[in]	deg	次数
	 *
	 *	\return	次数設定に成功した場合 true、失敗した場合 false を返します。
	 */
	bool			setDegree(int deg);

	//! 制御点設定関数
	/*!
	 *	曲線の制御点位置ベクトルを設定します。
	 *
	 *	\param[in]	ID	設定する制御点の ID。先頭は 0 になります。
	 *	\param[in]	pos	制御点位置ベクトル
	 *
	 *	\return	設定に成功した場合 true、失敗した場合 false を返します。
	 */
	bool			setCtrl(int ID, const fk_Vector &pos);

	//! 次数参照関数
	/*!
	 *	曲線の次数を参照します。
	 *
	 *	\return 次数
	 */
	int				getDegree(void);	

	//! 制御点参照関数
	/*!
	 *	曲線の制御点位置ベクトルを参照します。
	 *
	 *	\param[in]	ID	制御点 ID
	 *
	 *	\return	制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
	 */
	fk_Vector		getCtrl(int ID);

	//! 曲線算出関数
	/*!
	 *	パラメータに対応する曲線上の点の位置ベクトルを返します。
	 *	Bezier 曲線の幾何的定義ではパラメータの定義域は 0 から 1 までですが、
	 *	本関数はそれ以外の範囲であっても式の演算結果を返します。
	 *
	 *	\param[in]	t	曲線上のパラメータ
	 *
	 *	\return 曲線上の点の位置ベクトル
	 */
	fk_Vector		pos(double t);

	//! 曲線1階微分ベクトル算出関数
	/*!
	 *	パラメータに対応する曲線上の点の1階微分ベクトルを返します。
	 *	Bezier 曲線の幾何的定義ではパラメータの定義域は 0 から 1 までですが、
	 *	本関数はそれ以外の範囲であっても式の演算結果を返します。
	 *
	 *	\param[in]	t	曲線上のパラメータ
	 *
	 *	\return 曲線上の点の1階微分ベクトル
	 */
	fk_Vector		diff(double t);
};

#endif	// __FK_BEZCURVE_HEADER__
