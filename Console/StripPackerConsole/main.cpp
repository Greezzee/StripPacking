#include "../../PackerSource/Packing.h"
#include <iostream>

int main() {
	size_t rect_count;
	float strip_w_, strip_h_;
	strip_w_ = 80;
	rect_count = 13;
	std::cin >> strip_w_;
	int start_strip_count;
	std::list<strip_level_t> start_strip;
	start_strip.clear();
	std::cin >> start_strip_count;

	for (int i = 0; i < start_strip_count; i++) {
		float start_x, y;
		std::cin >> start_x >> y;
		start_strip.push_back({ start_x, y });
	}

	std::cin >> rect_count;
	std::vector<rect_t> rect_;
	rect_.resize(rect_count);

	for (size_t i = 0; i < rect_count; i++) {
		std::cin >> rect_[i].w >> rect_[i].h >> rect_[i].count;
		rect_[i].id = i;
		if (rect_[i].w > strip_w_) {
			std::cout << "Incorrect input\nExiting...\n";
			return -1;
		}
	}

	StripSolver ssolver;
	ssolver.SetStripWidth(strip_w_);
	auto solution = ssolver.SolveStrip(rect_, start_strip);
	rect_ = solution.solution_rect;
	strip_h_ = solution.solution_height;

	std::cout << "Solution: minimum height = " << strip_h_ << "\n";
	float total_S = 0;
	for (int i = 0; i < rect_.size(); i++) {
		std::cout << "Rect " << i + 1 << ": Size = {" << rect_[i].w << ", " << rect_[i].h << "} " <<
			"Position: {" << rect_[i].x << ", " << rect_[i].y << "}\n";
		total_S += rect_[i].w * rect_[i].h;
	}
	float real_S = strip_h_ * strip_w_;
	for (auto i = start_strip.begin(); std::next(i) != start_strip.end(); i++) {
		real_S -= i->h_level * (std::next(i)->start_x - i->start_x);
		solution.empty_space -= i->h_level * (std::next(i)->start_x - i->start_x);
	}
	real_S -= start_strip.back().h_level * (strip_w_ - start_strip.back().start_x);
	std::cout << "Solution efficenty: " << total_S / real_S * 100.f << "%\n";
	std::cout << "Solution empty_space: " << solution.empty_space << "\n";

	return 0;
}