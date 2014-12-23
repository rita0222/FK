// Base_CLI.h

#pragma once

#include <FK/Base.h>
#include <msclr/marshal_cppstd.h>

using namespace std;
using namespace System;


namespace FK_CLI
{
	public ref class FK
	{
	public:
		literal double PI = _FK_PI_DEFINE_;
		literal double EPS = _FK_EPS_DEFINE_;
	};

	public enum class fk_ObjectType
	{
		FK_BASEOBJECT,
		FK_MATRIXADMIN,
		FK_MODEL,
		FK_DISPLAYLINK,
		FK_SCENE,
		FK_SHAPE,
		FK_POLYGON,
		FK_LINE,
		FK_POLYLINE,
		FK_POINT,
		FK_CIRCLE,
		FK_SPHERE,
		FK_BLOCK,
		FK_CLOSEDLINE,
		FK_PRISM,
		FK_CAPSULE,
		FK_CONE,
		FK_INDEXFACESET,
		FK_LIGHT,
		FK_BEZCURVE,
		FK_BSPLCURVE,
		FK_BEZSURFACE,
		FK_BSPLSURFACE,
		FK_IMAGE,
		FK_TEXCOORD,
		FK_TEXTURE,
		FK_RECTTEXTURE,
		FK_TRITEXTURE,
		FK_MESHTEXTURE,
		FK_IFSTEXTURE,
		FK_UNICHAR,
		FK_UNISTR,
		FK_TEXTIMAGE,
		FK_COLOR,
		FK_MATERIAL,
		FK_PALETTE,
		FK_PLANE,
		FK_WINDOW,
		FK_PICKDATA,
		FK_PROJECTBASE,
		FK_PERSPECTIVE,
		FK_FRUSTUM,
		FK_ORTHO,
		FK_VERTEX,
		FK_HALF,
		FK_EDGE,
		FK_LOOP,
		FK_SOLID,
		FK_SHAPEVIEWER,
		FK_PARTICLE,
		FK_PARTICLESET
	};

	public ref class fk_BaseObject
	{
	public:
		bool dFlg;
		::fk_BaseObject *pBase;

		fk_BaseObject::fk_BaseObject(bool argNewFlg) : dFlg(true)
		{
			if(argNewFlg == true) this->pBase = new ::fk_BaseObject();
		}

		fk_BaseObject::~fk_BaseObject()
		{
			this->!fk_BaseObject();
		}

		fk_BaseObject::!fk_BaseObject()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		FK_CLI::fk_ObjectType getObjectType(void)
		{
			FK_CLI::fk_ObjectType type;

			switch(this->pBase->getObjectType()) {
			  case ::fk_ObjectType::FK_BASEOBJECT:
				type = FK_CLI::fk_ObjectType::FK_BASEOBJECT;
				break;

			  case ::fk_ObjectType::FK_MATRIXADMIN:
				type = FK_CLI::fk_ObjectType::FK_MATRIXADMIN;
				break;
				
			  case ::fk_ObjectType::FK_MODEL:
				type = FK_CLI::fk_ObjectType::FK_MODEL;
				break;
				
			  case ::fk_ObjectType::FK_DISPLAYLINK:
				type = FK_CLI::fk_ObjectType::FK_DISPLAYLINK;
				break;
				
			  case ::fk_ObjectType::FK_SCENE:
				type = FK_CLI::fk_ObjectType::FK_SCENE;
				break;
				
			  case ::fk_ObjectType::FK_SHAPE:
				type = FK_CLI::fk_ObjectType::FK_SHAPE;
				break;
				
			  case ::fk_ObjectType::FK_POLYGON:
				type = FK_CLI::fk_ObjectType::FK_POLYGON;
				break;
				
			  case ::fk_ObjectType::FK_LINE:
				type = FK_CLI::fk_ObjectType::FK_LINE;
				break;
				
			  case ::fk_ObjectType::FK_POLYLINE:
				type = FK_CLI::fk_ObjectType::FK_POLYLINE;
				break;
				
			  case ::fk_ObjectType::FK_POINT:
				type = FK_CLI::fk_ObjectType::FK_POINT;
				break;
				
			  case ::fk_ObjectType::FK_CIRCLE:
				type = FK_CLI::fk_ObjectType::FK_CIRCLE;
				break;
				
			  case ::fk_ObjectType::FK_SPHERE:
				type = FK_CLI::fk_ObjectType::FK_SPHERE;
				break;
				
			  case ::fk_ObjectType::FK_BLOCK:
				type = FK_CLI::fk_ObjectType::FK_BLOCK;
				break;
				
			  case ::fk_ObjectType::FK_CLOSEDLINE:
				type = FK_CLI::fk_ObjectType::FK_CLOSEDLINE;
				break;
				
			  case ::fk_ObjectType::FK_PRISM:
				type = FK_CLI::fk_ObjectType::FK_PRISM;
				break;
				
			  case ::fk_ObjectType::FK_CAPSULE:
				type = FK_CLI::fk_ObjectType::FK_CAPSULE;
				break;
				
			  case ::fk_ObjectType::FK_CONE:
				type = FK_CLI::fk_ObjectType::FK_CONE;
				break;
				
			  case ::fk_ObjectType::FK_INDEXFACESET:
				type = FK_CLI::fk_ObjectType::FK_INDEXFACESET;
				break;
				
			  case ::fk_ObjectType::FK_LIGHT:
				type = FK_CLI::fk_ObjectType::FK_LIGHT;
				break;
				
			  case ::fk_ObjectType::FK_BEZCURVE:
				type = FK_CLI::fk_ObjectType::FK_BEZCURVE;
				break;
				
			  case ::fk_ObjectType::FK_BSPLCURVE:
				type = FK_CLI::fk_ObjectType::FK_BSPLCURVE;
				break;
				
			  case ::fk_ObjectType::FK_BEZSURFACE:
				type = FK_CLI::fk_ObjectType::FK_BEZSURFACE;
				break;
				
			  case ::fk_ObjectType::FK_BSPLSURFACE:
				type = FK_CLI::fk_ObjectType::FK_BSPLSURFACE;
				break;
				
			  case ::fk_ObjectType::FK_IMAGE:
				type = FK_CLI::fk_ObjectType::FK_IMAGE;
				break;
				
			  case ::fk_ObjectType::FK_TEXCOORD:
				type = FK_CLI::fk_ObjectType::FK_TEXCOORD;
				break;
				
			  case ::fk_ObjectType::FK_TEXTURE:
				type = FK_CLI::fk_ObjectType::FK_TEXTURE;
				break;
				
			  case ::fk_ObjectType::FK_RECTTEXTURE:
				type = FK_CLI::fk_ObjectType::FK_RECTTEXTURE;
				break;
				
			  case ::fk_ObjectType::FK_TRITEXTURE:
				type = FK_CLI::fk_ObjectType::FK_TRITEXTURE;
				break;
				
			  case ::fk_ObjectType::FK_MESHTEXTURE:
				type = FK_CLI::fk_ObjectType::FK_MESHTEXTURE;
				break;
				
			  case ::fk_ObjectType::FK_IFSTEXTURE:
				type = FK_CLI::fk_ObjectType::FK_IFSTEXTURE;
				break;
				
			  case ::fk_ObjectType::FK_UNICHAR:
				type = FK_CLI::fk_ObjectType::FK_UNICHAR;
				break;
				
			  case ::fk_ObjectType::FK_UNISTR:
				type = FK_CLI::fk_ObjectType::FK_UNISTR;
				break;
				
			  case ::fk_ObjectType::FK_TEXTIMAGE:
				type = FK_CLI::fk_ObjectType::FK_TEXTIMAGE;
				break;
				
			  case ::fk_ObjectType::FK_COLOR:
				type = FK_CLI::fk_ObjectType::FK_COLOR;
				break;
				
			  case ::fk_ObjectType::FK_MATERIAL:
				type = FK_CLI::fk_ObjectType::FK_MATERIAL;
				break;
				
			  case ::fk_ObjectType::FK_PALETTE:
				type = FK_CLI::fk_ObjectType::FK_PALETTE;
				break;
				
			  case ::fk_ObjectType::FK_PLANE:
				type = FK_CLI::fk_ObjectType::FK_PLANE;
				break;
				
			  case ::fk_ObjectType::FK_WINDOW:
				type = FK_CLI::fk_ObjectType::FK_WINDOW;
				break;
				
			  case ::fk_ObjectType::FK_PICKDATA:
				type = FK_CLI::fk_ObjectType::FK_PICKDATA;
				break;
				
			  case ::fk_ObjectType::FK_PROJECTBASE:
				type = FK_CLI::fk_ObjectType::FK_PROJECTBASE;
				break;
				
			  case ::fk_ObjectType::FK_PERSPECTIVE:
				type = FK_CLI::fk_ObjectType::FK_PERSPECTIVE;
				break;
				
			  case ::fk_ObjectType::FK_FRUSTUM:
				type = FK_CLI::fk_ObjectType::FK_FRUSTUM;
				break;
				
			  case ::fk_ObjectType::FK_ORTHO:
				type = FK_CLI::fk_ObjectType::FK_ORTHO;
				break;
				
			  case ::fk_ObjectType::FK_VERTEX:
				type = FK_CLI::fk_ObjectType::FK_VERTEX;
				break;
				
			  case ::fk_ObjectType::FK_HALF:
				type = FK_CLI::fk_ObjectType::FK_HALF;
				break;
				
			  case ::fk_ObjectType::FK_EDGE:
				type = FK_CLI::fk_ObjectType::FK_EDGE;
				break;
				
			  case ::fk_ObjectType::FK_LOOP:
				type = FK_CLI::fk_ObjectType::FK_LOOP;
				break;
				
			  case ::fk_ObjectType::FK_SOLID:
				type = FK_CLI::fk_ObjectType::FK_SOLID;
				break;
				
			  case ::fk_ObjectType::FK_SHAPEVIEWER:
				type = FK_CLI::fk_ObjectType::FK_SHAPEVIEWER;
				break;
				
			  case ::fk_ObjectType::FK_PARTICLE:
				type = FK_CLI::fk_ObjectType::FK_PARTICLE;
				break;
				
			  case ::fk_ObjectType::FK_PARTICLESET:
				type = FK_CLI::fk_ObjectType::FK_PARTICLESET;
				break;
				
			  default:
				break;
			}
			return type;
		}
	};
}
