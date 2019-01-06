#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("StencilTest", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/Blend/Blend/Blend.vert", "E:/OpenGLProject/Blend/Blend/Blend.frag");
	
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(boxShader, "view");
	
	//创建箱子物体
	GameObject box;
	//初始化箱子的transform组件
	box.transform = new Transform(boxShader, "model");
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f));
	//初始化箱子的纹理
	box.texture = new Texture(TextureType::TwoD);
	//载入纹理数据
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;
	
	//创建边框的着色器
	Shader *smileFaceShader = engine.CreateShader("E:/OpenGLProject/Blend/Blend/Blend.vert", "E:/OpenGLProject/Blend/Blend/SmileFace.frag");
	//运行边框着色器
	smileFaceShader->RunProgram();
	//设置投影矩阵
	engine.InitProjection(smileFaceShader, "projection");
	//摄像机和着色器关联
	camera.AssociateShader(smileFaceShader, "view");
	
	//笑脸
	GameObject smileFace;
	//初始化笑脸的transform组件
	smileFace.transform = new Transform(smileFaceShader, "model");
	//设置在世界空间的位置
	smileFace.transform->Position(glm::vec3(0.5f, 0.5f, 0.505f));
	//初始化笑脸的纹理
	smileFace.texture = new Texture(TextureType::TwoD);
	//载入笑脸纹理数据
	smileFace.texture->LoadTexture("F:/GitRepository/Resource/blending_transparent_window.png");
	//载入笑脸的缓存数据
	smileFace.buffer = InitFaceBuffer();
	//记录渲染笑脸的着色器
	smileFace.shader = smileFaceShader;

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.box = &box;
	param.smileFace = &smileFace;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//开启融混
	glEnable(GL_BLEND);
	//设置融混的源因子和目标因子
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//开始游戏循环
	engine.Run(Update, &param);;

	return 0;
}