#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <string>
#include <vector>

class Buffer;
class Texture;
class Shader;

//模型的网格
class Mesh
{
public:
	Mesh();
	~Mesh();
	//网格的顶点位置
	std::vector<float> position;
	//网格的法线方向
	std::vector<float> normal;
	//网格的纹理坐标
	std::vector<float> texCoord;
	//网格的顶点索引
	std::vector<unsigned int> indices;
	//提交网格数据
	void CommitData();
	//加载网格的漫反射纹理数据
	void RecordDiffuseMap(Texture *diffuseMap, std::string diffuseName, GLuint textureUnit);
	//加载网格的镜面高光纹理数据
	void RecordSpecularMap(Texture *specularMap, std::string specularName, GLuint textureUnit);
	//绘制当前网格
	void Draw(Shader *shader);
private:
	//网格中的缓存
	Buffer *buffer;
	//网格的漫反射纹理贴图集合
	std::vector<Texture*> diffuseMaps;
	//网格镜面高光纹理贴图集合
	std::vector<Texture*> specularMaps;
	//漫反射纹理贴图采样器名字集合
	std::vector<std::string> diffuseNames;
	//镜面高光纹理贴图采样器名字集合
	std::vector<std::string> specularNames;
	//漫反射采样器绑定的纹理单元集合
	std::vector<GLuint> diffuseUnits;
	//镜面高光采样器绑定的纹理单元集合
	std::vector<GLuint> specularUnits;
};