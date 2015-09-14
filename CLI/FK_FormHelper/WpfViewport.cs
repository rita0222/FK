using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace FK_FormHelper
{
    public class fk_WpfViewport : fk_Viewport
    {
        private DispatcherTimer timerWpf = new DispatcherTimer();

        public fk_WpfViewport() : base(new System.Windows.Forms.Panel())
        {
            timerWpf.Interval = TimeSpan.FromMilliseconds(16);
            timerWpf.Tick += (s, ee) => Draw();
        }

        public override bool IsDrawing
        {
            get { return timerWpf.IsEnabled; }
            set { timerWpf.IsEnabled = value; }
        }

        public override int DrawInterval
        {
            get { return timerWpf.Interval.Milliseconds; }
            set { timerWpf.Interval = TimeSpan.FromMilliseconds(value); }
        }
    }
}
