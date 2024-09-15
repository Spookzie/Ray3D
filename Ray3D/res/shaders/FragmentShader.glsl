#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};


in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

//	LIGHTING	//
//Ambient
vec3 CalculateAmbient(Material material)
{
	return material.ambient;
}

//Diffuse
vec3 CalculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos0)
{
	vec3 posToLightDirVec = normalize(light_pos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	
	return (material.diffuse * diffuse);
}

//Specular
vec3 CalculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos0, vec3 camera_pos)
{
	vec3 lightToPosDirVec = normalize(vs_position - light_pos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(camera_pos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
	
	return material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;
}


void main()
{
	//fs_color = vec4(vs_color, 1.0f);
	//fs_color = texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord);

	//	LIGHTING	//
	vec3 ambientFinal = CalculateAmbient(material);
	vec3 diffuseFinal = CalculateDiffuse(material, vs_position, vs_normal, lightPos0);
	vec3 specularFinal = CalculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);

	fs_color = texture(material.diffuseTex, vs_texcoord) *
		( vec4(ambientFinal, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f) );
}