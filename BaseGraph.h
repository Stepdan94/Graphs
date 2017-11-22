#pragma once

#include "IGraph.h"

class BaseGraph : public IGraph
{
public:
	BaseGraph() = default;
	BaseGraph(const std::string& filename);
	BaseGraph(const GraphData& data);
	//BaseGraph(const BaseGraph& rhs);
	~BaseGraph() = default;

public:
	void Solve() override {}
	void Save(const std::string&) override;
	GraphData GetData() const override;

protected:
	size_t m_n;                    // Общее число вершин
	size_t m_start;                // Стартовая позиция
	std::vector<size_t> m_lengths; // Вектор длин
	std::vector<size_t> m_parents; // Вектор предков (для восстановления пути)
	std::vector<bool> m_isMarked;  // Вектор флагов (помечена вершина или нет) P.S. Да-да, вектор bool =)
	iMatrix m_adjMat;              // Матрица смежности. Значение элемента - вес ребра.
	iMatrix m_paths;               // Итоговые пути до вершин

	time_t m_startTime, m_endTime; // Временные засечки
};