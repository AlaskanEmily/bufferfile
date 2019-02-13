/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "bufferfile.h"

#include <Windows.h>

const void *BufferFile(const char *path, int *size) {
	HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	const int l_size = size[0] = GetFileSize(file, NULL);

	HANDLE mmiofile = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
	void *const output = MapViewOfFile(mmiofile, FILE_MAP_READ, 0, 0, l_size);

	CloseHandle(file);
	CloseHandle(mmiofile);

	return output;
}

void FreeBufferFile(const void *in, int size) {
	(void)size;
	UnmapViewOfFile((void*)in);
}
