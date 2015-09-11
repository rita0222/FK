// Particle_CLI.h

#pragma once

#include <FK/Particle.h>
#include "Attribute_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{

	//! パーティクル単体を制御するクラス
	/*!
	 *	このクラスは、パーティクル集合中のパーティクル単体を制御する機能を提供します。
	 *
	 *	「パーティクル」とは粒子のことで、流体表現などに利用します。
	 *	本クラスは、インスタンスをユーザが直接生成するのではなく、
	 *	まずは fk_ParticleSet クラス(厳密にはその派生クラス)のインスタンスを用意し、
	 *	fk_ParticleSet::NewParticle() を用いてインスタンスを生成します。
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
	 *	パーティクルは、 Handle() を呼び出すか、
	 *	または fk_ParticleSet::Handle() を呼び出すことで時間経過を行い、
	 *	速度は加速度によって自動的に更新され、位置も速度によって自動的に更新されます。
	 *	ただし、上記の属性はあらゆるタイミングで変更が可能となっており、
	 * 	速度や加速度を零ベクトルに設定した上で自前で位置を制御することも可能です。
	 *
	 *	本クラスでは、あくまで個別のパーティクル情報しか得られないため、
	 *	パーティクル同士の相互作用など、他のパーティクルの情報を得ることはできません。
	 *	そのような場合は、 fk_ParticleSet の機能を利用して下さい。
	 *	また、パーティクルの消去は fk_ParticleSet::RemoveParticle() を利用して下さい。
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
	public ref class fk_Particle : fk_Attribute {
	internal:
		::fk_Particle * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Particle(bool argNewFlg);
		fk_Particle();
		~fk_Particle();
		!fk_Particle();
#endif

		//! ID プロパティ
		/*!
		 *	パーティクルの ID を参照します。
		 */
		property int ID {
			int get();
		}

		//! 年齢プロパティ
		/*!
		 *	パーティクルの年齢を参照します。
		 *	年齢とは、パーティクルが生成されてから Handle() および
		 *	fk_ParticleSet::Handle() が呼ばれた回数のことです。
		 */
		property unsigned int Count {
			unsigned int get();
		}

		//! 位置ベクトルプロパティ
		/*!
		 *	パーティクルの位置ベクトルの参照・設定を行います。
		 */
		property fk_Vector^ Position {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		//!	速度ベクトルプロパティ
		/*!
		 *	パーティクルの速度ベクトルの参照・設定を行います。
		 */
		property fk_Vector^ Velocity {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		//!	加速度ベクトルプロパティ
		/*!
		 *	パーティクルの加速度ベクトルの参照・設定を行います。
		 */
		property fk_Vector^ Accel {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		//! 色 ID プロパティ
		/*!
		 *	パーティクルの色 ID の参照・設定を行います。
		 *
		 *	\sa fk_ParticleSet::SetColorPalette()
		 */
		property int ColorID {
			int get();
			void set(int);
		}

		//! 描画有無効プロパティ
		/*!
		 *	現在の描画状態の有無を参照・設定します。
		 *	true で描画が有効、false で描画が無効となります。
		 */
		property bool DrawMode {
			bool get();
			void set(bool);
		}
		
		//! 初期化関数
		/*!
		 *	パーティクルを初期化します。
		 */
		void Init(void);

		//! 年齢更新関数
		/*!
		 *	パーティクルの年齢を更新します。
		 *	これにより、速度ベクトルには加速度ベクトルが追加され、
		 *	位置ベクトルには速度ベクトルが追加されます。
		 *	同じパーティクル集合に属する別のパーティクルには影響しません。
		 *
		 *	\sa fk_ParticleSet::Handle()
		 */
		void Handle(void);
	};
}
