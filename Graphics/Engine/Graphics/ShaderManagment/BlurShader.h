#pragma once
#include "Shader.h"
#include "ShaderManager.h"
//! ����� ������ "��������"
class BlurShader : public Shader
{
public:
	BlurShader();
	~BlurShader();
	//! ������������ ������� ��������. ����� �����, ������� 0.01
	static void SetBlurRadius(float r);
	static float GetBlurRadius();

private:
	static float _radius;
	static sf::Shader my_shader;
	friend class ShaderManager;
};
