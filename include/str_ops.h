#include <stdlib.h>

#ifndef STR_OPS_H
#define STR_OPS_H

int lexi_compare(void *, void *);

int strip_punctuation(int letter);

void op_str(char *str, int (*operation)(int letter));

#endif
