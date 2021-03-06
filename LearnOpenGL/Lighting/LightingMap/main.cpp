#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightingMap", 512, 512);
	//创建着色器
	Shader *shader = engine.CreateShader("E:/OpenGLProject/LightingMaps/LightingMaps/LightingMap.vert", "E:/OpenGLProject/LightingMaps/LightingMaps/LightingMap.frag");

	//初始化缓存数组
	InitBuffer();
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	
	//运行着色器程序
	shader->RunProgram();
	
	//初始化投影矩阵
	engine.InitProjection(shader, "projection");

	//将摄像机和着色器相关联
	camera.AssociateShader(shader, "view");

	//创建物体的材质
	Material material;
	//设置材质的参数
	material.SetKSpecular(glm::vec3(0.5f, 0.5f, 0.5f), "material.KSpecular");
	material.SetKShininess(64.0f, "material.shininess");

	//创建漫反射的二维纹理
	Texture diffuseTexture(TextureType::TwoD, shader, "material.KDiffuse");
	//加载纹理数据
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//设置滤波为线性过滤
	diffuseTexture.SetTextureProperty(Filter::Linear);
	//设置纹理环绕为重复
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	//创建镜面反射的二维纹理
	Texture specularTexture(TextureType::TwoD, shader, "material.KSpecular");
	//加载纹理数据
	specularTexture.LoadTexture("F:/GitRepository/Resource/container2_specular.png");
	//设置滤波为线性过滤
	specularTexture.SetTextureProperty(Filter::Linear);
	//设置纹理环绕为重复
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	////创建放射光的二维纹理
	//Texture emissionTexture(TextureType::TwoD, shader, "material.emission");
	////加载纹理数据
	//emissionTexture.LoadTexture("F:/GitRepository/Resource/matrix.jpg");
	////设置滤波为线性过滤
	//emissionTexture.SetTextureProperty(Filter::Linear);
	////设置纹理环绕为重复
	//emissionTexture.SetTextureProperty(Wrap::Repeat);
	
	//初始化物体的Transform组件
	Transform *transform = new Transform(shader, "model");
	//创建物体
	GameObject box(transform);
	//为物体添加材质
	box.AddMaterial(&material);
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//创建点光源
	PointLight light(glm::vec3(0.7f, 0.7f, 4));
	//设置光源属性
	light.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
	light.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
	light.SetSpecular(glm::vec3(1, 1, 1), "light.specular");
	//将点光源和着色器相关联
	light.AssociateShader(shader, "wLightPosition");

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.object = &box;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}