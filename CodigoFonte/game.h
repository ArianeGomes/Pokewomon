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

//Defini��es
#define LarguraTela 800
#define AlturaTela 600
#define LarguraPersonagem 27
#define AlturaPersonagem 31
#define LarguraCentro 78
#define AlturaCentro 68
#define AlturaCentro2 62
#define TamanhoPlacaCentro 278
#define EscalaCentro 2.0
#define EscalaPersonagem 1.0
#define EscalaPersonagemCentro 2.5
#define EscalaLider 2.7
#define EscalaPokemonLuta 2.5
#define EscalaPokemonBolsa 0.7

class Jogo{
    public:
        Jogo();
        //Fun��o usada para jogar novamente
        void Reseta();
        //Fun��es usadas para verificar se o bot�o foi pressionado e trocar as sprites
        bool VerificaBotao(sf::Vector2i position, sf::Sprite Sprite);
        bool AtualizaBotao(sf::Event Event, sf::Vector2i position, sf::Sprite &Sprite, sf::IntRect rectSourceSprite);
        void CarregaImagens();
        void CarregaSons();
        void PosicaoMouse();
        void MovimentoPersonagem();
        //Fun��es de ataque para a luta e batalha
        void AtaqueCompleto(Pokemon* seuPokemon, Pokemon* Oponente);
        void RecebeAtaque(Pokemon* seuPokemon, Pokemon* Oponente);
        void Ataca(Pokemon* seuPokemon, Pokemon* Oponente);
        void Batalha();
        //Fun��es para comprar pokebolas
        void setQntMoedas(int valor);
        int derrubaMoedas(int valor);
        bool setQntPokebolas(int valor);
        bool CapturarPokemon(Pokemon* PokemonCapturar);
        bool ComprarPokebola();
        void Eventos();
        //Cen�rios
        void Menu();
        void Instrucao();
        void TelaCenarioPokemonInicial();
        void TelaCenarioPrincipal();
        void TelaCenarioCentro();
        void TelaCenarioGinasio();
        void TelaCenarioLuta();
        void TelaCenarioBatalha();
        void TelaCenarioGanhou();
        void TelaCenarioPerdeu();
        //L�gica do jogo para qual tela ir� abrir
        void Run();

    private:
        //Janela
        sf::RenderWindow window;
        sf::Event Event;
        //Imagens
        //Menu
        sf::Texture CenarioMenuTexture, PlayTexture, InstruTexture, SairTexture;
        sf::Sprite CenarioMenuSprite, PlaySprite, InstruSprite, SairSprite;
        //Instru��es
        sf::Texture CenarioInstruTexture, VoltarTexture;
        sf::Sprite CenarioInstruSprite, VoltarSprite;
        //Jogo
        //Cenario menu
        sf::Texture Pokemon1Texture, Pokemon0Texture, Pokemon2Texture;
        sf::Sprite Pokemon1Sprite, Pokemon0Sprite, Pokemon2Sprite;
        //Cenario escolha pokemon
        sf::Texture CenarioEscolhaPokemonTexture;
        sf::Sprite CenarioEscolhaPokemonSprite;
        //Cenario principal
        sf::Texture PersonagemTexture, Cenario1Texture, CentroTexture, Centro2Texture;
        sf::Sprite PersonagemSprite, Cenario1Sprite, CentroSprite, Centro2Sprite;
        sf::Texture MatinhoTexture, Cerca1Texture, Cerca2Texture, RioTexture;
        sf::Sprite MatinhoSprite[16][35], Cerca1Sprite, Cerca2Sprite, RioSprite;
        //Placas e avisos - Cenario principal
        sf::Texture PlacaCentroTexture, AvisoPlacaCentroTexture, PlacaCenario2Texture, AvisoPlacaCenario2Texture;
        sf::Sprite PlacaCentroSprite, AvisoPlacaCentroSprite, PlacaCenario2Sprite, AvisoPlacaCenario2Sprite;
        //Gambiarras para colisao
        sf::Texture Cerca12Texture, Cerca22Texture;
        sf::Sprite Cerca12Sprite, Cerca22Sprite;
        //Cenario centro
        sf::Texture Cenario2Texture, BalcaoCentroTexture, MaquinaCentroTexture, MesaCentroTexture, PlantaCentroTexture;
        sf::Sprite Cenario2Sprite, BalcaoCentroSprite, MaquinaCentroSprite, MesaCentroSprite, PlantaCentroSprite;
        //Gambiarras para colis�o - Cenario centro
        sf::Texture BalcaoCentro2Texture, MaquinaCentro2Texture, MesaCentro2Texture, PlantaCentro2Texture;
        sf::Sprite BalcaoCentro2Sprite, MaquinaCentro2Sprite, MesaCentro2Sprite, PlantaCentro2Sprite;
        //M�quina - Cen�rio centro
        sf::Texture AvisoPokemonTexture, LixeiraTexture, BolsaInvisivelTexture;
        sf::Sprite AvisoPokemonSprite, LixeiraSprite, BolsaInvisivelSprite[20];
        //Healar e vender pokebolas - Cen�rio centro
        sf::Texture AvisoPokebolaTexture, HealarTexture, CompraPokebolaTexture;
        sf::Sprite AvisoPokebolaSprite, HealarSprite, CompraPokebolaSprite;
        //Cenario ginasio
        sf::Texture Cenario3Texture, LiderGinasioTexture, LiderGinasio2Texture, ChaoGinasioTexture, AvisoLiderTexture, BatalharTexture;
        sf::Sprite Cenario3Sprite, LiderGinasioSprite, LiderGinasio2Sprite, ChaoGinasioSprite, AvisoLiderSprite, BatalharSprite;;
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
        //Cenario Game over e vit�ria
        sf::Texture GameOverTexture, GanhouTexture, BotaoGanhouTexture, BotaoPerdeuTexture;
        sf::Sprite GameOverSprite, GanhouSprite, BotaoGanhouSprite, BotaoPerdeuSprite;
        //Velocidade de movimento da personagem
        sf::Vector2f Cima, Baixo, Esquerda, Direita;
        //Movimento personagem
        sf::Vector2i AtualizaPersonagem;
        sf::Clock clock;
        //Verifica posi��o do mouse
        sf::Vector2i position;
        //Atualiza imagem do bot�o
        sf::IntRect rectSourceSprite, rectSourceSprite2;
        //Sons
        sf::Texture SomTexture;
        sf::Sprite SomSprite;
        sf::Music PrincipalMusic, BatalhaMusic, CentroMusic, GanhouMusic, LutaMusic, PerdeuMusic;

        //Bot�o
        int Sair, Start, Voltar, Instrucoes, Atacar, Fugir, Pokemon0, Pokemon1, Pokemon2;
        //Telas
        int PokemonInicial, CenarioPrincipal, CenarioGinasio, CenarioCentro;
        int CenarioLuta, CenarioGanhou, CenarioPerdeu, CenarioBatalha;
        //Moedas e pokebolas
        int moedas, pokebolas;
        //Tamanhos atualizados - personagem, centro e placa centro
        int AlturaPersonagemAtualizada, LarguraPersonagemAtualizada, TamanhoPlacaCentroAtualizada;
        int AlturaCentroAtualizada, AlturaCentroAtualizada2, LarguraCentroAtualizada;
        //Pokemon escolhido para come�ar o jogo e pokemon que est� lutando
        int PokemonLuta, PokemonEscolha;
        //Controla a continuidade da personagem
        float delta;
        //Para saber qual pokemon aliado e inimigo est� lutando e printar na tela
        int posicaoDoSeuPokemon, posicaoAdversario;
        //Auxiliar
        int i, j, inicio, auxID, Music;
        bool botaoFugir;

        //Ponteiros que v�o apontar para os pokemons que est�o batalhando
        Pokemon *seuPokemonBatalhando, *pokemonAdversarioBatalhando;

        //Lista de pokemons
        Lista PokemonsCapturaveis, batalhaGinasio, SeusPokemons;
};
#endif // GAME_H
