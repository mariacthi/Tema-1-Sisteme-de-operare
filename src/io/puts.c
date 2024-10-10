#include <unistd.h>
#include <string.h>

int puts(const char *s)
{
	/* using write for the actual string and checking what it returns  */
	size_t l = strlen(s);
	int x = write(1, s, l);
	if (x < 0)
		return x;

	/* adding the newline character */
	x = write(1, "\n", 1);
	if (x < 0)
		return x;

	return x;
}
