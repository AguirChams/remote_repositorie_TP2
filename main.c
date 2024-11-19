#include "ppm.h"

int main(void)
{
    struct ppm_image im;
    ppm_image_init(&im, 1024, 1024);

    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 1024; ++j) {
            ppm_image_setpixel(&im, i, j, i % 255, j % 255, (i + j) % 255);
        }
    }

    for (int i = 0; i < 1024; ++i) {
        ppm_image_setpixel(&im, i, i, 255, 0, 0);
    }

    ppm_image_dump(&im, "test.ppm");

    ppm_image_release(&im);

    return 0;
}
