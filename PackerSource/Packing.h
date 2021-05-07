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

	int count;

	int id;
};

struct strip_t {
	std::list<strip_level_t> level;
	float effective_space;
	float empty_space;
};

// ������� ������: ������ ��������������� � �������������� ��������� � ���������� ������ ��������
struct solution_t {
	std::vector<rect_t> solution_rect;
	float solution_height;
	float empty_space;
};

// �����, �������� �������� �������� ��������������� � ��������������� ����� � ������������� ������� ����� ������� ������ � ������
class StripSolver {
public:
	StripSolver():
		node_count_(0), solution_min_height_(INFINITY), subsolution_min_height_(INFINITY), solution_min_empty_(0), subsolution_min_empty_(0), best_solution_() {}

	// ������������� ������ �����. ����������� ������ SolveStrip ���������� ������������� ������
	void SetStripWidth(float width) { STRIP_W = width; }

	// ������ ������ �� ������������� ����� ������ �� ������ ������� ���������������
	solution_t SolveStrip(const std::vector<rect_t>& input, const std::list<strip_level_t> start_level);
private:
	float STRIP_W = 100;
	size_t node_count_;
	float solution_min_height_, subsolution_min_height_;
	float solution_min_empty_, subsolution_min_empty_;
	std::vector<rect_t> best_solution_;

	// ��������� ������������� rect �� ����� �� �������� ����� ����� strip, ����� � � ������ ���������. ����� ������������� �� ��������� �������
	float AddRect(strip_t& strip, rect_t& rect);

	// ��������� ������� �� ������ ����� ����� strip � ������ ���������� ��������������� rects
	float GetMaximumSolution(const strip_t& strip, const std::set<rect_t>& rects);

	//��������� ��������� �������������
	float GetMaxEmptySpace(const strip_t& strip, const std::set<rect_t>& rects);

	// ���������������� ������� �� ������ ����� ����� � ������ ���������� ���������������.
	float GetMinimunSolution(const strip_t& strip, const std::set<rect_t>& rects);

	// ���������� ������ ������� ������ �������. ������������� ��������� best_solution_ � solution_min_height �� ������ �������
	void CalcNode(const strip_t& strip, const std::set<rect_t>& rect, std::vector<rect_t> solution);
};

