#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <omp.h>

#define SIZE 10

using namespace std;

void init_arr(int *inp, int n);
void merge_sort(int *inp, int* out, int n);
void merge(int *inp, int* out, int n);
void print(int *inp, int n);

int main()
{
	int *arr = new int[SIZE];
	int *tmp = new int[SIZE];
	init_arr(arr, SIZE);

	merge_sort(arr, tmp, SIZE);

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

void merge_sort(int *inp, int* out, int n)
{
	if(n < 2)
		return;

	#pragma omp parallel sections
	{
		#pragma omp section		
		{
			merge_sort(inp, out, n/2);
		}

		#pragma omp section			
		{
			merge_sort(inp+(n/2), out+(n/2), n-(n/2));
		}
	}

	merge(inp, out, n);
}// End of quick_sort function

void merge(int *inp, int* out, int n)
{
	int i, j, k=0;

	i = 0;		j = n/2;

	while(i < n/2 && j < n)
	{
		if(inp[i] <= inp[j])
			out[k++] = inp[i++];
		else
			out[k++] = inp[j++];
	}
	while(i < n/2)
	{
		out[k++] = inp[i++];
	}
	while(j < n)
	{
		out[k++] = inp[j++];
	}

	memcpy(inp, out, n*sizeof(int));
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

