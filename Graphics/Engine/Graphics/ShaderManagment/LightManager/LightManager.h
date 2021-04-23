#pragma once

#include "SFML/Graphics.hpp"
#include "../../GraphicManager.h"
#include "../../../Utility/Coordinate.h"
/*
uniform int source_count;
uniform vec2 pos[128];
uniform vec4 light_color[128];
uniform float full_light_dist[128];
uniform float any_light_dist[128];
uniform float softness[128];
*/

struct LightData
{
	Vector2F pos; //! ������� ��������� � ������� �����������
	Color color; //! ���� ���������
	float full_dist; //! ������, � ������� �������� ����� �������� �� ������ ��������, � ������� ��������
	float any_dist; //! ������ �� ��������� full_dist, � �������� �������� ���� �����-���� ���������
	float softness; //! ����� "��������" ���������. ����� �� 0 �� 5
};
const unsigned source_max_count = 128;
class LightManager
{
public:
	//! ������������ �������������. ���������� �������������
	static void Init();

	//! ��������� ����� �������� �����
	//! ����� ��� ID � �������
	//! ����� -1, ���� �������� ����� �������� ����� �� �������
	static int AddLightSource(const LightData& data);

	//! ��������� �������� ��� ����������� �������� ����� �� ��� ID
	//! ����� false, ���� �������� �������� �� �������, ����� true
	static bool SetLightSource(unsigned ID, const LightData& data);

	//! ������� ��� ��������� �����
	static void ClearLightSource();

	//! ����� ������ ������� ��� ����������� ��������� � ������� �������� (� �������� view)
	static void SetPixelSize(float ps);

	//! ������������� �������� view. ������������� ������� ��� ��������� �����
	static void SetView(unsigned id);

	//! ������������� ���� ����������� ���������
	static void SetGlobalLight(const Color& glc);
private:

	static void ApplyLight(sf::Shader* shader);
	static void ApplyPixelLight(sf::Shader* shader);

	static unsigned view_id;

	//! ���������� ��� ��������
	static unsigned source_count;
	static sf::Glsl::Vec2 pos[source_max_count];
	static sf::Glsl::Vec4 light_color[source_max_count];
	static float full_light_dist[source_max_count];
	static float any_light_dist[source_max_count];
	static float softness[source_max_count];

	static float pixel_size;
	static sf::Glsl::Vec4 global_light_color;

	friend class ShaderManager;

	static bool is_change;
};