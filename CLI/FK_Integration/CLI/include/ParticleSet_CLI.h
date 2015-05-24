// Particle_CLI.h

#pragma once

#include <FK/Particle.h>
#include "Particle_CLI.h"
#include "Material_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{

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
	 *	-# 新しいクラスのインスタンスを作成し、以下のようなコードでモデルに登録します。
	 *
	 *			// fk_ParticleSet を継承した MyParticleSet クラスを事前に準備
	 *			MyParticleSet	pSet = new MyParticleSet();
	 *			fk_Model		mode = new fk_Model();
	 *
	 *			model.Shape = pSet.Shape;
	 *
	 *		もちろん、そのモデルはシーンに登録しておく必要があります。
	 *	-# 描画ループの中で Handle() を呼び出す。
	 *	.
	 *	このクラスと同様に点群を扱うクラスとして、 fk_Point があります。
	 *	fk_Particle や fk_ParticleSet が法則を記述することが主であることに対し、
	 *	fk_Point では点の制御をより直接的に行います。
	 *
	 *	\sa fk_Particle, fk_Point
	 */
	public ref class fk_ParticleSet : fk_BaseObject {
	internal:
		::fk_ParticleSet * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_ParticleSet(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_ParticleSet();

		//! デストラクタ
		~fk_ParticleSet();

		//! ファイナライザ
		!fk_ParticleSet();

		//! モデル設定用プロパティ
		/*!
		 *	モデルに形状を設定するためのプロパティです。
		 *
		 *	\note
		 *		現時点では、この形状インスタンスの型は fk_Point になっています。
		 *		しかし、将来においてはこの型が変更となる可能性があります。
		 *		この関数で得られるインスタンスが
		 *		fk_Point であることを前提とするような記述を行った場合、
		 *		将来のバージョンにおいて問題が生じる可能性があります。
		 */
		property fk_Shape^ Shape {
			fk_Shape^ get();
		}

		//! 年齢プロパティ
		/*!
		 *	パーティクル集合の年齢を参照します。
		 *	年齢とは、パーティクル集合が生成されてから
		 *	Handle() が呼ばれた回数のことです。
		 *
		 *	\note
		 *		個別のパーティクルで呼ばれた fk_Particle::Handle() はカウントしません。
		 */
		property unsigned int Count {
			unsigned int get();
		}

		//! パーティクル個数プロパティ
		/*!
		 *	現在生存しているパーティクルの個数を参照します。
		 */
		property unsigned int ParticleNum {
			unsigned int get();
		}

		//! パーティクル最大個数プロパティ
		/*!
		 *	パーティクル集合における、パーティクル個数の最大値の参照・設定を行います。
		 *	もし生存数がこの個数に達した場合、
		 *	NewParticle() を呼び出しても生成を行いません。
		 *	0 の場合無制限となります。デフォルトは 0 です。
		 */
		property unsigned int MaxSize {
			unsigned int get();
			void set(unsigned int);
		}

		//! 全体動作モードプロパティ
		/*!
		 *	Handle() 呼び出し時の、 AllMethod() の自動実行を制御します。
		 *	true の場合は AllMethod() の自動実行を行います。
		 *	false の場合は行いません。
		 *	デフォルトでは true となっています。
		 */
		property bool AllMode {
			bool get();
			void set(bool);
		}
		
		//! 個別動作モードプロパティ
		/*!
		 *	handle() 呼び出し時の、 IndivMethod() の自動実行を制御します。
		 *	true の場合は IndivMethod() の自動実行を行います。
		 *	false の場合は行いません。
		 *	デフォルトでは true となっています。
		 */
		property bool IndivMode {
			bool get();
			void set(bool);
		}

		//! 実行関数
		/*!
		 *	パーティクル集合および各パーティクルに対し、時間経過処理を実行します。
		 *	具体的には、以下の処理が行われます。
		 *	- 各パーティクルの fk_Particle::Handle() 実行。
		 *	- パーティクル集合および各パーティクルの年齢に 1 を追加。
		 */
		void Handle(void);

		//! パーティクル生成関数1
		/*!
		 *	パーティクルを原点上に新たに生成します。
		 *	ただし、既にパーティクル数が設定した最大値に達していた場合は、
		 *	生成を行いません。
		 *
		 *	\return
		 *		生成した場合、新たなパーティクルのインスタンスを返します。
		 *		失敗した場合は null を返します。
		 */
		fk_Particle^ NewParticle(void);

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
		 *		失敗した場合は null を返します。
		 */
		fk_Particle^ NewParticle(fk_Vector^ pos);

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
		fk_Particle^ NewParticle(double x, double y, double z);

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
		bool RemoveParticle(fk_Particle ^p);

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
		bool RemoveParticle(int ID);

		//! パーティクルインスタンス参照関数
		/*!
		 *	指定した ID を持つパーティクルインスタンスを返します。
		 *
		 *	\param[in]	ID	パーティクルID
		 *
		 *	\return 存在した場合はインスタンスを、存在しない場合は nullptr を返します。
		 */
		fk_Particle^ GetParticle(int ID);

		//! パーティクルインスタンス順次取得取得
		/*!
		 *	存在しているパーティクルを順次取得するのに利用していきます。
		 *	引数と返値は、以下のような関係を持ちます。
		 *	- 引数が null の場合は、IDが最も小さなパーティクルを返します。
		 *	- 引数のパーティクルに対し、次の大きな ID を持つパーティクルを返します。
		 *	- もし引数のパーティクルの ID が最大のものであった場合は、
		 *		null を返します。
		 *	.
		 *	以下のソースコードは、
		 *	AllMethod() の中で全てのパーティクルの総和平均座標を求めているものです。
		 *	ここで、「MyPaticleSet」は fk_ParticleSet クラスを派生したものとします。
		 *
		 *		void MyParticleSet::AllMethod(void)
		 *		{
		 *			fk_Particle  p;
		 *			fk_Vector    vec = new fk_Vector();
		 *			
		 *			p = GetNextParticle(null);
		 *			while(p != null) {
		 *				vec += p->GetPosition();
		 *				p = GetNextParticle(p);
		 *			}
		 *			vec /= double(getParticleNum());
		 *		}
		 *
		 *	\param[in]	p	パーティクルインスタンス
		 *
		 *	\return		上記解説を参照して下さい。
		 */
		fk_Particle^ GetNextParticle(fk_Particle^ p);

		//! カラーパレット設定1
		/*!
		 *	パーティクル集合内のカラーパレットに色を設定します。
		 *	ここで設定した色をパーティクルに反映するには、
		 *	fk_Particle::SetColorID() を用います。
		 *
		 *	\note
		 *		既にパーティクルに色 ID が設定されている状態で、
		 *		カラーパレット側の色を変更した場合、
		 *		パーティクルの色に即座に反映されます。
		 *
		 *	\param[in]	ID		色ID
		 *	\param[in]	col		色
		 */
		void SetColorPalette(int ID, fk_Color^ col);

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
		void SetColorPalette(int ID, float R, float G, float B);

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
		void SetColorPalette(int ID, double R, double G, double B);

		//! 個別初期化用仮想関数
		/*!
		 *	この関数は、 NewParticle() によってパーティクルが生成されたときに、
		 *	自動的に実行されます。
		 *	初期状態としては特に何も行いませんが、
		 *	この関数を上書き定義することによって、
		 *	パーティクル生成時にそのパーティクルに対して様々な制御を行うことができます。
		 *
		 *	\param[in]	p		新たに生成されたパーティクルインスタンス
		 */
		virtual void GenMethod(fk_Particle^ p);

		//! 全体動作用仮想関数
		/*!
		 *	この関数は、 Handle() が呼び出された時点で自動的に実行されます。
		 *	(ただし、 fk_ParticleSet::AllMode プロパティで
		 *	false が設定されている場合は呼び出されません。)
		 *	初期状態としては何も行いませんが、
		 *	この関数を上書き定義することによって、
		 *	パーティクル集合に対して様々な制御を行うことができます。
		 */
		virtual void AllMethod(void);

		//! 個別動作用仮想関数
		/*!
		 *	この関数は、 Handle() が呼び出された時点で、
		 *	各パーティクル個別に自動的に実行されます。
		 *	(ただし、 fk_ParticleSet::IndivMode プロパティで
		 *	false が設定されている場合は呼び出されません。)
		 *	初期状態としては何も行いませんが、
		 *	この関数を上書き定義することによって、
		 *	各パーティクルに対して様々な制御を行うことができます。
		 *
		 *	\param[in]	p		個別パーティクルインスタンス
		 */
		virtual void IndivMethod(fk_Particle^ p);
	};
}
