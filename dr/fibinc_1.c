#include <stdio.h>
#include <stdbool.h>

int main(){
	int q;
	scanf("%d", &q);
	int arr[q + 1];
	bool is_null_arr = true;
	for(int i = 0; i < q; ++i){
		scanf("%d", &arr[i]);
		if(arr[i] == 1){
			is_null_arr = false;
		}
	}
	arr[q] = 0;

	if(is_null_arr){
		arr[0] = 1;
	} else {
		bool k = true;
		for(int i = 0; i < q + 1; ++i){
			if(arr[i] == 1 && k){
				arr[i] = 0;
				if(i < q){
					if(arr[i + 1] != 1){
						arr[i + 1] = 1;
						k = false;
					}
				} else {
					arr[i] = 1;
				}
			} else if(i < q && arr[i + 1] == 1){
				arr[i] = 0;
				k = true;
			} else if(!k){
				break;
			}
		}
	}
    
    if(arr[q] == 0){
        for(int i = 0; i < q; ++i){
            printf("%d ", arr[i]);
        }
    } else {
        for(int i = 0; i < q + 1; ++i){
            printf("%d ", arr[i]);
        }
    }


	return 0;
}