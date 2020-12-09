#include <stdio.h>
#include <stdbool.h>

int main(){
	int n, m;
	scanf("%d %d", &m, &n);
	int max_of_row[m];
	int min_of_column[n];
	
	int min[n];
	for(int i = 0; i < m; ++i){
		int max, max_ind;

		for(int j = 0; j < n; ++j){
			int num;
			scanf("%d", &num);

			if(i == 0){
				min[j] = num;
				min_of_column[j] = i;
			} else {
				if(num < min[j]){
					min[j] = num;
					min_of_column[j] = i;
				}
			}

			if(j == 0){
				max = num;
				max_ind = j;
			} else {
				if(num > max){
					max = num;
					max_ind = j;
				}
			}
			max_of_row[i] = max_ind;
		}
	}

	bool is_find_saddle = false;

	for(int i = 0; i < n; ++i){
		if(max_of_row[min_of_column[i]] == i){
			printf("%d %d", min_of_column[i], max_of_row[min_of_column[i]]);
			is_find_saddle = true;
			break;
		}
	}

	if(!is_find_saddle){
	    printf("none");
	}

	return 0;
}