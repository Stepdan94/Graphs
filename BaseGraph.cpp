#include "BaseGraph.h"

#include <fstream>

BaseGraph::BaseGraph(const std::string& filename)
{
	std::ifstream in(filename);
	in >> m_n >> m_start;
	std::vector<std::vector<int>>(m_n, std::vector<int>(m_n)).swap(m_adjMat);
	for (size_t i = 0; i < m_n; ++i)
		for (size_t j = 0; j < m_n; ++j)
			in >> m_adjMat[i][j];

	in.close();

	std::vector<size_t>(m_n, INT_MAX).swap(m_lengths);
	m_lengths[m_start] = 0;

	std::vector<bool>(m_n, false).swap(m_isMarked);

	m_parents.resize(m_n);
	m_parents[m_start] = m_start;
}

BaseGraph::BaseGraph(const GraphData& data)
{
	m_n      = std::get<0>(data);
	m_start  = std::get<1>(data);
	m_adjMat = std::get<2>(data);

	std::vector<size_t>(m_n, INT_MAX).swap(m_lengths);
	m_lengths[m_start] = 0;

	std::vector<bool>(m_n, false).swap(m_isMarked);

	m_parents.resize(m_n);
	m_parents[m_start] = m_start;
}

//BaseGraph::BaseGraph(const BaseGraph& rhs)
//{
//	this->m_n = rhs.m_n;
//	this->m_start = rhs.m_start;
//	this->m_adjMat = rhs.m_adjMat;
//
//	std::vector<size_t>(m_n, INT_MAX).swap(m_lengths);
//	m_lengths[m_start] = 0;
//
//	std::vector<bool>(m_n, false).swap(m_isMarked);
//
//	m_parents.resize(m_n);
//	m_parents[m_start] = m_start;
//}

void BaseGraph::Save(const std::string& filename)
{
	std::ofstream of(filename);

	of << "Solution time: " << ((double)m_endTime - m_startTime) / ((double)CLOCKS_PER_SEC) << std::endl;
	for (size_t i = 0; i < m_n; ++i)
	{
		of << "Index: " << i << "; Length: " << (m_lengths.empty() ? 0 : m_lengths[i]) << "; Path: ";
		for (size_t j = 0; j < m_paths[i].size(); ++j)
			of << "->" << m_paths[i][j];
		of << std::endl;
	}

	of.close();
}

GraphData BaseGraph::GetData() const
{
	return { m_n, m_start, m_adjMat };
}