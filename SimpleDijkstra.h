#pragma once

#include "BaseGraph.h"

class SimpleDijkstra : public BaseGraph
{
public:
	SimpleDijkstra() = default;
	SimpleDijkstra(const std::string& filename);
	SimpleDijkstra(const GraphData& data);
	//SimpleDijkstra(const SimpleDijkstra& data);
	~SimpleDijkstra() = default;

	void Solve() override;
};