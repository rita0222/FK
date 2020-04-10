float FogValue()
{
	float d = distance(fk_CameraPosition, varP.xyz);
	return clamp((fk_FogParam.y - d)/(fk_FogParam.y - fk_FogParam.x), 0.0, 1.0);
}
