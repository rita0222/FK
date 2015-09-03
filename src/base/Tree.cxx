/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
#include <FK/Tree.h>
#include <FK/Error.H>
#include <algorithm>
#include <sstream>

using namespace std;

typedef fk_TList::iterator	list_ite;

fk_TreeData::fk_TreeData(fk_Tree *argTree,
						 const string argName, fk_TreeData *argParent)
{
	object = nullptr;
	base = argTree;
	name = argName;
	parent = argParent;
	deleteFlg = false;

	if(parent == nullptr) {
		depth = 0;
		maxDepth = 0;
	} else {
		depth = parent->getDepth() + 1;
		maxDepth = depth;
	}

	children.clear();
	return;
}

fk_TreeData::~fk_TreeData()
{
	if(deleteFlg == true) delete object;

	return;
}

int fk_TreeData::getDepth(void)
{
	return depth;
}

int fk_TreeData::getMaxDepth(void)
{
	return maxDepth;
}

fk_TreeData * fk_TreeData::getChild(fk_TreeData *argPrev)
{
	list_ite		ite;

	if(argPrev == nullptr) {
		if(children.empty() == true) return nullptr;
		return children.front();
	}

	ite = find(children.begin(), children.end(), argPrev);
	if(ite == children.end()) return nullptr;
	++ite;
	if(ite == children.end()) return nullptr;
	return (*ite);
}

fk_TreeData * fk_TreeData::getParent(void)
{
	return parent;
}

fk_TreeData * fk_TreeData::getNext(void)
{
	list_ite		ite;

	if(parent == nullptr) return nullptr;

	for(ite = parent->children.begin();
		ite != parent->children.end(); ++ite) {
		if((*ite) == this) {
			++ite;
			if(ite == parent->children.end()) return nullptr;
			return (*ite);
		}
	}
	return nullptr;
}

fk_TreeData * fk_TreeData::getPrev(void)
{
	list_ite		ite;

	if(parent == nullptr) return nullptr;

	ite = find(parent->children.begin(), parent->children.end(), this);
	if(ite == parent->children.end() ||
	   ite == parent->children.begin()) return nullptr;
	--ite;
	return (*ite);
}

int fk_TreeData::getOrder(void)
{
	list_ite		ite;
	int				order = 0;

	if(parent == nullptr) return 0;

	for(ite = parent->children.begin();
		ite != parent->children.end(); ++ite) {
		if((*ite) == this) return order;
		order++;
	}
	return -1;
}

int fk_TreeData::getChildrenSize(void)
{
	return int(children.size());
}

void fk_TreeData::_addChild(fk_TreeData *argChild)
{
	children.push_back(argChild);
	_calcMaxDepth();
	return;
}

void fk_TreeData::_clearChild(fk_TreeData *argChild)
{
	list_ite		ite;

	ite = find(children.begin(), children.end(), argChild);
	if(ite == children.end()) return;
	children.erase(ite);
	return;
}

void fk_TreeData::Print(void)
{
	list_ite		ite;
	stringstream	ss;
	

	for(int i = 0; i < depth; i++) {
		ss << "\t";
	}

	ss << "(" << name << ", " << maxDepth << ")";
	fk_PutError(ss.str());

	for(ite = children.begin(); ite != children.end(); ++ite) {
		(*ite)->Print();
	}
	return;
}

void fk_TreeData::_calcMaxDepth(void)
{
	list_ite		ite;
	int				tmpDepth;

	maxDepth = depth;
	for(ite = children.begin(); ite != children.end(); ++ite) {
		tmpDepth = (*ite)->getMaxDepth();
		if(tmpDepth > maxDepth) maxDepth = tmpDepth;
	}

	if(parent != nullptr) parent->_calcMaxDepth();
	return;
}

string fk_TreeData::getName(void)
{
	return name;
}

void fk_TreeData::setObject(fk_TreeBaseObject *argObject, bool argDelFlg)
{
	object = argObject;
	deleteFlg = argDelFlg;
	return;
}

fk_TreeBaseObject * fk_TreeData::getObject(void)
{
	return object;
}

fk_Tree::fk_Tree(const string argName)
{
	clear(argName);
	return;
}

fk_Tree::~fk_Tree(void)
{
	_clear();
	return;
}

fk_TreeData * fk_Tree::makeNewData(fk_Tree *argTree, string argName,
								   fk_TreeData *argParent)
{
	return(new fk_TreeData(argTree, argName, argParent));
}

void fk_Tree::_makeRoot(const string argName)
{
	//if(this == nullptr) return;
	_root = makeNewData(this, argName, nullptr);
	_treeData.clear();
	if(_root != nullptr) {
		_treeData.push_back(_root);
	}
	return;
}


fk_TreeData * fk_Tree::getRoot(void)
{
	return _root;
}

void fk_Tree::_clear(void)
{
	list_ite		ite;

	for(ite = _treeData.begin(); ite != _treeData.end(); ++ite) {
		delete *ite;
	}
	_treeData.clear();
	return;
}

void fk_Tree::_clearData(fk_TreeData *argData)
{
	list_ite		ite;

	ite = find(_treeData.begin(), _treeData.end(), argData);
	if(ite != _treeData.end()) {
		delete (*ite);
		_treeData.erase(ite);
	}
	return;
}

void fk_Tree::clear(const string argName)
{
	_clear();
	_makeRoot(argName);
	return;
}

bool fk_Tree::isArive(fk_TreeData *argData)
{
	if(argData == nullptr) return false;
	if(argData->base != this) return false;

	if(find(_treeData.begin(), _treeData.end(), argData) != _treeData.end()) {
		return true;
	}
	return false;
}

fk_TreeData * fk_Tree::addNewChild(fk_TreeData *argData, const string argName)
{
	fk_TreeData		*newData;

	if(isArive(argData) == false) return nullptr;

	newData = makeNewData(this, argName, argData);
	_treeData.push_back(newData);
	argData->_addChild(newData);

	return newData;
}

bool fk_Tree::deleteBranch(fk_TreeData *argData)
{
	fk_TreeData		*parent;

	if(isArive(argData) == false) return false;
	if(argData == _root) return false;

	parent = argData->parent;

	clearChildren(argData);

	parent->_clearChild(argData);
	_clearData(argData);
	parent->_calcMaxDepth();

	return true;
}

bool fk_Tree::clearChildren(fk_TreeData *argData)
{
	fk_TreeData		*childData;

	if(isArive(argData) == false) return false;

	for(childData = argData->getChild(nullptr);
		childData != nullptr;
		childData = argData->getChild(childData)) {
		deleteBranch(childData);
	}

	return true;
}

fk_TreeData * fk_Tree::cloneOneData(fk_TreeData *argParent,
									fk_TreeData *argData)
{
	fk_TreeData		*newChild;

	if(isArive(argParent) == false) return nullptr;

	newChild = addNewChild(argParent, argData->name);
	newChild->object = argData->object;
	return newChild;
}

fk_TreeData * fk_Tree::_simpleClone(fk_TreeData *argParentData,
									fk_TreeData *argFromData)
{
	list_ite		ite;
	fk_TreeData		*newData;

	newData = makeNewData(this, argFromData->name, argParentData);
	_treeData.push_back(newData);	// fix!(by rita)
	for(ite = argFromData->children.begin();
		ite != argFromData->children.end();
		++ite) {
		newData->_addChild(_simpleClone(newData, (*ite)));
	}
	newData->object = argFromData->object;
	return newData;
}


fk_TreeData * fk_Tree::cloneBranch(fk_TreeData *argParent,
								   fk_TreeData *argData)
{
	fk_TreeData		*tmpRoot;

	if(isArive(argParent) == false) {
		fk_PutError("fk_Tree", "cloneBranch", 1, "dst-node is dead.");
		return nullptr;
	}
	if(argData == nullptr) {
		fk_PutError("fk_Tree", "cloneBranch", 2, "src-node is dead.");
		return nullptr;
	}

	tmpRoot = _simpleClone(argParent, argData);
	argParent->_addChild(tmpRoot);
	return tmpRoot;
}

int fk_Tree::_setDepth(fk_TreeData *argData, int argDepth)
{
	list_ite		ite;
	int				tmpMax;

	if(argData == nullptr) return -1;
	argData->depth = argDepth;
	argData->maxDepth = argDepth;

	for(ite = argData->children.begin();
		ite != argData->children.end(); ++ite) {
		tmpMax = _setDepth(*ite, argDepth+1);
		if(tmpMax > argData->maxDepth) argData->maxDepth = tmpMax;
	}

	return argData->maxDepth;
}

bool fk_Tree::moveBranch(fk_TreeData *argParent, fk_TreeData *argData)
{
	fk_TreeData		*tmpData;

	if(argParent == nullptr || argData == nullptr) {
		fk_PutError("fk_Tree", "moveBranch", 1, "nullptr error.");
		return false;
	}

	if(isArive(argParent) == false) {
		fk_PutError("fk_Tree", "moveBranch", 2, "dst-node is dead.");
		return false;
	}
	if(isArive(argData) == false) {
		fk_PutError("fk_Tree", "moveBranch", 3, "src-node is dead.");
		return false;
	}

	for(tmpData = argParent; tmpData != nullptr; tmpData = tmpData->parent) {
		if(tmpData == argData) {
			fk_PutError("fk_Tree", "moveBranch", 4, "dst-node is under the src-node.");
			return false;
		}
	}

	argData->parent->_clearChild(argData);
	argData->parent->_calcMaxDepth();
	argData->parent = argParent;
	_setDepth(argData, argParent->depth + 1);
	argParent->_addChild(argData);

	return true;
}

void fk_Tree::toFront(int argNum, fk_TreeData *argData)
{
	list_ite	ite;
	fk_TList	*list;
	int			order;

	if(argNum == 0) return;
	if(isArive(argData) == false) return;
	if(argData->parent == nullptr) return;

	list = &(argData->parent->children);

	order = 0;
	for(ite = list->begin(); ite != list->end(); ++ite) {
		if((*ite) == argData) break;
		order++;
	}

	if(ite == list->end()) return;

	list->erase(ite);
	if(argNum < 0 || argNum > order) {
		list->push_front(argData);
	} else {
		ite = list->begin();
		for(int i = 0; i < order - argNum; i++) ++ite;
		list->insert(ite, argData);
	}
	return;
}

void fk_Tree::toBack(int argNum, fk_TreeData *argData)
{
	list_ite	ite;
	fk_TList	*list;
	int			order;

	if(argNum == 0) return;
	if(isArive(argData) == false) return;
	if(argData->parent == nullptr) return;

	list = &(argData->parent->children);

	order = 0;
	for(ite = list->begin(); ite != list->end(); ++ite) {
		if((*ite) == argData) break;
		order++;
	}

	if(ite == list->end()) return;

	list->erase(ite);
	if(argNum < 0 || int(list->size()) < order + argNum) {
		list->push_back(argData);
	} else {
		ite = list->begin();
		for(int i = 0; i < order+argNum; i++) ++ite;
		list->insert(ite, argData);
	}
	return;
}

fk_TreeData * fk_Tree::findData(const string argName)
{
	list_ite		ite;
	fk_TreeData		*cur;

	for(ite = _treeData.begin(); ite != _treeData.end(); ++ite) {
		cur = *ite;
		if(cur->name == argName) return cur;
	}
	return nullptr;
}

fk_TreeData * fk_Tree::foreachData(fk_TreeData *argData)
{
	list_ite		ite;

	if(argData == nullptr) {
		return _treeData.front();
	}
	ite = find(_treeData.begin(), _treeData.end(), argData);
	if(ite == _treeData.end()) return nullptr;
	++ite;
	if(ite == _treeData.end()) return nullptr;
	return (*ite);
}

void fk_Tree::Print(void)
{
	_root->Print();
	return;
}
