#include "Texture.h"
#include "../Library/stb_image.h"
#include "Shader.h"
#include <iostream>

Texture::Texture(TextureType textureType):
	textureType(textureType)
{
	//���Ҫ�󴴽���ά�����򴴽���ά�������
	if (textureType == TextureType::TwoD)
	{
		//����һ����ά����
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		//��������������
		glCreateSamplers(1, &sampler);
		//���ö�ά�����Ĭ�ϻ��ƺ��˲�
		this->SetTextureProperty(Filter::Linear);
		this->SetTextureProperty(Wrap::Repeat);
	}
	//���Ҫ�󴴽������������򴴽�����������
	else if (textureType == TextureType::Cube)
	{
		//�����������������
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &texture);
		//����������
		glCreateSamplers(1, &sampler);
		//����������������˲���������
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}
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
	//��ȡ������Ϣ�������
	textureData = stbi_load(texturePath, &width, &height, &nrChannel, 0);

	//��������ͨ������Ϊ����������ռ䲢��������
	if (nrChannel == 1)
	{
		glTextureStorage2D(texture, 1, GL_R8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, textureData);
	}
	else if (nrChannel == 3)
	{
		glTextureStorage2D(texture, 1, GL_RGB8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	}
	else if (nrChannel == 4)
	{
		glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	}
	//�ͷ���������
	stbi_image_free(textureData);
}

//��������������
void Texture::LoadTexture(std::string(&texturePath)[6])
{
	//��������
	unsigned char *textureData[6];
	//ͼ����
	int width;
	//ͼ��߶�
	int height;
	//��ɫͨ������
	int nrChannel;
	//�Ƿ��ǵ�һ�μ��صı�־
	bool firstFlag = true;
	
	//���������������
	for (auto i = 0; i < 6; i++)
	{
		textureData[i] = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannel, 0);
	}
	//����ͨ������������ռ䲢������������
	if (nrChannel == 3)
	{
		glTextureStorage2D(texture, 1, GL_RGB8, width, height);
		for (auto i = 0; i < 6; i++)
		{
			glTextureSubImage3D(texture, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, textureData[i]);
		}
	}
	else if (nrChannel == 4)
	{
		glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		for (auto i = 0; i < 6; i++)
		{
			glTextureSubImage3D(texture, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, textureData[i]);
		}
	}
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

//��תY��
void Texture::ReverseY(bool flag)
{
	stbi_set_flip_vertically_on_load(flag);
}


