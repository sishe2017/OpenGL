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
	//˥��ģ�Ͷ�����ϵ��
	float quadratic;
	//˥��ģ��һ����ϵ��
	float linear;
	//˥��ģ�ͳ�����ϵ��
	float constant;
};

//��ǰ����ĵ��λ��
in vec3 fragPosition;
//��ǰ����ĵ�ķ�����
in vec3 fragNormal;
//��ǰ����ĵ����������
in vec2 fragTexCoord;
//�۲�ռ���ƽ�й�ķ���
in vec3 vLightPosition;

//����Ĳ���
uniform Material material;
//��Դ������
uniform Light light;

//���������ƬԪ
out vec4 lastColor;


void main()
{
	//���㵱ǰ�㵽��Դ�ľ���
	float fragLightDistance = length(fragPosition - vLightPosition);
	//����˥��ֵ
	float attenuation = 1.0 / (light.quadratic * fragLightDistance * fragLightDistance + light.linear * fragLightDistance + light.constant);

	//���㻷�������
	vec4 ambient = vec4(light.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1) * attenuation;

	//��������ⷽ��
	vec3 lightDirection = normalize(fragPosition - vLightPosition);
	//�������������
	vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-lightDirection, fragNormal), 0) * attenuation;

	//���㵱ǰ�㵽�ӵ�ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴����ߵķ���
	vec3 reflectDirection = reflect(lightDirection, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(light.specular * texture(material.KSpecular, fragTexCoord).rgb, 1) * pow(max(dot(reflectDirection, viewDirection), 0), material.shininess) * attenuation;

	//������յ�ƬԪ
	lastColor = ambient + diffuse + specular;
}