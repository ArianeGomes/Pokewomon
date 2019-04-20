#ifndef NODE_H
#define NODE_H
#include "pokemon.h"
#include <iostream>

class Node{
    private:
        int ID;
        Pokemon estePokemon;
        Node* ProximoNode;
    public:
        Node(int ID);
        ~Node() {delete ProximoNode;}
        int getID();
        Node* getProximoNode();
        void setProximoNode(Node* ponteiro);
        Pokemon* getPokemon();
};
#endif // NODE_H
