/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "bufferfile.h"
#include <stdio.h>
#include <stdlib.h>

const void *BufferFile(const char *file, int *size){
    if(!file || !size){
        return NULL;
    }
    else{
        FILE * const that = fopen(file, "rb");
        unsigned to = 0, capacity = 0x100;
        char *buffer = NULL;
        
        if(!that){
            return NULL;
        }

        /* Load the file. */
        do{
            if(buffer){
                /* Check for rollover */
                const int new_capacity = capacity << 1;
                if(new_capacity < capacity){
                    free(buffer);
                    fclose(that);
                    return NULL;
                }
                else{
                    /* Check for alloc fail */
                    void *const new_buffer = realloc(buffer, new_capacity);
                    if(new_buffer == NULL){
                        free(buffer);
                        fclose(that);
                        return NULL;
                    }
                }
                
                buffer = new_buffer;
            }
            else{
                buffer = malloc(capacity);
                if(buffer == NULL){
                    /* Out of memory */
                    fclose(that);
                    return NULL;
                }
            }
            to += fread(buffer+to, 1, capacity-to, that);
        }while(!feof(that));

        size[0] = to;
        fclose(that);
        return buffer;
    }
}

void FreeBufferFile(const void *in, int size){
    (void)size;
    free((void*)in);
}
