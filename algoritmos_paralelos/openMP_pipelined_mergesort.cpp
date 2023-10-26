#include "openMP_pipelined_mergesort.h"

typedef struct{
  int* queue;
  int input_position;
  int output_position;
}circular_queue;

int* openMP_pipelined_mergesort(int* array, int number_of_elements){
  /*
  create last thread and a pair of queues, it will futurally overwrite original array
  positions
  */

  /*
  create middle threads connecting to last pair of queues, and generating
  another pair for output
  */

  //create first thread, with two circular queues, it will only iterate through 
  //the original array

  /*
   begin processing phase, the first thread will be copying the original arrays
   content to the queues alternately.
  */
  return 0;
}

