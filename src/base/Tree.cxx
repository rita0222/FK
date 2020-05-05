#include <FK/Tree.h>
#include <FK/Error.H>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace FK;

fk_TreeData::Member::Member(fk_Tree *argTree, const string &argName, fk_TreeData *argParent) :
	base(argTree), name(argName), parent(argParent), depth(0), maxDepth(0)
{
	return;
}

fk_TreeData::fk_TreeData(fk_Tree *argTree, const string &argName, fk_TreeData *argParent) :
	_m(make_unique<Member>(argTree, argName, argParent))
{
	if(argParent != nullptr) _m->depth = _m->maxDepth = argParent->getDepth() + 1;
	return;
}

fk_TreeData::~fk_TreeData()
{
	return;
}

int fk_TreeData::getDepth(void)
{
	return _m->depth;
}

int fk_TreeData::getMaxDepth(void)
{
	return _m->maxDepth;
}

fk_TreeData * fk_TreeData::getChild(fk_TreeData *argPrev)
{
	if(argPrev == nullptr) {
		if(_m->children.empty() == true) return nullptr;
		return _m->children.front();
	}

	td_ite ite = find(_m->children.begin(), _m->children.end(), argPrev);
	if(ite == _m->children.end()) return nullptr;
	++ite;
	if(ite == _m->children.end()) return nullptr;
	return (*ite);
}

fk_TreeData * fk_TreeData::getParent(void)
{
	return _m->parent;
}

fk_TreeData * fk_TreeData::getNext(void)
{
	if(getParent() == nullptr) return nullptr;

	fk_TDList *c = getParent()->_getChildren();

	for(td_ite ite = c->begin(); ite != c->end(); ++ite) {
		if((*ite) == this) {
			++ite;
			if(ite == c->end()) return nullptr;
			return (*ite);
		}
	}
	return nullptr;
}

fk_TreeData * fk_TreeData::getPrev(void)
{
	if(getParent() == nullptr) return nullptr;
	fk_TDList *c = getParent()->_getChildren();
	td_ite ite = find(c->begin(), c->end(), this);
	if(ite == c->end() || ite == c->begin()) return nullptr;
	--ite;
	return (*ite);
}

int fk_TreeData::getOrder(void)
{
	int				order = 0;

	if(getParent() == nullptr) return 0;

	fk_TDList *c = getParent()->_getChildren();
	for(td_ite ite = c->begin(); ite != c->end(); ++ite) {
		if((*ite) == this) return order;
		order++;
	}
	return -1;
}

int fk_TreeData::getChildrenSize(void)
{
	return int(_m->children.size());
}

void fk_TreeData::_addChild(fk_TreeData *argChild)
{
	_m->children.push_back(argChild);
	_calcMaxDepth();
	return;
}

void fk_TreeData::_clearChild(fk_TreeData *argChild)
{
	td_ite ite = find(_m->children.begin(), _m->children.end(), argChild);
	if(ite == _m->children.end()) return;
	_m->children.erase(ite);
	return;
}

fk_TreeData::fk_TDList * fk_TreeData::_getChildren(void)
{
	return &(_m->children);
}

void fk_TreeData::Print(void)
{
	stringstream ss;
	

	for(int i = 0; i < _m->depth; i++) {
		ss << "\t";
	}

	ss << "(" << _m->name << ", " << _m->maxDepth << ")";
	Error::Put(ss.str());

	for(td_ite ite = _m->children.begin(); ite != _m->children.end(); ++ite) {
		(*ite)->Print();
	}
	return;
}

void fk_TreeData::_calcMaxDepth(void)
{
	_m->maxDepth = _m->depth;
	for(td_ite ite = _m->children.begin(); ite != _m->children.end(); ++ite) {
		int tmpDepth = (*ite)->getMaxDepth();
		if(tmpDepth > _m->maxDepth) _m->maxDepth = tmpDepth;
	}

	if(_m->parent != nullptr) _m->parent->_calcMaxDepth();
	return;
}

string fk_TreeData::getName(void)
{
	return _m->name;
}

/*
void fk_TreeData::setObject(fk_TreeBaseObject *argObject, bool argDelFlg)
{
	object = argObject;
	deleteFlg = argDelFlg;
	return;
}
*/
void fk_TreeData::setObject(const shared_ptr<fk_TreeBaseObject> &argObject)
{
	_m->object = argObject;
}

fk_TreeBaseObject * fk_TreeData::getObject(void)
{
	return _m->object.get();
}

fk_Tree::Member::Member(void) : root(nullptr)
{
	return;
}

fk_Tree::fk_Tree(const string argName) : _m(make_unique<Member>())
{
	clear(argName);
	return;
}

fk_Tree::~fk_Tree(void)
{
	_clear();
	return;
}

fk_TreeData * fk_Tree::makeNewData(fk_Tree *argTree, string argName, fk_TreeData *argParent)
{
	_m->tree.push_back(make_unique<fk_TreeData>(argTree, argName, argParent));
	return _m->tree.back().get();
}

void fk_Tree::_makeRoot(const string argName)
{
	_m->root = makeNewData(this, argName, nullptr);
	return;
}

fk_TreeData * fk_Tree::getRoot(void)
{
	return _m->root;
}

fk_Tree::t_ite fk_Tree::_getIte(fk_TreeData *argData)
{
	return find_if(_m->tree.begin(), _m->tree.end(),
				   [argData](unique_ptr<fk_TreeData> &d) {
					   return (d.get() == argData);
				   });

}

void fk_Tree::_clear(void)
{
	_m->tree.clear();
	return;
}

void fk_Tree::_clearData(fk_TreeData *argData)
{
	t_ite ite = _getIte(argData);
	if(ite != _m->tree.end()) {
		_m->tree.erase(ite);
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
	if(argData->_m->base != this) return false;

	return (_getIte(argData) != _m->tree.end());
}

fk_TreeData * fk_Tree::addNewChild(fk_TreeData *argData, const string argName)
{
	if(isArive(argData) == false) return nullptr;
	return makeNewData(this, argName, argData);
}

bool fk_Tree::deleteBranch(fk_TreeData *argData)
{
	if(isArive(argData) == false) return false;
	if(argData == _m->root) return false;

	fk_TreeData *parent = argData->_m->parent;

	clearChildren(argData);

	parent->_clearChild(argData);
	_clearData(argData);
	parent->_calcMaxDepth();

	return true;
}

bool fk_Tree::clearChildren(fk_TreeData *argData)
{
	if(isArive(argData) == false) return false;

	for(fk_TreeData *childData = argData->getChild(nullptr);
		childData != nullptr;
		childData = argData->getChild(childData)) {
		deleteBranch(childData);
	}

	return true;
}

fk_TreeData * fk_Tree::cloneOneData(fk_TreeData *argParent, fk_TreeData *argData)
{
	if(isArive(argParent) == false) return nullptr;

	fk_TreeData *newChild = addNewChild(argParent, argData->_m->name);
	newChild->_m->object = argData->_m->object;
	return newChild;
}

fk_TreeData * fk_Tree::_simpleClone(fk_TreeData *argParentData, fk_TreeData *argFromData)
{
	fk_TreeData *newData = makeNewData(this, argFromData->_m->name, argParentData);
	fk_TreeData::fk_TDList *c = argFromData->_getChildren();
	for(fk_TreeData::td_ite ite = c->begin(); ite != c->end(); ++ite) {
		newData->_addChild(_simpleClone(newData, (*ite)));
	}
	newData->_m->object = argFromData->_m->object;
	return newData;
}


fk_TreeData * fk_Tree::cloneBranch(fk_TreeData *argParent, fk_TreeData *argData)
{
	if(isArive(argParent) == false) {
		Error::Put("fk_Tree", "cloneBranch", 1, "dst-node is dead.");
		return nullptr;
	}
	if(argData == nullptr) {
		Error::Put("fk_Tree", "cloneBranch", 2, "src-node is dead.");
		return nullptr;
	}

	fk_TreeData *tmpRoot = _simpleClone(argParent, argData);
	argParent->_addChild(tmpRoot);
	return tmpRoot;
}

int fk_Tree::_setDepth(fk_TreeData *argData, int argDepth)
{
	if(argData == nullptr) return -1;
	argData->_m->depth = argDepth;
	argData->_m->maxDepth = argDepth;

	fk_TreeData::fk_TDList *c = argData->_getChildren();

	for(fk_TreeData::td_ite ite = c->begin(); ite != c->end(); ++ite) {
		int tmpMax = _setDepth(*ite, argDepth+1);
		if(tmpMax > argData->_m->maxDepth) argData->_m->maxDepth = tmpMax;
	}

	return argData->_m->maxDepth;
}

bool fk_Tree::moveBranch(fk_TreeData *argParent, fk_TreeData *argData)
{
	if(argParent == nullptr || argData == nullptr) {
		Error::Put("fk_Tree", "moveBranch", 1, "nullptr error.");
		return false;
	}

	if(isArive(argParent) == false) {
		Error::Put("fk_Tree", "moveBranch", 2, "dst-node is dead.");
		return false;
	}
	if(isArive(argData) == false) {
		Error::Put("fk_Tree", "moveBranch", 3, "src-node is dead.");
		return false;
	}

	for(fk_TreeData *tmpData = argParent;
		tmpData != nullptr;
		tmpData = tmpData->_m->parent) {
		if(tmpData == argData) {
			Error::Put("fk_Tree", "moveBranch", 4, "dst-node is under the src-node.");
			return false;
		}
	}

	fk_TreeData *p = argData->_m->parent;

	p->_clearChild(argData);
	p->_calcMaxDepth();
	argData->_m->parent = argParent;
	_setDepth(argData, argParent->_m->depth + 1);
	argParent->_addChild(argData);

	return true;
}

void fk_Tree::toFront(int argNum, fk_TreeData *argData)
{
	if(argNum == 0) return;
	if(isArive(argData) == false) return;
	if(argData->_m->parent == nullptr) return;

	auto list = argData->getParent()->_getChildren();
	int order = 0;
	fk_TreeData::td_ite ite;
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
	if(argNum == 0) return;
	if(isArive(argData) == false) return;
	if(argData->_m->parent == nullptr) return;

	auto list = argData->getParent()->_getChildren();
	int order = 0;
	fk_TreeData::td_ite ite;

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
	for(auto ite = _m->tree.begin(); ite != _m->tree.end(); ++ite) {
		if(ite->get()->_m->name == argName) return ite->get();
	}
	return nullptr;
}

fk_TreeData * fk_Tree::foreachData(fk_TreeData *argData)
{
	if(argData == nullptr) {
		return _m->tree.front().get();
	}
	auto ite = _getIte(argData);
	if(ite == _m->tree.end()) return nullptr;
	++ite;
	if(ite == _m->tree.end()) return nullptr;
	return ite->get();
}

void fk_Tree::Print(void)
{
	_m->root->Print();
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
