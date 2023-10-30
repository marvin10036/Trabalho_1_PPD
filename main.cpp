#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <queue>
#include "array_functions/array_functions.h"
#include "algoritmos_sequenciais/bubblesort.h"
#include "algoritmos_sequenciais/quicksort.h"
#include "algoritmos_paralelos/pipelinedmergesort.h"

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
    for (int i=0; i<10; i++){
        int number_of_elements = pow(2,10);
        int* array = generate_array(number_of_elements);
        pipelinedmergesort(array,number_of_elements);
//  print_array(array, number_of_elements);
    }
//    print_array(array, number_of_elements);

//    time_t endTime = time(nullptr);
//    double elapsedTime = difftime(endTime, startTime);

////    std::cout << "Tempo decorrido: " << elapsedTime << " segundos" << std::endl;
//    queue<int>* pipeline{};
//    pipeline = new queue<int>[5];
//    for (int i=0; i< 1000; i++){
//        pipeline[0].front();
//        pipeline[0].front() >= pipeline[1].front();
//        pipeline[1].pop();
//    }

  return 0;
}
