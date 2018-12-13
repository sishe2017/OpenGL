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

//ģ��
class Model
{
public:
	Model();
	~Model();
	//������������������ּ��ϣ��±��ǹ���������Ԫ��
	std::vector<std::string> diffuseNameUnits;
	//����߹�������������ּ��ϣ��±��ǹ���������Ԫ��
	std::vector<std::string> specularNameUnits;
	//����ģ�͵���ɫ��
	Shader *shader;
	//ģ�͵�transform���
	Transform *transform;
	//����ģ������
	void LoadModel(std::string path);
	//����ģ��
	void Draw();
private:
	//�ݹ鴦��ڵ�
	void ProcessNode(aiNode *node);
	//����ڵ��е���������
	void ProcessMesh(aiMesh *mesh);
	//���������������ͼ����
	void LoadTexture(aiMaterial *material, aiTextureType type, Mesh *mesh, GLuint &textureUnit);
	//����ģ�����ݵĳ���
	aiScene *scene;
	//�洢ģ�����������������
	std::vector<Mesh*> meshs;
	//ģ�����ڵ�Ŀ¼
	std::string directory;
	//����ģ����Ҫ������������
	std::vector<Texture*> textures;
	//�����ļ���·������
	std::vector<std::string> paths;
};