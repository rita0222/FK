using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FK_CLI;

namespace FK_CSharpHelper
{
    public class fk_Viewport
    {
        private Timer timer = new Timer();
        private fk_Renderer renderer = new fk_Renderer();

        private Panel panel = null;
        private fk_Scene scene = null;

        public fk_Viewport(Panel argPanel)
        {
            panel = argPanel;

            if (panel.Visible)
            {
                // 既に表示されているパネルに対しては即初期化
                InitializeRenderer();
            }
            else
            {
                // まだ表示されていないパネルに対してはレイアウトイベントで初期化
                panel.Layout += (s, e) =>
                {
                    renderer.Initialize(panel.Handle, panel.Width, panel.Height);
                    if (scene != null) renderer.SetScene(scene);
                    timer.Enabled = true;
                };
            }

            panel.Paint += (s, e) => renderer.Draw();
            panel.Resize += (s, e) =>
            {
                renderer.Resize(panel.Width, panel.Height);
                renderer.Draw();
            };

            timer.Enabled = false;
            timer.Interval = 16;
            timer.Tick += (s, e) =>
            {
                if (PreDraw != null) PreDraw(null, null);
                renderer.Draw();
                if (PostDraw != null) PostDraw(null, null);
            };
        }

        public fk_Scene Scene
        {
            get
            {
                return scene;
            }

            set
            {
                scene = value;
                if (renderer != null) renderer.SetScene(scene);
            }
        }

        public bool IsDrawing
        {
            get { return timer.Enabled; }
            set { timer.Enabled = value; }
        }

        public int DrawInterval
        {
            get { return timer.Interval; }
            set { timer.Interval = value; }
        }

        public event EventHandler PreDraw;
        public event EventHandler PostDraw;

        private void InitializeRenderer()
        {
            renderer.Initialize(panel.Handle, panel.Width, panel.Height);
            if (scene != null) renderer.SetScene(scene);
            timer.Enabled = true;
        }
    }
}
