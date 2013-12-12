#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main()
{
    int N = 100;
    float dt = 0.01;
    float x[N], t[N];
    #pragma omp parallel for
        for (int i = 0; i < N; i++)
        {
            t[i] = i * dt;
            x[i] = sin(2 * M_PI * t[i]);
        }
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int j = 0; j < N; j++)
    {
        fprintf(f, "%f, %f\n", t[j], x[j]);
    }
    fclose(f);
    return 0;
}
