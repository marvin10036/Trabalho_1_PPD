#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "array_functions/array_functions.h"
#include "algoritmos_sequenciais/bubblesort.h"

int main(int argc, char** argv){
  int number_of_elements = 50;

  int* array = generate_array(number_of_elements);
  /*
  for(int i = 0; i < number_of_elements; i++){
    printf("%d, ", array[i]);
  }
  printf("\n");
  */

  int* copia_1 = copy_array(array, number_of_elements);

  printf("printando array copiado:\n");
  for(int i = 0; i < number_of_elements; i++){
    printf("%d, ", copia_1[i]);
  }
  printf("\n");

  bubblesort(copia_1, number_of_elements);
  printf("printando array copiado ordenado:\n");
  for(int i = 0; i < number_of_elements; i++){
    printf("%d, ", copia_1[i]);
  }
  printf("\n");
  return 0;
}
