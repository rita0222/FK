#include <FK/FK.h>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>

using namespace std;
using namespace FK;

class GUISet {
private:

	Fl_Value_Slider	*headSlider;				// ヘディング角用スライダー
	Fl_Value_Slider	*pitchSlider;				// ピッチ各用スライダー
	Fl_Roller		*scaleRoller;				// スケーリング用ローラー

	Fl_Group		*materialGroup;				// ラジオボタンのグループ
	Fl_Check_Button	*ambientButton;				// Ambient 用ボタン
	Fl_Check_Button	*diffuseButton;				// Diffuse 用ボタン
	Fl_Check_Button	*specularButton;			// Specular 用ボタン
	Fl_Check_Button	*emissionButton;			// Emission 用ボタン
	Fl_Button		*colorChooser;				// カラー設定呼び出しボタン

	Fl_Button		*fileOpenButton;			// ファイル選択呼び出しボタン
	Fl_Button		*exitButton;				// 終了ボタン

public:
	GUISet(void);								// コンストラクタ
	~GUISet();									// デストラクタ

	string			getFileName(void);			// ファイル名取得
	double			getHead(void);				// ヘディング角取得
	double			getPitch(void);				// ピッチ角取得
	double			getScale(void);				// スケール取得
	int				materialSelect(void);		// マテリアル種類取得
	bool			toggleColorChooser(void);	// カラー設定呼出判定
	bool			toggleFileOpen(void);		// ファイル取得呼出判定
	bool			toggleExit(void);			// 終了判定
};

GUISet::GUISet(void)
{
	// ヘディング角用スライダー各種設定
	headSlider = new Fl_Value_Slider(130, 330, 180, 20, "Head Angle");
	headSlider->type(FL_HOR_NICE_SLIDER);	// ナイスなスライダー
	headSlider->minimum(-fk_Math::PI);			// 最小値は -3.14
	headSlider->maximum(fk_Math::PI);				// 最高値は 3.14
	headSlider->value(0.0);					// 初期値は 0
	headSlider->labelsize(12);				// ラベル文字のサイズを 12pt に
	headSlider->textsize(12);				// カウンタのサイズも 12 に

	// ピッチ角用スライダー各種設定
	pitchSlider = new Fl_Value_Slider(130, 370, 180, 20, "Pitch Angle");
	pitchSlider->type(FL_HOR_NICE_SLIDER);
	pitchSlider->minimum(-fk_Math::PI);
	pitchSlider->maximum(fk_Math::PI);
	pitchSlider->value(0.0);
	pitchSlider->labelsize(12);
	pitchSlider->textsize(12);

	// スケーリング用ローラー各種設定
	scaleRoller = new Fl_Roller(160, 410, 120, 20, "Scale");
	scaleRoller->type(FL_HORIZONTAL);		// ローラーは横向き
	scaleRoller->minimum(-100.0);
	scaleRoller->maximum(100.0);
	scaleRoller->value(0.0);
	scaleRoller->labelsize(12);

	// 左側のマテリアル関係のボタンをグループ化しておく。
	materialGroup = new Fl_Group(10, 320, 100, 170);
	materialGroup->box(FL_THIN_UP_FRAME);	// ちょっと盛り上げる

	// Ambient 用ラジオボタン
	ambientButton = new Fl_Check_Button(10, 320, 100, 30, "Ambient");
	ambientButton->type(FL_RADIO_BUTTON);
	ambientButton->down_box(FL_DIAMOND_DOWN_BOX);

	// Diffuse 用ラジオボタン
	diffuseButton = new Fl_Check_Button(10, 350, 100, 30, "Diffuse");
	diffuseButton->type(FL_RADIO_BUTTON);
	diffuseButton->down_box(FL_DIAMOND_DOWN_BOX);

	// Specular 用ラジオボタン
	specularButton = new Fl_Check_Button(10, 380, 100, 30, "Specular");
	specularButton->type(FL_RADIO_BUTTON);
	specularButton->down_box(FL_DIAMOND_DOWN_BOX);

	// Emission 用ラジオボタン
	emissionButton = new Fl_Check_Button(10, 410, 100, 30, "Emission");
	emissionButton->type(FL_RADIO_BUTTON);
	emissionButton->down_box(FL_DIAMOND_DOWN_BOX);

	// カラー設定呼出ボタン
	colorChooser = new Fl_Button(20, 450, 80, 30, "ColorChange");
	colorChooser->type(0);		// 普通のボタンとして扱う
	colorChooser->labelsize(12);

	// MaterialGroup のグループの終了
	materialGroup->end();

	// とりあえず Ambient にチェックを入れる。
	ambientButton->value(1);

	// ファイル取得呼出ボタン
	fileOpenButton = new Fl_Button(120, 460, 90, 30, "File Open");
	fileOpenButton->type(0);
	fileOpenButton->labelsize(12);

	// 終了ボタン
	exitButton = new Fl_Button(220, 460, 90, 30, "Exit");
	exitButton->type(0);
	exitButton->labelsize(12);

	return;
}

GUISet::~GUISet()
{
	return;
}

string GUISet::getFileName(void)
{
	Fl_Native_File_Chooser	*fc;
	string					fileName;
	string					cwd;

	fc = new Fl_Native_File_Chooser();
	fc->title("VRML File Select");
	fc->filter("*.wrl");
	cwd = fk_System::get_cwd();
	if(cwd.empty() == false) fc->directory(cwd.c_str());
	fc->type(Fl_Native_File_Chooser::BROWSE_FILE);

	switch(fc->show()) {
	  case -1:
		fl_alert("%s", fc->errmsg());
		delete fc;
		return fileName;

	  case 1:
		delete fc;
		return fileName;

	  default:
		break;
	}

	fileName = fc->filename();
	delete fc;
	return fileName;
}


double GUISet::getHead(void)
{
	return headSlider->value();
}

double GUISet::getPitch(void)
{
	return pitchSlider->value();
}

double GUISet::getScale(void)
{
	// 10 の (scaleRoller->value()) 乗 を返す。

	return pow(10.0, scaleRoller->value());
}

int GUISet::materialSelect(void)
{
	// どのラジオボタンが選択されているかを取得

	if(ambientButton->value() == 1) return 1;
	if(diffuseButton->value() == 1) return 2;
	if(specularButton->value() == 1) return 3;
	if(emissionButton->value() == 1) return 4;

	return -1;
}

bool GUISet::toggleColorChooser(void)
{
	if(colorChooser->value() == 1) return true;
	return false;
}

bool GUISet::toggleFileOpen(void)
{
	if(fileOpenButton->value() == 1) {
		fileOpenButton->value(0);
		return true;
	}
	return false;
}

bool GUISet::toggleExit(void)
{
	if(exitButton->value() == 1) return true;
	return false;
}

void getMaterial(int index, fk_Material *mat, double *r, double *g, double *b)
{
	// Index によってマテリアルの各種属性を (R, G, B) に代入

	switch(index) {
	  case 1:
		*r = mat->getAmbient()->getR();
		*g = mat->getAmbient()->getG();
		*b = mat->getAmbient()->getB();
		break;
	  case 2:
		*r = mat->getDiffuse()->getR();
		*g = mat->getDiffuse()->getG();
		*b = mat->getDiffuse()->getB();
		break;
	  case 3:
		*r = mat->getSpecular()->getR();
		*g = mat->getSpecular()->getG();
		*b = mat->getSpecular()->getB();
		break;
	  case 4:
		*r = mat->getEmission()->getR();
		*g = mat->getEmission()->getG();
		*b = mat->getEmission()->getB();
		break;
	  default:
		break;
	}
	return;
}

void setMaterial(int index, fk_Material *mat, double r, double g, double b)
{
	// Index によって (R, G, B) を各種マテリアルに設定

	switch(index) {
	  case 1:
		mat->setAmbient(r, g, b);
		break;
	  case 2:
		mat->setDiffuse(r, g, b);
		break;
	  case 3:
		mat->setSpecular(r, g, b);
		break;
	  case 4:
		mat->setEmission(r, g, b);
		break;
	  default:
		break;
	}

	return;
}

int main(int, char *[])
{
	double			colorR, colorG, colorB;
	fk_Material		material;
	fk_IndexFaceSet	shape;
	fk_Light		light;
	fk_Model		shapeModel, lightModel[2], camera;
	fk_Scene		scene;
	string			fileName;

	Fl_Window		mainWindow(320, 500, "VRML Viewer");
	fk_Window		viewWin(10, 10, 300, 300);
	GUISet			gui;

	mainWindow.end();

	fk_System::setcwd();
	fk_Material::initDefault();

	// 光源の設定。今回は二つの平行光源
	lightModel[0].setShape(&light);
	lightModel[1].setShape(&light);
	lightModel[0].setMaterial(Material::White);
	lightModel[1].setMaterial(Material::White);
	lightModel[0].glFocus(-1.0, -1.0, 0.0);
	lightModel[1].glFocus(1.0, -1.0, 0.0);

	// ソリッドモデルの初期マテリアルに Yellow を用いる。
	material = Material::Yellow;
	shapeModel.setShape(&shape);
	shapeModel.setMaterial(material);

	// 視点の設定
	camera.glTranslate(0.0, 100.0, 1000.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	// ディスプレイリストへソリッド、光源、視点を登録
	scene.entryModel(&shapeModel);
	scene.entryModel(&lightModel[0]);
	scene.entryModel(&lightModel[1]);
	scene.entryCamera(&camera);

	// ViewWin にディスプレイリストを登録
	viewWin.setScene(&scene);

	mainWindow.show();
	viewWin.show();

	while(true) {

		if(mainWindow.visible() == 0) {
			if(Fl::wait() == 0) {
				break;
			} else {
				continue;
			}
		}
		if(viewWin.drawWindow() == 0) break;
		if(Fl::check() == 0) break;
		if(viewWin.winOpenStatus() == false) continue;

		// ライトを Y 軸中心に回転
		lightModel[0].glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, fk_Math::PI/100.0);
		lightModel[1].glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, fk_Math::PI/100.0);

		// スライダーやローラーに従ってソリッドモデルの姿勢と大きさを決定
		shapeModel.glAngle(gui.getHead(), gui.getPitch(), 0.0);
		shapeModel.setScale(gui.getScale());

		if(gui.toggleColorChooser() == true) {
			// カラー設定モード
			getMaterial(gui.materialSelect(), &material,
						&colorR, &colorG, &colorB);
			fl_color_chooser("COLOR SET", colorR, colorG, colorB);
			setMaterial(gui.materialSelect(), &material,
						colorR, colorG, colorB);
			shapeModel.setMaterial(material);
		}

		if(gui.toggleFileOpen() == true) {
			// ファイル取得モード
			fileName = gui.getFileName();
			if(fileName != "") {
				// キャンセルを押されたのでないなら
				if(shape.readVRMLFile(fileName, true, false) == false) {
					// VRML ファイルではなかったら
					fl_alert("%s is not VRML2.0 file.", fileName.c_str());
				} else {
					shapeModel.setMaterialMode(fk_MaterialMode::PARENT);
				}
			}
		}

		if(gui.toggleExit() == true) {
			// 終了ボタンが押されたら while ループを抜ける。
			break;
		}
	}

	return 0;
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
