// Copyright Toma Ariciu 312CAb 2023-2024
#pragma once

int valid_index(int index, int no_matrices);
int read_command(int *no_matrices, int *array_size, struct matrix ***array);
void print_dim_command(int no_matrices, struct matrix **array);
void print_command(int no_matrices, struct matrix **array);
int crop_command(int no_matrices, struct matrix ***array);
int multiply_command(int *no_matrices, int *array_size, struct matrix ***array);
int sort_command(int no_matrices, struct matrix **array);
int transpose_command(int no_matrices, struct matrix **array);
int exponentiation_command(int no_matrices, struct matrix **array);
int remove_command(int *no_matrices, int *array_size, struct matrix ***array);
void quit_command(int no_matrices, struct matrix **array);
int strassen_command(int *no_matrices, int *array_size, struct matrix ***array);
void exit_program(int no_matrices, struct matrix **array);
