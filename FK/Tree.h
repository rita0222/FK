#ifndef __FK_TREE_HEADER__
#define __FK_TREE_HEADER__

#include <list>
#include <string>
#include <iostream>

class fk_Tree;
class fk_TreeData;

//! 木構造オブジェクトデータの基底クラス
/*!
 *	このクラスは、単独としての機能は何もありませんが、
 *	本クラスを派生したクラスは
 *	fk_TreeData のオブジェクトとして設定することができます。
 *	詳しくは fk_TreeData::setObject() の解説を参照して下さい。
 *
 *	\sa fk_Tree, fk_TreeData
 */

class fk_TreeBaseObject {
 public:
	fk_TreeBaseObject(void) {};
	virtual ~fk_TreeBaseObject(void) {};
};

typedef std::list<fk_TreeData *>	fk_TList;


//! 木構造用ノードデータクラス
/*!
 *	このクラスは、木構造を用いたデータベースにおける、
 *	ノードデータに必要な機能を提供します。
 *
 *	本クラスは、FK の機能を利用するためのものではなく、
 *	ユーザが木構造を利用する際に便利なユーティリティクラスです。
 *	本クラスおよび fk_Tree, fk_TreeBaseObject の各クラスを用いて利用します。
 * 	本クラスの解説に使用される用語については、
 *	fk_Tree クラスの概要を参照して下さい。
 *
 *	各クラスの役割ですが、
 *	fk_Tree クラスは木構造全体のデータベースとなります。
 *	fk_TreeData は各ノードのデータを意味します。
 *	fk_TreeBaseObject は、
 *	fk_TreeData に対してユーザ定義のデータを付加するための基底クラスとなります。
 *	基本的には、ノードの生成、移動、消去といった操作は fk_Tree で、
 *	ノード自体の設定は fk_TreeData のメンバ関数で行うことになります。
 *
 *	本クラスのインスタンスは、基本的にはユーザが自前で生成するものではなく、
 *	fk_Tree の各種ノード生成関数によって自動的に生成されるものです。
 *	唯一の例外は fk_Tree クラスの派生クラスを作成し、
 *	そこで fk_Tree::makeNewData() を再定義する場合となります。
 *
 *	\sa fk_Tree, fk_TreeBaseObject
 */

class fk_TreeData {

	friend class			fk_Tree;

 private:
	fk_TreeBaseObject		*object;
	fk_Tree					*base;
	std::string				name;
	fk_TreeData				*parent;
	fk_TList				children;
	int						depth, maxDepth;
	bool					deleteFlg;

	void					_calcMaxDepth(void);
	void					_addChild(fk_TreeData *);
 	void					_clearChild(fk_TreeData *);

 public:
	//! コンストラクタ
	/*!
	 *	fk_Tree::makeNewData() を再定義する際に、
	 *	インスタンスを自前で生成する際に利用します。
	 *
	 *	\param[in]	tree	新ノードが属する fk_Tree インスタンス
	 *	\param[in]	name	新ノードに指定されている名称
	 *	\param[in]	parent	新ノードの親となるノードのインスタンス
	 *
	 *	\sa fk_Tree:makeNewData()
	 */
	fk_TreeData(fk_Tree *tree,
				const std::string name,
				fk_TreeData *parent);

	//! デストラクタ
	virtual ~fk_TreeData();

	//! 深さ参照関数
	/*!
	 *	このノードの深さを取得します。
	 *
	 * 	\return		深さ値
	 *
	 *	\sa getMaxDepth()
	 */
	int		getDepth(void);

	//! 枝深さ参照関数
	/*!
	 *	このノードを頂点とする枝の中で、最大の深さを取得します。
	 *	根ノードでこの関数を呼んだ場合は、全体の深さの最大値を返すことになります。
	 *
	 *	\return		枝中の最大深さ値
	 *
	 *	\sa getDepth()
	 */
	int		getMaxDepth(void);

	//! 子ノード逐次参照関数
	/*!
	 *	このノードの子ノードを逐次的に参照します。
	 *	引数に代入したノードインスタンスによる、以下のような動作を行います。
	 *	- 引数に nullptr を入力した場合、最も前にある子ノードを返します。
	 *		(子ノードが存在しなかった場合は、nullptr を返します。)
	 *	- その後、子ノードのインスタンスを入力すると、
	 *		その1つ後の子ノードを返します。
	 *	- 最下位のノードを入力した場合は、nullptr を返します。
	 *	- 子ノードでないインスタンスを入力した場合は、nullptr を返します。
	 *	.
	 *	以下のコードは、子ノードを順番に参照するものです。
	 *
	 *		fk_TreeData		*parent, *child;
	 *
	 *		for(child = parent->getChild(nullptr);
	 *			child != nullptr;
	 *			child = parent->getChild(child)) {
	 *			// child に子ノードが順番に入ります。
	 *		}
	 *
	 *	\param[in]	node	逐次参照対象ノードインスタンス
	 *
	 *	\return
	 *		引数の次の順位の子ノードインスタンスを返します。
	 *		該当するノードが存在しない場合は nullptr を返します。
	 *
	 *	\sa getParent(), getPrev(), getNext(), getChildrenSize()
	 */
	fk_TreeData *	getChild(fk_TreeData *node);
	
	//! 親ノード参照関数
	/*!
	 *	このノードの親ノードインスタンスを返します。
	 *	もし根ノードにおいてこの関数を呼んだ場合は、nullptr を返します。
	 *
	 *	\return		親ノードインスタンス
	 *
	 *	\sa getChild(), getChildrenSize()
	 */
	fk_TreeData *	getParent(void);

	//! 後ノード参照関数
	/*!
	 *	このノードを構成する兄弟ノードのうち、
	 *	順位が1つ後のノードインスタンスを返します。
	 *	そのようなノードが存在しない場合は nullptr を返します。
	 *
	 *	\return		後ノードインスタンス。存在しない場合は nullptr を返します。
	 *
	 *	\sa getChild(), getParent(), getPrev(), getOrder(), getChildrenSize()
	 */
	fk_TreeData *	getNext(void);

	//! 前ノード参照関数
	/*!
	 *	このノードを構成する兄弟ノードのうち、
	 *	順位が1つ前のノードインスタンスを返します。
	 *	そのようなノードが存在しない場合は nullptr を返します。
	 *
	 *	\return		前ノードインスタンス。存在しない場合は nullptr を返します。
	 *
	 *	\sa getChild(), getParent(), getNext(), getOrder(), getChildrenSize()
	 */
	fk_TreeData *	getPrev(void);

	//! 順位参照関数
	/*!
	 *	このノードの順位を参照します。
	 *	兄弟ノードが存在しない場合は、常に 1 となります。
	 *
	 *	\return		順位
	 *
	 *	\sa getNext(), getPrev(), getChildrenSize()
	 */
	int		getOrder(void);

	//! 子ノード個数参照関数
	/*!
	 *	このノードの子ノードの個数を返します。
	 *
	 *	\return		子ノード個数
	 *
	 *	\sa getParent(), getChild(), getOrder()
	 */
	int		getChildrenSize(void);

	//! 名称参照関数
	/*!
	 *	このノードの名称を取得します。
	 *
	 *	\return		名称
	 *
	 *	\sa setObject(), getObject()
	 */
	std::string		getName(void);

	// ユーザデータの挿入 (デストラクタで同時に消去されたくない場合は,
	// 後ろの引数で false を選択)

	//! ユーザデータ設定関数
	/*!
	 *	ユーザ定義によるデータをノードに設定します。
	 *	ユーザ定義のデータは、
	 *	fk_TreeBaseObject クラスを派生したものを作成しておきます。
	 *	fk_TreeBaseObject クラスは、
	 *	メンバもメンバ関数も定義されていない空のクラスです。
	 *
	 *	\note
	 *		ノードに対する操作によってノードの複製が行われた場合、
	 *		ポインタのコピーが行われます。
	 *		そのような操作が行われる可能性がある場合、
	 *		第2引数は false にしておき、
	 *		インスタンスの消去は自前で行うべきです。
	 *
	 *	\param[in]	object		ユーザ定義インスタンス
	 *	\param[in]	deleteFlg
	 *		true の場合、
	 *		ノードの消去とともにユーザ定義インスタンスも消去 (delete) します。
	 *		false の場合は、
	 *		ノードの消去時にユーザ定義インスタンスの消去 (delete) を行いません。
	 *
	 *	\sa fk_TreeBaseObject, getName(), getObject()
	 */
	void	setObject(fk_TreeBaseObject *object,
					  bool deleteFlg = true);

	//! ユーザデータ参照関数
	/*!
	 *	setObject() によって設定されていたユーザデータを取得します。
	 *	ユーザデータが設定されていなかった場合は nullptr を返します。
	 *
	 *	\return		ユーザ定義インスタンス
	 *
	 *	\sa fk_TreeBaseObject, setObject(), getName()
	 */
	fk_TreeBaseObject *		getObject(void);

#ifndef FK_DOXYGEN_USER_PROCESS
	void					Print(void);
#endif

};

//! 木構造用データベースクラス
/*!
 *	このクラスは、木構造を用いたデータベース機能を提供します。
 *
 *	本クラスは、FK の機能を利用するためのものではなく、
 *	ユーザが木構造を利用する際に便利なユーティリティクラスです。
 *	本クラスおよび fk_TreeData, fk_TreeBaseObject の各クラスを用いて利用します。
 *	これらのクラス中の解説で使用される用語を、以下のように定義します。
 *	- 根ノード:
 *		木構造の頂点(最上部)にあるノード。
 *	- 子ノード:
 *		あるノードに対し、その下方にあるノードのこと。
 *		任意のノードは、複数の子ノードを持つことができます。
 *	- 親ノード:
 *		あるノードに対し、その上方にあるノードのこと。
 *		根ノードは親ノードを持ちませんが、
 *		その他のノードは必ず親ノードを1つだけ持ちます。
 *	- 兄弟ノード:
 *		あるノードの子ノード全体のこと。
 *	- (あるノードの)前のノード:
 *		同じ親ノードを持つノードのうち、順番が1つ前に当たるノードのこと。
 *	- (あるノードの)後のノード:
 *		同じ親ノードを持つノードのうち、順番が1つ後に当たるノードのこと。
 *	- 枝:
 *		あるノードと、その下方に位置しているノード全てを総称した集合。
 *	- ノード間距離:
 *		あるノードを出発点とし、別のノードに親子間を伝って移動する際のステップ数。
 *	- ノードの深さ:
 *		あるノードの、根ノードからの距離のこと。
 *	- ノードの順位:
 *		兄弟ノードの中での、前から何番目に位置するかという順番のこと。
 *	.
 *	これを図で説明します。
 *	\image html Tree01.png "ツリー構造"
 *	\image latex Tree01.eps "ツリー構造" width=5cm
 *	- 図中で、ノード A が「根ルート」となります。
 *	- A からみれば、B, C, D は全て「子ノード」ということになります。
 *	- 逆に、A は B の「親ノード」となります。
 *	- B, C, D の集合は「兄弟ノード」となります。
 *		同様に、F, G も「兄弟ノード」となります。
 *	- B, C, D がこの順番に登録されていた場合、
 *		C にとって B は「前のノード」となり、
 *		B にとって C は「後のノード」となります。
 *		その場合の B, C, D の順位は 1, 2, 3 となります。
 *	- B の「前のノード」は存在しません。同様に、D の「後のノード」も存在しません。
 *	- D ノードの「枝」とは、D とその下部にあるノード全てとなりますので、
 *		D, F, G, H, I の集合ということになります。
 *	- E ノードと I ノードの「距離」は、親子関係を伝っていくと
 *		E → B → A → D → F → I となるため、距離は 5 となります。
 *	- E ノードの深さは 2、H ノードの深さは 3 となります。
 *		A ノードについては、根ノードとなるので深さは 0 となります。
 *	.
 *	各クラスの役割ですが、
 *	fk_Tree クラスは木構造全体のデータベースとなります。
 *	fk_TreeData は各ノードのデータを意味します。
 *	fk_TreeBaseObject は、
 *	fk_TreeData に対してユーザ定義のデータを付加するための基底クラスとなります。
 *	基本的には、ノードの生成、移動、消去といった操作は fk_Tree で、
 *	ノード自体の設定は fk_TreeData のメンバ関数で行うことになります。
 *
 *	各ノードには任意の名称をつけることができます。
 *	異なるノードに同一の名称をつけることは可能です。
 *	しかしその場合、 findData() でノードの検索を行う際には不都合が生じる場合があります。
 *	検索機能を有効利用したい場合は、名称を一意にしておくとよいでしょう。
 *
 *	\sa fk_TreeData, fk_TreeBaseObject
 */
 
class fk_Tree {

 private:
	fk_TList		_treeData;
	fk_TreeData		*_root;

	void			_clear(void);
	void			_makeRoot(const std::string);
	void			_clearData(fk_TreeData *);
	fk_TreeData *	_simpleClone(fk_TreeData *, fk_TreeData *);
	int				_setDepth(fk_TreeData *, int);

 protected:

	//! ノード生成時関数
	/*!
	 *	この関数は、
	 *	addNewChild() などで新たにノードが生成された際に、
	 *	各ノード (fk_TreeData インスタンス) ごとに呼び出される関数です。
	 *	fk_Tree クラスの派生クラスにおいて、本関数を再定義することにより、
	 *	ノード生成時に自動的に行っておきたい処理を記述することができます。
	 *	デフォルトでは、以下のようなコードになっています。
	 *
	 *		fk_TreeData * fk_Tree::makeNewData(fk_Tree *tree,
	 *										   const std::string name,
	 *										   fk_TreeData *parent)
	 *		{
	 *			return(new fk_TreeData(tree, name, parent));
	 *		}
	 *
	 *	本関数のコードでは、必ず fk_TreeData 型のインスタンスを生成し、
	 *	それを返す必要があります。
	 *
	 *	\param[in]	tree	新ノードが属する fk_Tree インスタンス
	 *	\param[in]	name	新ノードに指定されている名称
	 *	\param[in]	parent	新ノードの親となるノードのインスタンス
	 *
	 *	\return
	 *		新たなノードとなる fk_TreeData 型インスタンスを生成し、
	 *		それを返すようにして下さい。
	 */
	virtual fk_TreeData *	makeNewData(fk_Tree *tree,
										const std::string name,
										fk_TreeData *parent);

 public:
	//! コンストラクタ
	/*!
	 *	インスタンスの生成時に、
	 *	同時に根ノードとして fk_TreeData 型のノードが一つ自動的に生成されます。
	 *	引数によって、その根ノードに対する名称を設定します。
	 *
	 *	\param[in]	name		根ノードの名称
	 */
	fk_Tree(const std::string name = "default");

	//! デストラクタ
	virtual ~fk_Tree();

	//! 根ノード参照関数
	/*!
	 *	根ノードであるノードのインスタンスを返します。
	 *
	 *	\return		根ノードインスタンス
	 */
	fk_TreeData *	getRoot(void);

	//!	初期化関数
	/*!
	 *	現状の、根ノードを含む全てのノードを消去し、
	 *	新たな根ノードを作成します。
	 *
	 *	\param[in]	name	新しい根ノードの名称
	 *
	 *	\sa deleteBranch()
	 */
	void	clear(const std::string name);

	//! 新規ノード生成関数
	/*!
	 *	新たなノードを作成します。
	 *	既に兄弟ノードが存在していた場合、
	 *	その中での順位は一番後となります。
	 *
	 *	\param[in]	parent		新ノードの親となるノードのインスタンス
	 *	\param[in]	name		新ノードの名称
	 *
	 *	\return		新ノードのインスタンス
	 */
	fk_TreeData *	addNewChild(fk_TreeData *parent,
								const std::string name);

	//! ノードおよびその下の枝の消去関数
	/*!
	 *	指定したノードと、そのノードを元とする枝全体を消去します。
	 *	例えば、下図の左側において「D」のノードを指定した場合、
	 *	D および F, G, H, I のノードも消去します。
	 *	\image html Tree02.png "枝の消去"
	 *	\image latex Tree02.eps "枝の消去" width=10cm
	 *	根ノードについては、本関数によって消去はできません。
	 *	clearChildren() との違いは、本関数は指定ノードも消去しますが、
	 *	clearChildren() は指定ノードの消去は行わないことです。
	 *
	 *	\param[in]	node	消去するノードのインスタンス
	 *
	 *	\return
	 *		消去に成功すれば true を、失敗すれば false を返します。
	 *
	 *	\sa clear(), clearChildren()
	 */
	bool	deleteBranch(fk_TreeData *node);

	//! 子ノードおよびその下の枝の消去関数
	/*!
	 *	指定したノードの子ノード全てと、その子ノードを元とする枝全体を消去します。
	 *	例えば、下図の左側において「D」のノードを指定した場合、
	 *	F, G, H, I の各ノードを消去します。
	 *	\image html Tree03.png "子ノードの消去"
	 *	\image latex Tree03.eps "子ノードの消去" width=10cm
	 *	deleteBranch() との違いは、本関数は指定ノードの消去は行いませんが、
	 *	deleteBranch() では指定ノードも消去することです。
	 *
	 *	\param[in]	node	指定ノードインスタンス
	 *
	 *	\return
	 *		消去に成功すれば true を、失敗すれば false を返します。
	 *
	 *	\sa clear(), deleteBranch()
	 */
	bool	clearChildren(fk_TreeData *node);

	//! 単一ノード複製関数
	/*!
	 *	ノードの複製を行い、任意のノードの子ノードとして登録します。
	 *	複製する要素は以下のとおりです。
	 *	- 名称
	 *	- fk_TreeeData::setObject() によって登録されたユーザインスタンス
	 *	.
	 *	この関数においては、複製元のノードで子ノードが存在していた場合、
	 *	子ノードの複製は行いません。
	 *	例えば、下図の左側で「F」のノードを「B」のノードの下に複製した場合、
	 *	新たな「F」ノードの下には何もノードがない状態となります。
	 *	\image html Tree04.png "単一ノードの複製"
	 *	\image latex Tree04.eps "単一ノードの複製" width=10cm
	 *
	 *	複製した先に兄弟ノードが存在していた場合、
	 *	新たなノードの順位は一番後となります。
	 *
	 *	\param[in]	parent		複製先の親ノードインスタンス
	 *	\param[in]	node		複製元のノードインスタンス
	 *
	 *	\return
	 *		成功した場合、新たに生成されたノードインスタンスを返します。
	 *		失敗した場合は nullptr を返します。
	 *
	 *	\sa cloneBranch(), moveBranch()
	 */
	fk_TreeData *	cloneOneData(fk_TreeData *parent,
								 fk_TreeData *node);

	//! 枝複製関数
	/*!
	 *	枝の複製を行い、任意のノードの下に登録します。
	 *	複製する要素は以下のとおりです。
	 *	- 名称
	 *	- fk_TreeeData::setObject() によって登録されたユーザインスタンス
	 *	- 各兄弟ノードの前後関係
	 *	.
	 *	例えば、下図の左側で「F」のノードを「B」のノードの下に複製した場合、
	 *	新たな「F」ノードの子ノードとして「H」、「I」のノードも一緒に複製されます。
	 *	\image html Tree05.png "枝の複製"
	 *	\image latex Tree05.eps "枝の複製" width=10cm
	 *
	 *	複製した先に兄弟ノードが存在していた場合、
	 *	新たなノードの順位は一番後となります。
	 *
	 *	\param[in]	parent		複製先の親ノードインスタンス
	 *	\param[in]	node		複製元のノードインスタンス
	 *
	 *	\return
	 *		成功した場合、新たに生成されたノードインスタンスを返します。
	 *		失敗した場合は nullptr を返します。
	 *
	 *	\sa cloneOneData(), moveBranch()
	 */
	fk_TreeData *	cloneBranch(fk_TreeData *parent,
								fk_TreeData *node);

	//! 枝移動関数
	/*!
	 *	枝の移動を行います。
	 *	移動する要素は以下の通りです。
	 *	- 名称
	 *	- fk_TreeeData::setObject() によって登録されたユーザインスタンス
	 *	- 各兄弟ノードの前後関係
	 *	.
	 *	例えば、下図の左側で「F」のノードを「B」のノードの下に移動した場合、
	 *	「D」の下にあった「F」はなくなります。
	 *	\image html Tree06.png "枝の移動"
	 *	\image latex Tree06.eps "枝の移動" width=10cm
	 *
	 *	枝が移動できる条件として、
	 *	移動先となる親ノードに元の枝の中にあるノードを指定することはできません。
	 *	上図で例えると、「F」の移動先として「H」や「I」は指定できないことになります。
	 *	移動した先に兄弟ノードが存在していた場合、
	 *	新たなノードの順位は一番後となります。
	 *
	 *	\param[in]	parent		移動先の親ノードインスタンス
	 *	\param[in]	node		移動元のノードインスタンス
	 *
	 *	\return
	 *		成功した場合 true を、失敗した場合 false を返します。
	 *
	 *	\sa cloneOneData(), cloneBranch()
	 */
	bool	moveBranch(fk_TreeData *parent, fk_TreeData *node);

	//! 順位前進関数
	/*!
	 *	任意のノードに対し、兄弟ノードの中での順位を前に移動します。
	 *
	 *	\param[in]	n
	 *		前に移動する順位数。
	 *		ただし、n が以下の条件を満たした場合、
	 *		一番前に移動します。
	 *		- 順位よりも大きな数値を指定した場合。
	 *		- n が負の場合。(例えば -1 など)
	 *		.
	 *	\param[in]	node	操作対象ノードのインスタンス
	 *
	 *	\sa toBack()
	 */
	void	toFront(int n, fk_TreeData *node);

	//! 順位後退関数
	/*!
	 *	任意のノードに対し、兄弟ノードの中での順位を後に移動します。
	 *
	 *	\param[in]	n
	 *		後に移動する順位数。
	 *		ただし、n が以下の条件を満たした場合、
	 *		一番後に移動します。
	 *		- (兄弟ノードの個数) - (順位) よりも大きな数値を指定した場合。
	 *		- n が負の場合。(例えば -1 など)
	 *		.
	 *	\param[in]	node	操作対象ノードのインスタンス
	 *
	 *	\sa toFront()
	 */
	void	toBack(int n, fk_TreeData *node);

	// d が該当の木の中で生存するデータかどうか判定

	//! ノード生存確認関数
	/*!
	 *	指定したノードが、本インスタンスのデータ中に存在するかどうかを確認します。
	 *
	 *	\param[in]	node	確認対象ノードインスタンス
	 *
	 *	\return
	 *		データ内に存在していれば true を、していなければ false を返します。
	 */
	bool	isArive(fk_TreeData *node);

	// nという名前のデータを検索
	//! ノード検索関数
	/*!
	 *	名称をキーとしてノードを検索します。
	 *	もし同一名のノードがデータ内に存在している場合は、
	 *	最も早い段階で生成されていたインスタンスを返します。
	 *
	 *	\param[in]	name	検索対象ノード名
	 *
	 *	\return
	 *		見つかれば、そのインスタンスを返します。
	 *		データ内に存在していなかった場合は nullptr を返します。
	 */
	fk_TreeData *	findData(const std::string name);

	//! 逐次ノード参照関数
	/*!
	 *	データ内の各ノードを、逐次的に参照していきます。
	 *	引数に代入したノードインスタンスにより、以下のような動作を行います。
	 *	- 引数に nullptr を代入した場合、根ノードを返します。
	 *	- 任意のノードを引数に代入したときは、
	 *		そのノードの次に生成されたノードを返します。
	 *	- 最後に生成したノードを代入したときは、nullptr を返します。
	 *	.
	 *	以下のコードは、データ内の全てのノードを参照するものです。
	 *
	 *		fk_Tree			tree;
	 *		fk_TreeData		*node;
	 *
	 *		for(node = tree.foreachData(nullptr);
	 *			node != nullptr;
	 *			node = tree.foreachData(node)) {
	 *			// node 変数にノードが入っています。
	 *		}
	 *
	 *	\param[in]	node	逐次探索対象ノードインスタンス
	 *
	 *	\return
	 *		引数の次に生成されたノードインスタンスを返します。
	 *		引数のノードが最後に生成されたインスタンスであった場合は nullptr を返します。
	 */
	fk_TreeData *	foreachData(fk_TreeData *node);

#ifndef FK_DOXYGEN_USER_PROCESS
	void	Print(void);
#endif
};

#endif // !__FK_TREE_HEADER__

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
