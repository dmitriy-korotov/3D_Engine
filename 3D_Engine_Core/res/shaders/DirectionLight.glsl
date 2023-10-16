struct DirectionLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



vec3 calcDirectionLights(DirectionLight _light, vec3 _normal)
{
	vec3 ambient = _light.ambient * texture(inTexture, fTexCoord).rgb;
	
	float diff = max(dot(normalize(_light.direction), _normal), 0);
	vec3 diffuse = _light.diffuse * diff * texture(inTexture, fTexCoord).rgb;

	// need specular

	return ambient + diffuse;
}