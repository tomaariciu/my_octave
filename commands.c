// Copyright Toma Ariciu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "allocation.h"
#include "operations.h"
#include "commands.h"
#define MOD 10007

int valid_index(int index, int no_matrices)
{
	return 0 <= index && index < no_matrices;
}

int read_command(int *no_matrices, int *array_size, struct matrix ***array)
{
	struct matrix *curr_matrix = (struct matrix *)malloc(sizeof(struct matrix));
	if (!curr_matrix)
		return -1;
	if (read_matrix(curr_matrix) != 0) {
		free(curr_matrix);
		return -1;
	}
	if (add_to_array(no_matrices, array_size, array, curr_matrix) != 0) {
		delete_matrix(curr_matrix);
		free(curr_matrix);
		return -1;
	}
	return 0;
}

void print_dim_command(int no_matrices, struct matrix **array)
{
	int index = 0;
	scanf("%d", &index);
	if (!valid_index(index, no_matrices)) {
		printf("No matrix with the given index\n");
		return;
	}
	print_dimensions(array[index]);
}

void print_command(int no_matrices, struct matrix **array)
{
	int index = 0;
	scanf("%d", &index);
	if (!valid_index(index, no_matrices)) {
		printf("No matrix with the given index\n");
		return;
	}
	print_matrix(array[index]);
}

int crop_command(int no_matrices, struct matrix ***array)
{
	int index = 0;
	int n, m, *lines, *columns;
	scanf("%d", &index);
	scanf("%d", &n);
	lines = (int *)malloc(n * sizeof(int));
	if (!lines)
		return -1;
	for (int i = 0; i < n; i++)
		scanf("%d", &lines[i]);
	scanf("%d", &m);
	columns = (int *)malloc(m * sizeof(int));
	if (!columns) {
		free(lines);
		return -1;
	}
	for (int j = 0; j < m; j++)
		scanf("%d", &columns[j]);
	if (!valid_index(index, no_matrices)) {
		printf("No matrix with the given index\n");
		free(lines);
		free(columns);
		return 0;
	}
	if (crop_matrix((*array)[index], n, m, lines, columns) != 0) {
		free(lines);
		free(columns);
		return -1;
	}
	free(lines);
	free(columns);
	return 0;
}

int multiply_command(int *no_matrices, int *array_size, struct matrix ***array)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);
	if (!valid_index(index1, (*no_matrices)) ||
		!valid_index(index2, (*no_matrices))) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if ((*array)[index1]->m != (*array)[index2]->n) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	struct matrix *new_matrix = (struct matrix *)malloc(sizeof(struct matrix));
	if (!new_matrix)
		return -1;
	if (create_matrix((*array)[index1]->n,
					  (*array)[index2]->m, new_matrix) != 0) {
		free(new_matrix);
		return -1;
	}
	if (multiply_matrix((*array)[index1], (*array)[index2],
						new_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	if (add_to_array(no_matrices, array_size, array, new_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	return 0;
}

int sort_command(int no_matrices, struct matrix **array)
{
	if (no_matrices == 0)
		return 0;
	for (int p = 0; p < no_matrices; p++) {
		array[p]->sum = 0;
		for (int i = 0; i < array[p]->n; i++) {
			for (int j = 0; j < array[p]->m; j++) {
				array[p]->sum += array[p]->mat[i][j];
				array[p]->sum %= MOD;
				if (array[p]->sum < 0)
					array[p]->sum += MOD;
			}
		}
	}
	if (merge_sort(array, 0, no_matrices - 1) != 0)
		return -1;
	return 0;
}

int transpose_command(int no_matrices, struct matrix **array)
{
	int index = 0;
	scanf("%d", &index);
	if (!valid_index(index, no_matrices)) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (transpose_matrix(array[index]) != 0)
		return -1;
	return 0;
}

int exponentiation_command(int no_matrices, struct matrix **array)
{
	int index = 0, power = 0;
	scanf("%d %d", &index, &power);
	if (!valid_index(index, no_matrices)) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (power < 0) {
		printf("Power should be positive\n");
		return 0;
	}
	if (array[index]->n != array[index]->m) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	if (binary_exponentiation(array[index], power) != 0)
		return -1;
	return 0;
}

int remove_command(int *no_matrices, int *array_size, struct matrix ***array)
{
	int index = 0;
	scanf("%d", &index);
	if (valid_index(index, (*no_matrices))) {
		if (remove_from_array(no_matrices, array_size, array, index) != 0)
			return -1;
	} else {
		printf("No matrix with the given index\n");
	}
	return 0;
}

void quit_command(int no_matrices, struct matrix **array)
{
	delete_array(no_matrices, array);
	free(array);
}

int strassen_command(int *no_matrices, int *array_size, struct matrix ***array)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);
	if (!valid_index(index1, (*no_matrices)) ||
		!valid_index(index2, (*no_matrices))) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if ((*array)[index1]->m != (*array)[index2]->n) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	struct matrix *new_matrix = (struct matrix *)malloc(sizeof(struct matrix));
	if (!new_matrix)
		return -1;
	if (create_matrix((*array)[index1]->n,
					  (*array)[index2]->m, new_matrix) != 0) {
		free(new_matrix);
		return -1;
	}
	if (strassen((*array)[index1], (*array)[index2], new_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	if (add_to_array(no_matrices, array_size, array, new_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	return 0;
}

void exit_program(int no_matrices, struct matrix **array)
{
	printf("Memory allocation failed.\n");
	delete_array(no_matrices, array);
	free(array);
	exit(-1);
}
