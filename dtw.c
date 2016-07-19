#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dtw.h"

double dtw(double *x, double *y, int xsize, int ysize, double window_frac)
{
    /* DTW distance algorithm based on
    https://en.wikipedia.org/wiki/Dynamic_time_warping */
    const double LARGE_VALUE = 1e30;
    const int min_window = abs(xsize - ysize);
    int i, j, minj, maxj, window;
    double dist, min;
    double **distances = malloc((xsize + 1) * sizeof(double *));
    for(i = 0; i < xsize + 1; ++i)
        distances[i] = malloc((ysize + 1) * sizeof(double));

    window = window_frac*ysize;
    if(xsize > ysize)
        window = window_frac*xsize;

    if(window < min_window)
        window = min_window;

    for(i = 0; i <= xsize; ++i)
        for(j = 0; j <= ysize; ++j)
            distances[i][j] = LARGE_VALUE;
    distances[0][0] = 0.0;

    for(i = 0; i < xsize; ++i)
    {
        minj = i - window;
        if(minj < 0)
            minj = 0;
        maxj = i + window;
        if(maxj > ysize)
            maxj = ysize;
        for(j = minj; j < maxj; ++j)
        {
            dist = fabs(x[i] - y[j]);
            min = distances[i][j];
            if(min > distances[i][j+1])
                min = distances[i][j+1];
            if(min > distances[i+1][j])
                min = distances[i+1][j];
            distances[i+1][j+1] = dist + min;
        }
    }

    dist = distances[xsize][ysize];

    for(i = 0; i < xsize + 1; ++i)
        free(distances[i]);
    free(distances);

    return dist;
}

//int *dtw_path(double *x, double *y, int xsize, int ysize, double window_frac)
//{
//    /* DTW distance algorithm based on
//    https://en.wikipedia.org/wiki/Dynamic_time_warping */
//    //const double LARGE_VALUE = 1e30;
//    //const int min_window = abs(xsize - ysize);
//    //int i, j, minj, maxj, window;
//    //double dist, min;
//    //double **distances = malloc((xsize + 1) * sizeof(double *));
//    //for(i = 0; i < xsize + 1; ++i)
//    //    distances[i] = malloc((ysize + 1) * sizeof(double));
//
//    //window = window_frac*ysize;
//    //if(xsize > ysize)
//    //    window = window_frac*xsize;
//
//    //if(window < min_window)
//    //    window = min_window;
//
//    //for(i = 0; i <= xsize; ++i)
//    //    for(j = 0; j <= ysize; ++j)
//    //        distances[i][j] = LARGE_VALUE;
//    //distances[0][0] = 0.0;
//
//    //for(i = 0; i < xsize; ++i)
//    //{
//    //    minj = i - window;
//    //    if(minj < 0)
//    //        minj = 0;
//    //    maxj = i + window;
//    //    if(maxj > ysize)
//    //        maxj = ysize;
//    //    for(j = minj; j < maxj; ++j)
//    //    {
//    //        dist = fabs(x[i] - y[j]);
//    //        min = distances[i][j];
//    //        if(min > distances[i][j+1])
//    //            min = distances[i][j+1];
//    //        if(min > distances[i+1][j])
//    //            min = distances[i+1][j];
//    //        distances[i+1][j+1] = dist + min;
//    //    }
//    //}
//
//    //dist = distances[xsize][ysize];
//
//    //for(i = 0; i < xsize + 1; ++i)
//    //    free(distances[i]);
//    //free(distances);
//
//    //return dist;
//
//    int i, j;
//    int *path;
//    path = malloc((xsize + ysize)*sizeof(int)*2);
//    //int **path = malloc((xsize + ysize) * sizeof(int *));
//    //for(i = 0; i < xsize + ysize; ++i)
//    //    path[i] = malloc(2 * sizeof(int));
//    for(i = 0; i < (xsize + ysize); ++i)
//        for(j = 0; j < 2; ++j)
//            path[i*2+j] = i;
//    return path;
//}

int *dtw_path(double *x, double *y, int xsize, int ysize, double window_frac)
{
    const double LARGE_VALUE = 1e30;
    const int min_window = abs(xsize - ysize);
    int i, j, k, minj, maxj, window;
    double dist, min;
    double **distances = malloc((xsize + 1) * sizeof(double *));
    for(i = 0; i < xsize + 1; ++i)
        distances[i] = malloc((ysize + 1) * sizeof(double));

    window = window_frac*ysize;
    if(xsize > ysize)
        window = window_frac*xsize;

    if(window < min_window)
        window = min_window;

    for(i = 0; i <= xsize; ++i)
        for(j = 0; j <= ysize; ++j)
            distances[i][j] = LARGE_VALUE;
    distances[0][0] = 0.0;

    for(i = 0; i < xsize; ++i)
    {
        minj = i - window;
        if(minj < 0)
            minj = 0;
        maxj = i + window;
        if(maxj > ysize)
            maxj = ysize;
        for(j = minj; j < maxj; ++j)
        {
            dist = fabs(x[i] - y[j]);
            min = distances[i][j];
            if(min > distances[i][j+1])
                min = distances[i][j+1];
            if(min > distances[i+1][j])
                min = distances[i+1][j];
            distances[i+1][j+1] = dist + min;
        }
    }

    /* Backtrack to compute path */

    int *path = malloc((xsize + ysize + 1)*sizeof(int)*2);
    i = xsize;
    j = ysize;
    path[1] = xsize - 1;
    path[2] = ysize - 1;
    k = 2;
    while(i > 1 || j > 1)
    {
        if(i == 1) {
            --j;
        } else if(j == 1) {
            --i;
        } else {
            min = distances[i - 1][j - 1];
            if(distances[i - 1][j] < min)
                min = distances[i - 1][j];
            if(distances[i][j - 1] < min)
                min = distances[i][j - 1];

            if(distances[i - 1][j - 1] == min) {
                --i;
                --j;
            } else if(distances[i - 1][j] == min) {
                --i;
            } else {
                --j;
            }
        }
        path[k*2-1] = i - 1;
        path[k*2] = j - 1;
        ++k;
    }
    path[k*2-1] = 0;
    path[k*2] = 0;
    path[0] = k - 1;

    dist = distances[xsize][ysize];

    for(i = 0; i < xsize + 1; ++i)
        free(distances[i]);
    free(distances);

    return path;
}
