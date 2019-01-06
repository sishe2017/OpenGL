#version 450 core

//帧缓存的纹理采样器
uniform sampler2D frameTexture;

//当前计算的点的纹理坐标
in vec2 fragTexCoord;

//输出的最终片元
out vec4 lastColor;

//偏移
const float offset = 1.0f / 300.0f;

void main()
{
//	//原效果
//	lastColor = texture(frameTexture, fragTexCoord);

//	//反相效果
//	lastColor = vec4(vec3(1 - texture(frameTexture, fragTexCoord).rgb), 1);

//	//灰度效果
//	//先获取纹理颜色
//	vec4 textureColor = texture(frameTexture, fragTexCoord);
//	//计算三个颜色分量的平均值
//	float average = (textureColor.r + textureColor.g + textureColor.b) / 3.0f;
//	//输出灰度效果
//	lastColor = vec4(average, average, average, 1);

//	//核效果
//	//偏移量数组
//	vec2 offsets[9] =  vec2[](
//        vec2(-offset,  offset), // 左上
//        vec2( 0.0f,    offset), // 正上
//        vec2( offset,  offset), // 右上
//        vec2(-offset,  0.0f),   // 左
//        vec2( 0.0f,    0.0f),   // 中
//        vec2( offset,  0.0f),   // 右
//        vec2(-offset, -offset), // 左下
//        vec2( 0.0f,   -offset), // 正下
//        vec2( offset, -offset)  // 右下
//    );
//	//核
//	float kernel[9] = float[](
//        -1, -1, -1,
//        -1,  9, -1,
//        -1, -1, -1
//    );
//	//计算核效果采样结果
//	vec3 samplerResult[9];
//	for (int i = 0; i < 9; i++)
//	{
//		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
//	}
//	//累加加权纹理值
//	vec3 result = vec3(0);
//	for (int i = 0; i < 9; i++)
//	{
//		result += samplerResult[i] * kernel[i];
//	}
//	//输出最终片元
//	lastColor = vec4(result, 1);

//	//模糊效果
//	//偏移量数组
//	vec2 offsets[9] =  vec2[](
//        vec2(-offset,  offset), // 左上
//        vec2( 0.0f,    offset), // 正上
//        vec2( offset,  offset), // 右上
//        vec2(-offset,  0.0f),   // 左
//        vec2( 0.0f,    0.0f),   // 中
//        vec2( offset,  0.0f),   // 右
//        vec2(-offset, -offset), // 左下
//        vec2( 0.0f,   -offset), // 正下
//        vec2( offset, -offset)  // 右下
//    );
//	//核
//	float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//	);
//	//计算核效果采样结果
//	vec3 samplerResult[9];
//	for (int i = 0; i < 9; i++)
//	{
//		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
//	}
//	//累加加权纹理值
//	vec3 result = vec3(0);
//	for (int i = 0; i < 9; i++)
//	{
//		result += samplerResult[i] * kernel[i];
//	}
//	//输出最终片元
//	lastColor = vec4(result, 1);

	//边缘检测效果效果
	//偏移量数组
	vec2 offsets[9] =  vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
	//核
	float kernel[9] = float[](
    1, 1, 1,
    1, -8, 1,
    1, 1, 1  
	);
	//计算核效果采样结果
	vec3 samplerResult[9];
	for (int i = 0; i < 9; i++)
	{
		samplerResult[i] = vec3(texture(frameTexture, fragTexCoord.st + offsets[i]));
	}
	//累加加权纹理值
	vec3 result = vec3(0);
	for (int i = 0; i < 9; i++)
	{
		result += samplerResult[i] * kernel[i];
	}
	//输出最终片元
	lastColor = vec4(result, 1);
}