#include "timer.h"

static struct timeval startTime;
static struct timeval endTime;

void timer_start()
{
	gettimeofday(&startTime, NULL);
}

unsigned long long timer_mStop()
{
	gettimeofday(&endTime, NULL);

	return 1000 * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000;
}

unsigned long long timer_uStop()
{
	gettimeofday(&endTime, NULL);

	return 1000000 * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
}
