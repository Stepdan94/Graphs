#include "SimpleDijkstra.h"

/*
	Если алгоритм Дейкстры в методичке непонятен,
	то можно почитать здесь: http://e-maxx.ru/algo/dijkstra
*/

SimpleDijkstra::SimpleDijkstra(const std::string& filename)
	: BaseGraph(filename)
{
}

SimpleDijkstra::SimpleDijkstra(const GraphData& data)
	:BaseGraph(data)
{
}

//SimpleDijkstra::SimpleDijkstra(const SimpleDijkstra& data)
//	: BaseGraph(data)
//{
//}

void SimpleDijkstra::Solve()
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
		// Помечаем найденную
		m_isMarked[minIndex] = true;
		// Если расстояние до нее - INT_MAX, значит вершина не достижима из m_start
		// и эту итерацию можно останавливать
		if (m_lengths[minIndex] == INT_MAX) continue;
		// Просматриваем все ребра, начинающиеся из minIndex
		for (size_t j = 0; j < m_n; ++j)
		{
			if (m_adjMat[minIndex][j] > 0)
			{
				const auto min = std::min(m_lengths[j], m_lengths[minIndex] + m_adjMat[minIndex][j]);
				// При успешной релаксации записываем предка
				if (m_lengths[j] != min)
				{
					m_parents[j] = minIndex;
					m_lengths[j] = min;
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