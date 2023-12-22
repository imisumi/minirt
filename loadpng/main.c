// #define LODEPNG_COMPILE_CPP
// #include "lodepng.h"
#include "lodepng/lodepng.h"
// # include "../MLX42/include/lodepng/lodepng.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned width = 100; // Replace with your desired image width
    unsigned height = 100; // Replace with your desired image height

    // Allocate memory for the image data (RGBA format)
    // unsigned char* image_data = (unsigned char*)malloc(width * height * 4);
	uint8_t* image_data = (unsigned char*)malloc(width * height * 4);

    // Fill the image with white pixels (RGBA: 255, 255, 255, 255)
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned index = 4 * width * y + 4 * x;
            image_data[index + 0] = 255; // Red
            image_data[index + 1] = 0; // Green
            image_data[index + 2] = 255; // Blue
            image_data[index + 3] = 255; // Alpha
        }
    }

    // Save the image as output.png
    unsigned error = lodepng_encode32_file("output2.png", image_data, width, height);
    if (error) {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
    } else {
        printf("Image saved as output.png\n");
    }

    free(image_data);
    return 0;
}
