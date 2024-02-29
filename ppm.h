#ifndef PPM_H
#define PPM_H

/* Structure représentant un pixel avec ses composantes rouge, verte et bleue */
struct ppm_pixel {
    unsigned char r; // Composante rouge
    unsigned char g; // Composante verte
    unsigned char b; // Composante bleue
};

/* Fonction inline pour définir les valeurs d'un pixel */
static inline void ppm_setpixel(
    struct ppm_pixel *px,
    unsigned char r, unsigned char g, unsigned char b)
{
    px->r = r;
    px->g = g;
    px->b = b;
}

/* Structure représentant une image PPM avec ses dimensions et ses pixels */
struct ppm_image {
    unsigned int width;  // Largeur de l'image
    unsigned int height; // Hauteur de l'image
    struct ppm_pixel *px; // Tableau de pixels
};

/* Prototypes des fonctions principales pour gérer une image PPM */
int ppm_image_init(struct ppm_image *im, int w, int h);       // Initialiser une image PPM
int ppm_image_release(struct ppm_image *im);                 // Libérer la mémoire d'une image PPM

/* Fonction inline pour définir un pixel spécifique dans une image */
static inline void ppm_image_setpixel(
    struct ppm_image *im, int x, int y,
    unsigned char r, unsigned char g, unsigned char b)
{
    struct ppm_pixel *px = im->px + im->width * y + x; // Accès au pixel (x, y)
    ppm_setpixel(px, r, g, b); // Définir la couleur du pixel
}

/* Sauvegarder une image PPM dans un fichier */
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */
