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
	//�޸������С����
	this->scale = float(size/48.0f);
}

//����������ɫ
void Text::SetColor(glm::vec3 color)
{
	this->color = color;
}

//����������
void Text::LoadFont(std::string fontPath)
{
	//��������ص�����
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
	{
		cout << "load font error" << endl;
	}
	//���������С
	FT_Set_Pixel_Sizes(face, 0, 48);

	//��������������Ϊ1
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//����ǰ128���ַ�
	for (GLubyte c = 0; c < 128; c++)
	{
		//�����ַ�
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		//�����ַ�����
		GLuint texture;
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		//������������ռ�
		glTextureStorage2D(texture, 1, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		//��������
		glTextureSubImage2D(texture, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		//����������
		GLuint sampler;
		glCreateSamplers(1, &sampler);
		//���������ƺ��˲�
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
	//�ͷ���Դ
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

//��¼�ı�����
void Text::Content(std::string content, float x, float y)
{
	//������ɫ������
	shader->RunProgram();
	//�����ı��������±�
	shader->SetUniform("text", 0u);
	//����������ɫ
	shader->SetUniform("textColor", color);
	//��������
	unsigned char indices[2][3] =
	{
		{ 0, 1, 2 },{ 2, 1, 3 }
	};

	//�����ı��ַ�
	for (auto c : content)
	{
		//��ȡ��ǰ�ַ����ַ���Ϣ
		Character *ch = &characters[c];
		//�����ַ��ı��ε�ԭ������
		float xpos = x + ch->bearing.x * scale;
		float ypos = y - (ch->size.y - ch->bearing.y) * scale;
		//�����ַ��ı��εĿ�Ⱥ͸߶�
		float w = ch->size.x * scale;
		float h = ch->size.y * scale;
		//��¼��ǰ�ַ�������
		message.push_back(ch);

		//�ַ��ı��εĶ���λ��
		float *position = new float[8]
		{
			xpos, ypos + h,
			xpos + w, ypos + h,
			xpos, ypos,
			xpos + w, ypos
		};
		//�ַ��ı��ε���������
		float *texCoord = new float[8]
		{
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		//����һ����������¼��Щ����
		Buffer *buffer = new Buffer;
		buffer->LoadVertexData((const float*)position, 4, 2);
		buffer->LoadVertexData((const float*)texCoord, 4, 2);
		buffer->CommitData();
		buffer->LoadElements((const unsigned char*)indices, 6);
		//��¼�ַ��Ķ��㻺��
		buffers.push_back(buffer);

		//�ı��������ƶ�һ�ξ��룬׼���洢��һ���ַ�����Ϣ
		x += (ch->advance >> 6) * scale;
	}
}

//��Ⱦ����
void Text::Render()
{
	//������ɫ��
	shader->RunProgram();
	//�����ڻ�
	glEnable(GL_BLEND);
	//�����ڻ췽��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//��Ⱦ���ݵ�ÿһ���ַ�
	for (size_t i = 0; i < buffers.size(); i++)
	{
		//���ַ�����
		glBindTextureUnit(0u, message[i]->texture);
		//�󶨲�����
		glBindSampler(0u, message[i]->sampler);
		//�󶨶��㻺��
		buffers[i]->Bind();
		//����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	}
}
