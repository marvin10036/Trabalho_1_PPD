#include "bubblesort.h"

int* bubblesort(int* array, int number_of_elements){
  int i, j, temp;
  for (i = 0; i < number_of_elements; i++){
    for (j = 1; j < number_of_elements - i; j++){
      if(array[j] < array[j-1]){
        temp = array[j];
        array[j] = array[j-1];
        array[j-1] = temp;
      }
    }
  }
  return array;
}

