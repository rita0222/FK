using System;
using FK_CLI;

namespace FK_CLI_Viewer
{
	class Viewer
	{
		static void Main(string[] args)
		{
            const int SIZE = 40;

			var viewer = new fk_ShapeViewer(600, 600);
			var shape = new fk_IndexFaceSet();
			var pos = new fk_Vector[(SIZE+1)*(SIZE+1)];
			var moveVec = new fk_Vector();
			var movePos = new fk_Vector();
			var IFSet = new int[4*SIZE*SIZE];
			int i, j;
			double x, y;

			for(i = 0; i <= SIZE; ++i) {
				for(j = 0; j <= SIZE; ++j) {
					x = (double)(i - SIZE/2);
					y = (double)(j - SIZE/2);
					pos[i*(SIZE+1)+j] = new fk_Vector(x, y, (x*x - y*y)/(double)SIZE);
				}
			}

			for(i = 0; i < SIZE; i++) {
				for(j = 0; j < SIZE; j++) {
					IFSet[(i*SIZE + j)*4 + 0] = i*(SIZE+1) + j;
					IFSet[(i*SIZE + j)*4 + 1] = (i+1)*(SIZE+1) + j;
					IFSet[(i*SIZE + j)*4 + 2] = (i+1)*(SIZE+1) + j+1;
					IFSet[(i*SIZE + j)*4 + 3] = i*(SIZE+1) + j+1;
				}
			}

			shape.MakeIFSet(SIZE*SIZE, 4, IFSet, (SIZE+1)*(SIZE+1), pos);
			viewer.Shape = shape;
			viewer.DrawMode = fk_DrawMode.FRONTBACK_POLYMODE | fk_DrawMode.LINEMODE;
			viewer.Scale = 10.0;

			for(int counter = 0; viewer.Draw() == true; counter += 10) {
				for(i = 0; i <= SIZE; i++) {
					for(j = 0; j <= SIZE; j++) {
						moveVec.Set(0.0, 0.0, Math.Sin((double)(counter + j*40)*0.05/Math.PI));
						movePos = moveVec + pos[i*(SIZE+1)+j];
						shape.MoveVPosition(i*(SIZE+1)+j, movePos);
					}
				}
			}
		}
	}
}
