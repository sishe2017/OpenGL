#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Library/glm/glm.hpp"
#include <map>
#include <vector>
#include <glad/glad.h>

class Buffer;
class Shader;
class Window;


//�ı����
class Text
{
public:
	Text(Window *window);
	~Text();

	//���������С
	void SetSize(unsigned int size);
	//����������ɫ
	void SetColor(glm::vec3 color);
	//����������
	void LoadFont(std::string fontPath);
	//��¼�ı�����
	void Content(std::string content, float x, float y);
	//��Ⱦ����
	void Render();

private:
	struct Character
	{
		// ��������
		GLuint texture;
		//��ǰ�������������
		GLuint sampler;
		// ���δ�С
		glm::ivec2 size;
		// �ӻ�׼�ߵ�������/������ƫ��ֵ
		glm::ivec2 bearing;
		// ԭ�����һ������ԭ��ľ���
		GLuint advance;
	};
	//freetype��
	FT_Library ft;
	//��
	FT_Face face;
	//��ǰ�����С
	float scale = 1;
	//�ַ���Ϣ��
	std::map<GLchar, Character> characters;
	//Ҫ��Ⱦ���ı������õ����ַ�
	std::vector<Character*> message;
	//��Ⱦ�����õ����ı��εĶ��㻺��
	std::vector<Buffer*> buffers;
	//��Ⱦ����ʹ�õ���ɫ��
	Shader *shader;
	//������ɫ
	glm::vec3 color = glm::vec3(0);
};