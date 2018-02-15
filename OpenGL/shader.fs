#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture0;
uniform vec3 lightcolor;
uniform vec3 lightPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightcolor;
	FragColor = vec4(0.4 * lightcolor + diffuse, 1.0) * texture(texture0, TexCoord);
}