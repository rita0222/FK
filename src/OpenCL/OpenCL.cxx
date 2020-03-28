#include <FK/OpenCL.h>
#include <FK/Error.H>

// FK以外で利用する場合、ここに printf 互換の適当な関数名を書く
#define ErrOut fk_Printf

using namespace std;
using namespace FK;

fk_OpenCL::fk_OpenCL(void)
{
	command_queue = nullptr;
	context = nullptr;
	kernel = nullptr;
	program = nullptr;
	initFlg = false;
	
	return;
}

fk_OpenCL::~fk_OpenCL()
{
	release();
	return;
}

bool fk_OpenCL::ReadKernel(string argFileName)
{
	ifstream					inputFile(argFileName);

	if(inputFile.fail()) {
		return false;
	}
	istreambuf_iterator<char>	vdataBegin(inputFile);
	istreambuf_iterator<char>	vdataEnd;
	kernelStr = string(vdataBegin, vdataEnd);
	inputFile.close();
	
	return true;
}

bool fk_OpenCL::deviceInit(string argFileName, string argKernelName, bool argDebugMode)
{
	cl_int				ciErrNum = 0;	// エラーチェック用変数
	cl_platform_id		testID = nullptr;
	cl_device_id		testdevid = nullptr;
	cl_uint				devicenum = 0;
	
	ciErrNum = GetPlatformID(&testID, argDebugMode);

	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in fkclGetPlatformID()");
		return false;
	}

/*
	ciErrNum = clGetDeviceIDs(testID, CL_DEVICE_TYPE_DEFAULT, 0, nullptr, &devicenum);
	ciErrNum = clGetDeviceIDs(testID, CL_DEVICE_TYPE_DEFAULT, devicenum, &testdevid, nullptr);
*/

	ciErrNum = clGetDeviceIDs(testID, CL_DEVICE_TYPE_ALL, 0, nullptr, &devicenum);
	ciErrNum = clGetDeviceIDs(testID, CL_DEVICE_TYPE_ALL, devicenum, &testdevid, nullptr);

	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in clGetDeviceIDs()");
		return false;
	}

	if(argDebugMode == true) PrintDevInfo(testdevid);
	context = clCreateContext(nullptr, devicenum, &testdevid, nullptr, nullptr, &ciErrNum);

	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in clCreateContext()");
		return false;
	}
	
	//-- command_queueの作成
#ifdef _MACOSX_
	command_queue = clCreateCommandQueue(context, testdevid, 0, nullptr);
#else
	command_queue = clCreateCommandQueueWithProperties(context, testdevid, 0, nullptr);
#endif
	
	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in clCreateCmmandQueue()");
		return false;
	}

	if(ReadKernel(argFileName) == false) {
		ErrOut("Kernel Read Error.");
		return false;
	}
	
	size_t kernelLength = kernelStr.size();
	const char *kernelSource = kernelStr.c_str();

	program = clCreateProgramWithSource(context, 1, &kernelSource,
										const_cast<size_t *>(&kernelLength), &ciErrNum);

	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in clCreateProgramWithSource()");
		return false;
	}
		
	if(clBuildProgram(program, devicenum, &testdevid, nullptr, nullptr, nullptr) != CL_SUCCESS) {
		ErrOut("Error in clBuildProgram()");
		char	*log;
		size_t	length;

		clGetProgramBuildInfo(program, testdevid, CL_PROGRAM_BUILD_LOG, 0, nullptr, &length);
		log = new char [length];
		clGetProgramBuildInfo(program, testdevid, CL_PROGRAM_BUILD_LOG, length, log, nullptr);
		ErrOut(log);
		delete [] log;
		
		return false;
	}

	//-- kernelの作成
	kernel = clCreateKernel(program, argKernelName.c_str(), &ciErrNum);

	if(ciErrNum != CL_SUCCESS) {
		ErrOut("Error in clCreateKernel()");
		return false;
	}

	if (ciErrNum != CL_SUCCESS) {
		ErrOut("Error in clSetKernelArg()");
		return false;
	}

	initFlg = true;
	return true;
}

void fk_OpenCL::createData(int argID, size_t argSize, bool argWriteFlg)
{	
	cl_int		ciErrNum = 0;
	size_t		id = size_t(argID);
	
	if(argID < 0) return;
	if(id >= devFlg.size()) {
		size_t curMax = devFlg.size();
		devData.resize(id+1);
		devFlg.resize(id+1);
		for(size_t i = curMax; i <= id; i++) devFlg[i] = false;
	}

	if(devFlg[id] == true) clReleaseMemObject(devData[id]);
	
	if(argWriteFlg == true) {
		devData[id] = clCreateBuffer(context, CL_MEM_READ_WRITE, argSize, nullptr, &ciErrNum);
	} else {
		devData[id] = clCreateBuffer(context, CL_MEM_READ_ONLY, argSize, nullptr, &ciErrNum);
	}
	if(ciErrNum != CL_SUCCESS) PrintError(ciErrNum);
	devFlg[id] = true;
}

bool fk_OpenCL::sendData(int argID, size_t argSize, const void *argPtr)
{
	size_t id = size_t(argID);

	if(argID < 0) return false;
	if(id >= devFlg.size()) return false;
	if(devFlg[id] == false) return false;

	cl_int ciErrNum = clEnqueueWriteBuffer(command_queue, devData[id], CL_TRUE,
										   0, argSize, argPtr, 0, nullptr, nullptr);

	if (ciErrNum != CL_SUCCESS) {
		ErrOut("Error in clEnqueueWriteBuffer()");
		PrintError(ciErrNum);
		return false;
	}

	return true;
}
	
bool fk_OpenCL::getData(int argID, size_t argSize, void *argPtr)
{
	size_t id = size_t(argID);

	if(argID < 0) return false;
	if(id >= devFlg.size()) return false;
	if(devFlg[id] == false) return false;

	cl_int ciErrNum = clEnqueueReadBuffer(command_queue, devData[id], CL_TRUE,
										  0, argSize, argPtr, 0, nullptr, nullptr);
	
	if (ciErrNum != CL_SUCCESS) {
		ErrOut("Error in setReadBuffer");
		PrintError(ciErrNum);
		return false;
	}
	return true;
}

bool fk_OpenCL::run(size_t argSize)
{
	cl_int ciErrNum;
	
	for(size_t i = 0; i < devFlg.size(); i++) {
		if(devFlg[i] == true) {
			ciErrNum = clSetKernelArg(kernel, cl_uint(i), sizeof(cl_mem), &devData[i]);
			if (ciErrNum != CL_SUCCESS) {
				ErrOut("Error in SetKernel");
				PrintError(ciErrNum);
				return false;
			}
		}
	}

	ciErrNum = clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr,
									  &argSize, nullptr, 0, nullptr, nullptr);

	if (ciErrNum != CL_SUCCESS) {
		ErrOut("Error in RUN");
		PrintError(ciErrNum);
		return false;
	}
	return true;
}	


void fk_OpenCL::release(void)
{
	if(initFlg == true) {
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(command_queue);
		clReleaseContext(context);
		for(size_t i = 0; i < devFlg.size(); i++) {
			if(devFlg[i] == true) clReleaseMemObject(devData[i]);
		}
		initFlg = false;
	}
	return;
}

cl_int fk_OpenCL::GetPlatformID(cl_platform_id *argID, bool argInfoMode)
{
	const cl_uint	chBufsize = 1024;		// 取得する文字情報の書き込み用バッファサイズ
	char 			chBuffer[chBufsize];	// 取得する文字情報の書き込み用バッファ
	cl_uint			num_platforms;			// 取得したプラットフォームの数を書き込むunsigned int
	cl_platform_id	*clPlatformIDs;			// プラットフォームの数が不定なので、最初はアドレスのみ
	cl_int			ciErrNum;				// OpenCL関数実行時のエラーチェック用int
	
	fk_SetErrorMode(fk_ErrorMode::BROWSER_INTERACTIVE);

	*argID = nullptr;
 
	//-- OpenCLのプラットフォーム数取得
	//-- プラットフォームの数だけを取得。num_platformsに数が入る
	ciErrNum = clGetPlatformIDs(0, nullptr, &num_platforms);
	
	//-- clGetGPlatformIDs()が失敗した場合
	if(ciErrNum != CL_SUCCESS){
		ErrOut("Error in clGetPlatformID()");
		return -10;
		
	}else{
		//-- clGetPlatformIDs()は成功したが、platformの数が0の場合
		if (num_platforms == 0) {
			ErrOut("I can't find OpenCL Platform! Get away");
			return -20;
		//-- platformの数が1以上の場合

		}else if(argInfoMode == true) {

			clPlatformIDs = new cl_platform_id[num_platforms];
			//-- メモリ足りなきゃエラーです
			if(clPlatformIDs == nullptr){
				ErrOut("I failed to allocate memory for cl_platformID's. Give me a memory");
				return -30;
			}
 
			//-- 以上のエラーチェックを通過したら、以下のメイン処理へ
			//-- platformの数を表示
			ErrOut("number of platform(s) : %d", num_platforms);
 
			//-- platformIDの取得
			//-- 既に数は取得しているので、最後の引数はnullptr
			ciErrNum = clGetPlatformIDs(num_platforms, clPlatformIDs, nullptr);
 
			//-- 取得したplatformIDから、様々なID情報を取得し、表示
			for (cl_uint i = 0; i < num_platforms; ++i) {
				//-- (情報取得する対象のID, 取得したい情報の種類, 
				//-- 取得したデータを格納するバッファのデータサイズ, 
				//-- 取得したデータを格納するバッファへのポインタ, 取得した情報のデータの大きさ)
				//-- 取得したい情報の種類：プロファイル
			
				ciErrNum = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_PROFILE,
											 chBufsize, &chBuffer, nullptr);
				/*
				if(ciErrNum == CL_SUCCESS){
					ErrOut("PLATFORM_PROLILE : %s", chBuffer);
				}
				*/
				//-- 取得したい情報の種類：バージョン
				ciErrNum = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_VERSION,
											 chBufsize, &chBuffer, nullptr);
				if(ciErrNum == CL_SUCCESS){
					ErrOut("PLATFORM_VERSOIN : %s", chBuffer);
				}
				//-- 取得したい情報の種類：名前
				ciErrNum = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_NAME,
											 chBufsize, &chBuffer, nullptr);
				if (ciErrNum == CL_SUCCESS) {
					ErrOut("PLATFORM_NAME : %s", chBuffer);
				}
				//-- 取得したい情報の種類：VENDER
				ciErrNum = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_VENDOR,
											 chBufsize, &chBuffer, nullptr);
				if(ciErrNum == CL_SUCCESS){
					ErrOut("PLATFORM_VENDOR : %s", chBuffer);
				}
				//-- 取得したい情報の種類：機能拡張
				ciErrNum = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_EXTENSIONS,
											 chBufsize, &chBuffer, nullptr);
				if(ciErrNum == CL_SUCCESS){
					ErrOut("PLATFORM_EXTENSIONS : %s", chBuffer);
				}
 
				//-- 引数として受け取ったIDに、この関数内で取得したID情報を渡す
				*argID = clPlatformIDs[i];
 
 
			}
			delete [] clPlatformIDs;
		}
 
	}
 
	return CL_SUCCESS;
}

void fk_OpenCL::PrintDevInfo(cl_device_id argDev)
{
	string		zu, tmpStr;

#ifdef _MACOSX_
	zu = "%zu";
#else
	zu = "%d";
#endif

	ErrOut("-----DEVICE_INFO--------");
	const cl_uint chBufsize = 1024;
	char device_string[chBufsize];
	cl_int		ciErrNum;
 
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_NAME, chBufsize, &device_string, nullptr);
	if(ciErrNum == CL_SUCCESS) ErrOut("DEVICE_NAME : %s", device_string);
	else ErrOut("Error in CL_DEVICE_NAME");
 
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_VENDOR,
							   sizeof(device_string), &device_string, nullptr);

	if(ciErrNum == CL_SUCCESS) ErrOut("DEVICE_VENDER : %s", device_string);
	else ErrOut("Error in CL_DEVICE_VENDER");
 

	ciErrNum = clGetDeviceInfo(argDev, CL_DRIVER_VERSION,
							   sizeof(device_string), &device_string, nullptr);

	if(ciErrNum == CL_SUCCESS) ErrOut("DRIVER_VERSION : %s", device_string);
	else ErrOut("Error in CL_DRIVER_VERSION");
 

	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_VERSION,
							   sizeof(device_string), &device_string, nullptr);
	if(ciErrNum == CL_SUCCESS) ErrOut("DEVICE_VERSION : %s", device_string);
	else ErrOut("Error in CL_DEVICE_VERSION");
 
	cl_device_type type;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_TYPE, sizeof(type), &type, nullptr);
	if(ciErrNum == CL_SUCCESS){
		if( type & CL_DEVICE_TYPE_CPU ){
			ErrOut("CL_DEVICE_TYPE_CPU");
		}else if (type & CL_DEVICE_TYPE_GPU) {
			ErrOut("CL_DEVICE_TYPE_GPU");
		}else if (type & CL_DEVICE_TYPE_ACCELERATOR) {
			ErrOut("CL_DEVICE_TYPE_ACCELERATOR");
		}else if (type & CL_DEVICE_TYPE_DEFAULT) {
			ErrOut("CL_DEVICE_TYPE_DEFAULT");
		}
	}
 
	cl_uint compute_units;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_COMPUTE_UNITS,
							   sizeof(compute_units),&compute_units,nullptr);
	if(ciErrNum == CL_SUCCESS) ErrOut("CL_DEVICE_MAX_COMPUTE_UNITS : %u", compute_units);
	else ErrOut("Error in CL_DEVICE_MAX_COMPUTE_UNITS");
 
	cl_uint workitem_dims;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
							   sizeof(cl_uint), &workitem_dims, nullptr);
	if(ciErrNum == CL_SUCCESS) ErrOut("CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS : %u", workitem_dims);
	else ErrOut("Error in CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS");
 
	size_t workitem_size[3];	
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_WORK_ITEM_SIZES,
							   sizeof(workitem_size), &workitem_size, nullptr);
	if(ciErrNum == CL_SUCCESS) {
		tmpStr = "CL_DEVICE_MAX_WORK_ITEM_SIZE : " + zu + ", " + zu + ", " + zu;
		ErrOut(tmpStr.c_str(),
			   workitem_size[0], workitem_size[1], workitem_size[2]);
	} else {
		ErrOut("Error in CL_DEVICE_MAX_WORK_ITEM_SIZE");
	}
 
	size_t workgroup_size;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_WORK_GROUP_SIZE,
							   sizeof(workgroup_size), &workgroup_size, nullptr);
	if(ciErrNum == CL_SUCCESS) {
		tmpStr = "CL_DEVICE_MAX_WORK_GROUP_SIZE : " + zu;
		ErrOut(tmpStr.c_str(), workgroup_size);
	} else {
		ErrOut("Error in CL_DEVICE_MAX_WORK_GROUP_SIZE");
	}
 
	cl_uint addr_bits;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_ADDRESS_BITS,
							   sizeof(addr_bits), &addr_bits, nullptr);
	if(ciErrNum == CL_SUCCESS) ErrOut("CL_DEVICE_ADDRESS_BITS : %u", addr_bits);
	else ErrOut("Error in CL_DEVICE_ADDRESS_BITS");
 
	cl_ulong max_mem_alloc_size;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_MEM_ALLOC_SIZE,
							   sizeof(max_mem_alloc_size), &max_mem_alloc_size, nullptr);
	if (ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_MAX_MEM_ALLOC_SIZE : %u MByte",
				  (unsigned int)(max_mem_alloc_size / (1024 * 1024)));
	}
	else {
		ErrOut("Error in CL_DEVICE_MAX_MEM_ALLOC_SIZE");
	}
 
	cl_ulong mem_size;
	ciErrNum =  clGetDeviceInfo(argDev, CL_DEVICE_GLOBAL_MEM_SIZE,
								sizeof(mem_size), &mem_size, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_GLOBAL_MEM_SIZE : %u MByte",
				  (unsigned int)(mem_size / (1024 * 1024)));
	}
	else {
		ErrOut("Error in CL_DEVICE_GLOBAL_MEM_SIZE");
	}
 
	cl_bool error_correction_support;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_ERROR_CORRECTION_SUPPORT,
							   sizeof(error_correction_support), &error_correction_support, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_ERROR_CORRECTION_SUPPORT : %s",
				  error_correction_support == CL_TRUE ? "yes" : "no");
	} else {
		ErrOut("Error in CL_DEVICE_ERROR_CORRECTION_SUPPORT");
	}
 
	cl_device_local_mem_type local_mem_type;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_LOCAL_MEM_TYPE,
							   sizeof(local_mem_type), &local_mem_type, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_LOCAL_MEM_TYPE : %s", local_mem_type == 1 ? "local" : "global");
	} else {
		ErrOut("Error in CL_DEVICE_LOCAL_MEM_TYPE");
	}
 
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_LOCAL_MEM_SIZE,
							   sizeof(mem_size), &mem_size, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_LOCAL_MEM_SIZE : %u KByte", (unsigned int)(mem_size / 1024));
	} else {
		ErrOut("Error in CL_DEVICE_LOCAL_MEM_SIZE");
	}
 
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
							   sizeof(mem_size), &mem_size, nullptr);
	
	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE : %u KByte",
				  (unsigned int)(mem_size / 1024));
	} else {
		ErrOut("Error in CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE");
	}
 
	cl_command_queue_properties queue_properties;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_QUEUE_PROPERTIES,
							   sizeof(queue_properties), &queue_properties, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		if(queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) {
			ErrOut("CL_DEVICE_QUEUE_PROPERTIES : CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
		}
		if(queue_properties & CL_QUEUE_PROFILING_ENABLE) {
			ErrOut("CL_QUEUE_PROFILING_ENABLE : CL_QUEUE_PROFILING_ENABLE");
		}
	} else {
		ErrOut("Error in CL_DEVICE_QUEUE_PROPERTIES");
	}
 
    cl_bool image_support;
	ciErrNum =  clGetDeviceInfo(argDev, CL_DEVICE_IMAGE_SUPPORT,
								sizeof(image_support), &image_support, nullptr);
	
	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_IMAGE_SUPPORT : %s", image_support == 1 ? "TRUE" : "FALSE");
	} else {
		ErrOut("Error in CL_DEVICE_IMAGE_SUPPORT");
	}
 
    cl_uint max_read_image_args;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_READ_IMAGE_ARGS,
							   sizeof(max_read_image_args), &max_read_image_args, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_MAX_READ_IMAGE_ARGS : %u", max_read_image_args);
	} else {
		ErrOut("Error in CL_DEVICE_MAX_READ_IMAGE_ARGS");
	}

    cl_uint max_write_image_args;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
							   sizeof(max_write_image_args), &max_write_image_args, nullptr);
	
	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_MAX_WRITE_IMAGE_ARGS : %u", max_write_image_args);
	} else {
		ErrOut("Error in CL_DEVICE_MAX_WRITE_IMAGE_ARGS");
	}
	
    cl_device_fp_config fp_config;
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_SINGLE_FP_CONFIG,
							   sizeof(cl_device_fp_config), &fp_config, nullptr);

	if(ciErrNum == CL_SUCCESS) {
		ErrOut("CL_DEVICE_SINGLE_FP_CONFIG : %s%s%s%s%s%s", 
				  fp_config & CL_FP_DENORM ? "denorms " : "",
				  fp_config & CL_FP_INF_NAN ? "INF-quietNaNs " : "",
				  fp_config & CL_FP_ROUND_TO_NEAREST ? "round-to-nearest " : "",
				  fp_config & CL_FP_ROUND_TO_ZERO ? "round-to-zero " : "",
				  fp_config & CL_FP_ROUND_TO_INF ? "round-to-inf " : "",
				  fp_config & CL_FP_FMA ? "fma " : "");
	} else {
		ErrOut("Error in CL_DEVICE_SINGLE_FP_CONFIG");
	}
	
    size_t szMaxDims[5];
	
	ErrOut("CL_DEVICE_IMAGE <dim>");
	
	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_IMAGE2D_MAX_WIDTH,
							   sizeof(size_t), &szMaxDims[0], nullptr);
	tmpStr = "2D_MAX_WIDTH " + zu;
	ErrOut(tmpStr.c_str(), szMaxDims[0]);

	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
							   sizeof(size_t), &szMaxDims[1], nullptr);
	tmpStr = "2D_MAX_HEIGHT " + zu;
	ErrOut(tmpStr.c_str(), szMaxDims[1]);

	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_IMAGE3D_MAX_WIDTH,
							   sizeof(size_t), &szMaxDims[2], nullptr);
	tmpStr = "3D_MAX_WIDHT " + zu;
	ErrOut(tmpStr.c_str(), szMaxDims[2]);

	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_IMAGE3D_MAX_HEIGHT,
							   sizeof(size_t), &szMaxDims[3], nullptr);
	tmpStr = "3D_MAX_HEIGHT " + zu;

	ErrOut(tmpStr.c_str(), szMaxDims[3]);

	ciErrNum = clGetDeviceInfo(argDev, CL_DEVICE_IMAGE3D_MAX_DEPTH,
							   sizeof(size_t), &szMaxDims[4], nullptr);
	tmpStr = "3D_MAX_DEPTH " + zu;
	ErrOut(tmpStr.c_str(), szMaxDims[4]);
 

	//-- CL_DEVICE_PREFERRED_VECTOR_WIDTH_<type>
	ErrOut("CL_DEVICE_PREFERRED_VECTOR_WIDTH_<t>\t");
	cl_uint vec_width [6];
	clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
					sizeof(cl_uint), &vec_width[0], nullptr);
    clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
					sizeof(cl_uint), &vec_width[1], nullptr);
    clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
					sizeof(cl_uint), &vec_width[2], nullptr);
    clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
					sizeof(cl_uint), &vec_width[3], nullptr);
    clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
					sizeof(cl_uint), &vec_width[4], nullptr);
    clGetDeviceInfo(argDev, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
					sizeof(cl_uint), &vec_width[5], nullptr);
	ErrOut("CHAR %u, SHORT %u, INT %u, LONG %u, FLOAT %u, DOUBLE %u",
			  vec_width[0], vec_width[1], vec_width[2],
			  vec_width[3], vec_width[4], vec_width[5]);

	return;
}

void fk_OpenCL::PrintError(cl_int argErrNum)
{
	switch (argErrNum) {
		case CL_DEVICE_NOT_FOUND: // -1
			ErrOut("CL_DEVICE_NOT_FOUND");
			break;
		case CL_DEVICE_NOT_AVAILABLE: // -2
			ErrOut("CL_DEVICE_NOT_AVAILABLE");
			break;
		case CL_COMPILER_NOT_AVAILABLE: // -3
			ErrOut("CL_COMPILER_NOT_AVAILABLE");
			break;
		case CL_MEM_OBJECT_ALLOCATION_FAILURE: // -4
			ErrOut("CL_MEM_OBJECT_ALLOCATION_FAILURE");
			break;
		case CL_OUT_OF_RESOURCES: // -5
			ErrOut("CL_OUT_OF_RESOURCES");
			break;
		case CL_OUT_OF_HOST_MEMORY: // -6
			ErrOut("CL_OUT_OF_HOST_MEMORY");
			break;
		case CL_PROFILING_INFO_NOT_AVAILABLE: // -7
			ErrOut("CL_PROFILING_INFO_NOT_AVAILABLE");
			break;
		case CL_MEM_COPY_OVERLAP: // -8
			ErrOut("CL_MEM_COPY_OVERLAP");
			break;
		case CL_IMAGE_FORMAT_MISMATCH: // -9
			ErrOut("CL_IMAGE_FORMAT_MISMATCH");
			break;
		case CL_IMAGE_FORMAT_NOT_SUPPORTED: // -10
			ErrOut("CL_IMAGE_FORMAT_NOT_SUPPORTED");
			break;
		case CL_BUILD_PROGRAM_FAILURE: // -11
			ErrOut("CL_BUILD_PROGRAM_FAILURE");
			break;
		case CL_MAP_FAILURE: // -12
			ErrOut("CL_MAP_FAILURE");
			break;
		
		case CL_INVALID_VALUE: // -30
			ErrOut("CL_INVALID_VALUE");
			break;
		case CL_INVALID_DEVICE_TYPE: // -31
			ErrOut("CL_INVALID_DEVICE_TYPE");
			break;
		case CL_INVALID_PLATFORM: // -32
			ErrOut("CL_INVALID_PLATFORM");
			break;
		case CL_INVALID_DEVICE: // -33
			ErrOut("CL_INVALID_DEVICE");
			break;
		case CL_INVALID_CONTEXT: // -34
			ErrOut("CL_INVALID_CONTEXT");
			break;
		case CL_INVALID_QUEUE_PROPERTIES: // -35
			ErrOut("CL_INVALID_QUEUE_PROPERTIES");
			break;
		case CL_INVALID_COMMAND_QUEUE: // -36
			ErrOut("CL_INVALID_COMMAND_QUEUE");
			break;
		case CL_INVALID_HOST_PTR: // -37
			ErrOut("CL_INVALID_HOST_PTR");
			break;
		case CL_INVALID_MEM_OBJECT: // -38
			ErrOut("CL_INVALID_MEM_OBJECT");
			break;
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: // -39
			ErrOut("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
			break;
		case CL_INVALID_IMAGE_SIZE: // -40
			ErrOut("CL_INVALID_IMAGE_SIZE");
			break;
		case CL_INVALID_SAMPLER: // -41
			ErrOut("CL_INVALID_SAMPLER");
			break;
		case CL_INVALID_BINARY: // -42
			ErrOut("CL_INVALID_BINARY");
			break;
		case CL_INVALID_BUILD_OPTIONS: // -43
			ErrOut("CL_INVALID_BUILD_OPTIONS");
			break;
		case CL_INVALID_PROGRAM: //- 44
			ErrOut("CL_INVALID_PROGRAM");
			break;
		case CL_INVALID_PROGRAM_EXECUTABLE: // -45
			ErrOut("CL_INVALID_PROGRAM_EXECUTABLE");
			break;
		case CL_INVALID_KERNEL_NAME: // -46
			ErrOut("CL_INVALID_KERNEL_NAME");
			break;
		case CL_INVALID_KERNEL_DEFINITION: // -47
			ErrOut("CL_INVALID_KERNEL_DEFINITION");
			break;
		case CL_INVALID_KERNEL: // -48
			ErrOut("CL_INVALID_KERNEL");
			break;
		case CL_INVALID_ARG_INDEX: // -49
			ErrOut("CL_INVALID_ARG_INDEX");
			break;
		case CL_INVALID_ARG_VALUE: // -50
			ErrOut("CL_INVALID_ARG_VALUE");
			break;
		case CL_INVALID_ARG_SIZE: // -51
			ErrOut("CL_INVALID_ARG_SIZE");
			break;
		case CL_INVALID_KERNEL_ARGS: // -52
			ErrOut("CL_INVALID_KERNEL_ARGS");
			break;
		case CL_INVALID_WORK_DIMENSION: // -53
			ErrOut("CL_INVALID_WORK_DIMENSION");
			break;
		case CL_INVALID_WORK_GROUP_SIZE: // -54
			ErrOut("CL_INVALID_WORK_GROUP_SIZE");
			break;
		case CL_INVALID_WORK_ITEM_SIZE: // -55
			ErrOut("CL_INVALID_WORK_ITEM_SIZE");
			break;
		case CL_INVALID_GLOBAL_OFFSET: // -56
			ErrOut("CL_INVALID_GLOBAL_OFFSET");
			break;
		case CL_INVALID_EVENT_WAIT_LIST: // -57
			ErrOut("CL_INVALID_EVENT_WAIT_LIST");
			break;
		case CL_INVALID_EVENT: // -58
			ErrOut("CL_INVALID_EVENT");
			break;
		case CL_INVALID_OPERATION: // -59
			ErrOut("CL_INVALID_OPERATION");
			break;
		case CL_INVALID_GL_OBJECT: // -60
			ErrOut("CL_INVALID_GL_OBJECT");
			break;
		case CL_INVALID_BUFFER_SIZE: // -61
			ErrOut("CL_INVALID_BUFFER_SIZE");
			break;
		case CL_INVALID_MIP_LEVEL: // -62
			ErrOut("CL_INVALID_MIP_LEVEL");
			break;
		case CL_INVALID_GLOBAL_WORK_SIZE: // -63
			ErrOut("CL_INVALID_GLOBAL_WORK_SIZE");
			break;

		case CL_SUCCESS: // 0
			ErrOut("CL_SUCCESS");
			break;

		default:
			ErrOut("Unknown error code : %d", argErrNum);
			break;
	}
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
