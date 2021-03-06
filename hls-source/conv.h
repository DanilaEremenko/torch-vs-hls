#ifndef LAB4_1_IO_H_
#define LAB4_1_IO_H_
#include <stdlib.h>
#define EXPANDED_HEIGHT 3332
#define EXPANDED_WIDTH 5721
#define CONV_SIZE 3
#define TARGET_HEIGHT EXPANDED_HEIGHT - (CONV_SIZE - 1)
#define TARGET_WIDTH EXPANDED_WIDTH - (CONV_SIZE - 1)

typedef float data_sc;
void conv(
	data_sc input_img[EXPANDED_HEIGHT][EXPANDED_WIDTH],
	data_sc output_img[TARGET_HEIGHT][TARGET_WIDTH],
	data_sc conv_matrix[CONV_SIZE][CONV_SIZE]);

#endif
