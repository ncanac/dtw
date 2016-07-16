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

double dtw_path(double *x, double *y, int xsize, int ysize, double window_frac)
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

//void dtw_path(double *x, double *y, int xsize, int ysize, double window_frac
//              int *path, int *path_size)
//double dtw_path(double *x, double *y, int xsize, int ysize, double window_frac)
//{
//    const double LARGE_VALUE = 1e30;
//    const int min_window = abs(xsize - ysize);
//    int i, j, k, minj, maxj, window;
//    double dist, min;
//    double **distances = malloc((xsize + 1) * sizeof(double *));
//    for(i = 0; i < xsize + 1; ++i)
//        distances[i] = malloc((ysize + 1) * sizeof(double));
//    //double **path = malloc((xsize + ysize) * sizeof(int *));
//    //for(i = i; i < xsize + ysize; ++i)
//    //    path[i] = malloc(2 * sizeof(int));
//
//    window = window_frac*ysize;
//    if(xsize > ysize)
//        window = window_frac*xsize;
//
//    if(window < min_window)
//        window = min_window;
//
//    for(i = 0; i <= xsize; ++i)
//        for(j = 0; j <= ysize; ++j)
//            distances[i][j] = LARGE_VALUE;
//    distances[0][0] = 0.0;
//
//    for(i = 0; i < xsize; ++i)
//    {
//        minj = i - window;
//        if(minj < 0)
//            minj = 0;
//        maxj = i + window;
//        if(maxj > ysize)
//            maxj = ysize;
//        for(j = minj; j < maxj; ++j)
//        {
//            dist = fabs(x[i] - y[j]);
//            min = distances[i][j];
//            if(min > distances[i][j+1])
//                min = distances[i][j+1];
//            if(min > distances[i+1][j])
//                min = distances[i+1][j];
//            distances[i+1][j+1] = dist + min;
//        }
//    }
//
//    /* Backtrack to compute path */
//
//    //path[0][0] = xsize - 1;
//    //path[0][1] = ysize - 1;
//    //i = xsize;
//    //j = ysize;
//    //k = 1;
//    //while(i > 1 && j > 1)
//    //{
//    //    if(i == 1)
//    //    {
//    //        --j;
//    //    }
//    //    else if(j == 1)
//    //    {
//    //        --i;
//    //    }
//    //    else
//    //    {
//    //        min = distances[i - 1][j - 1];
//    //        if(distances[i - 1][j] < min)
//    //            min = distances[i - 1][j];
//    //        if(distances[i][j - 1] < min)
//    //            min = distances[i][j - 1]
//
//    //        if(distances[i - 1][j] == min)
//    //        {
//    //            --i;
//    //        }
//    //        else if(distances[i][j - 1] == min)
//    //        {
//    //            --j;
//    //        }
//    //        else
//    //        {
//    //            --i;
//    //            --j;
//    //        }
//    //    }
//    //    path[k][0] = i - 1;
//    //    path[k][1] = j - 1;
//    //    ++k;
//    //}
//    //path[k][0] = 0;
//    //path[k][1] = 0;
//    //++k;
//
//    //*path_size = k;
//
//    dist = distances[xsize][ysize];
//
//    for(i = 0; i < xsize + 1; ++i)
//        free(distances[i]);
//    free(distances);
//    //for(i = i; i < xsize + ysize; ++i)
//    //    free(path[i]);
//    //free(path);
//
//    return dist;
//}
