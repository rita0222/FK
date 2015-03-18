#include "ParticleSet_CLI.h"

namespace FK_CLI
{
	using namespace std;

	::fk_ParticleSet * fk_ParticleSet::GetP(void)
	{
		return (::fk_ParticleSet *)(pBase);
	}

	fk_ParticleSet::fk_ParticleSet() : fk_BaseObject(false)
	{
		pBase = new ::fk_ParticleSet();
	}

	fk_ParticleSet::fk_ParticleSet(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_ParticleSet();
		}
	}

	fk_ParticleSet::~fk_ParticleSet()
	{
		this->!fk_ParticleSet();
	}

	fk_ParticleSet::!fk_ParticleSet()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Shape^ fk_ParticleSet::Shape::get(void)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}

	unsigned int fk_ParticleSet::Count::get(void)
	{
		return GetP()->getCount();
	}

	unsigned int fk_ParticleSet::ParticleNum::get(void)
	{
		return GetP()->getParticleNum();
	}

	void fk_ParticleSet::MaxSize::set(unsigned int argMax)
	{
		GetP()->setMaxSize(argMax);
	}

	unsigned int fk_ParticleSet::MaxSize::get(void)
	{
		return GetP()->getMaxSize();
	}

	void fk_ParticleSet::AllMode::set(bool argMode)
	{
		GetP()->setAllMode(argMode);
	}

	bool fk_ParticleSet::AllMode::get(void)
	{
		return GetP()->getAllMode();
	}

	void fk_ParticleSet::IndivMode::set(bool argMode)
	{
		GetP()->setIndivMode(argMode);
	}

	bool fk_ParticleSet::IndivMode::get(void)
	{
		return GetP()->getIndivMode();
	}

	fk_Particle^ fk_ParticleSet::NewParticle(void)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle();
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::NewParticle(fk_Vector^ argPos)
	{
		if(!argPos) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle(::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::NewParticle(double argX, double argY, double argZ)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle(argX, argY, argZ);
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	bool fk_ParticleSet::RemoveParticle(fk_Particle ^argP)
	{
		return GetP()->removeParticle(argP->GetP());
	}

	bool fk_ParticleSet::RemoveParticle(int argID)
	{
		return GetP()->removeParticle(argID);
	}

	fk_Particle^ fk_ParticleSet::GetParticle(int argID)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->getParticle(argID);
		P->dFlg = false;
		return P;
	}

	fk_Particle^ fk_ParticleSet::GetNextParticle(fk_Particle^ argP)
	{
		::fk_Particle *pP = (!argP) ? nullptr : argP->GetP();
		pP = GetP()->getNextParticle(pP);
		if(pP == nullptr) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = pP;
		P->dFlg = false;
		return P;
	}

	void fk_ParticleSet::SetColorPalette(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setColorPalette(argID, *argCol->pCol);
	}

	void fk_ParticleSet::SetColorPalette(int argID, float argR, float argG, float argB)
	{
		GetP()->setColorPalette(argID, argR, argG, argB);
	}

	void fk_ParticleSet::SetColorPalette(int argID, double argR, double argG, double argB)
	{
		GetP()->setColorPalette(argID, argR, argG, argB);
	}

	void fk_ParticleSet::Handle(void)
	{
		if(AllMode == true) {
			AllMethod();
		}

		if(IndivMode == true) {
			fk_Particle^ P;

			for(P = GetNextParticle(nullptr); P != nullptr; P = GetNextParticle(P)) {
				IndivMethod(P);
			}
		}

		GetP()->handle();
	}

	void fk_ParticleSet::GenMethod(fk_Particle^)
	{
		return;
	}

	void fk_ParticleSet::AllMethod(void)
	{
		return;
	}

	void fk_ParticleSet::IndivMethod(fk_Particle^)
	{
		return;
	}

}
