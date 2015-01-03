#include "ParticleSet_CLI.h"

namespace FK_CLI
{
	using namespace std;

	fk_Particle^ fk_ParticleSet::newParticle(void)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle();
		P->dFlg = false;
		genMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::newParticle(fk_Vector^ argPos)
	{
		if(!argPos) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle(*argPos->pVec);
		P->dFlg = false;
		genMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::newParticle(double argX, double argY, double argZ)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle(argX, argY, argZ);
		P->dFlg = false;
		genMethod(P);
		return P;
	}

	bool fk_ParticleSet::removeParticle(fk_Particle ^argP)
	{
		return GetP()->removeParticle(argP->GetP());
	}

	bool fk_ParticleSet::removeParticle(int argID)
	{
		return GetP()->removeParticle(argID);
	}

	unsigned int fk_ParticleSet::getCount(void)
	{
		return GetP()->getCount();
	}

	fk_Particle^ fk_ParticleSet::getParticle(int argID)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->getParticle(argID);
		P->dFlg = false;
		return P;
	}

	fk_Particle^ fk_ParticleSet::getNextParticle(fk_Particle^ argP)
	{
		::fk_Particle *pP = (!argP) ? NULL : argP->GetP();
		pP = GetP()->getNextParticle(pP);
		if(pP == NULL) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = pP;
		P->dFlg = false;
		return P;
	}

	unsigned int fk_ParticleSet::getParticleNum(void)
	{
		return GetP()->getParticleNum();
	}

	void fk_ParticleSet::setMaxSize(unsigned int argMax)
	{
		GetP()->setMaxSize(argMax);
	}

	unsigned int fk_ParticleSet::getMaxSize(void)
	{
		return GetP()->getMaxSize();
	}

	void fk_ParticleSet::setColorPalette(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setColorPalette(argID, *argCol->pCol);
	}

	void fk_ParticleSet::setColorPalette(int argID, float argR, float argG, float argB)
	{
		GetP()->setColorPalette(argID, argR, argG, argB);
	}

	void fk_ParticleSet::setColorPalette(int argID, double argR, double argG, double argB)
	{
		GetP()->setColorPalette(argID, argR, argG, argB);
	}

	void fk_ParticleSet::genMethod(fk_Particle^)
	{
		return;
	}

	void fk_ParticleSet::allMethod(void)
	{
		return;
	}

	void fk_ParticleSet::indivMethod(fk_Particle^)
	{
		return;
	}

	void fk_ParticleSet::setAllMode(bool argMode)
	{
		GetP()->setAllMode(argMode);
	}

	bool fk_ParticleSet::getAllMode(void)
	{
		return GetP()->getAllMode();
	}

	void fk_ParticleSet::setIndivMode(bool argMode)
	{
		GetP()->setIndivMode(argMode);
	}

	bool fk_ParticleSet::getIndivMode(void)
	{
		return GetP()->getIndivMode();
	}

	void fk_ParticleSet::handle(void)
	{
		if(getAllMode() == true) {
			allMethod();
		}

		if(getIndivMode() == true) {
			fk_Particle^ P;

			for(P = getNextParticle(nullptr); P != nullptr; P = getNextParticle(P)) {
				indivMethod(P);
			}
		}

		GetP()->handle();
	}

	fk_Shape^ fk_ParticleSet::getShape(void)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}
}
