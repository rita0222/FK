using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_GenMatrix
{
	class Program
	{
		static void Main(string[] args)
		{
			var largeV = new fk_GenVector[3];
			var largeM = new fk_GenMatrix[2];
			const int DEG = 50;
			const int COUNT = 50;
			int i, j, c, diff;
			var rand = new Random();

			for(i = 0; i < 3; i++) largeV[i] = new fk_GenVector(DEG);
			for(i = 0; i < 2; i++) largeM[i] = new fk_GenMatrix(DEG);

			diff = 0;
			for(c = 0; c < COUNT; c++) {
				for(i = 0; i < DEG; i++) {
					largeV[0][i] = rand.NextDouble();
					for(j = 0; j < DEG; j++) {
						largeM[0][i, j] = rand.NextDouble();
					}
				}

				largeV[1] = largeM[0] * largeV[0];
				largeM[1] = largeM[0].getInverse();
				largeV[2] = largeM[1] * largeV[1];

				if(!largeV[0].Equals(largeV[2])) diff++;
			}
			Console.WriteLine("Diff Count = " + diff.ToString());
		}
	}
}
