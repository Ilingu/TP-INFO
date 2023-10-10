#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STBI_NO_FAILURE_STRINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#include "stb_image_write.h"

#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>

typedef struct image
{
    uint8_t **at;
    unsigned h;
    unsigned w;
} image;

image *image_new(unsigned h, unsigned w)
{
    uint8_t **at = malloc(h * sizeof(uint8_t *));
    for (unsigned i = 0; i < h; i++)
        at[i] = malloc(w * sizeof(uint8_t));

    image *im = malloc(1 * sizeof(image));
    im->at = at;
    im->h = h;
    im->w = w;

    return im;
}

void image_delete(image *im)
{
    for (unsigned i = 0; i < im->h; i++)
        free(im->at[i]);
    free(im->at);
    free(im);
}

void invert(image *im)
{
    for (unsigned raw = 0; raw < im->h; raw++)
        for (unsigned column = 0; column < im->w; column++)
            im->at[raw][column] = (uint8_t)255 - im->at[raw][column];
}

void binarize(image *im)
{
    for (unsigned raw = 0; raw < im->h; raw++)
        for (unsigned column = 0; column < im->w; column++)
            im->at[raw][column] = im->at[raw][column] < 128 ? (uint8_t)0 : (uint8_t)255;
}

void flip_horizontal(image *im)
{
    for (unsigned raw = 0; raw < im->h; raw++)
        for (unsigned column = 0; column < im->w / 2; column++)
        {
            unsigned opp_w = im->w - 1 - column;

            uint8_t opp_temp = im->at[raw][opp_w];
            im->at[raw][opp_w] = im->at[raw][column];
            im->at[raw][column] = opp_temp;
        }
}

image *image_load(char *filename)
{
    int w, h, channels;
    uint8_t *data = stbi_load(filename, &w, &h, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Erreur de lecture.\n");
        stbi_failure_reason();
        exit(EXIT_FAILURE);
    }
    if (channels != 1)
    {
        fprintf(stdout, "Pas une image en niveaux de gris.\n");
        exit(EXIT_FAILURE);
    }
    image *im = image_new(h, w);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            im->at[i][j] = data[j + i * w];
        }
    }
    free(data);
    return im;
}

void image_save(image *im, char *filename)
{
    int h = im->h;
    int w = im->w;
    int stride_length = w;
    uint8_t *data = malloc(w * h * sizeof(uint8_t));
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            data[j + i * w] = im->at[i][j];
        }
    }
    if (!stbi_write_png(filename, w, h, 1, data, stride_length))
    {
        fprintf(stderr, "Erreur d'écriture.\n");
        image_delete(im);
        free(data);
        exit(EXIT_FAILURE);
    }
    free(data);
}

typedef struct energy
{
    double **at;
    unsigned h;
    unsigned w;
} energy;

energy *energy_new(unsigned h, unsigned w)
{
    double **at = malloc(h * sizeof(double *));
    for (unsigned i = 0; i < h; i++)
        at[i] = malloc(w * sizeof(double));

    energy *e = malloc(1 * sizeof(energy));
    e->at = at;
    e->h = h;
    e->w = w;

    return e;
}

void energy_delete(energy *e)
{
    for (unsigned i = 0; i < e->h; i++)
        free(e->at[i]);
    free(e->at);
    free(e);
}

double absd(int a)
{
    return (double)abs(a);
}

void compute_energy(image *im, energy *e)
{
    unsigned w = im->w;
    unsigned h = im->h;

    for (unsigned i = 0; i < im->h; i++)
        for (unsigned j = 0; j < im->w; j++)
        {
            unsigned jr = j < w - 1 ? j + 1 : j, jl = j > 0 ? j - 1 : j, ib = i < h - 1 ? i + 1 : i, it = i > 0 ? i - 1 : i;
            double eij = (absd(im->at[i][jr] - im->at[i][jl]) / (double)(jr - jl)) + (absd(im->at[ib][j] - im->at[it][j]) / (double)(ib - it));
            e->at[i][j] = eij;
        }
}

image *energy_to_image(energy *e)
{
    image *im = image_new(e->h, e->w);

    double emax = e->at[0][0];
    double emin = e->at[0][0];

    for (unsigned i = 0; i < e->h; i++)
        for (unsigned j = 0; j < e->w; j++)
            if (e->at[i][j] > emax)
                emax = e->at[i][j];
            else if (e->at[i][j] < emin)
                emin = e->at[i][j];

    for (unsigned i = 0; i < im->h; i++)
        for (unsigned j = 0; j < im->w; j++)
            im->at[i][j] = (e->at[i][j] - emin) * 255.0 / (emax - emin);
    return im;
}

void remove_pixel(uint8_t *line, double *e, unsigned w)
{
    unsigned i_emin = 0;
    for (unsigned i = 0; i < w; i++)
        if (e[i] < e[i_emin])
            i_emin = i;

    for (unsigned i = i_emin; i < w - 1; i++)
    {
        line[i] = line[i + 1];
        e[i] = e[i + 1];
    }
}

void reduce_one_pixel(image *im, energy *e)
{
    for (unsigned i = 0; i < im->h; i++)
        remove_pixel(im->at[i], e->at[i], im->w);

    im->w--;
    e->w--;
}

void reduce_pixels(image *im, unsigned n)
{
    energy *e = energy_new(im->h, im->w);
    compute_energy(im, e);

    assert(e->h == im->h);
    assert(e->w == im->w);

    for (unsigned j = 0; j < n; j++)
        reduce_one_pixel(im, e);

    energy_delete(e);
}

unsigned best_column(energy *e)
{
    unsigned best_index = 0;
    double best_value = -1.0;

    for (unsigned column = 0; column < e->w; column++)
    {
        double sum = 0.0;
        for (unsigned raw = 0; raw < e->h; raw++)
            sum += e->at[raw][column];

        if (column == 0)
            best_value = sum;
        else if (sum < best_value)
        {
            best_index = column;
            best_value = sum;
        }
    }

    assert(best_value >= 0);
    return best_index;
}

void reduce_one_column(image *im, energy *e)
{
    unsigned best_col = best_column(e);
    for (unsigned col = best_col; col < im->w - 1; col++)
        for (unsigned raw = 0; raw < im->h; raw++)
        {
            im->at[raw][col] = im->at[raw][col + 1];
            e->at[raw][col] = e->at[raw][col + 1];
        }

    im->w--;
    e->w--;
}

void reduce_column(image *im, unsigned n)
{
    energy *e = energy_new(im->h, im->w);
    compute_energy(im, e);

    assert(e->h == im->h);
    assert(e->w == im->w);

    for (unsigned j = 0; j < n; j++)
        reduce_one_column(im, e);

    energy_delete(e);
}

// void energy_min_path(energy *e);

// path *path_new(int n);

// void path_delete(path *p);

// void compute_min_path(energy *e, path *p);

// void reduce_seam_carving(image *im, int n);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Fournir le fichier d'entrée et de sortie.\n");
        exit(EXIT_FAILURE);
    }
    char *f_in = argv[1];
    char *f_out = argv[2];

    image *im = image_load(f_in);

    reduce_column(im, 100);

    image_save(im, f_out); // save changes
    image_delete(im);

    return 0;
}
