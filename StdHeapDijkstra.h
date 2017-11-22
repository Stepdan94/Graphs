#pragma once

#include "BaseGraph.h"

class StdHeapDijkstra : public BaseGraph
{
public:
	StdHeapDijkstra() = default;
	StdHeapDijkstra(const std::string& filename);
	StdHeapDijkstra(const GraphData& data);
	//StdHeapDijkstra(const StdHeapDijkstra& data);
	~StdHeapDijkstra() = default;

	void Solve() override;

private:
	std::vector<HeapNode> m_heap;
};
