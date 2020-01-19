#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int main()
{
  int n = 100;
  int arr[n], arr_copy[n], perm[n];
  for (int i = 0; i < n; i++){
    arr[i] = 100 - i;
    arr_copy[i] = 100 - i;
    //perm[i] = i;
  }
  arr[50] = 650;
  arr_copy[50] = 650;
  int beg = 0;
  int end = 99;
  sort(arr, arr_copy, beg, end, perm);
  for (int i = 0; i < n; i++)
  {
    printf("with perm = %d, sorted array = %d \n", arr[perm[i]], arr_copy[i]);
  }

  return 0;
}


void swap(int *a, int *b)
{
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int arr_copy[], int beg, int end, int perm[])
{
  //int n = sizeof(arr)/(sizeof(arr[0]));
  int n = 100;
  if (end > beg + 1) {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r) {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    sort(arr, arr_copy, beg, l, perm);
    sort(arr, arr_copy, r, end, perm);
  }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (arr[i] == arr_copy[j]) perm[i] = j;
      }
    }
  }

/*
void sort(int arr[], int beg, int end)
{

  if (end > beg + 1) {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r) {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l);
    sort(arr, r, end);
  }
}
*/
