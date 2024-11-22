#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction pour initialiser une image PPM */
int ppm_image_init(struct ppm_image *im, int w, int h) {
    memset(im, 0, sizeof(struct ppm_image));  // Réinitialiser la structure

    im->width = w;   // Définir la largeur de l'image
    im->height = h;  // Définir la hauteur de l'image

    im->px = malloc(w * h * sizeof( struct ppm_pixel));  // Allouer de la mémoire pour les pixels

    if (!im->px) {  // Vérifier l'échec de l'allocation mémoire
        perror("malloc");
        return 1;
    }

    return 0;
}

/* Fonction pour libérer la mémoire d'une image PPM */
int ppm_image_release(struct ppm_image *im) {
    if (im == NULL)  // Vérifier si l'image est déjà nulle
        return 1;

    free(im->px);  // Libérer la mémoire des pixels
    im->px = NULL; // Réinitialiser le pointeur

    im->width = 0;  // Réinitialiser la largeur
    im->height = 0; // Réinitialiser la hauteur

    return 0;
}

/* Fonction pour sauvegarder une image PPM dans un fichier */
int ppm_image_dump(struct ppm_image *im, char *path) {
    FILE *out = fopen(path, "w");  // Ouvrir le fichier en écriture

    if (!out) {  // Vérifier si l'ouverture du fichier a échoué
        perror("fopen");
        return 1;
    }

    // Écrire l'en-tête PPM
    fprintf(out, "P6\n");
    fprintf(out, "%d\n", im->width);
    fprintf(out, "%d\n", im->height);
    fprintf(out, "255\n");  // Valeur maximale pour chaque composant de couleur

    // Écrire les données de l'image
    fwrite(im->px, sizeof(struct ppm_pixel), im->width * im->height, out);

    fclose(out);  // Fermer le fichier

    return 0;
}
