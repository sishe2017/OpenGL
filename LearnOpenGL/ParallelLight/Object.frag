#version 450 core

//ƬԪλ��
in vec3 fragPosition;
//ƬԪ������
in vec3 fragNormal;
//�ƹ�λ��
in vec3 vLightDirection;

//�ƹ���ɫ
uniform vec3 lightColor;
//���������ɫ
uniform vec4 objectColor;

//���������ƬԪ��ɫ
out vec4 lastColor;

void main()
{
	//������ϵ��
	float KAmbient = 0.2f;
	//���㵱ǰƬԪ�Ļ��������
	vec4 ambient = vec4(lightColor, 1) * KAmbient;

	//������ϵ��
	float KDiffuse = 1;
	//�������������
	vec4 diffuse = vec4(lightColor, 1) * KDiffuse * max(dot(normalize(fragNormal), -vLightDirection), 0.0f);

	//���㵱ǰƬԪ���۲��ķ���
	vec3 viewDirection = normalize(-fragPosition);
	//���㷴���ķ���
	vec3 reflectDirection = reflect(vLightDirection, normalize(fragNormal));
	//���淴��ϵ��
	float KSpecular = 0.5f;
	//���㵱ǰƬԪ�ľ��淴�����
	vec4 specular = vec4(lightColor, 1) * KSpecular * pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);

	//�������ƬԪ
	lastColor = (ambient + diffuse) * objectColor + specular;
	//lastColor = vec4(fragNormal, 1);
}