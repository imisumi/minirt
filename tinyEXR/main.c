// all:
// 	gcc -O2 -c -I../../deps/miniz ../../deps/miniz/miniz.c
// 	g++ -O2 -o rgbe2exr -I../common -I../../ -I../../deps/miniz rgbe2exr.cc ../../tinyexr.cc miniz.o

#include <stdio.h>
#include <stdlib.h>
#include "tinyexr.h"

int main()
{
	const char* input = "1.exr";
	float* out; // width * height * RGBA
	int width;
	int height;
	const char* err = NULL; // or nullptr in C++11

	int ret = LoadEXR(&out, &width, &height, input, &err);
	printf("width = %d, height = %d\n", width, height);

	if (ret != TINYEXR_SUCCESS)
	{
		if (err)
		{
			fprintf(stderr, "ERR : %s\n", err);
			FreeEXRErrorMessage(err);
		}
	}
	else
		free(out);
	return 0;
}
