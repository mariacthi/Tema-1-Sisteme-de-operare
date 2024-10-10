// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/fcntl/open.c#L5 */
	mode_t mode = 0;

	/* finding out the mode */
	if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	int result = syscall(__NR_open, filename, flags, mode);

	if (result < 0) {
		errno = -result;
		return -1;
	}

	return result;
}
