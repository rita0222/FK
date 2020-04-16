using System;
using FK_CLI;

namespace FK_Core_Test_Gregory
{
    class Program
    {
        static void modelInit(fk_Model argM)
        {
            argM.LineColor = new fk_Color(0.0, 0.0, 1.0);
            argM.PointColor = new fk_Color(1.0, 0.0, 0.0);
            argM.CurveColor = new fk_Color(0.0, 1.0, 0.0);
            argM.Material = fk_Material.Yellow;
            argM.SmoothMode = true;
            argM.PointSize = 5.0;
            argM.DrawMode = fk_Draw.GEOM_LINE | fk_Draw.GEOM_FACE | fk_Draw.LINE | fk_Draw.POINT;
        }

        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            var light = new fk_Light();
            var lightModel = new fk_Model();
            var camera = new fk_Model();

            var model = new fk_Model[2];
            var surf = new fk_Gregory[2];

            fk_Material.InitDefault();

            window.ClearModel();
            window.CameraModel = camera;
            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.Open();
            window.TrackBallMode = true;

            var ctrlP = new fk_Vector[4];
            for (int i = 0; i < 2; i++)
            {
                model[i] = new fk_Model();
                surf[i] = new fk_Gregory();
                surf[i].Div = 64;
                double x = (double)i * 30.0 - 30.0;

                for (int j = 0; j <= 3; j++)
                {
                    double d = 10.0 * (double)j;
                    ctrlP[0] = new fk_Vector(x + d, fk_Math.DRand(-17.0, -13.0), fk_Math.DRand(-15.0, 15.0));
                    ctrlP[1] = new fk_Vector(x + d, fk_Math.DRand(13.0, 17.0), fk_Math.DRand(-15.0, 15.0));
                    ctrlP[2] = new fk_Vector(x, d - fk_Math.DRand(13.0, 17.0), fk_Math.DRand(-15.0, 15.0));
                    ctrlP[3] = new fk_Vector(x + 30.0, d - fk_Math.DRand(13.0, 17.0), fk_Math.DRand(-15.0, 15.0));

                    surf[i].SetBoundary(fk_UV.U_S, j, ctrlP[0]);
                    surf[i].SetBoundary(fk_UV.U_E, j, ctrlP[1]);
                    surf[i].SetBoundary(fk_UV.V_S, j, ctrlP[2]);
                    surf[i].SetBoundary(fk_UV.V_E, j, ctrlP[3]);
                }

                surf[i].AdjustDerivative();
                model[i].Shape = surf[i];
                modelInit(model[i]);
                window.Entry(model[i]);
            }

            surf[1].SetBoundary(fk_UV.V_S, 0, surf[0].GetBoundary(fk_UV.V_E, 0));
            surf[1].SetBoundary(fk_UV.V_S, 3, surf[0].GetBoundary(fk_UV.V_E, 3));
            if (surf[1].Connect(surf[0], fk_UV.V_S, fk_UV.V_E, true, true) == false)
            {
                Console.WriteLine("Connect Error");
            }

            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlVec(0.0, 0.0, -1.0);
            window.Entry(lightModel);

            while (window.Update() == true)
            {
                if (window.GetKeyStatus('1', fk_Switch.DOWN))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        model[i].DrawMode = fk_Draw.GEOM_LINE | fk_Draw.GEOM_FACE | fk_Draw.LINE | fk_Draw.POINT;
                    }
                }

                if (window.GetKeyStatus('2', fk_Switch.DOWN))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        model[i].DrawMode = fk_Draw.GEOM_FACE | fk_Draw.LINE | fk_Draw.POINT;
                    }
                }

                if (window.GetKeyStatus('3', fk_Switch.DOWN))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        model[i].DrawMode = fk_Draw.GEOM_FACE;
                    }
                }
            }
        }
    }
}
