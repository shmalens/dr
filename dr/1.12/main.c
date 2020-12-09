#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 10
#define m 10

int main()
{
    int **a = (int **)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) {
        a[i] = (int *)malloc(sizeof(int) * m);
    }
    int j,i;
    int t=1;
    i=0;
    int v=0;
    int s=0;
    int r=1;
    int l=1,c=0,d=0;
    int f;
    f=n;
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < m; ++j) {
            a[k][j] = rand() % 100;
        }
    }

    while (t<=n*n)
    {
        //выводим справа на лево
        for (j=s;j<f;++j)
        {
            printf("%4d", a[i][j]);
//            a[i][j]=rand() % 100;
            ++t;

        }v=j-1;
        --j;
        //выводим с верху вниз
        if (t<=n*n)
        {
            for (i=r;i<f;++i)
            {
                printf("%4d", a[i][j]);
//                a[i][j]=rand() % 100;
                ++t;
            }l=i-1;
            --i;
        }
        //выводим с лева на право
        if (t<=n*n)
        {
            for (j=v-1;j>=c;--j)
            {
                printf("%4d", a[i][j]);
//                a[i][j]=rand() % 100;
                ++t;
            }
        }
        if (t<=n*n)
        {
            //выводим с низу верх
            for (i=l-1;i>d;--i)
            {
                printf("%4d", a[i][j]);
//                a[i][j+1]=rand() % 100;
                ++t;
            }
        }
        //уменшаем параметры матрицы(что бы числа шли внутрь а не заполнялись поверх тех которы уже заполнены)
        --f;

        ++s;
        ++r;
        ++c;
        ++d;
        ++i;
    }
    printf("\n\n");

    //вывод массива
    for (i=0;i<n;++i)
    {
        for (j=0;j<n;++j)
        {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    for (int k = 0; k < n; ++k) {
        free(a[k]);
    }
    free(a);

    return 0;
}