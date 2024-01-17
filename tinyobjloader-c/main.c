

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
#include <stdint.h>

typedef float	t_vec3f __attribute__ ((vector_size ((sizeof(float) * 4))));

// typedef uint32_t s_vert_indices[3] t_vert_indices
typedef uint32_t t_vert_indices[3];
typedef uint32_t t_vec3ui[3];

typedef struct s_tri_mesh
{
	t_vec3f		*vertices;
	t_vec3f		*normals;
	// t_vec2f		*uvs;
	t_vec3f		*colors;
	t_vec3f		*vert_indices;

}	t_tri_mesh;

typedef struct vertex_index
{
	t_vec3ui		*v;
	t_vec3f			*vn;
	t_vec3ui		*vt;
}	t_vertex_index;


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
	printf("num_shapes: %lu\n", num_shapes);
	printf("num_materials: %zu\n", num_materials);
	printf("attrib.vertices: %p\n", attrib.vertices);
	printf("attrib.num_vertices: %u\n", attrib.num_vertices);
	// printf("attrib.face_num_vert: %u\n", attrib.face_num_verts);
	printf("attrib.num_face_num_vert: %u\n", attrib.num_face_num_verts);
	printf("attrib.normals: %p\n", attrib.normals);
	printf("attrib.num_normals: %u\n", attrib.num_normals);
	printf("%s\n", shapes[0].name);
	float *vertuces = attrib.vertices;
	// for (int i = 0; i < attrib.num_vertices; i++)
	// {
	// 	printf("v %f %f %f\n", vertuces[i * 3], vertuces[i * 3 + 1], vertuces[i * 3 + 2]);
	// }
	// for (int i = 0; i < attrib.num_normals; i++)
	// {
	// 	printf("vn %f %f %f\n", attrib.normals[i * 3], attrib.normals[i * 3 + 1], attrib.normals[i * 3 + 2]);
	// }
	// printf("attrib.num_face_num_verts: %u\n", attrib.num_faces);
	// // for (int i = 0; i < attrib.num_face_num_verts; i++)
	// // {
	// // 	printf("f %d %d %d\n", attrib.face_num_verts[i * 3], attrib.face_num_verts[i * 3 + 1], attrib.face_num_verts[i * 3 + 2]);
	// // }
	t_vec3f	vert_indices[12];
	t_vert_indices *vert_indices2 = malloc(sizeof(t_vert_indices) * attrib.num_face_num_verts);
	int normals = attrib.num_normals;
	printf("normals: %d\n", normals);
	t_vec3f *normals2 = malloc(sizeof(t_vec3f) * normals);
	t_vertex_index indexes;
	indexes.v = malloc(sizeof(t_vec3ui) * attrib.num_face_num_verts);
	indexes.vn = malloc(sizeof(t_vec3f) * attrib.num_face_num_verts);
	indexes.vt = malloc(sizeof(t_vec3ui) * attrib.num_face_num_verts);
	for (int i = 0; i < attrib.num_face_num_verts; i++)
	{
		for (int j = 0; j < attrib.face_num_verts[i]; j++)
		{
			// vert_indices[i][j] = attrib.faces[i * 3 + j].v_idx;
			// vert_indices2[i][j] = attrib.faces[i * 3 + j].v_idx;
			indexes.v[i][j] = attrib.faces[i * 3 + j].v_idx;
			indexes.vn[i][j] = attrib.faces[i * 3 + j].vn_idx;
			indexes.vt[i][j] = attrib.faces[i * 3 + j].vt_idx;
			// printf("%d ", attrib.faces[i * 3 + j].vt_idx);
		}
		// printf("\n");
	}
	for (int i = 0; i < attrib.num_face_num_verts; i++)
	{
		printf("f %d %d %d\n", indexes.v[i][0], indexes.v[i][1], indexes.v[i][2]);
	}
	printf("\n");
	for (int i = 0; i < attrib.num_face_num_verts; i++)
	{
		printf("vn %f %f %f\n", indexes.vn[i][0], indexes.vn[i][1], indexes.vn[i][2]);
	}
	printf("\n");
	for (int i = 0; i < attrib.num_face_num_verts; i++)
	{
		printf("vt %d %d %d\n", indexes.vt[i][0], indexes.vt[i][1], indexes.vt[i][2]);
	}


	tinyobj_attrib_free(&attrib);
}
