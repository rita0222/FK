using System;
using FK_CLI;

namespace FK_CLI_GeomShader
{
    class GeomShader
    {
        const double AREA = 20.0;
        const double SPEED = 0.1;

        static fk_Vector PointMove(fk_Vector argP, fk_Vector argV)
        {
            return argP + SPEED * argV;
        }

        static fk_Vector VecChange(fk_Vector argP, fk_Vector argV)
        {
            if (Math.Abs(argP.x) > AREA && argP.x * argV.x > 0.0) argV.x = -argV.x;
            if (Math.Abs(argP.y) > AREA && argP.y * argV.y > 0.0) argV.y = -argV.y;
            return argV;
        }

        static fk_AppWindow WindowSetup()
        {
            var window = new fk_AppWindow();

            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.ShowGuide(fk_Guide.GRID_XY);
            window.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.Open();
            return window;
        }

        static void PointSetup(fk_Point argPoint, fk_Vector [] argPArray, fk_Vector [] argVArray)
        {
            for (int i = 0; i < argPArray.Length; i++)
            {
                argPArray[i] = new fk_Vector(fk_Math.DRand(-AREA, AREA), fk_Math.DRand(-AREA, AREA), 0.0);
                argVArray[i] = new fk_Vector(fk_Math.DRand(-1.0, 1.0), fk_Math.DRand(-1.0, 1.0), 0.0);
                argVArray[i].Normalize();
            }
            argPoint.SetVertex(argPArray);
            argPoint.SetShaderAttribute("pointVec", 2, argVArray);
        }

        static void ModelSetup(fk_Model argModel, fk_Point argPoint)
        {
            argModel.Shape = argPoint;
            argModel.PointColor = new fk_Color(1.0, 0.0, 0.0);
            argModel.PointSize = 5.0;
        }

        static void ShaderSetup(fk_Model argModel)
        {
            var shader = new fk_ShaderBinder();

            var program = shader.Program;
            program.LoadVertexShader("shader/geom_vs.glsl");
            program.LoadGeometryShader("shader/geom_gs.glsl");
            program.LoadFragmentShader("shader/geom_fs.glsl");

            if (program.Validate() == true)
            {
                shader.BindModel(argModel);
                shader.Parameter.ReserveAttribute("pointVec");
            }
            else
            {
                Console.WriteLine(program.LastError);
            }
        }

        static void PointUpdate(fk_Point argPoint, fk_Vector [] argPArray, fk_Vector [] argVArray)
        {
            for (int i = 0; i < argPArray.Length; i++)
            {
                argPArray[i] = PointMove(argPArray[i], argVArray[i]);
                argVArray[i] = VecChange(argPArray[i], argVArray[i]);
                argPoint.SetVertex(i, argPArray[i]);
            }
            argPoint.SetShaderAttribute("pointVec", 2, argVArray);
        }

        static void Main(string[] args)
        {
            var model = new fk_Model();
            var point = new fk_Point();
            var posArray = new fk_Vector[4];
            var vecArray = new fk_Vector[4];

            fk_Material.InitDefault();

            var window = WindowSetup();
            PointSetup(point, posArray, vecArray);
            ModelSetup(model, point);
            window.Entry(model);
            ShaderSetup(model);

            while (window.Update())
            {
                PointUpdate(point, posArray, vecArray);
            }
        }
    }
}