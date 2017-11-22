#include "GraphFactory.h"

#include "SimpleDijkstra.h"
#include "StdHeapDijkstra.h"
#include "SimplePrim.h"
#include "StdHeapPrim.h"

std::shared_ptr<IGraph> GraphFactory::CreateGraph(GraphType type, const std::string& filename)
{
	std::shared_ptr<IGraph> graph;

	switch (type)
	{
	case GraphType::SimpleDijkstra:
		graph.reset(new SimpleDijkstra(filename));
		break;
	case GraphType::StdHeapDijkstra:
		graph.reset(new StdHeapDijkstra(filename));
		break;
	case GraphType::SimplePrim:
		graph.reset(new SimplePrim(filename));
		break;
	case GraphType::StdHeapPrim:
		graph.reset(new StdHeapPrim(filename));
		break;
	}

	return graph;
}

std::shared_ptr<IGraph> GraphFactory::CreateGraph(GraphType type, const GenerateData& genData)
{
	const auto graphData = GenerateGraphData(genData);

	std::shared_ptr<IGraph> graph;

	switch (type)
	{
	case GraphType::SimpleDijkstra:
		graph.reset(new SimpleDijkstra(graphData));
		break;
	case GraphType::StdHeapDijkstra:
		graph.reset(new StdHeapDijkstra(graphData));
		break;
	case GraphType::SimplePrim:
		graph.reset(new SimplePrim(graphData));
		break;
	case GraphType::StdHeapPrim:
		graph.reset(new StdHeapPrim(graphData));
		break;
	}

	return graph;
}

std::shared_ptr<IGraph> GraphFactory::CreateGraph(GraphType type, const GraphData& graphData)
{
	std::shared_ptr<IGraph> graph;

	switch (type)
	{
	case GraphType::SimpleDijkstra:
		graph.reset(new SimpleDijkstra(graphData));
		break;
	case GraphType::StdHeapDijkstra:
		graph.reset(new StdHeapDijkstra(graphData));
		break;
	case GraphType::SimplePrim:
		graph.reset(new SimplePrim(graphData));
		break;
	case GraphType::StdHeapPrim:
		graph.reset(new StdHeapPrim(graphData));
		break;
	}

	return graph;
}

GraphData GraphFactory::GenerateGraphData(const GenerateData& genData)
{
	int n = genData.n;
	int start = genData.start;
	int edgeCount = (genData.edgeCount == EdgeCount::Sparse) ? int(0.005 * n) : n / 2;

	srand(time(NULL)); // сИдим

	iMatrix adjMat;
	std::vector<std::vector<int>>(n, std::vector<int>(n, 0)).swap(adjMat);

	std::vector<int> path;
	// Генерируем пути от точки старта до i
	for (size_t i = 0; i < n; ++i)
	{
		if (i == start) continue;

		size_t length = rand() % edgeCount + 2; // Длина нового пути
		std::vector<int>(length, -1).swap(path);
		path[0] = start;
		for (size_t j = 1; j < length; ++j)
		{
			// Генерим новую точку пути
			int point;
			do {
				point = rand() % n;
			} while (point == start || std::find(path.begin(), path.end(), point) != path.end());
			path[j] = point;
		}

		// Заполняем матрицу смежности согласно пути
		// Данные могут переписываться, т.к. значение матрицы - вес ребра, они случайны
		for (size_t j = 0; j < path.size() - 1; ++j)
			adjMat[path[j]][path[j + 1]] = rand() % 10 + 1;
	}

	return{ n, start, adjMat };
}