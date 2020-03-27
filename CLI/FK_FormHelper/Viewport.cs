using System;
using System.Windows.Forms;
using System.Diagnostics;
using FK_CLI;

namespace FK_FormHelper
{
    /// <summary>
    /// ビューポート
    /// </summary>
    public class fk_Viewport : IDisposable, fk_IBindableDrawer
    {
        private Control panel;
        private fk_Scene scene;
        private readonly fk_EngineWrapper engine;
        protected readonly ITimer timer;

        public fk_Viewport(Control argPanel)
        {
            engine = new fk_EngineWrapper();
            timer = MakeTimer();
            timer.Interval = 16;
            timer.Tick += (s, e) => Draw();

            Setup(argPanel);
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
                engine.SetScene(scene);
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

        public Control Panel
        {
            get { return panel; }
        }

        public event EventHandler Update;

        public event fk_DrawCallback PreDraw
        {
            add { this.engine.PreDraw += value; }
            remove { this.engine.PreDraw -= value; }
        }

        public event fk_DrawCallback PostDraw
        {
            add { this.engine.PostDraw += value; }
            remove { this.engine.PostDraw -= value; }
        }

        public void Dispose()
        {
            timer.Enabled = false;
            engine.Dispose();
        }

        public void Draw()
        {
            if (Update != null) Update(null, null);
            engine.Draw();
        }

        public bool GetProjectPosition(double argX, double argY, fk_Plane argPlane, out fk_Vector outPos)
        {
            var pos2d = new fk_Vector();
            bool ret = engine.GetProjectPosition(argX, argY, argPlane, pos2d);
            outPos = pos2d;
            return ret;
        }

        public bool GetProjectPosition(double argX, double argY, double argDist, out fk_Vector outPos)
        {
            var pos2d = new fk_Vector();
            bool ret = engine.GetProjectPosition(argX, argY, argDist, pos2d);
            outPos = pos2d;
            return ret;
        }

        public void GetWindowPosition(fk_Vector argPos, out fk_Vector outPos)
        {
            var pos2d = new fk_Vector();
            engine.GetWindowPosition(argPos, pos2d);
            outPos = pos2d;
        }

        protected virtual ITimer MakeTimer()
        {
            return new WinFormTimer();
        }

        private void Setup(Control argPanel)
        {
            if (IsInDesignMode()) return;

            panel = argPanel;

            if (panel.Handle != null)
            {
                InitializeRenderer(null, null);
            }
            else
            {
                panel.HandleCreated += InitializeRenderer;
            }

            panel.HandleDestroyed += (s, e) => Dispose();

            panel.Paint += (s, e) => engine.Draw();
            panel.Resize += (s, e) =>
            {
                engine.Resize(panel.Width, panel.Height);
                engine.Draw();
            };
        }

        private void InitializeRenderer(object sender, EventArgs args)
        {
            engine.Initialize(panel.Handle, panel.Width, panel.Height);
            if (scene != null) engine.SetScene(scene);
            IsDrawing = true;
            panel.HandleCreated -= InitializeRenderer;
        }

        public static bool IsInDesignMode()
        {
            bool returnFlag = false;
#if DEBUG
            if (System.ComponentModel.LicenseManager.UsageMode == System.ComponentModel.LicenseUsageMode.Designtime)
            {
                returnFlag = true;
            }
            else if (Process.GetCurrentProcess().ProcessName.ToUpper().Equals("DEVENV"))
            {
                returnFlag = true;
            }
#endif
            return returnFlag;
        }

        /// <summary>
        /// タイマーAPIを共通化するためのインタフェースです。
        /// </summary>
        protected interface ITimer
        {
            bool Enabled { get; set; }
            int Interval { get; set; }
            event EventHandler Tick;
        }

        /// <summary>
        /// WinFormのタイマーの実装です。
        /// 既存の実装をインタフェースに当てはめるだけです。
        /// </summary>
        private class WinFormTimer : Timer, ITimer { }
    }
}
