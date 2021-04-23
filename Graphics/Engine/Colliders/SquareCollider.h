#pragma once
#include "../Utility/Coordinate.h"
#include "../Gameplay/GameObject.h"
#include "UniversalCollider.h"
const float PI = 3.1415926f;

class SquareCollider : public UniversalCollider {
public:
	SquareCollider();

	//! ����� ������� ���������, ������ �� �������������
	void Init();

	//! ����� ������������� ���������
	//! ������ ������ size, ��������� � ������������ pos
	//! ������������� �� ���������, ������������� ���� ���������
	//! ����� - ������ ����� ����������� ����������
	void Init(const Vector2F& pos, const Vector2F& size);

	//! ����� ������������� ���������
	//! ������ ������ size, ��������� � ������������ pos
	//! �������������. ������ ������� ��������� ��� ����� angle (� ��������) � ��� x, ������ �������
	//! ����� (������������ ������ ���������� ����������� ���������� � ��������) - ������ ����� ����������� ����������
	void Init(const Vector2F& pos, const Vector2F& size,
		float angle);

	//! ����� ������������� ���������
	//! ������ ������ size, ��������� � ������������ pos
	//! ��������������. ������ ����� ���� (�� ������ ���������) - shape_angle (� ��������). shape_angle = PI/2 - ����� �������������
	//! ������ ������� ��������� ��� ����� angle (� ��������) � ��� x, ������ �������
	//! ����� (������������ ������ ���������� ����������� ���������� � ��������) - ������ ����� ����������� ����������
	void Init(const Vector2F& pos, const Vector2F& size,
		float angle, float shape_angle);

	float GetAngle() const;
	void SetAngle(float angle);
	Vector2F GetPos() const;
	void SetPos(Vector2F pos);
	Vector2F GetSize() const;
	void SetSize(Vector2F size);
	Vector2F GetPoint(unsigned i) const;

	virtual ~SquareCollider() {};
protected:

	void SetPoints(); //! ������ � ��������� ������� ����� ����������

	Vector2F _size; //! �������� ���� ������
	Vector2F _pos; //! ������� ������ � ������������ (����� - ����� ����������� ����������)
	float _angle; //! ���� �������� ���������� � �������� ������ �������. ��� _angle = 0 ������ ����� ����������� ��� x
	float _shape_angle; //! ������ ����� ���� ���������� � ��������. �� ��������� pi/2 (�������������)

	Vector2F _points[4]; //! ���������� ������/������, ������/�������, �����/�������, �����/������ ����� � ������ �������

	friend class Collider;
};

