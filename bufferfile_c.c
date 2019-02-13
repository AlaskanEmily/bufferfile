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
#include <stdio.h>
#include <stdlib.h>

void *BufferFile(const char *file, int *size){
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

void FreeBufferFile(void *in, int size){
    (void)size;
    free(in);
}
