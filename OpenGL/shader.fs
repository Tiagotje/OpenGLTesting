#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture0;
uniform vec3 lightcolor;
uniform vec3 objectcolor;
uniform bool textured;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = vec3(0.0f, 1.0f, 0.0f);
	float diff = max(dot(norm, lightDir), 0.0);
	float side = 1 - abs(dot(norm, vec3(0.0f, -1.0f, 0.0f)));
	vec3 diffuse = (0.6 * diff+0.6*side) * lightcolor;
	vec3 ambient =  0.3 * lightcolor;

	vec4 tex;
	if(textured)
		tex = texture(texture0, TexCoord);
	else 
		tex = vec4(objectcolor, 1.0f);
	
	FragColor = vec4(ambient + diffuse, 1.0f) * tex;
}