#version 450 core

//����Ĳ���
struct Material
{
	//���ʵ�������ⷴ��ϵ��
	sampler2D KDiffuse;
	//���ʵľ���߹ⷴ��ϵ��
	vec3 KSpecular;
	//���ʵķ����
	float shininess;
};
//ƽ�й�
struct ParallelLight
{
	//ƽ�йⷽ��
	vec3 direction;
	//���������
	vec3 ambient;
	//����������
	vec3 diffuse;
	//����߹����
	vec3 specular;
};
//���Դ
struct PointLight
{
	//λ��
	vec3 position;
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
//�۹�
struct SpotLight
{
	//λ��
	vec3 position;
	//����
	vec3 direction;
	//��Բ׶�ǵ�����
	float interCutOff;
	//��Բ׶�ǵ�����
	float outerCutOff;
	//�������շ���
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

//��ǰ����ĵ��λ��
in vec3 fragPos;
//��ǰ����ĵ�ķ�����
in vec3 fragNormal;
//��ǰ����ĵ����������
in vec2 fragTexCoord;

//����Ĳ���
uniform Material material;
//ƽ�й�Դ
uniform ParallelLight parallelLight;
//���Դ
uniform PointLight pointLight[2];
//�۹��
uniform SpotLight spotLight;
//�۲������
uniform vec3 viewPos;

//����ƽ�й�Ĺ���ֵ
vec4 CalParalllelLight(ParallelLight parallelLight, vec3 viewDir);
//������Դ�Ĺ���ֵ
vec4 CalPointLight(PointLight pointLight, vec3 viewDir);
//����۹�Ĺ���ֵ
vec4 CalSpotLight(SpotLight spotLight, vec3 viewDir);

//���������ƬԪ
out vec4 lastColor;

void main()
{
	//��ʼ������
	lastColor = vec4(0);
	//����ƬԪ���ӵ�ķ���
	vec3 viewDir = normalize(viewPos - fragPos);
	//�ۼ�ƽ�й�Ĺ���
	lastColor = CalParalllelLight(parallelLight, viewDir);
	//�ۼӵ��Դ�Ĺ���
	for (int i = 0; i < 2; i++)
	{
		lastColor += CalPointLight(pointLight[i], viewDir);
	}
	//�ۼӾ۹�Ĺ���
	lastColor += CalSpotLight(spotLight, viewDir);
}

//����ƽ�й�Ĺ���ֵ
vec4 CalParalllelLight(ParallelLight parallelLight, vec3 viewDir)
{
	//���㻷�������
	vec4 ambient = vec4(parallelLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//�������������
	vec4 diffuse = vec4(parallelLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(normalize(-parallelLight.direction), fragNormal), 0);
	//���㷴��ⷽ��
	vec3 reflectDir = reflect(parallelLight.direction, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(parallelLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);

	return ambient + diffuse + specular;
}

//������Դ�Ĺ���ֵ
vec4 CalPointLight(PointLight pointLight, vec3 viewDir)
{
	//���������ķ���
	vec3 incidentLightDir = normalize(fragPos - pointLight.position);

	//���㻷�������
	vec4 ambient = vec4(pointLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//��������������
	vec4 diffuse = vec4(pointLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);
	//���㷴��ⷽ��
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(pointLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	//�����Դ����ǰ��ľ���
	float lightFragDis = length(pointLight.position - fragPos);
	//����˥�����
	float attenuation = 1.0 / (pointLight.quadratic * lightFragDis * lightFragDis + pointLight.linear * lightFragDis + pointLight.constant);
	//�����Դ��������������˥�����
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//�������յ��Դ�Ĺ���
	//return ambient + diffuse + specular;
	return ambient + diffuse + specular;
}

//����۹�Ĺ���ֵ
vec4 CalSpotLight(SpotLight spotLight, vec3 viewDir)
{
	//���������ķ���
	vec3 incidentLightDir = normalize(fragPos - spotLight.position);

	//���㻷�������
	vec4 ambient = vec4(spotLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//�������������
	vec4 diffuse = vec4(spotLight.diffuse *  texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);
	//���㷴��ⷽ��
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(spotLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	//�����Դ����ǰ��ľ���
	float lightFragDis = length(spotLight.position - fragPos);
	//����˥�����
	float attenuation = 1.0 / (spotLight.quadratic * lightFragDis * lightFragDis + spotLight.linear * lightFragDis + spotLight.constant);
	//��Դ��������������˥��ֵ
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//����������ߺ;۹ⷽ��ļн�����
	float theta = dot(incidentLightDir, spotLight.direction);
	//��������Բ׶�����Ҳ�ֵ
	float epsilon = spotLight.interCutOff - spotLight.outerCutOff;
	//���㵱ǰ��Ĺ���ǿ�ȱ���
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0, 1);
	//������������;���߹�������Ϲ���ǿ�ȱ���
	diffuse *= intensity;
	specular *= intensity;

	return ambient + diffuse + specular;
}