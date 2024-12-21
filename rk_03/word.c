#include "word.h"

void destroy_words_with_count(char **words, size_t words_len, size_t *words_count)
{
    for (size_t i = 0; i < words_len; i++)
        free(words[i]);
    free(words);
    free(words_count);
}

int fscan_words_with_count(FILE *file, char ***words, size_t *words_len, size_t *words_capacity, size_t **words_count)
{
    char *data = NULL;
    size_t data_len = 0;

    *words = malloc(sizeof(char *) * INIT_SIZE);
    if (*words == NULL)
        return ENOMEM;

    *words_count = calloc(INIT_SIZE, sizeof(size_t) * INIT_SIZE);
    if (*words_count == NULL)
    {
        free(*words);
        return ENOMEM;
    }

    *words_len = 0;
    *words_capacity = INIT_SIZE;

    int flag;
    size_t ind;

    while (getline(&data, &data_len, file) != -1)
    {
        *strrchr(data, '\n') = '\0';
        if (data[0] == '\0')
        {
            destroy_words_with_count(*words, *words_len, *words_count);
            free(data);
            return EIO;
        }

        flag = 0;
        ind = 0;

        while (ind < *words_len && !flag)
            if (strcmp(data, (*words)[ind++]) == 0)
                flag = 1;

        if (flag)
            (*words_count)[ind - 1]++;
        else
        {
            (*words)[*words_len] = strdup(data);
            if ((*words)[*words_len] == NULL)
            {
                destroy_words_with_count(*words, *words_len, *words_count);
                free(data);
                return ENOMEM;
            }

            (*words_count)[(*words_len)++] = 1;

            if (*words_len >= *words_capacity)
            {
                char **words_buff = realloc(*words, sizeof(char*) * *words_capacity * 2);
                if (words_buff == NULL)
                {
                    destroy_words_with_count(*words, *words_len, *words_count);
                    free(data);
                    return ENOMEM;
                }
                *words = words_buff;

                size_t *count_buff = realloc(*words_count, sizeof(size_t) * *words_capacity * 2);
                if (count_buff == NULL)
                {
                    destroy_words_with_count(*words, *words_len, *words_count);
                    free(data);
                    return ENOMEM;
                }
                *words_count = count_buff;

                *words_capacity *= 2;
            }
        }
    }

    free(data);

    return EXIT_SUCCESS;
}

static void swap_strings(char **str1, char **str2)
{
    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

static void swap_size_t(size_t *num1, size_t *num2)
{
    size_t tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void bubble_sort_words_with_count(char **words, size_t words_len, size_t *words_count)
{
    int swap_flag = 0;

    for (size_t i = 0; i < words_len - 1 && !swap_flag; i++)
    {
        swap_flag = 1;
        for (size_t j = 0; j < words_len - i - 1; j++)
        {
            if (strcmp(words[j], words[j + 1]) > 0)
            {
                swap_strings(&words[j], &words[j + 1]);
                swap_size_t(&words_count[j], &words_count[j + 1]);
                swap_flag = 0;
            }
        }
    }
}

void fprint_words_with_count(FILE *file, char **words, size_t words_len, size_t *words_count)
{
    for (size_t i = 0; i < words_len; i++)
        fprintf(file, "%s %zu\n", words[i], words_count[i]);
}
