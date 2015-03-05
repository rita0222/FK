// Base_CLI.h

#pragma once

#include <FK/Base.h>

namespace FK_CLI {
	using namespace System;

	public ref class FK {
	public:
		literal double PI = _FK_PI_DEFINE_;
		literal double EPS = _FK_EPS_DEFINE_;
	};

	public enum class fk_ObjectType {
		BASEOBJECT,
		MATRIXADMIN,
		MODEL,
		DISPLAYLINK,
		SCENE,
		SHAPE,
		POLYGON,
		LINE,
		POLYLINE,
		POINT,
		CIRCLE,
		SPHERE,
		BLOCK,
		CLOSEDLINE,
		PRISM,
		CAPSULE,
		CONE,
		INDEXFACESET,
		LIGHT,
		BEZCURVE,
		BSPLCURVE,
		BEZSURFACE,
		BSPLSURFACE,
		IMAGE,
		TEXCOORD,
		TEXTURE,
		RECTTEXTURE,
		TRITEXTURE,
		MESHTEXTURE,
		IFSTEXTURE,
		UNICHAR,
		UNISTR,
		TEXTIMAGE,
		COLOR,
		MATERIAL,
		PALETTE,
		PLANE,
		WINDOW,
		PICKDATA,
		PROJECTBASE,
		PERSPECTIVE,
		FRUSTUM,
		ORTHO,
		VERTEX,
		HALF,
		EDGE,
		LOOP,
		SOLID,
		SHAPEVIEWER,
		PARTICLE,
		PARTICLESET
	};

	public ref class fk_BaseObject {
	public:
		bool dFlg;
		::fk_BaseObject *pBase;

		fk_BaseObject(bool);
		~fk_BaseObject();
		!fk_BaseObject();
	};
}
