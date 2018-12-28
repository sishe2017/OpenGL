#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;
class SkyBox;

//摄像机移动方向
enum class Direction
{
	//前
	Forward,
	//后
	Back,
	//左
	Left,
	//右
	Right,
	//上
	Up,
	//下
	Down
};

//摄像机类
class Camera
{
public:
	Camera(glm::vec3 cameraPosition);
	~Camera();
	//移动摄像机
	void Move(Direction direction);
	//设置摄像机移动的速度
	void SetSpeed(float speed);
	//俯仰角旋转
	void PitchRotate(Direction direction);
	//偏航角旋转
	void HeadingRotate(Direction direction);
	//关联着色器程序
	void AssociateShader(Shader *shader, const char *viewName);
	//关联着色器程序
	void AssociateShader(Shader *shader, const char *viewName, const char *viewPosName);
	//影响天空盒子
	void InflunceSkyBox(SkyBox *skyBox, const char *viewName);
	//观察矩阵
	glm::mat4 view;
	//摄像机位置
	glm::vec3 position;
private:

	//摄像机的前向量
	glm::vec3 front = glm::vec3(0, 0, -1.0f);
	//摄像机的上向量
	glm::vec3 up = glm::vec3(0, 1.0f, 0);
	//摄像机的右向量
	glm::vec3 right = glm::vec3(1.0f, 0, 0);
	//摄像机的俯仰角
	float pitch = 0;
	//摄像机的偏航角
	float heading = -90.0f;
	//摄像机朝向的目标
	glm::vec3 target = glm::vec3(0, 0, -1.0f);
	//摄像机和目标之间的距离
	float distance;
	//摄像机移动速度
	float speed = 0.1f;
	//摄像机旋转速度
	float rotateSpeed = 1.0f;
};

