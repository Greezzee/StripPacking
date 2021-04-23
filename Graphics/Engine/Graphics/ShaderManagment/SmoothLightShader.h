#pragma once
#include "Shader.h"

//! ������ �������� ���������
//! ��������� ����� ������������ LightManager
class SmoothLightShader : public Shader
{
public:
	SmoothLightShader();
	~SmoothLightShader();

private:
	static sf::Shader my_shader;
	friend class ShaderManager;
};
