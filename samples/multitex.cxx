﻿#define FK_DEF_SIZETYPE
#include <FK/FK.h>
#include <memory>

using namespace std;
using namespace FK;
using namespace FK::Material;

constexpr int WIN_W = 800; // ウィンドウ横幅
constexpr int WIN_H = 800; // ウィンドウ縦幅
constexpr double SP_X = -(double(WIN_W/2) - 10.0);
constexpr double SP_Y = double(WIN_H/2) - 10.0;

// 通常モデルのシェーダー設定
void ShaderSetup(fk_ShaderBinder *argBinder, fk_Model *argModel,
				 string argVP, string argFP)
{
	argModel->setSmoothMode(true);
	argBinder->getProgram()->loadVertexShader(argVP);
	argBinder->getProgram()->loadFragmentShader(argFP);
	if(argBinder->getProgram()->validate()) {
		argBinder->bindModel(argModel);
	} else {
		fk_Window::printf("Shader Error");
		fk_Window::putString(argBinder->getProgram()->getLastError());
	} 
}

void ModelSetup(fk_Model *argModel, fk_Material &argMat, fk_Vector argPos)
{
	argModel->setSmoothMode(true);
	argModel->setMaterial(argMat);
	argModel->glMoveTo(argPos);
}

int fID(int argI, int argJ, int divW)
{
	return (2 * (argI + divW * argJ));
}

int vID(int argI, int argJ, int divW)
{
	return (argI + (divW + 1) * argJ);
}

void CylMake(fk_IFSTexture *argIFS)
{
	int divW = 50;
	int divH = 20;
	double radius = 10.0;
	double height = 30.0;

	vector<int>	ifset(_st(divW) * _st(divH) * 6);
	vector<fk_Vector> pos((_st(divW) + 1) * (_st(divH) + 1));

	for(int j = 0; j <= divH; j++) {
		double h1 = height * double(j)/double(divH);

		for(int i = 0; i <= divW; i++) {
			int id = vID(i, j, divW);
			double theta = fk_Math::PI * 2.0 * double(i)/double(divW);
			double sin1 = sin(theta);
			double cos1 = cos(theta);
			pos[_st(id)] = fk_Vector(sin1 * radius, h1, cos1 * radius);
		}
	}

	for(int j = 0; j < divH; j++) {
		for(int i = 0; i < divW; i++) {
			int id_0 = vID(i, j, divW);
			int id_1 = vID(i+1, j, divW);
			int id_2 = vID(i+1, j+1, divW);
			int id_3 = vID(i, j+1, divW);
			_st faceOffset = _st(fID(i, j, divW)) * 3;

			ifset[faceOffset + 0] = id_0;
			ifset[faceOffset + 1] = id_1;
			ifset[faceOffset + 2] = id_3;

			ifset[faceOffset + 3] = id_2;
			ifset[faceOffset + 4] = id_3;
			ifset[faceOffset + 5] = id_1;
		}
	}

	argIFS->getIFS()->makeIFSet(int(ifset.size())/3, 3, ifset.data(),
								int(pos.size()), pos.data());

	vector<fk_TexCoord> coord(4);
	for(int j = 0; j <= divH; j++) { // y方向
		for(int i = 0; i <= divW; i++) { // xz方向
			int id = fID(i, j, divW);
			double x1 = double(i)/double(divW);
			double x2 = (double(i)+1.0)/double(divW);
			double y1 = double(j)/double(divH);
			double y2 = (double(j)+1.0)/double(divH);

			coord[0].set(x1, y1);
			coord[1].set(x2, y1);
			coord[2].set(x2, y2);
			coord[3].set(x1, y2);

			argIFS->setTextureCoord(id, 0, coord[0]);
			argIFS->setTextureCoord(id, 1, coord[1]);
			argIFS->setTextureCoord(id, 2, coord[3]);
			argIFS->setTextureCoord(id+1, 0, coord[2]);
			argIFS->setTextureCoord(id+1, 1, coord[3]);
			argIFS->setTextureCoord(id+1, 2, coord[1]);
		}
	}
}

fk_TexCoord getScale(fk_Image *argImage, fk_TexCoord *argScale)
{
	auto spriteSizeDim = argImage->getImageSize();
	auto spriteBufDim = argImage->getBufferSize();
	fk_TexCoord sprScale(double(spriteSizeDim->w)/double(spriteBufDim->w),
						 double(spriteSizeDim->h)/double(spriteBufDim->h));
	fk_TexCoord prodScale(double(argScale->x) * double(sprScale.x),
						  double(argScale->y) * double(sprScale.y));
	return prodScale;
}
	
int main(int, char **)
{
	fk_System::setcwd();

	unique_ptr<fk_AppWindow> window(new fk_AppWindow());
	unique_ptr<fk_IFSTexture> ifsShape(new fk_IFSTexture());
	unique_ptr<fk_Model> ifsModel(new fk_Model());
	unique_ptr<fk_Model> lightModel(new fk_Model());
	unique_ptr<fk_Model> camera(new fk_Model());
	unique_ptr<fk_SpriteModel> sprite(new fk_SpriteModel());
	unique_ptr<fk_ShaderBinder> binder(new fk_ShaderBinder());

	window->setSize(WIN_W, WIN_H);
	fk_InitMaterial();
	Error::SetMode(Error::Mode::BROWSER_INTERACTIVE);

	if(ifsShape->readPNG("data/image/poe.png") == false) {
		fl_alert("tex load err");
	}

	ifsShape->setTexRendMode(fk_TexRendMode::SMOOTH);
	CylMake(ifsShape.get());

	ifsModel->setShape(ifsShape.get());
	ModelSetup(ifsModel.get(), White, fk_Vector(0.0, 0.0, 0.0));

	if(sprite->initFont("data/font/rm1b.ttf") == false) {
		fl_alert("Font Init Error");
	}
	sprite->setPositionLT(SP_X, SP_Y);
	fk_Image *image = sprite->getImage();
	unique_ptr<fk_RectTexture> texture(new fk_RectTexture(image));

	window->setBGColor(0.5f, 0.5f, 0.5f);
	window->setCameraModel(camera.get());
	window->entry(ifsModel.get());
	window->entry(sprite.get());
	window->setTrackBallMode(true);
	window->showGuide();

	// 視点の位置と姿勢を設定
	camera->glMoveTo(0.0, 0.0, 100.0);
	camera->glFocus(0.0, 0.0, 0.0);
	camera->glUpvec(0.0, 1.0, 0.0);

	// ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
	window->open();
	Fl::check();

	ShaderSetup(binder.get(), ifsModel.get(), "data/shader/multi_vp.glsl", "data/shader/multi_fp.glsl");

	auto parameter = binder->getParameter();
		
	// シェーダー内で fk_TexID[1] で参照できるように設定
	parameter->attachTexture(1, texture.get());

	auto texSizeDim = ifsShape->getImageSize();
	auto texBufDim = ifsShape->getBufferSize();
	fk_TexCoord orgScale(double(texBufDim->w)/double(texSizeDim->w),
						 double(texBufDim->h)/double(texSizeDim->h));

	fk_TexCoord scaleCoord = getScale(image, &orgScale);
	vector<float>	scale = {scaleCoord.x, scaleCoord.y};
	parameter->setRegister("scale", &scale);
	for(int count = 0; window->update() == true; count++) {
		lightModel->glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, 0.01);
		sprite->drawText(to_string(count), true);
		sprite->setPositionLT(SP_X, SP_Y);

		texture->setImage(image);
		scaleCoord = getScale(image, &orgScale);
		scale[0] = scaleCoord.x * 5.0f;
		scale[1] = scaleCoord.y * 5.0f;
		parameter->setRegister("scale", &scale);
	}

	return 0;
}
