#include "../../PackerSource/Packing.h"
#include <iostream>

int main() {
	float strip_w, strip_h;
	size_t rect_count;
	std::vector<rect_t> rect;

	std::cin >> strip_w;
	std::cin >> rect_count;
	rect.resize(rect_count);
	for (int i = 0; i < rect_count; i++) {
		std::cin >> rect[i].w >> rect[i].h;
		rect[i].id = i;
		if (rect[i].w > strip_w) {
			std::cout << "Incorrect input\nExiting...\n";
			return -1;
		}
	}

	StripSolver ssolver;
	ssolver.SetStripWidth(strip_w);
	auto solution = ssolver.SolveStrip(rect);
	rect = solution.solution_rect;
	strip_h = solution.solution_height;

	std::cout << "Solution: minimum height = " << strip_h << "\n";
	float total_S = 0;
	for (int i = 0; i < rect.size(); i++) {
		std::cout << "Rect " << i + 1 << ": Size = {" << rect[i].w << ", " << rect[i].h << "} " <<
			"Position: {" << rect[i].x << ", " << rect[i].y << "}\n";
		total_S += rect[i].w * rect[i].h;
	}
	std::cout << "Solution efficenty: " << total_S / (strip_w * strip_h) * 100.f << "%\n";

	return 0;
}