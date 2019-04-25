# Pokéwomon
> Pokéwomon é um jogo baseado em Pokémon que possui o objetivo de incluir a comunidade feminina nos jogos e na computação. Devido a isso, foi desenvolvido somente com personagens mulheres e pokémons específicos.

[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]

O jogo Pokéwomon possui como objetivo a captura de variados pokémons através de
lutas com pokémons selvagens para que, então, o jogador se direcione ao Ginásio com o intuito
de combater a Líder de Ginásio; sendo que esta acontece contra todos os pokémons do mestre
adversário. Dessa forma, caso o jogador perca todos os seus pokémons (vida zero) de alguma
forma, o jogo é encerrado.

Realiza-se também a compra de pokébolas, através de moedas ganhas em batalhas
vencidas. Vale destacar que só é possível realizar capturas caso possua-se pelo menos uma
pokébola, as quais são compradas no Centro Pokéwomon, no qual também é feita a restauração
das vidas dos personagens.

![](../header.png)

## Instalação

### Linux:

Instalando SFML:

```sh
sudo apt-get install libsfml-dev
```

Compilando arquivos:

```sh
g++ -c /your/path/main.cpp /your/path/node.cpp /your/path/lista.cpp /your/path/pokemon.cpp /your/path/game.cpp 
g++ main.o node.o lista.o pokemon.o game.o -o pokewomon -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```