#include "array_functions.h"

int* generate_array(int number_of_elements){
  srand(time(NULL));
  int* output_array = calloc(number_of_elements, sizeof(int));
  for(int i = 0; i < number_of_elements; i++){
    output_array[i] = rand() % number_of_elements;
  }
  return output_array;
}

int* copy_array(int* original_array_pointer, int number_of_elements){
  int sizeof_array = (number_of_elements * sizeof(int));
  //calloc faz multiplicação internamente
  int* copied_array = calloc(number_of_elements, sizeof(int));

  memcpy(copied_array, original_array_pointer, sizeof_array);
  return copied_array;
}
