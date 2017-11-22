#include "StdHeapDijkstra.h"

namespace
{

const auto HeapComparePredicat = [](const HeapNode& node1, const HeapNode& node2)
{
	return node1.second > node2.second;
};

}

StdHeapDijkstra::StdHeapDijkstra(const std::string & filename)
	: BaseGraph(filename)
{
	// Создаем кучу
	m_heap.reserve(m_n);
	for (size_t i = 0; i < m_n; ++i)
		m_heap.push_back({ i, m_lengths[i] });
	std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);

	m_isMarked.clear();
}

StdHeapDijkstra::StdHeapDijkstra(const GraphData& data)
	: BaseGraph(data)
{
	// Создаем кучу
	m_heap.reserve(m_n);
	for (size_t i = 0; i < m_n; ++i)
		m_heap.push_back({ i, m_lengths[i] });
	std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);

	m_isMarked.clear();
}

//StdHeapDijkstra::StdHeapDijkstra(const StdHeapDijkstra& data)
//	: BaseGraph(data)
//{
//	// Создаем кучу
//	m_heap.reserve(m_n);
//	for (size_t i = 0; i < m_n; ++i)
//		m_heap.push_back({ i, m_lengths[i] });
//	std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);
//
//	m_isMarked.clear();
//}

void StdHeapDijkstra::Solve()
{
	m_startTime = clock();

	for (size_t i = 0; i < m_n; ++i)
	{
		// Вершина с наименьшей длиной среди не помеченных.
		const auto minElement = m_heap.front();
		std::pop_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);
		m_heap.pop_back();

		m_lengths[minElement.first] = minElement.second;

		// Если расстояние до нее - INT_MAX, значит вершина не достижима из m_start
		// и эту итерацию можно останавливать
		if (minElement.second == INT_MAX) continue;
		// Просматриваем все ребра, начинающиеся из minIndex
		for (size_t j = 0; j < m_heap.size(); ++j)
		{
			const auto ih = m_heap[j].first;
			const auto ie = minElement.first;
			if (m_adjMat[ie][ih] > 0)
			{
				const auto min = std::min(m_heap[j].second, minElement.second + m_adjMat[ie][ih]);
				// При успешной релаксации записываем предка
				if (m_heap[j].second != min)
				{
					m_parents[ih] = ie;
					m_heap[j].second = min;
				}
			}
		}
		std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);
	}

	m_endTime = clock();

	// Формируем итоговые пути
	m_paths.resize(m_n);
	for (size_t pntTo = 0; pntTo < m_n; ++pntTo)
	{
		for (size_t pntFrom = pntTo; pntFrom != m_start; pntFrom = m_parents[pntFrom])
			m_paths[pntTo].push_back(pntFrom);
		m_paths[pntTo].push_back(m_start);
		std::reverse(m_paths[pntTo].begin(), m_paths[pntTo].end());
	}
}