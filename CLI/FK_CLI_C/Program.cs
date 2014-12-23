using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_C
{
	class Program
	{
		static void Main(string[] args)
		{
			fk_AppWindow win = new fk_AppWindow();
			fk_Block block = new fk_Block(20.0, 20.0, 20.0);
			fk_Model model = new fk_Model();
			fk_Material mat = new fk_Material();
			fk_Vector origin = new fk_Vector();
			mat.setAmbDiff(0.9, 0.7, 0.4);
			model.setShape(block);
			model.setMaterial(mat);
			win.entry(model);
			win.open();
			while (win.update() == true)
			{
				model.glRotateWithVec(origin, fk_Axis.Y, FK.PI / 360.0);
			}
		}
	}
}
