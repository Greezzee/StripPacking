#pragma once
#include <SFML/System.hpp>

/*!
* �������� �������.
* ������ ���� ������� ������. ������ ������������ �� ���� ����!
* �������� �������������� �������� ���������!!!
* 
* ������� �� SFML
* ���������
*/
class TimeManager
{
public:

	//! �������������� �������������
	static void Init();

	//! �������������� ���������� ������ ����
	static void Update();

	//! ��������� �������� ��� ������� �� �������, �������� ���
	static void Restart();

	//! ���������� ����� � ���������� �������� ��� ������������� � �������������
	static unsigned long long GetTimeFromLastRestart();

	//! Vozvraschaet kollichestvo vremeny s momenta poslednego obnovleniya v SECUNDAH!
	static float GetDeltaTimeF();

	//! ���������� �����, ��������� � ����������� ����� (����� �� ������ ����) � �������������
	static unsigned long long GetDeltaTime();
private:
	static sf::Clock clock; //! SFML'�� ����
	static unsigned long long TimeFromLastRestart; //! ���������� ����������, ����� � ���������� �������� � �������������
	static unsigned long long DeltaTime; //! ���������� ����������, ����� ������� ����� � �������������
};

