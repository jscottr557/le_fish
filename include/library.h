#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#ifndef LIBRARY_H
#define LIBRARY_H

#define WORD_MAX_LEN 20

typedef char word_t[WORD_MAX_LEN + 1];

int count_words(char *filename);

word_t *read_library(char *filename);

int search_library(char *word, word_t *library, int word_count);

#endif
