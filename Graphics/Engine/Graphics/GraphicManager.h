#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "ShaderManagment/ShaderManager.h"
#include "DrawData.h"
#include "ShaderManagment/Shader.h"
#include "../Utility/Coordinate.h"
#include "../Debugger/Debugger.h"
#include "FPSCounter.h"

/*!
* ��������� �����, ��������������� ��� ������ � ��������.
*
* ����������� �������, ������� ����� ���� ������� � ������� ���� - ������� Draw, ����� ���������� ������ ������,
* �� ��������� ������� ������������ �� ���.
*
* ��� ���� �� �������� �������, ��������� �� SFML (���������, � ������, ����� �������������� ��� ����).
* ���� �������� ������������� ��������� � SFML �� ���-�� ������, ����� ����� ���������� ������ �����
* (� ����� TimeManager � InputManager), �������� ���������� ������� (����� �� ����������� ������ ������������� ���������� ����)
*
* ������� �������� ��������������� ������ ������� ������. ������� ������ ������ ID ����� �������� � ���� enum Sprites
*
* ��������� ������� �� DrawData � View.
* DrawData - ���������� � ���, ���, ��� � ��� ����� ���������� (�������� � ��������������� �����)
* View �������� �� �������������.
* ��������� View ����� �� ���������� � ������������ ������� ��������� ��������. ��������� � ��� ��� �������� View ��������� � DrawData.h
*
* ���������
*/
class GraphicManager
{
public:

	//! �������������, �������� �������������
	static void Init();

	//! ���������� ���������� ������ ����
	static bool Update();

	//! ����� ���������� ��� �������� ����. ���������� ��� ����, �������� � � ����������
	static void Exit();

	//static void LoadPack();
	//! ���������� ������ �������� DrawData, �������� � ���� View � view_id. data ��� ���� ���������� ��������!!!
	//! ����� true, ���� ���������� �������, false ���� ��� (id ������� ������ ��� ����� ����������� ��������)
	static bool Draw(DrawData data, unsigned view_id = 0);

	//! ��������� � data ��������������� View. ��� ���� data ����������!
	static void SetView(DrawData& data, unsigned view_id);

	//! �������� ���������� ����������� �������� �� ������ ������
	static unsigned GetSpritesCount();

	//! ����������� ����� ��� ��������, �������� �� ����������� ��������� ���������� (�� ����������� ����������� ������������ ������) 
	static void ClearSprites();

	//! �������� ���������� ����������� ������� �� ������ ������
	static unsigned GetTexturesCount();

	//! ����������� ����� ��� �������, �������� �� ����������� ��������� ���������� (�� ����������� ����������� ������������ ������) 
	static void ClearTextures();

	/*!
	* ��������� �������� �� ���� path �������� � �� ��������� ��������� id
	* ����� id ����� �������� ��� �������� ��������, ����� -1 � ������ ������ (��� ��������� id, �� ������ ���� �� ����)
	*/
	static int LoadTexture(const std::string& path);

	/*!
	* ��������� ������ �������� data � �������� ��� �� ��������� ��������� id
	* ����� id ������ ������� ��� �������� ��������, ����� -1 � ������ ������ (��� ��������� id, �� ������ ���� �� ����)
	*/
	static int LoadSprite(const GraphicPrefabData& data);

	/*!
	* ���������� ��������� �� view, ������� ������ ID.
	* View �� ������� ��������� ����� ��������, ��� ��� ��� ��������� ��������� �� ����������� ���� ��������, ������������ ������ view
	* ������������ �� ������������� ������ ��������� real_size �
	*/
	static View* GetView(unsigned view_id);

	/*!
	* ������� ����� view � ������ ��������� view
	* ����� id (> 0) ������ view, ���� view ��������� �������
	* ����� -1, ���� �� ���������� �������� view
	*/
	static int AddView(View view);

	/*!
	*  ������ ��� ���������������� view �� ������
	*/
	static void ResetViews();

	//! ��������� ������� ����-���� � ������� ������ �������� � ������� ������� view
	static Vector2F ConvertRealToView(Vector2F pos, unsigned view_id);

	//! ��������� ������� ����-���� � ������� ������ �������� � ������� ������� view
	static Vector2F ConvertRealPosToView(Vector2F pos, unsigned view_id);

	//! ��������� ������� ����-���� � ������� ������ view � ������� ������ ��������
	static Vector2F ConvertViewPosToReal(Vector2F pos, unsigned view_id);

	//! ��������� ������ ����-���� �� ������� ������ view � ������� ������ ��������. ��������� ������ ���� ��������� ������ real_size � virtual_size ���������!!!
	static float ConvertViewSizeToReal(float len, unsigned view_id);

	//! ����� ��������� �� ����-���� (�� ������� ������������ ������ �������)
	static sf::RenderWindow* GetWindow();

	//! ������������� ����� ���������� ������ � ��������
	//! ������ view �� ��������� ���, ����� ��� ��������������� ������ ����������
	//! �� ������ view, ����������� �� �����, �� ���� ��� ����� ��������� �������� ���������
	//! ���������� ������ ResetViews() � ��������� ����� �������� ������ ����������
	static void SetResolution(Vector2U new_size);

	//! ����� ���������� ������ � ��������
	static Vector2U GetResolution();

	//! �������������, ���������� �� ���������� � ������� ������ � ������� ���
	static void ShowFPS(bool is_show);

	//! ����� ������, ������� ����� ����������� � ������� ����
	//! ������ ���� ����������� ����� �������� ������� �������
	//! ��������� ������� ������ ��������� ���-��, �������� �� ������������ �������� ������
	//! ��� ���������� ������� ���������� shader = nullptr
	//! ���� ���� ������ ������������� ���-�� ����, �� ������� ������
	//! ������, ���������� � ����, �������� � ���� �������, ��� ���� �� �� ��������� ������ � ������� ������� �� ����
	static void SetLayerShader(unsigned layer, Shader* shader);

	//! ������������� ���-�� ����, �� ������� �������� ���������
	//! ��� ���������� ���-�� ����, ��� ������ � �������� ����� ���������
	//! � ��� ����� � ����������� � ���� �������
	//! �� ��������� �������� 20 ����
	static void SetLayersCount(unsigned count);
private:
	static sf::RenderWindow window; //! ���� SFML, �� ������� ���������� ��� ���������

	static std::vector<tge::TextureVertex> textures; //! ������ ���� ������� ����
	static std::vector<tge::Sprite> sprites; //! ������ ���� �������� ����

	static std::vector<tge::GraphicLayer> layers_to_draw; //! ������ ���� ����, ������� ����� ���������� � ������ ����

	static std::vector<View> views; //! ������ ���� Views.

	static unsigned LAYER_COUNT; //! ����� ���� ���� ���������. �� ������ �� ������ ��������. �������� �� ��, ����� ������� ��������� ������ ������, � ����� ���

	static unsigned _engine_textures_count; //! ���-�� �������, ���������� � ������
	static unsigned _engine_sprites_count; //! ���-�� ��������, ���������� � ������

	static std::vector<int> _basic_shapes;

	static tge::FPSCounter _fps_counter;

	friend class Debugger;
};

