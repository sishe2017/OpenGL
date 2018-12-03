#version 450 core

//Ц�������������
uniform sampler2D smileFaceTexture;

//��ǰ����ĵ����������
in vec2 fragTexCoord;

//���������ƬԪ
out vec4 lastColor;

void main()
{
	//���ƬԪ
	vec4 fColor = texture(smileFaceTexture, fragTexCoord);
	//����ͼƬ͸���Ĳ���
	if (fColor.a < 0.1f)
	{
		discard;
	}
	lastColor = fColor;
}