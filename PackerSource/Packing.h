#pragma once
#include <list>
#include <vector>
#include <set>


/*  ��������� - ������� ��� ����� �����.
 *  ���������� � ������ ����� �����: ������� � ���������� start_x ��� ����� ����� ������ h_level �� start_x ���������� �������� ������
 *
 */
struct strip_level_t {
	float start_x;
	float h_level;
};

/* ��������� - �������������. ������ w, ������ h, ���������� ������ ������� ���� (x, y)
 * ����������� ����� ������������� ���������� id ����� ������� �������������� � set'�
 */
struct rect_t {
	float x, y;
	float w, h;

	int id;
};


// ������� ������: ������ ��������������� � �������������� ��������� � ���������� ������ ��������
struct solution_t {
	std::vector<rect_t> solution_rect;
	float solution_height;
};

// �����, �������� �������� �������� ��������������� � ��������������� ����� � ������������� ������� ����� ������� ������ � ������
class StripSolver {
public:
	StripSolver():
		node_count_(0), solution_min_height_(INFINITY), best_solution_() {}

	// ������������� ������ �����. ����������� ������ SolveStrip ���������� ������������� ������
	void SetStripWidth(float width) { STRIP_W = width; }

	// ������ ������ �� ������������� ����� ������ �� ������ ������� ���������������
	solution_t SolveStrip(const std::vector<rect_t>& input);
private:
	float STRIP_W = 100;
	size_t node_count_;
	float solution_min_height_;
	std::vector<rect_t> best_solution_;

	// ��������� ������������� rect �� ����� �� �������� ����� ����� strip, ����� � � ������ ���������. ����� ������������� �� ��������� �������
	float AddRect(std::list<strip_level_t>& strip, rect_t& rect);

	// ��������� ������� �� ������ ����� ����� strip � ������ ���������� ��������������� rects
	float GetMaximumSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects);

	// ���������������� ������� �� ������ ����� ����� � ������ ���������� ���������������.
	float GetMinimunSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects);

	// ���������� ������ ������� ������ �������. ������������� ��������� best_solution_ � solution_min_height �� ������ �������
	void CalcNode(const std::list<strip_level_t>& strip, const std::set<rect_t>& rect, std::vector<rect_t> solution);
};

