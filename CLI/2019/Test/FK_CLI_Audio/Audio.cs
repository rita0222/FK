using System;
using System.Threading.Tasks;
using System.Threading;
using FK_CLI;

namespace FK_CLI_Audio
{
    class Program
    {
        static void Main(string[] args)
        {
            // マテリアル初期化
            fk_Material.InitDefault();

            // ウィンドウの各種設定
            var win = new fk_AppWindow();
            WindowSetup(win);

            // 立方体の各種設定
            var blockModel = new fk_Model();
            BlockSetup(blockModel, win);

            // BGM用変数の作成
            var bgm = new fk_BGM("epoq.ogg");
            double volume = 0.5;

            // SE用変数の作成
            var se = new fk_Sound(2);
            // 音源読み込み (IDは0番)
            se.LoadData(0, "MIDTOM2.wav");
            // 音源読み込み (IDは1番)
            se.LoadData(1, "SDCRKRM.wav");

            // ウィンドウ表示
            win.Open();

            // BGM再生スタート
            bgm.Start();

            // SE出力スタンバイ
            se.Start();

            var origin = new fk_Vector(0.0, 0.0, 0.0);
            while (win.Update())
            {
                blockModel.GlRotateWithVec(origin, fk_Axis.Y, Math.PI / 360.0);

                // volume値の変更
                volume = ChangeVolume(volume, win);
                bgm.Gain = volume;

                // SE再生
                PlaySE(se, win);
            }

            // BGM変数とSE変数に終了を指示
            // (最後にこれをやらないといつまでも再生が止まらずプログラムが終了しません)
            bgm.StopStatus = true;
            se.StopStatus = true;
        }

        // ウィンドウ設定メソッド
        static void WindowSetup(fk_AppWindow argWin)
        {
            argWin.CameraPos = new fk_Vector(0.0, 1.0, 20.0);
            argWin.CameraFocus = new fk_Vector(0.0, 1.0, 0.0);
            argWin.Size = new fk_Dimension(600, 600);
            argWin.BGColor = new fk_Color(0.6, 0.7, 0.8);
            argWin.ShowGuide(fk_GuideMode.GRID_XZ);
            argWin.TrackBallMode = true;
            argWin.FPS = 60;
        }

        // 立方体モデル設定メソッド
        static void BlockSetup(fk_Model argModel, fk_AppWindow argWin)
        {
            // 立方体の各種設定
            var block = new fk_Block(1.0, 1.0, 1.0);
            argModel.Shape = block;
            argModel.GlMoveTo(3.0, 3.0, 0.0);
            argModel.Material = fk_Material.Yellow;
            argWin.Entry(argModel);
        }

        // 音量調整メソッド
        static double ChangeVolume(double argVol, fk_AppWindow argWin)
        {
            double tmpV = argVol;

            // 上矢印キーで BGM 音量アップ
            if (argWin.GetSpecialKeyStatus(fk_Key.UP, fk_Switch.DOWN) == true)
            {
                tmpV += 0.1;
                if (tmpV > 1.0)
                {
                    tmpV = 1.0;
                }
            }

            // 下矢印キーで BGM 音量ダウン
            if (argWin.GetSpecialKeyStatus(fk_Key.DOWN, fk_Switch.DOWN) == true)
            {
                tmpV -= 0.1;
                if (tmpV < 0.0)
                {
                    tmpV = 0.0;
                }
            }
            return tmpV;
        }

        // SE再生(トリガー)メソッド
        static void PlaySE(fk_Sound argSE, fk_AppWindow argWin)
        {
            // Z キーで 0 番の SE を再生開始
            if (argWin.GetKeyStatus('Z', fk_Switch.DOWN) == true)
            {
                argSE.StartSound(0);
            }

            // X キーで 1 番の SE を再生開始
            if (argWin.GetKeyStatus('X', fk_Switch.DOWN) == true)
            {
                argSE.StartSound(1);
            }
        }
    }
}