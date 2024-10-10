// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* implementare asemanatoare cu cea de la lab1 Software Stack
	(exercitiul common functions) */
	for (; *source != '\0'; source++, destination++)
		*destination = *source;

	/* Also place NULL byte. */
	*destination = *source;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	for (; *source != '\0' && len > 0; source++, destination++, --len)
		*destination = *source;

	/* if source is a string with a length shorter than len,
	then the function fills the destination string with NULL bytes */
	while (len > 0) {
		*destination++ = '\0';
		len--;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* sursa: https://www.gnu.org/software/libc/manual/html_mono/libc.html */
	strcpy(destination + strlen(destination), source);
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* copying the bites at the end of the destination string */
	destination = destination + strlen(destination);

	for (; *source != '\0' && len > 0; source++, destination++, --len)
		*destination = *source;

	/* Also place NULL byte. */
	*destination = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/string/strcmp.c#L3 */
	for (; *str1 == *str2 && *str1; str1++, str2++)
		;

	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	for (; *str1 == *str2 && *str1 && *str2 && len > 0; str1++, str2++, len--)
		;

	if (len == 0 || (*str1 == '\0' && *str2 == '\0'))
		return 0;

	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	c = (char)c;

	/* if c is the string terminator, the function returns
	a pointer to the end of string */
	if (!c) return (char *)str + strlen(str);

	for(; *str && *str != c; str++)
		;

	/* if it didnt find the character */
	if (!(*str))
		return NULL;

	return (char *)str;
}

char *strrchr(const char *str, int c)
{
	c = (char)c;
	size_t l = strlen(str);

	for(; str[l] != c && l; --l)
		;

	/* if it didnt find the character */
	if (l == 0)
		return NULL;

	return (char *)str + l;
}

char *strstr(const char *haystack, const char *needle)
{
	if(*needle == '\0')
		return (char *)haystack;

	char letter = *needle;
	size_t l = strlen(needle);
	char *p = NULL;

	while (1) {
		/* searching for the first letter of needle*/
		p = strchr(haystack, (int)letter);
		if (!p)
			break;

		/* if it finds the first letter, then checks for
		the rest of the letters */
		size_t i;
		for(i = 0; i < l && p[i] == needle[i]; haystack++, i++)
			;

		if (i == l)
			break;
	}

	return p;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* sursa: chat GPT */
	if (*needle == '\0')
		return (char *)haystack;

	char *result = NULL;

	while (1) {
		char *p = strstr(haystack, needle);
        if (!p)
			break;

        result = p;
        haystack = p + 1;
	}

	return result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/string/memcpy.c#L5 */
	unsigned char *d = destination;
	const unsigned char *s = source;

	for (; num; num--)
		*d++ = *s++;

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/string/memmove.c#L9 */
	char *d = destination;
	const char *s = source;

	if (d == s)
		return d;

	while (num) {
		num--;
		d[num] = s[num];
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/string/memcmp.c#L3 */
	const unsigned char *p1 = ptr1, *p2 = ptr2;
	for (; num && *p1 == *p2; num--, p1++, p2++)
		;

	return num ? *p1 - *p2 : 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *s = source;

	for(; num; s++, num--)
		*s = (char)value;

	return source;
}
