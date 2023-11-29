// Copyright Toma Ariciu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "allocation.h"
#define MOD 10007

int double_array_size(int *array_size, struct matrix ***array)
{
	struct matrix **aux;
	(*array_size) *= 2;
	aux = (struct matrix **)
		  realloc((*array), (*array_size) * sizeof(struct matrix *));
	if (!aux)
		return -1;
	(*array) = aux;
	return 0;
}

int half_array_size(int *array_size, struct matrix ***array)
{
	if ((*array_size) == 1)
		return 0;
	struct matrix **aux;
	(*array_size) /= 2;
	aux = (struct matrix **)
		  realloc((*array), (*array_size) * sizeof(struct matrix *));
	if (!aux)
		return -1;
	(*array) = aux;
	return 0;
}

int add_to_array(int *no_matrices, int *array_size, struct matrix ***array,
				 struct matrix *new_matrix)
{
	if ((*no_matrices) + 1 > (*array_size)) {
		if (double_array_size(array_size, array) != 0)
			return -1;
	}
	(*array)[(*no_matrices)] = new_matrix;
	(*no_matrices)++;
	return 0;
}

int remove_from_array(int *no_matrices, int *array_size,
					  struct matrix ***array, int index)
{
	(*no_matrices)--;
	delete_matrix((*array)[index]);
	free((*array)[index]);
	for (int i = index; i < (*no_matrices); i++)
		(*array)[i] = (*array)[i + 1];
	if ((*no_matrices) < (*array_size) / 2) {
		if (half_array_size(array_size, array) != 0)
			return -1;
	}
	return 0;
}

void delete_array(int no_matrices, struct matrix **array)
{
	for (int i = 0; i < no_matrices; i++) {
		delete_matrix(array[i]);
		free(array[i]);
	}
}

void delete_block(struct matrix *block[], int n)
{
	for (int i = 0; i < n; i++) {
		delete_matrix(block[i]);
		free(block[i]);
	}
}

void deallocate_strassen(struct matrix *a[4], struct matrix *b[4],
						 struct matrix *m[7], struct matrix *aux1,
						 struct matrix *aux2)
{
	delete_block(a, 4);
	delete_block(b, 4);
	delete_block(m, 7);
	delete_matrix(aux1);
	delete_matrix(aux2);
	free(aux1);
	free(aux2);
}
