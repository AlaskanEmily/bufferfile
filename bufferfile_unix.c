/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "bufferfile.h"
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

const void *BufferFile(const char *file, int *size){
    if(!file || !size){
        return NULL;
    }
    else{
        
        const int fd = open(file, O_RDONLY);
        struct stat lstat;
        void *buffer = NULL;
        
        if(fd < 0){
            return NULL;
        }
        
        fstat(fd, &lstat);
        
        buffer = malloc(lstat.st_size);
        
        if(buffer){
            size[0] = lstat.st_size;
            read(fd, buffer, lstat.st_size);
        }
        
        close(fd);
        
        return buffer;
    }
}

void FreeBufferFile(const void *in, int size){
    (void)size;
    free((void*)in);
}
