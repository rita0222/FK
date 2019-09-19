using System;
using FK_CLI;

namespace FK_CLI_BezSurface
{
    class Program
    {
        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            var model = new fk_Model();
            var surf = new fk_BezSurface();

            fk_Material.InitDefault();
            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.CameraPos = new fk_Vector(0.0, 0.0, 200.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

            window.Open();
            window.TrackBallMode = true;

            surf.Degree = 3;
            surf.Div = 16;

            for(int i = 0; i <= 3; i++)
            {
                for(int j = 0; j <= 3; j++)
                {
                    var p = new fk_Vector(
                        -30.0 + 20.0 * i, -30.0 + 20.0 * j,
                        50.0 * Math.Sin(i) * Math.Cos(j));

                    surf.SetCtrl(i, j, p);
                }
            }

            model.LineColor = new fk_Color(0.0, 0.0, 1.0);
            model.PointColor = new fk_Color(1.0, 0.0, 0.0);
            model.CurveColor = new fk_Color(0.0, 1.0, 0.0);
            model.Material = fk_Material.Yellow;
            model.SmoothMode = true;
            model.PointSize = 5.0;
            model.Shape = surf;
            model.DrawMode = fk_Draw.GEOM_LINE | fk_Draw.GEOM_FACE | fk_Draw.LINE | fk_Draw.POINT;
            window.Entry(model);

            while (window.Update()) { }
        }
    }
}
