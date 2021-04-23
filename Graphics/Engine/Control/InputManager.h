#pragma once
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../Utility/Coordinate.h"

//! �������� �������� ����������� ������.
const unsigned KeysCount = 85;
enum KeyboardKey {
	NOTHING,
	ESC, N1, N2, N3, N4, N5, N6, N7, N8, N9, N0, MINUS, EQUAL, BACK,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	TAB, LSHIFT, LCTRL, LALT, RALT, RCTRL, RSHIFT,
	ENTER, BSLACH, //�������� ���� (����� ������)
	NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0, //����� �� �������
	TILDE,
	Q, W, E, R, T, Y, U, I, O, P,
	SQBROP, SQBRCL, //�������� � �������� ���������� ������
	A, S, D, F, G, H, J, K, L,
	SEMICOLON, APOSTROPHE,
	Z, X, C, V, B, N, M,
	COMMA, DOT, SLASH,
	SPACE,
	UP, DOWN, LEFT, RIGHT
};

const unsigned MouseKeysCount = 2;
enum MouseKey {
	Mouse_Left, Mouse_Right
};

//! ������ ���������� � ��������� ����������� �������
struct KeyData {
	bool is_pressed;
	bool is_realesed;
	bool is_down;
};

struct MouseData {
	Vector2F pos;
	KeyData l_button, r_button;
};

/*!
* ��������, ������� ������������� ������ � ���������� (� ������� � � ����) � ������������� �� ������ �������� � ����� ������� ����
*
* ��������� ��������� ��������� ����������, ��� ��� ������ ����� ����� ��������� ��������� ���������� � ������������ ��������� (L_Left, L_Right � ��)
* � �������� �������� ����, ����� ����������������� ������ ������������ ���������.
* ���� ����� ���������� ��������� ����������, ����� �������� ������� ����� ��������������� ������ ����������� (�� �� ��������)
*
* ������� �� SFML
*
* ���������. ����� ������ ��� ���������� ����� ������ ����������
*/

struct InputManager
{
	//! �� �������, ������������� ���������� ��� ������������� ����
	static void Init();

	//! �� �������, ������������� ���������� ������ ���� � ������� �����
	static void Update();

	//! ����� true � ����, � ������� ����������� ������� code ����������, ����� false
	static bool IsPressed(unsigned char code);

	//! ����� true � ����, � ������� ����������� ������� code ����������, ����� false
	static bool IsRealesed(unsigned char code);

	//! ����� true ���� code ������, ����� false
	static bool IsUp(unsigned char code);

	//! ����� true ���� code �� ������, ����� false
	static bool IsDown(unsigned char code);

	//! ����� true � ����, � ������� �������� ������� key ����������, ����� false
	static bool IsPressed(KeyboardKey key);

	//! ����� true � ����, � ������� �������� ������� key ����������, ����� false
	static bool IsRealesed(KeyboardKey key);

	//! ����� true ���� key ������, ����� false
	static bool IsUp(KeyboardKey key);

	//! ����� true ���� key �� ������, ����� false
	static bool IsDown(KeyboardKey key);

	//! ����� true � ����, � ������� ������� ���� key ����������, ����� false
	static bool IsPressed(MouseKey key);

	//! ����� true � ����, � ������� ����������� ������� key ����������, ����� false
	static bool IsRealesed(MouseKey key);

	//! ����� true ���� key ������, ����� false
	static bool IsUp(MouseKey key);

	//! ����� true ���� key �� ������, ����� false
	static bool IsDown(MouseKey key);

	//! ����� ���������� ������� � ������� ���� SFML
	static Vector2F GetMousePos();

	//! ��������� ������� � �����. ��� ����������� �������� IsUp, IsDown, ... ����, �������� ���������� � ��������� �������
	//! code �� ������ 255
	static void LinkToCode(KeyboardKey key, unsigned char code);

	//! ����� ������ ���������� KeyboradKey, ������� ���������� (IsPressed = true)
	//! ���� ������ ������� �� ������, ����� KeyboardKey::NOTHING
	static KeyboardKey GetPressedKey();
private:
	static MouseData _mouse_info; //! ���������� � ��������� ����

	static sf::Keyboard::Key _keys[KeysCount]; //����� KeybordKey � SFML
	static KeyboardKey _virtual_keys[255]; // ����� ����� � KeyboardKey
	static KeyData _key_data[KeysCount]; //! ���������� � ��������
};

