struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic; 
};



vec3 calcPointLight(PointLight _light, vec3 _normal, vec3 fPosition, vec3 _color)
{
	vec3 direction = normalize(reflect(fPosition - _light.position, _normal));

    float distance = length(fPosition - _light.position);

    float attenuation = 1.0 / (_light.constant + _light.linear * distance + _light.quadratic * pow(distance, 2));
    
    

    vec3 ambient = attenuation * _light.ambient * _color;
	


	float diff = max(dot(direction, _normal), 0);
	vec3 diffuse = attenuation * diff *_light.diffuse * _color;



	// need specular

	return ambient + diffuse;
}