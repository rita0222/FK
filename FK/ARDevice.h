#ifndef __FK_AR_DEVICE_HEADER__
#define __FK_AR_DEVICE_HEADER__

#include <map>
#include <FK/Model.h>
#include <FK/ARTexture.h>
#include <FK/Projection.h>
#include <AR/ar.h>
#include <AR/config.h>
#include <AR/param.h>
#include <AR/gsub.h>
#include <AR/video.h>

namespace FK {

	//! ARの状態を表す列挙型
	enum fk_AR_Device_Status {
		FK_AR_IMAGE_NULL,		//!< 画像未設定
		FK_AR_DETECT_ERROR,		//!< 検出エラー
		FK_AR_NO_DETECT,		//!< 未検出
		FK_AR_DETECT			//!< 検出成功
	};

#ifndef FK_DOXYGEN_USER_PROCESS
	
	class fk_ARPattern {
	public:
		std::string		name;
		int				id;
		double			width;
		double			transMat[3][4];
		fk_Model		*model;
		bool			contFlg;

		fk_ARPattern(void);
		~fk_ARPattern();
	};

#endif

	//! AR カメラデバイス用クラス
	/*!
	 *	このクラスは、AR利用でのカメラデバイスを制御するためのクラスです。
	 *	FK では、AR 用システムとして内部で ARToolKit を用いており、
	 *	各種の設定ファイルフォーマットは ARToolKit に準拠します。
	 *	ARToolKit についての詳細は、以下の URL を参照して下さい。
	 *	https://sourceforge.net/projects/artoolkit/
	 *
	 *	\sa fk_ARTexture
	 */

	class fk_ARDevice {

	private:
		std::string					vconf;
		int							videoXSize, videoYSize;
		int							thresh;

		std::vector<fk_ARPattern>	pat_array;
		std::map<int, int>			pat_map;

		ARParam			cparam;
		ARParamLT		*paramLT;
		ARPattHandle	*patHandle;
		ARHandle		*handle;
		AR3DHandle		*handle3D;
		AR_PIXEL_FORMAT	pixelFormat;

		std::string		cparam_name;
		fk_Matrix		cparam_mat;
	
		bool			contFlag, startFlag;

		void		CameraInit(void);
		void		CameraInit1(void);
		void		ConvARCMat(double, double);
		void		SetARCam(fk_Model *);
		void		ConvARModelR(fk_Matrix, fk_Model *);
		void		ConvARModelT(fk_Matrix, fk_Model *);
		void		SetMarkerModel(int, fk_Model *);
		int			GetID(int);
		int			CreatePattern(int);
		fk_PixelFormatType	ConvFormat(AR_PIXEL_FORMAT);

	public:

		//! コンストラクタ
		fk_ARDevice(void);

		//! デストラクタ
		~fk_ARDevice();

		//! 設定ファイル名設定関数
		/*!
		 *	AR 用の設定ファイル名を設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 */
		void		setConfigFile(std::string fileName);

		//! カメラパラメータファイル名設定関数
		/*!
		 *	AR 用カメラパラメータファイル名を設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 */
		void		setCameraParamFile(std::string fileName);

		//!	閾値設定関数
		/*!
		 *	検出の際の2値化処理の際の閾値を設定します。
		 *	検出精度が悪い場合、この値を変更することによって精度が向上する可能性があります。
		 *	値は、完全な黒が 0, 完全な白が 255 となります。
		 *	デフォルトでは 100 に設定されています。
		 *
		 *	\param[in]	th	閾値
		 */
		void		setThresh(int th);

		//!	閾値取得関数
		/*!
		 *	検出の際の2値化処理の際の閾値を取得します。
		 *	値は、完全な黒が 0, 完全な白が 255 となります。
		 *
		 *	\return	閾値
		 */
		int			getThresh(void);

		//! マーカー用パターンファイル設定関数1
		/*!
		 *	マーカー用のファイルを設定します。
		 *	マーカー用データのフォーマットは ARToolKit のマニュアルを参照して下さい。
		 *	なお、この関数を用いた場合、マーカーの内部 ID は自動的に 0 番となります。
		 *
		 *	\param[in]	fileName	パターンファイル名
		 */
		void		setPatternFile(std::string fileName);

		//! マーカー用パターンファイル設定関数2
		/*!
		 *	マーカー用のファイルを設定します。
		 *	マーカー用データのフォーマットは ARToolKit のマニュアルを参照して下さい。
		 *	本クラスでは、複数のマーカーを同時に登録することが可能で、
		 * 	その場合は id を別々にして登録を行って下さい。
		 *
		 *	\param[in]	id			マーカー ID
		 *	\param[in]	fileName	マーカーファイル名
		 */
		void		setPatternFile(int id, std::string fileName);

		//! マーカー実寸設定関数
		/*!
		 *	マーカーの実寸を指定します。
		 *	この値が適切に設定されていないと、検出の精度が悪くなる、
		 *	誤検出が多くなるなどの問題が生じる場合があります。
		 *	単位はミリメートルとなります。デフォルトは 80 に設定されています。
		 *
		 *	\param[in]	id		マーカー ID
		 *	\param[in]	width	マーカー実寸幅
		 */
		void		setPatternWidth(int id, double width);

		//! マーカー連動モデル設定関数
		/*!
		 *	カメラ映像中のマーカーと連動するモデルを設定します。
		 *	一つのマーカーに同時に複数のモデルを設定することはできません。
		 *	複数モデルを同時に連動させたい場合は、親子関係を用いて下さい。
		 *
		 *	\param[in]	id		マーカー ID
		 *	\param[in]	model	連動モデル
		 */
		void		setPatternModel(int id, fk_Model *model);

		//! カメラデバイス初期化関数
		/*!
		 *	カメラデバイスを初期化します。
		 *	AR を利用する際には必ず最初に一回実行して下さい。
		 */
		bool		deviceInit(void);

		//! カメラ投影設定関数
		/*!
		 *	初期化を行った後、投影情報の取得と設定を行います。
		 *	ここで得られた投資情報は、 fk_DisplayLink::setProjection() によって
		 *	FK 内のシーンに反映する必要があります。
		 *	なお、投影情報に関する詳細は fk_Frustum の説明を参照して下さい。
		 *
		 *	\param[in]	near		クリッピング近距離面への距離
		 *	\param[in]	far			クリッピング遠距離面への距離
		 *	\param[out]	proj		カメラから取得した一般投資投影情報
		 *	\param[in]	texture		AR投影映像用テクスチャ
		 *	\param[in]	video		AR投影映像用モデル
		 *	\param[in]	camera		カメラ用モデル
		 */
		void		makeProject(double near, double far, fk_Frustum *proj,
								fk_ARTexture *texture, fk_Model *video, fk_Model *camera);

		//! カメラ映像反映関数
		/*!
		 *	現在のカメラ映像の状態から、映像テクスチャの更新およびマーカーからの
		 *	モデル位置・姿勢への反映を行います。
		 *	事前に setPatternModel() で設定していた各モデルは、
		 *	マーカーの位置により自動的に位置・姿勢の変更が行われます。
		 *
		 *	\param[in]	texture		AR投影映像用テクスチャ
		 *
		 *	\return		現在のカメラデバイスの状況を返します。
		 */
		fk_AR_Device_Status		update(fk_ARTexture *texture);

		//! 検出状況参照関数
		/*!
		 *	setPatternFile() によって設定した各マーカーが、
		 *	現時点で検出に成功しているかどうかの判定結果を返します。
		 *
		 *	\param[in]	id		マーカー ID
		 *
		 *	\return		検出に成功していれば true を、失敗していれば false を返します。
		 */
		bool		getModelDetect(int id);
	};
}

#endif	//	!__FK_AR_DEVICE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
