#include <stdio.h>
#include "t.h"

int main() {
    int width = 800;
    int height = 400;
    printf("P3\n%d %d\n255\n", width, height);
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            vec3 col = { (float)x / (float)width, (float)y / (float)height, 0.2f };
            int ir = (int)(255.99 * col.x);
            int ig = (int)(255.99 * col.y);
            int ib = (int)(255.99 * col.z);
            printf("%d %d %d\n", ir, ig, ib);
        }
    }

    return 0;
}