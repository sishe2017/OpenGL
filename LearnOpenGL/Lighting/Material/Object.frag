#version 450 core

//����Ĳ���
struct Material
{
	//���ʵĻ����ⷴ��ϵ��
	vec3 KAmbient;
	//���ʵ�������ⷴ��ϵ��
	vec3 KDiffuse;
	//���ʵľ���߹ⷴ��ϵ��
	vec3 KSpecular;
	//���ʵķ����
	float shininess;
};
//��������
struct Light
{
	//�������շ���
	vec3 ambient;
	//����������
	vec3 diffuse;
	//����߹����
	vec3 specular;
};

//ƬԪλ��
in vec3 fragPosition;
//ƬԪ������
in vec3 fragNormal;
//�ƹ�λ��
in vec3 vLightPosition;

//�ƹ���ɫ
uniform vec3 lightColor;
//���������ɫ
uniform vec4 objectColor;
//����Ĳ���
uniform Material material;
//��������
uniform Light light;


//���������ƬԪ��ɫ
out vec4 lastColor;

void main()
{
	//���㵱ǰƬԪ�Ļ��������
	vec4 ambient = vec4(light.ambient * material.KAmbient, 1);

	//����������߷���
	vec3 lightDirection = normalize(vLightPosition - fragPosition);
	//�������������
	vec4 diffuse = vec4(light.diffuse * material.KDiffuse, 1) * max(dot(normalize(fragNormal),lightDirection), 0.0f);

	//���㵱ǰƬԪ���۲��ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴���ķ���
	vec3 reflectDirection = reflect(-lightDirection, normalize(fragNormal));
	//���㵱ǰƬԪ�ľ��淴�����
	vec4 specular = vec4(light.specular * material.KSpecular, 1) * pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

	//�������ƬԪ
	lastColor = (ambient + diffuse) * objectColor + specular;
	//lastColor = ambient * objectColor;
}