#pragma once

#include "BaseGraph.h"

class SimplePrim : public BaseGraph
{
public:
	SimplePrim() = default;
	SimplePrim(const std::string& filename);
	SimplePrim(const GraphData& data);
	//SimpleDijkstra(const SimpleDijkstra& data);
	~SimplePrim() = default;

	void Solve() override;
};