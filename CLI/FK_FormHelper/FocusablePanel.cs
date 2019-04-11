using System.Windows.Forms;

namespace FK_FormHelper
{
    public class FocusablePanel : Panel
    {
        public FocusablePanel()
        {
            SetStyle(ControlStyles.Selectable, true);
            TabStop = true;
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            Focus();
            base.OnMouseDown(e);
        }

        protected override bool IsInputKey(Keys keyData)
        {
            if (keyData == Keys.Up || keyData == Keys.Down) return true;
            if (keyData == Keys.Left || keyData == Keys.Right) return true;
            return base.IsInputKey(keyData);
        }
    }
}
