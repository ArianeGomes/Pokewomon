#include "lista.h"
#include <iostream>

Lista::Lista(){
    QntPokemonsBatalhaveis = 0;
    inicio = NULL;
    fim = NULL;
}

Lista::Lista(int ID){
    QntPokemonsBatalhaveis = 0;
    inicio = new Node(ID);
    fim = inicio;
}

int Lista::getQtdeAtual(){
    int qtde = 6;
    if (getTamanho() < 6){
        qtde = getTamanho();
    }
    return qtde;
}

bool Lista::Vazia(){
    if(inicio == NULL)
        return true;
    else
        return false;
}

//Retorna o tamanho da lista no momento
int Lista::getTamanho(){
    if(Vazia())
        return 0;
    Node* aux = inicio;
    int tamanho = 0;
    do{
        aux = aux->getProximoNode();
        tamanho++;
    }while(aux);

    return tamanho;
}

//Verifica se um elemento existe na lista
bool Lista::Existe(int valor){
    Node* aux = inicio;

    while(aux){
        if(aux->getID() == valor)
            return true;
        aux = aux->getProximoNode();
    }
    return false;
}

//Insere um novo node no final;
void Lista::InserirNoFinal(int ID){
    Node* NovoNode = new Node(ID);
    if(Vazia()){
        inicio = NovoNode;
        fim = NovoNode;
    }else{
        fim->setProximoNode(NovoNode);
        fim = NovoNode;
        if(getTamanho() == 1)
            inicio->setProximoNode(fim);
    }
}

void Lista::InserirNoFinalCapturado(int ID, int vidaCapturado){
    Node* NovoNode = new Node(ID);

    //para definir que a vida desse capturado é igual à vida que ele estava qnd foi capturado
    Pokemon* PokemonCapturado = NovoNode->getPokemon();
    PokemonCapturado->setVida(vidaCapturado);

    if(Vazia()){
        inicio = NovoNode;
        fim = NovoNode;
    }else{
        fim->setProximoNode(NovoNode);
        fim = NovoNode;
    }
}

void Lista::RemoverElementoFinal(){
    if(!Vazia()){
        // se houver só 1 elemento
        if(inicio->getProximoNode() == NULL)
            inicio = NULL;
        else if(inicio->getProximoNode()->getProximoNode() == NULL) // 2 elementos
            inicio->setProximoNode(NULL);
        else{// > 2 elementos
            Node* anterior_anterior = inicio;
            Node* anterior = inicio->getProximoNode();
            Node* corrente = inicio->getProximoNode()->getProximoNode();

            while(corrente){
                Node* aux = anterior;
                anterior = corrente;
                anterior_anterior = aux;
                corrente = corrente->getProximoNode();
            }
            delete anterior_anterior->getProximoNode();
            anterior_anterior->setProximoNode(NULL);
            fim = anterior_anterior;
        }
    }
}

void Lista::RetirarTodosElementos(){
    while(getTamanho() != 0)
        RemoverElementoFinal();
}

//remove um elemento da posição que deseja
Node* Lista::RemoverElemento(int posicao){
    Node* aux = inicio;

    //entra na condição de ter um node na posicao q vc escolheu
    if(posicao <= getTamanho()){
        if(posicao == 1){  //aux aponta para o Node q deseja retirar (primeiro)
            if(getTamanho() == 1)
                fim = NULL;
            inicio = inicio->getProximoNode();
            return(aux);
        }

        for(int i=1; i<posicao-1; i++) //aux aponta para o Node ANTERIOR do desejado
            aux = aux->getProximoNode();

        if(aux->getProximoNode()->getProximoNode() == NULL){ //se queremos tirar o ultimo
            fim = aux;
            aux = aux->getProximoNode();
            fim->setProximoNode(NULL);
            return(aux);
        }

        //demais casos - se a função nao parar no "return" de retirar do inicio, nem no de retirar do final.
        Node* Desejado = aux->getProximoNode();
        aux->setProximoNode(Desejado->getProximoNode());

        return(Desejado);
    } else
        return 0;
}

//insere o Node na posicao "posicao"
//ex : " a -> b -> c -> d -> "  posicao de A = 1, B = 2, ...
//se colocássemos algo na posição "3", C passaria a ser o 4° ...
void Lista::InserirElemento(Node* NodeDesejado, int posicao){
     Node* aux = inicio;
     if(posicao <= getTamanho()+1){
         //se quiser inserir no começo da lista
        if(posicao == 1){
            NodeDesejado->setProximoNode(inicio);
            inicio = NodeDesejado;
        }else{
            //aux aponta para o Node que está em (posicao-1)
            for(int i=1; i<posicao-1; i++)
                aux = aux->getProximoNode();

            //se deseja inserir no final da lista
            if(aux->getProximoNode() == NULL){
                aux->setProximoNode(NodeDesejado);
                fim = aux->getProximoNode();
                fim->setProximoNode(NULL);
            }
            else {//inserir em uma posiçao do meio~
                NodeDesejado->setProximoNode(aux->getProximoNode());
                aux->setProximoNode(NodeDesejado);
            }
        }
     }
 }
//obs: como essa função acima será usada apenas para a troca de elementos,
// não irá aumentar a QntPokemonsBatalhaveis

//está trocando os Nodes da posicao1 e da posicao2 de lugar
bool Lista::TrocaElementos(int posicao1, int posicao2){
    if(posicao1 < posicao2){
        if(posicao1 > 0 && posicao1 <= getTamanho()){
            Node* Elemento2 = RemoverElemento(posicao2);
            Node* Elemento1 = RemoverElemento(posicao1);
            InserirElemento(Elemento2, posicao1);
            InserirElemento(Elemento1, posicao2);
            return true;
        }
        return false;
    }else{
        if(posicao2 > 0 && posicao2 <= getTamanho()){
            Node* Elemento1 = RemoverElemento(posicao1);
            Node* Elemento2 = RemoverElemento(posicao2);
            InserirElemento(Elemento1, posicao2);
            InserirElemento(Elemento2, posicao1);
            return true;
        }
        return false;
    }
}

//MÉTODOS MAIS RELACIONADOS AO FUNCIONAMENTO DO JOGO EM SI
int Lista::getQntPokemonsBatalhaveis(){
    Pokemon* Aux = getPokemon(0);
    int qntPokemonsBolsa = 6;
    int qntPokemonsVivos = 0;
    if(getTamanho() < 6)
        qntPokemonsBolsa = getTamanho();
    for(int i=0; i<qntPokemonsBolsa; i++){
        Aux = getPokemon(i);
        if(Aux->estaVivo())
            qntPokemonsVivos++;
    }
    return qntPokemonsVivos;
}

//retorna o pokemon ""por referência"" do Node desejado
Pokemon* Lista::getPokemon(int posicao){
    Node* nodeDesejado = getNode(posicao);
    return (nodeDesejado->getPokemon());
}

//retorna um ponteiro para o Node/ endereço do Node da posicao desejada
Node* Lista::getNode(int posicao){
    if(posicao <= getTamanho()){
        Node* Aux = inicio;
        for(int i=0; i<posicao;i++)
            Aux = Aux->getProximoNode();
        return (Aux);
    }
    return 0;
}

//restaura a vida de todos os pokemons sem vida
void Lista::CurarPokemons(){
    Pokemon* Aux = getPokemon(0);
    int QntPokemonsCurar = 20;
    if(getTamanho() < 20){
        QntPokemonsCurar = getTamanho();
    }

    for(int i=0; i < QntPokemonsCurar; i++){
        Aux = getPokemon(i);
        Aux->curaVida();
    }
}

void Lista::CurarTodaLista(){
    Pokemon* Aux = getPokemon(0);

    for(int i=0; i<getTamanho(); i++){
        Aux = getPokemon(i);
        Aux->curaVida();
    }
}

//retorna o pokemon que vai batalhar & no parametro "posicao", passa qual a posicao desse pokemon
Pokemon* Lista::pokemonQueVaiBatalhar(int* posicao){
    if(getQntPokemonsBatalhaveis() != 0){
        if(getPokemon(0)->estaVivo()) {
            *posicao = 1;
            return getPokemon(0);
        } else if(getPokemon(1)->estaVivo()) {
            *posicao = 2;
            return getPokemon(1);
        } else if(getPokemon(2)->estaVivo()) {
            *posicao = 3;
            return getPokemon(2);
        } else if(getPokemon(3)->estaVivo()) {
            *posicao = 4;
            return getPokemon(3);
        } else if(getPokemon(4)->estaVivo()) {
            *posicao = 5;
            return getPokemon(4);
        } else if(getPokemon(5)->estaVivo()) {
            *posicao = 6;
            return getPokemon(5);
        }
    }
    return (NULL);
}