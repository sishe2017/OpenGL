#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

class Shader;

//��������
enum class TextureType
{
	//2D����
	TwoD,
	//3D����
	ThreeD,
	//����������
	Cube
};
//�˲�
enum class Filter
{
	//���Թ���
	Linear,
	//�ͽ�����
	Nearest
};
//�����Ʒ�ʽ
enum class Wrap
{
	//�ظ�
	Repeat,
	//����
	Mirror,
	//����
	Strench,
	//ָ����Ե��ɫ
	Border
};

class Texture
{
public:
	Texture(TextureType textureType);
	~Texture();

	//��������
	void LoadTexture(const char *texturePath);
	//�����˲�
	void SetTextureProperty(Filter filter);
	//����������
	void SetTextureProperty(Wrap wrap);
	//������󶨵�����Ԫ��
	void BindUnit(Shader *shader, const char *samplerName, GLuint textureUnit);
	//��Ե��ɫ
	float borderColor[4] = { 0 };

private:
	//��������
	TextureType textureType;
	//�˲�
	Filter filter;
	//�����Ʒ�ʽ
	Wrap wrap;
	//���������󼯺�
	GLuint sampler;
	//���������
	GLuint texture;
};