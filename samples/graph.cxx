#include <FK/FK.h>

using namespace FK;
using namespace std;

fk_GraphEdge * MakeEdge(fk_Graph *argGraph, bool argMode,
						unsigned int argID1, unsigned int argID2)
{
	fk_GraphNode *v1 = argGraph->getNode(argID1);
	fk_GraphNode *v2 = argGraph->getNode(argID2);

	return argGraph->makeEdge(argMode, v1, v2);
}

int main(int, char **)
{
	fk_Material::initDefault();
	constexpr int SIZE = 40;
	constexpr double HALF = double(SIZE-1)/2.0;
	unique_ptr<fk_AppWindow> window(new fk_AppWindow());
	unique_ptr<fk_Model> model(new fk_Model());
	unique_ptr<fk_Graph> graph(new fk_Graph(SIZE*SIZE));

	window->setSize(800, 800);
	window->setBGColor(0.6, 0.7, 0.8);
	window->setCameraPos(0.0, 0.0, 100.0);
	window->setCameraFocus(0.0, 0.0, 0.0);
	window->open();
	window->setTrackBallMode(true);

	fk_Vector P;
	fk_GraphEdge *edge;

	for(unsigned int i = 0; i < SIZE; ++i) {
		for(unsigned int j = 0; j < SIZE; ++j) {
			P.set(double(j) - HALF, double(i) - HALF, 0.0);
			graph->getNode(i*SIZE + j)->setPosition(P);

			if(j != SIZE-1) {
				edge = MakeEdge(graph.get(), true, i*SIZE+j, i*SIZE + j+1);
				edge->setColor(fk_Color(1.0, 0.0, 0.0));
			}
			if(i != SIZE-1) {
				edge = MakeEdge(graph.get(), true, i*SIZE+j, (i+1)*SIZE + j);
				edge->setColor(fk_Color(1.0, 0.0, 0.0));
			}
			if(i != SIZE-1 && j != SIZE-1) {
				edge = MakeEdge(graph.get(), false, i*SIZE + j, (i+1)*SIZE + j+1);
				edge->setColor(fk_Color(0.0, 0.0, 1.0));
			}				
			if(i != SIZE-1 && j != 0) {
				edge = MakeEdge(graph.get(), false, (i+1)*SIZE + j-1, i*SIZE + j);
				edge->setColor(fk_Color(0.0, 0.0, 1.0));
			}
		}
	}
	for(unsigned int i = 0; i < graph->getMaxEdgeID(); ++i) {
		edge = graph->getEdge(i);
		if(edge == nullptr) continue;
		edge->setIntCost(0, 1);
	}

	if(graph->makeCostTable(0, fk_CostType::INT) == false) fk_Window::printf("Error1");
	if(graph->setCostDirection(0, fk_CostDirection::FORWARD) == false) fk_Window::printf("Error2");
	if(graph->setEdgeCostID(0, 0) == false) fk_Window::printf("Error3");
	graph->setStart(0, graph->getNode(SIZE*(SIZE/2 + 5) + SIZE/2 - 4));
	graph->addGoal(0, graph->getNode(SIZE - 2));

	if(graph->makeCostTable(1, fk_CostType::LENGTH) == false) fk_Window::printf("Error4");
	if(graph->setCostDirection(1, fk_CostDirection::BACK) == false) fk_Window::printf("Error5");
	graph->setStart(1, graph->getNode(SIZE*(SIZE/2 + 5) + 3));
	graph->addGoal(1, graph->getNode(4*SIZE + 1));
	graph->addGoal(1, graph->getNode(8*SIZE + (SIZE - 2)));

	graph->initCostTable(0);
	while(graph->updateCostTable(0) == fk_CostStatus::CONTINUE);

	graph->initCostTable(1);
	while(graph->updateCostTable(1) == fk_CostStatus::CONTINUE);


	unsigned int costID = graph->getNodeCostID(0);
	double max = -1.0;
	double cost;
	fk_GraphNode *node;
	list<fk_GraphNode *> neighbor;

	for(unsigned int i = 0; i < graph->getNodeSize(); ++i) {
		node = graph->getNode(i);
		cost = double(node->getIntCost(costID));
		if(cost > max) max = cost;
	}

	fk_Color red(1.0, 0.0, 0.0);
	fk_Color blue(0.0, 0.0, 1.0);
	fk_Color col;
	for(unsigned int i = 0; i < graph->getNodeSize(); ++i) {
		node = graph->getNode(i);
		cost = double(node->getIntCost(costID));
		double t = cost/max;
		col = (1.0 - t)*red + t*blue;
		node->setColor(&col);
	}

	auto path = graph->getOnePath(0);
	
	model->setPointColor(1.0, 0.0, 0.0);
	model->setLineColor(0.0, 0.0, 1.0);
	model->setSize(5.0);
	model->setShape(graph.get());
	model->setDrawMode(fk_Draw::LINE | fk_Draw::POINT);
	model->setElementMode(fk_ElementMode::ELEMENT);
	window->entry(model.get());

	unique_ptr<fk_Model> spModel(new fk_Model());
	unique_ptr<fk_Sphere> sphere(new fk_Sphere(4, 1.0));
	spModel->setShape(sphere.get());
	spModel->setMaterial(Material::Yellow);
	window->entry(spModel.get());
	fk_GraphNode *curNode = nullptr;
	if(path.empty() == false) {
		spModel->glMoveTo(path.front()->getPosition());
		path.pop_front();
		curNode = path.front();
	}

	for(unsigned int i = 0; window->update() == true; ++i) {
		if(path.empty() == true) continue;
		if((spModel->getPosition() - curNode->getPosition()).dist() < 0.1) {
			curNode = path.front();
			path.pop_front();
		}
		spModel->glFocus(curNode->getPosition());
		spModel->loTranslate(0.0, 0.0, -0.1);
	}

	return 0;
}

