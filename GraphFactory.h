#pragma once

#include "IGraph.h"

class GraphFactory
{
public:
	GraphFactory() = default;
	~GraphFactory() = default;

	std::shared_ptr<IGraph> CreateGraph(GraphType type, const std::string& filename);
	std::shared_ptr<IGraph> CreateGraph(GraphType type, const GenerateData& genData);
	std::shared_ptr<IGraph> CreateGraph(GraphType type, const GraphData& graphData);

private:
	GraphData GenerateGraphData(const GenerateData& genData);
};