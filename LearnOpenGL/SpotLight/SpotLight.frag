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
	//�й�ǵ�����
	float cutoff;
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
	//��������ⷽ��
	vec3 incidentLightDir = normalize(fragPosition - vLightPosition);
	//��������ⷽ��;۹�Ʒ���ļнǵ�����
	float theta = dot(incidentLightDir, vLightDirection);

	//�����ǰ���Ƿ��ھ۹�Ʒ�Χ��
	if (theta > light.cutoff)
	{
		//���㵱ǰ�㵽��Դ�ľ���
		float fragLightDistance = length(fragPosition - vLightPosition);
		//����˥��ֵ
		float attenuation = 1.0 / (light.quadratic * fragLightDistance * fragLightDistance + light.linear * fragLightDistance + light.constant);
		
		//���㻷�������
		vec4 ambient = vec4(light.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);

		//�������������
		vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0) * attenuation;

		//���㵱ǰ�㵽�ӵ�ķ���
		vec3 viewDirection = normalize(-fragPosition);
		//���㷴����ߵķ���
		vec3 reflectDir = reflect(incidentLightDir, fragNormal);
		//���㾵��߹����
		vec4 specular = vec4(light.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDirection), 0), material.shininess) * attenuation;

		//������յ�ƬԪ
		lastColor = ambient + diffuse + specular;
	}
	//�����ǰ���ھ۹�Ʒ�Χ��
	else
	{
		//ֻ���㻷�������
		vec4 ambient = vec4(light.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
		//�������ƬԪ
		lastColor = ambient;
	}
}