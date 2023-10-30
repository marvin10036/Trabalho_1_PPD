#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include "array_functions/array_functions.cpp"
#include "algoritmos_sequenciais/bubblesort.h"
#include "algoritmos_sequenciais/quicksort.h"
#include "algoritmos_paralelos/pipelinedmergesort.cpp"

int main(int argc, char** argv){
  //trabalharemos com cópias para que todos os algoritmos tenham um array
  //desordenado a princípio
//  int* copia_1 = copy_array(array, number_of_elements);
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
//    time_t startTime = time(nullptr);
//    print_array(array, number_of_elements);
    for (int i=0; i<1000; i++){
        int number_of_elements = pow(2,9);
        int* array = generate_array(number_of_elements);
        pipelinedmergesort(array,number_of_elements);
//  print_array(array, number_of_elements);

    }
//    print_array(array, number_of_elements);

//    time_t endTime = time(nullptr);
//    double elapsedTime = difftime(endTime, startTime);

//    std::cout << "Tempo decorrido: " << elapsedTime << " segundos" << std::endl;

  return 0;
}
