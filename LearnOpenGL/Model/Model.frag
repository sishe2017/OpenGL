#version 450 core

//����Ĳ���
struct Material
{
	//���ʵ�������ⷴ��ϵ��
	sampler2D KDiffuse;
	//���ʵľ���߹ⷴ��ϵ��
	sampler2D KSpecular;
	//���ʵķ����
	float shininess;
};

//���Դ������
struct PointLight
{
	//���������
	vec3 ambient;
	//����������
	vec3 diffuse;
	//����߹����
	vec3 specular;
	//������˥��ϵ��
	float quadratic;
	//һ����˥��ϵ��
	float linear;
	//������˥��ϵ��
	float constant;
};

//�۲�ռ��ƬԪλ��
in vec3 fragPos;
//�۲�ռ�Ķ��㷨����
in vec3 fragNormal;
//���Դ�ڹ۲�ռ��λ��
in vec3 vLightPosition;
//��ǰ����ĵ����������
in vec2 fragTexCoord;

//����Ĳ���
uniform Material material;
//���Դ
uniform PointLight pointLight;

//���������ƬԪ
out vec4 lastColor;

//������Դ�Ĺ���ֵ
vec4 CalPointLight(PointLight pointLight, vec3 viewDir);

void main()
{
	//����۲췽��
	vec3 viewDir = normalize(0 - fragPos);
	//���ϵ��Դ����ֵ
	lastColor = CalPointLight(pointLight, viewDir);
}

//������Դ�Ĺ���ֵ
vec4 CalPointLight(PointLight pointLight, vec3 viewDir)
{
	//���������ķ���
	vec3 incidentLightDir = normalize(fragPos - vLightPosition);

	//���㻷�������
	vec4 ambient = vec4(pointLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//��������������
	vec4 diffuse = vec4(pointLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);
	//���㷴��ⷽ��
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(pointLight.specular * texture(material.KSpecular, fragTexCoord).rgb, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	//�����Դ����ǰ��ľ���
	float lightFragDis = length(vLightPosition - fragPos);
	//����˥�����
	float attenuation = 1.0 / (pointLight.quadratic * lightFragDis * lightFragDis + pointLight.linear * lightFragDis + pointLight.constant);
	//�����Դ��������������˥�����
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//�������յ��Դ�Ĺ���
	return ambient + diffuse + specular;
}
