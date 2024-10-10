// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/malloc/mallocng/malloc.c#L299 */
	if (size == 0)
		return NULL;

	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;

	/* adding the pointer to the list so as to be found
	when it needs to be freed*/
	if (mem_list_add(ptr, size) == -1) {
		munmap(ptr, size);
		return NULL;
	}

	return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	/* equivalent to malloc(nmemb * size)*/
	if (size == 0)
		return NULL;

	long total = nmemb * size;

	void *ptr = malloc(total);
	if (ptr)
		memset(ptr, 0, total);

	return ptr;
}

void free(void *ptr)
{
	if (!ptr)
		return;

	/* finding the pointer that was added to the list when malloc was used */
	struct mem_list *memory = mem_list_find(ptr);
	if (!memory)
		return;

	/* deleting the pointer from the list*/
	mem_list_del(memory->start);

	/* freeing the memory */
	munmap(ptr, memory->len);
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);

	if (size == 0) {
		free(ptr);
		return NULL;
	}

	/* using malloc for a new pointer */
	void *ptr2 = malloc(size);
	if (!ptr2)
		return NULL;

	/* copying the data from the old zone to the new one */
	memcpy(ptr2, ptr, size);

	/* freeing the old pointer */
	munmap(ptr, 0);

	return ptr2;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* sursa:
	https://elixir.bootlin.com/musl/latest/source/src/malloc/reallocarray.c#L5 */
	if (size && nmemb > -1 / size) {
		errno = ENOMEM;
		return (void *)-1;
	}
	return realloc(ptr, nmemb * size);
}
