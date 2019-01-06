#version 450 core

//ľ�������
uniform sampler2D woodenBoxSampler;
//Ц��������
uniform sampler2D smileFaceSampler;
//���ն�����ɫ����ľ����������
in vec2 vWoodenBoxTexCoord;
//���ն�����ɫ����Ц����������
in vec2 vSmileFaceTexCoord;
//�����ƬԪ��ɫ
out vec4 fColor;

void main()
{
	//�������
	fColor = mix(texture(woodenBoxSampler, vWoodenBoxTexCoord), texture(smileFaceSampler, vSmileFaceTexCoord),0.2);
//	fColor = texture(woodenBoxSampler, vWoodenBoxTexCoord) + texture(smileFaceSampler, vSmileFaceTexCoord);
}