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

#define quantidadePokemon 34

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
        void CarregaPokemon(int a);
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
        void TelaPrimeiroCenario();
        void TelaSegundoCenario();
        void TelaTerceiroCenario();
        void TelaQuartoCenario();
        void TelaCenarioCentro();
        void TelaCenarioGinasio1();
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

        //Cenario escolha pok�mon
        sf::Texture Pokemon1Texture, Pokemon0Texture, Pokemon2Texture, CenarioEscolhaPokemonTexture;
        sf::Sprite Pokemon1Sprite, Pokemon0Sprite, Pokemon2Sprite, CenarioEscolhaPokemonSprite;

        //Primeiro Cen�rio
        sf::Texture PersonagemTexture, PrimeiroCenarioTexture, CentroTexture, Centro2Texture;
        sf::Sprite PersonagemSprite, PrimeiroCenarioSprite, CentroSprite, Centro2Sprite;

        sf::Texture MatinhoTexture, Cerca1Texture, Cerca12Texture, Cerca22Texture, Cerca2Texture, 
        RioTexture, Arvore1Texture;
        sf::Sprite MatinhoSprite[16][35], Cerca1Sprite, Cerca12Sprite, Cerca22Sprite, Cerca2Sprite, 
        RioSprite, Arvore1Sprite;

        sf::Texture PlacaCentroTexture, AvisoPlacaCentroTexture, PlacaCenario2Texture, AvisoPlacaCenario2Texture;
        sf::Sprite PlacaCentroSprite, AvisoPlacaCentroSprite, PlacaCenario2Sprite, AvisoPlacaCenario2Sprite;

        //Segundo Cen�rio
        sf::Texture SegundoCenarioTexture, LagoTexture, MorroTexture;
        sf::Sprite SegundoCenarioSprite, LagoSprite, MorroSprite;

        sf::Texture ArvoresBaixo1Texture, ArvoresBaixo2Texture, ArvoresCimaTexture, ArvoresDireitaTexture, 
        ArvoresEsquerdaTexture, ArvoresCutTexture, ArvoreTexture;
        sf::Sprite ArvoresBaixo1Sprite, ArvoresBaixo2Sprite, ArvoresCimaSprite, ArvoresDireitaSprite, 
        ArvoresEsquerdaSprite, ArvoresCutSprite, ArvoreSprite;

        sf::Texture CercaHorizontal1Texture, CercaHorizontal2Texture, CercaVerticalTexture;
        sf::Sprite CercaHorizontal1Sprite, CercaHorizontal2Sprite, CercaVerticalSprite;

        //Terceiro Cen�rio
        sf::Texture TerceiroCenarioTexture, CantoCimaTexture, CantoEsquerdaTexture;
        sf::Sprite TerceiroCenarioSprite, CantoCimaSprite, CantoEsquerdaSprite;

        sf::Texture CantoInferior1Texture, CantoInferior2Texture, CantoInferior3Texture;
        sf::Sprite CantoInferior1Sprite, CantoInferior2Sprite, CantoInferior3Sprite;

        sf::Texture PedrasDireita1Texture, PedrasDireita2Texture, PedrasEsquerdaTexture, PedrasPassagemTexture;
        sf::Sprite PedrasDireita1Sprite, PedrasDireita2Sprite, PedrasEsquerdaSprite, PedrasPassagemSprite;

        //Quarto Cen�rio
        sf::Texture QuartoCenarioTexture, OceanoInternoBaixo1Texture, OceanoInternoBaixo2Texture;
        sf::Sprite QuartoCenarioSprite, OceanoInternoBaixo1Sprite, OceanoInternoBaixo2Sprite;

        sf::Texture OceanoExternoBaixoTexture, OceanoExternoCimaTexture, OceanoExternoDireitaTexture, 
        OceanoExternoEsquerdaTexture;
        sf::Sprite OceanoExternoBaixoSprite, OceanoExternoCimaSprite, OceanoExternoDireitaSprite, 
        OceanoExternoEsquerdaSprite;

        sf::Texture OceanoInternoCimaTexture, OceanoInternoDireitaTexture, OceanoInternoEsquerdaTexture;
        sf::Sprite OceanoInternoCimaSprite, OceanoInternoDireitaSprite, OceanoInternoEsquerdaSprite;

        //Cenario centro
        sf::Texture Cenario2Texture, BalcaoCentroTexture, MaquinaCentroTexture, MesaCentroTexture, PlantaCentroTexture;
        sf::Sprite Cenario2Sprite, BalcaoCentroSprite, MaquinaCentroSprite, MesaCentroSprite, PlantaCentroSprite;

        sf::Texture BalcaoCentro2Texture, MaquinaCentro2Texture, MesaCentro2Texture, PlantaCentro2Texture;
        sf::Sprite BalcaoCentro2Sprite, MaquinaCentro2Sprite, MesaCentro2Sprite, PlantaCentro2Sprite;

        sf::Texture AvisoPokemonTexture, LixeiraTexture, BolsaInvisivelTexture;
        sf::Sprite AvisoPokemonSprite, LixeiraSprite, BolsaInvisivelSprite[20];

        sf::Texture AvisoPokebolaTexture, HealarTexture, CompraPokebolaTexture;
        sf::Sprite AvisoPokebolaSprite, HealarSprite, CompraPokebolaSprite;

        //Cenario ginasios
        sf::Texture CenarioGinasio1Texture, CenarioGinasio2Texture, CenarioGinasio3Texture;
        sf::Sprite CenarioGinasio1Sprite, CenarioGinasio2Sprite, CenarioGinasio3Sprite;

        //Cenario ginasio 1
        sf::Texture Ginasio1Texture, Ginasio1MenorTexture, LiderGinasio1Texture, LiderGinasio1ColisaoTexture;
        sf::Sprite Ginasio1Sprite, Ginasio1MenorSprite, LiderGinasio1Sprite, LiderGinasio1ColisaoSprite;

        sf::Texture AvisoLiderTexture, BatalharTexture;
        sf::Sprite AvisoLiderSprite, BatalharSprite;

        //Cenario ginasio 2
        sf::Texture Ginasio2Texture, Ginasio2MenorTexture, LiderGinasio2Texture, LiderGinasio2ColisaoTexture;
        sf::Sprite Ginasio2Sprite, Ginasio2MenorSprite, LiderGinasio2Sprite, LiderGinasio2ColisaoSprite;

        //Cenario ginasio 3
        sf::Texture LiderGinasio3Texture, LiderGinasio3ColisaoTexture;
        sf::Sprite LiderGinasio3Sprite, LiderGinasio3ColisaoSprite;

        //Cenario luta
        sf::Texture CenarioLutaTexture, VidaTexture, AtacarTexture, FugirTexture;
        sf::Sprite CenarioLutaSprite, VidaSprite[12], AtacarSprite, FugirSprite;

        //Cenario batalha
        sf::Sprite PokemonAdversarioSprite[quantidadePokemon];

        //Pokemons e bolsa pokemon
        sf::Texture InvisivelTexture, PokemonTexture[quantidadePokemon], PokemonMortoTexture[quantidadePokemon],
        PokemonBordaTexture[quantidadePokemon], PokemonBordaMortoTexture[quantidadePokemon], BolsaTexture, 
        ForteTexture, FracoTexture, MedioTexture;

        sf::Sprite InvisivelSprite[2], PokemonSprite[quantidadePokemon], PokemonMortoSprite[quantidadePokemon], 
        PokemonBordaSprite[quantidadePokemon], PokemonBordaMortoSprite[quantidadePokemon], BolsaSprite, 
        ForteSprite[2], FracoSprite[2], MedioSprite[2];

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
        int PokemonInicial, PrimeiroCenario, SegundoCenario, TerceiroCenario, QuartoCenario;
        int CenarioGinasio1, CenarioGinasio2, CenarioGinasio3, CenarioCentro;
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
        int i, j, inicio, auxID, Music, cenarioAnterior;
        bool botaoFugir;

        //Ponteiros que v�o apontar para os pokemons que est�o batalhando
        Pokemon *seuPokemonBatalhando, *pokemonAdversarioBatalhando;

        //Lista de pokemons
        Lista PokemonsCapturaveis, BatalhaGinasio1, BatalhaGinasio2, BatalhaGinasio3, SeusPokemons;
};
#endif // GAME_H
