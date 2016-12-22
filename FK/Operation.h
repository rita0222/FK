#ifndef __FK_OPERATION_HEADER__
#define __FK_OPERATION_HEADER__

#include <vector>
#include <FK/DrawCache.h>
#include <FK/History.H>

namespace FK {

#ifdef __FK_OPERATION_CODE__
	static const int	MAKEV		= 1;
	static const int	DELV		= 2;
	static const int	MOVEV		= 3;
	static const int	MAKEE1		= 4;
	static const int	MAKEE2		= 5;
	static const int	MAKEE3		= 6;
	static const int	DELE1		= 7;
	static const int	DELE2		= 8;
	static const int	DELE3		= 9;
	static const int	MAKEL		= 10;
	static const int	DELL		= 11;
	static const int	SEPL		= 12;
	static const int	UNITL		= 13;
	static const int	SEPE		= 14;
	static const int	UNITE		= 15;
	static const int	NEGATE		= 16;

#endif

	//! オイラー操作用クラス
	/*!
	 *	このクラスは、 fk_Solid クラスのインスタンスにおいて、
	 *	位相操作を含む様々な変形に関する基本的な機能を提供します。
	 *	fk_Solid の位相についての詳細は、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」という章を参照して下さい。
	 *
	 *	境界表現によるソリッドモデルでは、
	 *	数種類の基本的な操作によって変形処理を実現します。
	 *	これを「オイラー操作」と呼び、
	 *	fk_Solid では 12 種類のオイラー操作が存在します。
	 *	どのような複雑な変形処理であっても、
	 *	これらのオイラー操作のみ合わせによって実現しています。
	 *	より高機能な形状操作機能については、
	 *	fk_Modify クラスの各機能を参照して下さい。
	 *
	 *	オイラー操作のもう一つの特徴は、
	 *	任意の操作について必ず「逆操作」が存在するということです。
	 *	これは、どのような変形処理についても、
	 *	元の形状に戻すための操作が必ず存在することを保障するということです。
	 *	このことにより、 fk_Solid では回数無制限の履歴操作を実現しています。
	 *	履歴操作については undoHistory(), redoHistory() を参照して下さい。
	 *
	 *	なお、本クラスの解説は独自の用語を用います。定義を以下に述べます。
	 *	- 独立頂点: 稜線に接続していない頂点のこと。
	 *	- 接続頂点: 稜線に接続している頂点のこと。
	 *	- 任意頂点: 全ての頂点のこと。
	 *	- 未定義稜線: 両側のループが定義されていない稜線のこと。
	 *	- 定義稜線: 両側、あるいは片側のループが定義されている稜線のこと。
	 *	- 任意稜線: 全ての稜線のこと。
	 *	- 定義半稜線: 親ループを保持する半稜線のこと。
	 *	- 未定義半稜線: 親ループを保持しない半稜線のこと。
	 *
	 *	\sa fk_Solid, fk_Modify, fk_DataAccess, fk_ReferenceL1, fk_ReferenceL2, fk_ReferenceL3
	 */

	class fk_Operation : public fk_DrawCache {

	public:
		//! コンストラクタ
		fk_Operation(fk_DataBase * = nullptr);

		//! デストラクタ
		virtual ~fk_Operation();

		//! \name オイラー操作関数
		//@{

		//! 頂点生成関数
		/*!
		 *	任意の位置に新たに頂点位相を生成します。
		 *	既にその位置に頂点が存在していたとしても、同じ場所に生成します。
		 *
		 *	なお、この操作の逆操作は deleteVertex() 関数となります。
		 *
		 *	\image html Euler01.png "makeVertex と deleteVertex"
		 *	\image latex Euler01.eps "makeVertex と deleteVertex" width=10cm
		 *
		 *	\param[in]	P		新規頂点の位置ベクトル
		 *
		 *	\return		新規頂点位相インスタンス
		 */
		fk_Vertex *		makeVertex(const fk_Vector P);

		//! 頂点削除関数
		/*!
		 *	独立頂点を削除します。
		 *	頂点が接続頂点であった場合や、
		 *	形状中に存在していなかった場合は変形操作を行いません。
		 *
		 *	なお、この操作の逆操作は makeVertex() 関数となります。
		 *
		 *	\image html Euler01.png "makeVertex と deleteVertex"
		 *	\image latex Euler01.eps "makeVertex と deleteVertex" width=10cm
		 *
		 *	\param[in]	V		頂点位相インスタンス
		 *
		 *	\return		削除に成功すれば true を、失敗すれば false を返します。
		 */
		bool			deleteVertex(fk_Vertex *V);

		//! 頂点移動関数
		/*!
		 *	任意頂点を指定した位置に移動します。
		 *	頂点は独立頂点であっても接続頂点であっても構いません。
		 *	形状中に存在していなかった場合は変形操作を行いません。
		 *
		 *	この操作の逆操作はこの関数自身となります。
		 *
		 *	\image html Euler02.png "moveVertex"
		 *	\image latex Euler02.eps "moveVertex" width=10cm
		 *
		 *	\param[in]	V	頂点位相インスタンス
		 *	\param[in]	P	移動先の位置ベクトル
		 *
		 *	\return		移動に成功すれば true を、失敗すれば false を返します。
		 */
		bool			moveVertex(fk_Vertex *V, fk_Vector P);

		//! 稜線生成関数
		/*!
		 *	稜線を新たに生成します。
		 *	この関数は、新稜線の端点となる頂点 V1, V2 の状態によって、
		 *	以下の3通りの処理を行います。
		 *
		 *	-# V_1 と V_2 が共に独立頂点の場合。 \n
		 *		この場合は、H_11, H_12, H_21, H_22 のいずれも nullptr を代入します。
		 *		引数自体を省略しても構いません。\n \n
		 *	-# V_1 が接続頂点で、V_2 が独立頂点の場合。 \n
		 *		新たに生成される稜線の半稜線を H1, H2 とし、
		 *		H1 の始点が V_1、H2 の始点が V_2 であるとします。
		 *		このとき、H_11 には接続後に H1 の前となる半稜線を代入します。
		 *		H_12 には、H2 の後となる半稜線を代入します。
		 *		このとき、H_11 および H_12 は未定義半稜線である必要があります。
		 *		H_21 と H_22 には nullptr を代入します。
		 *		H_21 と H_22 の引数は省略しても構いません。\n \n
		 *	-# V_1, V_2 のいずれも接続頂点の場合。 \n
		 *		新たに生成される稜線の半稜線を H1, H2 とし、
		 *		H1 の始点が V_1、H2 の始点が V_2 であるとします。
		 *		このとき、以下のような想定となる半稜線をそれぞれ代入します。
		 *		- H_11 は H1 の前
		 *		- H_12 は H2 の後
		 *		- H_21 は H2 の前
		 *		- H_22 は H1 の後
		 *		.
		 *		上記のいずれの半稜線も未定義稜線でなければなりません。
		 *	.
		 *	なお、この操作の逆操作は deleteEdge() 関数となります。
		 *
		 *	\image html Euler03.png "makeEdge と deleteEdge"
		 *	\image latex Euler03.eps "makeEdge と deleteEdge" width=10cm
		 *
		 *	\param[in]	V_1		新稜線の端点位相インスタンス
		 *	\param[in]	V_2		新稜線の端点位相インスタンス
		 *	\param[in]	H_11	半稜線位相インスタンス。詳細は上記参照のこと。
		 *	\param[in]	H_12	半稜線位相インスタンス。詳細は上記参照のこと。
		 *	\param[in]	H_21	半稜線位相インスタンス。詳細は上記参照のこと。
		 *	\param[in]	H_22	半稜線位相インスタンス。詳細は上記参照のこと。
		 *
		 *	\return
		 *		新稜線の生成に成功した場合、その位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 */
		fk_Edge *		makeEdge(fk_Vertex *V_1, fk_Vertex *V_2,
								 fk_Half *H_11 = nullptr,
								 fk_Half *H_12 = nullptr,
								 fk_Half *H_21 = nullptr,
								 fk_Half *H_22 = nullptr);

		//! 稜線削除関数
		/*!
		 *	未定義稜線を削除します。
		 *	稜線が定義稜線であった場合や、
		 *	形状中に存在していなかった場合は変形操作を行いません。
		 *
		 *	なお、この操作の逆操作は makeEdge() 関数となります。
		 *
		 *	\image html Euler03.png "makeEdge と deleteEdge"
		 *	\image latex Euler03.eps "makeEdge と deleteEdge" width=10cm
		 *
		 *	\param[in]	E		稜線位相インスタンス
		 *
		 *	\return		削除に成功すれば true を、失敗すれば false を返します。
		 */
		bool			deleteEdge(fk_Edge *E);

		//! ループ生成関数
		/*!
		 *	ループを新たに生成します。
		 *	引数に与えられる H が未定義半稜線である場合、
		 *	H が属する半稜線列の親ループとして新規ループが生成され、
		 *	それまで空洞であった場所に面が貼られます。
		 *	H が定義半稜線である場合は、生成に失敗することになります。
		 *
		 *	なお、この操作の逆操作は deleteLoop() 関数となります。
		 *
		 *	\image html Euler04.png "makeLoop と deleteLoop"
		 *	\image latex Euler04.eps "makeLoop と deleteLoop" width=10cm
		 *
		 *	\param[in]	H	未定義半稜線位相インスタンス
		 *
		 *	\return
		 *		生成に成功した場合、そのループ位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 */
		fk_Loop *		makeLoop(fk_Half *H);

		//! ループ削除関数
		/*!
		 *	ループを削除します。
		 *	成功した場合、存在していた面がなくなり空洞状態となります。
		 *	また、削除したループを親ループとして持っていた半稜線は、
		 *	全て未定義半稜線となります。
		 *
		 *	なお、この操作の逆操作は makeLoop() 関数となります。
		 *
		 *	\image html Euler04.png "makeLoop と deleteLoop"
		 *	\image latex Euler04.eps "makeLoop と deleteLoop" width=10cm
		 *
		 *	\param[in]	L	ループ位相インスタンス
		 *
		 *	\return		成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			deleteLoop(fk_Loop *L);

		//! ループ分割関数
		/*!
		 *	ループを分割します。
		 *	引数の H1 と H2 は同じループに属している必要があります。
		 *	分割の際に生成される稜線の端点は、
		 *	H1 の終点にあたる頂点と H2 の始点にあたる頂点となります。
		 *	始点した端点の間に既に稜線が存在していた場合であっても、
		 *	分割処理は行われます。
		 *	(その場合は、片方の面が縮退することになります。)
		 *	分割に成功した場合、H1 と H2 は新規ループ側に属することになりますので、
		 *	新規ループの位相インスタンスを得たい場合は
		 *	H1 や H2 の親ループを参照して下さい。
		 *
		 *	なお、この操作の逆操作は uniteLoop() 関数となります。
		 *
		 *	\image html Euler05.png "separateLoop と uniteLoop"
		 *	\image latex Euler05.eps "separateLoop と uniteLoop" width=10cm
		 *
		 *	\param[in]	H1		半稜線位相インスタンス
		 *	\param[in]	H2		半稜線位相インスタンス
		 *
		 *	\return
		 *		成功した場合、新規稜線の位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 */	
		fk_Edge *		separateLoop(fk_Half *H1, fk_Half *H2);

		//! ループ結合関数
		/*!
		 *	両側にループを保持する稜線 E を削除し、
		 *	両側のループを結合します。
		 *	E が両側にループを持つ稜線ではない場合は、
		 *	失敗として扱われ変形操作は行われません。
		 *
		 *	なお、この操作の逆操作は separateLoop() 関数となります。
		 *
		 *	\image html Euler05.png "separateLoop と uniteLoop"
		 *	\image latex Euler05.eps "separateLoop と uniteLoop" width=10cm
		 *	
		 *	\param[in]	E	稜線位相インスタンス
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool			uniteLoop(fk_Edge *E);

		//! 稜線分離関数
		/*!
		 *	任意稜線を分割し、新たな頂点を稜線の両端点の中点位置に生成します。
		 *
		 *	なお、この操作の逆操作は uniteEdge() 関数となります。
		 *
		 *	\image html Euler06.png "separateEdge と uniteEdge"
		 *	\image latex Euler06.eps "separateEdge と uniteEdge" width=10cm
		 *
		 *	\param[in]	E		稜線位相インスタンス
		 *
		 *	\return
		 *		成功すれば新規に生成された頂点位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 */
		fk_Vertex *		separateEdge(fk_Edge *E);

		//! 稜線結合関数
		/*!
		 *	2本の任意稜線を 1 本に結合します。
		 *	結合する稜線の間にある頂点位相 V を引数として入力します。
		 *	成功した場合は、V は削除されます。
		 *	V に接続している稜線が 2 本でなかった場合は失敗となり、形状操作は行われません。
		 *
		 *	なお、この操作の逆操作は separateEdge() 関数となります。
		 *
		 *	\image html Euler06.png "separateEdge と uniteEdge"
		 *	\image latex Euler06.eps "separateEdge と uniteEdge" width=10cm
		 *
		 *	\param[in]	V	頂点位相インスタンス
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool			uniteEdge(fk_Vertex *V);

		//! 形状反転関数
		/*!
		 *	形状全体の表裏を反転します。
		 *	内部的には、全ての稜線において半稜線の左右を入れ替えるという処理を行います。
		 *	この処理により、位相関係は以下のような状況となります。
		 *	- 関係の変わらないもの
		 *		- 頂点と半稜線の組み合わせ
		 *		- 稜線と半稜線の組み合わせ
		 *		- ループと頂点の組み合わせ
		 *		- ループと稜線の組み合わせ
		 *	- 関係が変化するもの
		 *		- ループと半稜線の組み合わせ
		 *		- 半稜線の接続
		 *	.
		 *	この操作の逆操作はこの関数自身となります。
		 */
		void			negateBody(void);

		//@}

		//! \name 履歴操作関数
		//@{

		//! 履歴保存モード設定関数
		/*!
		 *	履歴保存モードの有無効を設定します。
		 *	デフォルトでは「無効」となっており、
		 *	変形操作による履歴は保存されません。
		 *	この関数で「有効」に設定した時点から保存されます。
		 *	従って、設定を有効にする前の履歴は一切保存されないということに注意して下さい。
		 *
		 *	また、モードが有効となっている状態から無効に設定しなおしたとき、
		 *	有効時に保存されていた履歴は全て破棄されます。
		 *
		 *	\param[in]	mode
		 *		true の場合、履歴保存モードを有効とします。
		 *		false の場合は無効とします。
		 *
		 *	\sa getHistoryMode(), setHistoryMark()
		 */
		void			setHistoryMode(bool mode);

		//! 履歴保存モード参照関数
		/*!
		 *	履歴保存モードの状態を返します。
		 *	履歴保存モードについては、 setHistoryMode() の解説を参照して下さい。
		 *
		 *	\return		有効である場合 true を、無効である場合 false を返します。
		 *
		 *	\sa setHistoryMode()
		 */
		bool			getHistoryMode(void);

		//! 履歴マーク設定関数
		/*!
		 *	履歴操作を行う場合は、「マーク」というものを設定する必要があります。
		 *	このマークとは、形状の状態の「スナップショット」を保管するもので、
		 *	UNDO 操作や REDO 操作を行った際にはマークを行った時点まで戻ります。
		 *
		 *	UNDO 操作は undoHistory() 関数を、
		 *	REDO 操作は redoHistory() 関数を用います。
		 *
		 *	\sa setHistoryMode(), undoHistory(), redoHistory()
		 */
		void			setHistoryMark(void);

		//! UNDO 操作実行関数
		/*!
		 *	形状を、前に setHistoryMark() 関数によってマークした状態まで戻します。
		 *	複数回呼び出した場合は、マークした順番を逆に辿って戻していきます。
		 *	これを「UNDO 操作」と呼びます。
		 *	例えば、形状の初期状態を A、変形を進めてマークした状態を順番に
		 *	B、C、D とします。これを以下のように表記します。
		 *	アスタリスクは現時点での形状を意味します。
		 *	- A → B → C → *D
		 *	.
		 *	D の状態の形状にたいし、UNDO 操作を行うと形状は C、B、A と
		 *	順番に戻っていきます。
		 *	- A → B → C → *D
		 *	- A → B → *C → D
		 *	- A → *B → C → D
		 *	- *A → B → C → D
		 *	.
		 *	マークが以前にない状態で UNDO 操作を行った場合は、
		 *	履歴保存モードを有効にした時点まで戻ります。
		 *
		 *	戻した状態の形状を、改めて先の段階に戻す操作を「REDO 操作」と言います。
		 *	前述した例で、説明すると、D から一端 A まで戻した形状に対し、
		 *	REDO 操作を行うと B、C、D と移っていくということです。図にすると、
		 *	- *A → B → C → D
		 *	- A → *B → C → D
		 *	- A → B → *C → D
		 *	- A → B → C → *D
		 *	.
		 *	となっていくことを意味します。
		 *
		 *	ただし、UNDO 操作で戻した形状に対し、
		 *	REDO 操作以外の形状変形操作を行った場合、
		 *	先の履歴部分については破棄されてしまいます。
		 *	前述の例で説明すると、D の状態を一端 B にまで UNDO 操作で戻します。
		 *	図にすると、
		 *	- A → B → C → *D
		 *	.
		 *	この D の状態から、
		 *	- A → *B → C → D
		 *	.
		 *	この B の状態になるということです。ここで B の形状に変形操作を行うと、
		 *	C や D に至るための履歴情報が破棄されます。
		 *	- A → B → *B'
		 *	.
		 *	ただし、図にあるように B より前の履歴情報については保持されます。
		 *
		 *	\return		UNDO 操作に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa redoHistory()
		 */
		bool			undoHistory(void);

		//! REDO 操作実行関数
		/*!
		 *	UNDO 操作によって以前の状態に戻した形状に対し、
		 *	その後にマークした状態まで形状を戻します。
		 *	UNDO 操作や REDO 操作に関しての詳細は、
		 *	undoHistory() 関数の解説を参照して下さい。
		 *
		 *	\return		REDO 操作に成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa undoHistory()
		 */
		bool			redoHistory(void);
		//@}

		//! \name テセレーション制御関数
		//@{

		//! 形状全体テセレーション設定関数
		/*!
		 *	形状中の全てのループに対し、テセレーションの有無効を設定します。
		 *	この関数を呼ぶ前に行ったループ個別の設定は全て破棄されます。
		 *	テセレーションについての詳細は、
		 *	fk_Loop::setTesselateMode() 関数の解説を参照して下さい。
		 *
		 *	\param[in]	mode
		 *		true の場合、全てのループのテセレーションを有効とします。
		 *		false の場合は無効とします。
		 *
		 *	\sa fk_Loop::setTesselateMode()
		 */
		void			setTesselateMode(bool mode);

		//! 形状全体テセレーション状態参照関数
		/*!
		 *	直近の setTesselateMode() 関数による設定を返します。
		 *	これは、 setTesselateMode() によって形状全体の設定がなされた後、
		 *	fk_Loop::setTesselateMode() によって個別に有無効を設定されていた場合でも、
		 *	個別設定とは無関係です。
		 *	例えば、この関数で true が返ってきたとしても、
		 *	全てのループでテセレーションが有効となっているとは限りません。
		 *
		 *	\return		直近の setTesselateMode() 関数による設定値を返します。
		 */
		bool			getTesselateMode(void);
		//@}

#ifndef FK_DOXYGEN_USER_PROCESS
		void			PrintHistorySize(void);
#endif

	private:
		fk_History		history;
		bool			historyMode;
		bool			tesselateMode;

		fk_Loop *		SetLoop(fk_Half *, bool,
								fk_Loop * = nullptr, int = FK_UNDEFINED);
		void			UndefVNorm(fk_Vertex *);

		fk_Vertex *		MakeVertex(const fk_Vector, int);
		bool			DeleteVertex(fk_Vertex *);
		bool			MoveVertex(fk_Vertex *, fk_Vector);

		fk_Edge *		MakeEdge1(fk_Vertex *, fk_Vertex *,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED);
		fk_Edge *		MakeEdge2(fk_Vertex *, fk_Vertex *,
								  fk_Half *, fk_Half *, bool, bool,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED);
		fk_Edge *		MakeEdge3(fk_Vertex *, fk_Vertex *,
								  fk_Half *, fk_Half *,
								  fk_Half *, fk_Half *, bool, bool,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED,
								  int = FK_UNDEFINED);

		bool			DeleteEdge1(fk_Edge *);
		bool			DeleteEdge2(fk_Half *);
		bool			DeleteEdge3(fk_Edge *);

		fk_Loop *		MakeLoop(fk_Half *, int = FK_UNDEFINED);
		bool			DeleteLoop(fk_Loop *);

		fk_Edge *		SeparateLoop(fk_Half *, fk_Half *, fk_Half *, fk_Half *,
									 bool, bool,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED);

		bool			UniteLoop(fk_Edge *, fk_Half *);
		fk_Vertex *		SeparateEdge(fk_Edge *, bool, bool, bool, bool,
									 fk_Vector *,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED,
									 int = FK_UNDEFINED);

		bool			UniteEdge(fk_Vertex *);
		void			NegateBody(void);


		void			UndoCom(fk_Command *);
		void			RedoCom(fk_Command *);

		void			DeleteAllTesselateData(void);
	};
}

#endif // !__FK_OPERATION_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
