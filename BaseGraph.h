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
	size_t m_n;                    // ����� ����� ������
	size_t m_start;                // ��������� �������
	std::vector<size_t> m_lengths; // ������ ����
	std::vector<size_t> m_parents; // ������ ������� (��� �������������� ����)
	std::vector<bool> m_isMarked;  // ������ ������ (�������� ������� ��� ���) P.S. ��-��, ������ bool =)
	iMatrix m_adjMat;              // ������� ���������. �������� �������� - ��� �����.
	iMatrix m_paths;               // �������� ���� �� ������

	time_t m_startTime, m_endTime; // ��������� �������
};