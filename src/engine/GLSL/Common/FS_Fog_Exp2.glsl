float FogValue()
{
	float d = distance(fk_CameraPosition, varP.xyz) * fk_FogParam.z;
	return exp(-d*d);
}
