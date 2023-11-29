// Copyright Toma Ariciu 312CAb 2023-2024
#pragma once

struct matrix {
	int n, m, sum;
	int **mat;
};

void swap(int *x, int *y);
int create_matrix(int n, int m, struct matrix *curr_matrix);
int read_matrix(struct matrix *curr_matrix);
void print_matrix(struct matrix *curr_matrix);
void print_dimensions(struct matrix *curr_matrix);
void copy_matrix(struct matrix *curr_matrix, struct matrix *new_matrix);
int transpose_matrix(struct matrix *curr_matrix);
int crop_matrix(struct matrix *curr_matrix, int n, int m,
				int *lines, int *columns);
void delete_matrix(struct matrix *curr_matrix);
