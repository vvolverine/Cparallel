#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    char mode[2000][1000];
    float timeRange[10000];
    float res[33];
    timeRange[0] = 0.1;
    timeRange[1] = -0.1;
    float dd = 1000.0;
    char flag = 0;
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    #pragma omp parallel for
    for (int a = 0; a < 2000; a++)
    {
        for (int b = -500; b < 500; b++)
        {
            for (int t = 2; t < 10000; t++)
            {
                timeRange[t] = 1 - (a/dd) * timeRange[t-1] * timeRange[t-1] - (b/dd) * timeRange[t-2];
                if (fabs(timeRange[t]) > 5)
                {
                    flag = 1;
                    break;
                }
            }
            for (int i = 9700; i < 9733; i++)
            {
                if (flag == 1)
                {
                    mode[a][b+500] = 0;
                    //fprintf(f, "%4d", 0);
                    flag = 0;
                    break;
                }
                if (i == 9732)
                {
                    mode[a][b+500] = 33;
                    //fprintf(f, "%4d", 33);
                    break;
                }
                if (fabs(timeRange[i+1] - timeRange[9700]) < 1e-5)
                {
                    mode[a][b+500] = i - 9700 + 1;
                    //fprintf(f, "%4d", i - 9700 + 1);
                    break;
                }
            }
        }
        //fprintf(f, "\n");
    }
    for (int a = 0; a < 2000; a++)
    {
        for (int b = 0; b < 1000; b++)
        {
            fprintf(f, "%4d", mode[a][b]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Hello world!\n");
    return 0;
}
