#include "quicksort.h"

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int partition(int* array, int low, int high) {
  int pivot = array[high]; 
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(array[i], array[j]);
    }
  }

  swap(array[i + 1], array[high]);
  return (i + 1);
}

int* quicksort(int* array, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(array, low, high);

    quicksort(array, low, pivotIndex - 1);
    quicksort(array, pivotIndex + 1, high);
  }
  return array;
}