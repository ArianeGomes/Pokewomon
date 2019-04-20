#ifndef LISTA_H
#define LISTA_H
#include "node.h"
#include <iostream>

class Lista{
    private:
        Node* inicio;
        Node* fim;
        //quantidade de pokemons vivos q vc tem em mãos
        int QntPokemonsBatalhaveis;

    public:
        Lista();
        Lista(int ID);
        ~Lista(){
            delete inicio;
            delete fim;
        }
        int getQtdeAtual();
        bool Vazia();
        void InserirNoFinal(int ID);
        void InserirNoFinalCapturado(int ID, int vidaCapturado);
        int getTamanho();
        bool Existe(int valor);
        void RemoverElementoFinal();
        void RetirarTodosElementos();
        //RemoverElemento remove o elemento retorna o Node que você está removendo
        //Isso é importante para ser possível realizar a troca de posicao entre Nodes
        Node* RemoverElemento(int posicao);
        void InserirElemento(Node* Node, int posicao);
        bool TrocaElementos(int posicao1, int posicao2);
        //Funções mais relacionadas ao jogo
        int getQntPokemonsBatalhaveis();
        Node* getNode(int posicao);
        Pokemon* getPokemon(int posicao);
        void CurarPokemons();
        void CurarTodaLista(); //para os pokemons selvagens
        Pokemon* pokemonQueVaiBatalhar(int* posicao);
};

#endif // LISTA_H
