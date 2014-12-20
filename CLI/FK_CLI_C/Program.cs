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
			var obj = new fk_Sphere(8, 10.0);
			int num = obj.getFaceSize();
			Console.WriteLine(num);
			var pos = obj.getPosVec(100);
			Console.WriteLine(pos);

			var model1 = new fk_Model();
			var model2 = new fk_Model();
			model2.setShape(obj);
			model2.glMoveTo(10.0, 0.0, 0.0);
			model1.entryChild(model2);
			model1.glTranslate(0.0, 1.0, 0.0);
			var org = new fk_Vector(0.0, 0.0, 0.0);
			//model1.glRotateWithVec(org, fk_Axis.Z, FK.PI / 24.0);
			pos = model2.getInhPosition();
			Console.WriteLine(pos);
		}
	}
}
