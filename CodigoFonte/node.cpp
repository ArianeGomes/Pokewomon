#include "node.h"
#include <iostream>

Node::Node(int ID){
    this-> ID = ID;
    estePokemon.defineInfoPelaID(ID);
    this->ProximoNode = NULL;
}

int Node::getID(){
    return ID;
}

Node* Node::getProximoNode(){
    return ProximoNode;
}

void Node::setProximoNode(Node* proximo){
   this->ProximoNode = proximo;
}

Pokemon* Node::getPokemon(){
    Pokemon* pPokemon = &estePokemon;
    return (pPokemon);
}
