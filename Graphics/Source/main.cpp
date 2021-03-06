//#include <vld.h>
#include <iostream>
#include "../../PackerSource/Packing.h"
#include "../Engine/AllEngine.h"
#include <algorithm>
#include <unordered_set>
#include <set>


class PackScene : public Scene
{
public:
	void Init() {
		View view;
		view.real_size = Vector2F(1280, 720);
		view.unit_vector = Vector2F(1, -1);
		view_id_ = GraphicManager::AddView(view);
		view_ = GraphicManager::GetView(view_id_);
	}
	void Update() {
		if (InputManager::IsPressed(KeyboardKey::LEFT))
			rects_to_draw_count_ -= 1;
		if (InputManager::IsPressed(KeyboardKey::RIGHT))
			rects_to_draw_count_ += 1;

		if (InputManager::IsPressed(KeyboardKey::UP) || first_frame) {
			first_frame = false;
			size_t rect_count;
			strip_w_ = 80;
			rect_count = 13;
			std::cin >> strip_w_;
			int start_strip_count;
			start_strip.clear();
			std::cin >> start_strip_count;

			for (int i = 0; i < start_strip_count; i++) {
				float start_x, y;
				std::cin >> start_x >> y;
				start_strip.push_back({ start_x, y });
			}

			std::cin >> rect_count;
			rect_.resize(rect_count);
			for (size_t i = 0; i < rect_count; i++) {
				std::cin >> rect_[i].w >> rect_[i].h >> rect_[i].count;
				rect_[i].id = i;
				if (rect_[i].w > strip_w_) {
					std::cout << "Incorrect input\nExiting...\n";
					SceneManager::CloseScene(this);
					return;
				}

				for (int j = 0; j < rect_[i].count; j++) {
					Color color;
					color.r = rand() % 255;
					color.g = rand() % 255;
					color.b = rand() % 255;

					color_.push_back(color);
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

			float aspect_ratio_coef = std::max(solution.solution_height * 1280.f / 720.f, strip_w_);
			view_->virtual_size = Vector2F(aspect_ratio_coef, aspect_ratio_coef * 720.f / 1280.f);
		}

		Debugger::DrawLine(Vector2F(strip_w_ + 1, 0), Vector2F(strip_w_ + 1, strip_h_), 2, view_id_);

		for (auto i = start_strip.begin(); std::next(i) != start_strip.end(); i++) {
			Vector2F A, B, C;
			A = Vector2F(i->start_x, i->h_level);
			B = Vector2F(std::next(i)->start_x, i->h_level);
			C = Vector2F(std::next(i)->start_x, std::next(i)->h_level);

			Debugger::DrawLine(A, B, 1, view_id_);
			Debugger::DrawLine(B, C, 1, view_id_);
		}

		Debugger::DrawLine(Vector2F(start_strip.back().start_x, start_strip.back().h_level), Vector2F(strip_w_, start_strip.back().h_level), 1, view_id_);

		for (int i = 0; i < std::min(rect_.size(), rects_to_draw_count_); i++) {
			Vector2F A, B, C, D;
			A = Vector2F(rect_[i].x + 0.5, rect_[i].y - 0.5);
			B = Vector2F(rect_[i].x + rect_[i].w - 0.5, rect_[i].y - 0.5);
			C = Vector2F(rect_[i].x + rect_[i].w - 0.5, rect_[i].y - rect_[i].h + 0.5);
			D = Vector2F(rect_[i].x + 0.5, rect_[i].y - rect_[i].h + 0.5);
			Debugger::DrawLine(A, B, 1, view_id_, color_[i]);
			Debugger::DrawLine(B, C, 1, view_id_, color_[i]);
			Debugger::DrawLine(C, D, 1, view_id_, color_[i]);
			Debugger::DrawLine(D, A, 1, view_id_, color_[i]);

			Debugger::DrawLine(A, C, 1, view_id_, color_[i]);
			Debugger::DrawLine(B, D, 1, view_id_, color_[i]);
		}
	}
	void Destroy() {

	}

private:
	bool first_frame = true;
	size_t view_id_;
	View* view_;
	size_t rects_to_draw_count_ = 0;
	std::vector<rect_t> rect_;
	std::vector<Color> color_;
	std::list<strip_level_t> start_strip;

	float strip_w_;
	float strip_h_;
};

int main()
{
	GameManager::Init();
	Scene* start = new PackScene;
	start->Init();
	GameManager::Launch(start);
	return 0;
}