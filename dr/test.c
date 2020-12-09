#include <stdio.h>
#include <math.h>

int main(){
    int k, n;
    scanf("%d %d", &k, &n);

    for(int i = 2; i <= n; ++i){
        int num = i;
        int count = 0;
        double sqrt_val = sqrt(num);
        for (int j = 2; j < sqrt_val + 0.1; ){
            if (num % j == 0){
                ++count;
                num /= j;
            } else {
                ++j;
            }
        }
        if (num > 1){
            ++count;
        }

        if(count == k){
            printf("%d ", i);
        }
    }
    return 0;
}
