#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <utility>
#include <glad/glad.h>

class Mesh;
class Texture;
class Transform;
class Shader;

//模型
class Model
{
public:
	Model();
	~Model();
	//漫反射纹理采样器名字集合（下标是关联的纹理单元）
	std::vector<std::string> diffuseNameUnits;
	//镜面高光纹理采样器名字集合（下标是关联的纹理单元）
	std::vector<std::string> specularNameUnits;
	//绘制模型的着色器
	Shader *shader;
	//模型的transform组件
	Transform *transform;
	//加载模型数据
	void LoadModel(std::string path);
	//绘制模型
	void Draw();
private:
	//递归处理节点
	void ProcessNode(aiNode *node);
	//处理节点中的网格数据
	void ProcessMesh(aiMesh *mesh);
	//加载网格的纹理贴图数据
	void LoadTexture(aiMaterial *material, aiTextureType type, Mesh *mesh, GLuint &textureUnit);
	//保存模型数据的场景
	aiScene *scene;
	//存储模型中所有网格的容器
	std::vector<Mesh*> meshs;
	//模型所在的目录
	std::string directory;
	//加载模型需要的所有纹理集合
	std::vector<Texture*> textures;
	//纹理文件的路径集合
	std::vector<std::string> paths;
};