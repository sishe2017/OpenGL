#include "Texture.h"
#include "../Library/stb_image.h"
#include "Shader.h"

Texture::Texture(TextureType textureType):
	textureType(textureType)
{
	//��������������
	glCreateSamplers(1, &sampler);
	//����Ĭ�ϵ������ƺ�������˷�ʽ
	this->SetTextureProperty(Wrap::Repeat);
	this->SetTextureProperty(Filter::Linear);
}

Texture::~Texture()
{
}

//��������
void Texture::LoadTexture(const char * texturePath)
{
	//��������
	unsigned char *textureData;
	//ͼ����
	int width;
	//ͼ��߶�
	int height;
	//��ɫͨ������
	int nrChannel;
	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//��ȡľ��������Ϣ�������
	textureData = stbi_load(texturePath, &width, &height, &nrChannel, 0);

	//������������Ƕ�ά����
	if (textureType == TextureType::TwoD)
	{
		//������ά�������
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);

		//Ϊ����������ռ�
		if (nrChannel == 3)
		{
			glTextureStorage2D(texture, 1, GL_RGB8, width, height);
			//���������������
			glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		}
		else if (nrChannel == 4)
		{
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
			glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		}
	}

	//�ͷ���������
	stbi_image_free(textureData);
}

//�����˲�
void Texture::SetTextureProperty(Filter filter)
{
	//��¼��ǰ�˲�
	this->filter = filter;
	//�������Թ���
	if (filter == Filter::Linear)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (filter == Filter::Nearest)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}

//����������
void Texture::SetTextureProperty(Wrap wrap)
{
	//��¼��ǰ�����Ʒ�ʽ
	this->wrap = wrap;
	//�ظ�����
	if (wrap == Wrap::Repeat)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	//������
	else if (wrap == Wrap::Mirror)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
	//����
	else if (wrap == Wrap::Strench)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	//ָ����ɫ���
	else if (wrap == Wrap::Border)
	{
		glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, borderColor);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}
}

//������󶨵�����Ԫ��
void Texture::BindUnit(Shader * shader, const char * samplerName, GLuint textureUnit)
{
	//����ƬԪ��ɫ���в�������λ��ֵ
	shader->SetUniform(samplerName, textureUnit);
	//���������󶨵�����Ԫ
	glBindTextureUnit(textureUnit, texture);
	//������������󶨵�����Ԫ��
	glBindSampler(textureUnit, sampler);
}
