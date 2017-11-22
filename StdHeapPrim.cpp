#include "StdHeapPrim.h"

#include <cassert>
#include <iostream>

namespace
{

	const auto HeapComparePredicat = [](const HeapNode& node1, const HeapNode& node2)
	{
		return node1.second > node2.second;
	};

}

StdHeapPrim::StdHeapPrim(const std::string & filename)
	: BaseGraph(filename)
{
	// Создаем кучу
	m_heap.reserve(m_n);
	for (size_t i = 0; i < m_n; ++i)
		m_heap.push_back({ i, m_lengths[i] });
	std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);

	m_isMarked.clear();
	m_lengths.clear();
}

StdHeapPrim::StdHeapPrim(const GraphData& data)
	: BaseGraph(data)
{
	// Создаем кучу
	m_heap.reserve(m_n);
	for (size_t i = 0; i < m_n; ++i)
		m_heap.push_back({ i, m_lengths[i] });
	std::make_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);

	m_isMarked.clear();
	m_lengths.clear();
}

void StdHeapPrim::Solve()
{
	m_startTime = clock();

	for (size_t i = 0; i < m_n; ++i)
	{
		// Вершина с наименьшей длиной среди не помеченных.
		const auto minElement = m_heap.front();
		std::pop_heap(m_heap.begin(), m_heap.end(), HeapComparePredicat);
		m_heap.pop_back();

		if (minElement.second == INT_MAX)
		{
			assert(0 && "Алгоритм Прима: нет минимального остова!");
			std::cout << "Алгоритм Прима: нет минимального остова!" << std::endl;
			return;
		}

		// Просматриваем все ребра, начинающиеся из minIndex
		for (size_t j = 0; j < m_heap.size(); ++j)
		{
			const auto ih = m_heap[j].first;
			const auto ie = minElement.first;
			if (m_adjMat[ie][ih] > 0)
			{
				// При успешной релаксации записываем предка
				if (m_adjMat[ie][ih] < m_heap[j].second)
				{
					m_parents[ih] = ie;
					m_heap[j].second = m_adjMat[ie][ih];
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