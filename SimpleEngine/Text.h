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


//文本组件
class Text
{
public:
	Text(Window *window);
	~Text();

	//设置字体大小
	void SetSize(unsigned int size);
	//设置字体颜色
	void SetColor(glm::vec3 color);
	//加载字体风格
	void LoadFont(std::string fontPath);
	//记录文本内容
	void Content(std::string content, float x, float y);
	//渲染字体
	void Render();

private:
	struct Character
	{
		// 字形纹理
		GLuint texture;
		//当前字形纹理采样器
		GLuint sampler;
		// 字形大小
		glm::ivec2 size;
		// 从基准线到字形左部/顶部的偏移值
		glm::ivec2 bearing;
		// 原点距下一个字形原点的距离
		GLuint advance;
	};
	//freetype库
	FT_Library ft;
	//面
	FT_Face face;
	//当前字体大小
	float scale = 1;
	//字符信息表
	std::map<GLchar, Character> characters;
	//要渲染的文本内容用到的字符
	std::vector<Character*> message;
	//渲染字体用到的四边形的顶点缓存
	std::vector<Buffer*> buffers;
	//渲染字体使用的着色器
	Shader *shader;
	//字体颜色
	glm::vec3 color = glm::vec3(0);
};