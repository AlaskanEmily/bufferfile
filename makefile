# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: libbufferfile.a

bufferfile_mmap.o: bufferfile_mmap.c bufferfile.h
	cc -Wall -Werror -ansi -fPIC -c bufferfile_mmap.c -o bufferfile_mmap.o

libbufferfile.a: bufferfile_mmap.o
	ar rc libbufferfile.a bufferfile_mmap.o
	ranlib libbufferfile.a

clean:
	rm libbufferfile.a || true
	rm bufferfile_mmap.o || true

.PHONY: clean all
.IGNORE: clean
.SILENT: clean
