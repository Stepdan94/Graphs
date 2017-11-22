#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <tuple>
#include <memory>

using iMatrix = std::vector<std::vector<int>>;
using GraphData = std::tuple<size_t, size_t, iMatrix>;

enum class GraphType
{
	SimpleDijkstra,
	StdHeapDijkstra,
	SimplePrim,
	StdHeapPrim
};

enum class EdgeCount
{
	Dense, // Плотный граф, много ребер у каждой вершины
	Sparse // Разреженный граф, мало ребер у каждой вершины ( << n^2 )
};

struct GenerateData
{
	size_t n;
	size_t start;
	EdgeCount edgeCount;
};

/*
HeapNode - элемент std кучи:
size_t - номер вершины
size_t - длина
*/
using HeapNode = std::pair<size_t, size_t>;