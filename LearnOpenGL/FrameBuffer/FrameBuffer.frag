#version 450 core

//֡��������������
uniform sampler2D frameTexture;

//��ǰ����ĵ����������
in vec2 fragTexCoord;

//���������ƬԪ
out vec4 lastColor;

//ƫ��
const float offset = 1.0f / 300.0f;

void main()
{
//	//ԭЧ��
//	lastColor = texture(frameTexture, fragTexCoord);

//	//����Ч��
//	lastColor = vec4(vec3(1 - texture(frameTexture, fragTexCoord).rgb), 1);

//	//�Ҷ�Ч��
//	//�Ȼ�ȡ������ɫ
//	vec4 textureColor = texture(frameTexture, fragTexCoord);
//	//����������ɫ������ƽ��ֵ
//	float average = (textureColor.r + textureColor.g + textureColor.b) / 3.0f;
//	//����Ҷ�Ч��
//	lastColor = vec4(average, average, average, 1);

//	//��Ч��
//	//ƫ��������
//	vec2 offsets[9] =  vec2[](
//        vec2(-offset,  offset), // ����
//        vec2( 0.0f,    offset), // ����
//        vec2( offset,  offset), // ����
//        vec2(-offset,  0.0f),   // ��
//        vec2( 0.0f,    0.0f),   // ��
//        vec2( offset,  0.0f),   // ��
//        vec2(-offset, -offset), // ����
//        vec2( 0.0f,   -offset), // ����
//        vec2( offset, -offset)  // ����
//    );
//	//��
//	float kernel[9] = float[](
//        -1, -1, -1,
//        -1,  9, -1,
//        -1, -1, -1
//    );
//	//�����Ч���������
//	vec3 samplerResult[9];
//	for (int i = 0; i < 9; i++)
//	{
//		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
//	}
//	//�ۼӼ�Ȩ����ֵ
//	vec3 result = vec3(0);
//	for (int i = 0; i < 9; i++)
//	{
//		result += samplerResult[i] * kernel[i];
//	}
//	//�������ƬԪ
//	lastColor = vec4(result, 1);

//	//ģ��Ч��
//	//ƫ��������
//	vec2 offsets[9] =  vec2[](
//        vec2(-offset,  offset), // ����
//        vec2( 0.0f,    offset), // ����
//        vec2( offset,  offset), // ����
//        vec2(-offset,  0.0f),   // ��
//        vec2( 0.0f,    0.0f),   // ��
//        vec2( offset,  0.0f),   // ��
//        vec2(-offset, -offset), // ����
//        vec2( 0.0f,   -offset), // ����
//        vec2( offset, -offset)  // ����
//    );
//	//��
//	float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//	);
//	//�����Ч���������
//	vec3 samplerResult[9];
//	for (int i = 0; i < 9; i++)
//	{
//		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
//	}
//	//�ۼӼ�Ȩ����ֵ
//	vec3 result = vec3(0);
//	for (int i = 0; i < 9; i++)
//	{
//		result += samplerResult[i] * kernel[i];
//	}
//	//�������ƬԪ
//	lastColor = vec4(result, 1);

	//��Ե���Ч��Ч��
	//ƫ��������
	vec2 offsets[9] =  vec2[](
        vec2(-offset,  offset), // ����
        vec2( 0.0f,    offset), // ����
        vec2( offset,  offset), // ����
        vec2(-offset,  0.0f),   // ��
        vec2( 0.0f,    0.0f),   // ��
        vec2( offset,  0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2( 0.0f,   -offset), // ����
        vec2( offset, -offset)  // ����
    );
	//��
	float kernel[9] = float[](
    1, 1, 1,
    1, -8, 1,
    1, 1, 1  
	);
	//�����Ч���������
	vec3 samplerResult[9];
	for (int i = 0; i < 9; i++)
	{
		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
	}
	//�ۼӼ�Ȩ����ֵ
	vec3 result = vec3(0);
	for (int i = 0; i < 9; i++)
	{
		result += samplerResult[i] * kernel[i];
	}
	//�������ƬԪ
	lastColor = vec4(result, 1);
}