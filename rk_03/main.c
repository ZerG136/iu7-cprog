#include "word.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"

int main(void)
{
    char **words;
    size_t words_len;
    size_t words_capacity;
    size_t *words_count;

    FILE *in_file = fopen(IN_FILE, "r");
    if (in_file == NULL)
        return EACCES;

    int rc = fscan_words_with_count(in_file, &words, &words_len, &words_capacity, &words_count);

    fclose(in_file);
    if (rc)
        return rc;

    if (words_len == 0)
    {
        destroy_words_with_count(words, words_len, words_count);
        return EIO;
    }

    bubble_sort_words_with_count(words, words_len, words_count);

    FILE* out_file = fopen(OUT_FILE, "w");
    if (out_file == NULL)
    {
        destroy_words_with_count(words, words_len, words_count);
        return EACCES;
    }

    fprint_words_with_count(out_file, words, words_len, words_count);

    fclose(out_file);

    destroy_words_with_count(words, words_len, words_count);

    return EXIT_SUCCESS;
}
