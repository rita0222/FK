using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FK_CLI;

namespace FK_CSharpHelper
{
    public class fk_Viewport : IDisposable
    {
        private fk_Renderer renderer = new fk_Renderer();
        private Timer timerWinForm = new Timer();
        private Panel panel = null;
        private fk_Scene scene = null;

        public fk_Viewport(Panel argPanel)
        {
            Setup(argPanel);
            timerWinForm.Interval = 16;
            timerWinForm.Tick += (s, e) => Draw();
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

        public virtual bool IsDrawing
        {
            get { return timerWinForm.Enabled; }
            set { timerWinForm.Enabled = value; }
        }

        public virtual int DrawInterval
        {
            get { return timerWinForm.Interval; }
            set { timerWinForm.Interval = value; }
        }

        public Panel Panel
        {
            get { return panel; }
        }

        public event EventHandler PreDraw;
        public event EventHandler PostDraw;

        public void Dispose()
        {
            renderer.Dispose();
        }

        public void Draw()
        {
            if (PreDraw != null) PreDraw(null, null);
            renderer.Draw();
            if (PostDraw != null) PostDraw(null, null);
        }

        private void Setup(Panel argPanel)
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
                panel.Layout += (s, e) => this.InitializeRenderer();
            }

            panel.Paint += (s, e) => renderer.Draw();
            panel.Resize += (s, e) =>
            {
                renderer.Resize(panel.Width, panel.Height);
                renderer.Draw();
            };
        }

        private void InitializeRenderer()
        {
            renderer.Initialize(panel.Handle, panel.Width, panel.Height);
            if (scene != null) renderer.SetScene(scene);
            IsDrawing = true;
        }
    }
}
