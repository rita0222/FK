#include <FK/Material.h>

#define FK_MATPALCODE

#include <FK/MatExample.h>

using namespace FK;

namespace FK {
	namespace Material {
		const fk_Color defAmb(0.3, 0.3, 0.3);
		const fk_Color defDif(0.0, 0.0, 0.0);
		const fk_Color defSpe(1.0, 1.0, 1.0);
		constexpr double defShi = 30.0;

		fk_Material LightCyan(fk_Color(0.1, 0.2, 0.2),
							  fk_Color(0.0, 0.5, 0.5),
							  fk_Color(0.2, 0.2, 0.2),
							  60.0);
	
		fk_Material AshGray(fk_Color(0.2, 0.2, 0.2),
							fk_Color(0.4, 0.4, 0.4),
							fk_Color(0.01, 0.01, 0.01),
							10.0);
		
		fk_Material BambooGreen(fk_Color(0.15, 0.28, 0.23),
								fk_Color(0.23, 0.47, 0.19),
								fk_Color(0.37, 0.68, 0.28),
								20.0);

		fk_Material Blue(defAmb,
						 fk_Color(0.0, 0.0, 0.7),
						 defSpe,
						 defShi);

		fk_Material Brown(fk_Color(0.2, 0.1, 0.0),
						  fk_Color(0.35, 0.15, 0.0),
						  defSpe,
						  defShi);

		fk_Material BurntTitan(fk_Color(0.1, 0.07, 0.07),
							   fk_Color(0.44, 0.17, 0.1),
							   fk_Color(0.6, 0.39, 0.1),
							   16.0);

		fk_Material Coral(fk_Color(0.5, 0.3, 0.4),
						  fk_Color(0.9, 0.5, 0.7),
						  defSpe,
						  defShi);

		fk_Material Cream(defAmb,
						  fk_Color(0.8, 0.7, 0.6),
						  defSpe,
						  defShi);

		fk_Material Cyan(defAmb,
						 fk_Color(0.0, 0.6, 0.6),
						 defSpe,
						 defShi);

		fk_Material DarkBlue(fk_Color(0.1, 0.1, 0.4),
							 fk_Color(0.0, 0.0, 0.25),
							 defSpe,
							 defShi);

		fk_Material DarkGreen(fk_Color(0.1, 0.4, 0.1),
							  fk_Color(0.0, 0.2, 0.0),
							  defSpe,
							  defShi);

		fk_Material DarkPurple(fk_Color(0.3, 0.1, 0.3),
							   fk_Color(0.3, 0.0, 0.3),
							   defSpe,
							   defShi);

		fk_Material DarkRed(fk_Color(0.2, 0.0, 0.0),
							fk_Color(0.4, 0.0, 0.0),
							defSpe,
							defShi);

		fk_Material DarkYellow(defAmb,
							   fk_Color(0.4, 0.3, 0.0),
							   defSpe,
							   defShi);

		fk_Material DimYellow(fk_Color(0.18, 0.14, 0.0),
							  fk_Color(0.84, 0.86, 0.07),
							  fk_Color(0.92, 0.82, 0.49),
							  defShi);

		fk_Material Flesh(defAmb,
						  fk_Color(0.8, 0.6, 0.4),
						  defSpe,
						  defShi);

		fk_Material GlossBlack(fk_Color(0.0, 0.0, 0.0),
							   fk_Color(0.04, 0.04, 0.04),
							   defSpe,
							   defShi);

		fk_Material GrassGreen(fk_Color(0.0, 0.1, 0.0),
							   fk_Color(0.0, 0.7, 0.0),
							   fk_Color(0.47, 0.98, 0.49),
							   defShi);

		fk_Material Gray1(defAmb,
						  fk_Color(0.6, 0.6, 0.6),
						  fk_Color(0.1, 0.1, 0.1),
						  defShi);

		fk_Material Gray2(defAmb,
						  fk_Color(0.2, 0.2, 0.2),
						  fk_Color(0.1, 0.1, 0.1),
						  defShi);

		fk_Material Green(defAmb,
						  fk_Color(0.0, 0.5, 0.0),
						  defSpe,
						  defShi);

		fk_Material HolidaySkyBlue(fk_Color(0.01, 0.22, 0.4),
								   fk_Color(0.2, 0.66, 0.92),
								   fk_Color(0.47, 0.74, 0.74),
								   defShi);

		fk_Material IridescentGreen(fk_Color(0.04, 0.11, 0.07),
									fk_Color(0.09, 0.39, 0.18),
									fk_Color(0.08, 0.67, 0.1),
									14.0);

		fk_Material Ivory(fk_Color(0.36, 0.28, 0.18),
						  fk_Color(0.56, 0.52, 0.29),
						  fk_Color(0.72, 0.45, 0.4),
						  33.0);

		fk_Material LavaRed(fk_Color(0.14, 0.0, 0.0),
							fk_Color(0.62, 0.0, 0.0),
							fk_Color(1.0, 0.46, 0.46),
							18.0);

		fk_Material LightBlue(defAmb,
							  fk_Color(0.4, 0.4, 0.9),
							  defSpe,
							  defShi);

		fk_Material LightGreen(defAmb,
							   fk_Color(0.5, 0.7, 0.3),
							   defSpe,
							   defShi);

		fk_Material LightViolet(defAmb,
								fk_Color(0.5, 0.4, 0.9),
								defSpe,
								defShi);

		fk_Material Lilac(fk_Color(0.21, 0.09, 0.23),
						  fk_Color(0.64, 0.54, 0.6),
						  fk_Color(0.4, 0.26, 0.37),
						  15.0);

		fk_Material MatBlack(fk_Color(0.0, 0.0, 0.0),
							 fk_Color(0.0, 0.0, 0.0),
							 fk_Color(0.0, 0.0, 0.0),
							 defShi);

		fk_Material Orange(defAmb,
						   fk_Color(0.8, 0.3, 0.0),
						   fk_Color(0.2, 0.2, 0.2),
						   defShi);

		fk_Material PaleBlue(defAmb,
							 fk_Color(0.5, 0.7, 0.7),
							 defSpe,
							 defShi);

		fk_Material PearWhite(fk_Color(0.32, 0.29, 0.18),
							  fk_Color(0.64, 0.61, 0.5),
							  fk_Color(0.4, 0.29, 0.17),
							  15.0);

		fk_Material Pink(fk_Color(0.6, 0.2, 0.3),
						 fk_Color(0.9, 0.55, 0.55),
						 defSpe,
						 defShi);

		fk_Material Purple(defAmb,
						   fk_Color(0.7, 0.0, 0.7),
						   defSpe,
						   defShi);

		fk_Material Raw(fk_Color(1.0, 1.0, 1.0),
						fk_Color(0.0, 0.0, 0.0),
						fk_Color(0.0, 0.0, 0.0),
						0.0);

		fk_Material Red(defAmb,
						fk_Color(0.7, 0.0, 0.0),
						defSpe,
						defShi);

		fk_Material TrueWhite(fk_Color(1.0, 1.0, 1.0),
							  fk_Color(1.0, 1.0, 1.0),
							  fk_Color(1.0, 1.0, 1.0),
							  0.0);

		fk_Material UltraMarine(fk_Color(0.01, 0.03, 0.21),
								fk_Color(0.07, 0.12, 0.49),
								fk_Color(0.53, 0.52, 0.91),
								11.0);

		fk_Material Violet(defAmb,
						   fk_Color(0.4, 0.0, 0.8),
						   defSpe,
						   defShi);

		fk_Material White(defAmb,
						  fk_Color(1.0, 1.0, 1.0),
						  fk_Color(0.1, 0.1, 0.1),
						  defShi);

		fk_Material WhiteLight(fk_Color(0.0, 0.0, 0.0),
							   fk_Color(1.0, 1.0, 1.0),
							   fk_Color(1.0, 1.0, 1.0),
							   defShi);

		fk_Material Yellow(defAmb,
						   fk_Color(0.8, 0.6, 0.0),
						   defSpe,
						   defShi);
	}

	void fk_InitMaterial(void)
	{
		using namespace FK::Material;

		LightCyan.init();
		LightCyan.setAmbient(0.1f, 0.2f, 0.2f);
		LightCyan.setDiffuse(0.0f, 0.5f, 0.5f);
		LightCyan.setSpecular(0.2f, 0.2f, 0.2f);
		LightCyan.setShininess(60.0f);

		AshGray.init();
		AshGray.setAmbient(0.2f, 0.2f, 0.2f);
		AshGray.setDiffuse(0.4f, 0.4f, 0.4f);
		AshGray.setSpecular(0.01f, 0.01f, 0.01f);
		AshGray.setShininess(10.0f);

		BambooGreen.init();
		BambooGreen.setAmbient(0.15f, 0.28f, 0.23f);
		BambooGreen.setDiffuse(0.23f, 0.47f, 0.19f);
		BambooGreen.setSpecular(0.37f, 0.68f, 0.28f);
		BambooGreen.setShininess(20.0f);

		Blue.init();
		Blue.setDiffuse(0.0f, 0.0f, 0.7f);

		Brown.init();
		Brown.setAmbient(0.2f, 0.1f, 0.0f);
		Brown.setDiffuse(0.35f, 0.15f, 0.0f);

		BurntTitan.init();
		BurntTitan.setAmbient(0.1f, 0.07f, 0.07f);
		BurntTitan.setDiffuse(0.44f, 0.17f, 0.1f);
		BurntTitan.setSpecular(0.6f, 0.39f, 0.1f);
		BurntTitan.setShininess(16.0f);

		Coral.init();
		Coral.setAmbient(0.5f, 0.3f, 0.4f);
		Coral.setDiffuse(0.9f, 0.5f, 0.7f);

		Cream.init();
		Cream.setDiffuse(0.8f, 0.7f, 0.6f);

		Cyan.init();
		Cyan.setDiffuse(0.0f, 0.6f, 0.6f);

		DarkBlue.init();
		DarkBlue.setAmbient(0.1f, 0.1f, 0.4f);
		DarkBlue.setDiffuse(0.0f, 0.0f, 0.25f);

		DarkGreen.init();
		DarkGreen.setAmbient(0.1f, 0.4f, 0.1f);
		DarkGreen.setDiffuse(0.0f, 0.2f, 0.0f);

		DarkPurple.init();
		DarkPurple.setAmbient(0.3f, 0.1f, 0.3f);
		DarkPurple.setDiffuse(0.3f, 0.0f, 0.3f);

		DarkRed.init();
		DarkRed.setAmbient(0.2f, 0.0f, 0.0f);
		DarkRed.setDiffuse(0.4f, 0.0f, 0.0f);

		DarkYellow.init();
		DarkYellow.setDiffuse(0.4f, 0.3f, 0.0f);

		DimYellow.init();
		DimYellow.setAmbient(0.18f, 0.14f, 0.0f);
		DimYellow.setDiffuse(0.84f, 0.86f, 0.07f);
		DimYellow.setSpecular(0.92f, 0.82f, 0.49f);

		Flesh.init();
		Flesh.setDiffuse(0.8f, 0.6f, 0.4f);

		GlossBlack.init();
		GlossBlack.setAmbient(0.0f, 0.0f, 0.0f);
		GlossBlack.setDiffuse(0.04f, 0.04f, 0.04f);

		GrassGreen.init();
		GrassGreen.setAmbient(0.0f, 0.1f, 0.0f);
		GrassGreen.setDiffuse(0.0f, 0.7f, 0.0f);
		GrassGreen.setSpecular(0.47f, 0.98f, 0.49f);

		Gray1.init();
		Gray1.setDiffuse(0.6f, 0.6f, 0.6f);
		Gray1.setSpecular(0.1f, 0.1f, 0.1f);

		Gray2.init();
		Gray2.setDiffuse(0.2f, 0.2f, 0.2f);
		Gray2.setSpecular(0.1f, 0.1f, 0.1f);

		Green.init();
		Green.setDiffuse(0.0f, 0.5f, 0.0f);

		HolidaySkyBlue.init();
		HolidaySkyBlue.setAmbient(0.01f, 0.22f, 0.4f);
		HolidaySkyBlue.setDiffuse(0.2f, 0.66f, 0.92f);
		HolidaySkyBlue.setSpecular(0.47f, 0.74f, 0.74f);

		IridescentGreen.init();
		IridescentGreen.setAmbient(0.04f, 0.11f, 0.07f);
		IridescentGreen.setDiffuse(0.09f, 0.39f, 0.18f);
		IridescentGreen.setSpecular(0.08f, 0.67f, 0.1f);
		IridescentGreen.setShininess(14.0f);

		Ivory.init();
		Ivory.setAmbient(0.36f, 0.28f, 0.18f);
		Ivory.setDiffuse(0.56f, 0.52f, 0.29f);
		Ivory.setSpecular(0.72f, 0.45f, 0.4f);
		Ivory.setShininess(33.0f);

		LavaRed.init();
		LavaRed.setAmbient(0.14f, 0.0f, 0.0f);
		LavaRed.setDiffuse(0.62f, 0.0f, 0.0f);
		LavaRed.setSpecular(1.0f, 0.46f, 0.46f);
		LavaRed.setShininess(18.0f);

		LightBlue.init();
		LightBlue.setDiffuse(0.4f, 0.4f, 0.9f);

		LightCyan.init();
		LightCyan.setAmbient(0.1f, 0.2f, 0.2f);
		LightCyan.setDiffuse(0.0f, 0.5f, 0.5f);
		LightCyan.setSpecular(0.2f, 0.2f, 0.2f);
		LightCyan.setShininess(60.0f);

		LightGreen.init();
		LightGreen.setDiffuse(0.5f, 0.7f, 0.3f);

		LightViolet.init();
		LightViolet.setDiffuse(0.5f, 0.4f, 0.9f);

		Lilac.init();
		Lilac.setAmbient(0.21f, 0.09f, 0.23f);
		Lilac.setDiffuse(0.64f, 0.54f, 0.6f);
		Lilac.setSpecular(0.4f, 0.26f, 0.37f);
		Lilac.setShininess(15.0f);

		MatBlack.init();
		MatBlack.setAmbient(0.0f, 0.0f, 0.0f);
		MatBlack.setDiffuse(0.0f, 0.0f, 0.0f);
		MatBlack.setSpecular(0.0f, 0.0f, 0.0f);

		Orange.init();
		Orange.setDiffuse(0.8f, 0.3f, 0.0f);
		Orange.setSpecular(0.2f, 0.2f, 0.2f);

		PaleBlue.init();
		PaleBlue.setDiffuse(0.5f, 0.7f, 0.7f);

		PearWhite.init();
		PearWhite.setAmbient(0.32f, 0.29f, 0.18f);
		PearWhite.setDiffuse(0.64f, 0.61f, 0.5f);
		PearWhite.setSpecular(0.4f, 0.29f, 0.17f);
		PearWhite.setShininess(15.0f);

		Pink.init();
		Pink.setAmbient(0.6f, 0.2f, 0.3f);
		Pink.setDiffuse(0.9f, 0.55f, 0.55f);

		Purple.init();
		Purple.setDiffuse(0.7f, 0.0f, 0.7f);

		Raw.init();
		Raw.setAmbDiff(1.0f, 1.0f, 1.0f);
		Raw.setSpecular(0.0f, 0.0f, 0.0f);
		Raw.setShininess(0.0f);

		Red.init();
		Red.setDiffuse(0.7f, 0.0f, 0.0f);

		TrueWhite.init();
		TrueWhite.setAmbDiff(1.0f, 1.0f, 1.0f);
		TrueWhite.setSpecular(1.0f, 1.0f, 1.0f);
		TrueWhite.setShininess(0.0f);

		UltraMarine.init();
		UltraMarine.setAmbient(0.01f, 0.03f, 0.21f);
		UltraMarine.setDiffuse(0.07f, 0.12f, 0.49f);
		UltraMarine.setSpecular(0.53f, 0.52f, 0.91f);
		UltraMarine.setShininess(11.0f);

		Violet.init();
		Violet.setDiffuse(0.4f, 0.0f, 0.8f);

		White.init();
		White.setDiffuse(1.0f, 1.0f, 1.0f);
		White.setSpecular(0.1f, 0.1f, 0.1f);

		WhiteLight.init();
		WhiteLight.setAmbient(0.0f, 0.0f, 0.0f);
		WhiteLight.setDiffuse(1.0f, 1.0f, 1.0f);
		WhiteLight.setSpecular(1.0f, 1.0f, 1.0f);

		Yellow.init();
		Yellow.setDiffuse(0.8f, 0.6f, 0.0f);

		return;
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
