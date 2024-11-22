#include "ppm.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>

#define TRSH 2.0
#define ITER 1024ull

#define SIZEX 1500
#define SIZEY 1500

/* Structure pour la couleur */
struct col {
    int r;
    int g;
    int b;
};

/* Fonction pour calculer la couleur */
struct col getcol(int val, int max) {
    double q = (double)val / (double)max;
    struct col c = {0, 0, 0};

    if (q < 0.25) {
        c.r = (q * 4.0) * 255.0;
        c.b = 255;
    } else if (q < 0.5) {
        c.b = 255;
        c.g = 255;
        c.r = (q - 0.25) * 4.0 * 255.0;
    } else if (q < 0.75) {
        c.b = 255;
        c.r = 255;
        c.g = 255.0 - (q - 0.5) * 4.0 * 255.0;
    } else {
        c.b = 255 - (q - 0.75) * 4.0 * 255.0;
        c.g = 0;
        c.r = 255;
    }

    return c;
}

/* Fonction de zoom */
void zoom(double *x_min, double *x_max, double *y_min, double *y_max, double factor) {
    double x_center = (*x_min + *x_max) / 2;
    double y_center = (*y_min + *y_max) / 2;

    double width = (*x_max - *x_min) / factor;
    double height = (*y_max - *y_min) / factor;

    *x_min = x_center - width / 2;
    *x_max = x_center + width / 2;
    *y_min = y_center - height / 2;
    *y_max = y_center + height / 2;
}

/* Calcul des coordonnées x */
double cx(int x) {
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

/* Calcul des coordonnées y */
double cy(int y) {
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}

int main(int argc, char *argv[]) {
    struct ppm_image im;
    if (ppm_image_init(&im, SIZEX, SIZEY) != 0) {
        fprintf(stderr, "Erreur : Impossible d'initialiser l'image PPM\n");
        return 1;
    }

    int colref = log(ITER); // Référence pour la couleur

    /* Calcul du Mandelbrot et assignation des couleurs */
    for (int i = 0; i < SIZEX; ++i) {
        for (int j = 0; j < SIZEY; ++j) {
            unsigned long int iter = 0;
            double complex c = cx(i) + cy(j) * I;
            double complex z = 0;

            while (iter < ITER) {
                if (cabs(z) > TRSH) {
                    break;
                }

                z = z * z + c;
                iter++;
            }

            /* Affectation des couleurs */
            struct col cc = getcol(log(iter + 1), colref); // Ajout de +1 pour éviter log(0)
            ppm_image_setpixel(&im, i, j, cc.r, cc.g, cc.b);
        }
    }

    /* Sauvegarde de l'image */
    if (ppm_image_dump(&im, "m.ppm") != 0) {
        fprintf(stderr, "Erreur : Impossible de sauvegarder l'image\n");
        ppm_image_release(&im);
        return 1;
    }

    /* Libération de la mémoire */
    ppm_image_release(&im);

    return 0;
}
