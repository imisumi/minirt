#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb/stb_image_write.h"

unsigned char tone_map(float hdr_value) {
    const float threshold = 1.0f;

    if (hdr_value > threshold) {
        return 255; // White pixel
    }

    unsigned char mapped_value = (unsigned char)(hdr_value * 255.0f);
    return mapped_value;
}

int main(void)
{
    const char* filename = "sky_1k.hdr";
    int width, height, num_channels;
    float* pixels = stbi_loadf(filename, &width, &height, &num_channels, 0);

    if (pixels == NULL) {
        printf("Error in loading the image\n");
        return 1; // Return error code
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Access individual pixel values
            float r = pixels[(y * width + x) * num_channels];
            float g = pixels[(y * width + x) * num_channels + 1];
            float b = pixels[(y * width + x) * num_channels + 2];
            // if (r > 1.0f || g > 1.0f || b > 1.0f)
            //     printf("Pixel at (%d, %d) : %f, %f, %f\n", x, y, r, g, b);
        }
    }

    unsigned char* output_pixels = malloc(width * height * num_channels * sizeof(unsigned char));
    for (int i = 0; i < width * height * num_channels; ++i) {
        output_pixels[i] = tone_map(pixels[i]);
    }

    stbi_write_png("output.png", width, height, num_channels, output_pixels, width * num_channels);

    // Cleanup
    stbi_image_free(pixels);
    free(output_pixels);

    return 0;
}















t_vec4 per_pixel(t_ray ray, t_vec2 coord, t_scene s)
{
	// return get_sky_color(ray, coord);
	// return (vec4_create(coord.x, coord.y, 0.0f, 1.0f));







	// t_vec4 frag;
	// frag = vec4_create(ray.direction.x, ray.direction.y, ray.direction.z, 1.0f);
	// return (frag);

	
	t_vec3 color;

	t_obj_hit obj_hit;
	obj_hit.hit_distance = MAXFLOAT;

	t_sphere* closest_sphere = NULL;
	t_inv_plane* closest_inv_plane = NULL;
	t_inv_plane plane;
	plane.normal = vec3_create(1.0f, 0.0f, 0.0f);
	plane.position = vec3_create(-1.0f, 0.0f, 0.0f);

	float hit_distance = MAXFLOAT;
	
	for (int i = 0; i < s.nb_spheres; i++)
	{
		t_vec3 origin = vec3_sub(ray.origin, s.spheres[i].center);
		
		float a = vec3_dot(ray.direction, ray.direction);
		float b = 2.0 * vec3_dot(origin, ray.direction);
		float c = vec3_dot(origin, origin) - (s.spheres[i].radius * s.spheres[i].radius);

		float discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0.0f)
			continue;

		float closest_hit = (-b - sqrtf(discriminant)) / (2.0 * a);
		if (closest_hit < hit_distance)
		{
			hit_distance = closest_hit;
			// closest_sphere = &s.spheres[i];
			obj_hit.position = s.spheres[i].center;
			obj_hit.hit_distance = hit_distance;
		}
	}
	
	//plane intersection code
	for (int i = 0; i < s.nb_planes; i++)
	{
		float denom = vec3_dot(ray.direction, s.planes[i].normal);
		if (fabs(denom) > 1e-6)
		{
			t_vec3 p0l0 = vec3_sub(s.planes[i].position, ray.origin);
			float t = vec3_dot(p0l0, s.planes[i].normal) / denom;
			if (t < 0.0f)
				continue;
			
			if (t < hit_distance)
			{
				t_vec3 intersection_point = hit_position(ray, t);
				float half_width = s.planes->width / 2.0f;
				float half_height = s.planes->height / 2.0f;
				
				// Check if the intersection point lies within the plane's limits
				if (intersection_point.x >= (s.planes[i].position.x - half_width) &&
					intersection_point.x <= (s.planes[i].position.x + half_width) &&
					intersection_point.y >= (s.planes[i].position.y - half_height) &&
					intersection_point.y <= (s.planes[i].position.y + half_height) &&
					intersection_point.z >= (s.planes[i].position.z - half_height) &&
					intersection_point.z <= (s.planes[i].position.z + half_height))
				{
					hit_distance = t;
					closest_inv_plane = &plane;
					obj_hit.position = s.planes[i].position;
					obj_hit.hit_distance = hit_distance;

				}
			}
		}
	}

	if (obj_hit.hit_distance == MAXFLOAT)
	{
		return get_sky_color(ray, coord);
		return (vec4_create(0, 0, 0, 1.0));
	}


	t_vec3 origin = vec3_sub(ray.origin, obj_hit.position);
	t_vec3 hitPoint = hit_position(ray, hit_distance);
	t_vec3 normal = vec3_normalize(vec3_sub(hitPoint, obj_hit.position));

	t_vec3 lightDirection = vec3_fill(-1.0f);
	lightDirection = vec3_normalize(vec3_create(-1.0f, -1.0f, -1.0f));

	color = vec3_add_float(vec3_mul_float(normal, 0.5), 0.5f);

	float lightIntensity = vec3_dot(normal, vec3_mul_float(lightDirection, -1.0f));
	if (lightIntensity < 0.0f)
		lightIntensity = 0.0f;
	
	// color = vec3_create(1.0f, 0.0f, 1.0f);
	color  = vec3_normalize(color);
	color = vec3_mul_float(color, lightIntensity * 1.2);

	// return vec4_create(1, 0, 1, 1);
	return vec4_create(color.x, color.y, color.z, 1.0);
}