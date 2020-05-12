using System;
using FK_CLI;

namespace FK_CLI_Ball
{
	public class Ball
	{
		private const double DOWN_ACCEL		= 0.050;	// 降下時の加速度
		private const double RISE_ACCEL		= 0.053;	// 上昇時の減速度
		private const int	 DOWN_MODE		= 0;		// 降下モード
		private const int	 RISE_MODE		= 1;		// 上昇モード
		private const int	 LOD4_HIGH		= 200;		// 四分割距離 (鳥瞰)
		private const int	 LOD3_HIGH		= 300;		// 三分割距離 (鳥瞰)
		private const int	 LOD4_LOW		= 90;		// 四分割距離 (ブロック)
		private const int	 LOD3_LOW		= 120;		// 三分割距離 (ブロック)
		private const double TOP_BALL_POS	= 400.0;	// ボール始点高さ
		private const double BTM_BALL_POS	= 12.0;		// ボール跳ね返り高さ
		private const double BALL_SIZE		= 12.0;     // ボール半径
        private const int	 BOUND_CYCLE	= 6;        // 繰り返しあたりのバウンド回数
        private const int	 VIEW_CHANGE	= 4;        // 視点変更タイミング

        private int direction;       // ボールの状態(DOWN_MODE or RISE_MODE)
        private int	view_mode;		 // 視点モード
		private int	bound_count;	 // バウンド回数を数える変数
		private double y_trs;        // ボールのｙ座標移動量
		private fk_Sphere ball_2;	 // 2分割形状
		private fk_Sphere ball_3;	 // 3分割形状
		private fk_Sphere ball_4;	 // 4分割形状

		public const int LOW_MODE			= 0;		// ブロック視点モード
		public const int HIGH_MODE			= 1;		// 鳥瞰モード
        public const double ROTATE_SPEED	= 0.02;     // 回転速度


        public Ball()
		{
			ball_2 = new fk_Sphere(6, BALL_SIZE);
			ball_3 = new fk_Sphere(8, BALL_SIZE);
			ball_4 = new fk_Sphere(10, BALL_SIZE);
			Model = new fk_Model();
			Init();
		}

		public void Init()
		{
			direction	= DOWN_MODE;
			y_trs		= 0.0;
			view_mode	= HIGH_MODE;
			bound_count	= 1;
			Model.GlMoveTo(0.0, TOP_BALL_POS, 0.0);
			Model.Shape = ball_2;

            Model.Material = fk_Material.Red;
            Model.Material.Specular = new fk_Color(1.0, 1.0, 1.0);
            Model.Material.Shininess = 100.0f;
            Model.SmoothMode = true;
			Model.ShadowDraw = false;
        }

 
        public fk_Vector Pos
		{
			get
			{
				return Model.Position;
			}
		}

		public fk_Model Model { get; }

		public void LOD(fk_Vector argPos)
		{
			double	Distance = (Model.Position - argPos).Dist();
			switch(view_mode) {
				case HIGH_MODE:
					if(Distance < LOD4_HIGH) {
						Model.Shape = ball_4;
					} else if(Distance < LOD3_HIGH) {
						Model.Shape = ball_3;
					} else {
						Model.Shape = ball_2;
					}
					break;

				case LOW_MODE:
					if(Distance < LOD4_LOW) {
						Model.Shape = ball_4;
					} else if(Distance < LOD3_LOW) {
						Model.Shape = ball_3;
					} else {
						Model.Shape = ball_2;
					}
					break;

				default:
					break;
			}
		}

		public void Accel()
		{
			switch(direction) {
				case DOWN_MODE:
					y_trs += DOWN_ACCEL;
					Model.GlTranslate(0.0, -y_trs, 0.0);
					break;

				case RISE_MODE:
					y_trs -= RISE_ACCEL;
					Model.GlTranslate(0.0, y_trs, 0.0);
					break;

				default:
					break;
			}
		}

		public void Bound()
		{
			if(Model.Position.y < BTM_BALL_POS) {
				direction = RISE_MODE;
			} else if(y_trs < 0.01) {
				if(direction == RISE_MODE) {
					if(bound_count % BOUND_CYCLE < VIEW_CHANGE) {
						view_mode = HIGH_MODE;
					} else {
						view_mode = LOW_MODE;
					}
					bound_count++;
				}
				direction = DOWN_MODE;
			}
		}

		public int Draw(fk_Vector argPos)
		{
			LOD(argPos);
			Bound();
			Accel();

			if(bound_count > BOUND_CYCLE) Init();
			return view_mode;
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			//fk_Material.InitDefault();
            var win = new fk_AppWindow();
			win.Size = new fk_Dimension(800, 800);
			win.ClearModel(false); // デフォルト光源消去

			win.ShadowMode = fk_ShadowMode.SOFT_NICE;
			win.ShadowVec = new fk_Vector(1.0, -1.0, 1.0);
			win.ShadowAreaSize = 800.0;
			win.ShadowDistance = 800.0;
			win.ShadowResolution = 1024;
			win.ShadowVisibility = 1.0;
			win.ShadowBias = 0.005;
			win.FPS = 0;

			int view_mode = Ball.HIGH_MODE;
	
			var ball = new Ball();
            var lightBall = new fk_Sphere(4, 2.0);

			var viewModel = new fk_Model();
			var pointLightModel = new fk_Model();
			var parallelLightModel = new fk_Model();
			var groundModel = new fk_Model();
			var blockModel = new fk_Model();
            var lightBallModel = new fk_Model();

			var pointLight = new fk_Light();
			var parallelLight = new fk_Light();
			var ground = new fk_Circle(4, 100.0);
			var block = new fk_Block(10.0, 10.0, 10.0);

			// ### VIEW POINT ###
			// 上の方から見た視点
			viewModel.GlMoveTo(0.0, 400.0, 80.0);
			viewModel.GlFocus(0.0, 30.0, 0.0);
			viewModel.GlUpvec(0.0, 1.0, 0.0);

			// ### LIGHT ###
			pointLight.Type = fk_LightType.POINT;
            pointLight.SetAttenuation(0.01, 0.0, 0.2);
			pointLightModel.Shape = pointLight;
			pointLightModel.Material = fk_Material.WhiteLight;
			pointLightModel.GlTranslate(-60.0, 60.0, 0.0);
            pointLightModel.GlVec(0.0, -1.0, 0.0);

			parallelLight.Type = fk_LightType.PARALLEL;
			parallelLightModel.Shape = parallelLight;
			parallelLightModel.Material = fk_Material.WhiteLight;
			parallelLightModel.GlVec(1.0, -1.0, 1.0);

            lightBallModel.Shape = lightBall;
            lightBallModel.Material = fk_Material.TrueWhite;
            lightBallModel.GlTranslate(pointLightModel.InhPosition);
			lightBallModel.ShadowEffect = false;
			lightBallModel.ShadowDraw = false;

			// ### GROUND ###
			groundModel.Shape = ground;
			groundModel.Material = fk_Material.LightGreen;
			groundModel.Material.Specular = new fk_Color(0.1, 0.1, 0.1);
			groundModel.SmoothMode = true;
			groundModel.LoRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -Math.PI/2.0);

			// ### VIEW BLOCK ###
			blockModel.Shape = block;
			blockModel.Material = fk_Material.Blue;
            blockModel.Material.Specular = new fk_Color(1.0, 1.0, 1.0);
            blockModel.Material.Shininess = 70.0f;
			blockModel.GlMoveTo(60.0, 30.0, 0.0);
			blockModel.Parent = groundModel;
	
			// ### Model Entry ###
			win.CameraModel = viewModel;
			win.Entry(pointLightModel);
			win.Entry(parallelLightModel);
			win.Entry(ball.Model);
			win.Entry(groundModel);
			win.Entry(blockModel);
            win.Entry(lightBallModel);

			win.Open();

			while(win.Update() == true) {

				// ボールを弾ませて, カメラの状態を取得。
				view_mode = ball.Draw(viewModel.Position);

				if(view_mode == Ball.HIGH_MODE) {
					// カメラを上からの視点にする。
					viewModel.GlMoveTo(0.0, 400.0, 80.0);
					viewModel.GlFocus(0.0, 30.0, 0.0);
					viewModel.GlUpvec(0.0, 1.0, 0.0);
					win.Entry(blockModel);
				} else {
					// カメラをブロックからの視点にする。
					viewModel.GlMoveTo(blockModel.InhPosition);
					viewModel.GlTranslate(0.0, 10.0, 0.0);
					viewModel.GlFocus(ball.Pos);
					viewModel.GlUpvec(0.0, 1.0, 0.0);
					win.Remove(blockModel);
				}

				// 地面をくるくる回転させましょう。
				groundModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, Ball.ROTATE_SPEED);
			}
		}
	}
}
