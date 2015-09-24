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
