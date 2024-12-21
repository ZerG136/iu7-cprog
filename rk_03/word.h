#ifndef WORD_H__
#define WORD_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define _POSIX_C_SOURCE 200809L

#define INIT_SIZE 16

void destroy_words_with_count(char **words, size_t words_len, size_t *words_count);

int fscan_words_with_count(FILE *file, char ***words, size_t *words_len, size_t *words_capacity, size_t **words_count);

void bubble_sort_words_with_count(char **words, size_t words_len, size_t *words_count);

void fprint_words_with_count(FILE *file, char **words, size_t words_len, size_t *words_count);

#endif  //WORD_H__
