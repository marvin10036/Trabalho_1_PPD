#include "openMP_pipelined_mergesort.h"

using namespace std;

int* original_array_pointer;
int array_length;

void* final_thread(void* arg){
  queue<int>* parameters_array = (queue<int>*) arg;
  queue<int>* left_queue = parameters_array[0];
  queue<int>* right_queue = parameters_array[1];

  //iniciar loop de ficar esperando
  while(left_queue->size() + right_queue->size() != (array_length/2)+1){
    //bloqueia a thread até que ela possa começar a processar
  }

  int left_queue_merge_counter = ceil(array_length/2);
  int right_queue_merge_counter = ceil(array_length/2);

  for(int i = (array_length - 1); i >= 0 ; i--){
    if(left_queue_merge_counter == 0 || right_queue_merge_counter == 0){
      //terminar o merge
    }

    if ((left_queue->size() == 0 || right_queue->size() == 0) && i != 0){
      //bloqueia a thread 
    }

    if(left_queue->front() > right_queue->front()){
      *(original_array_pointer)[i] = left_queue->front();
      left_queue->pop();
      left_queue_merge_counter--;
    }
    else{
      *(original_array_pointer)[i] = right_queue->front();
      right_queue->pop();
      right_queue_merge_counter--;
    }
  }
  return NULL;
}

void* intermediary_thread(void* arg){
  queue<int>* parameters_array = (queue<int>*) arg;
  queue<int>* input_left_queue = parameters_array[0];
  queue<int>* input_right_queue = parameters_array[1];
  queue<int>* output_left_queue = parameters_array[2];
  queue<int>* output_right_queue = parameters_array[3];
  //size of subsequence ou id da thread para encontrar o mesmo

  for(int i = 0; i < ceil((array_length/2)/size_of_subsequence); i++){
    //um merge
    while(input_left_queue->size() + input_right_queue->size() != (size_of_subsequence+1){
      //bloqueia a thread até que ela possa começar a processar um merge
    }

    int left_queue_merge_counter = size_of_subsequence;
    int right_queue_merge_counter = size_of_subsequence;

    for(int j = (size_of_subsequence * 2); j >= 0 ; j--){
      if(left_queue_merge_counter == 0 || right_queue_merge_counter == 0){
        //terminar o merge
      }

      if ((input_left_queue->size() == 0 || input_right_queue->size() == 0) && j != 0){
        //bloqueia a thread
      }

      if(input_left_queue->front() > input_right_queue->front()){
        if(i%2 == 0){
          output_left_queue->push(input_left_queue->front());
        }else{
          output_right_queue->push(input_left_queue->front());
        }
        input_left_queue->pop();
        left_queue_merge_counter--;
      }
      else{
        if(i%2 == 0){
          output_left_queue->push(input_right_queue->front());
        }else{
          output_right_queue->push(input_right_queue->front());
        }
        input_right_queue->pop();
        right_queue_merge_counter--;
      }
    }
  }
 
 return NULL;
}

void* first_thread(void* arg){
  queue<int>* parameters_array = (queue<int>*) arg;
  queue<int>* left_queue = parameters_array[0];
  queue<int>* right_queue = parameters_array[1];

  for(int i = (array_length - 1); i >= 0 ; i--){
    if(i%2 == 0){
      right_queue->push(*(original_array_pointer)[i]);
    }
    else{
      left_queue->push(*(original_array_pointer)[i]);
    }
  }
  return NULL;
}

int* openMP_pipelined_mergesort(int* original_array, int number_of_elements){
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
  //print_array(array_exemplo, 8);
  array_length = number_of_elements;
  original_array_pointer = original_array;

  queue<int>* queue_array[num_of_queues];
  for (int i = 0; i < num_of_queues; i++){
    queue_array[i] = new queue<int>;
  }

  queue<int>* parameters_array[2] = {queue_array[0], queue_array[1]};

  final_thread((void *) parameters_array);
  for (int i = 0; i < num_of_queues; i+2){
    intermediary_thread((void *) [queue_array[i], queue_array[i+1], queue_array[i+2], queue_array[i+3]]);
  }
  first_thread((void *) [queue_array[num_of_queues - 1], queue_array[num_of_queues - 2]]);
  return 0;
}

