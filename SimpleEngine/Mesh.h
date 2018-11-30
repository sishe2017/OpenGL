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

//ģ�͵�����
class Mesh
{
public:
	Mesh();
	~Mesh();
	//����Ķ���λ��
	std::vector<float> position;
	//����ķ��߷���
	std::vector<float> normal;
	//�������������
	std::vector<float> texCoord;
	//����Ķ�������
	std::vector<unsigned int> indices;
	//�ύ��������
	void CommitData();
	//�����������������������
	void RecordDiffuseMap(Texture *diffuseMap, std::string diffuseName, GLuint textureUnit);
	//��������ľ���߹���������
	void RecordSpecularMap(Texture *specularMap, std::string specularName, GLuint textureUnit);
	//���Ƶ�ǰ����
	void Draw(Shader *shader);
private:
	//�����еĻ���
	Buffer *buffer;
	//�����������������ͼ����
	std::vector<Texture*> diffuseMaps;
	//������߹�������ͼ����
	std::vector<Texture*> specularMaps;
	//������������ͼ���������ּ���
	std::vector<std::string> diffuseNames;
	//����߹�������ͼ���������ּ���
	std::vector<std::string> specularNames;
	//������������󶨵�����Ԫ����
	std::vector<GLuint> diffuseUnits;
	//����߹�������󶨵�����Ԫ����
	std::vector<GLuint> specularUnits;
};