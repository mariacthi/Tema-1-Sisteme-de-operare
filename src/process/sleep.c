#include <unistd.h>
#include <internal/syscall.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
	/* creating the parameters for calling the nanosleep function */
	struct timespec sleep_time, remaining;
	sleep_time.tv_sec = seconds;
	sleep_time.tv_nsec = 0;

	int result = nanosleep(&sleep_time, &remaining);

	if (result != 0)
		return -1;

	return result;
}
