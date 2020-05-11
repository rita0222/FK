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

static fk_ShapeGUIMenuItem	globalMenuStatus = fk_ShapeGUIMenuItem::NONE;
static bool					globalMenuValue = true;

namespace FK {
	class fk_GUI_ {
	public:

		Fl_Menu_Bar *menuBar;
		Fl_Group *ortGroup;
		Fl_Value_Slider *headSlider;
		Fl_Value_Slider *pitchSlider;
		Fl_Value_Slider *bankSlider;
		Fl_Roller *scaleRoller;
		Fl_Roller *axisRoller;
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

	if(mItem == nullptr) return;
	labelString = mItem->label();
	if(labelString == "&WRLOpen") {
		globalMenuStatus = fk_ShapeGUIMenuItem::WRLOPEN;
	} else if(labelString == "S&TLOpen") {
		globalMenuStatus = fk_ShapeGUIMenuItem::STLOPEN;
	} else if(labelString == "D&XFOpen") {
		globalMenuStatus = fk_ShapeGUIMenuItem::DXFOPEN;
	} else if(labelString == "WRL&Save") {
		globalMenuStatus = fk_ShapeGUIMenuItem::WRLSAVE;
	} else if(labelString == "STLSave") {
		globalMenuStatus = fk_ShapeGUIMenuItem::STLSAVE;
	} else if(labelString == "&ImageSnap") {
		globalMenuStatus = fk_ShapeGUIMenuItem::IMAGESNAP;
	} else if(labelString == "&Quit") {
		globalMenuStatus = fk_ShapeGUIMenuItem::QUIT;
	} else if(labelString == "&PolyDraw") {
		globalMenuStatus = fk_ShapeGUIMenuItem::POLYDRAW;
	} else if(labelString == "&EdgeDraw") {
		globalMenuStatus = fk_ShapeGUIMenuItem::EDGEDRAW;
	} else if(labelString == "&VertexDraw") {
		globalMenuStatus = fk_ShapeGUIMenuItem::VERTEXDRAW;
	} else if(labelString == "&AxisDraw") {
		globalMenuStatus = fk_ShapeGUIMenuItem::AXISDRAW;
	} else if(labelString == "LightRotate") {
		globalMenuStatus = fk_ShapeGUIMenuItem::LIGHTROTATE;
	} else if(labelString == "Ambient") {
		globalMenuStatus = fk_ShapeGUIMenuItem::AMBIENT;
	} else if(labelString == "Diffuse") {
		globalMenuStatus = fk_ShapeGUIMenuItem::DIFFUSE;
	} else if(labelString == "Specular") {
		globalMenuStatus = fk_ShapeGUIMenuItem::SPECULAR;
	} else if(labelString == "Emission") {
		globalMenuStatus = fk_ShapeGUIMenuItem::EMISSION;
	} else if(labelString == "Shininess") {
		globalMenuStatus = fk_ShapeGUIMenuItem::SHININESS;
	} else if(labelString == "VertexColor") {
		globalMenuStatus = fk_ShapeGUIMenuItem::VERTEXCOLOR;
	} else if(labelString == "EdgeColor") {
		globalMenuStatus = fk_ShapeGUIMenuItem::EDGECOLOR;
	}

 	globalMenuValue = (mItem->value() != 0) ? true : false;

	return;
}

fk_ShapeViewer::Member::Member(void) :
	gui(make_unique<fk_GUI_>())
{
	return;
}

fk_ShapeViewer::fk_ShapeViewer(int argW, int argH) :
	fk_BaseObject(fk_Type::SHAPEVIEWER), _m(make_unique<Member>())
{
	InitValue();
	LightInit();
	AxisInit();
	ViewInit();
	clearModel();

	setWindowSize(argW, argH);
	ModelInit(0, &_m->localSolid);

	return;
}

fk_ShapeViewer::~fk_ShapeViewer()
{
	return;
}

void fk_ShapeViewer::GetMaterial(int argID, fk_ShapeGUIMenuItem index,
								 double *r, double *g, double *b)
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->polyMaterial.size()) return;

	// Index によってマテリアルの各種属性を (R, G, B) に代入

	switch(index) {
	  case fk_ShapeGUIMenuItem::AMBIENT:
		*r = _m->polyMaterial[id]->getAmbient()->getR();
		*g = _m->polyMaterial[id]->getAmbient()->getG();
		*b = _m->polyMaterial[id]->getAmbient()->getB();
		break;
	  case fk_ShapeGUIMenuItem::DIFFUSE:
		*r = _m->polyMaterial[id]->getDiffuse()->getR();
		*g = _m->polyMaterial[id]->getDiffuse()->getG();
		*b = _m->polyMaterial[id]->getDiffuse()->getB();
		break;
	  case fk_ShapeGUIMenuItem::SPECULAR:
		*r = _m->polyMaterial[id]->getSpecular()->getR();
		*g = _m->polyMaterial[id]->getSpecular()->getG();
		*b = _m->polyMaterial[id]->getSpecular()->getB();
		break;
	  case fk_ShapeGUIMenuItem::EMISSION:
		*r = _m->polyMaterial[id]->getEmission()->getR();
		*g = _m->polyMaterial[id]->getEmission()->getG();
		*b = _m->polyMaterial[id]->getEmission()->getB();
		break;
	  case fk_ShapeGUIMenuItem::EDGECOLOR:
		*r = _m->edgeColor[id]->getR();
		*g = _m->edgeColor[id]->getG();
		*b = _m->edgeColor[id]->getB();
		break;
	  case fk_ShapeGUIMenuItem::VERTEXCOLOR:
		*r = _m->vertexColor[id]->getR();
		*g = _m->vertexColor[id]->getG();
		*b = _m->vertexColor[id]->getB();
		break;
	  default:
		break;
	}
	return;
}

void fk_ShapeViewer::SetMaterial(int argID, fk_ShapeGUIMenuItem index,
								 double r, double g, double b)
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->polyMaterial.size()) return;

	// Index によって (R, G, B) を各種マテリアルに設定 

	switch(index) {
	  case fk_ShapeGUIMenuItem::AMBIENT:
		_m->polyMaterial[id]->setAmbient(r, g, b);
		break;
	  case fk_ShapeGUIMenuItem::DIFFUSE:
		_m->polyMaterial[id]->setDiffuse(r, g, b);
		break;
	  case fk_ShapeGUIMenuItem::SPECULAR:
		_m->polyMaterial[id]->setSpecular(r, g, b);
		break;
	  case fk_ShapeGUIMenuItem::EMISSION:
		_m->polyMaterial[id]->setEmission(r, g, b);
		break;
	  case fk_ShapeGUIMenuItem::EDGECOLOR:
		_m->edgeColor[id]->set(r, g, b);
		break;
	  case fk_ShapeGUIMenuItem::VERTEXCOLOR:
		_m->vertexColor[id]->set(r, g, b);
		break;
	  default:
		break;
	}

	return;
}

fk_Model * fk_ShapeViewer::GetModel(int argID)
{
	if(_m->IDMap.find(argID) == _m->IDMap.end()) return nullptr;
	return _m->modelArray[_st(_m->IDMap[argID])].get();
}
	

void fk_ShapeViewer::InitValue(void)
{
	_m->mainWindow.reset();
	_m->viewWin.reset();

	_m->mouseX = _m->mouseY = -1;

	InitFlag();
	return;
}

void fk_ShapeViewer::InitWindow(void)
{
	double head, pitch, bank, scale, axisScale;
	bool initFlg = true;

	head = pitch = bank = scale = axisScale = 0.0;

	if(_m->mainWindow != nullptr) {
		head = getHead();
		pitch = getPitch();
		bank = getBank();
		scale = getScale();
		axisScale = getAxisScale();
		initFlg = true;
	} else {
		initFlg = false;
	}

	_m->mainWindow.reset();
	_m->mainWindow = make_unique<Fl_Window>(_m->allWinSize.w,
											_m->allWinSize.h,
											"FK Shape Viewer");
	_m->viewWin = make_unique<fk_Window>(10, 40,
										 _m->fkWinSize.w, _m->fkWinSize.h);
	InitGUI();
	_m->mainWindow->end();

	if(initFlg == true) {
		setHead(head);
		setPitch(pitch);
		setBank(bank);
		setScale(scale);
		setAxisScale(axisScale);
	}

	_m->viewWin->setScene(&_m->scene);
	_m->mainWindow->show();
	_m->viewWin->show();

	setFPS(60);
	return;
}

void fk_ShapeViewer::InitGUI(void)
{
	_m->gui->menuBar = new Fl_Menu_Bar(0, 0, _m->allWinSize.w, 30);
	_m->gui->menuBar->menu(menuTable);
	_m->gui->menuBar->callback(LocalMenuToggle);
	globalMenuStatus = fk_ShapeGUIMenuItem::NONE;

	_m->gui->ortGroup = new Fl_Group(_m->groupPos.w, _m->groupPos.h, 215, 240); {

		_m->gui->ortGroup->box(FL_THIN_UP_FRAME);

		// ヘディング角用スライダー各種設定 
		_m->gui->headSlider = new Fl_Value_Slider(_m->groupPos.w + 10,
												  _m->groupPos.h + 20,
												  140, 20, "Head Angle");
		_m->gui->headSlider->type(FL_HOR_NICE_SLIDER);	// ナイスなスライダー
		_m->gui->headSlider->minimum(-fk_Math::PI);	// 最小値は -3.14
		_m->gui->headSlider->maximum(fk_Math::PI);	// 最高値は 3.14
		_m->gui->headSlider->value(0.0);		// 初期値は 0
		_m->gui->headSlider->labelsize(12);		// ラベル文字のサイズを 12pt に
		_m->gui->headSlider->textsize(12);		// カウンタのサイズも 12 に e

		// ピッチ角用スライダー各種設定 
		_m->gui->pitchSlider = new Fl_Value_Slider(_m->groupPos.w + 10,
												   _m->groupPos.h + 75,
												   140, 20, "Pitch Angle");
		_m->gui->pitchSlider->type(FL_HOR_NICE_SLIDER);
		_m->gui->pitchSlider->minimum(-fk_Math::PI);
		_m->gui->pitchSlider->maximum(fk_Math::PI);
		_m->gui->pitchSlider->value(0.0);
		_m->gui->pitchSlider->labelsize(12);
		_m->gui->pitchSlider->textsize(12);

		// ピッチ角用スライダー各種設定 
		_m->gui->bankSlider = new Fl_Value_Slider(_m->groupPos.w + 10,
												  _m->groupPos.h + 130,
												  140, 20, "Bank Angle");
		_m->gui->bankSlider->type(FL_HOR_NICE_SLIDER);
		_m->gui->bankSlider->minimum(-fk_Math::PI);
		_m->gui->bankSlider->maximum(fk_Math::PI);
		_m->gui->bankSlider->value(0.0);
		_m->gui->bankSlider->labelsize(12);
		_m->gui->bankSlider->textsize(12);

		// スケーリング用ローラー各種設定 
		_m->gui->scaleRoller = new Fl_Roller(_m->groupPos.w + 180,
											 _m->groupPos.h + 15,
											 15, 140, "Scale");
		_m->gui->scaleRoller->type(FL_VERTICAL);		// ローラーは縦向き
		_m->gui->scaleRoller->minimum(100.0);
		_m->gui->scaleRoller->maximum(-100.0);
		_m->gui->scaleRoller->value(0.0);
		_m->gui->scaleRoller->labelsize(12);

		// 座標軸用ローラー各種設定 
		_m->gui->axisRoller = new Fl_Roller(_m->groupPos.w + 20,
											_m->groupPos.h + 200,
											140, 15, "Axis Scale");
		_m->gui->axisRoller->type(FL_HORIZONTAL);
		_m->gui->axisRoller->minimum(-100.0);
		_m->gui->axisRoller->maximum(100.0);
		_m->gui->axisRoller->value(0.0);
		_m->gui->axisRoller->labelsize(12);

	} _m->gui->ortGroup->end();

	return;
}

void fk_ShapeViewer::InitFlag(void)
{
	_m->changeFlag = false;
	_m->lightFlag = false;
	_m->materialFlag = false;
	_m->moveFlag = false;
	_m->oldMoveFlag = false;

	_m->drawMode = fk_Draw::FACE | fk_Draw::LINE | fk_Draw::POINT;
	return;
}

void fk_ShapeViewer::LightInit(void)
{
	fk_Material mat(fk_Color(1.0, 1.0, 1.0),
					fk_Color(1.0, 1.0, 1.0),
					fk_Color(1.0, 1.0, 1.0), 30.0);

	_m->lightModel[0].setShape(&_m->light);
	_m->lightModel[0].setMaterial(mat);
	_m->lightModel[0].glFocus(0.0, 0.0, -1.0);
	_m->scene.entryModel(&_m->lightModel[0]);

	return;
}

void fk_ShapeViewer::AxisInit(void)
{
	fk_Vector linePos[4], rPos, lPos;
	fk_Color localRed, localGreen, localCyan;

	localRed.set(1.0f, 0.0f, 0.0f);
	localGreen.set(0.0f, 1.0f, 0.0f);
	localCyan.set(0.0f, 1.0f, 1.0f);

	linePos[0].set(0.0, 0.0, 0.0);
	linePos[1].set(1.0, 0.0, 0.0);
	linePos[2].set(0.0, 1.0, 0.0);
	linePos[3].set(0.0, 0.0, 1.0);

	_m->axisLine.allClear();
	_m->axisLine.pushLine(linePos[0], linePos[1]);
	_m->axisLine.pushLine(linePos[0], linePos[2]);
	_m->axisLine.pushLine(linePos[0], linePos[3]);

	_m->axisLine.setColor(0, localRed);
	_m->axisLine.setColor(1, localGreen);
	_m->axisLine.setColor(2, localCyan);

	_m->axisModel.setShape(&_m->axisLine);
	_m->axisModel.setParent(&_m->parentModel);
	_m->axisModel.setElementMode(fk_ElementMode::ELEMENT);
	_m->scene.entryModel(&_m->axisModel);
	_m->axisFlag = true;
	return;
}

void fk_ShapeViewer::ViewInit(void)
{
	_m->camera.glTranslate(0.0, 0.0, 1000.0);
	_m->camera.glFocus(0.0, 0.0, 0.0);
	_m->camera.glUpvec(0.0, 1.0, 0.0);

	_m->scene.entryCamera(&_m->camera);

	return;
}

void fk_ShapeViewer::clearModel(void)
{
	_m->modelArray.clear();
	_m->polyMaterial.clear();
	_m->edgeColor.clear();
	_m->vertexColor.clear();
	_m->IDMap.clear();

	return;
}

void fk_ShapeViewer::SetAllMaterial(void)
{
	_st		i;

	for(i = 0; i < _m->modelArray.size(); i++) {
		_m->modelArray[i]->setMaterial(*_m->polyMaterial[i]);
		_m->modelArray[i]->setLineColor(_m->edgeColor[i].get());
		_m->modelArray[i]->setPointColor(_m->vertexColor[i].get());
	}
	return;
}

void fk_ShapeViewer::SetSceneFlg(fk_ShapeGUIMenuItem argStatus)
{
	switch(argStatus) {
	  case fk_ShapeGUIMenuItem::POLYDRAW:
		_m->drawMode = _m->drawMode ^ fk_Draw::FACE;
		break;
	  case fk_ShapeGUIMenuItem::EDGEDRAW:
		_m->drawMode = _m->drawMode ^ fk_Draw::LINE;
		break;
	  case fk_ShapeGUIMenuItem::VERTEXDRAW:
		_m->drawMode = _m->drawMode ^ fk_Draw::POINT;
		break;
	  default:
		return;
	}

	SetDrawMode();
	return;
}

void fk_ShapeViewer::ModelInit(int argIndex, fk_Shape *argShape)
{
	fk_Model *localModel;

	if(_m->IDMap.find(argIndex) == _m->IDMap.end()) {

		_m->IDMap[argIndex] = int(_m->modelArray.size());

		_m->modelArray.push_back(make_unique<fk_Model>());
		localModel = _m->modelArray.back().get();
		localModel->setParent(&_m->parentModel);

		_m->polyMaterial.push_back(make_unique<fk_Material>());
		*(_m->polyMaterial.back()) = Material::Yellow;

		_m->edgeColor.push_back(make_unique<fk_Color>());
		_m->edgeColor.back()->set(0.0, 0.0, 1.0);

		_m->vertexColor.push_back(make_unique<fk_Color>());
		_m->vertexColor.back()->set(0.0, 1.0, 0.0);
	} else {
		localModel = GetModel(argIndex);
	}

	if(argShape == nullptr) {
		localModel->setShape(nullptr);
		return;
	}

	switch(argShape->getObjectType()) {
	  case fk_Type::RECTTEXTURE:
	  case fk_Type::TRITEXTURE:
	  case fk_Type::MESHTEXTURE:
	  case fk_Type::IFSTEXTURE:
		localModel->setShape(argShape);
		break;

	  case fk_Type::SOLID:
	  case fk_Type::POLYGON:
	  case fk_Type::POLYLINE:
	  case fk_Type::CLOSEDLINE:
	  case fk_Type::POINT:
	  case fk_Type::CIRCLE:
	  case fk_Type::SPHERE:
	  case fk_Type::PRISM:
	  case fk_Type::CONE:
	  case fk_Type::LIGHT:
	  case fk_Type::INDEXFACESET:
	  case fk_Type::BLOCK:
	  case fk_Type::LINE:

		localModel->setShape(argShape);
		localModel->setMaterial(Material::Yellow);
		localModel->setLineColor(0.0, 0.0, 1.0);
		localModel->setPointColor(0.0, 1.0, 0.0);
		localModel->setWidth(1.0);
		localModel->setSize(3.0);

		SetDrawMode();

		break;

	  default:
		return;
	}

	_m->scene.entryModel(localModel);
	_m->materialFlag = false;

	return;
}

void fk_ShapeViewer::RotateLight(double argAngle)
{
	_m->lightModel[0].glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, argAngle);

	return;
}

string fk_ShapeViewer::CommonFileChooser(string argFil,
										 int argType,
										 string argTitle)
{
	unique_ptr<Fl_Native_File_Chooser> fc(new Fl_Native_File_Chooser());
	string fileName = "";
	string pathName = fk_System::get_cwd();

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
	return fileName;
}

bool fk_ShapeViewer::MenuSelect(void)
{
	int i;
	_st j;
	string fileName;
	double colR, colG, colB, shininess;
	fk_Shape *shape = nullptr;
	fk_Solid *solid = nullptr;
	fk_IndexFaceSet	*ifset = nullptr;
	ifstream ifs;
	stringstream ss;
	const char *str;
	
	switch(globalMenuStatus) {

	  case fk_ShapeGUIMenuItem::NONE:
		break;

	  case fk_ShapeGUIMenuItem::QUIT:
		globalMenuStatus = fk_ShapeGUIMenuItem::NONE;
		return false;

	  case fk_ShapeGUIMenuItem::WRLOPEN:
		fileName = CommonFileChooser("*.wrl",
										 Fl_Native_File_Chooser::BROWSE_FILE,
										 "VRML2.0 File Select");
		if(fileName.length() == 0) break;
		if(_m->localSolid.readVRMLFile(fileName, true, false) == false) {
			fl_alert("%s : This is NOT VRML file.", fileName.c_str());
		} else {
			_m->changeFlag = true;
			_m->materialFlag = true;
		}

		SetDrawMode();

		shapeProcess(&_m->localSolid);

		break;

	  case fk_ShapeGUIMenuItem::STLOPEN:
		fileName = CommonFileChooser("*.stl",
									 Fl_Native_File_Chooser::BROWSE_FILE,
									 "STL File Select");
		if(fileName.length() == 0) break;

		if(_m->localSolid.readSTLFile(fileName, false) == false) {
			fl_alert("%s is not STL file.", fileName.c_str());
		} else {
			_m->changeFlag = true;
		}

		shapeProcess(&_m->localSolid);

		break;

	  case fk_ShapeGUIMenuItem::DXFOPEN:
		fileName = CommonFileChooser("*.dxf",
									 Fl_Native_File_Chooser::BROWSE_FILE,
									 "DXF File Select");
		if(fileName.length() == 0) break;

		if(_m->localSolid.readDXFFile(fileName, false) == false) {
			fl_alert("%s is not DXF file.", fileName.c_str());
		} else {
			_m->changeFlag = true;
		}

		shapeProcess(&_m->localSolid);

		break;

	  case fk_ShapeGUIMenuItem::WRLSAVE:

		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save File Select");

		if(fileName.length() == 0) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", nullptr, "No", "Yes") == 1) {
				break;
			}
		}

		shape = getShape(0);
		if(shape == nullptr) break;

		switch(shape->getObjectType()) {
		  case fk_Type::SOLID:
		  case fk_Type::POLYGON:
		  case fk_Type::LINE:
		  case fk_Type::POLYLINE:
		  case fk_Type::CLOSEDLINE:
		  case fk_Type::POINT:
			solid = static_cast<fk_Solid *>(shape);
			if(solid->writeVRMLFile(fileName, _m->polyMaterial[0].get()) == false) {
				fl_alert("%s: Can't Write.", fileName.c_str());
			}
			break;

		  case fk_Type::INDEXFACESET:
		  case fk_Type::BLOCK:
		  case fk_Type::CIRCLE:
		  case fk_Type::SPHERE:
		  case fk_Type::PRISM:
		  case fk_Type::CONE:
			ifset = static_cast<fk_IndexFaceSet *>(shape);
			if(ifset->writeVRMLFile(fileName, _m->polyMaterial[0].get()) == false) {
				fl_alert("%s: Can't Write.", fileName.c_str());
			}
			break;
			
		  default:
			break;
		}

		break;

	  case fk_ShapeGUIMenuItem::STLSAVE:
		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save File Select");

		if(fileName.length() == 0) break;

		shape = getShape(0);
		if(shape == nullptr) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", nullptr, "No", "Yes") == 1) {
				break;
			}
		}

		solid = static_cast<fk_Solid *>(shape);
		if(solid == nullptr) break;
		if(solid->writeSTLFile(fileName) == false) {
			fl_alert("%s: Can't Write.", fileName.c_str());
		}
		// ModelInit(0, &localSolid);

		break;

	  case fk_ShapeGUIMenuItem::IMAGESNAP:
		fileName = CommonFileChooser("*",
									 Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
									 "Save Image File Select");

		if(fileName.length() == 0) break;

		ifs.open(fileName);
		if(!ifs.fail()) {
			ifs.close();
			if(fl_choice("OverWrite?", nullptr, "No", "Yes") == 1) {
				break;
			}
		}

		Fl::check();
		_m->viewWin->drawWindow();
		Fl::check();
		_m->viewWin->drawWindow();
		Fl::check();

		if(snapImage(fileName) == false) {
			fl_alert("%s: Can't Write.", fileName.c_str());
		}
		break;

	  case fk_ShapeGUIMenuItem::POLYDRAW:
	  case fk_ShapeGUIMenuItem::EDGEDRAW:
	  case fk_ShapeGUIMenuItem::VERTEXDRAW:
		SetSceneFlg(globalMenuStatus);
		break;

	  case fk_ShapeGUIMenuItem::LIGHTROTATE:
		_m->lightFlag = globalMenuValue;
		break;

	  case fk_ShapeGUIMenuItem::AXISDRAW:
		if(globalMenuValue == true) {
			_m->scene.entryModel(&_m->axisModel);
			_m->axisFlag = true;
		} else {
			_m->scene.removeModel(&_m->axisModel);
			_m->axisFlag = false;
		}
		break;

	  case fk_ShapeGUIMenuItem::AMBIENT:
	  case fk_ShapeGUIMenuItem::DIFFUSE:
	  case fk_ShapeGUIMenuItem::SPECULAR:
	  case fk_ShapeGUIMenuItem::EMISSION:
	  case fk_ShapeGUIMenuItem::EDGECOLOR:
	  case fk_ShapeGUIMenuItem::VERTEXCOLOR:

		GetMaterial(0, globalMenuStatus, &colR, &colG, &colB);
		fl_color_chooser("Material Set", colR, colG, colB);
		for(i = 0; i < getModelNum(); i++) {
			SetMaterial(i, globalMenuStatus, colR, colG, colB);
		}

		SetAllMaterial();
		break;

	  case fk_ShapeGUIMenuItem::SHININESS:

		ss.clear();
		shininess = _m->polyMaterial[0]->getShininess();
		ss << shininess;
		str = fl_input("Please input Shininess Value.", ss.str().c_str());
		if(str == nullptr) break;
		shininess = atof(str);
		if(shininess >= 1.0 && shininess <= 128.0) {
			for(j = 0; j < _st(getModelNum()); j++) {
				_m->polyMaterial[j]->setShininess(shininess);
			}
		}
		SetAllMaterial();
		break;

	  default:
		break;
	}
	globalMenuStatus = fk_ShapeGUIMenuItem::NONE;
	return true;

}

void fk_ShapeViewer::SetOrientation(double argHead, double argPitch,
									double argBank, double argScale)
{
	_m->parentModel.glAngle(argHead, argPitch, argBank);
	_m->parentModel.setScale(argScale);

	return;
}

void fk_ShapeViewer::SetAxisLine(double argVal)
{
	_m->axisLine.setVertex(0, 1, fk_Vector(argVal, 0.0, 0.0));
	_m->axisLine.setVertex(1, 1, fk_Vector(0.0, argVal, 0.0));
	_m->axisLine.setVertex(2, 1, fk_Vector(0.0, 0.0, argVal));

	return;
}

void fk_ShapeViewer::MovePosition(double argX, double argY, double argZ)
{
	fk_Vector vec = _m->parentModel.getInvMatrix() * fk_Vector(argX, argY, argZ);

	for(auto &model : _m->modelArray) {
		model->glTranslate(vec);
	}

	_m->axisModel.glTranslate(vec);
	return;
}

void fk_ShapeViewer::DragShape(void)
{
	if(_m->viewWin == nullptr) return;
	if(_m->viewWin->getMouseStatus(fk_MouseButton::M1) == true) {
		_m->moveFlag = true;
		double oldX = double(_m->mouseX);
		double oldY = double(_m->mouseY);
		auto [x, y] = _m->viewWin->getMousePosition();
		_m->mouseX = x;
		_m->mouseY = y;
		if(_m->oldMoveFlag == true) {
			double tmpX = (double(_m->mouseX) - oldX)*720.0/double(_m->fkWinSize.h);
			double tmpY = (oldY - double(_m->mouseY))*720.0/double(_m->fkWinSize.h);
			MovePosition(tmpX, tmpY, 0.0);
		}
	} else {
		_m->moveFlag = false;
	}
	return;
}

void fk_ShapeViewer::KeyHandle(void)
{
	if(_m->viewWin == nullptr) return;

	if(_m->viewWin->getKeyStatus(' ', false) == true) {
		if(_m->viewWin->getSpecialKeyStatus(fk_Key::SHIFT_R, false) == true ||
		   _m->viewWin->getSpecialKeyStatus(fk_Key::SHIFT_L, false) == true) {
			setScale(getScale()/1.005);
		} else {
			setScale(getScale()*1.005);
		}
	}

	if(_m->viewWin->getSpecialKeyStatus(fk_Key::LEFT, false) == true) {
		setHead(getHead() - 0.02);
	}

	if(_m->viewWin->getSpecialKeyStatus(fk_Key::RIGHT, false) == true) {
		setHead(getHead() + 0.02);
	}

	return;
}

bool fk_ShapeViewer::draw(void)
{
	if(_m->mainWindow == nullptr || _m->viewWin == nullptr) return false;

	if(MenuSelect() == false) {
		return false;
	}

	if(_m->lightFlag == true) {
		RotateLight(fk_Math::PI/100.0);
	}

	if(_m->changeFlag == true) {
		clearModel();
		ModelInit(0, &_m->localSolid);
		_m->changeFlag = false;
	}

	DragShape();
	KeyHandle();

	_m->oldMoveFlag = _m->moveFlag;

	SetOrientation(getHead(), getPitch(), getBank(), getScale());
	SetAxisLine(getAxisScale());

	if(_m->fps != 0) _m->fps_admin.timeRegular();
	bool loopFlg = true;
	while(loopFlg == true) {
		if(_m->mainWindow->visible() == 0) {
			if(Fl::wait() == 0) return false;
			continue;
		}

		if(_m->fps_admin.getDrawFlag() || _m->fps == 0) {
			if(_m->viewWin->drawWindow() == 0) return false;
		}
		if(Fl::check() == 0) return false;

		if(_m->viewWin->winOpenStatus() == false) continue;
		loopFlg = false;
	}

	return true;
}

void fk_ShapeViewer::setWindowSize(int argW, int argH)
{
	_m->fkWinSize.set(argW, argH);
	_m->allWinSize.set(_m->fkWinSize.w + 245, _m->fkWinSize.h + 50);
	_m->groupPos.set(_m->fkWinSize.w + 20, 40);

	InitWindow();
	return;
}

void fk_ShapeViewer::setShape(int argIndex, fk_Shape *argShape)
{
	if(argShape == nullptr) {
		ModelInit(argIndex, nullptr);
		return;
	}

	if(argShape->getPaletteSize() > 0) {
		_m->materialFlag = true;
	}

	ModelInit(argIndex, argShape);
	return;
}

void fk_ShapeViewer::setShape(fk_Shape *argShape)
{
	setShape(0, argShape);
	return;
}

void fk_ShapeViewer::setDrawMode(fk_Draw argMode)
{
	_m->drawMode = argMode;
	SetDrawMode();

	return;
}

void fk_ShapeViewer::setDrawMode(int argID, fk_Draw argMode)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setDrawMode(argMode);
	return;
}

void fk_ShapeViewer::SetDrawMode(void)
{
	_st				i;
	Fl_Menu_Item	*mP, *mE, *mV;

	mP = const_cast<Fl_Menu_Item *>(_m->gui->menuBar->menu() + 9);
	mE = const_cast<Fl_Menu_Item *>(_m->gui->menuBar->menu() + 10);
	mV = const_cast<Fl_Menu_Item *>(_m->gui->menuBar->menu() + 11);

	mP->flags = mE->flags = mV->flags = FL_MENU_TOGGLE;

	if((_m->drawMode & fk_Draw::FACE) != fk_Draw::NONE) {
		mP->flags |= FL_MENU_VALUE;
	}

	if((_m->drawMode & fk_Draw::LINE) != fk_Draw::NONE) {
		mE->flags |= FL_MENU_VALUE;
	}

	if((_m->drawMode & fk_Draw::POINT) != fk_Draw::NONE) {
		mV->flags |= FL_MENU_VALUE;
	}

	for(i = 0; i < _m->modelArray.size(); i++) {
		_m->modelArray[i]->setDrawMode(_m->drawMode);
	}

	return;
}

void fk_ShapeViewer::setElementMode(fk_ElementMode argMode)
{
	for(auto &model : _m->modelArray) {
		model->setElementMode(argMode);
	}

	return;
}

void fk_ShapeViewer::setElementMode(int argID, fk_ElementMode argMode)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setElementMode(argMode);
	return;
}

fk_ElementMode fk_ShapeViewer::getElementMode(void)
{
	if(_m->modelArray.empty() == true) return fk_ElementMode::NONE;
	return _m->modelArray[0]->getElementMode();
}

fk_ElementMode fk_ShapeViewer::getElementMode(int argID)
{
	fk_Model *model = GetModel(argID);
	if(model == nullptr) return fk_ElementMode::NONE;
	return model->getElementMode();
}

void fk_ShapeViewer::setShadingMode(fk_ShadingMode argMode)
{
	for(auto &model : _m->modelArray) {
		model->setShadingMode(argMode);
	}
	return;
}

void fk_ShapeViewer::setShadingMode(int argID, fk_ShadingMode argMode)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setShadingMode(argMode);
	return;
}

fk_ShadingMode fk_ShapeViewer::getShadingMode(void)
{
	if(_m->modelArray.empty() == true) return fk_ShadingMode::PHONG;
	return _m->modelArray[0]->getShadingMode();
}

fk_ShadingMode fk_ShapeViewer::getShadingMode(int argID)
{
	fk_Model *model = GetModel(argID);
	if(model == nullptr) return fk_ShadingMode::PHONG;
	return model->getShadingMode();
}	

void fk_ShapeViewer::setSmoothMode(bool argMode)
{
	for(auto &model : _m->modelArray) {
		model->setSmoothMode(argMode);
	}
	return;
}

void fk_ShapeViewer::setSmoothMode(int argID, bool argMode)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setSmoothMode(argMode);
	return;
}

bool fk_ShapeViewer::getSmoothMode(void)
{
	if(_m->modelArray.empty() == true) return false;
	return _m->modelArray[0]->getSmoothMode();
}

bool fk_ShapeViewer::getSmoothMode(int argID)
{
	fk_Model *model = GetModel(argID);
	if(model == nullptr) return false;
	return model->getSmoothMode();
}	

void fk_ShapeViewer::setBlendStatus(bool argMode)
{
	_m->scene.setBlendStatus(argMode);
	return;
}

bool fk_ShapeViewer::getBlendStatus(void)
{
	return _m->scene.getBlendStatus();
}
/*
void fk_ShapeViewer::setFrameMode(fk_FrameMode argMode)
{
	if(_m->viewWin == nullptr) return;
	_m->viewWin->setFrameMode(argMode);
	return;
}

void fk_ShapeViewer::setFrameInterval(int argInterval)
{
	if(_m->viewWin == nullptr) return;
	_m->viewWin->setFrameInterval(argInterval);
	return;
}
*/
void fk_ShapeViewer::setBGColor(fk_Color argColor)
{
	_m->scene.setBGColor(argColor);
	return;
}

void fk_ShapeViewer::setBGColor(float argR, float argG, float argB)
{
	_m->scene.setBGColor(argR, argG, argB);
	return;
}

fk_Color fk_ShapeViewer::getBGColor(void)
{
	return _m->scene.getBGColor();
}

void fk_ShapeViewer::setHead(double argVal)
{
	int div;
	double trueVal;

	div = static_cast<int>(argVal / (2.0*fk_Math::PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*fk_Math::PI);
	if(trueVal >= fk_Math::PI) {
		trueVal -= 2.0*fk_Math::PI;
	} else if(trueVal <= -fk_Math::PI) {
		trueVal += 2.0*fk_Math::PI;
	}

	Fl::focus(_m->gui->headSlider);
	_m->gui->headSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setPitch(double argVal)
{
	int div;
	double trueVal;

	div = static_cast<int>(argVal / (2.0*fk_Math::PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*fk_Math::PI);
	if(trueVal >= fk_Math::PI) {
		trueVal -= 2.0*fk_Math::PI;
	} else if(trueVal <= -fk_Math::PI) {
		trueVal += 2.0*fk_Math::PI;
	}

	Fl::focus(_m->gui->pitchSlider);
	_m->gui->pitchSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setBank(double argVal)
{
	int div;
	double trueVal;

	div = static_cast<int>(argVal / (2.0*fk_Math::PI));
	trueVal = argVal - static_cast<double>(div)*(2.0*fk_Math::PI);
	if(trueVal >= fk_Math::PI) {
		trueVal -= 2.0*fk_Math::PI;
	} else if(trueVal <= -fk_Math::PI) {
		trueVal += 2.0*fk_Math::PI;
	}

	Fl::focus(_m->gui->bankSlider);
	_m->gui->bankSlider->value(trueVal);
	return;
}

void fk_ShapeViewer::setScale(double argVal)
{
	Fl::focus(_m->gui->scaleRoller);
	if(argVal <= 0.0) return;
	_m->gui->scaleRoller->value(log10(argVal));
}

void fk_ShapeViewer::setAxisScale(double argVal)
{
	if(argVal <= 0.0) return;
	_m->gui->axisRoller->value(log10(argVal));
}

void fk_ShapeViewer::setAxisMode(bool argMode)
{
	Fl_Menu_Item *mA;

	mA = const_cast<Fl_Menu_Item *>(_m->gui->menuBar->menu() + 12);
	mA->flags = FL_MENU_TOGGLE;
	if(argMode == true) {
		_m->axisFlag = true;
		_m->scene.entryModel(&_m->axisModel);
		mA->flags |= FL_MENU_VALUE;
	} else {
		_m->axisFlag = false;
		_m->scene.removeModel(&_m->axisModel);
	}
	return;
}

void fk_ShapeViewer::setPosition(int argID, fk_Vector argPos)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->glMoveTo(argPos);
	return;
}

void fk_ShapeViewer::setPosition(int argID,
								 double argX, double argY, double argZ)
{
	fk_Vector pos(argX, argY, argZ);

	setPosition(argID, pos);
	return;
}

void fk_ShapeViewer::setMaterial(int argID, fk_Material argMat)
{
	_st trueID;

	if(_m->IDMap.find(argID) == _m->IDMap.end()) return;
	trueID = _st(_m->IDMap[argID]);

	*_m->polyMaterial[trueID] = argMat;
	SetAllMaterial();
	return;
}

void fk_ShapeViewer::setEdgeColor(int argID, fk_Color argCol)
{
	_st trueID;

	if(_m->IDMap.find(argID) == _m->IDMap.end()) return;
	trueID = _st(_m->IDMap[argID]);

	*_m->edgeColor[trueID] = argCol;
	SetAllMaterial();
	return;
}


void fk_ShapeViewer::setVertexColor(int argID, fk_Color argCol)
{
	_st trueID;

	if(_m->IDMap.find(argID) == _m->IDMap.end()) return;
	trueID = _st(_m->IDMap[argID]);

	*_m->vertexColor[trueID] = argCol;
	SetAllMaterial();
	return;
}

void fk_ShapeViewer::setAngle(int argID, fk_Angle argAngle)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->glAngle(argAngle);
	return;
}

void fk_ShapeViewer::setAngle(int argID,
							  double argH, double argP, double argB)
{
	fk_Angle angle(argH, argP, argB);

	setAngle(argID, angle);
	return;
}

void fk_ShapeViewer::setVec(int argID, fk_Vector argVec)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->glVec(argVec);
	return;
}

void fk_ShapeViewer::setVec(int argID, double argX, double argY, double argZ)
{
	fk_Vector vec(argX, argY, argZ);

	setVec(argID, vec);
	return;
}

void fk_ShapeViewer::setUpvec(int argID, fk_Vector argVec)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->glUpvec(argVec);
	return;
}

void fk_ShapeViewer::setUpvec(int argID, double argX, double argY, double argZ)
{
	fk_Vector vec(argX, argY, argZ);

	setUpvec(argID, vec);
	return;
}

void fk_ShapeViewer::setLineWidth(int argID, double argW)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setWidth(argW);
	return;
}

void fk_ShapeViewer::setPointSize(int argID, double argS)
{
	fk_Model *model = GetModel(argID);
	if(model != nullptr) model->setSize(argS);
	return;
}

int fk_ShapeViewer::getModelNum(void)
{
	return static_cast<int>(_m->modelArray.size());
}

fk_Shape * fk_ShapeViewer::getShape(int argID)
{
	if(_m->IDMap.find(argID) == _m->IDMap.end()) {
		return(nullptr);
	}

	return _m->modelArray[_st(_m->IDMap[argID])]->getShape();
}

fk_Draw fk_ShapeViewer::getDrawMode(void)
{
	if(_m->modelArray.empty() == true) {
		return fk_Draw::NONE;
	}

	return _m->modelArray[0]->getDrawMode();
}

fk_Draw fk_ShapeViewer::getDrawMode(int argID)
{
	fk_Model	*model = GetModel(argID);
	if(model == nullptr) return fk_Draw::NONE;
	return model->getDrawMode();
}
/*
fk_FrameMode fk_ShapeViewer::getFrameMode(void)
{
	if(_m->viewWin == nullptr) return fk_FrameMode::DEFAULT;
	return _m->viewWin->getFrameMode();
}

int fk_ShapeViewer::getFrameInterval(void)
{
	if(_m->viewWin == nullptr) return 0;
	return _m->viewWin->getFrameInterval();
}

int fk_ShapeViewer::getSkipFrame(void)
{
	if(_m->viewWin == nullptr) return 0;
	return _m->viewWin->getSkipFrame();
}
*/

void fk_ShapeViewer::setFPS(int argFPS)
{
	if(argFPS <= 0) {
		_m->fps = 0;
		_m->fps_admin.setFrameSkipMode(false);
	} else {
		_m->fps = argFPS;
		_m->fps_admin.setFrameSkipMode(true);
		_m->fps_admin.setFPS(argFPS);
	}
}

double fk_ShapeViewer::getHead(void)
{
	return _m->gui->headSlider->value();
}

double fk_ShapeViewer::getPitch(void)
{
	return _m->gui->pitchSlider->value();
}

double fk_ShapeViewer::getBank(void)
{
	return _m->gui->bankSlider->value();
}

double fk_ShapeViewer::getScale(void)
{
	return pow(10.0, _m->gui->scaleRoller->value());
}

double fk_ShapeViewer::getAxisScale(void)
{
	return pow(10.0, _m->gui->axisRoller->value());
}

bool fk_ShapeViewer::getAxisMode(void)
{
	return _m->axisFlag;
}

fk_Vector fk_ShapeViewer::getCenter(void)
{
	fk_Vector	dummy(0.0, 0.0, 0.0);

	if(_m->modelArray.empty() == true) {
		return dummy;
	}

	return -(_m->modelArray[0]->getInhPosition());
}

double fk_ShapeViewer::getLineWidth(int)
{
	return -1.0;
}

double fk_ShapeViewer::getPointSize(int argID)
{
	fk_Model	*model = GetModel(argID);
	if(model == nullptr) return -1.0;
	return model->getPointSize();
}

bool fk_ShapeViewer::shapeProcess(fk_Solid *)
{
	return true;
}

bool fk_ShapeViewer::snapImage(string argFName, fk_ImageType argFormat,
							   fk_SnapProcMode argMode)
{
	if(_m->viewWin == nullptr) return false;
	return _m->viewWin->snapImage(argFName, argFormat, argMode);
}

bool fk_ShapeViewer::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	if(_m->viewWin == nullptr) return false;
	return _m->viewWin->snapImage(argImage, argMode);
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
	_m->parentModel.SetTreeDelMode(false);
	for(_st i = 0; i < _m->modelArray.size(); i++) {
		_m->modelArray[i]->SetTreeDelMode(false);
	}
	_m->lightModel[0].SetTreeDelMode(false);
	//lightModel[1].SetTreeDelMode(false);
	_m->camera.SetTreeDelMode(false);
	_m->axisModel.SetTreeDelMode(false);

	return;
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
