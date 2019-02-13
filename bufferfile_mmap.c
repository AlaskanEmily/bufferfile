/*
 * Copyright (c) 2016-2019 Alaskan Emily, Transnat Games
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
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <assert.h>

void *BufferFile(const char *file, int *size){
    if(!file || !size){
        return NULL;
    }
    else{
        const int fd = open(file, O_RDONLY);
        struct stat lstat;

        if(fd < 0){
            return NULL;
        }

        fstat(fd, &lstat);
        {
            void *const data =
                mmap(NULL, lstat.st_size, PROT_READ, MAP_SHARED, fd, 0);
            if(data!=MAP_FAILED){
                size[0] = lstat.st_size;
                return data;
            }
            else{
                return NULL;
            }
        }
    }
}

void FreeBufferFile(void *in, int size){
    munmap(in, size);
}
