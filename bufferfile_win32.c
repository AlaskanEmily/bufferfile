/*
 * Copyright (c) 2017-2019 Alaskan Emily, Transnat Games
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software
 *      in a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#include "bufferfile.h"

#include <Windows.h>

void *BufferFile(const char *path, int *size) {
	HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	const int l_size = size[0] = GetFileSize(file, NULL);

	HANDLE mmiofile = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
	void *const output = MapViewOfFile(mmiofile, FILE_MAP_READ, 0, 0, l_size);

	CloseHandle(file);
	CloseHandle(mmiofile);

	return output;
}

void FreeBufferFile(void *in, int size) {
	(void)size;
	UnmapViewOfFile(in);
}
