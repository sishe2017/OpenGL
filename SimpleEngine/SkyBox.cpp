#include "SkyBox.h"
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"

SkyBox::SkyBox()
{
	//初始化立方体纹理
	texture = new Texture(TextureType::Cube);
	//初始化天空盒的顶点缓存
	buffer = new Buffer;

	//顶点位置数据
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
	//索引
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
	//载入顶点位置数据
	buffer->LoadVertexData((const float*)postion, 24, 3);
	//提交数据
	buffer->CommitData();
	//载入索引数据
	buffer->LoadElements((const unsigned char *)indices, 36);
}

SkyBox::~SkyBox()
{
}

//绘制天空盒
void SkyBox::Draw()
{
	//绘制天空盒
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
}

////按照右，左，上，下，前，后的顺序加载天空盒的纹理
void SkyBox::LoadTexture(std::string (&texturePath)[6])
{
	texture->LoadTexture(texturePath);
}
