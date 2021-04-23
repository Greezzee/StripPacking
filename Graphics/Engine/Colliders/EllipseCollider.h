#pragma once
#include "../Gameplay/GameObject.h"
#include "../Utility/Coordinate.h"
#include "UniversalCollider.h"
/*!
* ��������� � ���� �������
* ������� ����� ���� ��� �������� Gameobject, ���� ������ ��� ��������� ������
* ����� ������ � ������������.
* 
* 
* 
* IsCollide() �� �������
* ��������� ���������
*/
class EllipseCollider : public UniversalCollider
{
public:

	EllipseCollider();
	virtual ~EllipseCollider() {};

	/*!
	* ������������� �������� ������� (����� � ������������ (0, 0))
	*/
	void Init();

	/*!
	* ������������� �������
	* pos - ������� ������ �������
	* angle - ���� �������� ������� � �������� ������������ ������ (0 �������� ������������ ���, ������� ������ �������)
	* size - ����� ��������
	*/
	void Init(Vector2F pos, float angle, Vector2F size);

	Vector2F GetPos() const;
	Vector2F GetSize() const;
	float GetAngle() const;

	void SetPos(const Vector2F& pos);
	void SetSize(const Vector2F& size);
	void SetAngle(float angle);

protected:
	Vector2F _pos, _size;//! ������� ������ ������� � ����� ��� ��������
	float _angle;        //! ���� �������� ������� ������������ ������ ������ ������� ������� � ��������

	const static unsigned COLLIDE_ITERATIONS; //! ���������� �������� ��������. ������ �������� - ������, �� ������. �� ������������ ����� ������ 4

	friend class Collider;
};

