#include "SkyBox.h"
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"

SkyBox::SkyBox()
{
	//��ʼ������������
	texture = new Texture(TextureType::Cube);
	//��ʼ����պеĶ��㻺��
	buffer = new Buffer;

	//����λ������
	const float postion[24][3] =
	{
		//x = 1
		{ 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f }, {1.0f, -1.0f, -1.0f }, {1.0f, 1.0f, -1.0f },
		//x = -1
		{ -1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f }, {-1.0f, -1.0f, -1.0f },{ -1.0f, 1.0f, -1.0f },
		//y = 1
		{ 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f },{ 1.0f, 1.0f, -1.0f },
		//y = -1
		{ 1.0f, -1.0f, 1.0f },{ -1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },
		//z = 1
		{ 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f }, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f },
		//z = -1
		{ 1.0f, 1.0f, -1.0f },{ -1.0f, 1.0f, -1.0f },{ -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },
	};
	//����
	const unsigned char indices[12][3] =
	{
		//x = 1
		{ 0,  1,  2 },{ 2,  3,  0 },
		//x = -1
		{ 6,  5,  4 },{ 4,  7,  6 },
		//y = 1
		{ 10,  9, 8 },{ 8, 11, 10 },
		//y = -1
		{ 12, 13, 14 },{ 14, 15, 12 },
		//z = 1
		{ 16, 17, 18 },{ 18, 19, 16 },
		//z = -1
		{ 22, 21, 20 },{ 20, 23, 22 },
	};
	//���붥��λ������
	buffer->LoadVertexData((const float*)postion, 24, 3);
	//�ύ����
	buffer->CommitData();
	//������������
	buffer->LoadElements((const unsigned char *)indices, 36);
}

SkyBox::~SkyBox()
{
}

//������պ�
void SkyBox::Draw()
{
	//������պ�
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
}

////�����ң����ϣ��£�ǰ�����˳�������պе�����
void SkyBox::LoadTexture(std::string (&texturePath)[6])
{
	texture->LoadTexture(texturePath);
}
