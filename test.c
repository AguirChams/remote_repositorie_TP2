#include <stdio.h>
#include <stdlib.h>

// Fonction pour écrire l'entête d'un fichier PPM
void write_ppm_header(FILE *file, int width, int height) {
    fprintf(file, "P3\n"); // Format ASCII PPM
    fprintf(file, "%d %d\n", width, height); // Dimensions de l'image
    fprintf(file, "255\n"); // Valeur maximale pour les couleurs
}

// Fonction pour écrire les pixels dans le fichier PPM
void write_ppm_data(FILE *file, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r = (x * 255) / width;  // Dégradé rouge
            int g = (y * 255) / height; // Dégradé vert
            int b = ((x + y) * 255) / (width + height); // Dégradé bleu (optionnel)
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }
}

int main() {
    const int width = 1024;  // Largeur de l'image
    const int height = 768;  // Hauteur de l'image
    const char *filename = "test.ppm"; // Nom du fichier de sortie

    // Ouvrir le fichier en mode écriture
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    // Écrire l'en-tête et les données
    write_ppm_header(file, width, height);
    write_ppm_data(file, width, height);

    // Fermer le fichier
    fclose(file);

    printf("Image PPM générée : %s\n", filename);
    return 0;
}
