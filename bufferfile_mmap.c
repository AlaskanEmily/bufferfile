/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "bufferfile.h"
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <assert.h>

const void *BufferFile(const char *file, int *size){
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

void FreeBufferFile(const void *in, int size){
    munmap((void*)in, size);
}
