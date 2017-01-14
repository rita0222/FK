/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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

#ifndef __FK_SHADER_PARAMETER_HEADER__
#define __FK_SHADER_PARAMETER_HEADER__

#include <FK/TextureSampler.h>
#include <string>
#include <map>

//! シェーダーパラメーター管理クラス
/*!
 *	このクラスは、シェーダープログラムに対してパラメーターを渡すための機能を提供します。
 *	本クラスの機能は、 fk_ShaderBinder クラスの
 *	fk_ShaderBinder::getParameter() によってインスタンスを得ることで利用します。
 *
 *	\sa fk_ShaderBinder, fk_ShaderParameter, fk_TextureSampler
 */

class fk_ShaderParameter
{
public:
	//! コンストラクタ
	fk_ShaderParameter();

	//! デストラクタ
	virtual ~fk_ShaderParameter();

	//! エラーメッセージプロパティ
	/*!
	 *	シェーダーに関するエラーが生じた場合に、
	 *	エラーメッセージの文字列をこのプロパティから取得できます。
	 */
	std::string getLastError(void);

	//! float 型 uniform 変数設定関数
	/*!
	 *	この関数は、バーテックスシェーダーやフラグメントシェーダーに対し、
	 *	float 型の uniform 変数を渡す設定を行います。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	value
	 *		uniform 変数に渡す値
	 */
	void setRegister(std::string name, float value);

	//! float 配列型 uniform 変数設定関数
	/*!
	 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
	 *	float 配列型の uniform 変数を渡す設定を行います。
	 *	配列のサイズは 1 から 4 までで、
	 *	GLSL 内での型は配列サイズが 1 から順に float, vec2, vec3, vec4 となります。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	value
	 *		uniform 変数に渡す配列
	 */
	void setRegister(std::string name, std::vector<float> *value);

	//! int 型 uniform 変数設定関数
	/*!
	 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
	 *	int 型の uniform 変数を渡す設定を行います。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	value
	 *		uniform 変数に渡す値
	 */
	void setRegister(std::string name, int value);

	//! int 配列型 uniform 変数設定関数
	/*!
	 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
	 *	int 配列型の uniform 変数を渡す設定を行います。
	 *	配列のサイズは 1 から 4 までで、
	 *	GLSL 内での型は配列サイズが 1 から順に int, ivec2, ivec3, ivec4 となります。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	value
	 *		uniform 変数に渡す配列
	 */
	void setRegister(std::string name, std::vector<int> *value);
	
	//! 行列型 uniform 変数設定関数
	/*!
	 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
	 *	行列型の uniform 変数を渡す設定を行います。
	 *	この関数の引数は fk_Matrix 型変数となり、
	 *	GLSL コード内での型は mat4 となります。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	value
	 *		uniform 変数に渡す行列
	 */
	void setRegister(std::string name, fk_Matrix *value);

	//! uniform 変数解除関数
	/*!
	 *	各種 setRegister() 関数で設定した uniform 変数を解除します。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\return
	 *		uniform 変数が存在していた場合は解除し true を返します。
	 *		変数が存在していなかった場合は false を返します。
	 */
	bool removeRegister(std::string name);

	//! float 配列型 attribute 変数設定関数
	/*!
	 *	この関数は、
	 *	バーテックスシェーダーに対し float 配列型の attribute 変数を渡す設定を行います。
	 *	1つの頂点に対して渡せる要素数は 1 から 4 までで、第2引数で指定します。
	 *	value に渡す配列のサイズは dim * 頂点数である必要があります。
	 *	GLSL 内での型は、要素数が 1 から順に float, vec2, vec3, vec4 となります。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	dim
	 *		attribute 変数の要素数
	 *
	 *	\param[in]	value
	 *		attribute 変数に渡す値の配列
	 */
	void addAttribute(std::string name, int dim, std::vector<float> *value);

	//! int 配列型 attribute 変数設定関数
	/*!
	 *	この関数は、
	 *	バーテックスシェーダーに対し int 配列型の attribute 変数を渡す設定を行います。
	 *	1つの頂点に対して渡せる要素数は 1 から 4 までで、第2引数で指定します。
	 *	value に渡す配列のサイズは dim * 頂点数である必要があります。
	 *	GLSL 内での型は、要素数が 1 から順に int, ivec2, ivec3, ivec4 となります。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\param[in]	dim
	 *		attribute 変数の要素数
	 *
	 *	\param[in]	value
	 *		attribute 変数に渡す値の配列
	 */
	void addAttribute(std::string name, int dim, std::vector<int> *value);

	//! attribute 変数解除関数
	/*!
	 *	各種 addAttribute() 関数で設定した attribute 変数を解除します。
	 *
	 *	\param[in]	name
	 *		GLSL コード内での変数名
	 *
	 *	\return
	 *		attribute 変数が存在していた場合は解除し true を返します。
	 *		変数が存在していなかった場合は false を返します。
	 */
	bool removeAttribute(std::string name);

	//! 参照テクスチャ設定関数
	/*!
	 *	GLSLコード内の参照テクスチャを設定します。
	 *	ここで設定したテクスチャは、
	 *	GLSL内では sampler2D 型 uniform 変数として扱われます。
	 *	複数のテクスチャを設定した場合、
	 *	GLSLコード内で変数を宣言した順番に割り振られます。
	 *
	 *	\param[in]	unit
	 *		シェーダー内でのテクスチャ ID を指定します。
	 *		0 から 31 までを指定することができます。
	 *		既に使用している ID を用いた場合、
	 *		前にその ID を用いていたテクスチャの設定は破棄されます。
	 *		GLSLコード内では、複数の sampler2D 変数に対し ID の若い順に割り振られます。
	 *
	 *	\param[in]	texture
	 *		テクスチャオブジェクト。詳細は fk_TextureSampler を参照して下さい。
	 *
	 *	\return
	 *		設定に成功すれば true を、失敗すれば false を返します。
	 */
	bool attachTexture(int unit, fk_TextureSampler *texture);

	//! 参照テクスチャ解除関数
	/*!
	 *	attachTexture() メソッドにて設定した参照テクスチャを解除します。
	 *
	 *	\param[in]	unit
	 *		テクスチャ ID
	 *
	 *	\return
	 *		解除に成功すれば true を、失敗すれば false を返します。
	 */
	bool detachTexture(int unit);


#ifndef FK_DOXYGEN_USER_PROCESS
	bool Apply(GLuint);
#endif
	
private:
	GLint GetLocation(GLuint, std::string);
	GLint GetAttributeLocation(GLuint, std::string);

	std::map<std::string, float> floatTable;
	std::map<std::string, std::vector<float> > floatArrayTable;
	std::map<std::string, int> intTable;
	std::map<std::string, std::vector<int> > intArrayTable;
	std::map<std::string, fk_Matrix> matrixTable;
	std::map<std::string, int> locationTable;

	std::map<std::string, std::tuple<int, std::vector<float> *> > floatAttributeTable;
	std::map<std::string, std::tuple<int, std::vector<int> *> > intAttributeTable;

	std::map<std::string, int> attributeLocationTable;
	std::map<int, fk_TextureSampler *> textureTable;

	std::string lastError;
	unsigned int lastAppliedId;
};

#endif
