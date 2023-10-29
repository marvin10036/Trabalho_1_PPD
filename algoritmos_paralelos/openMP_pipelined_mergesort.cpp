#include "openMP_pipelined_mergesort.h"

using namespace std;

void* final_thread(void* arg){
  queue<int>* parameters_array = (queue<int>*) arg;
  //iniciar loop de ficar esperando
  return NULL;
}

void* intermediary_thread(void* arg){
  return NULL;
}

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
  //the original array copying their real int value to the queues at first

  /*
   begin processing phase, the first thread will be copying the original arrays
   content to the queues alternately.
  */
  int array_exemplo[8] = {1,5,3,2,8,7,4,6};
  int num_of_intermediary_threads = 2;
  int num_of_queues = (num_of_intermediary_threads * 2) + 2;
  print_array(array_exemplo, 8);

  queue<int>* queue_array[num_of_queues];
  for (int i = 0; i < num_of_queues; i++){
    queue_array[i] = new queue<int>;
  }

  queue<int>* parameters_array[2] = {&left_queue, &right_queue};

  final_thread((void *) parameters_array);
  for (int i = 0; i < num_of_intermediary_threads; i++){
    intermediary_thread((void *) [queue_array, 1,2,3,4]);
  }
  return 0;
}

