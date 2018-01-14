#include <stdio.h>	
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10000

pthread_mutex_t lock_number_of_threads;

typedef struct 
{
	int *input;
	int size;
}parameters;

void assign_value(parameters *prm,int *array, int len)
{
	prm->input = array;
	prm->size = len;
}

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
	FILE *fp = fopen("Output_Mergesort.txt", "w+");
	int i = 0;
	while( i < SIZE )
	{
		fprintf(fp, "%d\n", *(input + i));
		i++;
	}	
}

void Merge(int *input, int size_of_left, int size_of_right)
{
	int i,j,k,temp[size_of_left + size_of_right];
	i = 0; j = 0; k = 0;

	
	while ( i < size_of_left && j < size_of_right )
	{
		if(*(input + i) < *(input + size_of_left + j))
		{
			temp[k] = *(input + i);
			i++;
		}

		else
		{
			temp[k] = *(input + size_of_left + j);
			j++;
		}
		k++;
	}
	
	if( i < size_of_left )
	{
		while( i < size_of_left )
		{
		//	printf("if one\n");
			temp[k] = *(input + i);
			i++;
			k++;
		}
	}	

	if( j < size_of_right )
	{
		//printf("if two\n");
		while( j < size_of_right )
		{
			temp[k] = *(input + size_of_left + j);
			j++;
			k++;
		}
	}

	for( i = 0 ; i < (size_of_right + size_of_left) ; i++ )
	{
		*(input + i) = temp[i];
	}
}




void *MergeSort(void *arg)
{
	
	parameters *prmtrs = arg;
	//printf("size of input = %d\n", prmtrs->size);
	int *input = prmtrs->input;//, left, right;
	int size_of_input = prmtrs->size;    
    pthread_t left_thread, right_thread;
    
	int middle_index = (size_of_input / 2);
	if(size_of_input <= 1)
	{
       return NULL;
	}
			
	//sem_init(&sem_bin, 0, 1);
	parameters *prm_left = (parameters *)malloc(sizeof(parameters));
	parameters *prm_right = (parameters *)malloc(sizeof(parameters));
	
	assign_value(prm_left, input, middle_index);
	assign_value(prm_right, input + middle_index, size_of_input - middle_index);
	
	int left = pthread_create(&left_thread, NULL, MergeSort, (void *)prm_left);

	if(left != 0)
    {
       perror("Left thread creation failed");
    }

	int right = pthread_create(&right_thread, NULL, MergeSort, (void *)prm_right);
        
    if (right != 0)
    {
    	perror("Right thread creation failed");
    }
	//MergeSort((void *)prm_left);
	
	//MergeSort((void *)prm_right);

    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);


	Merge(input , middle_index, size_of_input - (middle_index ));

	
}

void MergeSort_util(int *ptr, int size)
{
	parameters *prm = (parameters *)malloc(sizeof(parameters));
	assign_value(prm, ptr, size);
	pthread_t thread;
	int res = pthread_create(&thread, NULL, MergeSort, (void *)prm);
	pthread_join(thread, NULL);
}

int main(int argc, char const *argv[])
{
	int *begin = (int *)malloc(SIZE*sizeof(int));
	fill_array(begin);
	MergeSort_util(begin, SIZE);
	output(begin);	
	return 0;
}