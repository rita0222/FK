#include <FK/Time.h>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace FK;

static system_clock::time_point procStart = system_clock::now();

fk_Time::fk_Time(void)
{
	init();
}

fk_Time::~fk_Time() {}

void fk_Time::start(void)
{
	runMode = true;
	stamp = system_clock::now();
}

void fk_Time::stop(void)
{
	auto now = system_clock::now();
	lap += double(duration_cast<microseconds>(now - stamp).count())/1000000.0;
	runMode = false;
}

void fk_Time::init(void)
{
	lap = 0.0;
	runMode = false;
}

double fk_Time::lapTime(void)
{
	auto now = system_clock::now();
	return ((runMode) ?
			double(duration_cast<microseconds>(now - stamp).count())/1000000.0 + lap : lap);
}

void fk_Time::sleep(double argSec)
{
	if(argSec < 0.0) return;
	this_thread::sleep_for(microseconds(int(argSec * 1000000.0)));
}

void fk_Time::usleep(double argSec)
{
	if(argSec < 0.0) return;
	this_thread::sleep_for(microseconds(int(argSec)));
}

double fk_Time::now(void)
{
	return double(duration_cast<microseconds>(system_clock::now() - procStart).count())/1000000.0;
}
