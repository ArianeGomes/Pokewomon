#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
#define EscalaPersonagemGinasio 1.5
#define EscalaPokemonLuta 2.5
#define EscalaPokemonBolsa 0.7
#define quantidadePokemon 34
#define qtdeColisoesGinasio1 10
#define qtdeColisoesGinasio2 14

enum direcoes {esquerda, direita, baixo, cima};

Jogo::Jogo(){
    //Menu - botão
    Sair = 0;
    Start = 0;
    Instrucoes = 0;

    //Instruções - botão
    Voltar = 0;

    //Luta e batalha - botão
    Atacar = 0;
    Fugir = 0;

    //Tela pokemon inicial - botão
    Pokemon0 = 0;
    Pokemon1 = 0;
    Pokemon2 = 0;

    //Telas
    PokemonInicial = 1;
    PrimeiroCenario = 0;
    SegundoCenario = 0;
    CenarioGinasio1 = 0;
    CenarioCentro = 0;
    CenarioLuta = 0;
    CenarioBatalha = 0;
    CenarioGanhou = 0;
    CenarioPerdeu = 0;

    //Moedas e Pokebolas
    moedas = 0;
    pokebolas = 5;

    //Auxiliar
    i = 0;
    j = 0;
    inicio = 1;
    auxID = -1;
    botaoFugir = true;
    Music = 1;
    cenarioAnterior = 0;

    //Controle da continuidade da personagem
    delta = 0;

    //Atualiza imagem da personagem
    AtualizaPersonagem.x = 0;
    AtualizaPersonagem.y = 1;

    //Velocidade de movimento da personagem
    Cima.x = 0;
    Cima.y = 120;
    Baixo.x = 0;
    Baixo.y = 120;
    Esquerda.x = 120;
    Esquerda.y = 0;
    Direita.x = 120;
    Direita.y = 0;

    //Largura e altura redimensionada da personagem
    AlturaPersonagemAtualizada = 0;
    LarguraPersonagemAtualizada = 0;

    //Largura e altura redimensionada do centro
    AlturaCentroAtualizada = 0;
    LarguraCentroAtualizada = 0;

    //Tamanho redimensionado da placa do centro
    TamanhoPlacaCentroAtualizada = 0;

    //Lista pokemons capturáveis
    for(i=0;i<quantidadePokemon;i++)
        PokemonsCapturaveis.InserirNoFinal(i);

    //Lista pokemons inimigos ginásio
    for(i = 16; i < quantidadePokemon; i++) {
        if (i < 22)
            BatalhaGinasio1.InserirNoFinal(i);
        else if (i < 28)
            BatalhaGinasio2.InserirNoFinal(i);
        else
            BatalhaGinasio3.InserirNoFinal(i);
        
    }
    BatalhaGinasio1.CurarTodaLista();
    BatalhaGinasio2.CurarTodaLista();
    BatalhaGinasio3.CurarTodaLista();
}

void Jogo::Reseta(){
    //Menu - botão
    Sair = 0;
    Start = 0;
    Instrucoes = 0;

    //Instruções - botão
    Voltar = 0;

    //Luta e batalha - botão
    Atacar = 0;
    Fugir = 0;

    //Tela pokemon inicial - botão
    Pokemon0 = 0;
    Pokemon1 = 0;
    Pokemon2 = 0;

    //Telas
    PokemonInicial = 1;
    PrimeiroCenario = 0;
    SegundoCenario = 0;
    CenarioGinasio1 = 0;
    CenarioCentro = 0;
    CenarioLuta = 0;
    CenarioBatalha = 0;
    CenarioGanhou = 0;
    CenarioPerdeu = 0;

    //Moedas e Pokebolas
    moedas = 0;
    pokebolas = 5;

    //Auxiliar
    i = 0;
    j = 0;
    inicio = 1;
    auxID = -1;
    botaoFugir = true;
    Music = 1;
    cenarioAnterior = 0;

    //Controle da continuidade da personagem
    delta = 0;

    //Atualiza imagem da personagem
    AtualizaPersonagem.x = 0;
    AtualizaPersonagem.y = 1;

    //Velocidade de movimento da personagem
    Cima.x = 0;
    Cima.y = 120;
    Baixo.x = 0;
    Baixo.y = 120;
    Esquerda.x = 120;
    Esquerda.y = 0;
    Direita.x = 120;
    Direita.y = 0;

    //Reseta a lista dos seus pokemons para começar tudo de novo
    SeusPokemons.RetirarTodosElementos();

    //Cura a vida de todos os pokemons da batalha
    BatalhaGinasio1.CurarTodaLista();
    BatalhaGinasio2.CurarTodaLista();
    BatalhaGinasio3.CurarTodaLista();

    //Seta a posição da personagem e a escala
    PersonagemSprite.setPosition(0,155);
    PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
    AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
    LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;

    //Atualiza a imagem do som
    SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
}

bool Jogo::VerificaBotao(sf::Vector2i position, sf::Sprite Sprite){
    //Verifica posição
    int width = Sprite.getGlobalBounds().width;
    int height = Sprite.getGlobalBounds().height;

    if (position.x>Sprite.getPosition().x && position.x<(Sprite.getPosition().x + width)){
        if (position.y>Sprite.getPosition().y && position.y<(Sprite.getPosition().y + height)){
            return true;
        }
    }
    return false;
}

bool Jogo::AtualizaBotao(sf::Event Event, sf::Vector2i position, sf::Sprite &Sprite, sf::IntRect rectSourceSprite){
    int flag = 0;
    if (Event.type == sf::Event::MouseButtonPressed || sf::Joystick::isButtonPressed(0, 2)){
        if (Event.mouseButton.button == sf::Mouse::Left){
            if(VerificaBotao(position, Sprite)){
                rectSourceSprite.top = 142;
                Sprite.setTextureRect(rectSourceSprite);
                flag = 1;
                return 1;
            }
        }
    }else if (Event.type == sf::Event::MouseButtonReleased){
        if (Event.mouseButton.button == sf::Mouse::Left){
            flag = 0;
            if(VerificaBotao(position, Sprite))
                rectSourceSprite.top = 74;
            else
                rectSourceSprite.top = 0;
        }
    }else if (Event.type == sf::Event::MouseMoved){
        if(flag == 0){
            if(VerificaBotao(position, Sprite))
                rectSourceSprite.top = 74;
            else
                rectSourceSprite.top = 0;
        }
    }
    Sprite.setTextureRect(rectSourceSprite);
    return 0;
}

void Jogo::CarregaImagens(){
    //*************************************************cenário Menu
    CenarioMenuTexture.loadFromFile("Imagens/Menu.png");
    CenarioMenuSprite.setTexture(CenarioMenuTexture);

    //Play
    PlayTexture.loadFromFile("Imagens/Botoes/BotaoJogar.png");
    rectSourceSprite = sf::IntRect(0, 0, 215, 79); //Corta a imagem
    PlaySprite = sf::Sprite(PlayTexture, rectSourceSprite);
    PlaySprite.setPosition(50, AlturaTela/2);

    //Instruções
    InstruTexture.loadFromFile("Imagens/Botoes/BotaoInstrucoes.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    InstruSprite = sf::Sprite(InstruTexture, rectSourceSprite);
    InstruSprite.setPosition(50, AlturaTela/2 + 80);

    //Sair
    SairTexture.loadFromFile("Imagens/Botoes/BotaoSair.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    SairSprite = sf::Sprite(SairTexture, rectSourceSprite);
    SairSprite.setPosition(50, AlturaTela/2 + 160);


    //***************************************************cenário Instruções
    CenarioInstruTexture.loadFromFile("Imagens/Instrucoes.png");
    CenarioInstruSprite.setTexture(CenarioInstruTexture);

    //botão voltar no cenário Instruções
    VoltarTexture.loadFromFile("Imagens/Botoes/BotaoVoltar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    VoltarSprite = sf::Sprite(VoltarTexture, rectSourceSprite);
    VoltarSprite.setPosition(LarguraTela - 250, AlturaTela - 120);


    //***************************************************cenário escolha pokemon
    CenarioEscolhaPokemonTexture.loadFromFile("Imagens/EscolhaPokemon.png");
    CenarioEscolhaPokemonSprite.setTexture(CenarioEscolhaPokemonTexture);
    CenarioEscolhaPokemonSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

    //Pokemons iniciais
    //Pokemon1
    Pokemon1Texture.loadFromFile("Imagens/Botoes/BotaoPokemon1.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon1Sprite = sf::Sprite(Pokemon1Texture, rectSourceSprite);
    Pokemon1Sprite.setPosition(124, 32);

    //Pokemon0
    Pokemon0Texture.loadFromFile("Imagens/Botoes/BotaoPokemon0.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon0Sprite = sf::Sprite(Pokemon0Texture, rectSourceSprite);
    Pokemon0Sprite.setPosition(238, 493);

    //Pokemon2
    Pokemon2Texture.loadFromFile("Imagens/Botoes/BotaoPokemon2.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon2Sprite = sf::Sprite(Pokemon2Texture, rectSourceSprite);
    Pokemon2Sprite.setPosition(585, 246);


    //*************************************************** Primeiro cenário
    PrimeiroCenarioTexture.loadFromFile("Imagens/Cenarios/PrimeiroCenario.png");
    PrimeiroCenarioSprite.setTexture(PrimeiroCenarioTexture);

    //Centro jogo
    CentroTexture.loadFromFile("Imagens/Colisao/Centro.png");
    CentroSprite.setTexture(CentroTexture);

    //Centro jogo Colisão
    Centro2Texture.loadFromFile("Imagens/Colisao/Centro2.png");
    Centro2Sprite.setTexture(Centro2Texture);
    Centro2Sprite.setScale(EscalaCentro, EscalaCentro);
    Centro2Sprite.setPosition(300,7);
    AlturaCentroAtualizada2 = AlturaCentro2 * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    //Placa centro jogo
    PlacaCentroTexture.loadFromFile("Imagens/Colisao/PlacaCentro.png");
    PlacaCentroSprite.setTexture(PlacaCentroTexture);
    PlacaCentroSprite.setPosition(272,128);

    //Aviso da placa do centro
    AvisoPlacaCentroTexture.loadFromFile("Imagens/Avisos/AvisoCentro.png");
    AvisoPlacaCentroSprite.setTexture(AvisoPlacaCentroTexture);
    AvisoPlacaCentroSprite.setPosition(285.5,500);

    //Placa ginásio
    PlacaCenario2Texture.loadFromFile("Imagens/Colisao/PlacaCenario2.png");
    PlacaCenario2Sprite.setTexture(PlacaCenario2Texture);
    PlacaCenario2Sprite.setPosition(784,122);

    //Aviso da placa do ginásio
    AvisoPlacaCenario2Texture.loadFromFile("Imagens/Avisos/AvisoGinasio.png");
    AvisoPlacaCenario2Sprite.setTexture(AvisoPlacaCenario2Texture);
    AvisoPlacaCenario2Sprite.setPosition(285.5,500);

    //Matinho
    MatinhoTexture.loadFromFile("Imagens/Matinho.png");

    //Cerca
    Cerca1Texture.loadFromFile("Imagens/Colisao/Cerca1.png");
    Cerca1Sprite.setTexture(Cerca1Texture);
    Cerca1Sprite.setPosition(0,128);

    Cerca2Texture.loadFromFile("Imagens/Colisao/Cerca2.png");
    Cerca2Sprite.setTexture(Cerca2Texture);
    Cerca2Sprite.setPosition(465,128);

    //Cerca Colisão
    Cerca12Texture.loadFromFile("Imagens/Colisao/Cerca12.png");
    Cerca12Sprite.setTexture(Cerca12Texture);
    Cerca12Sprite.setPosition(0,128);

    Cerca22Texture.loadFromFile("Imagens/Colisao/Cerca22.png");
    Cerca22Sprite.setTexture(Cerca22Texture);
    Cerca22Sprite.setPosition(465,128);

    //Rio
    RioTexture.loadFromFile("Imagens/Colisao/Rio.png");
    RioSprite.setTexture(RioTexture);
    RioSprite.setPosition(20,415);

    //Árvore
    Arvore1Texture.loadFromFile("Imagens/Colisao/Arvore1.png");
    Arvore1Sprite.setTexture(Arvore1Texture);
    Arvore1Sprite.setPosition(425,96);

    //Pokemon invisivel
    InvisivelTexture.loadFromFile("Imagens/Pokemons/PokemonInvisivel.png");
    InvisivelSprite[0].setTexture(InvisivelTexture);
    InvisivelSprite[1].setTexture(InvisivelTexture);
    InvisivelSprite[2].setTexture(InvisivelTexture);

    //Bolsa de pokémons
    BolsaTexture.loadFromFile("Imagens/Bolsa.png");
    BolsaSprite.setTexture(BolsaTexture);
    BolsaSprite.setPosition(495,9);

    //Personagem jogo
    PersonagemTexture.loadFromFile("Imagens/Personagens/Personagem.png");
    PersonagemSprite.setTexture(PersonagemTexture);
    PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
    PersonagemSprite.setPosition(0,155);
    AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
    LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;


    //***************************************************Segundo cenário
    SegundoCenarioTexture.loadFromFile("Imagens/Cenarios/SegundoCenario.png");
    SegundoCenarioSprite.setTexture(SegundoCenarioTexture);

    Ginasio1Texture.loadFromFile("Imagens/Colisao/Ginasio1.png");
    Ginasio1Sprite.setTexture(Ginasio1Texture);
    Ginasio1Sprite.setPosition(143,145);

    Ginasio1MenorTexture.loadFromFile("Imagens/Colisao/Ginasio1Menor.png");
    Ginasio1MenorSprite.setTexture(Ginasio1MenorTexture);
    Ginasio1MenorSprite.setPosition(143,145);

    LagoTexture.loadFromFile("Imagens/Colisao/Lago.png");
    LagoSprite.setTexture(LagoTexture);
    LagoSprite.setPosition(428,259);

    MorroTexture.loadFromFile("Imagens/Colisao/Morro.png");
    MorroSprite.setTexture(MorroTexture);
    MorroSprite.setPosition(333,105);

    //Árvores segundo cenário
    ArvoresBaixo1Texture.loadFromFile("Imagens/Colisao/ArvoresBaixo1.png");
    ArvoresBaixo1Sprite.setTexture(ArvoresBaixo1Texture);
    ArvoresBaixo1Sprite.setPosition(0,582);

    ArvoresBaixo2Texture.loadFromFile("Imagens/Colisao/ArvoresBaixo2.png");
    ArvoresBaixo2Sprite.setTexture(ArvoresBaixo2Texture);
    ArvoresBaixo2Sprite.setPosition(414,582);

    ArvoresCimaTexture.loadFromFile("Imagens/Colisao/ArvoresCima.png");
    ArvoresCimaSprite.setTexture(ArvoresCimaTexture);
    ArvoresCimaSprite.setPosition(0,0);

    ArvoresDireitaTexture.loadFromFile("Imagens/Colisao/ArvoresDireita.png");
    ArvoresDireitaSprite.setTexture(ArvoresDireitaTexture);
    ArvoresDireitaSprite.setPosition(LarguraTela - 64,0);

    ArvoresEsquerdaTexture.loadFromFile("Imagens/Colisao/ArvoresEsquerda.png");
    ArvoresEsquerdaSprite.setTexture(ArvoresEsquerdaTexture);
    ArvoresEsquerdaSprite.setPosition(0,107);

    ArvoresCutTexture.loadFromFile("Imagens/Colisao/ArvoresCut.png");
    ArvoresCutSprite.setTexture(ArvoresCutTexture);
    ArvoresCutSprite.setPosition(800,221);
    ArvoresCutSprite.setPosition(333,221);

    ArvoreTexture.loadFromFile("Imagens/Colisao/Arvore.png");
    ArvoreSprite.setTexture(ArvoreTexture);

    //Cercas segundo cenário
    CercaHorizontal1Texture.loadFromFile("Imagens/Colisao/CercaHorizontal1.png");
    CercaHorizontal1Sprite.setTexture(CercaHorizontal1Texture);
    CercaHorizontal1Sprite.setPosition(143,214);

    CercaHorizontal2Texture.loadFromFile("Imagens/Colisao/CercaHorizontal2.png");
    CercaHorizontal2Sprite.setTexture(CercaHorizontal2Texture);
    CercaHorizontal2Sprite.setPosition(60,308);

    CercaVerticalTexture.loadFromFile("Imagens/Colisao/CercaVertical.png");
    CercaVerticalSprite.setTexture(CercaVerticalTexture);
    CercaVerticalSprite.setPosition(327,18);

    //***************************************************Terceiro Cenário
    TerceiroCenarioTexture.loadFromFile("Imagens/Cenarios/TerceiroCenario.png");
    TerceiroCenarioSprite.setTexture(TerceiroCenarioTexture);

    //Ginásio do Terceiro Cenário
    Ginasio2Texture.loadFromFile("Imagens/Colisao/Ginasio2.png");
    Ginasio2Sprite.setTexture(Ginasio2Texture);
    Ginasio2Sprite.setPosition(612,-7);

    Ginasio2MenorTexture.loadFromFile("Imagens/Colisao/Ginasio2Menor.png");
    Ginasio2MenorSprite.setTexture(Ginasio2MenorTexture);
    Ginasio2MenorSprite.setPosition(612,-7);

    //Cantos do Terceiro Cenário
    CantoCimaTexture.loadFromFile("Imagens/Colisao/CantoCima.png");
    CantoCimaSprite.setTexture(CantoCimaTexture);
    CantoCimaSprite.setPosition(466, 225);

    CantoEsquerdaTexture.loadFromFile("Imagens/Colisao/CantoEsquerda.png");
    CantoEsquerdaSprite.setTexture(CantoEsquerdaTexture);
    CantoEsquerdaSprite.setPosition(466, 225);

    CantoInferior1Texture.loadFromFile("Imagens/Colisao/CantoInferior1.png");
    CantoInferior1Sprite.setTexture(CantoInferior1Texture);
    CantoInferior1Sprite.setPosition(466, 417);

    CantoInferior2Texture.loadFromFile("Imagens/Colisao/CantoInferior2.png");
    CantoInferior2Sprite.setTexture(CantoInferior2Texture);
    CantoInferior2Sprite.setPosition(592, 417);

    CantoInferior3Texture.loadFromFile("Imagens/Colisao/CantoInferior3.png");
    CantoInferior3Sprite.setTexture(CantoInferior3Texture);
    CantoInferior3Sprite.setPosition(752, 417);

    //Pedras do Terceiro Cenário
    PedrasDireita1Texture.loadFromFile("Imagens/Colisao/PedrasDireita1.png");
    PedrasDireita1Sprite.setTexture(PedrasDireita1Texture);
    PedrasDireita1Sprite.setPosition(577, 0);

    PedrasDireita2Texture.loadFromFile("Imagens/Colisao/PedrasDireita2.png");
    PedrasDireita2Sprite.setTexture(PedrasDireita2Texture);
    PedrasDireita2Sprite.setPosition(720, 0);

    PedrasPassagemTexture.loadFromFile("Imagens/Colisao/PedrasPassagem.png");
    PedrasPassagemSprite.setTexture(PedrasPassagemTexture);
    PedrasPassagemSprite.setPosition(304, 225);

    PedrasEsquerdaTexture.loadFromFile("Imagens/Colisao/PedrasEsquerda.png");
    PedrasEsquerdaSprite.setTexture(PedrasEsquerdaTexture);
    PedrasEsquerdaSprite.setPosition(0,0);

    //***************************************************Quarto Cenário
    QuartoCenarioTexture.loadFromFile("Imagens/Cenarios/QuartoCenario.png");
    QuartoCenarioSprite.setTexture(QuartoCenarioTexture);

    //Oceanos
    OceanoExternoCimaTexture.loadFromFile("Imagens/Colisao/OceanoExternoCima.png");
    OceanoExternoCimaSprite.setTexture(OceanoExternoCimaTexture);
    OceanoExternoCimaSprite.setPosition(0,134);

    OceanoExternoEsquerdaTexture.loadFromFile("Imagens/Colisao/OceanoExternoEsquerda.png");
    OceanoExternoEsquerdaSprite.setTexture(OceanoExternoEsquerdaTexture);
    OceanoExternoEsquerdaSprite.setPosition(123,294);

    OceanoExternoDireitaTexture.loadFromFile("Imagens/Colisao/OceanoExternoDireita.png");
    OceanoExternoDireitaSprite.setTexture(OceanoExternoDireitaTexture);
    OceanoExternoDireitaSprite.setPosition(624,294);

    OceanoExternoBaixoTexture.loadFromFile("Imagens/Colisao/OceanoExternoBaixo.png");
    OceanoExternoBaixoSprite.setTexture(OceanoExternoBaixoTexture);
    OceanoExternoBaixoSprite.setPosition(176,577);

    OceanoInternoCimaTexture.loadFromFile("Imagens/Colisao/OceanoInternoCima.png");
    OceanoInternoCimaSprite.setTexture(OceanoInternoCimaTexture);
    OceanoInternoCimaSprite.setPosition(224,321);

    OceanoInternoEsquerdaTexture.loadFromFile("Imagens/Colisao/OceanoInternoEsquerda.png");
    OceanoInternoEsquerdaSprite.setTexture(OceanoInternoEsquerdaTexture);
    OceanoInternoEsquerdaSprite.setPosition(224,340);

    OceanoInternoDireitaTexture.loadFromFile("Imagens/Colisao/OceanoInternoDireita.png");
    OceanoInternoDireitaSprite.setTexture(OceanoInternoDireitaTexture);
    OceanoInternoDireitaSprite.setPosition(541,340);

    OceanoInternoBaixo1Texture.loadFromFile("Imagens/Colisao/OceanoInternoBaixo1.png");
    OceanoInternoBaixo1Sprite.setTexture(OceanoInternoBaixo1Texture);
    OceanoInternoBaixo1Sprite.setPosition(224,526);

    OceanoInternoBaixo2Texture.loadFromFile("Imagens/Colisao/OceanoInternoBaixo2.png");
    OceanoInternoBaixo2Sprite.setTexture(OceanoInternoBaixo2Texture);
    OceanoInternoBaixo2Sprite.setPosition(432,526);

    //***************************************************cenário Centro
    Cenario2Texture.loadFromFile("Imagens/Cenarios/CenarioCentro.png");
    Cenario2Sprite.setTexture(Cenario2Texture);

    //Balcao do Centro
    BalcaoCentroTexture.loadFromFile("Imagens/Colisao/BalcaoCentro.png");
    BalcaoCentroSprite.setTexture(BalcaoCentroTexture);
    BalcaoCentroSprite.setPosition(51,81);

    //Balcao do Centro Colisão
    BalcaoCentro2Texture.loadFromFile("Imagens/Colisao/BalcaoCentro2.png");
    BalcaoCentro2Sprite.setTexture(BalcaoCentro2Texture);
    BalcaoCentro2Sprite.setPosition(51,81);

    //Planta do Centro
    PlantaCentroTexture.loadFromFile("Imagens/Colisao/PlantaCentro.png");
    PlantaCentroSprite.setTexture(PlantaCentroTexture);
    PlantaCentroSprite.setPosition(0,172);

    //Planta do Centro Colisão
    PlantaCentro2Texture.loadFromFile("Imagens/Colisao/PlantaCentro2.png");
    PlantaCentro2Sprite.setTexture(PlantaCentro2Texture);
    PlantaCentro2Sprite.setPosition(0,172);

    //Mesa do Centro
    MesaCentroTexture.loadFromFile("Imagens/Colisao/MesaCentro.png");
    MesaCentroSprite.setTexture(MesaCentroTexture);
    MesaCentroSprite.setPosition(694,164);

    //Mesa do Centro Colisão
    MesaCentro2Texture.loadFromFile("Imagens/Colisao/MesaCentro2.png");
    MesaCentro2Sprite.setTexture(MesaCentro2Texture);
    MesaCentro2Sprite.setPosition(694,164);

    //Maquina do Centro
    MaquinaCentroTexture.loadFromFile("Imagens/Colisao/MaquinaCentro.png");
    MaquinaCentroSprite.setTexture(MaquinaCentroTexture);
    MaquinaCentroSprite.setPosition(640,182);

    //Maquina do Centro Colisão
    MaquinaCentro2Texture.loadFromFile("Imagens/Colisao/MaquinaCentro2.png");
    MaquinaCentro2Sprite.setTexture(MaquinaCentro2Texture);
    MaquinaCentro2Sprite.setPosition(640,182);

    //cenário comprar pokebolas e healar pokemons
    AvisoPokebolaTexture.loadFromFile("Imagens/Avisos/AvisoPokebola.png");
    AvisoPokebolaSprite.setTexture(AvisoPokebolaTexture);
    AvisoPokebolaSprite.setPosition(95.5,450);

    //botão healar
    HealarTexture.loadFromFile("Imagens/Botoes/BotaoEncherVida.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    HealarSprite = sf::Sprite(HealarTexture, rectSourceSprite);
    HealarSprite.setPosition(200, 520);

    //botão comprar pokebola
    CompraPokebolaTexture.loadFromFile("Imagens/Botoes/BotaoPokebola.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    CompraPokebolaSprite = sf::Sprite(CompraPokebolaTexture, rectSourceSprite);
    CompraPokebolaSprite.setPosition(440, 520);

    //Aviso bolsa do centro
    AvisoPokemonTexture.loadFromFile("Imagens/Avisos/AvisoPokemons.png");
    AvisoPokemonSprite.setTexture(AvisoPokemonTexture);
    AvisoPokemonSprite.setPosition(LarguraTela/2 - 145.5,300);

    //Lixeira - para agir como botão
    LixeiraTexture.loadFromFile("Imagens/Lixeira.png");
    LixeiraSprite.setTexture(LixeiraTexture);
    LixeiraSprite.setPosition(LarguraTela/2 - 130.5,315);

    //Bolsa invisivel - para agir como botão
    BolsaInvisivelTexture.loadFromFile("Imagens/BolsaInvisivel.png");
    i = 0;
    j = 0;
    for(int a = 0; a < 20; a++){
        BolsaInvisivelSprite[a].setTexture(BolsaInvisivelTexture);
        if (a < 6){
            BolsaInvisivelSprite[a].setPosition(278+a*42, 359);
        }else if (a < 13){
            BolsaInvisivelSprite[a].setPosition(259+i*42, 457);
            i++;
        }else{
            BolsaInvisivelSprite[a].setPosition(259+j*42, 498);
            j++;
        }
    }


    //***************************************************cenário ginásio 1
    CenarioGinasio1Texture.loadFromFile("Imagens/Cenarios/CenarioGinasio1.png");
    CenarioGinasio1Sprite.setTexture(CenarioGinasio1Texture);

    //Lider ginásio
    LiderGinasio1Texture.loadFromFile("Imagens/Personagens/LiderGinasio1.png");
    LiderGinasio1Sprite.setTexture(LiderGinasio1Texture);
    LiderGinasio1Sprite.setPosition(380,290);
    LiderGinasio1Sprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);

    LiderGinasio1ColisaoTexture.loadFromFile("Imagens/Personagens/LiderGinasio1Colisao.png");
    LiderGinasio1ColisaoSprite.setTexture(LiderGinasio1ColisaoTexture);
    LiderGinasio1ColisaoSprite.setPosition(380,290);
    LiderGinasio1ColisaoSprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);

    //Aviso lider
    AvisoLiderTexture.loadFromFile("Imagens/Avisos/AvisoLider.png");
    AvisoLiderSprite.setTexture(AvisoLiderTexture);
    AvisoLiderSprite.setPosition(95.5,450);

    //botão batalhar com a líder
    BatalharTexture.loadFromFile("Imagens/Botoes/BotaoDesafiar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    BatalharSprite = sf::Sprite(BatalharTexture, rectSourceSprite);
    BatalharSprite.setPosition(320, 520);

    //Colisões ginásio 1
    for (int a = 0; a < qtdeColisoesGinasio1; a++){
        CarregaColisoes(a, 1);
        Ginasio1ColisoesSprite[a].setTexture(Ginasio1ColisoesTexture[a]);
    }

    Ginasio1ColisoesSprite[0].setPosition(0,582);
    Ginasio1ColisoesSprite[1].setPosition(0,0);
    Ginasio1ColisoesSprite[2].setPosition(574,0);
    Ginasio1ColisoesSprite[3].setPosition(0,0);
    Ginasio1ColisoesSprite[4].setPosition(534,259);
    Ginasio1ColisoesSprite[5].setPosition(198,299);
    Ginasio1ColisoesSprite[6].setPosition(439,360);
    Ginasio1ColisoesSprite[7].setPosition(183,360);
    Ginasio1ColisoesSprite[8].setPosition(322,456);
    Ginasio1ColisoesSprite[9].setPosition(447,455);

    //***************************************************cenário ginásio 2
    CenarioGinasio2Texture.loadFromFile("Imagens/Cenarios/CenarioGinasio2.png");
    CenarioGinasio2Sprite.setTexture(CenarioGinasio2Texture);

    //Lider ginásio
    LiderGinasio2Texture.loadFromFile("Imagens/Personagens/LiderGinasio2.png");
    LiderGinasio2Sprite.setTexture(LiderGinasio2Texture);
    LiderGinasio2Sprite.setPosition(380,290);
    LiderGinasio2Sprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);

    LiderGinasio2ColisaoTexture.loadFromFile("Imagens/Personagens/LiderGinasio2Colisao.png");
    LiderGinasio2ColisaoSprite.setTexture(LiderGinasio2ColisaoTexture);
    LiderGinasio2ColisaoSprite.setPosition(380,290);
    LiderGinasio2ColisaoSprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);
    /*
    //Aviso lider
    AvisoLiderTexture.loadFromFile("Imagens/Avisos/AvisoLider.png");
    AvisoLiderSprite.setTexture(AvisoLiderTexture);
    AvisoLiderSprite.setPosition(95.5,450);

    //botão batalhar com a líder
    BatalharTexture.loadFromFile("Imagens/Botoes/BotaoDesafiar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    BatalharSprite = sf::Sprite(BatalharTexture, rectSourceSprite);
    BatalharSprite.setPosition(320, 520);
    */

    //Colisões ginásio 2
    for (int a = 0; a < qtdeColisoesGinasio2; a++){
        CarregaColisoes(a, 2);
        Ginasio2ColisoesSprite[a].setTexture(Ginasio2ColisoesTexture[a]);
    }

    Ginasio2ColisoesSprite[0].setPosition(0,0);
    Ginasio2ColisoesSprite[1].setPosition(0,543);
    Ginasio2ColisoesSprite[2].setPosition(594,0);
    Ginasio2ColisoesSprite[3].setPosition(0,0);
    Ginasio2ColisoesSprite[4].setPosition(207,277);
    Ginasio2ColisoesSprite[5].setPosition(521,269);
    Ginasio2ColisoesSprite[6].setPosition(417,405);
    Ginasio2ColisoesSprite[7].setPosition(348,405);
    Ginasio2ColisoesSprite[8].setPosition(312,405);
    Ginasio2ColisoesSprite[9].setPosition(451,404);
    Ginasio2ColisoesSprite[10].setPosition(208,368);
    Ginasio2ColisoesSprite[11].setPosition(487,368);
    Ginasio2ColisoesSprite[12].setPosition(276,335);
    Ginasio2ColisoesSprite[13].setPosition(417,335);

    //***************************************************cenário Luta
    CenarioLutaTexture.loadFromFile("Imagens/Cenarios/CenarioLuta.png");
    CenarioLutaSprite.setTexture(CenarioLutaTexture);
    CenarioLutaSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

    //botão atacar no cenário luta
    AtacarTexture.loadFromFile("Imagens/Botoes/BotaoAtacar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    AtacarSprite = sf::Sprite(AtacarTexture, rectSourceSprite);
    AtacarSprite.setPosition(LarguraTela/2 - 300, AlturaTela - 105);

    //botão fugir no cenário luta
    FugirTexture.loadFromFile("Imagens/Botoes/BotaoFugir.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    FugirSprite = sf::Sprite(FugirTexture, rectSourceSprite);
    FugirSprite.setPosition(LarguraTela/2 + 99, AlturaTela - 105);

    //Vida do pokémon
    VidaTexture.loadFromFile("Imagens/Vida.png");

    for (int a = 0; a < 12; a++) {
        VidaSprite[a].setTexture(VidaTexture);
        if (a < 6)
            VidaSprite[a].setPosition(24+(50*a), 137);
        else
            VidaSprite[a].setPosition(188+(50*a), 337);
    }


    //***************************************************pokémons
    for (int a = 0; a < quantidadePokemon; a++){
        CarregaPokemon(a);
        //Pokemon vivo
        PokemonSprite[a].setTexture(PokemonTexture[a]);
        //Pokemon adversário
        PokemonAdversarioSprite[a].setTexture(PokemonTexture[a]);
        //Pokemon morto
        PokemonMortoSprite[a].setTexture(PokemonMortoTexture[a]);
        //Pokemon borda vivo
        PokemonBordaSprite[a].setTexture(PokemonBordaTexture[a]);
        //Pokemon borda morto
        PokemonBordaMortoSprite[a].setTexture(PokemonBordaMortoTexture[a]);
    }

    //Pokemon forte
    ForteTexture.loadFromFile("Imagens/Forte.png");
    ForteSprite[0].setTexture(ForteTexture);
    ForteSprite[0].setPosition(9,291);
    ForteSprite[1].setTexture(ForteTexture);
    ForteSprite[1].setPosition(695,130);

    //Pokemon fraco
    FracoTexture.loadFromFile("Imagens/Fraco.png");
    FracoSprite[0].setTexture(FracoTexture);
    FracoSprite[0].setPosition(9,291);
    FracoSprite[1].setTexture(FracoTexture);
    FracoSprite[1].setPosition(695,130);

    //Pokemon medio
    MedioTexture.loadFromFile("Imagens/Medio.png");
    MedioSprite[0].setTexture(MedioTexture);
    MedioSprite[0].setPosition(9,291);
    MedioSprite[1].setTexture(MedioTexture);
    MedioSprite[1].setPosition(695,130);


    //***************************************************Quantidade de moedas e pokebolas
    QuantidadeTexture.loadFromFile("Imagens/Numeros.png");
    i = 0;
    j = 0;
    for(int a=0; a<21; a++){
        if(a < 7){
            rectSourceSprite2 = sf::IntRect(25*a, 0, 25, 23); //Corta a imagem
            QuantidadeMoedasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
            QuantidadePokebolasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
        }
        else if(a >= 7 && a < 14){
            rectSourceSprite2 = sf::IntRect(25*i, 23, 25, 23); //Corta a imagem
            QuantidadeMoedasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
            QuantidadePokebolasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
            i++;
        }
        else{
            rectSourceSprite2 = sf::IntRect(25*j, 46, 25, 23); //Corta a imagem
            QuantidadeMoedasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
            QuantidadePokebolasSprite[a] = sf::Sprite(QuantidadeTexture, rectSourceSprite2);
            j++;
        }
        QuantidadeMoedasSprite[a].setPosition(767,15); //Alterar
        QuantidadePokebolasSprite[a].setPosition(767,35);
    }


    //***************************************************cenário Perdeu
    GameOverTexture.loadFromFile("Imagens/Perdeu.png");
    GameOverSprite.setTexture(GameOverTexture);

    //botão jogar novamente quando perde
    BotaoPerdeuTexture.loadFromFile("Imagens/Botoes/BotaoJogarPerdeu.png");
    BotaoPerdeuSprite.setTexture(BotaoPerdeuTexture);
    BotaoPerdeuSprite.setPosition(479,492);


    //***************************************************cenário Ganhou
    GanhouTexture.loadFromFile("Imagens/Ganhou.png");
    GanhouSprite.setTexture(GanhouTexture);

    //botão jogar novamente quando ganha
    BotaoGanhouTexture.loadFromFile("Imagens/Botoes/BotaoJogarGanhou.png");
    BotaoGanhouSprite.setTexture(BotaoGanhouTexture);
    BotaoGanhouSprite.setPosition(479,492);


    //***************************************************Som
    SomTexture.loadFromFile("Imagens/Som.png");
    SomSprite.setTexture(SomTexture);
    SomSprite.setPosition(0,0);
    SomSprite.setScale(0.8, 0.8);
    SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
}

void Jogo::CarregaColisoes(int a, int ginasio){
    char b[2];
    sprintf(b, "%d", a);
    char str[200];

    switch (ginasio) {
        case 1: 
            strcpy(str, "Imagens/Ginasios/Ginasio1Colisao");

            strcat(str, b);
            strcat(str, ".png");

            Ginasio1ColisoesTexture[a].loadFromFile(str); break;
        case 2: 
            strcpy(str, "Imagens/Ginasios/Ginasio2Colisao");

            strcat(str, b);
            strcat(str, ".png");

            Ginasio2ColisoesTexture[a].loadFromFile(str); break;
        /*
        case 3: 
            strcpy(str, "Imagens/Ginasios/Ginasio3Colisao");

            strcat(str, b);
            strcat(str, ".png");

            Ginasio3ColisoesTexture[a].loadFromFile(str); break;
        case 4: 
            strcpy(str, "Imagens/Ginasios/Ginasio4Colisao");

            strcat(str, b);
            strcat(str, ".png");

            Ginasio4ColisoesTexture[a].loadFromFile(str); break;
        */
    }

}

void Jogo::CarregaSons(){
    //música principal
    PrincipalMusic.openFromFile("Som/PrimeiroCenarioSom.wav");
    PrincipalMusic.setVolume(200);

    //música batalha
    BatalhaMusic.openFromFile("Som/CenarioBatalhaSom.wav");
    BatalhaMusic.setVolume(200);

    //música centro
    CentroMusic.openFromFile("Som/CenarioCentroSom.wav");
    CentroMusic.setVolume(200);

    //música ganhou
    GanhouMusic.openFromFile("Som/CenarioGanhouSom.wav");
    GanhouMusic.setVolume(200);

    //música luta
    LutaMusic.openFromFile("Som/CenarioLutaSom.wav");
    LutaMusic.setVolume(200);

    //música perdeu
    PerdeuMusic.openFromFile("Som/CenarioPerdeuSom.wav");
    PerdeuMusic.setVolume(200);
}

void Jogo::CarregaPokemon(int a) {
    char b[2];
    sprintf(b, "%d", a);
    char c[10] = "Morto";
    char d[10] = "Borda";
    char str1[200] = "Imagens/Pokemons/Pokemon";
    char str2[200] = "Imagens/Pokemons/Pokemon";
    char str3[200] = "Imagens/Pokemons/Pokemon";
    char str4[200] = "Imagens/Pokemons/Pokemon";

    strcat(str1, b);

    strcat(str2, b);
    strcat(str2, c);

    strcat(str3, d);
    strcat(str3, b);

    strcat(str4, d);
    strcat(str4, b);
    strcat(str4, c);

    strcat(str1, ".png");
    strcat(str2, ".png");
    strcat(str3, ".png");
    strcat(str4, ".png");
    
    PokemonTexture[a].loadFromFile(str1);
    PokemonMortoTexture[a].loadFromFile(str2);
    PokemonBordaTexture[a].loadFromFile(str3);
    PokemonBordaMortoTexture[a].loadFromFile(str4);   
}

void Jogo::PosicaoMouse(){
    //Pega a posição do mouse atual para verificar se pressionou os botões
    position = sf::Mouse::getPosition(window);
}

void Jogo::MovimentoPersonagem(){
    //Controla a continuidade da personagem
    delta = clock.restart().asSeconds();

    //Movimenta para a esquerda
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //Verifica se não está no fim da tela pela esquerda
        if(PersonagemSprite.getPosition().x > 0){
            AtualizaPersonagem.y = 2;
            if (PrimeiroCenario){
                PersonagemSprite.move(-Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
            }else if (SegundoCenario) {
                PersonagemSprite.move(-Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCutSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaVerticalSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(LagoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MorroSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
            }else if (TerceiroCenario){
                PersonagemSprite.move(-Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(CantoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior3Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasPassagemSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio2MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
            }else if (QuartoCenario){
                PersonagemSprite.move(-Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(OceanoExternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoBaixoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
            }else if (CenarioGinasio1){
                PersonagemSprite.move((-Esquerda.x-80)*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[0].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[1].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[2].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[3].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[4].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[5].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[6].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[7].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[8].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[9].getGlobalBounds()))
                    PersonagemSprite.move((+Esquerda.x+80)*delta,Esquerda.y);
            }else if (CenarioGinasio2){
                PersonagemSprite.move((-Esquerda.x-80)*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds()))
                    PersonagemSprite.move((+Esquerda.x+80)*delta,Esquerda.y);
            }else if (CenarioCentro){
                PersonagemSprite.move((-Esquerda.x-120)*delta,Esquerda.y);
            }
        }
    }
    //Movimenta para a direita
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //Verifica se não está no fim da tela pela direita
        if(PersonagemSprite.getPosition().x < LarguraTela - LarguraPersonagemAtualizada){
            AtualizaPersonagem.y = 3;
            if(PrimeiroCenario){
                PersonagemSprite.move(Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
            }else if(SegundoCenario) {
                PersonagemSprite.move(Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCutSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaVerticalSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(LagoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MorroSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
            }else if (TerceiroCenario){
                PersonagemSprite.move(Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(CantoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior3Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasPassagemSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio2MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
            }else if (QuartoCenario){
                PersonagemSprite.move(+Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(OceanoExternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoBaixoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
            }else if(CenarioGinasio1){
                PersonagemSprite.move((+Direita.x+80)*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[0].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[1].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[2].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[3].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[4].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[5].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[6].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[7].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[8].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[9].getGlobalBounds()))
                    PersonagemSprite.move((-Direita.x-80)*delta,Direita.y);
            }else if(CenarioGinasio2){
                PersonagemSprite.move((+Direita.x+80)*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds()))
                    PersonagemSprite.move((-Direita.x-80)*delta,Direita.y);
            }else if(CenarioCentro){
                PersonagemSprite.move((+Direita.x+120)*delta,Direita.y);
            }
        }
    }
    //Movimenta para baixo
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(PersonagemSprite.getPosition().y < AlturaTela - AlturaPersonagemAtualizada){
            AtualizaPersonagem.y = 1;
            if(PrimeiroCenario){
                PersonagemSprite.move(Baixo.x,+Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
            }else if (SegundoCenario){
                PersonagemSprite.move(Baixo.x,+Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCutSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaVerticalSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(LagoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MorroSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
            }else if (TerceiroCenario){
                PersonagemSprite.move(Baixo.x,+Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(CantoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior3Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasPassagemSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio2MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
            }else if (QuartoCenario){
                PersonagemSprite.move(Baixo.x,+Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(OceanoExternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoBaixoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
            }else if(CenarioGinasio1){
                PersonagemSprite.move(Baixo.x,(+Baixo.y+120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds())
                //|| PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[0].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[1].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[2].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[3].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[4].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[5].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[6].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[7].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[8].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[9].getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,(-Baixo.y-120)*delta);
            }else if(CenarioGinasio2){
                PersonagemSprite.move(Baixo.x,(+Baixo.y+120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,(-Baixo.y-120)*delta);
            }else if(CenarioCentro){
                PersonagemSprite.move(Baixo.x,(+Baixo.y+120)*delta);
            }
        }
   }
   //Movimenta para cima
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if(PersonagemSprite.getPosition().y > 0){
            AtualizaPersonagem.y = 0;
            if(PrimeiroCenario){
                PersonagemSprite.move(Cima.x,-Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
            }else if(SegundoCenario) {
                PersonagemSprite.move(Cima.x,-Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresBaixo2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoreSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(ArvoresCutSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaHorizontal2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CercaVerticalSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(LagoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MorroSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
            }else if (TerceiroCenario){
                PersonagemSprite.move(Cima.x,-Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(CantoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(CantoInferior3Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasDireita2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasPassagemSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PedrasEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio2MenorSprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
            }else if (QuartoCenario){
                PersonagemSprite.move(Cima.x,-Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(OceanoExternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoExternoBaixoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoCimaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoEsquerdaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoDireitaSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo1Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(OceanoInternoBaixo2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
            }else if(CenarioGinasio1){
                PersonagemSprite.move(Cima.x,(-Cima.y-120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[0].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[1].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[2].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[3].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[4].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[5].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[6].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[7].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[8].getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[9].getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
            }else if(CenarioGinasio2){
                PersonagemSprite.move(Cima.x,(-Cima.y-120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1ColisaoSprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
            }else if(CenarioCentro){
                PersonagemSprite.move(Cima.x,(-Cima.y-120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(BalcaoCentro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MesaCentro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(PlantaCentro2Sprite.getGlobalBounds())
                || PersonagemSprite.getGlobalBounds().intersects(MaquinaCentro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
            }
        }
    }

    //Verifica se e qual botão do movimento da personagem está sendo pressionada para que altere sua imagem
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        //Atualiza as imagens do eixo x
        AtualizaPersonagem.x++;
        //Verifica se as imagens do eixo x acabaram
        if(AtualizaPersonagem.x*27 >= 81)
            AtualizaPersonagem.x = 0;
    }else
        AtualizaPersonagem.x = 0;

    //Delay para que as imagens da personagem mude mais devagar e não fique zoado
    sf::Time delayTime = sf::milliseconds(50);
    sf::sleep(delayTime);

    //Realiza a alteração da imagem da personagem dependendo do lado para qual está indo
    //Verifica se a personagem está na area do matinho, se sim, só mostra a imagem da sua cabeça
    if((PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada - 12 > 300
    && PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 300 + 272) 
    && (PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada/2 > 150
    && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada/2 < 150 + 595)
    && PrimeiroCenario)
        PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*27, AtualizaPersonagem.y*31, 27, 31-12));
    else
        PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*27, AtualizaPersonagem.y*31, 27, 31));
}
/*
void Jogo::ColisaoGinasio1(int direcao){
    for (int a = 0; a < qtdeColisoesGinasio1; a++) {
        switch (direcao) {
            case 0: //Esquerda
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move((+Esquerda.x+120)*delta,Esquerda.y);
                break;
            case 1: //Direita
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move((-Direita.x-120)*delta,Direita.y);
                break;
            case 2: //Baixo
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,(-Baixo.y-120)*delta);
                break;
            case 3: //Cima
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio1ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
                break;
        }
    }
}
/*
void Jogo::ColisaoGinasio2(int direcao){
    for (int a = 0; a < qtdeColisoesGinasio2; a++) {
        switch (direcao) {
            case 0: //Esquerda
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio2ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
                break;
            case 1: //Direita
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio2ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
                break;
            case 2: //Baixo
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio2ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
                break;
            case 3: //Cima
                if(PersonagemSprite.getGlobalBounds().intersects(Ginasio2ColisoesSprite[a].getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
                break;
        }
    }
}*/

//diminui a sua vida de acordo com o ataque do oponente
void Jogo::RecebeAtaque(Pokemon* seuPokemon, Pokemon* Oponente){
    if(seuPokemon->getVida() > 0)
        seuPokemon->setVida(seuPokemon->getVida() - Oponente->getAtaque());

    if(seuPokemon->getVida() < 1)
        seuPokemon->setVida(0);
}

//diminui a vida do oponente de acordo com o seu ataque
void Jogo::Ataca(Pokemon* seuPokemon, Pokemon* Oponente){
    if(Oponente->getVida() > 0)
        Oponente->setVida(Oponente->getVida() - seuPokemon->getAtaque());

    if(Oponente->getVida() < 1)
        Oponente->setVida(0);
}

void Jogo::AtaqueCompleto(Pokemon* seuPokemon, Pokemon* Oponente){
    Ataca(seuPokemon, Oponente);

    if(Oponente->estaVivo())
        RecebeAtaque(seuPokemon, Oponente);
}

void Jogo::Batalha(){
    //Se tem pokemon aliado vivo
    if(SeusPokemons.getQntPokemonsBatalhaveis() != 0){
        if(Atacar){
            Atacar = 0;

            //Delay para o botão posterior não pegar o click anterior
            sf::Time delayTime = sf::milliseconds(200);
            sf::sleep(delayTime);

            botaoFugir = false;

            //Se o pokemon adversário está vivo realiza o ataque e atualiza o pokemon aliado
            if(pokemonAdversarioBatalhando->estaVivo()){
                AtaqueCompleto(seuPokemonBatalhando, pokemonAdversarioBatalhando);
                //Atualiza qual pokemon voce vai usar na batalha
                seuPokemonBatalhando = SeusPokemons.pokemonQueVaiBatalhar(&posicaoDoSeuPokemon);
            }

            //Caso estiver no cenário da batalha, atualiza o pokemon adversário
            if(CenarioBatalha && BatalhaGinasio1.getPokemon(5)->estaVivo()){
                pokemonAdversarioBatalhando = (BatalhaGinasio1.pokemonQueVaiBatalhar(&posicaoAdversario));
            }
        }
    }
}

void Jogo::setQntMoedas(int valor){
    if((moedas+valor) <= 20){
        moedas = moedas + valor;
        if(moedas < 0)
            moedas = 0;
    }else{
        if(moedas < 20){
            while(moedas < 20)
                moedas++;
        }
     }
}

int Jogo::derrubaMoedas(int atkOponente){
    if(atkOponente == 1)
        return 1;
    else if(atkOponente == 2)
        return 2;
    else if(atkOponente == 3)
        return 3;
    return 0;
}

bool Jogo::setQntPokebolas(int valor){
    if(pokebolas+valor <= 20){
        pokebolas = pokebolas + valor;
        if(pokebolas < 0)
            pokebolas = 0;
        return true;
    }else{
        return false;
    }
}

bool Jogo::CapturarPokemon(Pokemon* PokemonCapturar){
    if(pokebolas > 0){
        SeusPokemons.InserirNoFinalCapturado(PokemonCapturar->getID(), PokemonCapturar->getVida());
        setQntPokebolas(-1);
        return true;
    }else{
        return false;
    }
}

bool Jogo::ComprarPokebola(){
    int quantidade = 1;
    if(quantidade > moedas){
        return false;
    }else{
        if(setQntPokebolas(quantidade) > 0)
            setQntMoedas((quantidade)*-1);
        return true;
    }
}

void Jogo::Eventos(){
    while (window.pollEvent(Event)){
        if(Event.type == sf::Event::Closed){
            SeusPokemons.RetirarTodosElementos();
            window.close();
        }
        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)){
            SeusPokemons.RetirarTodosElementos();
            window.close();
        }
    }
}

void Jogo::Menu(){
    //Verifica a posição do mouse
    PosicaoMouse();
    //Verifica se apertou um dos três botões da tela
    Start = AtualizaBotao(Event, position, PlaySprite, rectSourceSprite);
    Instrucoes = AtualizaBotao(Event, position, InstruSprite, rectSourceSprite);
    Sair = AtualizaBotao(Event, position, SairSprite, rectSourceSprite);

    window.clear();
    window.draw(CenarioMenuSprite);
    window.draw(PlaySprite);
    window.draw(InstruSprite);
    window.draw(SairSprite);
    window.display();
    //Delay para aparecer a imagem do botão pressionado
    sf::Time delayTime = sf::milliseconds(100);
    sf::sleep(delayTime);
}

void Jogo::Instrucao(){
    //Verifica a posição do mouse
    PosicaoMouse();
    //Verifica se apertou o botão voltar
    Voltar = AtualizaBotao(Event, position, VoltarSprite, rectSourceSprite);
    if(Voltar)
        Instrucoes = 0;

    window.clear();
    window.draw(CenarioInstruSprite);
    window.draw(VoltarSprite);
    window.display();

    //Delay para aparecer a imagem do botão pressionado e atualizar o click
    sf::Time delayTime = sf::milliseconds(100);
    sf::sleep(delayTime);
}

void Jogo::TelaCenarioPokemonInicial(){
    PosicaoMouse();
    Pokemon0 = AtualizaBotao(Event, position, Pokemon0Sprite, rectSourceSprite);
    Pokemon1 = AtualizaBotao(Event, position, Pokemon1Sprite, rectSourceSprite);
    Pokemon2 = AtualizaBotao(Event, position, Pokemon2Sprite, rectSourceSprite);

    window.clear();
    window.draw(CenarioEscolhaPokemonSprite);
    window.draw(Pokemon1Sprite);
    window.draw(Pokemon0Sprite);
    window.draw(Pokemon2Sprite);
    window.display();

    //Delay para aparecer a imagem do botão pressionado
    sf::Time delayTime = sf::milliseconds(100);
    sf::sleep(delayTime);

    //Ao escolher o pokemon, vai para o cenário do centro
    if(Pokemon1 || Pokemon0 || Pokemon2){
        PokemonInicial = 0;
        PrimeiroCenario = 1;
        if (Pokemon0)
            PokemonEscolha = 0;
        else if (Pokemon1)
            PokemonEscolha = 1;
        else if (Pokemon2)
            PokemonEscolha = 2;
        //Insere na lista dos pokemons aliados dependendo da escolha
        SeusPokemons.InserirNoFinal(PokemonEscolha);
    }
}

void Jogo::TelaPrimeiroCenario(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();

    ArvoreSprite.setPosition(425,96);

    CentroSprite.setScale(EscalaCentro, EscalaCentro);
    CentroSprite.setPosition(300,40);
    AlturaCentroAtualizada = AlturaCentro * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    Centro2Sprite.setScale(EscalaCentro, EscalaCentro);
    Centro2Sprite.setPosition(300,40);
    AlturaCentroAtualizada2 = AlturaCentro2 * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    //Curar pokemons que você está batalhando
    PokemonsCapturaveis.CurarTodaLista();

    MovimentoPersonagem();

    //Dispõe os matinhos em uma area da tela
    for(i=0; i<16; i++){
        for(int j=0; j<35; j++){
            Matinho1Sprite[i][j].setTexture(MatinhoTexture);
            if(j == 0){
                if(i == 0)
                    Matinho1Sprite[i][j].setPosition(150, 300);
                else
                    Matinho1Sprite[i][j].setPosition(150, Matinho1Sprite[i-1][j].getPosition().y + 17);
            }
            else
                Matinho1Sprite[i][j].setPosition(Matinho1Sprite[i][j-1].getPosition().x + 17, Matinho1Sprite[i][j-1].getPosition().y);
        }
    }

    //Sprite invisível para ir para o cenário da luta
    while(inicio && (InvisivelSprite[1].getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds()))){
        InvisivelSprite[0].setPosition(150 + (rand() % 268), 300 + (rand() %  176));
        InvisivelSprite[1].setPosition(378 + (rand() % 268), 300 + (rand() %  176));
    }

    //Para não entrar no while acima, já que será sorteado novamente na função luta
    inicio = 0;

    //Seta a posição e a escala do pokemon escolhido
    PokemonSprite[PokemonEscolha].setPosition(499, 13);
    PokemonSprite[PokemonEscolha].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);

    window.clear();
    window.draw(PrimeiroCenarioSprite);
    window.draw(PlacaCentroSprite);
    window.draw(PlacaCenario2Sprite);

    //Altera a imagem do matinho para dar a impressão de movimento
    for(i=0; i<16; i++){
        for(int j=0; j<35; j++){
            if(PersonagemSprite.getGlobalBounds().intersects(Matinho1Sprite[i][j].getGlobalBounds()))
                Matinho1Sprite[i][j].setTextureRect(sf::IntRect(16, 0, 16, 16));
            else
                Matinho1Sprite[i][j].setTextureRect(sf::IntRect(0, 0, 16, 16));
            window.draw(Matinho1Sprite[i][j]);
        }
    }

    window.draw(Cerca1Sprite);
    window.draw(Cerca2Sprite);
    window.draw(Cerca12Sprite);
    window.draw(Cerca22Sprite);
    window.draw(RioSprite);
    window.draw(Arvore1Sprite);
    window.draw(CentroSprite);
    window.draw(Centro2Sprite);

    //Mostra o aviso da placa do centro, caso a personagem colida
    if(PersonagemSprite.getGlobalBounds().intersects(PlacaCentroSprite.getGlobalBounds())){
        window.draw(AvisoPlacaCentroSprite);
    }

    //Mostra o aviso da placa do ginásio, caso a personagem colida
    if(PersonagemSprite.getGlobalBounds().intersects(PlacaCenario2Sprite.getGlobalBounds())){
        window.draw(AvisoPlacaCenario2Sprite);
    }

    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);

    //Mostra a imagem dos pokemons na bolsa
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }

    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);
    window.draw(SomSprite);
    window.display();

    //Mudança de tela
    //A personagem entra em uma área especifica da tela e vai para o segundo cenário
    if(PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada >= LarguraTela && (PersonagemSprite.getPosition().y > 150 &&  PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 205)){
        PrimeiroCenario = 0;
        SegundoCenario = 1;
        InvisivelSprite[0].setPosition(346 + (rand() % 196), 20 + (rand() % 40));
        InvisivelSprite[1].setPosition(65 + (rand() % 40), 340 + (rand() %  126));
        InvisivelSprite[2].setPosition(426 + (rand() % 135), 388 + (rand() % 10));
        PersonagemSprite.setPosition(0, 30);
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do centro
    else if(PersonagemSprite.getGlobalBounds().intersects(CentroSprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (CentroSprite.getPosition().x + 25*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (Centro2Sprite.getPosition().x + 50*EscalaCentro)){
            PrimeiroCenario = 0;
            CenarioCentro = 1;
            cenarioAnterior = 1;
            PersonagemSprite.setScale(EscalaPersonagemCentro, EscalaPersonagemCentro);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemCentro;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemCentro;
            PersonagemSprite.setPosition(PersonagemSprite.getPosition().x, 599 - AlturaPersonagemAtualizada);
        }
    }
    //Se a personagem colidir com os sprites invisiveis, irá para a tela da batalha contra um pokemon aleatório
    else if(PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds()) ||
       PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds())){
        CenarioLuta = 1;
        PrimeiroCenario = 0;
        cenarioAnterior = 1;
        PokemonLuta = rand() % 15;
    }
}

void Jogo::TelaSegundoCenario(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();

    ArvoreSprite.setPosition(494,263);

    CentroSprite.setScale(EscalaCentro, EscalaCentro);
    CentroSprite.setPosition(218,310);
    AlturaCentroAtualizada = AlturaCentro * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    Centro2Sprite.setScale(EscalaCentro, EscalaCentro);
    Centro2Sprite.setPosition(218,310);

    Ginasio1Sprite.setScale(EscalaCentro, EscalaCentro);
    Ginasio1MenorSprite.setScale(EscalaCentro, EscalaCentro);

    MovimentoPersonagem();

    window.clear();
    window.draw(SegundoCenarioSprite);

    //Curar pokemons que você está batalhando
    PokemonsCapturaveis.CurarTodaLista();

    //Dispõe os matinhos em uma area da tela
    for(i=0; i<4; i++){
        for(int j=0; j<18; j++){
            Matinho2CimaSprite[i][j].setTexture(MatinhoTexture);
            if(j == 0){
                if(i == 0)
                    Matinho2CimaSprite[i][j].setPosition(346, 36);
                else
                    Matinho2CimaSprite[i][j].setPosition(346, Matinho2CimaSprite[i-1][j].getPosition().y + 17);
            }
            else
                Matinho2CimaSprite[i][j].setPosition(Matinho2CimaSprite[i][j-1].getPosition().x + 17, Matinho2CimaSprite[i][j-1].getPosition().y);
        }
    }

    //Dispõe os matinhos em uma area da tela
    for(i=0; i<14; i++){
        for(int j=0; j<7; j++){
            Matinho2EsquerdaSprite[i][j].setTexture(MatinhoTexture);
            if(j == 0){
                if(i == 0)
                    Matinho2EsquerdaSprite[i][j].setPosition(74, 340);
                else
                    Matinho2EsquerdaSprite[i][j].setPosition(74, Matinho2EsquerdaSprite[i-1][j].getPosition().y + 17);
            }
            else
                Matinho2EsquerdaSprite[i][j].setPosition(Matinho2EsquerdaSprite[i][j-1].getPosition().x + 17, Matinho2EsquerdaSprite[i][j-1].getPosition().y);
        }
    }

    //Dispõe os matinhos em uma area da tela
    for(i=0; i<6; i++){
        for(int j=0; j<14; j++){
            Matinho2DireitaSprite[i][j].setTexture(MatinhoTexture);
            if(j == 0){
                if(i == 0)
                    Matinho2DireitaSprite[i][j].setPosition(426, 388);
                else
                    Matinho2DireitaSprite[i][j].setPosition(426, Matinho2DireitaSprite[i-1][j].getPosition().y + 17);
            }
            else
                Matinho2DireitaSprite[i][j].setPosition(Matinho2DireitaSprite[i][j-1].getPosition().x + 17, Matinho2DireitaSprite[i][j-1].getPosition().y);
        }
    }

    //Sprite invisível para ir para o cenário da luta
    while(inicio && (PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[2].getGlobalBounds()))){
        InvisivelSprite[0].setPosition(346 + (rand() % 196), 20 + (rand() % 40));
        InvisivelSprite[1].setPosition(65 + (rand() % 40), 340 + (rand() %  126));
        InvisivelSprite[2].setPosition(426 + (rand() % 135), 388 + (rand() % 10));
    }

    //Para não entrar no while acima, já que será sorteado novamente na função luta
    inicio = 0;

    //Seta a posição e a escala do pokemon escolhido
    PokemonSprite[PokemonEscolha].setPosition(499, 13);
    PokemonSprite[PokemonEscolha].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);

    //Altera a imagem do matinho para dar a impressão de movimento
    for(i=0; i<4; i++){
        for(int j=0; j<18; j++){
            if(PersonagemSprite.getGlobalBounds().intersects(Matinho2CimaSprite[i][j].getGlobalBounds()))
                Matinho2CimaSprite[i][j].setTextureRect(sf::IntRect(16, 0, 16, 16));
            else
                Matinho2CimaSprite[i][j].setTextureRect(sf::IntRect(0, 0, 16, 16));
            window.draw(Matinho2CimaSprite[i][j]);
        }
    }
    for(i=0; i<14; i++){
        for(int j=0; j<7; j++){
            if(PersonagemSprite.getGlobalBounds().intersects(Matinho2EsquerdaSprite[i][j].getGlobalBounds()))
                Matinho2EsquerdaSprite[i][j].setTextureRect(sf::IntRect(16, 0, 16, 16));
            else
                Matinho2EsquerdaSprite[i][j].setTextureRect(sf::IntRect(0, 0, 16, 16));
            window.draw(Matinho2EsquerdaSprite[i][j]);
        }
    }
    for(i=0; i<6; i++){
        for(int j=0; j<14; j++){
            if(PersonagemSprite.getGlobalBounds().intersects(Matinho2DireitaSprite[i][j].getGlobalBounds()))
                Matinho2DireitaSprite[i][j].setTextureRect(sf::IntRect(16, 0, 16, 16));
            else
                Matinho2DireitaSprite[i][j].setTextureRect(sf::IntRect(0, 0, 16, 16));
            window.draw(Matinho2DireitaSprite[i][j]);
        }
    }

    window.draw(ArvoresCutSprite);
    window.draw(CentroSprite);
    window.draw(Centro2Sprite);
    window.draw(Ginasio1Sprite);
    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);

    //Mostra a imagem dos pokemons na bolsa
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }

    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);
    window.draw(SomSprite);
    window.display();

    //Mudança de tela
    //A personagem entra em uma área especifica da tela e vai para o primeiro cenário
    if(PersonagemSprite.getPosition().x < 0 && (PersonagemSprite.getPosition().y > 10 &&  PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 107)){
        PrimeiroCenario = 1;
        SegundoCenario = 0;
        InvisivelSprite[0].setPosition(150 + (rand() % 268), 300 + (rand() %  176));
        InvisivelSprite[1].setPosition(378 + (rand() % 268), 300 + (rand() %  176));
        InvisivelSprite[2].setPosition(800, 600);
        PersonagemSprite.setPosition(LarguraTela - LarguraPersonagemAtualizada, 155);
    }
    //A personagem entra em uma área especifica da tela e vai para o terceiro cenário
    else if(PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada >= 600 && (PersonagemSprite.getPosition().x > 200 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 600)){
        TerceiroCenario = 1;
        SegundoCenario = 0;
        PersonagemSprite.setPosition(353, 0);
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do centro
    else if(PersonagemSprite.getGlobalBounds().intersects(CentroSprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (CentroSprite.getPosition().x + 25*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (Centro2Sprite.getPosition().x + 50*EscalaCentro)){
            SegundoCenario = 0;
            CenarioCentro = 1;
            cenarioAnterior = 2;
            PersonagemSprite.setScale(EscalaPersonagemCentro, EscalaPersonagemCentro);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemCentro;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemCentro;
            PersonagemSprite.setPosition(PersonagemSprite.getPosition().x + 100, 599 - AlturaPersonagemAtualizada);
        }
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do primeiro ginásio
    else if(PersonagemSprite.getGlobalBounds().intersects(Ginasio1Sprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (Ginasio1Sprite.getPosition().x + 45*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (Ginasio1Sprite.getPosition().x + 70*EscalaCentro)){
            SegundoCenario = 0;
            CenarioGinasio1 = 1;
            cenarioAnterior = 2;
            PersonagemSprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemGinasio;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemGinasio;
            PersonagemSprite.setPosition(380, 549 - AlturaPersonagemAtualizada);
        }
    }
    //Se a personagem colidir com os sprites invisiveis, irá para a tela da batalha contra um pokemon aleatório
    else if(PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds()) ||
       PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds()) ||
       PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[2].getGlobalBounds())){
        CenarioLuta = 1;
        SegundoCenario = 0;
        cenarioAnterior = 2;
        PokemonLuta = 9 + (rand() % 13);
    }
}

void Jogo::TelaTerceiroCenario(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();


    MovimentoPersonagem();

    Ginasio2Sprite.setScale(EscalaCentro, EscalaCentro);
    Ginasio2MenorSprite.setScale(EscalaCentro, EscalaCentro);

    window.clear();
    window.draw(TerceiroCenarioSprite);
    window.draw(CantoCimaSprite);
    window.draw(CantoEsquerdaSprite);
    window.draw(CantoInferior1Sprite);
    window.draw(CantoInferior2Sprite);
    window.draw(CantoInferior3Sprite);
    window.draw(PedrasDireita1Sprite);
    window.draw(PedrasDireita2Sprite);
    window.draw(PedrasEsquerdaSprite);

    CentroSprite.setScale(EscalaCentro, EscalaCentro);
    CentroSprite.setPosition(491,269);
    AlturaCentroAtualizada = AlturaCentro * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    Centro2Sprite.setScale(EscalaCentro, EscalaCentro);
    Centro2Sprite.setPosition(491,269);

    window.draw(CentroSprite);
    window.draw(PedrasPassagemSprite);
    window.draw(Ginasio2Sprite);
    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);

    //Mostra a imagem dos pokemons na bolsa
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }

    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);
    window.draw(SomSprite);
    window.display();

    //Mudança de tela
    //A personagem entra em uma área especifica da tela e vai para o segundo cenário
    if(PersonagemSprite.getPosition().y <= 0 && (PersonagemSprite.getPosition().x > 200 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 600)){
        SegundoCenario = 1;
        TerceiroCenario = 0;
        InvisivelSprite[0].setPosition(346 + (rand() % 196), 20 + (rand() % 40));
        InvisivelSprite[1].setPosition(65 + (rand() % 40), 340 + (rand() %  126));
        InvisivelSprite[2].setPosition(426 + (rand() % 135), 388 + (rand() % 10));
        PersonagemSprite.setPosition(360, 599 - AlturaPersonagemAtualizada);
    }
    //A personagem entra em uma área especifica da tela e vai para o quarto cenário
    else if(PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada >= 600 && (PersonagemSprite.getPosition().x > 200 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 600)){
        QuartoCenario = 1;
        TerceiroCenario = 0;
        PersonagemSprite.setPosition(400, 0);
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do centro
    else if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (CentroSprite.getPosition().x + 25*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (CentroSprite.getPosition().x + 50*EscalaCentro)){
            TerceiroCenario = 0;
            CenarioCentro = 1;
            cenarioAnterior = 3;
            PersonagemSprite.setScale(EscalaPersonagemCentro, EscalaPersonagemCentro);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemCentro;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemCentro;
            PersonagemSprite.setPosition(PersonagemSprite.getPosition().x + 100, 599 - AlturaPersonagemAtualizada);
        }
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do primeiro ginásio
    else if(PersonagemSprite.getGlobalBounds().intersects(Ginasio2Sprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (Ginasio2Sprite.getPosition().x + 45*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (Ginasio2Sprite.getPosition().x + 70*EscalaCentro)){
            TerceiroCenario = 0;
            CenarioGinasio2 = 1;
            cenarioAnterior = 3;
            PersonagemSprite.setScale(EscalaPersonagemGinasio, EscalaPersonagemGinasio);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemGinasio;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemGinasio;
            PersonagemSprite.setPosition(415 - LarguraPersonagemAtualizada, 599 - AlturaPersonagemAtualizada);
        }
    }/*
    //Se a personagem colidir com os sprites invisiveis, irá para a tela da batalha contra um pokemon aleatório
    else if(PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds()) ||
       PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds())){
        CenarioLuta = 1;
        TerceiroCenario = 0;
        cenarioAnterior = 3;
        PokemonLuta = 22 + (rand() % 6);
    }*/
}

void Jogo::TelaQuartoCenario(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();


    MovimentoPersonagem();

    window.clear();
    window.draw(QuartoCenarioSprite);
    window.draw(OceanoExternoCimaSprite);
    window.draw(OceanoExternoEsquerdaSprite);
    window.draw(OceanoExternoDireitaSprite);
    window.draw(OceanoExternoBaixoSprite);
    window.draw(OceanoInternoCimaSprite);
    window.draw(OceanoInternoEsquerdaSprite);
    window.draw(OceanoInternoDireitaSprite);
    window.draw(OceanoInternoBaixo1Sprite);
    window.draw(OceanoInternoBaixo2Sprite);
    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);

    //Mostra a imagem dos pokemons na bolsa
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }

    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);
    window.draw(SomSprite);
    window.display();

    //Mudança de tela
    //A personagem entra em uma área especifica da tela e vai para o segundo cenário
    if(PersonagemSprite.getPosition().y <= 0 && (PersonagemSprite.getPosition().x > 200 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 600)){
        TerceiroCenario = 1;
        QuartoCenario = 0;
        PersonagemSprite.setPosition(350, 599 - AlturaPersonagemAtualizada);
    }
}

void Jogo::TelaCenarioCentro(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();

    MovimentoPersonagem();
    window.clear();

    window.draw(Cenario2Sprite);
    window.draw(BalcaoCentroSprite);
    window.draw(PlantaCentroSprite);
    window.draw(MesaCentroSprite);
    window.draw(MaquinaCentroSprite);
    window.draw(BalcaoCentro2Sprite);
    window.draw(PlantaCentro2Sprite);
    window.draw(MesaCentro2Sprite);
    window.draw(MaquinaCentro2Sprite);
    window.draw(PersonagemSprite);

    //Caso a personagem colida com o balção em um determinado espaço
    if(PersonagemSprite.getGlobalBounds().intersects(BalcaoCentroSprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > 350 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 450){
            window.draw(AvisoPokebolaSprite);
            window.draw(HealarSprite);
            window.draw(CompraPokebolaSprite);

            //PosicaoMouse();
            //Cura todos os pokemons caso aperte no botão de curar
            if(AtualizaBotao(Event, position, HealarSprite, rectSourceSprite)){
                SeusPokemons.CurarPokemons();
            }
            //Compra pokebolas caso aperte no botão de comprar
            else if(AtualizaBotao(Event, position, CompraPokebolaSprite, rectSourceSprite)){
                while(moedas > 0 && pokebolas < 20){
                    ComprarPokebola();
                }
            }
        }
    }

    //Caso a personagem colida com a maquina
    if(PersonagemSprite.getGlobalBounds().intersects(MaquinaCentroSprite.getGlobalBounds())){
        //Verifica se a bolsa invisivel foi pressionada, para realizar a troca dos pokemons na lista
        if((Event.type == sf::Event::MouseButtonPressed)){
            for(int a = 0; a < SeusPokemons.getTamanho(); a++){
                if(VerificaBotao(position, BolsaInvisivelSprite[a])){
                    if(auxID == -1) {
                        auxID = a;
                    }else{
                        if(auxID != a){ //Não troca ele por ele mesmo
                            SeusPokemons.TrocaElementos(auxID+1, a+1);
                        }
                        auxID = -1;
                    }
                }
            }
            //Verifica se a sprite da lixeira foi apertada para realizar a remoção do pokemon
            if(VerificaBotao(position, LixeiraSprite)){
                if(auxID != -1){
                    SeusPokemons.RemoverElemento(auxID+1);
                    auxID = -1;
                }
            }
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(200);
            sf::sleep(delayTime);
        }

        window.draw(AvisoPokemonSprite);
        window.draw(LixeiraSprite);

        //Variáveis utilizadas para imprimir na bolsa os pokemons da lista de acordo com o tamanho da mesma
        i = 0;
        j = 0;
        for(int a = 0; a < SeusPokemons.getTamanho(); a++){
            if(a < 6){
                if(!SeusPokemons.getPokemon(a)->estaVivo()){
                    if(auxID == a){
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(278+a*41, 359);
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(278+a*41, 359);
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }else{
                    if(auxID == a){
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(278+a*41, 359);
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(278+a*41, 359);
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }
            }else if(a < 13){
                if(!SeusPokemons.getPokemon(a)->estaVivo()){
                    if(auxID == a){
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+i*41, 457);
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+i*41, 457);
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }else{
                    if(auxID == a){
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+i*41, 457);
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+i*41, 457);
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }
                i++;
            }else{
                if(!SeusPokemons.getPokemon(a)->estaVivo()){
                    if(auxID == a){
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+j*41, 498);
                        PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+j*41, 498);
                        PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }else{
                    if(auxID == a){
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+j*41, 498);
                        PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonBordaSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }else{
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(259+j*41, 498);
                        PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                        window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
                    }
                }
                j++;
            }
        }
    }
    //Mostra a bolsa menor com os 6 primeiros pokemons da lista na tela
    else{
        //Atualiza o auxiliar de troca e remoção dos pokemons da lista
        auxID = -1;

        window.draw(BolsaSprite);
        window.draw(QuantidadeMoedasSprite[moedas]);
        window.draw(QuantidadePokebolasSprite[pokebolas]);
        //Mostra os 6 primeiros pokemons da lista na tela
        for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
            if(!SeusPokemons.getPokemon(a)->estaVivo()) {
                PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
                PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
            }else{
                PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
                PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
                window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
            }
        }
    }

    window.draw(SomSprite);
    window.display();

    //A personagem entra numa área específica da tela e vai para o cenário anterior
    if((PersonagemSprite.getPosition().y > 600 - AlturaPersonagemAtualizada) && (PersonagemSprite.getPosition().x > 400 - 60 &&  PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 400 + 60)){
        if(cenarioAnterior == 1) {
            PrimeiroCenario = 1;
            CenarioCentro = 0;
            cenarioAnterior = 0;
            PersonagemSprite.setPosition(PersonagemSprite.getPosition().x, CentroSprite.getPosition().y + AlturaCentroAtualizada);
        } else if(cenarioAnterior == 2) {
            SegundoCenario = 1;
            CenarioCentro = 0;
            cenarioAnterior = 0;
            PersonagemSprite.setPosition(PersonagemSprite.getPosition().x - 100, CentroSprite.getPosition().y + AlturaCentroAtualizada);
        } else if(cenarioAnterior == 3) {
            TerceiroCenario = 1;
            CenarioCentro = 0;
            cenarioAnterior = 0;
            PersonagemSprite.setPosition(550, 409);
        }
        PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
    }
}

void Jogo::TelaCenarioGinasio1(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();

    MovimentoPersonagem();

    window.clear();
    window.draw(CenarioGinasio1Sprite);
    window.draw(LiderGinasio1Sprite);
    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);

    //Mostra os pokemons na tela
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }
    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);
    window.draw(SomSprite);
    window.display();

    //Caso a personagem colida com a líder do ginásio
    if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio1Sprite.getGlobalBounds())){
        window.draw(AvisoLiderSprite);
        window.draw(BatalharSprite);
        PosicaoMouse();
        CenarioBatalha = AtualizaBotao(Event, position, BatalharSprite, rectSourceSprite);

        //Mudança de tela para cenário batalha
        if(CenarioBatalha){
            CenarioGinasio1 = 0;
            CenarioBatalha = 1;
            CenarioLuta = 0;
            SegundoCenario = 0;
        }
    }
    window.draw(SomSprite);
    window.display();
    
    //A personagem entra numa área específica da tela e vai para o cenário principal
    if(PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada >= 550 && (PersonagemSprite.getPosition().x > 370 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 430)){
        SegundoCenario = 1;
        CenarioGinasio1 = 0;
        PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
        PersonagemSprite.setPosition(Ginasio1Sprite.getPosition().x + 45*EscalaCentro, Ginasio1Sprite.getPosition().y + 79*EscalaCentro);
    }
}

void Jogo::TelaCenarioGinasio2(){
    PosicaoMouse();

    if(Event.type == sf::Event::MouseButtonPressed){
        if(VerificaBotao(position, SomSprite)){
            if(Music == 0){
                Music = 1;
            }
            else if(Music == 1){
                Music = 0;
            }
            SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
            //Delay para o click de cima n pegar o de baixo
            sf::Time delayTime = sf::milliseconds(150);
            sf::sleep(delayTime);
        }
    }

    //Verifica a música
    if(Music){
        if(!PrincipalMusic.getStatus()){
            PrincipalMusic.play();
        }else if((CentroMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2)){
            CentroMusic.stop();
            LutaMusic.stop();
        }
    }else
        PrincipalMusic.stop();

    MovimentoPersonagem();

    window.clear();
    window.draw(CenarioGinasio2Sprite);
    window.draw(LiderGinasio2Sprite);
    window.draw(PersonagemSprite);
    window.draw(BolsaSprite);
    //Mostra os pokemons na tela
    for(int a = 0; a < SeusPokemons.getQtdeAtual(); a++){
        if(!SeusPokemons.getPokemon(a)->estaVivo()){
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonMortoSprite[SeusPokemons.getPokemon(a)->getID()]);
        }else{
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setPosition(499+a*41, 13);
            PokemonSprite[SeusPokemons.getPokemon(a)->getID()].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);
            window.draw(PokemonSprite[SeusPokemons.getPokemon(a)->getID()]);
        }
    }
    window.draw(QuantidadeMoedasSprite[moedas]);
    window.draw(QuantidadePokebolasSprite[pokebolas]);

    //Caso a personagem colida com a líder do ginásio
    if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio2ColisaoSprite.getGlobalBounds())){
        window.draw(AvisoLiderSprite);
        window.draw(BatalharSprite);
        PosicaoMouse();
        CenarioBatalha = AtualizaBotao(Event, position, BatalharSprite, rectSourceSprite);

        //Mudança de tela para cenário batalha
        if(CenarioBatalha){
            CenarioGinasio2 = 0;
            CenarioBatalha = 1;
            CenarioLuta = 0;
            TerceiroCenario = 0;
        }
    }
    window.draw(SomSprite);
    window.display();
    
    //A personagem entra numa área específica da tela e vai para o cenário principal
    if(PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada >= 580 && (PersonagemSprite.getPosition().x > 370 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 430)){
        TerceiroCenario = 1;
        CenarioGinasio2 = 0;
        PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
        PersonagemSprite.setPosition(Ginasio2Sprite.getPosition().x + 45*EscalaCentro, Ginasio2Sprite.getPosition().y + 79*EscalaCentro);
    }
}

// Luta contra pokémons selvagens
void Jogo::TelaCenarioLuta(){
    //Verifica som
    if(Music){
        if(!LutaMusic.getStatus()){
            LutaMusic.play();
        }else if (PrincipalMusic.getStatus() == 2){
            PrincipalMusic.stop();
        }
    }else
        LutaMusic.stop();

    //Ponteiros que vão apontar para os pokemons que estão batalhando
    //Atuliza o ponteiro para o pokemon que está vivo somente a primeira vez, pois dps faz isso na função batalha
    if(botaoFugir)
        seuPokemonBatalhando = SeusPokemons.pokemonQueVaiBatalhar(&posicaoDoSeuPokemon);
    //Atualiza com o pokemon inimigo sorteado aleatoriamente
    pokemonAdversarioBatalhando = PokemonsCapturaveis.getPokemon(PokemonLuta);

    PosicaoMouse();
    Atacar = AtualizaBotao(Event, position, AtacarSprite, rectSourceSprite);
    Fugir = AtualizaBotao(Event, position, FugirSprite, rectSourceSprite);

    window.clear();
    //Caso não tenha pokemons vivos, gameover
    if(SeusPokemons.getQntPokemonsBatalhaveis() == 0){
        CenarioLuta = 0;
        CenarioPerdeu = 1;
    }
    //Caso tenha pokemons vivos
    else{
        //Seta a posição e a escala do pokemon adversário
        PokemonAdversarioSprite[PokemonLuta].setPosition(535, 180);
        PokemonAdversarioSprite[PokemonLuta].setScale(EscalaPokemonLuta, EscalaPokemonLuta);

        //Seta a posição e a escala do pokemon aliado
        PokemonSprite[seuPokemonBatalhando->getID()].setPosition(120, 310);
        PokemonSprite[seuPokemonBatalhando->getID()].setScale(EscalaPokemonLuta, EscalaPokemonLuta);

        window.draw(CenarioLutaSprite);

        //Mostra o nível de ataque do pokemon aliado
        if(seuPokemonBatalhando->getAtaque() == 1){
            window.draw(FracoSprite[0]);
        }else if (seuPokemonBatalhando->getAtaque() == 2){
            window.draw(MedioSprite[0]);
        }else if (seuPokemonBatalhando->getAtaque() == 3){
            window.draw(ForteSprite[0]);
        }

        //Mostra o nível de ataque do pokemon inimigo
        if(pokemonAdversarioBatalhando->getAtaque() == 1){
            window.draw(FracoSprite[1]);
        }else if (pokemonAdversarioBatalhando->getAtaque() == 2){
            window.draw(MedioSprite[1]);
        }else if (pokemonAdversarioBatalhando->getAtaque() == 3){
            window.draw(ForteSprite[1]);
        }

        //Mostra a vida do pokemon inimigo
        for(int a = 0; a < pokemonAdversarioBatalhando->getVida(); a++){
            window.draw(VidaSprite[a]);
        }

        //Mostra a vida do pokemon aliado
        for(int a = 0; a < seuPokemonBatalhando->getVida(); a++){
            window.draw(VidaSprite[a+6]);
        }

        window.draw(AtacarSprite);

        //Caso não tenha atacado ainda o inimigo, há a opção de fugir
        if(botaoFugir)
            window.draw(FugirSprite);

        window.draw(PokemonAdversarioSprite[PokemonLuta]);
        window.draw(PokemonSprite[seuPokemonBatalhando->getID()]);

        //Realiza a batalha dos pokemons
        Batalha();
    }
    window.display();

    //Caso escolha fugir ou o pokemon inimigo está morto
    if((Fugir && botaoFugir) || !pokemonAdversarioBatalhando->estaVivo()){
        //Captura o pokemon inimigo
        if(!pokemonAdversarioBatalhando->estaVivo()){
            if (SeusPokemons.getTamanho() < 20)
                CapturarPokemon(pokemonAdversarioBatalhando);
            setQntMoedas(derrubaMoedas(pokemonAdversarioBatalhando->getAtaque()));
        }

        //Atualiza a variável auxiliar para verificar se fugiu e volta para o cenário principal
        botaoFugir = true;
        if(cenarioAnterior == 1) {
            PrimeiroCenario = 1;
            CenarioLuta = 0;
            cenarioAnterior = 0;
        } else if(cenarioAnterior == 2) {
            SegundoCenario = 1;
            CenarioLuta = 0;
            cenarioAnterior = 0;
        } else if(cenarioAnterior == 3) {
            TerceiroCenario = 1;
            CenarioLuta = 0;
            cenarioAnterior = 0;
        }

        //Sorteia novamente dois lugares aleatórios para a personagem colidir e capturar pokemons
        inicio = 1;
    }
}

// Batalha contra líder pokémon
void Jogo::TelaCenarioBatalha(){
    //Verifica o som
    if(Music){
        if(!BatalhaMusic.getStatus()){
            BatalhaMusic.play();
        }else if(PrincipalMusic.getStatus() == 2){
            PrincipalMusic.stop();
        }
    }else
        BatalhaMusic.stop();

    //Atualiza o pokemon aliado e inimigo
    if(botaoFugir){
        seuPokemonBatalhando = SeusPokemons.pokemonQueVaiBatalhar(&posicaoDoSeuPokemon);
        pokemonAdversarioBatalhando = BatalhaGinasio1.pokemonQueVaiBatalhar(&posicaoAdversario);
    }

    PosicaoMouse();
    Atacar = AtualizaBotao(Event, position, AtacarSprite, rectSourceSprite);

    window.clear();
    //Caso não tenha pokemons, gameover
    if(SeusPokemons.getQntPokemonsBatalhaveis() == 0){
        CenarioBatalha = 0;
        CenarioPerdeu = 1;
    }else{
        //Seta a posição e a escala no pokemon adversário
        PokemonAdversarioSprite[pokemonAdversarioBatalhando->getID()].setPosition(535, 180);
        PokemonAdversarioSprite[pokemonAdversarioBatalhando->getID()].setScale(EscalaPokemonLuta, EscalaPokemonLuta);

        //Seta a posição e a escala do pokemon aliado
        PokemonSprite[seuPokemonBatalhando->getID()].setPosition(120, 310);
        PokemonSprite[seuPokemonBatalhando->getID()].setScale(EscalaPokemonLuta, EscalaPokemonLuta);

        window.draw(CenarioLutaSprite);

        //Mostra o nível de ataque do pokemon aliado
        if(seuPokemonBatalhando->getAtaque() == 1){
            window.draw(FracoSprite[0]);
        }else if (seuPokemonBatalhando->getAtaque() == 2){
            window.draw(MedioSprite[0]);
        }else if (seuPokemonBatalhando->getAtaque() == 3){
            window.draw(ForteSprite[0]);
        }

        //Mostra o nível de ataque do pokemon inimigo
        if(pokemonAdversarioBatalhando->getAtaque() == 1){
            window.draw(FracoSprite[1]);
        }else if(pokemonAdversarioBatalhando->getAtaque() == 2){
            window.draw(MedioSprite[1]);
        }else if(pokemonAdversarioBatalhando->getAtaque() == 3){
            window.draw(ForteSprite[1]);
        }

        //Vida do pokemon inimigo
        for(int a = 0; a < pokemonAdversarioBatalhando->getVida(); a++){
            window.draw(VidaSprite[a]);
        }

        //Vida do pokemon aliado
        for(int a = 0; a < seuPokemonBatalhando->getVida(); a++){
            window.draw(VidaSprite[a+6]);
        }

        window.draw(AtacarSprite);
        window.draw(PokemonAdversarioSprite[pokemonAdversarioBatalhando->getID()]);
        window.draw(PokemonSprite[seuPokemonBatalhando->getID()]);

        //Realiza o ataque
        Batalha();

        //Caso tenha ganho a batalha
        if(!pokemonAdversarioBatalhando->estaVivo()){
            CenarioBatalha = 0;
            SegundoCenario = 1;

            ArvoresCutSprite.setPosition(850,221);
            LiderGinasio1Sprite.setPosition(850,221);
            LiderGinasio1ColisaoSprite.setPosition(850,221);

            PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
            AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
            LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
            PersonagemSprite.setPosition(Ginasio1Sprite.getPosition().x + 45*EscalaCentro, Ginasio1Sprite.getPosition().y + 79*EscalaCentro);
            //CenarioGanhou = 1;
        }
    }
    window.display();
}

void Jogo::TelaCenarioGanhou(){
    //Verifica o som
    if(!GanhouMusic.getStatus()) {
        GanhouMusic.play();
    }else if((PrincipalMusic.getStatus() == 2) || (BatalhaMusic.getStatus() == 2)){
        PrincipalMusic.stop();
        BatalhaMusic.stop();
    }

    window.clear();
    window.draw(GanhouSprite);
    window.draw(BotaoGanhouSprite);
    window.display();

    PosicaoMouse();
    //Verifica se quer jogar novamente
    if(AtualizaBotao(Event, position, BotaoGanhouSprite, rectSourceSprite)){
        Reseta();
    }
}

void Jogo::TelaCenarioPerdeu(){
    //Verifica o som
    if(!PerdeuMusic.getStatus()){
        PerdeuMusic.play();
    }else if((PrincipalMusic.getStatus() == 2) || (LutaMusic.getStatus() == 2) || (BatalhaMusic.getStatus() == 2)){
        PrincipalMusic.stop();
        LutaMusic.stop();
        BatalhaMusic.stop();
    }

    window.clear();
    window.draw(GameOverSprite);
    window.draw(BotaoPerdeuSprite);
    window.display();

    PosicaoMouse();
    //Verifica se quer jogar novamente
    if(AtualizaBotao(Event, position, BotaoPerdeuSprite, rectSourceSprite)){
        Reseta();
    }
}

void Jogo::Run(){
    //Cria a janela .exe
    window.create(sf::VideoMode(LarguraTela, AlturaTela), "Pokewomon", sf::Style::Close);
    window.setFramerateLimit(60); //Setar velocidade para qualquer computador

    //Carrega as imagens e sons
    CarregaImagens();
    CarregaSons();
    //PikachuSound.play();

    while(window.isOpen()){
        Eventos();

        PrincipalMusic.setLoop(true);
        BatalhaMusic.setLoop(true);
        CentroMusic.setLoop(true);
        LutaMusic.setLoop(true);
        PerdeuMusic.setLoop(true);

        //Menu
        if(((!Start) && (!Instrucoes) && (!Sair))){
            //Verifica Musica
            if(!PrincipalMusic.getStatus()){
                PrincipalMusic.play();
            }else if((PerdeuMusic.getStatus() == 2) || (GanhouMusic.getStatus() == 2)){
                PerdeuMusic.stop();
                GanhouMusic.stop();
            }
            Menu();
        }

        //Jogo
        else if(Start){
            srand(time(NULL));

            //Tela para escolher o pokemon inicial
            if(PokemonInicial){
                TelaCenarioPokemonInicial();
            }
            //Primeiro cenário do jogo
            else if(PrimeiroCenario){
                TelaPrimeiroCenario();
            }
            //Segundo cenário do jogo
            else if(SegundoCenario){
                TelaSegundoCenario();
            }
            //Terceiro cenário do jogo
            else if(TerceiroCenario){
                TelaTerceiroCenario();
            }
            //Quarto cenário do jogo
            else if(QuartoCenario){
                TelaQuartoCenario();
            }
            //Cenário para realar os pokemons
            else if(CenarioCentro){
                TelaCenarioCentro();
            }
            //Cenário para entrar no ginásio
            else if(CenarioGinasio1){
                TelaCenarioGinasio1();
            }
            //Cenário para entrar no ginásio
            else if(CenarioGinasio2){
                TelaCenarioGinasio2();
            }
            /*//Cenário para entrar no ginásio
            else if(CenarioGinasio3){
                TelaCenarioGinasio3();
            }*/
            //Cenário para lutar na batalha
            else if(CenarioLuta) {
                TelaCenarioLuta();
            }
            //Cenário para lutar no ginásio
            else if(CenarioBatalha){
                TelaCenarioBatalha();
            }
            //Cenário de vitória
            else if (CenarioGanhou){
                TelaCenarioGanhou();
            }
            //Cenário de derrota
            else if (CenarioPerdeu){
                TelaCenarioPerdeu();
            }
        }
        //Instruções
        else if(Instrucoes){
            Instrucao();
            if(!PrincipalMusic.getStatus())
                PrincipalMusic.play();
        }
        //Sair
        else if(Sair){
            SeusPokemons.RetirarTodosElementos();
            window.close();
        }
    }
}