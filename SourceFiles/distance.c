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

int min_int(int a, int b){

	return a <= b ? a : b;
}

int distance(char *a, char *b){

	if(a == NULL || b == NULL)
		return -1;

	int strlen_a, strlen_b, i, j;
	strlen_a = strlen(a);
	strlen_b = strlen(b);

	if(strlen_a == 0 || strlen_b == 0)
		return strlen_a == 0 ? strlen_b : strlen_a;

	int array[strlen_a + 1][strlen_b + 1];
	for(i = 0; i < strlen_a + 1; i++)
		array[i][0] = i;
	for(j = 0; j < strlen_b + 1; j++)
		array[0][j] = j;

	for(i = 1; i < strlen_a + 1; i++){

		for(j = 1; j < strlen_b + 1; j++){

			if(a[i-1] == b[j-1])
				array[i][j] = array[i-1][j-1];
			else 
				array[i][j] = min_int(array[i][j-1],min_int(array[i-1][j-1], array[i-1][j])) + 1;
		}
	}

	// PRINT
	// printf("\n        ");
	// for(j = 0; j < strlen_b; j++)
	// 	printf("  %c ", b[j]);
	// printf("\n");
	// for(i = 0; i < strlen_a + 1; i++){
	// 	if(i == 0) 
	// 		printf("    "); 
	// 	else 
	// 		printf("  %c ", a[i-1]);
	// 	for(j = 0; j < strlen_b + 1; j++)
	// 		printf("| %d ", array[i][j]);
	// 	printf("|\n");
	// }
	// printf("\n a = \"%s\", strlen_a = %d \n b = \"%s\", strlen_b = %d \n\n distance = %d\n", a, strlen_a, b, strlen_b, array[strlen_a][strlen_b]);

	return array[strlen_a][strlen_b];
}

// int main(int argc, char **argv){

// 	distance(argv[1], argv[2]);

// 	return 0;
// }