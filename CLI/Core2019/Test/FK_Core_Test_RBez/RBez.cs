using System;
using FK_CLI;

namespace FK_Core_Test_RBez
{
    class RBez
    {
        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            var model = new fk_Model();
            var curv = new fk_RBezCurve();

            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.TrackBallMode = true;
            window.FPS = 60;

            curv.Degree = 2;
            curv.Div = 32;

            double l = 10.0;
            double h = 30.0;
            double w = l / Math.Sqrt(l * l + h * h);

            curv.SetCtrl(0, new fk_Vector(-l, 0.0, 0.0));
            curv.SetCtrl(1, new fk_Vector(0.0, h, 0.0));
            curv.SetCtrl(2, new fk_Vector(l, 0.0, 0.0));

            curv.SetWeight(1, w);

            model.LineColor = new fk_Color(0.0, 0.0, 1.0);
            model.PointColor = new fk_Color(0.0, 1.0, 0.0);
            model.CurveColor = new fk_Color(1.0, 0.0, 0.0);
            model.PointSize = 5.0;
            model.Shape = curv;
            model.DrawMode = fk_Draw.GEOM_LINE | fk_Draw.LINE | fk_Draw.POINT;
            window.Entry(model);

            window.Open();

            while(window.Update())
            {
                if (window.GetSpecialKeyStatus(fk_Key.RIGHT, fk_Switch.PRESS)) h += 0.1;
                if (window.GetSpecialKeyStatus(fk_Key.LEFT, fk_Switch.PRESS)) h -= 0.1;
                if (window.GetSpecialKeyStatus(fk_Key.UP, fk_Switch.PRESS)) w += 0.01;
                if (window.GetSpecialKeyStatus(fk_Key.DOWN, fk_Switch.PRESS)) w -= 0.01;

                curv.SetCtrl(1, new fk_Vector(0.0, h, 0.0));
                curv.SetWeight(1, w);
            }
        }
    }
}
