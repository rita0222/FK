using System;
using FK_CLI;

namespace FK_CLI_Graph
{
    class Graph
    {
        static fk_GraphEdge MakeEdge(fk_Graph argGraph, bool argMode, uint argID1, uint argID2)
        {
            var v1 = argGraph.GetNode(argID1);
            var v2 = argGraph.GetNode(argID2);
            return argGraph.MakeEdge(argMode, v1, v2);
        }

        static void Main(string[] args)
        {
			fk_Material.InitDefault();

            const int SIZE = 40;
            const double HALF = (double)(SIZE - 1) / 2.0;
            var window = new fk_AppWindow();
            var model = new fk_Model();
            var graph = new fk_Graph(SIZE * SIZE);

            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.Open();
            window.TrackBallMode = true;

            var P = new fk_Vector();
            fk_GraphEdge edge;

            for(uint i = 0; i < SIZE; ++i)
            {
                for(uint j = 0; j < SIZE; ++j)
                {
                    P.Set((double)j - HALF, (double)i - HALF, 0.0);
                    graph.GetNode(i * SIZE + j).Position = P;

                    if (j != SIZE - 1)
                    {
                        edge = MakeEdge(graph, true, i*SIZE + j, i*SIZE + j+1);
                        edge.Color = new fk_Color(1.0, 0.0, 0.0);
                    }

                    if (i != SIZE - 1)
                    {
                        edge = MakeEdge(graph, true, i*SIZE + j, (i+1)*SIZE + j);
                        edge.Color = new fk_Color(1.0, 0.0, 0.0);
                    }

                    if (i != SIZE-1 && j != SIZE-1)
                    {
                        edge = MakeEdge(graph, false, i*SIZE + j, (i+1)*SIZE + j+1);
                        edge.Color = new fk_Color(0.0, 0.0, 1.0);
                    }
                    if (i != SIZE - 1 && j != 0)
                    {
                        edge = MakeEdge(graph, true, (i+1)*SIZE + j-1, i*SIZE + j);
                        edge.Color = new fk_Color(0.0, 0.0, 1.0);
                    }
                }
            }

			for (uint i = 0; i < graph.MaxEdgeID; ++i)
			{
				edge = graph.GetEdge(i);
				if (edge == null) continue;
				edge.SetIntCost(0, 1);
			}

			if (graph.MakeCostTable(0, fk_CostType.INT) == false) Console.WriteLine("Error1");
			if (graph.SetCostDirection(0, fk_CostDirection.FORWARD) == false) Console.WriteLine("Error2");
			if (graph.SetEdgeCostID(0, 0) == false) Console.WriteLine("Error3");
			graph.SetStart(0, graph.GetNode(SIZE * (SIZE / 2 + 5) + SIZE / 2 - 4));
			graph.AddGoal(0, graph.GetNode(SIZE - 2));

			if (graph.MakeCostTable(1, fk_CostType.LENGTH) == false) Console.WriteLine("Error4");
			if (graph.SetCostDirection(1, fk_CostDirection.BACK) == false) Console.WriteLine("Error5");
			graph.SetStart(1, graph.GetNode(SIZE * (SIZE / 2 + 5) + 3));
			graph.AddGoal(1, graph.GetNode(4 * SIZE + 1));
			graph.AddGoal(1, graph.GetNode(8 * SIZE + (SIZE - 2)));

			graph.InitCostTable(0);
			while (graph.UpdateCostTable(0) == fk_CostStatus.CONTINUE) ;

			graph.InitCostTable(1);
			while (graph.UpdateCostTable(1) == fk_CostStatus.CONTINUE) ;


			uint costID = graph.GetNodeCostID(0);
			double max = -1.0;
			double cost;

			for (uint i = 0; i < graph.NodeSize; ++i)
			{
				var node = graph.GetNode(i);
				cost = (double)(node.GetIntCost(costID));
				if (cost > max) max = cost;
			}

			var red = new fk_Color(1.0, 0.0, 0.0);
			var blue = new fk_Color(0.0, 0.0, 1.0);

			for (uint i = 0; i < graph.NodeSize; ++i)
			{
				var node = graph.GetNode(i);
				cost = (double)(node.GetIntCost(costID));
				double t = cost / max;
				node.Color = (1.0 - t) * red + t * blue;
			}

			var path = graph.GetOnePath(0);

			model.PointColor = new fk_Color(1.0, 0.0, 0.0);
			model.LineColor = new fk_Color(0.0, 0.0, 1.0);
			model.PointSize = 5.0;
			model.Shape = graph;
			model.DrawMode = fk_Draw.LINE | fk_Draw.POINT;
			model.ElementMode = fk_ElementMode.ELEMENT;
			window.Entry(model);

			var spModel = new fk_Model();
			var sphere = new fk_Sphere(4, 1.0);
			spModel.Shape = sphere;
			spModel.Material = fk_Material.Yellow;
			window.Entry(spModel);
			fk_GraphNode curNode = null;
			if (path.Count > 0)
			{
				spModel.GlMoveTo(path[0].Position);
				path.RemoveAt(0);
				curNode = path[0];
			}

			for (uint i = 0; window.Update() == true; ++i)
			{
				if (path.Count == 0) continue;
				if ((spModel.Position - curNode.Position).Dist() < 0.1)
				{
					curNode = path[0];
					path.RemoveAt(0);
				}
				spModel.GlFocus(curNode.Position);
				spModel.LoTranslate(0.0, 0.0, -0.1);
			}
        }
    }
}
