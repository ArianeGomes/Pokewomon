#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(){
    ID = 0;
    Nome = " ";
    Ataque = 0;
    Vida  = 0;
    Tipo = " ";
    Vantagem[0] = " ";
    Vantagem[1] = " ";
    Desvantagem = " ";
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
            Nome = "Bellsprout";
            Ataque = 1;
            Vida = 6;
            Tipo = "Grama";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Agua";
            Desvantagem = "Fogo";
        break;
        case 1:
            Nome = "Ponyta_w2";
            Ataque = 1;
            Vida = 6;
            Tipo = "Fogo";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Grama";
            Desvantagem = "Agua";
        break;
        case 2:
            Nome = "Clefairy";
            Ataque = 1;
            Vida = 6;
            Tipo = "Fada";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Noturno";
            Desvantagem = "Veneno";
        break;
        case 3:
            Nome = "Cherrim";
            Ataque = 2;
            Vida = 6;
            Tipo = "Grama";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Agua";
            Desvantagem = "Fogo";
        break;
        case 4:
            Nome = "Togepi";
            Ataque = 2;
            Vida = 6;
            Tipo = "Fada";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Noturno";
            Desvantagem = "Veneno";
        break;
        case 5:
            Nome = "Spinarak";
            Ataque = 2;
            Vida = 6;
            Tipo = "Veneno";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Fada";
            Desvantagem = "Fogo";
        break;
        case 6:
            Nome = "Mew";
            Ataque = 3;
            Vida = 6;
            Tipo = "Psiquico";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Lutador";
            Desvantagem = "Fantasma";
        break;
        case 7:
            Nome = "Cubone";
            Ataque = 3;
            Vida = 6;
            Tipo = "Terra";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Veneno";
            Desvantagem = "Agua";
        break;
        case 8:
            Nome = "Minun";
            Ataque = 3;
            Vida = 6;
            Tipo = "Eletrico";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Voador";
            Desvantagem = "Terra";
        break;
        case 9:
            Nome = "Eevee";
            Ataque = 1;
            Vida = 6;
            Tipo = "Normal";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Nenhum";
            Desvantagem = "Fantasma";
        break;
        case 10:
            Nome = "Flareon";
            Ataque = 1;
            Vida = 6;
            Tipo = "Fogo";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Grama";
            Desvantagem = "Agua";
        break;
        case 11:
            Nome = "Jolteon";
            Ataque = 1;
            Vida = 6;
            Tipo = "Eletrico";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Voador";
            Desvantagem = "Terra";
        break;
        case 12:
            Nome = "Vaporeon";
            Ataque = 1;
            Vida = 6;
            Tipo = "Agua";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Fogo";
            Desvantagem = "Grama";
        break;
        case 13:
            Nome = "Glaceon";
            Ataque = 2;
            Vida = 6;
            Tipo = "Gelo";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Nenhum";
            Desvantagem = "Fogo";
        break;
        case 14:
            Nome = "Leafeon";
            Ataque = 2;
            Vida = 6;
            Tipo = "Grama";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Agua";
            Desvantagem = "Fogo";
        break;
        case 15:
            Nome = "Umbreon";
            Ataque = 2;
            Vida = 6;
            Tipo = "Noturno";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Psiquico";
            Desvantagem = "Fada";
        break;
        case 16:
            Nome = "Espeon";
            Ataque = 2;
            Vida = 6;
            Tipo = "Psiquico";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Noturno";
            Desvantagem = "Lutador";
        break;
        case 17:
            Nome = "Sylveon";
            Ataque = 3;
            Vida = 6;
            Tipo = "Fada";
            Vantagem[0] = Tipo;
            Vantagem[1] = "Noturno";
            Desvantagem = "Veneno";
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