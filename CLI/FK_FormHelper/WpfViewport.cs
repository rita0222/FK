using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace FK_FormHelper
{
    /// <summary>
    /// WPF用のビューポート
    /// </summary>
    public class fk_WpfViewport : fk_Viewport
    {
        public fk_WpfViewport(System.Windows.Forms.Control argPanel) : base(argPanel)
        {            
        }

        protected override ITimer MakeTimer()
        {
            return new WpfTimer();
        }

        /// <summary>
        /// WPF用のタイマーの実装です。
        /// WinFormのタイマーとの差分を吸収しています。
        /// </summary>
        private class WpfTimer : DispatcherTimer, ITimer
        {
            public bool Enabled
            {
                get { return base.IsEnabled; }
                set { base.IsEnabled = value; }
            }

            public new int Interval
            {
                get { return base.Interval.Milliseconds; }
                set { base.Interval = TimeSpan.FromMilliseconds(value); }
            }
        }
    }
}
