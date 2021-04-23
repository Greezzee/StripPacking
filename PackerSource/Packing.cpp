#include "Packing.h"

bool operator<(const rect_t& a, const rect_t& b) {
	return a.id < b.id;
}

solution_t StripSolver::SolveStrip(const std::vector<rect_t>& input) {
	std::set<rect_t> input_set;
	for (size_t i = 0; i < input.size(); i++) {
		input_set.insert(input[i]);
	}

	std::list<strip_level_t> strip_top;
	strip_top.push_back({ 0, 0 });
	std::vector<rect_t> buf_solution;

	CalcNode(strip_top, input_set, buf_solution);

	solution_t out;
	out.solution_height = solution_min_height_;
	out.solution_rect = best_solution_;

	return out;
}

float StripSolver::AddRect(std::list<strip_level_t>& strip, rect_t& rect) {
	float min_h = INFINITY;
	auto new_pos = strip.begin();
	for (auto i = strip.begin(); i != strip.end(); i++) { // ищем подходящее место для прямоугольника (самое "низкое" из тех, куда он может встать)
		if (i->start_x + rect.w > STRIP_W) break;
		float m = i->h_level;
		for (auto j = std::next(i); j != strip.end() && j->start_x < i->start_x + rect.w; j++)
			if (j->h_level > m)
				m = j->h_level;
		float h = m + rect.h;
		if (h < min_h) {
			min_h = h;
			new_pos = i;
		}
	}

	float old_h = new_pos->h_level; // редактируем карту высот с учётом появления нового прямоугольника
	new_pos->h_level = min_h;
	strip.insert(std::next(new_pos), { new_pos->start_x + rect.w, 0 });
	auto end = std::next(new_pos);
	while (std::next(end) != strip.end() && end->start_x > std::next(end)->start_x) {
		old_h = std::next(end)->h_level;
		strip.erase(std::next(end));
	}
	end->h_level = old_h;
	float max = 0;
	for (auto i = strip.begin(); i != strip.end(); i++) // ищем наивысшую точку чтобы вернуть её
		if (i->h_level > max)
			max = i->h_level;
	rect.x = new_pos->start_x; // устанавливаем координаты верхнего левого угла
	rect.y = new_pos->h_level;
	return max;
}

float StripSolver::GetMaximumSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects) {
	float max_h = 0;
	for (auto i = strip.begin(); i != strip.end(); i++) // ищем наивысшую точку
		if (i->h_level > max_h)
			max_h = i->h_level;
	for (auto i = rects.begin(); i != rects.end(); i++) // складываем все прямоугольники на неё в один столб
		max_h += i->h;
	return max_h;
}

float StripSolver::GetMinimunSolution(const std::list<strip_level_t>& strip, const std::set<rect_t>& rects) {
	float max_h = 0;
	for (auto i = strip.begin(); i != strip.end(); i++) // ищем наивысшую точку
		if (i->h_level > max_h)
			max_h = i->h_level;

	float total_square = 0;
	for (auto i = rects.begin(); i != rects.end(); i++) // ищем суммарную площадь прямоугольников
		total_square += i->w * i->h;

	for (auto i = strip.begin(); std::next(i) != strip.end(); i++) // для поиска идеализированного решения, представим прямоугольники "жидкостью" и "выльем" её на карту высот
		total_square -= (std::next(i)->start_x - i->start_x) * i->h_level;

	if (total_square < 0.f)
		return max_h;

	return max_h + total_square / STRIP_W;
}

void StripSolver::CalcNode(const std::list<strip_level_t>& strip, const std::set<rect_t>& rect, std::vector<rect_t> solution) {
	node_count_++;
	for (auto i = rect.begin(); i != rect.end(); i++) { // создаём ветви решений
		std::list<strip_level_t> strip_buf = strip;
		rect_t buf_rect = *i;
		float new_h = AddRect(strip_buf, buf_rect);
		if (rect.size() == 1) { // если отстался всего один прямоугольник - заканчиваем решение и проверяем его на эффективность
			if (new_h <= solution_min_height_) {
				solution.push_back(buf_rect);
				best_solution_ = solution;
				solution_min_height_ = new_h;
			}
			return;
		}

		std::set<rect_t> rects_buf = rect; // ищем минимум решения с выбранным прямоугольником
		rects_buf.erase(*i);
		if (GetMinimunSolution(strip_buf, rects_buf) > solution_min_height_) // если идеальное решение хуже какого-то уже найденного или другого максимального - отбрасываем
			return;

		float max_h = GetMaximumSolution(strip_buf, rects_buf); // ищем максимальное решение. Если оно лучше, чем любое другое ранее найденное - устанавливаем найденное
		if (max_h < solution_min_height_) {
			solution_min_height_ = max_h;
		}

		solution.push_back(buf_rect);
		CalcNode(strip_buf, rects_buf, solution); // продолжим построение дерева уже без этого прямоугольника
		solution.pop_back();
	}
}