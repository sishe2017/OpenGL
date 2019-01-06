#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Material.h"
#include "DataSet.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Blinn-Phong", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Blinn-Phong/Blinn-Phong/Box.vert",
		"E:/OpenGLProject/Blinn-Phong/Blinn-Phong/Box.frag");
	
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(boxShader, "view","viewPos");
	
	//创建箱子物体
	GameObject box;
	//初始化箱子的transform组件
	box.transform = new Transform(boxShader, "model");
	//设置箱子的纹理
	box.texture = new Texture(TextureType::TwoD);
	//载入纹理数据
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//创建物体的材质
	Material *material = new Material;
	material->SetKSpecular(glm::vec3(1.0f), "material.KSpecular");
	material->SetKShininess(32.0f, "material.shininess");
	//给物体添加材质
	box.AddMaterial(boxShader, material);
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f));
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;

	//创建点光源的名字集合
	PointLightName pln;
	pln.positionName = "pointLight.pos";
	pln.quadraticName = "pointLight.quadratic";
	pln.linearName = "pointLight.linear";
	pln.constantName = "pointLight.constant";
	pln.ambientName = "pointLight.ambient";
	pln.diffuseName = "pointLight.diffuse";
	pln.specularName = "pointLight.specular";

	//创建一个点光源
	PointLight pointLight;
	//设置点光源的位置
	pointLight.position = glm::vec3(0.5f, 0.5f, 2.0f);
	//设置点光源的光源分量
	pointLight.SetADS(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	//设置点光源的衰减模型系数
	pointLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	//将点光源和名字集合联系
	pointLight.AssociateShader(boxShader, &pln);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}