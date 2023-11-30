// Copyright Toma Ariciu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "allocation.h"
#include "operations.h"
#define MOD 10007

// Inmultirea a doua matrice
int multiply_matrix(struct matrix *matrix1, struct matrix *matrix2,
					struct matrix *result)
{
	// Aloc o matrice auxiliara
	struct matrix *aux = (struct matrix *)malloc(sizeof(struct matrix));
	if (!aux)
		return -1;
	if (create_matrix(matrix1->n, matrix2->m, aux) != 0) {
		free(aux);
		return -1;
	}
	// Calculez rezultatul inmultirii
	for (int i = 0; i < aux->n; i++) {
		for (int j = 0; j < aux->m; j++) {
			for (int k = 0; k < matrix1->m; k++) {
				aux->mat[i][j] += matrix1->mat[i][k] * matrix2->mat[k][j];
				aux->mat[i][j] %= MOD;
			}
			if (aux->mat[i][j] < 0)
				aux->mat[i][j] += MOD;
		}
	}
	// Copiez rezultatul inmultirii in matricea corespunzatoare
	// si eliberez auxiliara
	copy_matrix(aux, result);
	delete_matrix(aux);
	free(aux);
	return 0;
}

// Suma a doua matrice
void add_matrix(struct matrix *matrix1, struct matrix *matrix2,
				struct matrix *result, int sign)
{
	for (int i = 0; i < result->n; i++) {
		for (int j = 0; j < result->m; j++) {
			result->mat[i][j] = (matrix1->mat[i][j] +
								 sign * matrix2->mat[i][j]) % MOD;
			if (result->mat[i][j] < 0)
				result->mat[i][j] += MOD;
		}
	}
}

// Algoritmul de sortare a matricelor
int merge_sort(struct matrix **array, int left, int right)
{
	struct matrix **aux = (struct matrix **)malloc((right - left + 1) *
												   sizeof(struct matrix *));
	if (!aux)
		return -1;
	// Impart array-ul in doua jumatati
	int mid = (left + right) / 2;
	int i = left, j = mid + 1, k = 0;
	if (left == right) {
		free(aux);
		return 0;
	}
	// Sortez fiecare jumatate
	if (merge_sort(array, left, mid) != 0) {
		free(aux);
		return -1;
	}
	if (merge_sort(array, mid + 1, right) != 0) {
		free(aux);
		return -1;
	}
	// Unesc cele doua jumatati
	while (i <= mid || j <= right) {
		if (j > right || (i <= mid && array[i]->sum <= array[j]->sum)) {
			aux[k] = array[i];
			i++;
		} else {
			aux[k] = array[j];
			j++;
		}
		k++;
	}
	for (i = 0; i < k; i++)
		array[left + i] = aux[i];
	free(aux);
	return 0;
}

// Exponentierea rapida
int binary_exponentiation(struct matrix *curr_matrix, int power)
{
	// Creez o matrice pentru rezultat
	struct matrix *aux = (struct matrix *)malloc(sizeof(struct matrix));
	if (!aux || create_matrix(curr_matrix->n, curr_matrix->m, aux) != 0)
		return -1;
	// Initializez cu matricea identitate
	for (int i = 0; i < curr_matrix->n; i++)
		aux->mat[i][i] = 1;
	// Algoritmul de exponentiere in timp logaritmic
	while (power) {
		if (power & 1)
			multiply_matrix(aux, curr_matrix, aux);
		multiply_matrix(curr_matrix, curr_matrix, curr_matrix);
		power >>= 1;
	}
	// Copiez rezultatul din matricea auxiliara
	copy_matrix(aux, curr_matrix);
	delete_matrix(aux);
	free(aux);
	return 0;
}

// Calcularea matricelor pentru Strassen
int compute_matrix(struct matrix *a[4], struct matrix *b[4],
				   struct matrix *m[7], struct matrix *aux1,
				   struct matrix *aux2)
{
	// a si b sunt cele 4 matrice blocuri
	// aux1 si aux2 sunt folosite pentru a calcula
	// cele 7 matrice auxiliare
	add_matrix(a[0], a[3], aux1, 1);
	add_matrix(b[0], b[3], aux2, 1);
	if (strassen(aux1, aux2, m[0]) != 0)
		return -1;
	add_matrix(a[2], a[3], aux1, 1);
	copy_matrix(b[0], aux2);
	if (strassen(aux1, aux2, m[1]) != 0)
		return -1;
	copy_matrix(a[0], aux1);
	add_matrix(b[1], b[3], aux2, -1);
	if (strassen(aux1, aux2, m[2]) != 0)
		return -1;
	copy_matrix(a[3], aux1);
	add_matrix(b[2], b[0], aux2, -1);
	if (strassen(aux1, aux2, m[3]) != 0)
		return -1;
	add_matrix(a[0], a[1], aux1, 1);
	copy_matrix(b[3], aux2);
	if (strassen(aux1, aux2, m[4]) != 0)
		return -1;
	add_matrix(a[2], a[0], aux1, -1);
	add_matrix(b[0], b[1], aux2, 1);
	if (strassen(aux1, aux2, m[5]) != 0)
		return -1;
	add_matrix(a[1], a[3], aux1, -1);
	add_matrix(b[2], b[3], aux2, 1);
	if (strassen(aux1, aux2, m[6]) != 0)
		return -1;
	return 0;
}

int strassen(struct matrix *matrix1, struct matrix *matrix2,
			 struct matrix *result)
{
	struct matrix *a[4], *b[4], *m[7], *aux1, *aux2;
	int new_dim = result->n / 2;
	// Conditia de oprire: marimea matricei de 1
	if (result->n == 1) {
		result->mat[0][0] = (matrix1->mat[0][0] * matrix2->mat[0][0]) % MOD;
		if (result->mat[0][0] < 0)
			result->mat[0][0] += MOD;
		return 0;
	}
	if (build_blocks(a, 4, new_dim) != 0)
		return -1;
	if (build_blocks(b, 4, new_dim) != 0) {
		delete_block(a, 4);
		return -1;
	}
	if (build_blocks(m, 7, new_dim) != 0) {
		delete_block(a, 4);
		delete_block(b, 4);
		return -1;
	}
	aux1 = (struct matrix *)malloc(sizeof(struct matrix));
	if (!aux1) {
		delete_block(a, 4);
		delete_block(b, 4);
		delete_block(m, 7);
		return -1;
	}
	aux2 = (struct matrix *)malloc(sizeof(struct matrix));
	if (!aux2) {
		delete_block(a, 4);
		delete_block(b, 4);
		delete_block(m, 7);
		free(aux1);
		return -1;
	}
	if (build_aux(aux1, aux2, new_dim) != 0) {
		delete_block(a, 4);
		delete_block(b, 4);
		delete_block(m, 7);
		free(aux1);
		free(aux2);
		return -1;
	}
	for (int i = 0; i < 4; i++) {
		int x = (i / 2) * new_dim, y = (i % 2) * new_dim;
		initialize_block(matrix1, a[i], x, y, new_dim);
		initialize_block(matrix2, b[i], x, y, new_dim);
	}
	if (compute_matrix(a, b, m, aux1, aux2) != 0) {
		deallocate_strassen(a, b, m, aux1, aux2);
		return -1;
	}
	// Calculez rezultatul in functie de matricele auxiliare
	for (int i = 0; i < new_dim; i++) {
		for (int j = 0; j < new_dim; j++) {
			int i2 = i + new_dim, j2 = j + new_dim;
			result->mat[i][j] = m[0]->mat[i][j] + m[3]->mat[i][j] -
								m[4]->mat[i][j] + m[6]->mat[i][j];
			result->mat[i][j2] = m[2]->mat[i][j] + m[4]->mat[i][j];
			result->mat[i2][j] = m[1]->mat[i][j] + m[3]->mat[i][j];
			result->mat[i2][j2] = m[0]->mat[i][j] - m[1]->mat[i][j] +
								  m[2]->mat[i][j] + m[5]->mat[i][j];
		}
	}
	for (int i = 0; i < result->n; i++) {
		for (int j = 0; j < result->m; j++) {
			result->mat[i][j] %= MOD;
			if (result->mat[i][j] < 0)
				result->mat[i][j] += MOD;
		}
	}
	deallocate_strassen(a, b, m, aux1, aux2);
	return 0;
}

// Alocarea matricelor auxiliare
int build_blocks(struct matrix *block[], int n, int dim)
{
	for (int i = 0; i < n; i++) {
		block[i] = (struct matrix *)malloc(sizeof(struct matrix));
		if (!block[i]) {
			for (int j = 0; j < i; j++) {
				delete_matrix(block[j]);
				free(block[j]);
			}
			return -1;
		}
		if (create_matrix(dim, dim, block[i]) != 0) {
			for (int j = 0; j < i; j++) {
				delete_matrix(block[j]);
				free(block[j]);
			}
			free(block[i]);
			return -1;
		}
	}
	return 0;
}

int build_aux(struct matrix *aux1, struct matrix *aux2, int dim)
{
	if (create_matrix(dim, dim, aux1) != 0)
		return -1;
	if (create_matrix(dim, dim, aux2) != 0) {
		delete_matrix(aux1);
		return -1;
	}
	return 0;
}

// Initializarea matricelor blocuri
void initialize_block(struct matrix *curr_matrix, struct matrix *block,
					  int x, int y, int dim)
{
	for (int i = x; i < x + dim; i++)
		for (int j = y; j < y + dim; j++)
			block->mat[i - x][j - y] = curr_matrix->mat[i][j];
}
