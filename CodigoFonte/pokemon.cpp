#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(){
    ID = 0;
    Nome = " ";
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
    switch(ID)
    {
        case 0: // no nome, o primeiro é relacionado ao ataque, o segundo à vida~~
            Nome = "fraco1";
            Ataque = 1;
            Vida = 6;
        break;
        case 1:
            Nome = "fraco2";
            Ataque = 1;
            Vida = 6;
        break;
        case 2:
            Nome = "fraco3";
            Ataque = 1;
            Vida = 6;
        break;
        case 3:
            Nome = "medio1";
            Ataque = 2;
            Vida = 6;
        break;
        case 4:
            Nome = "medio2";
            Ataque = 2;
            Vida = 6;
        break;
        case 5:
            Nome = "medio3";
            Ataque = 2;
            Vida = 6;
        break;
        case 6:
            Nome = "forte1";
            Ataque = 3;
            Vida = 6;
        break;
        case 7:
            Nome = "forte2";
            Ataque = 3;
            Vida = 6;
        break;
        case 8:
            Nome = "forte";
            Ataque = 3;
            Vida = 6;
        break;
    }

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
