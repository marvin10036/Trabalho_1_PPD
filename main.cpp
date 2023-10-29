#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "array_functions/array_functions.h"
#include "algoritmos_sequenciais/bubblesort.h"
#include "algoritmos_sequenciais/quicksort.h"
#include "algoritmos_paralelos/pipelined_mergesort.h"

int main(int argc, char** argv){
  int number_of_elements = 8;

  int* array = generate_array(number_of_elements);
  //trabalharemos com cópias para que todos os algoritmos tenham um array
  //desordenado a princípio
  int* copia_1 = copy_array(array, number_of_elements);
//  int* copia_2 = copy_array(array2, number_of_elements2);

//  printf("printando array copiado:\n");
//  print_array(copia_1, number_of_elements);
//
//  bubblesort(copia_1, number_of_elements);
//  quicksort(copia_2, 0, number_of_elements2);
//
//  printf("printando array copiado ordenado por bubblesort:\n");
//  print_array(copia_1, number_of_elements);
//
//  printf("printando array copiado ordenado por quicksort:\n");
//  print_array(copia_2, number_of_elements2);

    pipelined_mergesort(copia_1,number_of_elements);

  return 0;
}
