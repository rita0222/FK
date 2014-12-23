// Scene_CLI.h

#pragma once

#include <FK/SimpleWindow.h>
#include "GuideObject_CLI.h"

using namespace std;
using namespace System;
using namespace msclr::interop;

namespace FK_CLI
{
	public ref class fk_AppWindow : fk_BaseObject
	{
	internal:
		::fk_AppWindow * GetP(void)
		{
			return reinterpret_cast<::fk_AppWindow *>(this->pBase);
		}

	public:
		fk_AppWindow::fk_AppWindow(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_AppWindow *p = new ::fk_AppWindow();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_AppWindow::fk_AppWindow() : fk_BaseObject(false)
		{
			::fk_AppWindow *p = new ::fk_AppWindow();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_AppWindow::~fk_AppWindow()
		{
			this->!fk_AppWindow();
		}

		fk_AppWindow::!fk_AppWindow()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void setWindowName(String^ argName)
		{
			GetP()->setWindowName(marshal_as<string>(argName));
		}

		void setSize(int argW, int argH)
		{
			GetP()->setSize(argW, argH);
		}

		void setInnerSize(int argX, int argY, int argW, int argH)
		{
			GetP()->setInnerSize(argX, argY, argW, argH);
		}

		void setBGColor(double argR, double argG, double argB)
		{
			GetP()->setBGColor(argR, argG, argB);
		}

		void setBGColor(fk_Color ^argC)
		{
			GetP()->setBGColor(*argC->GetP());
		}

		void open(void)
		{
			GetP()->open();
		}
		
		void close(void)
		{
			GetP()->close();
		}
		
		bool update(bool argForceFlg)
		{
			return GetP()->update(argForceFlg);
		}

		bool update(void)
		{
			return GetP()->update(false);
		}
		
		void setFPS(int argFPS)
		{
			GetP()->setFPS(argFPS);
		}

		void showGuide(void)
		{
			GetP()->showGuide(FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);
		}
		
		void showGuide(fk_GuideMode argMode)
		{
			GetP()->showGuide(int(argMode));
		}

		void hideGuide(void)
		{
			GetP()->hideGuide();
		}

		void setGuideAxisWidth(double argWidth)
		{
			GetP()->setGuideAxisWidth(argWidth);
		}

		void setGuideGridWidth(double argWidth)
		{
			GetP()->setGuideGridWidth(argWidth);
		}

		void setGuideScale(double argScale)
		{
			GetP()->setGuideScale(argScale);
		}

		void setGuideNum(int argNum)
		{
			GetP()->setGuideNum(argNum);
		}

		void setCameraPos(double argX, double argY, double argZ)
		{
			GetP()->setCameraPos(argX, argY, argZ);
		}

		void setCameraPos(fk_Vector ^argV)
		{
			GetP()->setCameraPos(*argV->pVec);
		}

		void setCameraFocus(double argX, double argY, double argZ)
		{
			GetP()->setCameraFocus(argX, argY, argZ);
		}

		void setCameraFocus(fk_Vector ^argV)
		{
			GetP()->setCameraFocus(*argV->pVec);
		}

		void setCameraModel(fk_Model ^argM)
		{
			GetP()->setCameraModel(argM->GetP());
		}
			
		fk_Model^ getCameraModel(void)
		{
			fk_Model^ M = gcnew fk_Model(false);
			M->pBase = reinterpret_cast<::fk_Model *>(GetP()->getCameraModel());
			M->dFlg = false;
			return M;
		}

		void setCameraDefault(void)
		{
			GetP()->setCameraDefault();
		}

		void setScene(fk_Scene^ argScene, bool argCL)
		{
			GetP()->setScene(argScene->GetP(), argCL);
		}
		
		void setScene(fk_Scene^ argScene)
		{
			GetP()->setScene(argScene->GetP(), false);
		}
			
		fk_Scene ^getScene(void)
		{
			fk_Scene ^S = gcnew fk_Scene(false);
			S->pBase = reinterpret_cast<::fk_BaseObject *>(GetP()->getScene());
			S->dFlg = false;
			return S;
		}
		
		void setSceneDefault(void)
		{
			GetP()->setSceneDefault();
		}
			
		void entry(fk_Model ^argModel)
		{
			GetP()->entry(argModel->GetP());
		}

		void entry(fk_Model ^argM, fk_GuideObject^ argGuide)
		{
			GetP()->entry(argM->GetP(), argGuide->GetP());
		}
			
		//void entry(fk_SpriteModel *model);
		//void entry(fk_SpriteModel &model);
		//void entry(fk_Performer *chara);
		//void entry(fk_Performer &chara);

		void remove(fk_Model ^argM)
		{
			GetP()->remove(argM->GetP());
		}

		void remove(fk_Model^ argM, fk_GuideObject^ argGuide)
		{
			GetP()->remove(argM->GetP(), argGuide->GetP());
		}

		//void remove(fk_SpriteModel *model);
		//void remove(fk_SpriteModel &model);
		//void remove(fk_Performer *chara);
		//void remove(fk_Performer &chara);

		void clearModel(bool argCL)
		{
			GetP()->clearModel(argCL);
		}

		void clearModel(void)
		{
			GetP()->clearModel(false);
		}

		bool getKeyStatus(char argK, fk_SwitchStatus argStatus)
		{
			return GetP()->getKeyStatus(argK, argStatus, false);
		}
		bool getKeyStatus(char argK, fk_SwitchStatus argStatus, bool argInFlg)
		{
			return GetP()->getKeyStatus(argK, argStatus, argInFlg);
		}
		/*

		bool			getSpecialKeyStatus(fk_SpecialKey keyCode,
											fk_SwitchStatus status, bool insideFlg = false);
	fk_SwitchStatus		getMouseStatus(fk_MouseButton buttonCode);
	bool				getMouseStatus(fk_MouseButton buttonCode,
									   fk_SwitchStatus status, bool insideFlg);
	fk_Vector			getMousePosition(void);
	void				setCursorState(bool visible, bool center);
	void setTrackBallMode(bool mode);
	bool isModelPicked(fk_Model *model, int pixel = 1,
					   int mouseX = -1, int mouseY = -1);
	bool isModelPicked(fk_Model &model, int pixel = 1,
					   int mouseX = -1, int mouseY = -1);
	void procMouseView(fk_Model *camera, double spinX,
					   double spinY, bool lockSW);
	void procMouseView(fk_Model &camera, double spinX,
					   double spinY, bool lockSW);
		*/
	};
}
