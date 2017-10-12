// VectorBool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "windows.h"
#include <vector>

static double CurrentTime()
{
	static LARGE_INTEGER Frequency = { };
	if (Frequency.QuadPart == 0)
		QueryPerformanceFrequency(&Frequency);
	static LARGE_INTEGER StartTime = { };
	if (StartTime.QuadPart == 0)
		QueryPerformanceCounter(&StartTime);

	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);

	return double(Time.QuadPart - StartTime.QuadPart) / Frequency.QuadPart;
}

static void report(const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	char buf[512];
	vsnprintf(buf, 512, fmt, vl);
	printf("%s", buf);
	OutputDebugStringA(buf);
	va_end(vl);
}

int main()
{
	report("initializing\n");
	std::vector<float> float_vec;
	std::vector<char> char_vec;
	std::vector<bool> bool_vec;

	const int kVecSize = 1000000;
	const int kIterations = 10;

	float_vec.resize(kVecSize);
	char_vec.resize(kVecSize);
	bool_vec.resize(kVecSize);

	for (int i = 0; i < kVecSize; i++)
	{
		char_vec[i] = rand() > RAND_MAX / 2;
		bool_vec[i] = rand() > RAND_MAX / 2;
	}

	report("running bools\n");
	double bool_avg_time = 0;
	for (int i = 0; i < kIterations; i++)
	{
		double s = CurrentTime();
		for (int j=0; j<kVecSize; j++)
			float_vec[i] = bool_vec[i] ? 1.f : 0.f;
		double t = (CurrentTime() - s);
		bool_avg_time += t;
		report("%d: %.2fms\n", i, t * 1000.0);
	}
	bool_avg_time /= kIterations;

	report("running chars\n");
	double char_avg_time = 0;
	for (int i = 0; i < kIterations; i++)
	{
		double s = CurrentTime();
		for (int j = 0; j<kVecSize; j++)
			float_vec[i] = char_vec[i] ? 1.f : 0.f;
		double t = (CurrentTime() - s);
		char_avg_time += t;
		report("%d: %.2fms\n", i, t * 1000.0);
	}
	char_avg_time /= kIterations;

	report("\n");
	report("bool avg: %.2fms\n", bool_avg_time * 1000.0);
	report("char avg: %.2fms\n", char_avg_time * 1000.0);
	report("\n");

    return 0;
}

