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
			var obj = new fk_Block();
			int num = obj.getFaceSize();
			Console.WriteLine(num);

		}
	}
}
