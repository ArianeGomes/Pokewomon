#ifndef POKEMON_H
#define POKEMON_H
#include <iostream>

using namespace std;

class Pokemon{
    public:
        Pokemon();
        Pokemon(int ID);
        ~Pokemon(){}
        void defineInfoPelaID(int ID);
        string getNome();
        int getID();
        int getAtaque();
        int getVida();
        void curaVida();
        void setVida(int novaVida);
        bool estaVivo();

    private:
        int ID;
        string Nome, Tipo, Vantagem[2], Desvantagem;
        int Ataque, Vida;
};
#endif // POKEMON_H
