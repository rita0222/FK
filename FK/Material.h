﻿#ifndef __FK_MATERIAL_HEADER__
#define __FK_MATERIAL_HEADER__

#include <FK/Color.h>

namespace FK {

	//! マテリアル(質感)を管理するクラス
	/*!
	 *	このクラスは、マテリアル(質感)を管理、制御する機能を提供します。
	 *	FKにおけるマテリアルは、以下の要素によって成り立っています。
	 *
	 *	- 環境反射係数 (Ambient)
	 *	- 拡散反射係数 (Diffuse)
	 *	- 鏡面反射係数 (Specular)
	 *	- 鏡面反射ハイライト (Shininess)
	 *	.
	 *	これらのうち、前者3つは fk_Color による RGBA 色表現であり、
	 *	後者1つは float 型によるスカラー値となっています。
	 *	各要素についての詳細はユーザーズマニュアルやCGの解説文献を参照して下さい。
	 *
	 *	マテリアルには、最初から定義されているグローバル変数があります。
	 *	これらのリストはユーザーズマニュアルの付録Aに記されています。
	 *	利用するには、 initDefault() 関数を呼ぶ必要があります。
	 *
	 *	インスタンス生成時の初期状態は以下のような値となります。
	 *
	 *	- 環境反射係数: (0.3, 0.3, 0.3, 1.0)
	 *	- 拡散反射係数: (0.0, 0.0, 0.0, 1.0)
	 *	- 鏡面反射係数: (1.0, 1.0, 1.0, 1.0)
	 *	- 鏡面反射ハイライト: 30.0
	 *	.
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::setBlendStatus() の説明を参照して下さい。
	 *
	 *	\sa fk_Color, fk_Palette, fk_Scene
	 */

	class fk_Material : public fk_BaseObject {

#ifndef FK_DOXYGEN_USER_PROCESS
		class Member {
		public:
			fk_Color diffuse, ambient, specular;
			float shininess;

			Member(void);
		};
#endif

	public:

		//! コンストラクタ
		fk_Material(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Material(const fk_Color &,
					const fk_Color &,
					const fk_Color &,
					float);
#endif
		

		//! デストラクタ
		virtual ~fk_Material();

		//! 比較等号演算子
		/*!
		 *	この等号演算子では、各色要素の差が
		 *	fk_Color::EPS (現バージョンでは 0.0001) 内の誤差内であれば
		 *	等しいと判断します。
		 */
		friend bool operator==(fk_Material left, fk_Material right);

		//! コピーコンストラクタ
		fk_Material(const fk_Material &arg);

		//! 代入演算子
		fk_Material & operator =(const fk_Material &arg);



		//! 初期化関数
		/*!
		 *	変数を初期状態に戻します。
		 */
		void init(void);

		//! \name 設定用関数
		///@{

		//! 環境反射係数設定関数1
		/*!
		 *	環境反射係数を設定します。引数は fk_Color 型です。
		 *
		 *	\param[in] c 色
		 */
		void setAmbient(fk_Color c);

		//! 環境反射係数設定関数2
		/*!
		 *	環境反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す float 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setAmbient(float r, float g, float b, float a = 1.0f);

		//! 環境反射係数設定関数3
		/*!
		 *	環境反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す double 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setAmbient(double r, double g, double b, double a = 1.0);

		//! 拡散反射係数設定関数1
		/*!
		 *	拡散反射係数を設定します。引数は fk_Color 型です。
		 *
		 *	\param[in] c 色
		 */
		void setDiffuse(fk_Color c);

		//! 拡散反射係数設定関数2
		/*!
		 *	拡散反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す float 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setDiffuse(float r, float g, float b, float a = 1.0f);

		//! 拡散反射係数設定関数3
		/*!
		 *	拡散反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す double 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setDiffuse(double r, double g, double b, double a = 1.0);

		//! 鏡面反射設定関数1
		/*!
		 *	鏡面反射係数を設定します。引数は fk_Color 型です。
		 *
		 *	\param[in] c 色
		 */
		void setSpecular(fk_Color c);

		//! 鏡面反射係数設定関数2
		/*!
		 *	鏡面反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す float 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setSpecular(float r, float g, float b, float a = 1.0f);

		//! 鏡面反射係数設定関数3
		/*!
		 *	鏡面反射係数を設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す double 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setSpecular(double r, double g, double b, double a = 1.0);

		//! 鏡面反射ハイライト設定関数1
		/*!
		 *	鏡面反射ハイライトを設定します。引数は float 型です。
		 *
		 *	\param[in] s 鏡面反射ハイライト
		 */
		void setShininess(float s);

		//! 鏡面反射ハイライト設定関数2
		/*!
		 *	鏡面反射ハイライトを設定します。引数は double 型です。
		 *
		 *	\param[in] s 鏡面反射ハイライト
		 */
		void setShininess(double s);

		//! 環境反射・拡散反射同時設定関数1
		/*!
		 *	環境反射係数と拡散反射係数を同一の値で設定します。引数は fk_Color 型です。
		 *
		 *	\param[in] c 色
		 */
		void setAmbDiff(fk_Color c);

		//! 環境反射・拡散反射同時設定関数2
		/*!
		 *	環境反射係数と拡散反射係数を同一の値で設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す float 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setAmbDiff(float r, float g, float b, float a = 1.0f);

		//! 環境反射・拡散反射同時設定関数3
		/*!
		 *	環境反射係数と拡散反射係数を同一の値で設定します。
		 *	引数は R, G, B の各色要素および透過要素 A を表す double 型の数値です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A(透過)要素
		 */
		void setAmbDiff(double r, double g, double b, double a = 1.0);
		///@}

		//! \name 参照用関数
		///@{

		//! 環境反射係数参照関数
		/*!
		 *	返り値の型はポインタであることに注意して下さい。
		 *	ここで得られるアドレスは参照元マテリアルの実体であり、
		 *	実体の値を修正すると元マテリアルの色要素を修正することになります。
		 *
		 *	\return 環境反射係数へのポインタ
		 *
		 *	\sa setAmbient(), setAmbDiff()
		 */
		fk_Color * getAmbient(void);

		//! 拡散反射係数参照関数
		/*!
		 *	返り値の型はポインタであることに注意して下さい。
		 *	ここで得られるアドレスは参照元マテリアルの実体であり、
		 *	実体の値を修正すると元マテリアルの色要素を修正することになります。
		 *
		 *	\return 拡散反射係数へのポインタ
		 *
		 *	\sa setDiffuse(), setAmbDiff()
		 */
		fk_Color * getDiffuse(void);

		//! 鏡面反射係数参照関数
		/*!
		 *	返り値の型はポインタであることに注意して下さい。
		 *	ここで得られるアドレスは参照元マテリアルの実体であり、
		 *	実体の値を修正すると元マテリアルの色要素を修正することになります。
		 *
		 *	\return 鏡面反射係数へのポインタ
		 *
		 *	\sa setSpecular()
		 */
		fk_Color * getSpecular(void);


		//! 鏡面反射ハイライト参照関数
		/*!
		 *	\return 鏡面反射ハイライト
		 *
		 *	\sa setShininess()
		 */
		float getShininess(void);

		//! 透明度設定関数1
		/*!
		 *	環境反射係数、拡散反射係数、鏡面反射係数の透明度を一括して設定します。
		 *  引数は float 型です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\note
		 *	透過色を設定した場合でも、
		 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
		 *	詳細は fk_Scene::setBlendStatus() の説明を参照して下さい。
		 *
		 *	\param[in] a 透明度
		 *
		 *	\sa fk_Scene::setBlendStatus()
		 */
		void setAlpha(float a);

		//! 透明度設定関数2
		/*!
		 *	環境反射係数、拡散反射係数、鏡面反射係数の透明度を一括して設定します。
		 *  引数は double 型です。
		 *	設定できる値は 0 から 1 までで、
		 *	範囲外の数値については上下限に丸められます。
		 *
		 *	\note
		 *	透過色を設定した場合でも、
		 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
		 *	詳細は fk_Scene::setBlendStatus() の説明を参照して下さい。
		 *
		 *	\param[in] a 透明度
		 *
		 *	\sa fk_Scene::setBlendStatus()
		 */
		void setAlpha(double a);
		///@}

		//! デフォルトマテリアル初期化関数
		/*!
		 *	この関数を呼ぶと、
		 *	ユーザーズマニュアルに掲載しているマテリアル変数の値を、
		 *	マニュアルに記載してある値に初期化します。
		 *	この関数を呼んだ後、該当マテリアル変数を
		 *	別のマテリアル値に設定することが可能です。
		 *
		 *	この関数は static 宣言されているため、
		 *	クラスのインスタンスを生成しなくても呼ぶことができます。
		 */
		static void	initDefault(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		void setEmission(fk_Color c);
		void setEmission(float r, float g, float b);
		void setEmission(double r, double g, double b);
		fk_Color * getEmission(void);
		float getAlpha(void);

		void Print(int, std::string = "");
#endif

	private:
		std::unique_ptr<Member> _m;
	};
}
#endif // __FK_MATERIAL_HEADER__

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
