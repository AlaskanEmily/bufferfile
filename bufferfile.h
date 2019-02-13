/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#ifndef BUFFERFILE_BUFFERFILE_H
#define BUFFERFILE_BUFFERFILE_H

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

const void *BufferFile(const char *file, int *size);
void FreeBufferFile(const void *in, int size);

#ifdef __cplusplus
}
#endif

#endif /* BUFFERFILE_BUFFERFILE_H */
