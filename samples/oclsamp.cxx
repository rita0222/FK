#include <FK/FK.h>
#include <FK/OpenCL.h>


using namespace std;
using namespace FK;

int main(int, char **)
{
	const size_t	SIZE = 100000;
	fk_OpenCL		opencl;
	vector<float>	a(SIZE), b(SIZE*3);
	size_t			i;
	
	//fk_System::setcwd();

	// 初期化。カーネルファイル名とカーネル関数名。
	// デバッグモードにしたければ第3引数にtrueを追加。

	fk_SetErrorMode(FK_ERR_CONSOLE_INTERACTIVE);
	if(opencl.deviceInit("oclsamp.cl", "fk_OpenCL", false) == false) {
		cerr << "Dev Init Error." << endl;
		return 1;
	}

	// デバイス(GPU)内にデータバッファ作成。
	// (引数番号, データサイズ, CPU側からGPUにデータを転送するならtrue)
	opencl.createData(0, sizeof(float)*SIZE, false);
	opencl.createData(1, sizeof(float)*SIZE*3, true);

	// 3次元座標配列を適当に設定
	for(i = 0; i < SIZE*3; i++) b[i] = float(sin(i));

	for(int count = 0; count <= 1000; count++) {

		// CPUからGPUにデータ転送
		// (引数番号, データサイズ, データポインタ)
		opencl.sendData(1, sizeof(float)*SIZE*3, &b[0]);

		// 実行。引数は配列データ数
		opencl.run(SIZE);

		// 処理後、GPUからCPUにデータ転送。
		// (引数番号, データサイズ, データポインタ)
		opencl.getData(0, sizeof(float)*SIZE, &a[0]);

		if(count % 100 == 0) {
			for(i = 0; i < SIZE; i += 10000) {
				cout << count << ", " << a[i] << endl;
			}
		}
	}
	return 0;
}
