#include <thread>
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

struct AtributosLista {
    int len_lista = 10;
    int* lista{};
    int lista_ordenada = 0;
    int numero_threads{};
    queue<int>* pipeline{};
};

void pInicio(AtributosLista atributosLista){
    for (int i=0; i< atributosLista.len_lista; i++){
        atributosLista.pipeline[i%2].push(atributosLista.lista[atributosLista.len_lista-i-1]);
    }
}

void pMeio(int id, AtributosLista atributosLista){
    int quantidade_enviada = 0;
    int posicao = 0;
    int cima = 0;
    int baixo = 0;
    queue<int> &esquerda_cima = atributosLista.pipeline[2*(id-1)];
    queue<int> &esquerda_baixo = atributosLista.pipeline[2*(id)-1];
    queue<int> &direita_cima = atributosLista.pipeline[2*id];
    queue<int> &direita_baixo = atributosLista.pipeline[2*id+1];

    while (atributosLista.len_lista != quantidade_enviada){
        if ((esquerda_cima.size() >= (static_cast<int>(pow(2,(id-1)))) && !esquerda_baixo.empty()) ||
                (esquerda_baixo.size() >= (static_cast<int>(pow(2,(id-1)))) && !esquerda_cima.empty())){
            do {
                if ((!esquerda_cima.empty())&&(!esquerda_baixo.empty())){
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
}

void pFinal(int id, AtributosLista atributosLista){
    int quantidade_alterada= 0;
    queue<int> &esquerda_cima = atributosLista.pipeline[2*(id-1)];
    queue<int> &esquerda_baixo = atributosLista.pipeline[2*(id)-1];
    while (quantidade_alterada != atributosLista.len_lista) {
        if ((esquerda_cima.size() >= (static_cast<int>(pow(2, (id - 1)))) && !esquerda_baixo.empty()) ||
            (esquerda_baixo.size() >= (static_cast<int>(pow(2, (id - 1)))) && !esquerda_cima.empty())) {
            do {
                if (esquerda_cima.front() >= esquerda_baixo.front()){
                    atributosLista.lista[atributosLista.len_lista-quantidade_alterada-1] = esquerda_cima.front();
                    esquerda_cima.pop();
                }
                else{
                    atributosLista.lista[atributosLista.len_lista-quantidade_alterada-1] = esquerda_baixo.front();
                    esquerda_baixo.pop();
                }
                quantidade_alterada++;
            }while ((quantidade_alterada%(static_cast<int>(pow(2,id))))!=0);
        }
    }
}


int pipelined_mergesort(int *lista, int len_lista) {
    AtributosLista atributo_lista;
    atributo_lista.len_lista = len_lista;
    atributo_lista.lista = lista; //{121,2,21,4,45,-6,7};
    atributo_lista.numero_threads = static_cast<int>(ceil(log2(atributo_lista.len_lista))+1);
    atributo_lista.pipeline = new queue<int>[(atributo_lista.numero_threads-1)*2];
    thread threads[atributo_lista.numero_threads];
//    cout << atributo_lista.numero_threads << endl;
//    cout << (atributo_lista.numero_threads-1)*2 << endl;

    for (int i = 0; i < atributo_lista.numero_threads; i++) {
        if (i == 0)
            threads[i] = thread(pInicio, atributo_lista);
        else if (i == atributo_lista.numero_threads-1){
            threads[i] = thread(pFinal, i, atributo_lista);
        }
        else {
            threads[i] = thread(pMeio,i, atributo_lista);
        }
    }

    for (int i = 0; i < atributo_lista.numero_threads; i++) {
        threads[i].join();
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