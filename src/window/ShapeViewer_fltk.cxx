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

#define FK_DEF_SIZETYPE


#include <FK/ShapeViewer.h>
#include <FK/Vertex.h>
#include <FK/Error.H>
#include <FK/System.h>

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <sstream>

using namespace std;
using namespace FK;

static fk_ShapeGUIMenuItem	globalMenuStatus = FK_SV_GUI_NONE;
static bool					globalMenuValue = true;

namespace FK {
	class fk_GUI_ {
	public:

		Fl_Menu_Bar			*menuBar;
		Fl_Group			*ortGroup;
		Fl_Value_Slider		*headSlider;
		Fl_Value_Slider		*pitchSlider;
		Fl_Value_Slider		*bankSlider;
		Fl_Roller			*scaleRoller;
		Fl_Roller			*axisRoller;
	};
}

Fl_Menu_Item menuTable[] = {
	{"&File",		FL_ALT + 'f',	0, 0, FL_SUBMENU, 0, 0, 0, 0},
	{"&WRLOpen",	FL_ALT + 'w',	0, 0, 0, 0, 0, 0, 0},
	{"S&TLOpen",	FL_ALT + 't',	0, 0, 0, 0, 0, 0, 0},
	{"D&XFOpen",	FL_ALT + 'x',	0, 0, 0, 0, 0, 0, 0},
	{"WRL&Save",	FL_ALT + 'w',	0, 0, 0, 0, 0, 0, 0},
	{"&ImageSnap",	FL_ALT + 'i',	0, 0, 0, 0, 0, 0, 0},
	{"&Quit",		FL_ALT + 'q',	0, 0, 0, 0, 0, 0, 0},
	{0,				0,				0, 0, 0, 0, 0, 0, 0},
	{"&DrawStatus",	FL_ALT + 'd',	0, 0, FL_SUBMENU, 0, 0, 0, 0},
	{"&PolyDraw",	FL_ALT + 'p',	0, 0, FL_MENU_TOGGLE | FL_MENU_VALUE,
	 0, 0, 0, 0},
	{"&EdgeDraw",	FL_ALT + 'e',	0, 0, FL_MENU_TOGGLE | FL_MENU_VALUE,
	 0, 0, 0, 0},
	{"&VertexDraw",	FL_ALT + 'v',	0, 0, FL_MENU_TOGGLE, 0, 0, 0, 0},
	{"&AxisDraw",	FL_ALT + 'a',	0, 0, FL_MENU_TOGGLE | FL_MENU_VALUE,
	 0, 0, 0, 0},
	{"LightRotate",	0,				0, 0, FL_MENU_TOGGLE, 0, 0, 0, 0},
	{0,				0,				0, 0, 0, 0, 0, 0, 0},
	{"Material",	0,				0, 0, FL_SUBMENU, 0, 0, 0, 0},
	{"Ambient",		0,				0, 0, 0, 0, 0, 0, 0},
	{"Diffuse",		0,				0, 0, 0, 0, 0, 0, 0},
	{"Specular",	0,				0, 0, 0, 0, 0, 0, 0},
	{"Emission",	0,				0, 0, 0, 0, 0, 0, 0},
	{"Shininess",	0,				0, 0, 0, 0, 0, 0, 0},
	{"VertexColor",	0,				0, 0, 0, 0, 0, 0, 0},
	{"EdgeColor",	0,				0, 0, 0, 0, 0, 0, 0},
	{0,				0,				0, 0, 0, 0, 0, 0, 0},
	{0,				0,				0, 0, 0, 0, 0, 0, 0}
};

static void LocalMenuToggle(Fl_Widget *argW, void *)
{
	Fl_Menu_			*mw = static_cast<Fl_Menu_ *>(argW);
	const Fl_Menu_Item	*mItem = mw->mvalue();
	string				labelString;

	if(mItem == NULL) return;
	labelString = mItem->label();
	if(labelString == "&WRLOpen") {
		globalMenuStatus = FK_SV_GUI_WRLOPEN;
	} else if(labelString == "S&TLOpen") {
		globalMenuStatus = FK_SV_GUI_STLOPEN;
	} else if(labelString == "D&XFOpen") {
		globalMenuStatus = FK_SV_GUI_DXFOPEN;
	} else if(labelString == "WRL&Save") {
		globalMenuStatus = FK_SV_GUI_WRLSAVE;
	} else if(labelString == "STLSave") {
		globalMenuStatus = FK_SV_GUI_STLSAVE;
	} else if(labelString == "&ImageSnap") {
		globalMenuStatus = FK_SV_GUI_IMAGESNAP;
	} else if(labelString == "&Quit") {
		globalMenuStatus = FK_SV_GUI_QUIT;
	} else if(labelString == "&PolyDraw") {
		globalMenuStatus = FK_SV_GUI_POLYDRAW;
	} else if(labelString == "&EdgeDraw") {
		globalMenuStatus = FK_SV_GUI_EDGEDRAW;
	} else if(labelString == "&VertexDraw") {
		globalMenuStatus = FK_SV_GUI_VERTEXDRAW;
	} else if(labelString == "&AxisDraw") {
		globalMenuStatus = FK_SV_GUI_AXISDRAW;
	} else if(labelString == "LightRotate") {
		globalMenuStatus = FK_SV_GUI_LIGHTROTATE;
	} else if(labelString == "Ambient") {
		globalMenuStatus = FK_SV_GUI_AMBIENT;
	} else if(labelString == "Diffuse") {
		globalMenuStatus = FK_SV_GUI_DIFFUSE;
	} else if(labelString == "Specular") {
		globalMenuStatus = FK_SV_GUI_SPECULAR;
	} else if(labelString == "Emission") {
		globalMenuStatus = FK_SV_GUI_EMISSION;
	} else if(labelString == "Shininess") {
		globalMenuStatus = FK_SV_GUI_SHININESS;
	} else if(labelString == "VertexColor") {
		globalMenuStatus = FK_SV_GUI_VERTEXCOLOR;
	} else if(labelString == "EdgeColor") {
		globalMenuStatus = FK_SV_GUI_EDGECOLOR;
	}

 	globalMenuValue = (mItem->value() != 0) ? true : false;

	return;
}

void fk_ShapeViewer::GetMaterial(int argID, fk_ShapeGUIMenuItem index,
								 double *r, double *g, double *b)
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= polyMaterial.size()) return;

	// Index によってマテリアルの各種属性を (R, G, B) に代入

	switch(index) {
	  case FK_SV_GUI_AMBIENT:
		*r = polyMaterial[id]->getAmbient()->getR();
		*g = polyMaterial[id]->getAmbient()->getG();
		*b = polyMaterial[id]->getAmbient()->getB();
		break;
	  case FK_SV_GUI_DIFFUSE:
		*r = polyMaterial[id]->getDiffuse()->getR();
		*g = polyMaterial[id]->getDiffuse()->getG();
		*b = polyMaterial[id]->getDiffuse()->getB();
		break;
	  case FK_SV_GUI_SPECULAR:
		*r = polyMaterial[id]->getSpecular()->getR();
		*g = polyMaterial[id]->getSpecular()->getG();
		*b = polyMaterial[id]->getSpecular()->getB();
		break;
	  case FK_SV_GUI_EMISSION:
		*r = polyMaterial[id]->getEmission()->getR();
		*g = polyMaterial[id]->getEmission()->getG();
		*b = polyMaterial[id]->getEmission()->getB();
		break;
	  case FK_SV_GUI_EDGECOLOR:
		*r = edgeColor[id]->getR();
		*g = edgeColor[id]->getG();
		*b = edgeColor[id]->getB();
		break;
	  case FK_SV_GUI_VERTEXCOLOR:
		*r = vertexColor[id]->getR();
		*g = vertexColor[id]->getG();
		*b = vertexColor[id]->getB();
		break;
	  default:
		break;
	}
	return;
}

void fk_ShapeViewer::SetMaterial(int argID, fk_ShapeGUIMenuItem index,
								 double r, double g, double b)
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= polyMaterial.size()) return;

	// Index によって (R, G, B) を各種マテリアルに設定 

	switch(index) {
	  case FK_SV_GUI_AMBIENT:
		polyMaterial[id]->setAmbient(r, g, b);
		break;
	  case FK_SV_GUI_DIFFUSE:
		polyMaterial[id]->setDiffuse(r, g, b);
		break;
	  case FK_SV_GUI_SPECULAR:
		polyMaterial[id]->setSpecular(r, g, b);
		break;
	  case FK_SV_GUI_EMISSION:
		polyMaterial[id]->setEmission(r, g, b);
		break;
	  case FK_SV_GUI_EDGECOLOR:
		edgeColor[id]->set(r, g, b);
		break;
	  case FK_SV_GUI_VERTEXCOLOR:
		vertexColor[id]->set(r, g, b);
		break;
	  default:
		break;
	}

	return;
}

fk_ShapeViewer::fk_ShapeViewer(int argW, int argH)
	: fk_BaseObject(FK_SHAPEVIEWER)
{
	fk_Material::initDefault();

	gui = new fk_GUI_();
	InitValue();
	LightInit();
	AxisInit();
	ViewInit();
	clearModel();

	setWindowSize(argW, argH);
	ModelInit(0, &localSolid);

	return;
}

fk_ShapeViewer::~fk_ShapeViewer()
{
	delete mainWindow;
	delete gui;
	clearModel();

	return;
}

void fk_ShapeViewer::InitValue(void)
{
	mainWindow = NULL;
	viewWin = NULL;

	mouseX = mouseY = -1;

	InitFlag();
	return;
}

void fk_ShapeViewer::InitWindow(void)
{
	double	head, pitch, bank, scale, axisScale;
	bool	initFlg = true;

	head = pitch = bank = scale = axisScale = 0.0;

	if(mainWindow != NULL) {
		head = getHead();
		pitch = getPitch();
		bank = getBank();
		scale = getScale();
		axisScale = getAxisScale();
		initFlg = true;
	} else {
		initFlg = false;
	}

	delete mainWindow;

	mainWindow = new Fl_Window(allWinSize.w, allWinSize.h, "FK Shape Viewer");
	viewWin = new fk_Window(10, 40, fkWinSize.w, fkWinSize.h);
	InitGUI();
	mainWindow->end();

	if(initFlg == true) {
		setHead(head);
		setPitch(pitch);
		setBank(bank);
		setScale(scale);
		setAxisScale(axisScale);
	}

	viewWin->setScene(&scene);
	mainWindow->show();
	viewWin->show();

	return;
}

void fk_ShapeViewer::InitGUI(void)
{
	gui->menuBar = new Fl_Menu_Bar(0, 0, allWinSize.w, 30);
	gui->menuBar->menu(menuTable);
	gui->menuBar->callback(LocalMenuToggle);
	globalMenuStatus = FK_SV_GUI_NONE;

	gui->ortGroup = new Fl_Group(groupPos.w, groupPos.h, 215, 240); {

		gui->ortGroup->box(FL_THIN_UP_FRAME);

		// ヘディング角用スライダー各種設定 
		gui->headSlider = new Fl_Value_Slider(groupPos.w + 10,
											  groupPos.h + 20,
											  140, 20, "Head Angle");
		gui->headSlider->type(FL_HOR_NICE_SLIDER);	// ナイスなスライダー
		gui->headSlider->minimum(-FK_PI);	// 最小値は -3.14
		gui->headSlider->maximum(FK_PI);	// 最高値は 3.14
		gui->headSlider->value(0.0);		// 初期値は 0
		gui->headSlider->labelsize(12);		// ラベル文字のサイズを 12pt に
		gui->headSlider->textsize(12);		// カウンタのサイズも 12 に e

		// ピッチ角用スライダー各種設定 
		gui->pitchSlider = new Fl_Value_Slider(groupPos.w + 10,
											   groupPos.h + 75,
											   140, 20, "Pitch Angle");
		gui->pitchSlider->type(FL_HOR_NICE_SLIDER);
		gui->pitchSlider->minimum(-FK_PI);
		gui->pitchSlider->maximum(FK_PI);
		gui->pitchSlider->value(0.0);
		gui->pitchSlider->labelsize(12);
		gui->pitchSlider->textsize(12);

		// ピッチ角用スライダー各種設定 
		gui->bankSlider = new Fl_Value_Slider(groupPos.w + 10,
											  groupPos.h + 130,
											  140, 20, "Bank Angle");
		gui->bankSlider->type(FL_HOR_NICE_SLIDER);
		gui->bankSlider->minimum(-FK_PI);
		gui->bankSlider->maximum(FK_PI);
		gui->bankSlider->value(0.0);
		gui->bankSlider->labelsize(12);
		gui->bankSlider->textsize(12);

		// スケーリング用ローラー各種設定 
		gui->scaleRoller = new Fl_Roller(groupPos.w + 180,
										 groupPos.h + 15,
										 15, 140, "Scale");
		gui->scaleRoller->type(FL_VERTICAL);		// ローラーは縦向き
		gui->scaleRoller->minimum(100.0);
		gui->scaleRoller->maximum(-100.0);
		gui->scaleRoller->value(0.0);
		gui->scaleRoller->labelsize(12);

		// 座標軸用ローラー各種設定 
		gui->axisRoller = new Fl_Roller(groupPos.w + 20,
										groupPos.h + 200,
										140, 15, "Axis Scale");
		gui->axisRoller->type(FL_HORIZONTAL);
		gui->axisRoller->minimum(-100.0);
		gui->axisRoller->maximum(100.0);
		gui->axisRoller->value(0.0);
		gui->axisRoller->labelsize(12);

	} gui->ortGroup->end();

	return;
}

void fk_ShapeViewer::InitFlag(void)
{
	changeFlag = false;
	lightFlag = false;
	materialFlag = false;
	moveFlag = false;
	oldMoveFlag = false;

	drawMode = FK_POLYMODE | FK_LINEMODE;
	return;
}

void fk_ShapeViewer::LightInit(void)
{
	fk_Material		mat;

	mat.setAmbient(1.0, 1.0, 1.0);
	mat.setDiffuse(1.0, 1.0, 1.0);
	mat.setSpecular(1.0, 1.0, 1.0);

	lightModel[0].setShape(&light);
	lightModel[0].setMaterial(mat);
	lightModel[0].glFocus(-1.0, -1.0, 0.0);

	lightModel[1].setShape(&light);
	lightModel[1].setMaterial(mat);
	lightModel[1].glFocus(1.0, -1.0, 0.0);

	scene.entryModel(&lightModel[0]);
	scene.entryModel(&lightModel[1]);

	return;
}

void fk_ShapeViewer::AxisInit(void)
{
	fk_Vector		linePos[4], rPos, lPos;
	fk_Material		localRed, localGreen, localCyan;
	fk_Edge			*curE;

	localRed.setAmbient(1.0f, 0.0f, 0.0f);
	localGreen.setAmbient(0.0f, 1.0f, 0.0f);
	localCyan.setAmbient(0.0f, 1.0f, 1.0f);

	linePos[0].set(0.0, 0.0, 0.0);
	linePos[1].set(1.0, 0.0, 0.0);
	linePos[2].set(0.0, 1.0, 0.0);
	linePos[3].set(0.0, 0.0, 1.0);

	axisLine.allClear();
	axisLine.pushLine(linePos[0], linePos[1]);
	axisLine.pushLine(linePos[0], linePos[2]);
	axisLine.pushLine(linePos[0], linePos[3]);

	axisLine.setPalette(localRed, 0);
	axisLine.setPalette(localGreen, 1);
	axisLine.setPalette(localCyan, 2);

	curE = axisLine.getNextE(NULL);
	while(curE != NULL) {
		rPos = axisLine.getRightVOnE(curE)->getPosition();
		lPos = axisLine.getLeftVOnE(curE)->getPosition();

		if(rPos.x > 0.5 || lPos.x > 0.5) {
			curE->setElemMaterialID(0);
		} else if(rPos.y > 0.5 || lPos.y > 0.5) {
			curE->setElemMaterialID(1);
		} else if(rPos.z > 0.5 || lPos.z > 0.5) {
			curE->setElemMaterialID(2);
		}

		curE = axisLine.getNextE(curE);
	}

	axisModel.setShape(&axisLine);
	axisModel.setParent(&parentModel);
	axisLine.setMaterialMode(FK_PARENT_MODE);
	axisModel.setMaterialMode(FK_PARENT_MODE);
	scene.entryModel(&axisModel);
	axisFlag = true;
	return;
}

void fk_ShapeViewer::ViewInit(void)
{
	camera.glTranslate(0.0, 0.0, 1000.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	scene.entryCamera(&camera);

	return;
}

void fk_ShapeViewer::clearModel(void)
{
	_st		i;

	for(i = 0; i < modelArray.size(); i++) {
		scene.removeModel(modelArray[i]);

		delete modelArray[i];
		delete polyMaterial[i];
		delete edgeColor[i];
		delete vertexColor[i];
	}

	modelArray.clear();
	polyMaterial.clear();
	edgeColor.clear();
	vertexColor.clear();
	IDMap.clear();

	return;
}

void fk_ShapeViewer::SetAllMaterial(void)
{
	_st		i;

	for(i = 0; i < modelArray.size(); i++) {
		modelArray[i]->setMaterial(*polyMaterial[i]);
		modelArray[i]->setLineColor(edgeColor[i]);
		modelArray[i]->setPointColor(vertexColor[i]);
	}
	return;
}

void fk_ShapeViewer::SetSceneFlg(fk_ShapeGUIMenuItem argStatus)
{
	switch(argStatus) {
	  case FK_SV_GUI_POLYDRAW:
		drawMode ^= FK_POLYMODE;
		break;
	  case FK_SV_GUI_EDGEDRAW:
		drawMode ^= FK_LINEMODE;
		break;
	  case FK_SV_GUI_VERTEXDRAW:
		drawMode ^= FK_POINTMODE;
		break;
	  default:
		return;
	}

	SetDrawMode();
	return;
}

void fk_ShapeViewer::ModelInit(int argIndex, fk_Shape *argShape)
{
	fk_Model	*localModel;
	_st			trueID;
	fk_Material	mat;
	fk_Color	eCol, vCol;
	fk_Material	*matP;
	fk_Color	*eColP, *vColP;

	mat = Material::Yellow;
	eCol.set(0.0, 0.0, 1.0);
	vCol.set(0.0, 1.0, 0.0);

	if(IDMap.find(argIndex) == IDMap.end()) {

		IDMap[argIndex] = int(modelArray.size());

		localModel = new fk_Model();
		modelArray.push_back(localModel);
		localModel->setParent(&parentModel);

		matP = new fk_Material();
		*matP = mat;
		polyMaterial.push_back(matP);

		eColP = new fk_Color();
		*eColP = eCol;
		edgeColor.push_back(eColP);

		vColP = new fk_Color();
		*vColP = vCol;
		vertexColor.push_back(vColP);

	} else {
		trueID = static_cast<_st>(IDMap[argIndex]);
		localModel = modelArray[trueID];
	}

	if(argShape == NULL) {
		localModel->setShape(NULL);
		return;
	}

	switch(argShape->getObjectType()) {
	  case FK_RECTTEXTURE:
	  case FK_TRITEXTURE:
	  case FK_MESHTEXTURE:
	  case FK_IFSTEXTURE:
		localModel->setShape(argShape);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
	  case FK_POINT:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
	  case FK_LIGHT:
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_LINE:

		argShape->setMaterialMode(FK_PARENT_MODE);
		parentModel.setMaterialMode(FK_PARENT_MODE);

		localModel->setShape(argShape);
		localModel->setMaterial(mat);
		localModel->setLineColor(&eCol);
		localModel->setPointColor(&vCol);
		localModel->setWidth(1.0);
		localModel->setSize(3.0);

		if(materialFlag == true ) {
			localModel->setMaterialMode(FK_PARENT_MODE);
		} else {
			localModel->setMaterialMode(FK_CHILD_MODE);
		}

		SetDrawMode();

		break;

	  default:
		return;
	}

	scene.entryModel(localModel);
	materialFlag = false;

	return;
}

void fk_ShapeViewer::RotateLight(double argAngle)
{
	lightModel[0].glRotateWithVec(0.0, 0.0, 0.0, fk_Y, argAngle);
	lightModel[1].glRotateWithVec(0.0, 0.0, 0.0, fk_Y, argAngle);

	return;
}

string fk_ShapeViewer::CommonFileChooser(string argFil,
										 int argType,
										 string argTitle)
{
	Fl_Native_File_Chooser	*fc;
	string					fileName = "";
	string					pathName;

	pathName = fk_System::get_cwd();
	fc = new Fl_Native_File_Chooser();
	fc->type(argType);
	fc->title(argTitle.c_str());
	fc->filter(argFil.c_str());
	if(pathName.empty() == false) fc->directory(pathName.c_str());

	switch(fc->show()) {
	  case -1:
		fl_alert("%s", fc->errmsg());
		break;
	  case 1:
		return fileName;
	  default:
		break;
	}

	fileName = fc->filename();
	delete fc;
	return fileName;
}

bool fk_ShapeViewer::MenuSelect(void)
{
	int				i;
	_st				j;
	string			fileName;
	double			colR, colG, colB, shininess;
	fk_Shape		*shape;
	fk_Solid		*solid = NULL;
	fk_IndexFaceSet	*ifset;
	ifstream	  	ifs;
	const char		*str;
	stringstream	ss;

	switch(globalMenuStatus) {

	  case FK_SV_GUI_NONE:
		break;

	  case FK_SV_GUI_QUIT:
		globalMenuStatus = FK_SV_GUI_NONE;
		return false;

	  case FK_SV_GUI_WRLOPEN:
		fileName = CommonFileChooser("*.wrl",
									 Fl_Native_File_Chooser::BROWSE_FILE,
									 "VRML2.0 File Select");
		if(fileName.length() == 0) break;
		if(localSolid.readVRMLFile(fileName, true, false) == false) {
			fl_alert("%s : This is NOT VRML file.", fileName.c_str());
		} else {
			changeFlag = true;
			materialFlag = true;
		}

		SetDrawMode();

		shapeProcess(&localSolid);

		break;

	  case FK_SV_GUI_STLOPEN:
		fileName = CommonFileChooser("*.stl",
									 Fl_Native_File_Chooser::BROWSE_FILE,
									 "STL File Select");
		if(fileName.length() == 0) break;

		if(localSolid.readSTLFile(fileName, false) == false) {
			fl_alert("%s is not STL file.", fileName.c_str());
		} else {
			changeFlag = true;
		}

		shapeProcess(&localSolid);

		break;

	  case FK_SV_GUI_DXFOPEN:
		fileName = CommonFileChooser("*.dxf",
									 Fl_Native_File_Chooser::BROWSE_FILE,
									 "DXF File Select");
		if(fileName.length() == 0) break;

		if(localSolid.readDXFFile(fileName, false) == false) {
			fl_alert("%s is not DXF file.", fileName.c_str());
		} else {
			changeFlag = true;
		}

		shapeProcess(&localSolid);

		break;

	  case FK_SV_GUI_WRLSAVE:

		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save File Select");

		if(fileName.length() == 0) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", NULL, "No", "Yes") == 1) {
				break;
			}
		}

		shape = getShape(0);
		if(shape == NULL) break;

		switch(shape->getObjectType()) {
		  case FK_SOLID:
		  case FK_POLYGON:
		  case FK_LINE:
		  case FK_POLYLINE:
		  case FK_CLOSEDLINE:
		  case FK_POINT:
			solid = static_cast<fk_Solid *>(shape);
			if(solid->writeVRMLFile(fileName, polyMaterial[0]) == false) {
				fl_alert("%s: Can't Write.", fileName.c_str());
			}
			break;

		  case FK_INDEXFACESET:
		  case FK_BLOCK:
		  case FK_CIRCLE:
		  case FK_SPHERE:
		  case FK_PRISM:
		  case FK_CONE:
			ifset = static_cast<fk_IndexFaceSet *>(shape);
			if(ifset->writeVRMLFile(fileName, polyMaterial[0]) == false) {
				fl_alert("%s: Can't Write.", fileName.c_str());
			}
			break;

		  default:
			break;
		}

		break;

	  case FK_SV_GUI_STLSAVE:
		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save File Select");

		if(fileName.length() == 0) break;

		shape = getShape(0);
		if(shape == NULL) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", NULL, "No", "Yes") == 1) {
				break;
			}
		}

		if(solid == NULL) break;
		if(solid->writeSTLFile(fileName) == false) {
			fl_alert("%s: Can't Write.", fileName.c_str());
		}
		// ModelInit(0, &localSolid);

		break;

	  case FK_SV_GUI_IMAGESNAP:
		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save Image File Select");

		if(fileName.length() == 0) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", NULL, "No", "Yes") == 1) {
				break;
			}
		}

		Fl::check();
		viewWin->drawWindow();
		Fl::check();
		viewWin->drawWindow();
		Fl::check();

		if(snapImage(fileName) == false) {
			fl_alert("%s: Can't Write.", fileName.c_str());
		}
		break;

	  case FK_SV_GUI_POLYDRAW:
	  case FK_SV_GUI_EDGEDRAW:
	  case FK_SV_GUI_VERTEXDRAW:
		SetSceneFlg(globalMenuStatus);
		break;

	  case FK_SV_GUI_LIGHTROTATE:
		lightFlag = globalMenuValue;
		break;

	  case FK_SV_GUI_AXISDRAW:
		if(globalMenuValue == true) {
			scene.entryModel(&axisModel);
			axisFlag = true;
		} else {
			scene.removeModel(&axisModel);
			axisFlag = false;
		}
		break;

	  case FK_SV_GUI_AMBIENT:
	  case FK_SV_GUI_DIFFUSE:
	  case FK_SV_GUI_SPECULAR:
	  case FK_SV_GUI_EMISSION:
	  case FK_SV_GUI_EDGECOLOR:
	  case FK_SV_GUI_VERTEXCOLOR:

		GetMaterial(0, globalMenuStatus, &colR, &colG, &colB);
		fl_color_chooser("Material Set", colR, colG, colB);
		for(i = 0; i < getModelNum(); i++) {
			SetMaterial(i, globalMenuStatus, colR, colG, colB);
		}

		SetAllMaterial();
		break;

	  case FK_SV_GUI_SHININESS:

		ss.clear();
		shininess = polyMaterial[0]->getShininess();
		ss << shininess;
		str = fl_input("Please input Shininess Value.", ss.str().c_str());
		if(str == NULL) break;
		shininess = atof(str);
		if(shininess >= 1.0 && shininess <= 128.0) {
			for(j = 0; j < static_cast<_st>(getModelNum()); j++) {
				polyMaterial[j]->setShininess(shininess);
			}
		}
		SetAllMaterial();
		break;
	  default:
		break;
	}
	globalMenuStatus = FK_SV_GUI_NONE;
	return true;

}

void fk_ShapeViewer::SetOrientation(double argHead, double argPitch,
									double argBank, double argScale)
{
	parentModel.glAngle(argHead, argPitch, argBank);
	parentModel.setScale(argScale);

	return;
}

void fk_ShapeViewer::SetAxisLine(double argVal)
{
	fk_Vector		pos[3];

	pos[0].set(argVal, 0.0, 0.0);
	pos[1].set(0.0, argVal, 0.0);
	pos[2].set(0.0, 0.0, argVal);

	axisLine.setVertex(0, 1, pos[0]);
	axisLine.setVertex(1, 1, pos[1]);
	axisLine.setVertex(2, 1, pos[2]);

	return;
}

void fk_ShapeViewer::MovePosition(double argX, double argY, double argZ)
{
	fk_Matrix		mat;
	fk_Vector		orgVec(argX, argY, argZ), vec;
	_st				i;

	mat = parentModel.getInvMatrix();
	vec = mat * orgVec;

	for(i = 0; i < modelArray.size(); i++) {
		modelArray[i]->glTranslate(vec);
	}

	axisModel.glTranslate(vec);
	return;
}

void fk_ShapeViewer::DragShape(void)
{
	double		tmpX, tmpY;

	if(viewWin == NULL) return;
	if(viewWin->getMouseStatus(FK_MOUSE1) == true) {
		moveFlag = true;
		double oldX = mouseX;
		double oldY = mouseY;
		viewWin->getMousePosition(&mouseX, &mouseY);
		if(oldMoveFlag == true) {
			tmpX = static_cast<double>(mouseX - oldX)*720.0/static_cast<double>(fkWinSize.h);
			tmpY = static_cast<double>(oldY - mouseY)*720.0/static_cast<double>(fkWinSize.h);
			MovePosition(tmpX, tmpY, 0.0);
		}
	} else {
		moveFlag = false;
	}
	return;
}

void fk_ShapeViewer::KeyHandle(void)
{
	if(viewWin == NULL) return;

	if(viewWin->getKeyStatus(' ', false) == true) {
		if(viewWin->getSpecialKeyStatus(FK_SHIFT_R, false) == true ||
		   viewWin->getSpecialKeyStatus(FK_SHIFT_L, false) == true) {
			setScale(getScale()/1.005);
		} else {
			setScale(getScale()*1.005);
		}
	}

	if(viewWin->getSpecialKeyStatus(FK_LEFT, false) == true) {
		setHead(getHead() - 0.02);
	}

	if(viewWin->getSpecialKeyStatus(FK_RIGHT, false) == true) {
		setHead(getHead() + 0.02);
	}

	return;
}

bool fk_ShapeViewer::draw(void)
{
	bool	loopFlg;

	if(mainWindow == NULL || viewWin == NULL) return false;

	if(MenuSelect() == false) {
		return false;
	}

	if(lightFlag == true) {
		RotateLight(FK_PI/100.0);
	}

	if(changeFlag == true) {
		clearModel();
		ModelInit(0, &localSolid);
		changeFlag = false;
	}

	DragShape();
	KeyHandle();

	oldMoveFlag = moveFlag;

	SetOrientation(getHead(), getPitch(), getBank(), getScale());
	SetAxisLine(getAxisScale());

	loopFlg = true;
	while(loopFlg == true) {
		if(mainWindow->visible() == 0) {
			if(Fl::wait() == 0) return false;
			continue;
		}

		if(viewWin->drawWindow() == 0) return false;
		if(Fl::check() == 0) return false;

		if(viewWin->winOpenStatus() == false) continue;
		loopFlg = false;
	}

	return true;
}

void fk_ShapeViewer::setWindowSize(int argW, int argH)
{
	fkWinSize.set(argW, argH);
	allWinSize.set(fkWinSize.w + 245, fkWinSize.h + 50);
	groupPos.set(fkWinSize.w + 20, 40);

	InitWindow();
	return;
}

void fk_ShapeViewer::setOGLPointerMode(bool argMode)
{
	if(viewWin == NULL) return;
	viewWin->setOGLPointerMode(argMode);
	return;
}

bool fk_ShapeViewer::getOGLPointerMode(void)
{
	if(viewWin == NULL) return false;
	return viewWin->getOGLPointerMode();
}


void fk_ShapeViewer::setShape(int argIndex, fk_Shape *argShape)
{
	if(argShape == NULL) {
		ModelInit(argIndex, NULL);
		return;
	}

	if(argShape->getPaletteSize() > 0) {
		materialFlag = true;
	}

	ModelInit(argIndex, argShape);
	return;
}

void fk_ShapeViewer::setShape(fk_Shape *argShape)
{
	setShape(0, argShape);
	return;
}

void fk_ShapeViewer::setDrawMode(fk_DrawMode argMode)
{
	drawMode = argMode;
	SetDrawMode();

	return;
}

void fk_ShapeViewer::setDrawMode(int argID, fk_DrawMode argMode)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->setDrawMode(argMode);
	return;
}

void fk_ShapeViewer::SetDrawMode(void)
{
	_st				i;
	Fl_Menu_Item	*mP, *mE, *mV;

	mP = const_cast<Fl_Menu_Item *>(gui->menuBar->menu() + 9);
	mE = const_cast<Fl_Menu_Item *>(gui->menuBar->menu() + 10);
	mV = const_cast<Fl_Menu_Item *>(gui->menuBar->menu() + 11);

	mP->flags = mE->flags = mV->flags = FL_MENU_TOGGLE;

	if((drawMode & FK_POLYMODE) != FK_NONEMODE) {
		mP->flags |= FL_MENU_VALUE;
	}

	if((drawMode & FK_LINEMODE) != FK_NONEMODE) {
		mE->flags |= FL_MENU_VALUE;
	}

	if((drawMode & FK_POINTMODE) != FK_NONEMODE) {
		mV->flags |= FL_MENU_VALUE;
	}

	for(i = 0; i < modelArray.size(); i++) {
		modelArray[i]->setDrawMode(drawMode);
	}

	return;
}

void fk_ShapeViewer::setElementMode(fk_ElementMode argMode)
{
	for(_st i = 0; i < modelArray.size(); i++) {
		modelArray[i]->setElementMode(argMode);
	}

	return;
}

void fk_ShapeViewer::setElementMode(int argID, fk_ElementMode argMode)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->setElementMode(argMode);
	return;
}

fk_ElementMode fk_ShapeViewer::getElementMode(void)
{
	if(modelArray.empty() == true) return FK_ELEM_NONE;
	return modelArray[0]->getElementMode();
}

fk_ElementMode fk_ShapeViewer::getElementMode(int argID)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return FK_ELEM_NONE;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	return model->getElementMode();
}
	
void fk_ShapeViewer::setBlendStatus(bool argMode)
{
	scene.setBlendStatus(argMode);
	return;
}

bool fk_ShapeViewer::getBlendStatus(void)
{
	return scene.getBlendStatus();
}

void fk_ShapeViewer::setFrameMode(fk_FrameMode argMode)
{
	if(viewWin == NULL) return;
	viewWin->setFrameMode(argMode);
	return;
}

void fk_ShapeViewer::setFrameInterval(int argInterval)
{
	if(viewWin == NULL) return;
	viewWin->setFrameInterval(argInterval);
	return;
}

void fk_ShapeViewer::setBGColor(fk_Color argColor)
{
	scene.setBGColor(argColor);
	return;
}

void fk_ShapeViewer::setBGColor(float argR, float argG, float argB)
{
	scene.setBGColor(argR, argG, argB);
	return;
}

fk_Color fk_ShapeViewer::getBGColor(void)
{
	return scene.getBGColor();
}

void fk_ShapeViewer::setHead(double argVal)
{
	int		div;
	double	trueVal;

	div = static_cast<int>(argVal / (2.0*FK_PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*FK_PI);
	if(trueVal >= FK_PI) {
		trueVal -= 2.0*FK_PI;
	} else if(trueVal <= -FK_PI) {
		trueVal += 2.0*FK_PI;
	}

	Fl::focus(gui->headSlider);
	gui->headSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setPitch(double argVal)
{
	int		div;
	double	trueVal;

	div = static_cast<int>(argVal / (2.0*FK_PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*FK_PI);
	if(trueVal >= FK_PI) {
		trueVal -= 2.0*FK_PI;
	} else if(trueVal <= -FK_PI) {
		trueVal += 2.0*FK_PI;
	}

	Fl::focus(gui->pitchSlider);
	gui->pitchSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setBank(double argVal)
{
	int		div;
	double	trueVal;

	div = static_cast<int>(argVal / (2.0*FK_PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*FK_PI);
	if(trueVal >= FK_PI) {
		trueVal -= 2.0*FK_PI;
	} else if(trueVal <= -FK_PI) {
		trueVal += 2.0*FK_PI;
	}

	Fl::focus(gui->bankSlider);
	gui->bankSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setScale(double argVal)
{
	Fl::focus(gui->scaleRoller);
	if(argVal <= 0.0) return;
	gui->scaleRoller->value(log10(argVal));
}

void fk_ShapeViewer::setAxisScale(double argVal)
{
	if(argVal <= 0.0) return;
	gui->axisRoller->value(log10(argVal));
}

void fk_ShapeViewer::setAxisMode(bool argMode)
{
	Fl_Menu_Item		*mA;

	mA = const_cast<Fl_Menu_Item *>(gui->menuBar->menu() + 12);
	mA->flags = FL_MENU_TOGGLE;
	if(argMode == true) {
		axisFlag = true;
		scene.entryModel(&axisModel);
		mA->flags |= FL_MENU_VALUE;
	} else {
		axisFlag = false;
		scene.removeModel(&axisModel);
	}
	return;
}

void fk_ShapeViewer::setPosition(int argID, fk_Vector argPos)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->glMoveTo(argPos);
	return;
}

void fk_ShapeViewer::setPosition(int argID,
								 double argX, double argY, double argZ)
{
	fk_Vector		pos(argX, argY, argZ);

	setPosition(argID, pos);
	return;
}

void fk_ShapeViewer::setMaterial(int argID, fk_Material argMat)
{
	_st		trueID;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);

	*polyMaterial[trueID] = argMat;
	SetAllMaterial();
	return;
}

void fk_ShapeViewer::setEdgeColor(int argID, fk_Color argCol)
{
	_st		trueID;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);

	*edgeColor[trueID] = argCol;
	SetAllMaterial();
	return;
}


void fk_ShapeViewer::setVertexColor(int argID, fk_Color argCol)
{
	_st		trueID;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);

	*vertexColor[trueID] = argCol;
	SetAllMaterial();
	return;
}

void fk_ShapeViewer::setAngle(int argID, fk_Angle argAngle)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->glAngle(argAngle);
	return;
}

void fk_ShapeViewer::setAngle(int argID,
							  double argH, double argP, double argB)
{
	fk_Angle		angle(argH, argP, argB);

	setAngle(argID, angle);
	return;
}

void fk_ShapeViewer::setVec(int argID, fk_Vector argVec)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->glVec(argVec);
	return;
}

void fk_ShapeViewer::setVec(int argID, double argX, double argY, double argZ)
{
	fk_Vector		vec(argX, argY, argZ);

	setVec(argID, vec);
	return;
}

void fk_ShapeViewer::setUpvec(int argID, fk_Vector argVec)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->glUpvec(argVec);
	return;
}

void fk_ShapeViewer::setUpvec(int argID, double argX, double argY, double argZ)
{
	fk_Vector		vec(argX, argY, argZ);

	setUpvec(argID, vec);
	return;
}

void fk_ShapeViewer::setLineWidth(int argID, double argW)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->setWidth(argW);
	return;
}

void fk_ShapeViewer::setPointSize(int argID, double argS)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	model->setSize(argS);
	return;
}

int fk_ShapeViewer::getModelNum(void)
{
	return static_cast<int>(modelArray.size());
}

fk_Shape * fk_ShapeViewer::getShape(int argID)
{
	if(IDMap.find(argID) == IDMap.end()) {
		return(NULL);
	}

	return modelArray[static_cast<_st>(IDMap[argID])]->getShape();
}

fk_DrawMode fk_ShapeViewer::getDrawMode(void)
{
	if(modelArray.empty() == true) {
		return FK_NONEMODE;
	}

	return modelArray[0]->getDrawMode();
}

fk_DrawMode fk_ShapeViewer::getDrawMode(int argID)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return FK_NONEMODE;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	return model->getDrawMode();
}

fk_FrameMode fk_ShapeViewer::getFrameMode(void)
{
	if(viewWin == NULL) return FK_DEFAULT_FRAME;
	return viewWin->getFrameMode();
}

int fk_ShapeViewer::getFrameInterval(void)
{
	if(viewWin == NULL) return 0;
	return viewWin->getFrameInterval();
}

int fk_ShapeViewer::getSkipFrame(void)
{
	if(viewWin == NULL) return 0;
	return viewWin->getSkipFrame();
}

double fk_ShapeViewer::getHead(void)
{
	return gui->headSlider->value();
}

double fk_ShapeViewer::getPitch(void)
{
	return gui->pitchSlider->value();
}

double fk_ShapeViewer::getBank(void)
{
	return gui->bankSlider->value();
}

double fk_ShapeViewer::getScale(void)
{
	return pow(10.0, gui->scaleRoller->value());
}

double fk_ShapeViewer::getAxisScale(void)
{
	return pow(10.0, gui->axisRoller->value());
}

bool fk_ShapeViewer::getAxisMode(void)
{
	return axisFlag;
}

fk_Vector fk_ShapeViewer::getCenter(void)
{
	fk_Vector	dummy(0.0, 0.0, 0.0);

	if(modelArray.empty() == true) {
		return dummy;
	}

	return -(modelArray[0]->getInhPosition());
}

double fk_ShapeViewer::getLineWidth(int argID)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return -1.0;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	return model->getWidth();
}

double fk_ShapeViewer::getPointSize(int argID)
{
	_st			trueID;
	fk_Model	*model;

	if(IDMap.find(argID) == IDMap.end()) return -1.0;
	trueID = static_cast<_st>(IDMap[argID]);
	model = modelArray[trueID];
	return model->getWidth();
}

bool fk_ShapeViewer::shapeProcess(fk_Solid *)
{
	return true;
}

bool fk_ShapeViewer::snapImage(string argFName, fk_ImageType argFormat,
							   fk_SnapProcMode argMode)
{
	if(viewWin == NULL) return false;
	return viewWin->snapImage(argFName, argFormat, argMode);
}

bool fk_ShapeViewer::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	if(viewWin == NULL) return false;
	return viewWin->snapImage(argImage, argMode);
}

void fk_ShapeViewer::setPutStrMode(const fk_PutStrMode argMode)
{
	fk_Window::setPutStrMode(argMode);
	return;
}

fk_PutStrMode fk_ShapeViewer::getPutStrMode(void)
{
	return fk_Window::getPutStrMode();
}

bool fk_ShapeViewer::setPutFile(const string &argFileName)
{
	return fk_Window::setPutFile(argFileName);
}

void fk_ShapeViewer::putString(const string &argStr)
{
	fk_Window::putString(argStr);
	return;
}

#ifndef FK_CLI_CODE
void fk_ShapeViewer::printf(const char *argFormat, ...)
{
	va_list		ap;
	char		buffer[1024];

	va_start(ap, argFormat);
	vsnprintf(buffer, 1023, argFormat, ap);
	va_end(ap);
	fk_Window::putString(buffer);
	return;
}
#endif

void fk_ShapeViewer::clearBrowser(void)
{
	fk_Window::clearBrowser();
	return;
}

void fk_ShapeViewer::SetFinalizeMode(void)
{
	parentModel.SetTreeDelMode(false);
	for(_st i = 0; i < modelArray.size(); i++) {
		modelArray[i]->SetTreeDelMode(false);
	}
	lightModel[0].SetTreeDelMode(false);
	lightModel[1].SetTreeDelMode(false);
	camera.SetTreeDelMode(false);
	axisModel.SetTreeDelMode(false);

	return;
}
