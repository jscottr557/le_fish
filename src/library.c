#include <math.h>
#include <string.h>

#include "../include/library.h"
#include "../include/str_ops.h"

#define DEBUG

int count_words(char *filename) {
  int number_of_words = 0;

  FILE *file = fopen(filename, "r");
  if(file == NULL || ferror(file) != 0) {
    return 0;
  }

  word_t word;
  while(fscanf(file, "%20s", word) != EOF) {
    number_of_words++;
  }

  #ifdef DEBUG
  printf("Number of words: %d\n", number_of_words);
  #endif

  fclose(file);
  return number_of_words;
}

word_t *read_library(char *filename) {
  if(filename == NULL) {
    return NULL;
  }

  word_t *word_list = malloc(count_words(filename) * sizeof(word_t));
  if(word_list == NULL) {
    return NULL;
  }

  FILE *file = fopen(filename, "r");
  if(file == NULL || ferror(file) != 0) {
    return NULL;
  }

  int counter = 0;
  while(fscanf(file, "%20s", word_list[counter]) != EOF) {
    op_str(word_list[counter], &tolower);

    #ifdef DEBUG
    printf("read word: %s\n", word_list[counter]);
    #endif

    counter++;
  }

  fclose(file);
  return word_list;
}


//Returns 0 if word found, positive if not
int search_library(char *word, word_t *library, int word_count) {
  if(word == NULL) {
    return -1;
  }

  int library_pos = 0;
  int word_match = 1;

  while((word_match = strcmp(word, library[library_pos])) &&
         library_pos < word_count) {
    fflush(stdout);
    library_pos++;
  }

  return abs(word_match);
}
