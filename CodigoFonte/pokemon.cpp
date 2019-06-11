#include "pokemon.h"
#include <iostream>
#include <string.h>
#include <cstdio>

Pokemon::Pokemon(){
    ID = 0;
    Ataque = 0;
    Vida  = 0;
}

//criei esse construtor no intuito de inicializar o pokemon com as informações certas, mas na implementação nem usei ele
//usei direto a função "defineInfoPelaID"
Pokemon::Pokemon(int ID){
    defineInfoPelaID(ID);
}

void Pokemon::setVida(int novaVida){
    Vida = novaVida;
}

void Pokemon::curaVida(){
    //como a vida é a única coisa alteravel, para curar ele restaura mesmo as configurações iniciais do pokemon
    defineInfoPelaID(ID);
}

bool Pokemon::estaVivo(){
    if(getVida() > 0)
        return true;
    else
        return false;
}

void Pokemon::defineInfoPelaID(int ID){
    this->ID = ID;
    int indice = -1;
    FILE * arquivo = fopen("pokemons.txt", "r");

    while(indice != ID){
        fscanf(arquivo, "%d-%[^-]-%d-%d-%[^-]-%[^-]-%[^\n]\n", &indice, Nome, &Ataque, &Vida, Tipo, Vantagem[1], Desvantagem);
        strcpy(Vantagem[0], Tipo);
    }

    fclose(arquivo);
}

string Pokemon::getNome(){
    return (Nome);
}

int Pokemon::getID(){
    return (ID);
}

int Pokemon::getAtaque(){
    return (Ataque);
}

int Pokemon::getVida(){
    return (Vida);
}