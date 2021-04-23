#pragma once
#include "Coordinate.h"

/*!
* ���������, �������� ������ ����� �� ��������� � ���������� ���������
*/
struct Line
{
	float a, b, c; //! ������������ ������ ax + by + c = 0
	Line();
	Line(const Vector2F& p, const Vector2F& q); //! ����������� ����� ������, ���������� ����� 2 ������ �����

	void Normalize(); //! �������� ������������ ������ � ����, ��� sqrt(a^2 + b^2) = 1

	float Distance(const Vector2F& p); //! ����� ��������� ���������� �� ����� �� ������ ������
};

/*!
* ���������, ������������ �� 2 �������.
* ������ ������� ��������� ����� a � b, ������ - ����� c � d
*/
bool Intersect(Vector2F a, Vector2F b, Vector2F c, Vector2F d);

/*!
* ���������, ��������� �� ����� x ����� ������� l � r
*/
inline bool Between(float l, float r, float x);
