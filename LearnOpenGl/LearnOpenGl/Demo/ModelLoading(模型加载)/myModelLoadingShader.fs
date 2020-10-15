#version 330 core
out vec4 FragColor;
out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
//    FragColor = texture(texture_diffuse1, TexCoords);
    

    //最终片段颜色：环境颜色+漫反射颜色+镜面反射颜色
    vec3 result =  vec3(1.0f,1.0f,1.0f) * vec3(texture(texture_diffuse1, TexCoords));
    color = vec4(result , 1.0f);

    
    
}
