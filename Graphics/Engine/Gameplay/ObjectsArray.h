#pragma once
#include <vector>
#include "GameObject.h"
namespace tge {
	//! ���������, �������� ��� �������� � ������ ���� ������� (�� ID)
	struct KilledArray
	{
		std::vector<int> obj_id; //! ������ ID �������� ��������. -1 �������� ���������� �������
		unsigned top; //! ���-�� �������� ��������
	};

	//! ������ ��� ������� �� ������ ����
	struct Layer {
		std::vector<int> obj_id; //! ������ ID �������� �� ������ ����. -1 �������� ���������� �������
		unsigned top; //! ���-�� �������� �� ����
	};

	//! ������ �� ����� ���������� �������
	struct ObjectData
	{
		GameObject* obj; //! ��������� �� ������
		/*!
		* ��������� ������ ������� � ��������������� ����.
		* -1, ���� ������ ����������� � ��������������� ����
		*/
		std::vector<int> layer_pos;
	};

	//! ������ ��� ���� �������� �� ������� ����, � ���� ����� � �� ��������, ���������� ��������
	struct ObjectsArray
	{
		ObjectsArray();

		void SetMaxObjects(unsigned new_size);
		void SetLayersCount(unsigned count);

		std::vector<ObjectData> obj; //! ������ ������ ���� ��������. ������������ ID ������� - ������� ��� ������ � ���� �������
		std::vector<Layer> layers; //! ������ ������ ��� ���� �����
		KilledArray to_kill; //! �������, ���������� �������� �� ��������� �����
		unsigned top; //! ���-�� ���� �������� �� ������� ����

		unsigned MAX_OBJECTS; //! ������������ ���������� �������� �� ����� ������� ����
		unsigned LAYERS_COUNT; //! ���������� ���� �������� �� ����� ������� ����
	};
}

//! ������, ������� ���������� ������������ �������� ����, ����� �������� � ���� ������
struct GameobjectSpawnData
{
	GameObject* obj; //! ��������� �� ��� ��������� ������, �������� �������� ������ � ������� ���������������
	std::vector<bool> is_on_layer; //! ���������� � ���, �� ����� ����� �� ������������
};
