struct DirectionLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



vec3 calcDirectionLight(DirectionLight _light, vec3 _normal, vec3 _color)
{
	vec3 ambient = _light.ambient * _color;
	
	float diff = max(dot(_light.direction, _normal), 0);
	vec3 diffuse = _light.diffuse * diff * _color;

	// need specular

	return ambient + diffuse;
}