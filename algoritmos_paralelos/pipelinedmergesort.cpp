#include <pthread.h>
#include "pipelinedmergesort.h"
#include <mutex>
#include <iostream>
#include <cmath>
#include <queue>
#include <limits>
using namespace std;
std::mutex myMutex;
//const int tamanho_lista = 10;
//const int numero_threads = static_cast<int>(ceil(log2(tamanho_lista))) + 1;
//const int tamanho_pipeline = (2+numero_threads)*(numero_threads-1);
//int pipeline[tamanho_pipeline];
//mutex lista_mutex[tamanho_lista];
//int lista[tamanho_lista] = {10,9,3,4,5,2,6,1,8,7};
queue<int>* pipeline{};
int len_lista;
int* lista{};
int numero_threads{};


void* pInicio(void* arg){

    for (int i=0; i< len_lista; i++){
//        cout << i%2 << endl;
//        cout << atributosLista.pipeline[i%2].front()<< endl;
//        cout << atributosLista.lista[atributosLista.len_lista-i-1]<< endl;
        pipeline[i%2].push(lista[len_lista-i-1]);
    }
    pthread_exit(NULL);
}

void* pMeio(void* arg){
    int* param = (static_cast<int*>(arg));
    int id = *param;
    int quantidade_enviada = 0;
    int posicao = 0;
    int cima = 0;
    int baixo = 0;
    queue<int> &esquerda_cima = pipeline[2*(id-1)];
    queue<int> &esquerda_baixo = pipeline[2*(id)-1];
    queue<int> &direita_cima = pipeline[2*id];
    queue<int> &direita_baixo = pipeline[2*id+1];

    while (len_lista != quantidade_enviada){
        if ((esquerda_cima.size() >= (static_cast<int>(pow(2,(id-1)))) && !esquerda_baixo.empty()) ||
                (esquerda_baixo.size() >= (static_cast<int>(pow(2,(id-1)))) && !esquerda_cima.empty())){
            do {
                if ((!esquerda_cima.empty())&&(!esquerda_baixo.empty())){
//                    cout << esquerda_cima.front() << endl;
//                    cout << esquerda_baixo.front() << endl;
                    if (esquerda_cima.front() >= esquerda_baixo.front()){
                        if (!(posicao%2)) {
                            direita_cima.push(esquerda_cima.front());
                            esquerda_cima.pop();
                        }else{
                            direita_baixo.push(esquerda_cima.front());
                            esquerda_cima.pop();
                        }
                        cima++;
                    }else {
                        if (!(posicao%2)) {
                            direita_cima.push(esquerda_baixo.front());
                            esquerda_baixo.pop();
                        }else{
                            direita_baixo.push(esquerda_baixo.front());
                            esquerda_baixo.pop();
                        }
                        baixo++;
                    }
                    quantidade_enviada++;

                    if (cima == (static_cast<int>(pow(2,id)))/2){
                        while (quantidade_enviada%(static_cast<int>(pow(2,id)))!=0){
                            if (!esquerda_baixo.empty()){
                                if (!(posicao%2)) {
                                    direita_cima.push(esquerda_baixo.front());
                                    esquerda_baixo.pop();
                                }else{
                                    direita_baixo.push(esquerda_baixo.front());
                                    esquerda_baixo.pop();
                                }
                                baixo++;
                                quantidade_enviada++;
                            }
                        }
                        cima = 0;
                        baixo = 0;
                    } else if (baixo == (static_cast<int>(pow(2,id)))/2){
                        while (quantidade_enviada%(static_cast<int>(pow(2,id)))!=0){
                            if (!esquerda_cima.empty()){
                                if (!(posicao%2)) {
                                    direita_cima.push(esquerda_cima.front());
                                    esquerda_cima.pop();
                                }else{
                                    direita_baixo.push(esquerda_cima.front());
                                    esquerda_cima.pop();
                                }
                                cima++;
                                quantidade_enviada++;
                            }
                        }
                        cima = 0;
                        baixo =0;
                    }

                }
            } while ((quantidade_enviada%(static_cast<int>(pow(2,id))))!=0);
            posicao++;
        }
    }
    pthread_exit(NULL);

}

void* pFinal(void*arg){
    int* param = (static_cast<int*>(arg));
    int id = *param;
    int quantidade_enviada= 0;
    int cima = 0;
    int baixo = 0;
    queue<int> &esquerda_cima = pipeline[2*(id-1)];
    queue<int> &esquerda_baixo = pipeline[2*(id)-1];
    while (quantidade_enviada != len_lista) {
        if ((esquerda_cima.size() >= (static_cast<int>(pow(2, (id - 1)))) && !esquerda_baixo.empty()) ||
            (esquerda_baixo.size() >= (static_cast<int>(pow(2, (id - 1)))) && !esquerda_cima.empty())) {
            do {
                if ((!esquerda_cima.empty())&&(!esquerda_baixo.empty())){
//                    cout << esquerda_cima.front() << endl;
//                    cout << esquerda_baixo.front() << endl;
                    if (esquerda_cima.front() >= esquerda_baixo.front()){
                        lista[len_lista-quantidade_enviada-1] = esquerda_cima.front();
                        esquerda_cima.pop();
                        cima++;
                    }else {
                        lista[len_lista-quantidade_enviada-1] = esquerda_baixo.front();
                        esquerda_baixo.pop();
                        baixo++;
                    }
                    quantidade_enviada++;

                    if (cima == (static_cast<int>(pow(2,id)))/2){
                        while (quantidade_enviada%(static_cast<int>(pow(2,id)))!=0){
                            if (!esquerda_baixo.empty()){
                                lista[len_lista-quantidade_enviada-1] = esquerda_baixo.front();
                                esquerda_baixo.pop();

                                baixo++;
                                quantidade_enviada++;
                            }
                        }
                        cima = 0;
                        baixo = 0;
                    } else if (baixo == (static_cast<int>(pow(2,id)))/2){
                        while (quantidade_enviada%(static_cast<int>(pow(2,id)))!=0){
                            if (!esquerda_cima.empty()){
                                lista[len_lista-quantidade_enviada-1] = esquerda_cima.front();
                                esquerda_cima.pop();
                                cima++;
                                quantidade_enviada++;
                            }
                        }
                        cima = 0;
                        baixo =0;
                    }

                }
            } while ((quantidade_enviada%(static_cast<int>(pow(2,id))))!=0);
        }
    }
    pthread_exit(NULL);

}


int pipelinedmergesort(int *lista1, int len_lista1) {
    len_lista = len_lista1;
    lista = lista1; //{121,2,21,4,45,-6,7};
    numero_threads = static_cast<int>(ceil(log2(len_lista))+1);
//    cout << numero_threads << endl;
//    cout << (numero_threads-1)*2 <<endl;
//    atributo_lista.pipeline = new queue<int>[(atributo_lista.numero_threads-1)*2];
    pthread_t threads[numero_threads];
    int thread_ids[numero_threads];

    pipeline = new queue<int>[(numero_threads-1)*2];

    for (int i = 0; i < numero_threads; i++) {
        thread_ids[i] = i;
        if (i == 0)
            pthread_create(&threads[i], NULL, pInicio, (void*)&thread_ids[i]);
        else if (i == numero_threads-1){
            pthread_create(&threads[i], NULL, pFinal, (void*)&thread_ids[i]);
        }
        else {
            pthread_create(&threads[i], NULL, pMeio, (void*)&thread_ids[i]);
        }
    }

    for (int i = 0; i < numero_threads; i++) {
        pthread_join(threads[i], NULL);
    }

//    while (!atributo_lista.pipeline[(atributo_lista.numero_threads-1)*2-2].empty()) {
//        cout << atributo_lista.pipeline[(atributo_lista.numero_threads-1)*2-2].front() << endl;
//        atributo_lista.pipeline[(atributo_lista.numero_threads-1)*2-2].pop();
//    }
//    for (int i = 0; i<(atributo_lista.numero_threads-1)*2;i++){
//        if (!atributo_lista.pipeline[i].empty()){
//            cout<< "index: "<< i << endl;
//            }
//    }


    return 0;
}
