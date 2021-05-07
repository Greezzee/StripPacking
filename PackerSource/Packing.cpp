#include "Packing.h"

bool operator<(const rect_t& a, const rect_t& b) {
	return a.id < b.id;
}

solution_t StripSolver::SolveStrip(const std::vector<rect_t>& input, const std::list<strip_level_t> start_level) {
	std::set<rect_t> input_set;
	for (size_t i = 0; i < input.size(); i++) {
		input_set.insert(input[i]);
	}

	strip_t strip_top;
	strip_top.level = start_level;
	strip_top.empty_space = 0;
	strip_top.effective_space = 0;
	std::vector<rect_t> buf_solution;

	CalcNode(strip_top, input_set, buf_solution);

	solution_t out;
	out.solution_height = solution_min_height_;
	out.solution_rect = best_solution_;
	out.empty_space = solution_min_empty_;

	return out;
}

float StripSolver::AddRect(strip_t& strip, rect_t& rect) {
	float min_h = INFINITY;
	auto& level = strip.level;
	auto new_pos = level.begin();
	for (auto i = level.begin(); i != level.end(); i++) { // ищем подходящее место для прямоугольника (самое "низкое" из тех, куда он может встать)
		if (i->start_x + rect.w > STRIP_W) break;
		float m = i->h_level;
		for (auto j = std::next(i); j != level.end() && j->start_x < i->start_x + rect.w; j++)
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
	level.insert(std::next(new_pos), { new_pos->start_x + rect.w, 0 });
	auto end = std::next(new_pos);
	while (std::next(end) != level.end() && end->start_x > std::next(end)->start_x) {
		old_h = std::next(end)->h_level;
		level.erase(std::next(end));
	}
	end->h_level = old_h;
	float max = 0;
	for (auto i = level.begin(); i != level.end(); i++) // ищем наивысшую точку чтобы вернуть её
		if (i->h_level > max)
			max = i->h_level;
	rect.x = new_pos->start_x; // устанавливаем координаты верхнего левого угла
	rect.y = new_pos->h_level;
	float new_space = rect.h * rect.w;
	//strip.center_of_mass_y = ((strip.center_of_mass_y * strip.total_mass) + (rect.y - rect.h / 2.f) * new_mass) / (strip.total_mass + new_mass);
	strip.effective_space += new_space;
	strip.empty_space = 0;
	for (auto i = level.begin(); i != level.end(); i++) {
		float start;
		if (std::next(i) == level.end())
			start = STRIP_W;
		else
			start = std::next(i)->start_x;
		strip.empty_space += i->h_level * (start - i->start_x);
	}
	strip.empty_space -= strip.effective_space;
	return max;
}

float StripSolver::GetMaximumSolution(const strip_t& strip, const std::set<rect_t>& rects) {
	float max_h = 0;
	auto& level = strip.level;
	auto strip_buf = strip;
	auto rect_buf = rects;
	for (auto i = rect_buf.begin(); i != rect_buf.end(); i++)
		for (int j = 0; j < i->count; j++) {
		auto rect = *i;
		max_h = AddRect(strip_buf, rect);
	}
	return max_h;
}

float StripSolver::GetMaxEmptySpace(const strip_t& strip, const std::set<rect_t>& rects) {
	auto strip_buf = strip;
	for (auto i = rects.begin(); i != rects.end(); i++)
		for (int j = 0; j < i->count; j++) {
			auto rect = *i;
			AddRect(strip_buf, rect);
		}
	return strip_buf.empty_space;
}

float StripSolver::GetMinimunSolution(const strip_t& strip, const std::set<rect_t>& rects) {
	float max_h = 0;
	auto& level = strip.level;
	for (auto i = level.begin(); i != level.end(); i++) // ищем наивысшую точку
		if (i->h_level > max_h)
			max_h = i->h_level;

	float total_square = 0;
	for (auto i = rects.begin(); i != rects.end(); i++) // ищем суммарную площадь прямоугольников
		total_square += i->w * i->h * i->count;

	for (auto i = level.begin(); i != level.end(); i++) { // для поиска идеализированного решения, представим прямоугольники "жидкостью" и "выльем" её на карту высот
		float start;
		if (std::next(i) == level.end())
			start = STRIP_W;
		else
			start = std::next(i)->start_x;
		total_square -= (start - i->start_x) * (max_h - i->h_level);
	}

	if (total_square < 0.f)
		return max_h;

	return max_h + total_square / STRIP_W;
}

void StripSolver::CalcNode(const strip_t& strip, const std::set<rect_t>& rect, std::vector<rect_t> solution) {
	node_count_++;
	auto& level = strip.level;
	for (auto i = rect.begin(); i != rect.end(); i++) { // создаём ветви решений
		auto strip_buf = strip;
		rect_t buf_rect = *i;
		float new_h = AddRect(strip_buf, buf_rect);
		if (rect.size() == 1 && buf_rect.count == 1) { // если отстался всего один прямоугольник - заканчиваем решение и проверяем его на эффективность
			if (new_h < solution_min_height_ || 
			   (new_h - solution_min_height_ <= 1e-5f && strip_buf.empty_space < solution_min_empty_) ||
			   (new_h <= solution_min_height_ && best_solution_.empty())) {
				solution.push_back(buf_rect);
				best_solution_ = solution;
				solution_min_height_ = new_h;
				subsolution_min_height_ = new_h;
				solution_min_empty_ = strip_buf.empty_space;
				subsolution_min_empty_ = strip_buf.empty_space;
			}
			return;
		}

		std::set<rect_t> rects_buf = rect; // ищем минимум решения с выбранным прямоугольником
		rects_buf.erase(*i);
		if (i->count > 1) {
			buf_rect.count--;
			rects_buf.insert(buf_rect);
		}

		float min_h = GetMinimunSolution(strip_buf, rects_buf);
		if (min_h > subsolution_min_height_) // если идеальное решение хуже какого-то уже найденного или другого максимального - отбрасываем
			return;
		if (subsolution_min_height_ - min_h <= 0e-5f && subsolution_min_empty_ < strip_buf.empty_space) // если идеальное решение близко к уже найденному, но хуже по плотности - отбрасываем
			return;

		float max_h = GetMaximumSolution(strip_buf, rects_buf); // ищем максимальное решение. Если оно лучше, чем любое другое ранее найденное - устанавливаем найденное
		if (max_h < subsolution_min_height_) {
			subsolution_min_height_ = max_h;
		}

		float max_empt = GetMaxEmptySpace(strip_buf, rects_buf);
		if (max_empt < subsolution_min_empty_) {
			subsolution_min_empty_ = max_empt;
		}

		solution.push_back(buf_rect);
		CalcNode(strip_buf, rects_buf, solution); // продолжим построение дерева уже без этого прямоугольника
		solution.pop_back();
	}
}