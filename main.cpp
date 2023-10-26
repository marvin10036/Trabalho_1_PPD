#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "array_functions/array_functions.h"
#include "algoritmos_sequenciais/bubblesort.h"

int main(int argc, char** argv){
  int number_of_elements = 50;

  int* array = generate_array(number_of_elements);
  //trabalharemos com cópias para que todos os algoritmos tenham um array
  //desordenado a princípio
  int* copia_1 = copy_array(array, number_of_elements);

  printf("printando array copiado:\n");
  print_array(copia_1, number_of_elements);

  bubblesort(copia_1, number_of_elements);

  printf("printando array copiado ordenado:\n");
  print_array(copia_1, number_of_elements);

  return 0;
}
