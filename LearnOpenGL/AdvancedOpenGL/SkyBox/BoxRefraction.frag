#version 450 core

//��������VS�Ķ�������
in vec3 fragPos;
//��������VS�Ķ��㷨����
in vec3 fragNormal;

//��պв�����
uniform samplerCube skyBoxSampler;
//�۲�λ��
uniform vec3 viewPos;

//�����ƬԪ��ɫ
out vec4 lastColor;

void main()
{
	//��������Ͳ����������ʱ�ֵ
	float ratio = 1.0 / 1.52;
	//����۲췽��
	vec3 viewDir = normalize(fragPos - viewPos);
	//���㻷��ӳ�䷴��ķ�������
	vec3 refractDir = refract(viewDir, fragNormal, ratio);
	//���ƬԪ
	lastColor = texture(skyBoxSampler, refractDir);
}