#pragma once

#include "Types.h"

class IGraph
{
public:
	virtual ~IGraph() = default;

	virtual void Solve() = 0;
	virtual void Save(const std::string&) = 0;
	virtual GraphData GetData() const = 0;
};