#include "game.h"
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
#define EscalaCentro 2.0
#define EscalaPersonagem 1.0
#define EscalaPersonagemCentro 2.5
#define EscalaLider 2.7
#define EscalaPokemonLuta 2.5
#define EscalaPokemonBolsa 0.7

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
    CenarioPrincipal = 0;
    CenarioGinasio = 0;
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
    PokemonsCapturaveis.InserirNoFinal(0);
    PokemonsCapturaveis.InserirNoFinal(1);
    PokemonsCapturaveis.InserirNoFinal(2);
    PokemonsCapturaveis.InserirNoFinal(3);
    PokemonsCapturaveis.InserirNoFinal(4);
    PokemonsCapturaveis.InserirNoFinal(5);
    PokemonsCapturaveis.InserirNoFinal(6);
    PokemonsCapturaveis.InserirNoFinal(7);
    PokemonsCapturaveis.InserirNoFinal(8);

    //Lista pokemons inimigos ginásio
    batalhaGinasio.InserirNoFinal(3);
    batalhaGinasio.InserirNoFinal(4);
    batalhaGinasio.InserirNoFinal(5);
    batalhaGinasio.InserirNoFinal(6);
    batalhaGinasio.InserirNoFinal(7);
    batalhaGinasio.InserirNoFinal(8);
    batalhaGinasio.CurarTodaLista();
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
    CenarioPrincipal = 0;
    CenarioGinasio = 0;
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
    batalhaGinasio.CurarTodaLista();
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
    //*************************************************Cenário Menu
    CenarioMenuTexture.loadFromFile("Imagens/Menu.png");
    CenarioMenuSprite.setTexture(CenarioMenuTexture);

    //Play
    PlayTexture.loadFromFile("Imagens/BotaoJogar.png");
    rectSourceSprite = sf::IntRect(0, 0, 215, 79); //Corta a imagem
    PlaySprite = sf::Sprite(PlayTexture, rectSourceSprite);
    PlaySprite.setPosition(50, AlturaTela/2);

    //Instruções
    InstruTexture.loadFromFile("Imagens/BotaoInstrucoes.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    InstruSprite = sf::Sprite(InstruTexture, rectSourceSprite);
    InstruSprite.setPosition(50, AlturaTela/2 + 80);

    //Sair
    SairTexture.loadFromFile("Imagens/BotaoSair.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    SairSprite = sf::Sprite(SairTexture, rectSourceSprite);
    SairSprite.setPosition(50, AlturaTela/2 + 160);

    //***************************************************Cenário Instruções
    CenarioInstruTexture.loadFromFile("Imagens/Instrucoes.png");
    CenarioInstruSprite.setTexture(CenarioInstruTexture);

    //Botão voltar no cenário instruções
    VoltarTexture.loadFromFile("Imagens/BotaoVoltar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    VoltarSprite = sf::Sprite(VoltarTexture, rectSourceSprite);
    VoltarSprite.setPosition(LarguraTela - 250, AlturaTela - 120);

    //***************************************************Cenário escolha pokemon
    CenarioEscolhaPokemonTexture.loadFromFile("Imagens/EscolhaPokemon.png");
    CenarioEscolhaPokemonSprite.setTexture(CenarioEscolhaPokemonTexture);
    CenarioEscolhaPokemonSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

    //Pokemons iniciais
    //Pokemon1
    Pokemon1Texture.loadFromFile("Imagens/BotaoPokemon1.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon1Sprite = sf::Sprite(Pokemon1Texture, rectSourceSprite);
    Pokemon1Sprite.setPosition(124, 32);

    //Pokemon0
    Pokemon0Texture.loadFromFile("Imagens/BotaoPokemon0.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon0Sprite = sf::Sprite(Pokemon0Texture, rectSourceSprite);
    Pokemon0Sprite.setPosition(238, 493);

    //Pokemon2
    Pokemon2Texture.loadFromFile("Imagens/BotaoPokemon2.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    Pokemon2Sprite = sf::Sprite(Pokemon2Texture, rectSourceSprite);
    Pokemon2Sprite.setPosition(585, 246);

    //***************************************************Cenário de capturar pokemon
    Cenario1Texture.loadFromFile("Imagens/CenarioPrincipal.png");
    Cenario1Sprite.setTexture(Cenario1Texture);

    //Centro jogo
    CentroTexture.loadFromFile("Imagens/Centro.png");
    CentroSprite.setTexture(CentroTexture);
    CentroSprite.setScale(EscalaCentro, EscalaCentro);
    CentroSprite.setPosition(300,7);
    AlturaCentroAtualizada = AlturaCentro * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    //Centro jogo ------- Gambiarra
    Centro2Texture.loadFromFile("Imagens/Centro2.png");
    Centro2Sprite.setTexture(Centro2Texture);
    Centro2Sprite.setScale(EscalaCentro, EscalaCentro);
    Centro2Sprite.setPosition(300,7);
    AlturaCentroAtualizada2 = AlturaCentro2 * EscalaCentro;
    LarguraCentroAtualizada = LarguraCentro * EscalaCentro;

    //Placa centro jogo
    PlacaCentroTexture.loadFromFile("Imagens/PlacaCentro.png");
    PlacaCentroSprite.setTexture(PlacaCentroTexture);
    PlacaCentroSprite.setPosition(272,128);

    //Aviso da placa do centro
    AvisoPlacaCentroTexture.loadFromFile("Imagens/AvisoCentro.png");
    AvisoPlacaCentroSprite.setTexture(AvisoPlacaCentroTexture);
    AvisoPlacaCentroSprite.setPosition(285.5,500);

    //Placa ginásio
    PlacaCenario2Texture.loadFromFile("Imagens/PlacaCenario2.png");
    PlacaCenario2Sprite.setTexture(PlacaCenario2Texture);
    PlacaCenario2Sprite.setPosition(784,122);

    //Aviso da placa do ginásio
    AvisoPlacaCenario2Texture.loadFromFile("Imagens/AvisoGinasio.png");
    AvisoPlacaCenario2Sprite.setTexture(AvisoPlacaCenario2Texture);
    AvisoPlacaCenario2Sprite.setPosition(285.5,500);

    //Matinho
    MatinhoTexture.loadFromFile("Imagens/Matinho.png");

    //Dispõe os matinhos em uma area da tela
    for(i=0; i<16; i++){
        for(int j=0; j<35; j++){
            MatinhoSprite[i][j].setTexture(MatinhoTexture);
            if(j == 0){
                if(i == 0)
                    MatinhoSprite[i][j].setPosition(150, 300);
                else
                    MatinhoSprite[i][j].setPosition(150, MatinhoSprite[i-1][j].getPosition().y + 17);
            }
            else
                MatinhoSprite[i][j].setPosition(MatinhoSprite[i][j-1].getPosition().x + 17, MatinhoSprite[i][j-1].getPosition().y);
        }
    }

    //Cerca
    Cerca1Texture.loadFromFile("Imagens/Cerca1.png");
    Cerca1Sprite.setTexture(Cerca1Texture);
    Cerca1Sprite.setPosition(0,128);

    Cerca2Texture.loadFromFile("Imagens/Cerca2.png");
    Cerca2Sprite.setTexture(Cerca2Texture);
    Cerca2Sprite.setPosition(465,128);

    //Cerca -------- Gambiarra
    Cerca12Texture.loadFromFile("Imagens/Cerca12.png");
    Cerca12Sprite.setTexture(Cerca12Texture);
    Cerca12Sprite.setPosition(0,128);

    Cerca22Texture.loadFromFile("Imagens/Cerca22.png");
    Cerca22Sprite.setTexture(Cerca22Texture);
    Cerca22Sprite.setPosition(465,128);

    //Rio
    RioTexture.loadFromFile("Imagens/Rio.png");
    RioSprite.setTexture(RioTexture);
    RioSprite.setPosition(20,415);

    //Pokemon invisivel
    InvisivelTexture.loadFromFile("Imagens/PokemonInvisivel.png");
    InvisivelSprite[0].setTexture(InvisivelTexture);
    InvisivelSprite[1].setTexture(InvisivelTexture);

    //Bolsa de pokémons
    BolsaTexture.loadFromFile("Imagens/Bolsa.png");
    BolsaSprite.setTexture(BolsaTexture);
    BolsaSprite.setPosition(495,9);

    //Personagem jogo
    PersonagemTexture.loadFromFile("Imagens/Personagem.png");
    PersonagemSprite.setTexture(PersonagemTexture);
    PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
    PersonagemSprite.setPosition(0,155);
    AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
    LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;

    //***************************************************Cenário Centro
    Cenario2Texture.loadFromFile("Imagens/CenarioCentro.png");
    Cenario2Sprite.setTexture(Cenario2Texture);

    //Balcao do Centro
    BalcaoCentroTexture.loadFromFile("Imagens/BalcaoCentro.png");
    BalcaoCentroSprite.setTexture(BalcaoCentroTexture);
    BalcaoCentroSprite.setPosition(51,81);

    //Balcao do Centro ------- Gambiarra
    BalcaoCentro2Texture.loadFromFile("Imagens/BalcaoCentro2.png");
    BalcaoCentro2Sprite.setTexture(BalcaoCentro2Texture);
    BalcaoCentro2Sprite.setPosition(51,81);

    //Planta do Centro
    PlantaCentroTexture.loadFromFile("Imagens/PlantaCentro.png");
    PlantaCentroSprite.setTexture(PlantaCentroTexture);
    PlantaCentroSprite.setPosition(0,172);

    //Planta do Centro ------- Gambiarra
    PlantaCentro2Texture.loadFromFile("Imagens/PlantaCentro2.png");
    PlantaCentro2Sprite.setTexture(PlantaCentro2Texture);
    PlantaCentro2Sprite.setPosition(0,172);

    //Mesa do Centro
    MesaCentroTexture.loadFromFile("Imagens/MesaCentro.png");
    MesaCentroSprite.setTexture(MesaCentroTexture);
    MesaCentroSprite.setPosition(694,164);

    //Mesa do Centro ------- Gambiarra
    MesaCentro2Texture.loadFromFile("Imagens/MesaCentro2.png");
    MesaCentro2Sprite.setTexture(MesaCentro2Texture);
    MesaCentro2Sprite.setPosition(694,164);

    //Maquina do Centro
    MaquinaCentroTexture.loadFromFile("Imagens/MaquinaCentro.png");
    MaquinaCentroSprite.setTexture(MaquinaCentroTexture);
    MaquinaCentroSprite.setPosition(640,182);

    //Maquina do Centro ------- Gambiarra
    MaquinaCentro2Texture.loadFromFile("Imagens/MaquinaCentro2.png");
    MaquinaCentro2Sprite.setTexture(MaquinaCentro2Texture);
    MaquinaCentro2Sprite.setPosition(640,182);

    //Cenário comprar pokebolas e healar pokemons
    AvisoPokebolaTexture.loadFromFile("Imagens/AvisoPokebola.png");
    AvisoPokebolaSprite.setTexture(AvisoPokebolaTexture);
    AvisoPokebolaSprite.setPosition(95.5,450);

    //Botão healar
    HealarTexture.loadFromFile("Imagens/BotaoEncherVida.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    HealarSprite = sf::Sprite(HealarTexture, rectSourceSprite);
    HealarSprite.setPosition(200, 520);

    //Botão comprar pokebola
    CompraPokebolaTexture.loadFromFile("Imagens/BotaoPokebola.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    CompraPokebolaSprite = sf::Sprite(CompraPokebolaTexture, rectSourceSprite);
    CompraPokebolaSprite.setPosition(440, 520);

    //Aviso bolsa do centro
    AvisoPokemonTexture.loadFromFile("Imagens/AvisoPokemons.png");
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

    //***************************************************Cenário Ginásio
    Cenario3Texture.loadFromFile("Imagens/CenarioGinasio.png");
    Cenario3Sprite.setTexture(Cenario3Texture);

    //Chão Ginásio
    ChaoGinasioTexture.loadFromFile("Imagens/ChaoGinasio.png");
    ChaoGinasioSprite.setTexture(ChaoGinasioTexture);
    ChaoGinasioSprite.setPosition(0,130);

    //Lider Ginásio
    LiderGinasioTexture.loadFromFile("Imagens/LiderGinasio.png");
    LiderGinasioSprite.setTexture(LiderGinasioTexture);
    LiderGinasioSprite.setPosition(540,240);
    LiderGinasioSprite.setScale(EscalaLider, EscalaLider);

    //Lider Ginásio --- gambiarra
    LiderGinasio2Texture.loadFromFile("Imagens/LiderGinasioGambiarra.png");
    LiderGinasio2Sprite.setTexture(LiderGinasio2Texture);
    LiderGinasio2Sprite.setPosition(553,240);
    LiderGinasio2Sprite.setScale(EscalaLider, EscalaLider);

    //Aviso lider
    AvisoLiderTexture.loadFromFile("Imagens/AvisoLider.png");
    AvisoLiderSprite.setTexture(AvisoLiderTexture);
    AvisoLiderSprite.setPosition(95.5,450);

    //Botão batalhar com a líder
    BatalharTexture.loadFromFile("Imagens/BotaoDesafiar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    BatalharSprite = sf::Sprite(BatalharTexture, rectSourceSprite);
    BatalharSprite.setPosition(320, 520);

    //***************************************************Cenário Luta
    CenarioLutaTexture.loadFromFile("Imagens/CenarioLuta.png");
    CenarioLutaSprite.setTexture(CenarioLutaTexture);
    CenarioLutaSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

    //Botão atacar no cenário luta
    AtacarTexture.loadFromFile("Imagens/BotaoAtacar.png");
    rectSourceSprite = sf::IntRect(0, 0, 201, 71); //Corta a imagem
    AtacarSprite = sf::Sprite(AtacarTexture, rectSourceSprite);
    AtacarSprite.setPosition(LarguraTela/2 - 300, AlturaTela - 105);

    //Botão fugir no cenário luta
    FugirTexture.loadFromFile("Imagens/BotaoFugir.png");
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

    //***************************************************Pokémons
    for (int a = 0; a < 9; a++){
        switch(a){
            case 0: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon0.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon0Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda0.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda0Morto.png");
                    break;
            case 1: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon1.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon1Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda1.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda1Morto.png");
                    break;
            case 2: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon2.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon2Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda2.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda2Morto.png");
                    break;
            case 3: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon3.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon3Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda3.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda3Morto.png");
                    break;
            case 4: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon4.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon4Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda4.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda4Morto.png");
                    break;
            case 5: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon5.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon5Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda5.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda5Morto.png");
                    break;
            case 6: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon6.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon6Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda6.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda6Morto.png");
                    break;
            case 7: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon7.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon7Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda7.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda7Morto.png");
                    break;
            case 8: //Pokemon vivo
                    PokemonTexture[a].loadFromFile("Imagens/Pokemon8.png");
                    //Pokemon morto
                    PokemonMortoTexture[a].loadFromFile("Imagens/Pokemon8Morto.png");
                    //Pokemon borda vivo
                    PokemonBordaTexture[a].loadFromFile("Imagens/PokemonBorda8.png");
                    //Pokemon borda morto
                    PokemonBordaMortoTexture[a].loadFromFile("Imagens/PokemonBorda8Morto.png");
                    break;
        }
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

    //***************************************************Cenário Perdeu
    GameOverTexture.loadFromFile("Imagens/Perdeu.png");
    GameOverSprite.setTexture(GameOverTexture);

    //Botão jogar novamente quando perde
    BotaoPerdeuTexture.loadFromFile("Imagens/BotaoJogarPerdeu.png");
    BotaoPerdeuSprite.setTexture(BotaoPerdeuTexture);
    BotaoPerdeuSprite.setPosition(479,492);

    //***************************************************Cenário Ganhou
    GanhouTexture.loadFromFile("Imagens/Ganhou.png");
    GanhouSprite.setTexture(GanhouTexture);

    //Botão jogar novamente quando ganha
    BotaoGanhouTexture.loadFromFile("Imagens/BotaoJogarGanhou.png");
    BotaoGanhouSprite.setTexture(BotaoGanhouTexture);
    BotaoGanhouSprite.setPosition(479,492);

    //***************************************************Som
    SomTexture.loadFromFile("Imagens/Som.png");
    SomSprite.setTexture(SomTexture);
    SomSprite.setPosition(0,0);
    SomSprite.setScale(0.8, 0.8);
    SomSprite.setTextureRect(sf::IntRect(Music*52, 0, 52, 54));
}

void Jogo::CarregaSons(){
    //Música principal
    PrincipalMusic.openFromFile("Som/CenarioPrincipalSom.wav");
    PrincipalMusic.setVolume(200);

    //Música batalha
    BatalhaMusic.openFromFile("Som/CenarioBatalhaSom.wav");
    BatalhaMusic.setVolume(200);

    //Música centro
    CentroMusic.openFromFile("Som/CenarioCentroSom.wav");
    CentroMusic.setVolume(200);

    //Música ganhou
    GanhouMusic.openFromFile("Som/CenarioGanhouSom.wav");
    GanhouMusic.setVolume(200);

    //Música luta
    LutaMusic.openFromFile("Som/CenarioLutaSom.wav");
    LutaMusic.setVolume(200);

    //Música perdeu
    PerdeuMusic.openFromFile("Som/CenarioPerdeuSom.wav");
    PerdeuMusic.setVolume(200);
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
            if(CenarioPrincipal == 1){
                PersonagemSprite.move(-Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds()))
                    PersonagemSprite.move(+Esquerda.x*delta,Esquerda.y);
            }else if(CenarioGinasio){
                PersonagemSprite.move((-Esquerda.x-120)*delta,Esquerda.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio2Sprite.getGlobalBounds()))
                    PersonagemSprite.move((+Esquerda.x+120)*delta,Esquerda.y);
                if(!PersonagemSprite.getGlobalBounds().intersects(ChaoGinasioSprite.getGlobalBounds()))
                    PersonagemSprite.move((+Esquerda.x+120)*delta,Esquerda.y);
            }else if(CenarioCentro){
                PersonagemSprite.move((-Esquerda.x-120)*delta,Esquerda.y);
            }
        }
    }
    //Movimenta para a direita
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //Verifica se não está no fim da tela pela direita
        if(PersonagemSprite.getPosition().x < LarguraTela - LarguraPersonagemAtualizada){
            AtualizaPersonagem.y = 3;
            if(CenarioPrincipal == 1){
                PersonagemSprite.move(Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds()))
                    PersonagemSprite.move(-Direita.x*delta,Direita.y);
            }else if(CenarioGinasio){
                PersonagemSprite.move((+Direita.x+120)*delta,Direita.y);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio2Sprite.getGlobalBounds())){
                    PersonagemSprite.move((-Direita.x-120)*delta,Direita.y);
                }
                if(!PersonagemSprite.getGlobalBounds().intersects(ChaoGinasioSprite.getGlobalBounds()))
                    PersonagemSprite.move((-Direita.x-120)*delta,Direita.y);
            }else if(CenarioCentro){
                PersonagemSprite.move((+Direita.x+120)*delta,Direita.y);
            }
        }
    }
    //Movimenta para baixo
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(PersonagemSprite.getPosition().y < AlturaTela - AlturaPersonagemAtualizada){
            AtualizaPersonagem.y = 1;
            if(CenarioPrincipal == 1){
                PersonagemSprite.move(Baixo.x,+Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,-Baixo.y*delta);
            }else if(CenarioGinasio){
                PersonagemSprite.move(Baixo.x,(+Baixo.y+120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Baixo.x,(-Baixo.y-120)*delta);
                if(!PersonagemSprite.getGlobalBounds().intersects(ChaoGinasioSprite.getGlobalBounds()))
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
            if(CenarioPrincipal == 1){
                PersonagemSprite.move(Cima.x,-Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Centro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(RioSprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca12Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(Cerca22Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,+Cima.y*delta);
            }else if(CenarioCentro){
                PersonagemSprite.move(Cima.x,(-Cima.y-120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(BalcaoCentro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
                else if(PersonagemSprite.getGlobalBounds().intersects(MesaCentro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
                else if(PersonagemSprite.getGlobalBounds().intersects(PlantaCentro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
                else if(PersonagemSprite.getGlobalBounds().intersects(MaquinaCentro2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
            }else if(CenarioGinasio){
                PersonagemSprite.move(Cima.x,(-Cima.y-120)*delta);
                if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasio2Sprite.getGlobalBounds()))
                    PersonagemSprite.move(Cima.x,(+Cima.y+120)*delta);
                if(!PersonagemSprite.getGlobalBounds().intersects(ChaoGinasioSprite.getGlobalBounds()))
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
    if((PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada - 12 > 300 && PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 300 + 272) &&
       (PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada/2 > 150 && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada/2 < 150 + 595) && CenarioPrincipal)
        PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*27, AtualizaPersonagem.y*31, 27, 31-12));
    else
        PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*27, AtualizaPersonagem.y*31, 27, 31));
}

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
            if(CenarioBatalha && batalhaGinasio.getPokemon(5)->estaVivo()){
                pokemonAdversarioBatalhando = (batalhaGinasio.pokemonQueVaiBatalhar(&posicaoAdversario));
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

int Jogo::derrubaMoedas(int idOponente){
    if(idOponente == 0 || idOponente == 1 || idOponente == 2)
        return 1;
    if(idOponente == 3 || idOponente == 4 || idOponente == 5)
        return 2;
    if(idOponente == 6 || idOponente == 7 || idOponente == 8)
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
        CenarioPrincipal = 1;
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

void Jogo::TelaCenarioPrincipal(){
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

    //Curar pokemons que você está batalhando
    PokemonsCapturaveis.CurarTodaLista();

    MovimentoPersonagem();

    //Sprite invisível para ir para o cenário da luta
    while(inicio && (InvisivelSprite[1].getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[0].getGlobalBounds())
        || PersonagemSprite.getGlobalBounds().intersects(InvisivelSprite[1].getGlobalBounds()))){
        InvisivelSprite[0].setPosition(150 + (rand() % 228), 300 + (rand() %  136));
        InvisivelSprite[1].setPosition(378 + (rand() % 228), 300 + (rand() %  136));
    }

    //Para não entrar no while acima, já que será sorteado novamente na função luta
    inicio = 0;

    //Seta a posição e a escala do pokemon escolhido
    PokemonSprite[PokemonEscolha].setPosition(499, 13);
    PokemonSprite[PokemonEscolha].setScale(EscalaPokemonBolsa, EscalaPokemonBolsa);

    window.clear();
    window.draw(Cenario1Sprite);
    window.draw(PlacaCentroSprite);
    window.draw(PlacaCenario2Sprite);

    //Altera a imagem do matinho para dar a impressão de movimento
    for(i=0; i<16; i++){
        for(int j=0; j<35; j++){
            if(PersonagemSprite.getGlobalBounds().intersects(MatinhoSprite[i][j].getGlobalBounds()))
                MatinhoSprite[i][j].setTextureRect(sf::IntRect(16, 0, 16, 16));
            else
                MatinhoSprite[i][j].setTextureRect(sf::IntRect(0, 0, 16, 16));
            window.draw(MatinhoSprite[i][j]);
        }
    }

    window.draw(Cerca1Sprite);
    window.draw(Cerca2Sprite);
    window.draw(Cerca12Sprite);
    window.draw(Cerca22Sprite);
    window.draw(RioSprite);
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

    //Mostra a iagem dos pokemons na bolsa
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
    //A personagem entra em uma área especifica da tela e vai para o cenário do ginásio
    if(PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada >= LarguraTela && (PersonagemSprite.getPosition().y > 150 &&  PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 205)){
        CenarioPrincipal = 0;
        CenarioGinasio = 1;
        PersonagemSprite.setScale(EscalaPersonagemCentro, EscalaPersonagemCentro);
        PersonagemSprite.setPosition(0, PersonagemSprite.getPosition().y);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagemCentro;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagemCentro;
    }
    //A personagem entra em uma área especifica da tela e vai para o cenário do centro
    else if(PersonagemSprite.getGlobalBounds().intersects(CentroSprite.getGlobalBounds())){
        if(PersonagemSprite.getPosition().x > (CentroSprite.getPosition().x + 25*EscalaCentro) && PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < (Centro2Sprite.getPosition().x + 50*EscalaCentro)){
            CenarioPrincipal = 0;
            CenarioCentro = 1;
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
        CenarioPrincipal = 0;
        PokemonLuta = rand() % 9;
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

    //A personagem entra numa área específica da tela e vai para o cenário principal
    if((PersonagemSprite.getPosition().y > 600 - AlturaPersonagemAtualizada) && (PersonagemSprite.getPosition().x > 400 - 60 &&  PersonagemSprite.getPosition().x + LarguraPersonagemAtualizada < 400 + 60)){
        CenarioPrincipal = 1;
        CenarioCentro = 0;
        PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
        PersonagemSprite.setPosition(PersonagemSprite.getPosition().x, CentroSprite.getPosition().y + AlturaCentroAtualizada);
    }
}

void Jogo::TelaCenarioGinasio(){
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
    window.draw(Cenario3Sprite);
    window.draw(ChaoGinasioSprite);
    window.draw(LiderGinasioSprite);
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
    if(PersonagemSprite.getGlobalBounds().intersects(LiderGinasioSprite.getGlobalBounds())){
        window.draw(AvisoLiderSprite);
        window.draw(BatalharSprite);
        //PosicaoMouse();
        CenarioBatalha = AtualizaBotao(Event, position, BatalharSprite, rectSourceSprite);

        //Mudança de tela para cenário batalha
        if(CenarioBatalha){
            CenarioGinasio = 0;
            CenarioBatalha = 1;
            CenarioLuta = 0;
            CenarioPrincipal = 0;
        }
    }
    window.draw(SomSprite);
    window.display();

    //A personagem entra numa área específica da tela e vai para o cenário principal
    if(PersonagemSprite.getPosition().x < 0 && (PersonagemSprite.getPosition().y > 150 &&  PersonagemSprite.getPosition().y + AlturaPersonagemAtualizada < 255)){
        CenarioPrincipal = 1;
        CenarioGinasio = 0;
        PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
        AlturaPersonagemAtualizada = AlturaPersonagem * EscalaPersonagem;
        LarguraPersonagemAtualizada = LarguraPersonagem * EscalaPersonagem;
        PersonagemSprite.setPosition(800 - LarguraPersonagemAtualizada, PersonagemSprite.getPosition().y);
    }
}

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

        //Seta a posição e a escola do pokemon aliado
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
            setQntMoedas(derrubaMoedas(pokemonAdversarioBatalhando->getID()));
        }

        //Atualiza a variável auxiliar para verificar se fugiu e volta para o cenário principal
        botaoFugir = true;
        CenarioPrincipal = 1;
        CenarioLuta = 0;

        //Sorteia novamente dois lugares aleatórios para a personagem colidir e capturar pokemons
        inicio = 1;
    }
}

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
        pokemonAdversarioBatalhando = batalhaGinasio.pokemonQueVaiBatalhar(&posicaoAdversario);
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
            CenarioGanhou = 1;
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
    window.create(sf::VideoMode(LarguraTela, AlturaTela), "Pokemon", sf::Style::None);
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
            //Cenário para caçar pokemon
            else if(CenarioPrincipal){
                TelaCenarioPrincipal();
            }
            //Cenário para realar os pokemons
            else if(CenarioCentro){
                TelaCenarioCentro();
            }
            //Cenário para entrar no ginásio
            else if(CenarioGinasio){
                TelaCenarioGinasio();
            }
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
