

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static char* mmap_file(size_t* len, const char* filename)
{
#ifdef _WIN64
  HANDLE file =
      CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

  if (file == INVALID_HANDLE_VALUE) { /* E.g. Model may not have materials. */
    return NULL;
  }

  HANDLE fileMapping = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
  assert(fileMapping != INVALID_HANDLE_VALUE);

  LPVOID fileMapView = MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);
  char* fileMapViewChar = (char*)fileMapView;
  assert(fileMapView != NULL);

  DWORD file_size = GetFileSize(file, NULL);
  (*len) = (size_t)file_size;

  return fileMapViewChar;
#else

  struct stat sb;
  char* p;
  int fd;

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("open");
    return NULL;
  }

  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    return NULL;
  }

  if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "%s is not a file\n", filename);
    return NULL;
  }

  p = (char*)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }

  if (close(fd) == -1) {
    perror("close");
    return NULL;
  }

  (*len) = sb.st_size;

  return p;

#endif
}

static void get_file_data(void* ctx, const char* filename, const int is_mtl,
                          const char* obj_filename, char** data, size_t* len) {
	// NOTE: If you allocate the buffer with malloc(),
	// You can define your own memory management struct and pass it through `ctx`
	// to store the pointer and free memories at clean up stage(when you quit an
	// app)
	// This example uses mmap(), so no free() required.
	(void)ctx;

	if (!filename) {
		fprintf(stderr, "null filename\n");
		(*data) = NULL;
		(*len) = 0;
		return;
	}

	size_t data_len = 0;

	*data = mmap_file(&data_len, filename);
	(*len) = data_len;
}

int	main(int argc, char **argv)
{
	printf("Hello World!\n");

	tinyobj_attrib_t attrib;
	tinyobj_shape_t* shapes = NULL;
	size_t num_shapes;
	tinyobj_material_t* materials = NULL;
	size_t num_materials;

	unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
	// const char* filename = "cornell_box.obj";
	const char* filename = "default_cube.obj";
	int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, 
			&num_materials, filename, get_file_data, NULL, flags);
	if (ret != TINYOBJ_SUCCESS)
		return 0;
	// printf("num_shapes: %lu\n", num_shapes);
	// printf("num_materials: %zu\n", num_materials);
	// printf("attrib.vertices: %p\n", attrib.vertices);
	// printf("attrib.num_vertices: %u\n", attrib.num_vertices);
	// printf("attrib.normals: %p\n", attrib.normals);
	// printf("attrib.num_normals: %u\n", attrib.num_normals);
	// printf("%s\n", shapes[0].name);
	float *vertuces = attrib.vertices;
	for (int i = 0; i < attrib.num_vertices; i++)
	{
		printf("v %f %f %f\n", vertuces[i * 3], vertuces[i * 3 + 1], vertuces[i * 3 + 2]);
	}
	for (int i = 0; i < attrib.num_normals; i++)
	{
		printf("vn %f %f %f\n", attrib.normals[i * 3], attrib.normals[i * 3 + 1], attrib.normals[i * 3 + 2]);
	}
	// free memory
	tinyobj_attrib_free(&attrib);
}
