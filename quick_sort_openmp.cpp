#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define SIZE 10

using namespace std;

void init_arr(int *inp, int n);
void quick_sort(int low, int high, int *inp);
int partition(int low, int high, int *inp);
void print(int *inp, int n);

int main()
{
	int *arr = new int[SIZE];

	init_arr(arr, SIZE);

	quick_sort(0, SIZE-1, arr);

	print(arr, SIZE);

	return 0;
}// End of main function

void init_arr(int *inp, int n)
{
	time_t t;
	srand((unsigned) time(&t));

	int i;

	for(i = 0; i < n; i++)
	{
		inp[i] = rand()%100;
	}

}// End of init_arr function

void quick_sort(int low, int high, int *inp)
{
	int j;
	if(low < high)
	{
		j = partition(low, high, inp);

		#pragma omp parallel sections
		{
			#pragma omp section			//sort left sublist
			{
				quick_sort(low, j-1, inp);
			}

			#pragma omp section			//sort right sublist
			{
				quick_sort(j+1, high, inp);
			}
		}
	}
}// End of quick_sort function

int partition(int low, int high, int *inp)
{
	int i, j, pivot, tmp;

	pivot=low;	i=low+1;	j=high;

	while(1)
	{
		while(i<high && inp[i]<=inp[pivot])
			i++;
		while(inp[j] > inp[pivot])
			j--;

		if(i < j)
        	{
            		//Swap i and j position element
            		tmp = inp[i];          inp[i] = inp[j];          inp[j] = tmp;
        	}
        	else
        	{
            		//Swap j and pivot position element
            		tmp = inp[j];          inp[j] = inp[pivot];      inp[pivot] = tmp;
            		return j;
        	}
	}
}// End of partition function

void print(int *inp, int n)
{
	int i;
	cout<<"\n Sorted array: \n";
	for(i = 0; i < n; i++)
	{
		cout<<" "<<inp[i]<<" ";
	}
	cout<<"\n";
}// End of print function

