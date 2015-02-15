﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Ball
{
	public class Ball
	{
		private const double	DOWN_ACCEL		= 1.0500;	// 降下時の加速度
		private const double	RISE_ACCEL		= 1.0530;	// 上昇時の減速度
		private const int		DOWN_MODE		= 0;		// 降下モード
		private const int		RISE_MODE		= 1;		// 上昇モード
		private const int		LOD4_HIGH		= 200;		// 四分割距離 (鳥瞰)
		private const int		LOD3_HIGH		= 300;		// 三分割距離 (鳥瞰)
		private const int		LOD4_LOW		= 90;		// 四分割距離 (ブロック)
		private const int		LOD3_LOW		= 120;		// 三分割距離 (ブロック)
		private const double	TOP_BALL_POS	= 300.0;	// ボール始点高さ
		private const double	BTM_BALL_POS	= 18.0;		// ボール跳ね返り高さ
		private const double	BALL_SIZE		= 12.0;		// ボール半径

		private int direction;		// ボールの状態(DOWN_MODE or RISE_MODE)
		private int	view_mode;		// 視点モード
		private int	bound_count;	// バウンド回数を数える変数
		private double y_trs;			// ボールのｙ座標移動量
		private fk_Model ball_model;		// ボールのモデル
		private fk_Sphere BALL2;			// 二分割形状
		private fk_Sphere BALL3;			// 三分割形状
		private fk_Sphere BALL4;			// 四分割形状

		public const int LOW_MODE		= 0;		// ブロック視点モード
		public const int HIGH_MODE		= 1;		// 鳥瞰モード

		public Ball()
		{
			BALL2 = new fk_Sphere(6, BALL_SIZE);
			BALL3 = new fk_Sphere(8, BALL_SIZE);
			BALL4 = new fk_Sphere(10, BALL_SIZE);
			ball_model = new fk_Model();
			init();
		}

		public void init()
		{
			direction	= DOWN_MODE;
			y_trs		= 0.1;
			view_mode	= HIGH_MODE;
			bound_count	= 1;
			ball_model.glMoveTo(0.0, TOP_BALL_POS, 0.0);
			ball_model.setShape(BALL2);
		}

		public fk_Model getModel()
		{
			return ball_model;
		}

		public fk_Vector getPosition()
		{
			return ball_model.getPosition();
		}

		public void lod(fk_Vector pos)
		{
			double	Distance = (ball_model.getPosition() - pos).Dist();
			switch(view_mode) {
				case HIGH_MODE:
					if(Distance < LOD4_HIGH) {
						ball_model.setShape(BALL4);
					} else if(Distance < LOD3_HIGH) {
						ball_model.setShape(BALL3);
					} else {
						ball_model.setShape(BALL2);
					}
					break;

				case LOW_MODE:
					if(Distance < LOD4_LOW) {
						ball_model.setShape(BALL4);
					} else if(Distance < LOD3_LOW) {
						ball_model.setShape(BALL3);
					} else {
						ball_model.setShape(BALL2);
					}
					break;

				default:
					break;
			}
		}

		public void accel()
		{
			switch(direction) {
				case DOWN_MODE:
					y_trs *= DOWN_ACCEL;
					ball_model.glTranslate(0.0, -y_trs, 0.0);
					break;

				case RISE_MODE:
					y_trs /= RISE_ACCEL;
					ball_model.glTranslate(0.0, y_trs, 0.0);
					break;

				default:
					break;
			}
		}

		public void bound()
		{
			if(ball_model.getPosition().y < BTM_BALL_POS) {
				direction = RISE_MODE;
			} else if(y_trs < 0.01) {
				if(direction == RISE_MODE) {
					if(bound_count % 4 < 2) {
						view_mode = HIGH_MODE;
					} else {
						view_mode = LOW_MODE;
					}
					bound_count++;
				}
				direction = DOWN_MODE;
			}
		}

		public int draw(fk_Vector pos)
		{
			lod(pos);
			bound();
			accel();
			//４回跳ね返ると初期化
			if(bound_count > 4) init();
			return view_mode;
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			win.SetSize(600, 600);
			win.ClearModel(false); // デフォルト光源消去

			int view_mode = Ball.HIGH_MODE;
	
			var ball = new Ball();
			
			var viewModel = new fk_Model();
			var lightModel = new fk_Model();
			var groundModel = new fk_Model();
			var blockModel = new fk_Model();

			var light = new fk_Light();
			var ground = new fk_Circle(4, 100.0);
			var block = new fk_Block(10.0, 10.0, 10.0);


			fk_Material.initDefault();

			// ### VIEW POINT ###
			// 上の方から見た視点
			viewModel.glMoveTo(0.0, 400.0, 80.0);
			viewModel.glFocus(0.0, 30.0, 0.0);
			viewModel.glUpvec(0.0, 1.0, 0.0);

			// ### LIGHT ###
			light.setLightType(fk_LightType.POINT);
			light.setAttenuation(0.0, 0.0);
			lightModel.setShape(light);
			lightModel.setMaterial(fk_Material.White);
			lightModel.glTranslate(-60.0, 60.0, 0.0);

			// ### GROUND ###
			groundModel.setShape(ground);
			groundModel.setMaterial(fk_Material.LightGreen);
			groundModel.setSmoothMode(true);
			groundModel.loRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -FK.PI/2.0);

			// ### VIEW BLOCK ###
			blockModel.setShape(block);
			blockModel.setMaterial(fk_Material.Blue);
			blockModel.glMoveTo(60.0, 30.0, 0.0);
			blockModel.setParent(groundModel);

			// ### BALL ###
			ball.getModel().setMaterial(fk_Material.Red);
			ball.getModel().setSmoothMode(true);
	
			// ### Model Entry ###
			win.SetCameraModel(viewModel);
			win.Entry(lightModel);
			win.Entry(ball.getModel());
			win.Entry(groundModel);
			win.Entry(blockModel); 

			win.Open();

			while(win.Update() == true) {

				// ボールを弾ませて, カメラの状態を取得。
				view_mode = ball.draw(viewModel.getPosition());

				if(view_mode == Ball.HIGH_MODE) {
					// カメラを上からの視点にする。
					viewModel.glMoveTo(0.0, 400.0, 80.0);
					viewModel.glFocus(0.0, 30.0, 0.0);
					viewModel.glUpvec(0.0, 1.0, 0.0);
					//win.entry(blockModel);
				} else {
					// カメラをブロックからの視点にする。
					viewModel.glMoveTo(blockModel.getInhPosition());
					viewModel.glTranslate(0.0, 10.0, 0.0);
					viewModel.glFocus(ball.getPosition());
					viewModel.glUpvec(0.0, 1.0, 0.0);
					//win.remove(blockModel);
				}

				// 地面をくるくる回転させましょう。
				groundModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.02);
			}
		}
	}
}
