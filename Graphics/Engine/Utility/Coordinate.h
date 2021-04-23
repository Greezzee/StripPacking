#pragma once
const double EPS = 1E-9;

/*!
* �������� ���������: ��������� ������� ��������� �����.
*
* ������������ � �������� ���������� ������ ��� float, �� � ������ ������� ������� � ���������.
*
* ����� ������ ���������� � SFML ��������, ����� �������� ��������� ���������� �� sfml ���� ���, ��� �� �� ���������
*/
struct Vector2F
{
	//! ����������� �� ���������, ������ (0, 0)
	Vector2F();

	//! ����������� ������� (a, b)
	Vector2F(float a, float b);

	//! ����������� �����������
	Vector2F(const Vector2F& that);
	float x, y;

	//! ����� ����� �������
	float Magnitude() const;

	//! ����� ������� ����� �������. �������, ��� ������� �����
	float SqrMagnitude() const;

	//! ����� ��������� ������, �������������� � ������
	Vector2F Normalized() const;

	//! �������� �������� �������� � ��������� �� ����� ��������� � ������������� ���������� ����������
	/*!
	* ������� �������� ��������� � ������� ������� �� ������
	* (a, b) * (c, d) = (a * c, b * d)
	* (a, b) / (c, d) = (a / c, b / d)
	*/
	const Vector2F& operator=(const Vector2F& that);
	const Vector2F& operator+=(const Vector2F& that);
	const Vector2F& operator-=(const Vector2F& that);

	const bool operator< (const Vector2F& that);

	//! ����� ��������� ������������ ��������
	static float ScalarMult(const Vector2F& a, const Vector2F& b);
};

struct Vector2U
{
	//! ����������� �� ���������, ������ (0, 0)
	Vector2U();

	//! ����������� ������� (a, b)
	Vector2U(unsigned a, unsigned b);

	//! ����������� �����������
	Vector2U(const Vector2U& that);
	unsigned x, y;

	//! �������� �������� �������� � ��������� �� ����� ��������� � ������������� ���������� ����������
	/*!
	* ������� �������� ��������� � ������� ������� �� ������
	* (a, b) * (c, d) = (a * c, b * d)
	* (a, b) / (c, d) = (a / c, b / d)
	*/
	const Vector2U& operator=(const Vector2U& that);
	const Vector2U& operator+=(const Vector2U& that);
	const Vector2U& operator-=(const Vector2U& that);
};

struct Vector2D
{
	//! ����������� �� ���������, ������ (0, 0)
	Vector2D();

	//! ����������� ������� (a, b)
	Vector2D(double a, double b);

	//! ����������� �����������
	Vector2D(const Vector2D& that);
	double x, y;

	//! ����� ����� �������
	double Magnitude() const;

	//! ����� ������� ����� �������. �������, ��� ������� �����
	double SqrMagnitude() const;

	//! ����� ��������� ������, �������������� � ������
	Vector2D Normalized();

	//! �������� �������� �������� � ��������� �� ����� ��������� � ������������� ���������� ����������
	/*!
	* ������� �������� ��������� � ������� ������� �� ������
	* (a, b) * (c, d) = (a * c, b * d)
	* (a, b) / (c, d) = (a / c, b / d)
	*/
	const Vector2D& operator=(const Vector2D& that);
	const Vector2D& operator+=(const Vector2D& that);
	const Vector2D& operator-=(const Vector2D& that);

	const bool operator< (const Vector2D& that);

};


struct Vector2I
{
	//! ����������� �� ���������, ������ (0, 0)
	Vector2I();

	//! ����������� ������� (a, b)
	Vector2I(int a, int b);

	//! ����������� �����������
	Vector2I(const Vector2I& that);
	int x, y;

	//! �������� �������� �������� � ��������� �� ����� ��������� � ������������� ���������� ����������
	/*!
	* ������� �������� ��������� � ������� ������� �� ������
	* (a, b) * (c, d) = (a * c, b * d)
	* (a, b) / (c, d) = (a / c, b / d)
	*/
	const Vector2I& operator=(const Vector2I& that);
	const Vector2I& operator+=(const Vector2I& that);
	const Vector2I& operator-=(const Vector2I& that);

	Vector2F to2F() const;

};

const Vector2F& operator+(const Vector2F& that);
const Vector2F operator-(const Vector2F& that);
const Vector2F operator+(const Vector2F& a, const Vector2F& b);
const Vector2F operator*(const Vector2F& a, const Vector2F& b);
const Vector2F operator/(const Vector2F& a, const Vector2F& b);
const Vector2F operator-(const Vector2F& a, const Vector2F& b);
const Vector2F operator*(float a, const Vector2F& b);
const Vector2F operator*(const Vector2F& a, float b);
const Vector2F operator/(const Vector2F& a, float b);
const bool operator==(const Vector2F& a, const Vector2F& b);
const bool operator!=(const Vector2F& a, const Vector2F& b);
const Vector2U& operator+(const Vector2U& that);
const Vector2U operator-(const Vector2U& that);
const Vector2U operator+(const Vector2U& a, const Vector2U& b);
const Vector2U operator*(const Vector2U& a, const Vector2U& b);
const Vector2U operator/(const Vector2U& a, const Vector2U& b);
const Vector2U operator-(const Vector2U& a, const Vector2U& b);
const Vector2U operator*(unsigned a, const Vector2U& b);
const Vector2U operator*(const Vector2U& a, unsigned b);
const Vector2U operator/(const Vector2U& a, unsigned b);
const bool operator==(const Vector2U& a, const Vector2U& b);
const bool operator!=(const Vector2U& a, const Vector2U& b);
const Vector2D& operator+(const Vector2D& that);
const Vector2D operator-(const Vector2D& that);
const Vector2D operator+(const Vector2D& a, const Vector2D& b);
const Vector2D operator*(const Vector2D& a, const Vector2D& b);
const Vector2D operator/(const Vector2D& a, const Vector2D& b);
const Vector2D operator-(const Vector2D& a, const Vector2D& b);
const Vector2D operator*(double a, const Vector2D& b);
const Vector2D operator*(const Vector2D& a, double b);
const Vector2D operator/(const Vector2D& a, double b);
const bool operator==(const Vector2D& a, const Vector2D& b);
const bool operator!=(const Vector2D& a, const Vector2D& b);
const Vector2I& operator+(const Vector2I& that);
const Vector2I operator-(const Vector2I& that);
const Vector2I operator+(const Vector2I& a, const Vector2I& b);
const Vector2I operator*(const Vector2I& a, const Vector2I& b);
const Vector2I operator/(const Vector2I& a, const Vector2I& b);
const Vector2I operator-(const Vector2I& a, const Vector2I& b);
const Vector2I operator*(int a, const Vector2I& b);
const Vector2I operator*(const Vector2I& a, int b);
const Vector2I operator/(const Vector2I& a, int b);
const bool operator==(const Vector2I& a, const Vector2I& b);
const bool operator!=(const Vector2I& a, const Vector2I& b);