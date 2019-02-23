#include "Text.h"
#include <iostream>
#include <glad/glad.h>
#include "Shader.h"
#include "Buffer.h"
#include "Window.h"

using namespace std;

Text::Text(Window *window)
{
	if (FT_Init_FreeType(&(ft)))
	{
		cout << "init face error" << endl;
	}
	shader = new Shader(
		"E:/OpenGLProject/TextRendering/TextRendering/text.vs",
		"E:/OpenGLProject/TextRendering/TextRendering/text.fs");
	glm::mat4 projection = glm::ortho(0.0f, (float)(window->width), 0.0f, (float)(window->height));
	shader->RunProgram();
	shader->SetUniform("projection", projection);
}

Text::~Text()
{
}

void Text::SetSize(unsigned int size)
{
	//修改字体大小变量
	this->scale = float(size/48.0f);
}

//设置字体颜色
void Text::SetColor(glm::vec3 color)
{
	this->color = color;
}

//加载字体风格
void Text::LoadFont(std::string fontPath)
{
	//将字体加载到面上
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
	{
		cout << "load font error" << endl;
	}
	//设置字体大小
	FT_Set_Pixel_Sizes(face, 0, 48);

	//字体对齐参数设置为1
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//加载前128个字符
	for (GLubyte c = 0; c < 128; c++)
	{
		//加载字符
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		//生成字符纹理
		GLuint texture;
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		//给纹理对象分配空间
		glTextureStorage2D(texture, 1, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		//更新数据
		glTextureSubImage2D(texture, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		//创建采样器
		GLuint sampler;
		glCreateSamplers(1, &sampler);
		//设置纹理环绕和滤波
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			sampler,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	//释放资源
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

//记录文本内容
void Text::Content(std::string content, float x, float y)
{
	//运行着色器程序
	shader->RunProgram();
	//设置文本采样器下标
	shader->SetUniform("text", 0u);
	//设置字体颜色
	shader->SetUniform("textColor", color);
	//绘制索引
	unsigned char indices[2][3] =
	{
		{ 0, 1, 2 },{ 2, 1, 3 }
	};

	//遍历文本字符
	for (auto c : content)
	{
		//获取当前字符的字符信息
		Character *ch = &characters[c];
		//计算字符四边形的原点坐标
		float xpos = x + ch->bearing.x * scale;
		float ypos = y - (ch->size.y - ch->bearing.y) * scale;
		//计算字符四边形的宽度和高度
		float w = ch->size.x * scale;
		float h = ch->size.y * scale;
		//记录当前字符的纹理
		message.push_back(ch);

		//字符四边形的顶点位置
		float *position = new float[8]
		{
			xpos, ypos + h,
			xpos + w, ypos + h,
			xpos, ypos,
			xpos + w, ypos
		};
		//字符四边形的纹理坐标
		float *texCoord = new float[8]
		{
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		//生成一个缓存来记录这些数据
		Buffer *buffer = new Buffer;
		buffer->LoadVertexData((const float*)position, 4, 2);
		buffer->LoadVertexData((const float*)texCoord, 4, 2);
		buffer->CommitData();
		buffer->LoadElements((const unsigned char*)indices, 6);
		//记录字符的顶点缓存
		buffers.push_back(buffer);

		//四边形向右移动一段距离，准备存储下一个字符的信息
		x += (ch->advance >> 6) * scale;
	}
}

//渲染字体
void Text::Render()
{
	//运行着色器
	shader->RunProgram();
	//开启融混
	glEnable(GL_BLEND);
	//设置融混方程
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//渲染内容的每一个字符
	for (size_t i = 0; i < buffers.size(); i++)
	{
		//绑定字符纹理
		glBindTextureUnit(0u, message[i]->texture);
		//绑定采样器
		glBindSampler(0u, message[i]->sampler);
		//绑定顶点缓存
		buffers[i]->Bind();
		//绘制
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	}
}
