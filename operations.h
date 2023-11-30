// Copyright Toma Ariciu 312CAb 2023-2024
#pragma once

int multiply_matrix(struct matrix *matrix1, struct matrix *matrix2,
					struct matrix *result);
int merge_sort(struct matrix **array, int left, int right);
int binary_exponentiation(struct matrix *curr_matrix, int power);
int compute_matrix(struct matrix *a[4], struct matrix *b[4],
				   struct matrix *m[7], struct matrix *aux1,
				   struct matrix *aux2);
int strassen(struct matrix *matrix1, struct matrix *matrix2,
			 struct matrix *result);
int build_blocks(struct matrix *block[], int n, int dim);
int build_aux(struct matrix *aux1, struct matrix *aux2, int dim);
void initialize_block(struct matrix *curr_matrix, struct matrix *block,
					  int x, int y, int dim);
