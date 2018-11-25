#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/ParalllelLight.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/SpotLight.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("ParallelLight", 512, 512);
	//创建着色器
	Shader *shader = engine.CreateShader("E:/OpenGLProject/MultipleLight/MultipleLight/MultipleLight.vert", "E:/OpenGLProject/MultipleLight/MultipleLight/MultipleLight.frag");

	//初始化缓存数组
	InitBuffer();
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	
	//运行着色器程序
	shader->RunProgram();
	
	//初始化投影矩阵
	engine.InitProjection(shader, "projection");

	//将摄像机和着色器相关联
	camera.AssociateShader(shader, "view", "viewPos");

	//创建物体的材质
	Material material;
	//设置材质的参数
	material.SetKSpecular(glm::vec3(1.0f, 1.0f, 1.0f), "material.KSpecular");
	material.SetKShininess(32.0f, "material.shininess");

	//创建漫反射的二维纹理
	Texture diffuseTexture(TextureType::TwoD, shader, "material.KDiffuse");
	//加载纹理数据
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//设置滤波为线性过滤
	diffuseTexture.SetTextureProperty(Filter::Linear);
	//设置纹理环绕为重复
	diffuseTexture.SetTextureProperty(Wrap::Repeat);
	
	//创建物体
	GameObject *box[5];
	for (int i = 0; i < 5; i++)
	{
		//配置物体的transform组件
		Transform *transform = new Transform(shader, "model");
		//创建游戏物体
		box[i] = new GameObject(transform);
		//为物体添加材质
		box[i]->AddMaterial(&material);
	}
	//设置箱子的位置
	box[0]->transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	box[1]->transform->Position(glm::vec3(2.0f, 5.0f, -15.0f));
	box[2]->transform->Position(glm::vec3(-1.5f, -2.2f, -2.5f));
	box[3]->transform->Position(glm::vec3(-3.8f, -2.0f, -12.3f));
	box[4]->transform->Position(glm::vec3(2.4f, -0.4f, -3.5f));

	//设置平行光的在着色器的名字集合
	ParallelLightName parallelLightName;
	parallelLightName.directionName = "parallelLight.direction";
	parallelLightName.ambientName = "parallelLight.ambient";
	parallelLightName.specularName = "parallelLight.specular";
	parallelLightName.diffuseName = "parallelLight.diffuse";
	//创建一个平行光
	ParallelLight parallelLight;
	//设置平行光的方向
	parallelLight.SetDirection(glm::vec3(-3, -1, -4));
	//设置平行光的三个分量
	parallelLight.SetADS(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f));
	//关联着色器
	parallelLight.AssociateShader(shader, &parallelLightName);

	//创建两个点光源的名字集合
	PointLightName pointLightName[2];
	//创建两个点光源
	PointLight pointLight[2];
	//设置第一个点光源的名字集合
	pointLightName[0].positionName = "pointLight[0].position";
	pointLightName[0].ambientName = "pointLight[0].ambient";
	pointLightName[0].diffuseName = "pointLight[0].diffuse";
	pointLightName[0].specularName = "pointLight[0].specular";
	pointLightName[0].quadraticName = "pointLight[0].quadratic";
	pointLightName[0].linearName = "pointLight[0].linear";
	pointLightName[0].constantName = "pointLight[0].constant";
	//设置第一个点光源的位置
	pointLight[0].position = glm::vec3(1.5f, 0.5f, 1.5f);
	//设置第一个点光源的三个属性
	pointLight[0].SetADS(glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(1.0f));
	//设置第一个点光源衰减系数
	pointLight[0].SetAttenuation(0.032f, 0.09f, 1.0f);
	//将第一个点光源关联着色器
	pointLight[0].AssociateShader(shader, &pointLightName[0]);
	//设置第二个点光源的名字集合
	pointLightName[1].positionName = "pointLight[1].position";
	pointLightName[1].ambientName = "pointLight[1].ambient";
	pointLightName[1].diffuseName = "pointLight[1].diffuse";
	pointLightName[1].specularName = "pointLight[1].specular";
	pointLightName[1].quadraticName = "pointLight[1].quadratic";
	pointLightName[1].linearName = "pointLight[1].linear";
	pointLightName[1].constantName = "pointLight[1].constant";
	//设置第二个点光源的位置
	pointLight[1].position = glm::vec3(-1.5, 1.5, 0);
	//设置第二个点光源的三个属性
	pointLight[1].SetADS(glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(1.0f));
	//设置第二个点光源衰减系数
	pointLight[1].SetAttenuation(0.032f, 0.09f, 1.0f);
	//将第二个点光源关联着色器
	pointLight[1].AssociateShader(shader, &pointLightName[1]);

	//设置聚光灯在着色器中和名字集合
	SpotLightName spotLightName;
	spotLightName.positionName = "spotLight.position";
	spotLightName.directionName = "spotLight.direction";
	spotLightName.interCutOffName = "spotLight.interCutOff";
	spotLightName.outerCutOffName = "spotLight.outerCutOff";
	spotLightName.ambientName = "spotLight.ambient";
	spotLightName.diffuseName = "spotLight.diffuse";
	spotLightName.specularName = "spotLight.specular";
	spotLightName.quadraticName = "spotLight.quadratic";
	spotLightName.linearName = "spotLight.linear";
	spotLightName.constantName = "spotLight.constant";
	//创建一个聚光灯
	SpotLight spotLight;
	//设置聚光灯的位置
	spotLight.position = glm::vec3(0.5f, 0.5f, 2.5f);
	//设置聚光灯的方向
	spotLight.SetDirection(glm::vec3(0, 0, -1.0f));
	//设置聚光灯的内外圆锥角
	spotLight.SetCutOff(13.0f, 17.0f);
	//设置环境光分量,漫反射光分量,镜面高光分量
	spotLight.SetADS(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f));
	//设置衰减模型系数
	spotLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	//将聚光灯和着色器联系
	spotLight.AssociateShader(shader, &spotLightName);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.object = box;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}