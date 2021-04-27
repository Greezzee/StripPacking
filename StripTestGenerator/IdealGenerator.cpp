#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct rect_t {
	float w, h;
};

int main() {
	int test_count = 10;

	for (int i = 0; i < test_count; i++) {
		std::ofstream file(std::string("test") + std::to_string(i) +".txt");
		float W = (float)(std::rand() % 100000) / 1000.f + 20.f;
		float H = (float)(std::rand() % 100000) / 1000.f + 20.f;
		int rect_count = std::rand() % 10 + 4;
		std::vector<rect_t> out = { {W, H} };

		while (out.size() != rect_count) {
			int j = std::rand() % out.size();
			rect_t buf = out[j];
			out.erase(out.begin() + j, out.begin() + j + 1);
			float k = (float)(rand() % 9000) / 10000.f + 0.1;
			if (rand() % 2 == 0) {
				out.push_back({ buf.w, buf.h * k });
				out.push_back({ buf.w, buf.h * (1.f - k) });
			}
			else {
				out.push_back({ buf.w * k, buf.h });
				out.push_back({ buf.w * (1.f - k), buf.h });
			}
		}
		file << W + 0.001 << "\n";
		file << rect_count << "\n";

		for (int j = 0; j < rect_count; j++) {
			file << out[j].w << " " << out[j].h << "\n";
		}
		file.close();
	}
	return 0;
}