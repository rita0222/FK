using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FK_CLI;

namespace PlugInTestApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

			var	mat	= new fk_Matrix();
            var vec = new fk_Vector();
            vec.x = 1.0;
            vec.y = 0.0;
            vec.z = 0.0;
            vec.normalize();
            this.textBox1.Text = vec.ToString();

			mat.makeRot(FK.PI/6.0, fk_Axis.Z);
			fk_Vector vec2 = mat * vec;			

			this.textBox2.Text = vec2.ToString();			
            var vecA = new fk_Vector();
            var vecB = new fk_Vector();

			
            vecA.x = 2.0;
            vecB.y = 3.0;

            var vecC = vecA + vecB;

			var vecH = new fk_HVector();
			vecH.x = 5.0;
			vecH.y = 2.0;
			vecH.w = 1.0;

			fk_Vector vecD = vecH;
			fk_HVector vecH2 = vecD;
            this.textBox3.Text = vecH2.ToString();

        }
    }
}
