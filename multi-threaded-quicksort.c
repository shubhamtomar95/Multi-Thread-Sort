#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10000

typedef struct 
{
    int *input;
    int size;
}param;


void fill_array(int *input)
{
    FILE *fp = fopen("input.txt", "r");
    int num,i = 0;
    while(fscanf(fp, "%d", &num) > 0)
    {
        *(input + i) = num;
        i++;
    }
}

void output(int *input)
{
    FILE *fp = fopen("output_quicksort.txt", "w+");
    int i = 0;
    while( i < SIZE - 1)
    {
        fprintf(fp, "%d\n", *(input + i));
        i++;
    }
    fprintf(fp, "%d", *(input + i));

}

void assign_value(param *prm,int *array, int len)
{
    prm->input = array;
    prm->size = len;
}

void swap(int *a, int *b)
{    
    int temp = *a;
    *a = *b;
    *b = temp;
}

int choose_pivot(int *input)
{
    return 0;
}


int partition_around_pivot(int *input, int size_of_input)
{
    int pivot,first_unpartioned, first_partioned,pivot_index,i;
    /*Here first_partioned is index of the first element greater than the pivot*/
    pivot = *(input);/*We choose the first element to be the pivot*/
    first_partioned = 1;/*This is the index of first_partioned element*/
    first_unpartioned = first_partioned;
    for(i = 1 ; i < size_of_input; i++ )
    {
        
        /*We itereate through the the loop size_of_input - 1 number of times, 
          everytime comapring pivot with the first_unpartioned element
          (first_unpartioned = first_partioned; first_unpartioned < size_of_input; first_unpartioned++)*/
        if(*(input + first_unpartioned) < pivot)
        {
            /*If the first_unpartioned element < pivot we swap the first_partioned element with it*/
            swap(input + first_unpartioned, input + first_partioned);
            first_partioned++;
            /*After swapping the index is increased */
        }
        
        first_unpartioned++;
    }

    pivot_index = first_partioned - 1;
    swap(input, input + pivot_index);
    return pivot_index;
}

void *QuickSort(void *ptr_input)
{
    int pivot_index,i, *input = ((param *)ptr_input)->input, size_of_input = ((param *)ptr_input)->size, res;
    if(size_of_input <= 1)
    {    
        return 0;
    }    
    
    pivot_index = partition_around_pivot(input, size_of_input); 
    
    pthread_t left_thread, right_thread;
    
    param *prm_left = (param *)malloc(sizeof(param));
    
    assign_value(prm_left, input, pivot_index);
    
    res = pthread_create(&left_thread, NULL, QuickSort, (void *) prm_left);
    
    if(res != 0)
    {
        perror("Left thread creation failed");
    }
    
    param *prm_right = (param *)malloc(sizeof(param));
    
    assign_value(prm_right, input + pivot_index + 1, size_of_input -pivot_index - 1);
    
    res = pthread_create(&right_thread, NULL, QuickSort, (void *) prm_right);
    
    if(res != 0)
    {
        perror("Right thread creation failed");
    }

    pthread_join(left_thread, NULL);
    
    pthread_join(right_thread, NULL);

}

int main(int argc, char const *argv[])
{
    pthread_t main_thread;
    
    int *input = (int *)malloc(sizeof(int)*SIZE);
    fill_array(input);
    
    param *prm = (param *)malloc(sizeof(int));
    assign_value(prm, input, SIZE);
    
    int res = pthread_create(&main_thread, NULL, QuickSort, (void *) prm);
    
    pthread_join(main_thread, NULL);
    
    output(input);

    return 0;
}