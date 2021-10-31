#include <stdio.h>
#include <string.h>

#include "BKTree.h"

// Return the max integer number
int max_int(int a, int b){

	return a > b ? a : b;
}
// Calculate distance between two strings
int distance(char str1[], char str2[]){

	int i, j, ii, jj,
		strlen1 = strlen(str1), strlen2 = strlen(str2),
		hit_spot_str1 = -1, hit_spot_str2 = -1, hit_length = 0, temp_length, distance;

	if(strlen1 == 0 || strlen2 == 0)
		return strlen1 == 0 ? strlen2 : strlen1;

	for(i = 0; i < strlen1; i++){

		for(j = 0; j < strlen2; j++){

			if(str1[i] == str2[j]){

				if(hit_length == 0){

					hit_spot_str1 = i;
					hit_spot_str2 = j;					
				}

				temp_length = 1;
				ii = i + 1;
				jj = j + 1;

				while(ii != strlen1 && jj != strlen2){

					if(str1[ii] == str2[jj])
						temp_length++;
					else
						break;

					ii++; 
					jj++;
				}

				if(temp_length > hit_length){

					hit_length = temp_length;
					hit_spot_str1 = i;
					hit_spot_str2 = j;
				}
			}
		}
	}

	distance = max_int(hit_spot_str1, hit_spot_str2) + max_int(strlen1 - (hit_spot_str1 + hit_length), strlen2 - (hit_spot_str2 + hit_length));

	//Print Result
	printf("String1 : %s\nString2 : %s\nHit : \"", str1, str2);
	if(hit_length != 0){
		for(i = hit_spot_str1; i < hit_spot_str1 + hit_length; i++)
			printf("%c", str1[i]);
	}
	printf("\"\nHit spot str1 : str1[%d] = '%c'\nHit spot str2 : str2[%d] = '%c'\nHit length = %d\nDistance = %d\n", hit_spot_str1, str1[hit_spot_str1], hit_spot_str2, str2[hit_spot_str2], hit_length, distance);

	return distance;
}

// TEST
// int main(int argc, char** argv){

// 	// char str1[20], str2[20];
// 	// strcpy(str1, "hell"); 
// 	// strcpy(str2, "small");


// 	// for(i = 0; i < strlen(str1); i++){

// 	// 	printf("%c\n", str1[i]);
// 	// }
// 	// printf("Size: %ld\n", strlen(str1));

// 	distance(argv[1], argv[2]);

// 	return 0;
// }