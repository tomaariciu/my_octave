// Copyright Toma Ariciu 312CAb 2023-2024
#pragma once

int double_array_size(int *array_size, struct matrix ***array);
int half_array_size(int *array_size, struct matrix ***array);
int add_to_array(int *no_matrices, int *array_size, struct matrix ***array,
				 struct matrix *new_matrix);
int remove_from_array(int *no_matrices, int *array_size, struct matrix ***array,
					  int index);
void delete_array(int no_matrices, struct matrix **array);
void delete_block(struct matrix *block[], int n);
void deallocate_strassen(struct matrix *a[4], struct matrix *b[4],
						 struct matrix *m[7], struct matrix *aux1,
						 struct matrix *aux2);
