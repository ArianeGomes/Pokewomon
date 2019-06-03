#ifndef GAME_H
#define GAME_H

#include "pokemon.h"
#include "node.h"
#include "lista.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Definições
#define LarguraTela 800
#define AlturaTela 600
#define LarguraPersonagem 27
#define AlturaPersonagem 31
#define LarguraCentro 78
#define AlturaCentro 68
#define AlturaCentro2 62
#define TamanhoPlacaCentro 278
#define EscalaCentro 1.5
#define EscalaPersonagem 0.9
#define EscalaPersonagemCentro 2.5
#define EscalaLider 2.7
#define EscalaPokemonLuta 2.5
#define EscalaPokemonBolsa 0.7
#define quantidadePokemon 18 

class Jogo{
    public:
        Jogo();
        //Função usada para jogar novamente
        void Reseta();
        //Funções usadas para verificar se o botão foi pressionado e trocar as sprites
        bool VerificaBotao(sf::Vector2i position, sf::Sprite Sprite);
        bool AtualizaBotao(sf::Event Event, sf::Vector2i position, sf::Sprite &Sprite, sf::IntRect rectSourceSprite);
        void CarregaImagens();
        void CarregaSons();
        void CarregaPokemon(int a);
        void PosicaoMouse();
        void MovimentoPersonagem();
        //Funções de ataque para a luta e batalha
        void AtaqueCompleto(Pokemon* seuPokemon, Pokemon* Oponente);
        void RecebeAtaque(Pokemon* seuPokemon, Pokemon* Oponente);
        void Ataca(Pokemon* seuPokemon, Pokemon* Oponente);
        void Batalha();
        //Funções para comprar pokebolas
        void setQntMoedas(int valor);
        int derrubaMoedas(int valor);
        bool setQntPokebolas(int valor);
        bool CapturarPokemon(Pokemon* PokemonCapturar);
        bool ComprarPokebola();
        void Eventos();
        //Cenários
        void Menu();
        void Instrucao();
        void TelaCenarioPokemonInicial();
        void TelaPrimeiroCenario();
        void TelaSegundoCenario();
        void TelaCenarioCentro();
        void TelaCenarioGinasio1();
        void TelaCenarioLuta();
        void TelaCenarioBatalha();
        void TelaCenarioGanhou();
        void TelaCenarioPerdeu();
        //Lógica do jogo para qual tela irá abrir
        void Run();

    private:
        //Janela
        sf::RenderWindow window;
        sf::Event Event;

        //Imagens
        //Menu
        sf::Texture CenarioMenuTexture, PlayTexture, InstruTexture, SairTexture;
        sf::Sprite CenarioMenuSprite, PlaySprite, InstruSprite, SairSprite;

        //Instruções
        sf::Texture CenarioInstruTexture, VoltarTexture;
        sf::Sprite CenarioInstruSprite, VoltarSprite;
        
        //Cenario escolha pokémon
        sf::Texture Pokemon1Texture, Pokemon0Texture, Pokemon2Texture, CenarioEscolhaPokemonTexture;
        sf::Sprite Pokemon1Sprite, Pokemon0Sprite, Pokemon2Sprite, CenarioEscolhaPokemonSprite;

        //Primeiro Cenário
        sf::Texture PersonagemTexture, PrimeiroCenarioTexture, CentroTexture, Centro2Texture;
        sf::Sprite PersonagemSprite, PrimeiroCenarioSprite, CentroSprite, Centro2Sprite;

        sf::Texture MatinhoTexture, Cerca1Texture, Cerca12Texture, Cerca22Texture, Cerca2Texture, RioTexture, Arvore1Texture;
        sf::Sprite MatinhoSprite[16][35], Cerca1Sprite, Cerca12Sprite, Cerca22Sprite, Cerca2Sprite, RioSprite, Arvore1Sprite;

        sf::Texture PlacaCentroTexture, AvisoPlacaCentroTexture, PlacaCenario2Texture, AvisoPlacaCenario2Texture;
        sf::Sprite PlacaCentroSprite, AvisoPlacaCentroSprite, PlacaCenario2Sprite, AvisoPlacaCenario2Sprite;

        //Segundo Cenário
        sf::Texture SegundoCenarioTexture, Ginasio1Texture, Ginasio1MenorTexture, LagoTexture, MorroTexture;
        sf::Sprite SegundoCenarioSprite, Ginasio1Sprite, Ginasio1MenorSprite, LagoSprite, MorroSprite;

        sf::Texture ArvoresBaixo1Texture, ArvoresBaixo2Texture, ArvoresCimaTexture, ArvoresDireitaTexture, ArvoresEsquerdaTexture, ArvoresCutTexture, ArvoreTexture;
        sf::Sprite ArvoresBaixo1Sprite, ArvoresBaixo2Sprite, ArvoresCimaSprite, ArvoresDireitaSprite, ArvoresEsquerdaSprite, ArvoresCutSprite, ArvoreSprite;

        sf::Texture CercaHorizontal1Texture, CercaHorizontal2Texture, CercaVerticalTexture;
        sf::Sprite CercaHorizontal1Sprite, CercaHorizontal2Sprite, CercaVerticalSprite;

        //Cenario centro
        sf::Texture Cenario2Texture, BalcaoCentroTexture, MaquinaCentroTexture, MesaCentroTexture, PlantaCentroTexture;
        sf::Sprite Cenario2Sprite, BalcaoCentroSprite, MaquinaCentroSprite, MesaCentroSprite, PlantaCentroSprite;

        sf::Texture BalcaoCentro2Texture, MaquinaCentro2Texture, MesaCentro2Texture, PlantaCentro2Texture;
        sf::Sprite BalcaoCentro2Sprite, MaquinaCentro2Sprite, MesaCentro2Sprite, PlantaCentro2Sprite;

        sf::Texture AvisoPokemonTexture, LixeiraTexture, BolsaInvisivelTexture;
        sf::Sprite AvisoPokemonSprite, LixeiraSprite, BolsaInvisivelSprite[20];

        sf::Texture AvisoPokebolaTexture, HealarTexture, CompraPokebolaTexture;
        sf::Sprite AvisoPokebolaSprite, HealarSprite, CompraPokebolaSprite;

        //Cenario ginasio 1
        sf::Texture LiderGinasioTexture, LiderGinasio2Texture, AvisoLiderTexture, BatalharTexture;
        sf::Sprite LiderGinasioSprite, LiderGinasio2Sprite, AvisoLiderSprite, BatalharSprite;

        //Cenario luta
        sf::Texture CenarioLutaTexture, VidaTexture, AtacarTexture, FugirTexture;
        sf::Sprite CenarioLutaSprite, VidaSprite[12], AtacarSprite, FugirSprite;

        //Cenario batalha
        sf::Sprite PokemonAdversarioSprite[9];

        //Pokemons e bolsa pokemon
        sf::Texture InvisivelTexture, PokemonTexture[9], PokemonMortoTexture[9], PokemonBordaTexture[9], PokemonBordaMortoTexture[9], BolsaTexture, ForteTexture, FracoTexture, MedioTexture;
        sf::Sprite InvisivelSprite[2], PokemonSprite[9], PokemonMortoSprite[9], PokemonBordaSprite[9], PokemonBordaMortoSprite[9], BolsaSprite, ForteSprite[2], FracoSprite[2], MedioSprite[2];
        
        //Quantidade de moedas e pokebolas
        sf::Texture QuantidadeTexture;
        sf::Sprite QuantidadeMoedasSprite[21], QuantidadePokebolasSprite[21];

        //Cenario Game over e vitória
        sf::Texture GameOverTexture, GanhouTexture, BotaoGanhouTexture, BotaoPerdeuTexture;
        sf::Sprite GameOverSprite, GanhouSprite, BotaoGanhouSprite, BotaoPerdeuSprite;

        //Velocidade de movimento da personagem
        sf::Vector2f Cima, Baixo, Esquerda, Direita;

        //Movimento personagem
        sf::Vector2i AtualizaPersonagem;
        sf::Clock clock;

        //Verifica posição do mouse
        sf::Vector2i position;

        //Atualiza imagem do botão
        sf::IntRect rectSourceSprite, rectSourceSprite2;

        //Sons
        sf::Texture SomTexture;
        sf::Sprite SomSprite;
        sf::Music PrincipalMusic, BatalhaMusic, CentroMusic, GanhouMusic, LutaMusic, PerdeuMusic;

        //Botão
        int Sair, Start, Voltar, Instrucoes, Atacar, Fugir, Pokemon0, Pokemon1, Pokemon2;

        //Telas
        int PokemonInicial, PrimeiroCenario, SegundoCenario, TerceiroCenario, CenarioGinasio1, CenarioCentro;
        int CenarioLuta, CenarioGanhou, CenarioPerdeu, CenarioBatalha;

        //Moedas e pokebolas
        int moedas, pokebolas;

        //Tamanhos atualizados - personagem, centro e placa centro
        int AlturaPersonagemAtualizada, LarguraPersonagemAtualizada, TamanhoPlacaCentroAtualizada;
        int AlturaCentroAtualizada, AlturaCentroAtualizada2, LarguraCentroAtualizada;

        //Pokemon escolhido para começar o jogo e pokemon que está lutando
        int PokemonLuta, PokemonEscolha;

        //Controla a continuidade da personagem
        float delta;

        //Para saber qual pokemon aliado e inimigo está lutando e printar na tela
        int posicaoDoSeuPokemon, posicaoAdversario;

        //Auxiliar
        int i, j, inicio, auxID, Music, cenarioAnterior;
        bool botaoFugir;

        //Ponteiros que vão apontar para os pokemons que estão batalhando
        Pokemon *seuPokemonBatalhando, *pokemonAdversarioBatalhando;

        //Lista de pokemons
        Lista PokemonsCapturaveis, batalhaGinasio, SeusPokemons;
};
#endif // GAME_H
