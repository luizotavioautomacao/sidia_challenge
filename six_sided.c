/* ****************************************************************************************/
/* // **********  ////    Program to test the C concepts - 
/* // **********  ////    How can compile the program?
/* // **********  ////    In prompt the command or terminal:
/* // **********  ////    LINUX: gcc six_sided.c -o obj_exec && ./obj_exec 
/* // **********  ////    WINDOWS: gcc six_sided.c -o obj_exec && obj_exec 
/* // **********  ////    valgrind > valgrind --leak-check=full ./obj_exec
/* // **********  ////    Author: Luiz Otávio Mendes de Oliveira
/* // **********  ////    Creation date:    01jul2018
/* // **********  ////    Revision date:    02jul2018  
/* // **********  ////    ******************************************************************/

#include <stdio.h> // printf, puts, scanf
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

char *readline();
char **split_string(char *);
int start = 0;

int solution(int A[], int N)
{
    int best_spin = INT32_MAX;
    int position_spin = 0;
    int j = 0;

    for (int i = 1; i <= 6; i++)
    {

        int spin = 0;
        for (int j = 0; j < N; j++)
        {
            if (*(A + j) == i)
            {
                continue;
            }

            else if (*(A + j) + i == 7)
            {
                spin += 2;
            }
            else
                spin += 1;
        }

        //printf("spin: %i , position: %i\n", spin, i);
        if (best_spin > spin)
        {
            best_spin = spin;
            position_spin = i;
        }
    }

    return best_spin;
}

int main()
{
    puts("Digite o tamanho do vetor: ");
    char *n_str = readline();
    char *n_endptr;                       // trash, not number
    int n = strtol(n_str, &n_endptr, 10); // number of elements > convert string to long

    if (n_endptr == n_str || *n_endptr != '\0')
    {
        exit(EXIT_FAILURE);
    }

    char **arr_temp = split_string(readline());

    int *arr = malloc(n * sizeof(int)); // array

    for (int i = 0; i < n; i++)
    {
        char *arr_item_endptr; // trash, not number
        char *arr_item_str = *(arr_temp + i);
        int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

        if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0')
        {
            exit(EXIT_FAILURE);
        }

        *(arr + i) = arr_item;
    }

    int retorno = solution(arr, n);

    // Próximo número inteiro não inserido no vetor:
    printf("%i\n", retorno);

    return 0;
}

char *readline()
{
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char *data = malloc(alloc_length);

    while (1)
    {
        char *cursor = data + data_length;
        char *line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line)
        {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
        {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line)
        {
            break;
        }
    }

    if (data[data_length - 1] == '\n')
    {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    }
    else
    {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char **split_string(char *str)
{
    char **splits = NULL;
    char *token = strtok(str, " ");

    int spaces = 0;

    while (token)
    {
        splits = realloc(splits, sizeof(char *) * ++spaces);
        if (!splits)
        {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}