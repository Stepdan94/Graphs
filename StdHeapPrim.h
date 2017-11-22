#pragma once

#include "BaseGraph.h"

class StdHeapPrim : public BaseGraph
{
public:
	StdHeapPrim() = default;
	StdHeapPrim(const std::string& filename);
	StdHeapPrim(const GraphData& data);
	~StdHeapPrim() = default;

	void Solve() override;

private:
	std::vector<HeapNode> m_heap;
};
