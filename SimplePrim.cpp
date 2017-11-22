#include "SimplePrim.h"

#include <cassert>
#include <iostream>

/*
	Алгоритм Прима: http://www.e-maxx-ru.1gb.ru/algo/mst_prim
	Случай разреженных графов.
*/

SimplePrim::SimplePrim(const std::string& filename)
	: BaseGraph(filename)
{
}

SimplePrim::SimplePrim(const GraphData& data)
	: BaseGraph(data)
{
}

void SimplePrim::Solve()
{
	m_startTime = clock();

	for (size_t i = 0; i < m_n; ++i)
	{
		// Вершина с наименьшей длиной среди не помеченных.
		size_t minLength = INT_MAX;
		size_t minIndex;
		for (size_t j = 0; j < m_n; ++j)
		{
			if (!m_isMarked[j] && m_lengths[j] < minLength)
			{
				minIndex = j;
				minLength = m_lengths[j];
			}
		}

		if (m_lengths[minIndex] == INT_MAX)
		{
			assert(0 && "Алгоритм Прима: нет минимального остова!");
			std::cout << "Алгоритм Прима: нет минимального остова!" << std::endl;
			return;
		}

		// Помечаем найденную
		m_isMarked[minIndex] = true;

		// Просматриваем все ребра, начинающиеся из minIndex
		for (size_t j = 0; j < m_n; ++j)
		{
			if (m_adjMat[minIndex][j] > 0)
			{
				if (m_adjMat[minIndex][j] < m_lengths[j])
				{
					m_parents[j] = minIndex;
					m_lengths[j] = m_adjMat[minIndex][j];
				}
			}
		}
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