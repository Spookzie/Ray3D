#version 330 core


struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emissiveColor;

	sampler2D diffuseTex;
	sampler2D specularTex;
	
	float emissiveIntensity;
};


struct PointLight
{
	vec3 position;
	vec3 color;

	float intensity;
	float constant;
	float linear;
	float quadratic;
};


in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 cameraPos;


//	LIGHTING	//
//Attenuation
float CalculateAttenuation(PointLight light, vec3 vsPos)
{
	float dist = length(light.position - vsPos);

	return ( light.constant / (1.0 + light.linear * dist + light.quadratic * pow(dist,2)) );
}

//Ambient
vec3 CalculateAmbient(Material mat)
{
	return mat.ambient;
}

//Diffuse
vec3 CalculateDiffuse(Material mat, vec3 normal, vec3 lightDir)
{
	float diffuse = max(dot(normal, lightDir), 0.0);

    return (mat.diffuse * diffuse);
}

//Specular
vec3 CalculateSpecular(Material mat, vec3 normal, vec3 vsPos, vec3 lightDir, vec3 viewDir)
{
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec		= pow(max(dot(viewDir, reflectDir), 0.0), 48);		// You can change shininess (32, more popularly used) if needed
    
	return (mat.specular * spec * texture(mat.specularTex, vs_texcoord).rgb);
}

//Emissive
vec3 CalculateEmissive(Material mat)
{
	return (mat.emissiveColor * mat.emissiveIntensity);
}


void main()
{
	//	LIGHTING	//
	//Normalized directions
	vec3 normal	  = normalize(vs_normal);
    vec3 lightDir = normalize(pointLight.position - vs_position);
    vec3 viewDir  = normalize(cameraPos - vs_position);


	//Ambient, Diffuse, & Specular
	vec3 ambientFinal  = CalculateAmbient(material);
	vec3 diffuseFinal  = CalculateDiffuse(material, normal, lightDir);
	vec3 specularFinal = CalculateSpecular(material, normal, vs_position, lightDir, viewDir);


	//Emissive
	vec3 emissiveFinal = CalculateEmissive(material);


	//Attenuation
	float attenuation = CalculateAttenuation(pointLight, vs_position);
	vec3 finalColor = (ambientFinal + diffuseFinal + specularFinal) * attenuation + emissiveFinal;		//Applying attenuation to all final lighting values
	

	//Fetching diffuse texture color
	vec4 texColor = texture(material.diffuseTex, vs_texcoord);

	fs_color = texColor * vec4(finalColor, 1.0f);
}