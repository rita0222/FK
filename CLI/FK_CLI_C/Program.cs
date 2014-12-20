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

			var model = new fk_Model();
			model.setShape(obj);
			Console.WriteLine(model);
		}
	}
}
