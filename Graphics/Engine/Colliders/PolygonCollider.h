#pragma once

#include "../Utility/Coordinate.h"
#include "../Gameplay/GameObject.h"
#include "SquareCollider.h"
#include "UniversalCollider.h"
#include <vector>

class PolygonCollider : public UniversalCollider 
{
public:

	PolygonCollider();
	PolygonCollider(const SquareCollider& that);

	//! ����� ������� ���������
	void Init();

	//! ����� ������������� ��������� - ����� ������� ��������������
	void Init(const SquareCollider& that);

	//! ����� ������������� ���������
	//! points - ������ ������ ���������� ������������ ����� (0, 0)
	//! pos - ��������� ������ � ������������
	void Init(const Vector2F& pos, std::vector<Vector2F>& points);

	//! ����� ������������� ���������
	//! points - ������ ������ ���������� ������������ ����� (0, 0)
	//! pos - ��������� ������ � ������������
	//! angle - ������� ������ ������� ���������� ������������ ������
	void Init(const Vector2F& pos, std::vector<Vector2F>& points, float angle);

	float GetAngle() const;
	void SetAngle(float angle);
	Vector2F GetPos() const;
	void SetPos(Vector2F pos);
	unsigned GetPointsCount() const;
	Vector2F GetPoint(unsigned i) const;

	virtual ~PolygonCollider() {};

protected:

	Vector2F _pos; //! ������� ������ � ������������ (����� - ����� ����������� ����������)
	float _angle; //! ���� �������� ���������� � �������� ������ �������. ��� _angle = 0 ������ ����� ����������� ��� x

	std::vector<Vector2F> _points; //! ���������� ������/������, ������/�������, �����/�������, �����/������ ����� � ������ �������

	friend class Collider;
};
