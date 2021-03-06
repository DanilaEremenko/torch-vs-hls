#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "conv.h"

#define RUNS 3

data_sc input_img[EXPANDED_HEIGHT][EXPANDED_WIDTH];
data_sc expected_res[TARGET_HEIGHT][TARGET_WIDTH];
data_sc actual_res[TARGET_HEIGHT][TARGET_WIDTH];
data_sc conv_matrix[CONV_SIZE][CONV_SIZE] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

void print_arr(data_sc *arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}

int readmatrix(int rows, int cols, data_sc (*a)[cols], const char *filename)
{

	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
		return 0;

	for (size_t row_i = 0; row_i < rows; ++row_i)
	{
		for (size_t col_i = 0; col_i < cols; ++col_i)
		{
			fscanf(fp, "%f", a[row_i] + col_i);
			// printf("readed [%d][%d] = %f\n", row_i, col_i, *a[row_i]);
		}
	}

	fclose(fp);
	return 1;
}

int assert_matrixes(data_sc matrix_1[TARGET_HEIGHT][TARGET_WIDTH], data_sc matrix_2[TARGET_HEIGHT][TARGET_WIDTH])
{
	for (int row_i = 0; row_i < TARGET_HEIGHT; row_i++)
		for (int col_i = 0; col_i < TARGET_WIDTH; col_i++)
			if (matrix_1[row_i][col_i] != matrix_2[row_i][col_i])
			{
				printf("--------TEST FAILURE-------- EXPECTED[%d][%d] = %f, ACTUAL[%d][%d] = %f\n", row_i, col_i, matrix_1[row_i][col_i], row_i, col_i, matrix_2[row_i][col_i]);
				return 1;
				// }
			}
	// else
	// {
	// 	printf("----------OK---------------- EXPECTED[%d][%d] = %f, ACTUAL[%d][%d] = %f\n", row_i, col_i, matrix_1[row_i][col_i], row_i, col_i, matrix_2[row_i][col_i]);
	// }

	return 0;
}

int test()
{
	struct timespec t0, t1;
	printf("initializing array\n");
	
	if (!readmatrix(EXPANDED_HEIGHT, EXPANDED_WIDTH, &input_img, "../../../../test_data/input.txt"))
	{
		printf("Error while reading input matrix\n");
		return 1;
	}

	if (!readmatrix(TARGET_HEIGHT, TARGET_WIDTH, &expected_res, "../../../../test_data/res.txt"))
	{
		printf("Error while reading expected matrix\n");
		return 1;
	}

	int run_i;
	int cmp_i;

	int mismatches = 0;

	for (run_i = 0; run_i < RUNS; run_i++)
	{

		conv(input_img, actual_res, conv_matrix);

		if (assert_matrixes(expected_res, actual_res))
		{
			mismatches++;
			printf("RUN %d FAILED\n", run_i);
		}
		else
		{
			printf("RUN %d PASSED\n", run_i);
		}
	}

	if (mismatches == 0)
	{
		printf("\n--------TEST PASSED--------\n");
		return 0;
	}
	else
	{
		printf("\n--------TEST FAILED--------\n");
		return 1;
	}
}

int main()
{
	srand(22);
	return test();
}
