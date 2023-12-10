#include "utils.hpp"
#include <iostream>

int *create_random_n_arr(int size)
{
    int *random_arr;
    int temp;
    int idx;
    int dup_flag;

    random_arr = (int *)malloc(sizeof(int) * size);
    if (!random_arr)
    {
		std::cout << "Error: create_random_n_arr: malloc failed" << std::endl;
        return (0);
    }
    srand(time(NULL));
    idx = 0;
    while (idx < size)
    {
        temp = rand() % size;
        dup_flag = 0;
        for (int j = 0; j < idx; j++)
        {
            if (temp == random_arr[j])
            {
                dup_flag = 1;
                break;
            }
        }
        if (dup_flag == 0)
            random_arr[idx++] = temp;
    }
    return (random_arr);
}

