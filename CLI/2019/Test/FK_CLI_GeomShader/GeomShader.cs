using System;
using FK_CLI;

namespace FK_CLI_GeomShader
{
    class GeomShader
    {
        const double AREA = 20.0;
        const double SPEED = 0.1;
        static Random rnd = new Random();

        static double GetRand(double argMin, double argMax)
        {
            return (argMin + (argMax - argMin) * rnd.NextDouble());
        }

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

        static void Main(string[] args)
        {
            var model = new fk_Model();
            var point = new fk_Point();
            var shader = new fk_ShaderBinder();
            var posArray = new fk_Vector[4];
            var vecArray = new fk_Vector[4];

            fk_Material.InitDefault();

            // ウィンドウ生成
            var window = new fk_AppWindow();
            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.ShowGuide(fk_Guide.GRID_XY);
            window.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.Open();

            for(int i = 0; i < posArray.Length; i++)
            {
                posArray[i] = new fk_Vector(GetRand(-AREA, AREA), GetRand(-AREA, AREA), 0.0);
                vecArray[i] = new fk_Vector(GetRand(-1.0, 1.0), GetRand(-1.0, 1.0), 0.0);
                vecArray[i].Normalize();
            }
            point.SetVertex(posArray);
            point.SetShaderAttribute("pointVec", 2, vecArray);

            model.Shape = point;
            model.PointColor = new fk_Color(1.0, 0.0, 0.0);
            model.PointSize = 5.0;

            window.Entry(model);

            var program = shader.Program;
            program.LoadVertexShader("shader/geom_vs.glsl");
            program.LoadGeometryShader("shader/geom_gs.glsl");
            program.LoadFragmentShader("shader/geom_fs.glsl");

            if(program.Validate() == true)
            {
                shader.BindModel(model);
                shader.Parameter.ReserveAttribute("pointVec");
            } else
            {
                Console.WriteLine(program.LastError);
            }

            while (window.Update())
            {
                for(int i = 0; i < posArray.Length; i++)
                {
                    posArray[i] = PointMove(posArray[i], vecArray[i]);
                    vecArray[i] = VecChange(posArray[i], vecArray[i]);
                    point.SetVertex(i, posArray[i]);
                }
                point.SetShaderAttribute("pointVec", 2, vecArray);
            }
        }
    }
}