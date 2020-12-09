#include <stdio.h>
#include <math.h>

#define EPS 0.01

double result(){
    int i = 0;
    double fibPrev = 1.0 ;
    double fibn = 1.0;
    double fibPost = 2.0
    double fib = 2.0;
    while ((fabs( (fibPost/fibn) - (fibn/fibPrev ))) > EPS)
    {
        i++;
        fib = fibPost;
        fibPost = fibPost + fibn;
        fibPrev = fibn;
        fibn = fib;
    }
    printf("Счетчик итераций = %d\n", i);
    return fibPost/fibn;
}

double limit()
{
    return  (1 + sqrt(5))/2;
}

double absolutelyError(double res)
{
    return fabs(limit() - res);
}

double relivateError(double res){
    return absolutelyError(res) / fabs(limit());
}

int main()
{   double res;

    res = result();

    printf("Предел отношения двух последовательных членов: %.50f \n", res);
    printf("Абсолютная погрешность равна: %.50f\nОтносительная погрешность равна: %.50f", absolutelyError(res), relivateError(res));
}
