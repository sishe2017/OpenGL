#include "Texture.h"
#include "../Library/stb_image.h"
#include "Shader.h"

Texture::Texture(TextureType textureType):
	textureType(textureType)
{
	//创建采样器对象
	glCreateSamplers(1, &sampler);
	//设置默认的纹理环绕和纹理过滤方式
	this->SetTextureProperty(Wrap::Repeat);
	this->SetTextureProperty(Filter::Linear);
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
	//翻转y轴
	stbi_set_flip_vertically_on_load(true);
	//获取木箱纹理信息相关数据
	textureData = stbi_load(texturePath, &width, &height, &nrChannel, 0);

	//如果纹理类型是二维纹理
	if (textureType == TextureType::TwoD)
	{
		//创建二维纹理对象
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);

		//为纹理对象分配空间
		if (nrChannel == 3)
		{
			glTextureStorage2D(texture, 1, GL_RGB8, width, height);
			//更新纹理对象数据
			glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		}
		else if (nrChannel == 4)
		{
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
			glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		}
	}

	//释放纹理数据
	stbi_image_free(textureData);
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
