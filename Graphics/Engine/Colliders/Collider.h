#pragma once
#include "EllipseCollider.h"
#include "SquareCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

class Collider
{
public:
	/*!
	* �������� ��������� �� 2 ������������� ����������
	* ����� false, ���� ������ ������� �� ������������
	* ����� true, ����� ������������
	*
	* ������� �� 100% ������, ���������� �����������. ������� �������� ���������� COLLIDE_ITERATIONS
	*/
	static bool IsCollide(EllipseCollider* a, EllipseCollider* b);

	//! ���������, ������������ �� 2 ������ ����������
	static bool IsCollide(SquareCollider* a, SquareCollider* b);

	//! ���������, ������������ �� 2 ������ �����
	static bool IsCollide(CircleCollider* a, CircleCollider* b);

	//! ���������, ������������ �� ������ ���� � ������ �������������
	static bool IsCollide(CircleCollider* a, SquareCollider* b);

	//! ���������, ������������ �� ������ ���� � ������ �������������
	static bool IsCollide(SquareCollider* a, CircleCollider* b);

	//! ���������, ������������ �� ��� ������ ��������������
	static bool IsCollide(PolygonCollider* a, PolygonCollider* b);

	//! ���������, ������������ �� ������ ������������ ��������� � ������ ������
	static bool IsCollide(UniversalCollider* a, CircleCollider* b);

	//! ���������, ������������ �� ������ ������������ ��������� � ������ ��������
	static bool IsCollide(UniversalCollider* a, EllipseCollider* b);

	//! ���������, ������������ �� ������ ������������ ��������� � ������ ���������������
	static bool IsCollide(UniversalCollider* a, PolygonCollider* b);

	//! ���������, ������������ �� ������ ������������ ��������� � ������ ���������������
	static bool IsCollide(UniversalCollider* a, SquareCollider* b);

	//! ���������, ������������ �� ��� ������ ������������ ����������
	//! ���� ������������ ���������� �� ����� ���� �������� ������������� �����, ������� ������ � ����� false
	//! ������������� ���� �� ������ ������:
	//! EllipseCollider � ������ �������
	//! CircleCollider � PolygonCollider � � EllipseCollider
	//! SquareCollider � EllipseCollider
	//! PolygonCollider � EllipseCollider � CircleCollider
	static bool IsCollide(UniversalCollider* a, UniversalCollider* b);

	//! ��������� �� ������ ���������� a ������ � ����������� direction
	//! ����������, ������� ������ ������ ��������� a � ����������� ������� �������, ����� ����������� � b
	//! ����� ������� ���������� � ��� �� ��������, � ������� ������ ����������
	//! ����� NAN, ���� ��� �������� � ������ �����������, a ������� �� �������� b
	static float DistanceBetween(SquareCollider* a, SquareCollider* b, const Vector2F& direction);

	//! ��������� �� ������ ���������� a ������ � ����������� direction
	//! ����������, ������� ������ ������ ��������� a � ����������� ������� �������, ����� ����������� � b
	//! ����� ������� ���������� � ��� �� ��������, � ������� ������ ����������
	//! ����� NAN, ���� ��� �������� � ������ �����������, a ������� �� �������� b
	//! �� ��������
	static float DistanceBetween(CircleCollider* a, SquareCollider* b, const Vector2F& direction);

	//! ��������� �� ������ ���������� a ������ � ����������� direction
	//! ����������, ������� ������ ������ ��������� a � ����������� ������� �������, ����� ����������� � b
	//! ����� ������� ���������� � ��� �� ��������, � ������� ������ ����������
	//! ����� NAN, ���� ��� �������� � ������ �����������, a ������� �� �������� b
	static float DistanceBetween(CircleCollider* a, CircleCollider* b, const Vector2F& direction);

	//! ��������� �� ������ ���������� a ������ � ����������� direction
	//! ����������, ������� ������ ������ ��������� a � ����������� ������� �������, ����� ����������� � b
	//! ����� ������� ���������� � ��� �� ��������, � ������� ������ ����������
	//! ����� NAN, ���� ��� �������� � ������ �����������, a ������� �� �������� b
	static float DistanceBetween(PolygonCollider* a, PolygonCollider* b, const Vector2F& direction);

	static float DistanceBetween(UniversalCollider* a, UniversalCollider* b, const Vector2F& direction);

private:

	//! ��������� ����������� ���� ����������� �� ��� norm
	static bool AxisIntersect(SquareCollider* a, SquareCollider* b, const Vector2F& norm);

	//! ����� �� �����������... � ������� �� ��������
	static Vector2F AxisDistance(SquareCollider* a, SquareCollider* b, const Vector2F& norm, const Vector2F& dir);

	//! ��������� ����������� ���� ����������� �� ��� norm
	static bool AxisIntersect(PolygonCollider* a, PolygonCollider* b, const Vector2F& norm);

	//! ����� �� �����������... � ������� �� ��������
	static Vector2F AxisDistance(PolygonCollider* a, PolygonCollider* b, const Vector2F& norm, const Vector2F& dir);
};
