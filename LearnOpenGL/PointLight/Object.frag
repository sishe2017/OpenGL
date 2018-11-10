#version 450 core

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
//˥��ģ�Ͷ���������
uniform float expFactor;
//˥��ģ��һ��������
uniform float linearFactor;
//˥��ģ�ͳ���������
uniform float constantFactor;

//���������ƬԪ��ɫ
out vec4 lastColor;

void main()
{
	//������ϵ��
	float KAmbient = 0.2f;
	//���㵱ǰƬԪ�Ļ��������
	vec4 ambient = vec4(lightColor, 1) * KAmbient;


	//���㵱ǰ�㵽��Դ�ľ���
	float pointDistance = length(vLightPosition - fragPosition);
	//����˥�����
	float attenuation = 1.0f / (expFactor * pointDistance * pointDistance + linearFactor * pointDistance + constantFactor);
	
	//����������߷���
	vec3 lightDirection = normalize(vLightPosition - fragPosition);
	//������ϵ��
	float KDiffuse = 1;
	//�������������
	vec4 diffuse = vec4(lightColor, 1) * KDiffuse * max(dot(normalize(fragNormal),lightDirection), 0.0f) * attenuation;

	//���㵱ǰƬԪ���۲��ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴���ķ���
	vec3 reflectDirection = reflect(-lightDirection, normalize(fragNormal));
	//���淴��ϵ��
	float KSpecular = 0.5f;
	//���㵱ǰƬԪ�ľ��淴�����
	vec4 specular = vec4(lightColor, 1) * KSpecular * pow(max(dot(viewDirection, reflectDirection), 0.0f), 32) * attenuation;

	//�������ƬԪ
	lastColor = (ambient + diffuse) * objectColor + specular;
}