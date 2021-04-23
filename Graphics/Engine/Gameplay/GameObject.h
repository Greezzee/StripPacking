#pragma once
#include <string>

#include "../Utility/Coordinate.h"

class ObjectContainer;

/*!
* ����������� �����, �� �������� ������ ������������� ��� ������� ������� (��������, ����, ������� ���������, �������, ����� � ��)
* ��� �������� ������� ���������� ������� �������� ������� Init, ���� ��� ����������
* ������� Update � Draw ���������� ������������� ������ ����
* Destroy ���������� ������������� ��� �������� �������
*
* ���������
*/
class GameObject
{
public:

	/*!
	* ������������� �������
	*/
	virtual void Init() {};

	/*!
	* ������������� �������, ���������� ������� � �������� �������.
	* ��������� ��������� �� ������������ ������ owner, �� �� �������� ����� �������������!!!
	* ������� ��� �� ������� ���������� �������� ������, ���� ������� ������-�������� ����� ���������,
	* � ��� �������� ������� ������ �� ���� �� ������. ������ owner �������� ������ � ���� Init.
	* ������ ������� owner � ���������� �������� ��������, ���� ������ ������� � ����� ��������� ������������.
	*/
	virtual void Init(GameObject* owner) {};

	//! ���������� �������. ���������� ������ ���� (�� ������ ������. � ������� �������� ����� � ������ ������� ���������� � ��� �� �����)
	virtual void Update() = 0;

	//! ��������� �������. ��������������� �������! ���������� ������ ������ ���� (���� �� �����)
	virtual void Draw() = 0;

	//! ����������� �������. ���������� 1 ���, ����� ������� ���� ���������� ������
	virtual void Destroy() = 0;

	//! �������� ��������� ������ ������� ����� ����
	virtual GameObject* Clone() const = 0;

	Vector2F GetPos();
	void SetPos(Vector2F pos);
	Vector2F GetDirection();
	void SetDirection(Vector2F dir);
	float GetRotation();
	void SetRotation(float angle);

	void SetTag(const std::string& new_tag);
	const std::string& GetTag();

	virtual ~GameObject() {};
protected:
	std::string _tag; //! ������, � ������� ����� ���� �������� ��, ��� ������. ����� �� ������������ ������� �����

	Vector2F _pos; //! ������� �������� ������� � ������������
	Vector2F _basic_direction; //! WIP, ������ ������������� �������� �� ���������! (1, 0)
	float _angle = 0; //! ���� �������� ������� � �������� ������ ������� �������

	ObjectContainer* gamefield = nullptr; //! ��������� �� ������� ����, � ������� ���� ������ ������� ������

private:

	//! ������������ ������� �� ������� ��� ������� ������ �������
	void SetID(unsigned new_id);
	unsigned GetID() const;

	//! ������������ ������� �� ������� ��� ������� ������ �������
	void SetGamefield(ObjectContainer* field);
	ObjectContainer* GetGamefield();

	unsigned _ID; //! ������������ ����� ������� � ������� ���� ��������. �� ������� ��� � �� ������ ���

	friend class Collider;
	friend class ObjectContainer;
};

