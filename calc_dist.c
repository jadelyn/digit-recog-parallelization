/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * You MUST implement the calc_min_dist() function in this file.
 *
 * You do not need to implement/use the swap(), flip_horizontal(), transpose(), or rotate_ccw_90()
 * functions, but you may find them useful. Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "digit_rec.h"
#include "utils.h"
#include "limits.h"


/* Swaps the values pointed to by the pointers X and Y. */
void swap(unsigned char *x, unsigned char *y) {
    /* Optional function */
    int tmp = *x;
    *x = *y;
    *y = tmp;

}

/* Flips the elements of a square array ARR across the y-axis. */
void flip_horizontal(unsigned char *arr, int width) {
    /* Optional function */
    int x, y;
    for (y = 0; y < width; y++) {
        for (x = 0; x < width / 2; x++) {
            swap(arr + width * y + x, arr + width * y + (width - 1 - x));
        }
    }
}

/* Transposes the square array ARR. */
void transpose(unsigned char *arr, int width) {
    /* Optional function */
    int x, y;
    for (y = 0; y < width; y++) {
        for (x = 0; x < width / 2; x++) {
            swap(arr + width * y + x, arr + width * x + y);
        }
    }
}

/* Rotates the square array ARR by 90 degrees counterclockwise. */
void rotate_ccw_90(unsigned char *arr, int width) {
    /* Optional function */
    int x, y;
    unsigned char newarr[width * width];
    for (y = 0; y < width; y++) {
      for (x = 0; x < width; x++) {
        newarr[width * (width - x - 1) + y] = arr[width * y + x];
      }
    }
    for (int i = 0; i < width * width; i++) {
      arr[i] = newarr[i];
    }
}

/* Returns the squared Euclidean distance between each pixel in two images, given
 * an IMAGE, a TEMPLATE with side length T_WIDTH and a starting point, START. */
unsigned int calc_dist(unsigned char *image, int i_width, unsigned char *template, int t_width,
    int start_x, int start_y) {
    unsigned int squaredSum = 0;
    int counter = 0;
    for (int i = start_y; i < t_width + start_y; i++) {
        for (int k = start_x; k < t_width + start_x; k++, counter++) {
            squaredSum += (image[i_width * i + k] - template[counter]) * (image[i_width * i + k] - template[counter]);
        }
    }
    return squaredSum;
}


/** Returns the minimum distance. */
unsigned int calc_min(unsigned char *image, int i_width, unsigned char *template,
    int t_width, int start_x, int start_y, unsigned int min_dist) {
    unsigned int newDist = 0;
    for (int i = 0; i < 4; i++) {
        rotate_ccw_90(template, t_width);
        newDist = calc_dist(image, i_width, template, t_width, start_x, start_y);
        if (newDist < min_dist) {
            min_dist = newDist;
        }
    }
    flip_horizontal(template, t_width);
    for (int i = 0; i < 4; i++) {
        rotate_ccw_90(template, t_width);
        newDist = calc_dist(image, i_width, template, t_width, start_x, start_y);
        if (newDist < min_dist) {
            min_dist = newDist;
        }
    }
    flip_horizontal(template, t_width);
    return min_dist;
}

/* Returns the squared Euclidean distance between TEMPLATE and IMAGE. The size of IMAGE
 * is I_WIDTH * I_HEIGHT, while TEMPLATE is square with side length T_WIDTH. The template
 * image should be flipped, rotated, and translated across IMAGE.
 */
unsigned int calc_min_dist(unsigned char *image, int i_width, int i_height, 
        unsigned char *template, int t_width) {
    unsigned int min_dist = UINT_MAX;
    /* YOUR CODE HERE */
    for (int i = 0; i + t_width - 1 < i_width; i++) {
        for (int j = 0; j + t_width - 1 < i_height; j++) {
            min_dist = calc_min(image, i_width, template, t_width, i, j, min_dist);
        }
    }
    return min_dist;
}

