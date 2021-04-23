#pragma once
#include <list>
#include <vector>
#include <set>


/*  Структура - элемент для карты высот.
 *  Помещенная в список имеет смысл: начиная с координаты start_x вся лента имеем высоту h_level до start_x следующего элемента списку
 *
 */
struct strip_level_t {
	float start_x;
	float h_level;
};

/* Структура - прямоугольник. Ширина w, высота h, координата левого правого угла (x, y)
 * Обязательно нужно останавливать уникальный id чтобы хранить прямоугольники в set'е
 */
struct rect_t {
	float x, y;
	float w, h;

	int id;
};


// Решение задачи: вектор прямоугольников с установленными позициями и полученная высота упаковки
struct solution_t {
	std::vector<rect_t> solution_rect;
	float solution_height;
};

// Класс, решающий проблему упаковки прямоугольников в полубесконечную ленту с установленной шириной ленты методом ветвей и границ
class StripSolver {
public:
	StripSolver():
		node_count_(0), solution_min_height_(INFINITY), best_solution_() {}

	// Устанавливает ширину ленты. Последующие вызовы SolveStrip используют установленную ширину
	void SetStripWidth(float width) { STRIP_W = width; }

	// Решить задачу на установленной ранее ширине на данном векторе прямоугольников
	solution_t SolveStrip(const std::vector<rect_t>& input);
private:
	float STRIP_W = 100;
	size_t node_count_;
	float solution_min_height_;
	std::vector<rect_t> best_solution_;

	// Добавляет прямоугольник rect на ленту по заданной карте высот strip, меняя её с учётом установки. Кладёт прямоугольник на наилучшую позицию
	float AddRect(std::list<strip_level_t>& strip, rect_t& rect);

	// Наихудшее решение на данной карте высот strip и данным множеством прямоугольников rects
	float GetMaximumSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects);

	// Идеализированное решение на данной карте высот и данным множеством прямоугольников.
	float GetMinimunSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects);

	// Рекурсивно создаёт вершины дерева решений. Автоматически установит best_solution_ и solution_min_height на лучшее решение
	void CalcNode(const std::list<strip_level_t>& strip, const std::set<rect_t>& rect, std::vector<rect_t> solution);
};

