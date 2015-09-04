﻿#ifndef __FK_PARTICLE_HEADER__
#define __FK_PARTICLE_HEADER__

#include <FK/Base.h>
#include <FK/Vector.h>
#include <FK/Material.h>
#include <FK/Attribute.h>

class fk_Point;
class fk_IDAdmin;
class fk_Shape;

//! パーティクル単体を制御するクラス
/*!
 *	このクラスは、パーティクル集合中のパーティクル単体を制御する機能を提供します。
 *
 *	「パーティクル」とは粒子のことで、流体表現などに利用します。
 *	本クラスは、インスタンスをユーザが直接生成するのではなく、
 *	まずは fk_ParticleSet クラス(厳密にはその派生クラス)のインスタンスを用意し、
 *	fk_ParticleSet::newParticle() を用いてインスタンスを生成します。
 *
 *	個々のパーティクルは、以下のような属性を持っています。
 *	- ID番号
 *	- 位置
 *	- 速度
 *	- 加速度
 *	- 年齢
 *	- 色インデックス
 *	- 描画有無属性
 *	.
 *	パーティクルは、 handle() を呼び出すか、
 *	または fk_ParticleSet::handle() を呼び出すことで時間経過を行い、
 *	速度は加速度によって自動的に更新され、位置も速度によって自動的に更新されます。
 *	ただし、上記の属性はあらゆるタイミングで変更が可能となっており、
 * 	速度や加速度を零ベクトルに設定した上で自前で位置を制御することも可能です。
 *
 *	本クラスでは、あくまで個別のパーティクル情報しか得られないため、
 *	パーティクル同士の相互作用など、他のパーティクルの情報を得ることはできません。
 *	そのような場合は、 fk_ParticleSet の機能を利用して下さい。
 *	また、パーティクルの消去は fk_ParticleSet::removeParticle() を利用して下さい。
 *
 *	fk_Particle クラスは fk_Attribute クラスの派生クラスですので、
 *	パーティクルに対し独自の属性や情報を個別に持たせたい場合は、
 *	fk_Attribute の機能を利用することができます。
 *
 *	このクラスと同様に点群を扱うクラスとして、 fk_Point があります。
 *	fk_Particle や fk_ParticleSet が法則を記述することが主であることに対し、
 *	fk_Point では点の制御をより直接的に行います。
 *
 *	\sa fk_ParticleSet, fk_Attribute, fk_Point
 */

class fk_Particle: public fk_Attribute {

 private:
	int				id;			// 頂点 ID 
	fk_Point		*base;		// 全体位相 
	unsigned int	count;		// 年齢 
	fk_Vector		velocity;	// 速度 
	fk_Vector		accel;		// 加速度 

 public:
#ifndef FK_DOXYGEN_USER_PROCESS

	fk_Particle(fk_Point *, int);
	virtual ~fk_Particle();

#endif

	//! 初期化関数
	/*!
	 *	パーティクルを初期化します。
	 */
	void			init(void);

	//! ID参照関数
	/*!
	 *	パーティクルの ID を参照します。
	 *
	 *	\return		ID番号
	 */
	int				getID(void) const;

	//! 年齢参照関数
	/*!
	 *	パーティクルの年齢を参照します。
	 *	年齢とは、パーティクルが生成されてから handle() および
	 *	fk_ParticleSet::handle() が呼ばれた回数のことです。
	 *
	 *	\return		年齢
	 */
	unsigned int	getCount(void) const;

	//! 位置ベクトル参照設定 
	/*!
	 *	パーティクルの位置ベクトルを参照します。
	 *
	 *	\return		位置ベクトル
	 */
	fk_Vector		getPosition(void) const;

	//! 位置ベクトル設定関数1
	/*!
	 *	パーティクルの位置ベクトルを設定します。
	 *
	 *	\param[in]	pos		位置ベクトル
	 */
	void			setPosition(const fk_Vector &pos);

	//! 位置ベクトル設定関数2
	/*!
	 *	パーティクルの位置ベクトルを設定します。
	 *
	 *	\param[in]	x		位置ベクトルのx成分
	 *	\param[in]	y		位置ベクトルのy成分
	 *	\param[in]	z		位置ベクトルのz成分
	 */
	void			setPosition(double x, double y, double z);

	//!	速度ベクトル参照設定 
	/*!
	 *	パーティクルの速度ベクトルを参照します。
	 *
	 *	\return		速度ベクトル
	 */
	fk_Vector		getVelocity(void) const;

	//! 速度ベクトル設定関数1
	/*!
	 *	パーティクルの速度ベクトルを設定します。
	 *
	 *	\param[in]	vel		速度ベクトル
	 */
	void			setVelocity(const fk_Vector &vel);

	//! 速度ベクトル設定関数2
	/*!
	 *	パーティクルの速度ベクトルを設定します。
	 *
	 *	\param[in]	x		速度ベクトルのx成分
	 *	\param[in]	y		速度ベクトルのy成分
	 *	\param[in]	z		速度ベクトルのz成分
	 */
	void			setVelocity(double x, double y, double z);

	//!	加速度ベクトル参照設定 
	/*!
	 *	パーティクルの加速度ベクトルを参照します。
	 *
	 *	\return		加速度ベクトル
	 */
	fk_Vector		getAccel(void) const;

	//! 加速度ベクトル設定関数1
	/*!
	 *	パーティクルの加速度ベクトルを設定します。
	 *
	 *	\param[in]	acc		加速度ベクトル
	 */
	void			setAccel(const fk_Vector &acc);

	//! 加速度ベクトル設定関数2
	/*!
	 *	パーティクルの加速度ベクトルを設定します。
	 *
	 *	\param[in]	x		加速度ベクトルのx成分
	 *	\param[in]	y		加速度ベクトルのy成分
	 *	\param[in]	z		加速度ベクトルのz成分
	 */
	void			setAccel(double x, double y, double z);

	//! 色 ID 参照関数
	/*!
	 *	パーティクルの色 ID を参照します。
	 *
	 *	\return		色 ID
	 *
	 *	\sa fk_ParticleSet::setColorPalette()
	 */
	int				getColorID(void) const;

	//! 色 ID 設定関数
	/*!
	 *	パーティクルの色 ID を設定します。
	 *
	 *	\param[in]	ID		色 ID
	 *
	 *	\sa fk_ParticleSet::setColorPalette()
	 */
	void			setColorID(int ID);

	//! 描画有無効参照関数
	/*!
	 *	現在の描画状態の有無を参照します。
	 *
	 *	\return
	 *		描画が有効である場合 true を、
	 *		無効となっている場合 false を返します。
	 */
	bool			getDrawMode(void) const;

	//! 描画有無効設定関数
	/*!
	 *	現在の描画状態の有無を設定します。
	 *
	 *	\param[in]	mode
	 *		true の場合、描画を有効とします。false の場合無効とします。
	 */
	void			setDrawMode(bool mode);

	//! 年齢更新関数
	/*!
	 *	パーティクルの年齢を更新します。
	 *	これにより、速度ベクトルには加速度ベクトルが追加され、
	 *	位置ベクトルには速度ベクトルが追加されます。
	 *	同じパーティクル集合に属する別のパーティクルには影響しません。
	 *
	 *	\sa fk_ParticleSet::handle()
	 */
	void			handle(void);
};

//! パーティクル集合を制御するクラス
/*!
 *	このクラスは、パーティクル集合を制御する機能を提供します。
 *
 *	「パーティクル」とは粒子のことで、流体表現などに利用します。
 *	本クラスは、そのままインスタンスを生成して利用するのではなく、
 *	このクラスの継承クラスに対して仮想関数を上書きして利用することを想定しています。
 *	具体的には、以下のような手順となります。
 *	-# まず fk_ParticleSet を継承したクラスを準備します。
 *	-# そのクラスで、各種仮想関数の上書きによってパーティクルの挙動を記述します。
 *	-# 新しいクラスのインスタンスを作成し、
 *		getShape() を使ってモデルに登録しておきます。
 *		もちろん、そのモデルはシーンに登録しておく必要があります。
 *	-# 描画ループの中で handle() を呼び出す。
 *	.
 *	このクラスと同様に点群を扱うクラスとして、 fk_Point があります。
 *	fk_Particle や fk_ParticleSet が法則を記述することが主であることに対し、
 *	fk_Point では点の制御をより直接的に行います。
 *
 *	\sa fk_Particle, fk_Point
 */

class fk_ParticleSet: public fk_BaseObject {

 private:
	std::vector<fk_Particle *>	pSet;
	fk_IDAdmin					*pAdmin;
	fk_Point					*point;
	unsigned int				count;
	bool						allMode, indivMode;
	unsigned int				maxNum;

 public:
	//! コンストラクタ
	/*!
	 *	初期値として、パーティクル最大個数をとります。
	 *
	 *	\param[in]	max		パーティクル最大個数
	 */
	fk_ParticleSet(unsigned int max = 0);

	//! デストラクタ
	virtual ~fk_ParticleSet();

	//! 実行関数
	/*!
	 *	パーティクル集合および各パーティクルに対し、時間経過処理を実行します。
	 *	具体的には、以下の処理が行われます。
	 *	- 各パーティクルの fk_Particle::handle() 実行。
	 *	- パーティクル集合および各パーティクルの年齢に 1 を追加。
	 */
	void			handle(void);

	//! モデル設定用関数
	/*!
	 *	モデルに形状を設定するための関数です。
	 *
	 *	\return		形状インスタンス
	 *
	 *	\note
	 *		現時点では、この形状インスタンスの型は fk_Point になっています。
	 *		しかし、将来においてはこの型が変更となる可能性があります。
	 *		この関数で得られるインスタンスが
	 *		fk_Point であることを前提とするような記述を行った場合、
	 *		将来のバージョンにおいて問題が生じる可能性があります。
	 */
	fk_Shape *		getShape(void) const;

	//! パーティクル生成関数1
	/*!
	 *	パーティクルを原点上に新たに生成します。
	 *	ただし、既にパーティクル数が設定した最大値に達していた場合は、
	 *	生成を行いません。
	 *
	 *	\return
	 *		生成した場合、新たなパーティクルのインスタンスを返します。
	 *		失敗した場合は nullptr を返します。
	 */
	fk_Particle *	newParticle(void);

	//! パーティクル生成関数2
	/*!
	 *	パーティクルを指定した位置ベクトルの場所に新たに生成します。
	 *	ただし、既にパーティクル数が設定した最大値に達していた場合は、
	 *	生成を行いません。
	 *
	 *	\param[in]	pos		生成場所の位置ベクトル
	 *
	 *	\return
	 *		生成した場合、新たなパーティクルのインスタンスを返します。
	 *		失敗した場合は nullptr を返します。
	 */
	fk_Particle *	newParticle(const fk_Vector &pos);

	//! パーティクル生成関数3
	/*!
	 *	パーティクルを指定した位置ベクトルの場所に新たに生成します。
	 *	ただし、既にパーティクル数が設定した最大値に達していた場合は、
	 *	生成を行いません。
	 *
	 *	\param[in]	x		生成場所の位置ベクトルのx成分
	 *	\param[in]	y		生成場所の位置ベクトルのy成分
	 *	\param[in]	z		生成場所の位置ベクトルのz成分
	 *
	 *	\return
	 *		生成した場合、新たなパーティクルのインスタンスを返します。
	 *		失敗した場合は nullptr を返します。
	 */
	fk_Particle *	newParticle(double x, double y, double z);

	//! パーティクル削除関数1
	/*!
	 *	指定したパーティクルを削除します。
	 *	削除したパーティクルが持っていた ID は、
	 *	新たに生成したパーティクルで再利用します。
	 *
	 *	\param[in]	p		削除パーティクル
	 *
	 *	\return		削除に成功すれば true を、失敗すれば false を返します。
	 */
	bool			removeParticle(fk_Particle *p);

	//! パーティクル削除関数2
	/*!
	 *	指定した ID を持つパーティクルを削除します。
	 *	削除したパーティクルが持っていた ID は、
	 *	新たに生成したパーティクルで再利用します。
	 *
	 *	\param[in]	ID		削除パーティクル ID
	 *
	 *	\return		削除に成功すれば true を、失敗すれば false を返します。
	 */
	bool			removeParticle(int ID);

	//! 年齢参照関数
	/*!
	 *	パーティクル集合の年齢を参照します。
	 *	年齢とは、パーティクル集合が生成されてから
	 *	handle() が呼ばれた回数のことです。
	 *
	 *	\return		年齢
	 */
	unsigned int	getCount(void) const;

	//! パーティクルインスタンス参照関数
	/*!
	 *	指定した ID を持つパーティクルインスタンスを返します。
	 *
	 *	\param[in]	ID	パーティクルID
	 *
	 *	\return 存在した場合はインスタンスを、存在しない場合は nullptr を返します。
	 */
	fk_Particle *	getParticle(int ID) const;

	//! パーティクルインスタンス順次取得取得
	/*!
	 *	存在しているパーティクルを順次取得するのに利用していきます。
	 *	引数と返値は、以下のような関係を持ちます。
	 *	- 引数が nullptr の場合は、IDが最も小さなパーティクルを返します。
	 *	- 引数のパーティクルに対し、次の大きな ID を持つパーティクルを返します。
	 *	- もし引数のパーティクルの ID が最大のものであった場合は、
	 *		nullptr を返します。
	 *	.
	 *	以下のソースコードは、
	 *	allMethod() の中で全てのパーティクルの総和平均座標を求めているものです。
	 *	ここで、「MyPaticleSet」は fk_ParticleSet クラスを派生したものとします。
	 *
	 *		void MyParticleSet::allMethod(void)
	 *		{
	 *			fk_Particle  *p;
	 *			fk_Vector    vec(0.0, 0.0, 0.0);
	 *			
	 *			p = getNextParticle(nullptr);
	 *			while(p != nullptr) {
	 *				vec += p->getPosition();
	 *				p = getNextParticle(p);
	 *			}
	 *			vec /= double(getParticleNum());
	 *		}
	 *
	 *	\param[in]	p	パーティクルインスタンス
	 *
	 *	\return		上記解説を参照して下さい。
	 */
	fk_Particle *	getNextParticle(fk_Particle *p) const;

	//! パーティクル個数参照関数
	/*!
	 *	現在生存しているパーティクルの個数を返します。
	 *
	 *	\return		パーティクル個数
	 */
	unsigned int	getParticleNum(void) const;

	//! パーティクル最大個数設定関数
	/*!
	 *	パーティクル集合における、パーティクル個数の最大値を設定します。
	 *	もし生存数がこの個数に達した場合、
	 *	newParticle() を呼び出しても生成を行いません。
	 *	0 の場合無制限となります。デフォルトは 0 です。
	 *
	 *	\param[in]	max		最大個数
	 */
	void			setMaxSize(unsigned int max);

	//! パーティクル最大個数参照関数
	/*!
	 *	パーティクル集合における、パーティクル個数の最大値を参照します。
	 *	もし生存数がこの個数に達した場合、
	 *	newParticle() を呼び出しても生成を行いません。
	 *	0 の場合無制限となります。デフォルトは 0 です。
	 *
	 *	\return		最大個数
	 */
	unsigned int	getMaxSize(void) const;

	//! カラーパレット設定1
	/*!
	 *	パーティクル集合内のカラーパレットに色を設定します。
	 *	ここで設定した色をパーティクルに反映するには、
	 *	fk_Particle::setColorID() を用います。
	 *
	 *	\note
	 *		既にパーティクルに色 ID が設定されている状態で、
	 *		カラーパレット側の色を変更した場合、
	 *		パーティクルの色に即座に反映されます。
	 *
	 *	\param[in]	ID		色ID
	 *	\param[in]	col		色
	 */
	void			setColorPalette(int ID, const fk_Color &col);

	//! カラーパレット設定2
	/*!
	 *	パーティクル集合内のカラーパレットに色を設定します。
	 *	色成分の最小値は 0、最大値は 1 です。
	 *	ここで設定した色をパーティクルに反映するには、
	 *	fk_Particle::setColorID() を用います。
	 *
	 *	\note
	 *		既にパーティクルに色 ID が設定されている状態で、
	 *		カラーパレット側の色を変更した場合、
	 *		パーティクルの色に即座に反映されます。
	 *
	 *	\param[in]	ID		色ID
	 *	\param[in]	R		色のR(赤)成分
	 *	\param[in]	G		色のG(緑)成分
	 *	\param[in]	B		色のB(青)成分
	 */
	void			setColorPalette(int ID, float R, float G, float B);

	//! カラーパレット設定3
	/*!
	 *	パーティクル集合内のカラーパレットに色を設定します。
	 *	色成分の最小値は 0、最大値は 1 です。
	 *	ここで設定した色をパーティクルに反映するには、
	 *	fk_Particle::setColorID() を用います。
	 *
	 *	\note
	 *		既にパーティクルに色 ID が設定されている状態で、
	 *		カラーパレット側の色を変更した場合、
	 *		パーティクルの色に即座に反映されます。
	 *
	 *	\param[in]	ID		色ID
	 *	\param[in]	R		色のR(赤)成分
	 *	\param[in]	G		色のG(緑)成分
	 *	\param[in]	B		色のB(青)成分
	 */
	void			setColorPalette(int ID, double R, double G, double B);

	//! 個別初期化用仮想関数
	/*!
	 *	この関数は、 newParticle() によってパーティクルが生成されたときに、
	 *	自動的に実行されます。
	 *	初期状態としては特に何も行いませんが、
	 *	この関数を上書き定義することによって、
	 *	パーティクル生成時にそのパーティクルに対して様々な制御を行うことができます。
	 *
	 *	\param[in]	p		新たに生成されたパーティクルインスタンス
	 */
	virtual void	genMethod(fk_Particle *p);

	//! 全体動作用仮想関数
	/*!
	 *	この関数は、 handle() が呼び出された時点で自動的に実行されます。
	 *	(ただし、 setAllMode() で false が設定されている場合は呼び出されません。)
	 *	初期状態としては何も行いませんが、
	 *	この関数を上書き定義することによって、
	 *	パーティクル集合に対して様々な制御を行うことができます。
	 */
	virtual void	allMethod(void);

	//! 個別動作用仮想関数
	/*!
	 *	この関数は、 handle() が呼び出された時点で、
	 *	各パーティクル個別に自動的に実行されます。
	 *	(ただし、 setIndivMode() で false が設定されている場合は呼び出されません。)
	 *	初期状態としては何も行いませんが、
	 *	この関数を上書き定義することによって、
	 *	各パーティクルに対して様々な制御を行うことができます。
	 *
	 *	\param[in]	p		個別パーティクルインスタンス
	 */
	virtual void	indivMethod(fk_Particle *p);

	//! 全体動作モード設定関数
	/*!
	 *	handle() 呼び出し時の、 allMethod() の自動実行を制御します。
	 *	デフォルトでは true となっています。
	 *
	 *	\param[in]	mode
	 *		true の場合は allMethod() の自動実行を行います。
	 *		false の場合は行いません。
	 */
	void			setAllMode(bool mode);

	//! 全体動作モード参照関数
	/*!
	 *	handle() 呼び出し時の、 allMethod() の自動実行状態を参照します。
	 *
	 *	\return
	 *		true の場合は allMethod() の自動実行を行います。
	 *		false の場合は行いません。
	 */
	bool			getAllMode(void) const;

	//! 個別動作モード設定関数
	/*!
	 *	handle() 呼び出し時の、 indivMethod() の自動実行を制御します。
	 *	デフォルトでは true となっています。
	 *
	 *	\param[in]	mode
	 *		true の場合は indivMethod() の自動実行を行います。
	 *		false の場合は行いません。
	 */
	void			setIndivMode(bool mode);

	//! 個別動作モード参照関数
	/*!
	 *	handle() 呼び出し時の、 indivMethod() の自動実行状態を参照します。
	 *
	 *	\return
	 *		true の場合は indivMethod() の自動実行を行います。
	 *		false の場合は行いません。
	 */
	bool			getIndivMode(void) const;
};

#endif // !__FK_PARTICLE_HEADER__

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
