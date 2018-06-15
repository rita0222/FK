using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_ARTest
{
    class rotateModel
    {
        private fk_Model baseModel, block, line1, line2;
        private void MakeLine()
        {
            var linePos = new fk_Vector[3];
            linePos[0] = new fk_Vector(0.0, 0.0, 50.0);
            linePos[1] = new fk_Vector(50.0, 0.0, 0.0);
            linePos[2] = -linePos[1];

            var lineShape1 = new fk_Line();
            var lineShape2 = new fk_Line();
            lineShape1.PushLine(linePos[0], linePos[1]);
            lineShape2.PushLine(linePos[0], linePos[2]);
            line1.Shape = lineShape1;
            line2.Shape = lineShape2;
            line1.LineColor = new fk_Color(1.0, 0.0, 0.0);
            line2.LineColor = new fk_Color(0.0, 1.0, 0.0);
        }

        public rotateModel()
        {
            fk_Material.InitDefault();

            baseModel = new fk_Model();
            block = new fk_Model();
            line1 = new fk_Model();
            line2 = new fk_Model();

            var blockShape = new fk_Block(20.0, 20.0, 20.0);
            block.Shape = blockShape;
            block.Material = fk_Material.Yellow;
            block.SmoothMode = true;
            block.GlMoveTo(0.0, 0.0, 10.0);
            block.Parent = baseModel;
            baseModel.Scale = 1.0;

            MakeLine();
            line1.Parent = block;
            line2.Parent = block;
        }

        public void Entry(fk_AppWindow argWin)
        {
            argWin.Entry(block);
            argWin.Entry(line1);
            argWin.Entry(line2);
        }

        public void Remove(fk_AppWindow argWin)
        {
            argWin.Remove(block);
            argWin.Remove(line1);
            argWin.Remove(line2);
        }

        public fk_Model Base
        {
            get
            {
                return baseModel;
            }
        }

        public void Rotate()
        {
            line1.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Z, Math.PI / 300.0);
            line2.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Z, Math.PI / 300.0);
        }
    }



    class Program
    {

        static void WindowSetup(fk_AppWindow argW)
        {
            fk_Material.InitDefault();
            argW.Size = new fk_Dimension(1000, 800);
            argW.BGColor = new fk_Color(0.1, 0.1, 0.1);
            argW.TrackBallMode = true;
        }

        static void ARInit(fk_ARDevice argAR, fk_Model argM1, fk_Model argM2)
        {
            argAR.SetConfigFile("");
            argAR.SetCameraParamFile("ARData/camera_para.dat");
            argAR.Thresh = 100;

            argAR.SetPatternFile(0, "ARData/kanji.patt");
            argAR.SetPatternWidth(0, 80.0);
            argAR.SetPatternModel(0, argM1);

            argAR.SetPatternFile(1, "ARData/hiro.patt");
            argAR.SetPatternWidth(1, 80.0);
            argAR.SetPatternModel(1, argM2);

            if(argAR.DeviceInit() == false)
            {
                Console.WriteLine("Device Error");
            }
        }

        static void VideoInit(fk_ARTexture argVideo, fk_ARDevice argDev,
            fk_AppWindow argWin, fk_Model argModel, fk_Model argCamera)
        {
            var proj = new fk_Frustum();

            argWin.CameraModel = argCamera;
            argDev.MakeProject(50.0, 5000.0, proj, argVideo, argModel, argCamera);
            argVideo.Type = fk_PixelFormatType.DEFAULT;
            argWin.Scene.Projection = proj;
            argModel.Shape = argVideo;
            argWin.Entry(argModel);
        }
        
        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            WindowSetup(window);

            var block = new rotateModel[2];
            block[0] = new rotateModel();
            block[1] = new rotateModel();
            block[0].Entry(window);
            block[1].Entry(window);

            var ar_dev = new fk_ARDevice();
            var videoTex = new fk_ARTexture();
            ARInit(ar_dev, block[0].Base, block[1].Base);

            var camera = new fk_Model();
            var videoModel = new fk_Model();

            VideoInit(videoTex, ar_dev, window, videoModel, camera);

            window.Open();

            while (window.Update())
            {
                for(int i = 0; i < 2; i++)
                {
                    block[i].Rotate();
                }

                videoTex.Update();

                switch (ar_dev.Update(videoTex))
                {
                    case fk_AR_Device_Status.IMAGE_NULL:
                        break;

                    case fk_AR_Device_Status.DETECT_ERROR:
                        return;

                    case fk_AR_Device_Status.DETECT:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ar_dev.GetModelDetect(i))
                            {
                                block[i].Entry(window);
                            }
                            else
                            {
                                block[i].Remove(window);
                            }
                        }
                        break;

                    case fk_AR_Device_Status.NO_DETECT:
                        for (int i = 0; i < 2; i++)
                        {
                            block[i].Remove(window);
                        }
                        break;

                    default:
                        break;
                }
            }
        }
    }
}
