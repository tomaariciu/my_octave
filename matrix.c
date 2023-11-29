// Copyright Toma Ariciu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#define MOD 10007

void swap(int *x, int *y)
{
	(*x) = (*x) ^ (*y);
	(*y) = (*y) ^ (*x);
	(*x) = (*x) ^ (*y);
}

int create_matrix(int n, int m, struct matrix *curr_matrix)
{
	curr_matrix->n = n;
	curr_matrix->m = m;
	curr_matrix->sum = 0;
	curr_matrix->mat = (int **)malloc(n * sizeof(int *));
	if (!curr_matrix->mat)
		return -1;
	for (int i = 0; i < n; i++) {
		curr_matrix->mat[i] = (int *)malloc(m * sizeof(int));
		if (!curr_matrix->mat[i]) {
			for (int j = 0; j < i; j++)
				free(curr_matrix->mat[j]);
			free(curr_matrix->mat);
			return -1;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			curr_matrix->mat[i][j] = 0;
	return 0;
}

int read_matrix(struct matrix *curr_matrix)
{
	int n, m;
	scanf("%d %d", &n, &m);
	if (create_matrix(n, m, curr_matrix) != 0) {
		delete_matrix(curr_matrix);
		return -1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &curr_matrix->mat[i][j]);
	return 0;
}

void print_matrix(struct matrix *curr_matrix)
{
	for (int i = 0; i < curr_matrix->n; i++) {
		for (int j = 0; j < curr_matrix->m; j++)
			printf("%d ", curr_matrix->mat[i][j]);
		printf("\n");
	}
}

void print_dimensions(struct matrix *curr_matrix)
{
	printf("%d %d\n", curr_matrix->n, curr_matrix->m);
}

void copy_matrix(struct matrix *curr_matrix, struct matrix *new_matrix)
{
	for (int i = 0; i < new_matrix->n; i++)
		for (int j = 0; j < new_matrix->m; j++)
			new_matrix->mat[i][j] = curr_matrix->mat[i][j];
}

int transpose_matrix(struct matrix *curr_matrix)
{
	struct matrix *new_matrix = (struct matrix *)malloc(sizeof(struct matrix));
	if (!new_matrix)
		return -1;
	if (create_matrix(curr_matrix->n, curr_matrix->m, new_matrix) != 0) {
		free(new_matrix);
		return -1;
	}
	copy_matrix(curr_matrix, new_matrix);
	delete_matrix(curr_matrix);
	swap(&curr_matrix->n, &curr_matrix->m);
	if (create_matrix(curr_matrix->n, curr_matrix->m, curr_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	for (int i = 0; i < curr_matrix->n; i++)
		for (int j = 0; j < curr_matrix->m; j++)
			curr_matrix->mat[i][j] = new_matrix->mat[j][i];
	delete_matrix(new_matrix);
	free(new_matrix);
	return 0;
}

int crop_matrix(struct matrix *curr_matrix, int n, int m,
				int *lines, int *columns)
{
	struct matrix *new_matrix = (struct matrix *)malloc(sizeof(struct matrix));
	if (!new_matrix)
		return -1;
	if (create_matrix(curr_matrix->n, curr_matrix->m, new_matrix) != 0) {
		free(new_matrix);
		return -1;
	}
	copy_matrix(curr_matrix, new_matrix);
	delete_matrix(curr_matrix);
	if (create_matrix(n, m, curr_matrix) != 0) {
		delete_matrix(new_matrix);
		free(new_matrix);
		return -1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			curr_matrix->mat[i][j] = new_matrix->mat[lines[i]][columns[j]];
	delete_matrix(new_matrix);
	free(new_matrix);
	return 0;
}

void delete_matrix(struct matrix *curr_matrix)
{
	for (int i = 0; i < curr_matrix->n; i++)
		free(curr_matrix->mat[i]);
	free(curr_matrix->mat);
}
