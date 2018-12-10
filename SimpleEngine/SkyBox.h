#pragma once
#include <string>

class Texture;
class Transform;
class Buffer;
class Shader;

//��պ���
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	//��Ⱦ��պе���ɫ��
	Shader *shader;
	//������պ�
	void Draw();
	//�����ң����ϣ��£�ǰ�����˳�������պе�����
	void LoadTexture(std::string (&texturePath)[6]);
	//����������
	Texture * texture;
	//������պ�����Ҫ�Ķ��㻺��
	Buffer *buffer;
};