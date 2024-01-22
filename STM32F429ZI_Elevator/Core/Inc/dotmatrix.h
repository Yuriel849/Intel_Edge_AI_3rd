#ifndef _DOTMATRIX_H_
#define _DOTMATRIX_H_

#include "main.h"

void write_column_data(int col);
void write_row_data(unsigned char data);
int dotmatrix_main_test(void);
int scroll_num_test(void);
void upper_elevator(int src_floor, int dest_floor);

#endif /* _DOTMATRIX_H_ */
