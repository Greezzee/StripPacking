#pragma once
#include "ObjectsArray.h"

/*!
* ����� �������� ����.
* �������� �����-���� ������ � ����������� ��.
* ������ ������� ������� � ���������� ���������� ���
* 
* ����� ������� ��������� ������� ����� ������������
* 
* �� ������ ������ �������� ����� ������ �������� ���� � Gameplay Scene. ���� �������������� ������� ���� �� �����
* ������� ���� ����� ������������. � ���� ������ ��� ������� ���������� ������������� �� ����.
* 
* �������� �������� �������� �� ������� ����.
* ���������� ���� �������� ������ ��������, � ������� ����� ��������� ��� ������� �������.
* ���� - ������������ ��������� ������� ��������
* ���� ������ ����� ���������� �� ����� ���������� ��������� ���� (� ��� ����� � �� ���������� �� �� �����).
* ����� ������� ��������� �������� �������������� ��������.
* ��������, Player ��������� �� ���� Red, ��� ������� Bullet ����� �� ���� Red, ��������� Bullet �� ���� Blue
* ����� ��������� ������� ������ ��������� ��������, ���������� ����������� ������ �� ���� Blue, ��� ������������� ������� ���� Red.
* 
* ������� �������������� �������� ��������� � ����������
* 
* Init, Update, Destroy ����� ��������
* 
* ��������� �� �������
*/

class ObjectContainer
{
public:
	//! ������������� ������� ���� (��� ��������).
	void Init();

	//! ������������� ������� ���� (��� ��������) � �������� ������
	//! ����. ���-�� �������� � ����
	void Init(unsigned max_obj, unsigned layers_count);

	//! ����������� �������� ���� � ������� ���� ������
	void Destroy();

	/*!
	* ������� ����� ������� ������. ��������� GameobjectSpawnData �������, �������� ������ ��� ����� ������ �������
	* GameobjectSpawnData ��������:
	*	��������� �� ��� ������. �� ��� ������ ���� ������, ������ ��� ���� �������� � �� ������������������.
	*	������ bool'��, ������� ���������, �� ����� ����� ������ ������������. ��� ���� ������ �������������
	*/
	void SpawnObject(const GameobjectSpawnData& new_object);

	/*!
	* ����������� �������. ������������� ������� ������ � �������� Destroy �� ��������� �����.
	* ��������� ��������� �� ������, �������� ����� ������
	*/
	void KillObject(const GameObject* object);

	/*!
	* ���������� ����� ������� �����. ������������ ������� ��� �������.
	* �������� �������� ����� ������ ����� ��������� ����� �������� �������� �����������, ��� � ���� ���� Update ���� ��������
	* ����� ��� ����� ������������ ��������
	*/
	void ClearKilledObjects();

	void ApplyToAllObjects(void (*func)(GameObject*, void*), void* data = nullptr);
	void ApplyToLayerObjects(unsigned layer_id, void(*func)(GameObject*, void*), void* data = nullptr);

	virtual ~ObjectContainer() {};
private:

	/*!
	* ����������� �������. ������������� ������� ������ � �������� Destroy �� ��������� �����.
	* ��������� ������������ ID ������� (����� �������� � ������� GetID), ����� ��������� O(1)
	*/
	void KillObject(const unsigned ID);

	tge::ObjectsArray* _objects = nullptr;//! ������ ���� ��������. ��������� � ����������� �����
};

