#include <unistd.h>
#include <time.h>
#include <internal/syscall.h>
#include <errno.h>

int nanosleep(const struct timespec *requested_time, struct timespec *remaining)
{
	int result = syscall(__NR_nanosleep, requested_time, remaining);

	if (result < 0) {
		errno = -result;
		return -1;
	}

	return result;
}
