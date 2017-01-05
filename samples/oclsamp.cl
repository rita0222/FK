// B に入っている3次元座標配列の大きさを A に格納するサンプル

float myDist(float3);
__kernel void fk_OpenCL(__global float *, __global float *);

float myDist(float3 v)
{
	return length(v);
}

__kernel void fk_OpenCL(__global float *A, __global float *B)
{
	unsigned int id = get_global_id(0);
	unsigned int id3 = id*3;
	float3	 v;

	v.x = B[id3];
	v.y = B[id3+1];
	v.z = B[id3+2];	

	A[id] = myDist(v);
}
