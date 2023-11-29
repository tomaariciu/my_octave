// Copyright Toma Ariciu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "allocation.h"
#include "operations.h"
#include "commands.h"

int main(void)
{
	char command;
	int no_matrices = 0, array_size = 1, valid_command = 0;
	struct matrix **array = malloc(array_size * sizeof(struct matrix *));
	do {
		scanf("%c", &command);
		valid_command = 0;
		if (command == 'L') {
			valid_command = 1;
			if (read_command(&no_matrices, &array_size, &array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'D') {
			valid_command = 1;
			print_dim_command(no_matrices, array);
		}
		if (command == 'P') {
			valid_command = 1;
			print_command(no_matrices, array);
		}
		if (command == 'C') {
			valid_command = 1;
			if (crop_command(no_matrices, &array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'M') {
			valid_command = 1;
			if (multiply_command(&no_matrices, &array_size, &array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'O') {
			valid_command = 1;
			if (sort_command(no_matrices, array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'T') {
			valid_command = 1;
			if (transpose_command(no_matrices, array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'R') {
			valid_command = 1;
			if (exponentiation_command(no_matrices, array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'F') {
			valid_command = 1;
			if (remove_command(&no_matrices, &array_size, &array) != 0)
				exit_program(no_matrices, array);
		}
		if (command == 'Q') {
			valid_command = 1;
			quit_command(no_matrices, array);
		}
		if (command == 'S') {
			valid_command = 1;
			if (strassen_command(&no_matrices, &array_size, &array) != 0)
				exit_program(no_matrices, array);
		}
		if (valid_command == 0)
			printf("Unrecognized command\n");
		scanf("\n");
	} while (command != 'Q');
	return 0;
}
