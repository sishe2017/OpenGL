#version 450 core

//����Ĳ���
struct Material
{
	//���ʵ�������ⷴ��ϵ��
	sampler2D KDiffuse;
	//���ʵľ���߹ⷴ��ϵ��
	sampler2D KSpecular;
	//�����
	sampler2D emission;
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

//��ǰ����ĵ��λ��
in vec3 fragPosition;
//��ǰ����ĵ�ķ�����
in vec3 fragNormal;
//��ǰ����ĵ����������
in vec2 fragTexCoord;
//�۲�ռ���ƽ�й�ķ���
in vec3 vLightDirection;

//����Ĳ���
uniform Material material;
//��Դ������
uniform Light light;

//���������ƬԪ
out vec4 lastColor;


void main()
{
	//���㻷�������
	vec4 ambient = vec4(light.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);

	//�������������
	vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-vLightDirection, fragNormal), 0);

	//���㵱ǰ�㵽�ӵ�ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴����ߵķ���
	vec3 reflectDirection = reflect(vLightDirection, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(light.specular * texture(material.KSpecular, fragTexCoord).rgb, 1) * pow(max(dot(reflectDirection, viewDirection), 0), material.shininess);

	//������յ�ƬԪ
	lastColor = ambient + diffuse + specular;
}