///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// Project : Assignment_1
// File : 
///////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "distance.h"

int min_int(const int a, const int b){

	return a <= b ? a : b;
}

int edit_distance(const char *a, const char *b){

	if(a == NULL || b == NULL)
		return -1;

	int length_a, length_b, i, j;
	length_a = strlen(a);
	length_b = strlen(b);

	if(length_a == 0 || length_b == 0)
		return length_a == 0 ? length_b : length_a;

	int array[length_a + 1][length_b + 1];
	for(i = 0; i < length_a + 1; i++)
		array[i][0] = i;
	for(j = 0; j < length_b + 1; j++)
		array[0][j] = j;

	for(i = 1; i < length_a + 1; i++){

		for(j = 1; j < length_b + 1; j++){

			if(a[i-1] == b[j-1])
				array[i][j] = array[i-1][j-1];
			else 
				array[i][j] = min_int(array[i][j-1],min_int(array[i-1][j-1], array[i-1][j])) + 1;
		}
	}

	// PRINT RESULTS 
	// printf("\n        ");
	// for(j = 0; j < length_b; j++)
	// 	printf("  %c ", b[j]);
	// printf("\n");
	// for(i = 0; i < length_a + 1; i++){
	// 	if(i == 0) 
	// 		printf("    "); 
	// 	else 
	// 		printf("  %c ", a[i-1]);
	// 	for(j = 0; j < length_b + 1; j++)
	// 		printf("| %d ", array[i][j]);
	// 	printf("|\n");
	// }
	// printf("\n a = \"%s\", length_a = %d \n b = \"%s\", length_b = %d \n\n distance = %d\n", a, length_a, b, length_b, array[length_a][length_b]);

	return array[length_a][length_b];
}

int hamming_distance(const char *a, const char *b){

	if(a == NULL || b == NULL)
		return -1;

	int length_a, length_b, i, dist;
	length_a = strlen(a);
	length_b = strlen(b);

	if(length_a != length_b || length_a == 0 || length_b == 0)
		return 1;

	dist = 0;
	for(i = 0; i < length_a; i++){

		if(a[i] != b[i])
			dist++;
	}

	return dist;
}

int exact_match(const char *a, const char *b){

	if(a == NULL || b == NULL)
		return -1;

	return strcmp(a, b) == 0 ? 0 : 1;
}

// int main(int argc, char **argv){
// 	distance(argv[1], argv[2]);
// 	return 0;
// }