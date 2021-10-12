#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define NOTFOUND -1

void getData(int array[], int n);
void printData(int array[], int n);
void InsertionSort(int array[], int n);
int BinarySearchRec(int item, int array[], int start, int end);

int main()
{
    int list[N];
    int item, found;
 
    /* generate random list */
    getData(list, N);
    printf("Original array: ");
    printData(list, N);

    /* call insertion sort */
    InsertionSort(list, N);
    printf("Sorted array: ");
    printData(list, N);

    /* get item from the user */
    printf("Which number do you want to find in the list? ");
    scanf("%d", &item);

    /* call binary search */
    found = BinarySearchRec(item, list, 0, N-1);
    printf("Item %d was %sfound in the list\n", item, (found==NOTFOUND) ? "NOT " : "");

    return 0;
}

/* generate random data for array of N values */
void getData(int array[], int n)
{
    int i;
    srand(clock());
    for (i = 0; i < n; i++)
        array[i] = rand() / 1000000;
}

/* print 1D array */
void printData(int array[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n"); 
}

/* insertion sort */
void InsertionSort(int array[], int n)
{
    int us; /* unsorted index */
    int s;  /* sorted index */
    int usItem;  /* current unsorted item */
    
    for (us = 1; us < n; us++)
    {
        usItem = array[us];
        
        for (s = us-1; (s >= 0) && (array[s] > usItem); s--)
            array[s+1] = array[s];
    
        array[s+1] = usItem;
    }
}

/* recursive binary search */
int BinarySearchRec(int item, int array[], int start, int end)
{
    int middle = (end + start) / 2;

    /* terminal cases */
    if (end < start ) return NOTFOUND;    
    if (item == array[middle]) return middle;

    if (item < array[middle])
             return BinarySearchRec(item, array, start, middle - 1);
    else
             return BinarySearchRec(item, array, middle + 1, end);
}
  
