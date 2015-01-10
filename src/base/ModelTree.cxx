/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/Model.h>
#include <FK/Error.H>
#include <FK/Tree.h>
#include <sstream>

#include <msclr/marshal_cppstd.h>

using namespace std;
using namespace msclr::interop;

unique_ptr<fk_Tree> fk_Model::_modelTree(new fk_Tree("modelTree"));

class fk_ModelTreeObject : public fk_TreeBaseObject {
private:
	fk_Model		*model;

public:
	fk_ModelTreeObject(void);
	~fk_ModelTreeObject();

	void			SetModel(fk_Model *);
	fk_Model *		GetModel(void);
};

fk_ModelTreeObject::fk_ModelTreeObject(void)
{
	model = NULL;
	return;
}

fk_ModelTreeObject::~fk_ModelTreeObject()
{
	return;
}

void fk_ModelTreeObject::SetModel(fk_Model *argModel)
{
	model = argModel;
	return;
}

fk_TreeData * fk_Model::GetTreeData(fk_Model *argModel)
{
	fk_TreeData				*curData;
	fk_ModelTreeObject		*object;

	for(curData = _modelTree->foreachData(NULL);
		curData != NULL; curData = _modelTree->foreachData(curData)) {
		object = static_cast<fk_ModelTreeObject *>(curData->getObject());
		if(object == NULL) continue;
		if(object->GetModel() == argModel) return curData;
	}
	return NULL;
}

fk_Model * fk_ModelTreeObject::GetModel(void)
{
	return model;
}

void fk_Model::SetTreeDelMode(bool argMode)
{
	treeDelMode = argMode;
	return;
}

void fk_Model::EntryTree(void)
{
	fk_ModelTreeObject		*thisObject;
	stringstream			ss;
	
	if(treeFlag == true) return;

	treeFlag = true;

	thisObject = new fk_ModelTreeObject();
	ss << "m" << _modelID;
	treeData = _modelTree->addNewChild(_modelTree->getRoot(), ss.str());
	thisObject->SetModel(this);
	treeData->setObject(thisObject);
	parent = NULL;

	return;
}

void fk_Model::DeleteTree(void)
{
	if(treeFlag == false) return;

	if(treeDelMode == true) {
		deleteChildren();
		deleteParent();
		if(treeData == NULL) return;
		_modelTree->deleteBranch(treeData);
	}
	treeData = NULL;
	return;
}
	

bool fk_Model::setParent(fk_Model *argModel, bool argBindFlg)
{
	fk_TreeData		*parentData;
	fk_HVector		tmpPos, tmpVec, tmpUpVec;
	fk_Matrix	   	tmpMat;

	EntryTree();

	if(argModel == NULL) {
		deleteParent(argBindFlg);
		return true;
	}

	if(parent != NULL) deleteParent(argBindFlg);

	argModel->EntryTree();

	if((parentData = argModel->treeData) == NULL) return false;
	if(treeData == NULL) return false;
	if(_modelTree->moveBranch(parentData, treeData) == false) return false;

	parent = argModel;

	if(argBindFlg == true) {
		tmpPos.set(0.0, 0.0, 0.0, 1.0);
		tmpVec.set(0.0, 0.0, -1.0, 0.0);
		tmpUpVec.set(0.0, 1.0, 0.0, 0.0);
		tmpMat = parent->getInhInvMatrix() * getMatrix();
		glMoveTo(tmpMat * tmpPos);
		glVec(tmpMat * tmpVec);
		glUpvec(tmpMat * tmpUpVec);
	}

	return true;
}

void fk_Model::deleteParent(bool argBindFlg)
{
	fk_HVector		tmpPos, tmpVec, tmpUpVec;
	fk_Matrix		tmpMat;

	EntryTree();

	if(parent == NULL) return;
	if(treeFlag == false) return;
	if(treeData == NULL) return;

	_modelTree->moveBranch(_modelTree->getRoot(), treeData);

	if(argBindFlg == true) {
		tmpPos.set(0.0, 0.0, 0.0, 1.0);
		tmpVec.set(0.0, 0.0, -1.0, 0.0);
		tmpUpVec.set(0.0, 1.0, 0.0, 0.0);
		tmpMat = getInhMatrix();
		glMoveTo(tmpMat * tmpPos);
		glVec(tmpMat * tmpVec);
		glUpvec(tmpMat * tmpUpVec);
	}

	parent = NULL;
	return;
}

fk_Model * fk_Model::getParent(void) const
{
	return parent;
}

bool fk_Model::entryChild(fk_Model *argModel, bool argBindFlg)
{
	if(argModel == NULL) return true;
	return (argModel->setParent(this, argBindFlg));
}

bool fk_Model::deleteChild(fk_Model *argModel, bool argBindFlg)
{
	fk_TreeData				*childData;
	fk_ModelTreeObject		*modelObject;
	fk_Model				*childModel;

	if(argModel == NULL) return false;
	if(argModel->parent != this) return false;

	if((childData = argModel->treeData) == NULL) return false;

	modelObject = static_cast<fk_ModelTreeObject *>(childData->getObject());
	if(modelObject == NULL) return false;

	childModel = modelObject->GetModel();
	if(childModel == NULL) return false;

	childModel->deleteParent(argBindFlg);

	return true;
}

void fk_Model::deleteChildren(bool argBindFlg)
{
	fk_TreeData				*curChild;
	vector<fk_TreeData *>	childrenArray;
	fk_ModelTreeObject		*modelObject;
	fk_Model				*childModel;
	unsigned int			i;

	if(treeFlag == false) return;
	if(treeData == NULL) return;

	for(curChild = treeData->getChild(NULL);
		curChild != NULL; curChild = treeData->getChild(curChild)) {
		childrenArray.push_back(curChild);
	}

	for(i = 0; i < childrenArray.size(); i++) {
		modelObject = static_cast<fk_ModelTreeObject *>(childrenArray[i]->getObject());
		if(modelObject == NULL) return;

		childModel = modelObject->GetModel();
		if(childModel == NULL) return;

		childModel->deleteParent(argBindFlg);
	}

	return;
}

fk_Model * fk_Model::foreachChild(fk_Model *argModel)
{
	fk_TreeData				*argChild, *nextChild;
	fk_ModelTreeObject		*childObject;

	if(treeFlag == false) return NULL;
	if(treeData == NULL) return NULL;

	if(argModel == NULL) {
		nextChild = treeData->getChild(NULL);
	} else {
		if((argChild = argModel->treeData) == NULL) return NULL;
		nextChild = argChild->getNext();
	}

	if(nextChild == NULL) return NULL;
	childObject = static_cast<fk_ModelTreeObject *>(nextChild->getObject());
	if(childObject == NULL) return NULL;

	return childObject->GetModel();
}


void fk_Model::TreePrint(void)
{
	_modelTree->Print();
	return;
}
