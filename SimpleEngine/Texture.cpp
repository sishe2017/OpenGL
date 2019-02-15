#include "Texture.h"
#include "../Library/stb_image.h"
#include "Shader.h"
#include <iostream>

Texture::Texture(TextureType textureType):
	textureType(textureType)
{
	//如果要求创建二维纹理则创建二维纹理对象
	if (textureType == TextureType::TwoD)
	{
		//创建一个二维纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		//创建采样器对象
		glCreateSamplers(1, &sampler);
		//设置二维纹理的默认环绕和滤波
		this->SetTextureProperty(Filter::Linear);
		this->SetTextureProperty(Wrap::Repeat);
	}
	//如果要求创建立方体纹理则创建立方体纹理
	else if (textureType == TextureType::Cube)
	{
		//创建立方体纹理对象
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &texture);
		//创建采样器
		glCreateSamplers(1, &sampler);
		//设置立方体纹理的滤波和纹理环绕
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

//加载纹理
void Texture::LoadTexture(const char * texturePath)
{
	//纹理数据
	unsigned char *textureData;
	//图像宽度
	int width;
	//图像高度
	int height;
	//颜色通道数量
	int nrChannel;
	//获取纹理信息相关数据
	textureData = stbi_load(texturePath, &width, &height, &nrChannel, 0);

	//根据纹理通道数量为纹理对象分配空间并更新数据
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
	//释放纹理数据
	stbi_image_free(textureData);
}

//加载立方体纹理
void Texture::LoadTexture(std::string(&texturePath)[6])
{
	//纹理数据
	unsigned char *textureData[6];
	//图像宽度
	int width;
	//图像高度
	int height;
	//颜色通道数量
	int nrChannel;
	//是否是第一次加载的标志
	bool firstFlag = true;
	
	//加载六个面的数据
	for (auto i = 0; i < 6; i++)
	{
		textureData[i] = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannel, 0);
	}
	//根据通道数量来分配空间并更新纹理数据
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

//设置滤波
void Texture::SetTextureProperty(Filter filter)
{
	//记录当前滤波
	this->filter = filter;
	//设置线性过滤
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

//设置纹理环绕
void Texture::SetTextureProperty(Wrap wrap)
{
	//记录当前纹理环绕方式
	this->wrap = wrap;
	//重复环绕
	if (wrap == Wrap::Repeat)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	//镜像环绕
	else if (wrap == Wrap::Mirror)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
	//拉伸
	else if (wrap == Wrap::Strench)
	{
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	//指定颜色填充
	else if (wrap == Wrap::Border)
	{
		glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, borderColor);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}
}

//将纹理绑定到纹理单元中
void Texture::BindUnit(Shader * shader, const char * samplerName, GLuint textureUnit)
{
	//设置片元着色器中采样器的位置值
	shader->SetUniform(samplerName, textureUnit);
	//将纹理对象绑定到纹理单元
	glBindTextureUnit(textureUnit, texture);
	//将采样器对象绑定到纹理单元中
	glBindSampler(textureUnit, sampler);
}

//反转Y轴
void Texture::ReverseY(bool flag)
{
	stbi_set_flip_vertically_on_load(flag);
}


