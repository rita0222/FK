using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Viewer
{
	class Program
	{
		static void Main(string[] args)
		{
			var viewer = new fk_ShapeViewer(600, 600);
			var shape = new fk_IndexFaceSet();
			var pos = new fk_Vector[121];
			var moveVec = new fk_Vector();
			var movePos = new fk_Vector();
			var IFSet = new int[4*100];
			int i, j;
			double x, y;

			for(i = 0; i <= 10; ++i) {
				for(j = 0; j <= 10; ++j) {
					x = (double)(i-5);
					y = (double)(j-5);
					pos[i*11+j] = new fk_Vector(x, y, (x*x - y*y)/10.0);
				}
			}

			for(i = 0; i < 10; i++) {
				for(j = 0; j < 10; j++) {
					IFSet[(i*10 + j)*4 + 0] = i*11 + j;
					IFSet[(i*10 + j)*4 + 1] = (i+1)*11 + j;
					IFSet[(i*10 + j)*4 + 2] = (i+1)*11 + j+1;
					IFSet[(i*10 + j)*4 + 3] = i*11 + j+1;
				}
			}

			shape.makeIFSet(100, 4, IFSet, 121, pos);
			viewer.setShape(0, shape);
			viewer.setDrawMode((uint)(fk_DrawMode.FRONTBACK_POLYMODE | fk_DrawMode.LINEMODE));
			viewer.setScale(10.0);

			for(int counter = 0; viewer.draw() == true; counter += 10) {
				for(i = 0; i <= 10; i++) {
					for(j = 0; j <= 10; j++) {
						moveVec.set(0.0, 0.0, Math.Sin((double)(counter + j*40)*0.05/FK.PI));
						movePos = moveVec + pos[i*11+j];
						shape.moveVPosition(i*11+j, movePos);
					}
				}
			}
		}
	}
}
