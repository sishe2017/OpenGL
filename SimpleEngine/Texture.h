#pragma once
#include <glad/glad.h>

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
	Texture(TextureType textureType, Shader *shader, const char *samplerName);
	~Texture();

	//��������
	void LoadTexture(const char *texturePath);
	//�����˲�
	void SetTextureProperty(Filter filter);
	//����������
	void SetTextureProperty(Wrap wrap);
	//��Ե��ɫ
	float borderColor[4] = { 0 };
private:
	//��������
	TextureType textureType;
	//�˲�
	Filter filter;
	//�����Ʒ�ʽ
	Wrap wrap;
	//����Ԫ
	static GLuint textureUnit;
	//�������
	GLuint texture;
	//����������
	GLuint sampler;
};