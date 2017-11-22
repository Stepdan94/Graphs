#include "GraphFactory.h"

#include <iostream>

void main()
{
	GraphFactory factory;
	GraphData graphData;
	GenerateData genData{ 1000, 0, EdgeCount::Dense };

	auto simpleDijkstra = factory.CreateGraph(GraphType::SimpleDijkstra, genData);
	simpleDijkstra->Solve();
	simpleDijkstra->Save("Test/SimpleDijkstra.txt");
	graphData = simpleDijkstra->GetData();
	simpleDijkstra.reset();

	std::cout << "SimpleDijkstra completed!" << std::endl;

	auto stdHeapDijkstra = factory.CreateGraph(GraphType::StdHeapDijkstra, graphData);
	graphData.swap(GraphData());
	stdHeapDijkstra->Solve();
	stdHeapDijkstra->Save("Test/StdHeapDijkstra.txt");
	graphData = stdHeapDijkstra->GetData();
	stdHeapDijkstra.reset();

	std::cout << "StdHeapDijkstra completed!" << std::endl;

	auto simplePrim = factory.CreateGraph(GraphType::SimplePrim, graphData);
	graphData.swap(GraphData());
	simplePrim->Solve();
	simplePrim->Save("Test/SimplePrim.txt");
	graphData = simplePrim->GetData();
	simplePrim.reset();

	std::cout << "SimplePrim completed!" << std::endl;

	auto stdHeapPrim = factory.CreateGraph(GraphType::StdHeapPrim, graphData);
	graphData.swap(GraphData());
	stdHeapPrim->Solve();
	stdHeapPrim->Save("Test/StdHeapPrim.txt");
	stdHeapPrim.reset();

	std::cout << "StdHeapPrim completed!" << std::endl;

	system("pause");
}