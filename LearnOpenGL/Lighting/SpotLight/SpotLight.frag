#version 450 core

//����Ĳ���
struct Material
{
	//���ʵ�������ⷴ��ϵ��
	sampler2D KDiffuse;
	//���ʵľ���߹ⷴ��ϵ��
	vec3 KSpecular;
	//�����
	sampler2D emission;
	//���ʵķ����
	float shininess;
};
//��������
struct Light
{
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
in vec3 fragPosition;
//��ǰ����ĵ�ķ�����
in vec3 fragNormal;
//��ǰ����ĵ����������
in vec2 fragTexCoord;
//�۲�ռ��о۹�Ƶ�λ��
in vec3 vLightPosition;
//�۲�ռ��о۹�Ƶķ���
in vec3  vLightDirection;

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

	//��������ⷽ��
	vec3 incidentLightDir = normalize(fragPosition - vLightPosition);
	//�������������
	vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);

	//���㵱ǰ�㵽�ӵ�ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴����ߵķ���
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//���㾵��߹����
	vec4 specular = vec4(light.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDirection), 0), material.shininess);

	//���㵱ǰ�㵽��Դ�ľ���
	float fragLightDistance = length(fragPosition - vLightPosition);
	//����˥��ֵ
	float attenuation = 1.0 / (light.quadratic * fragLightDistance * fragLightDistance + light.linear * fragLightDistance + light.constant);
	//��Դ������������˥��ֵ
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	//��������ⷽ��;۹�Ʒ���ļнǵ�����
	float theta = dot(incidentLightDir, vLightDirection);
	//��������Բ׶�����Ҳ�ֵ
	float epsilon = light.interCutOff - light.outerCutOff;
	//����۹�Ƶ��ڸõ�Ĺ���ǿ��
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0, 1);
	//����������;���߹��������ǿ��ֵ
	diffuse  *= intensity;
	specular *= intensity;

	//�������ƬԪ
	lastColor = ambient + diffuse + specular;
}