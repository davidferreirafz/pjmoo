///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Jogo.h"

int main(int argc, char * argv[]) 
{
    GAT* jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->executar();
    } catch (std::exception& e) {
        UtilLog::sistema("!!!!!!!!!!");
        UtilLog::sistema("Exceção: %s",e.what());
        UtilLog::sistema("!!!!!!!!!!");
    } catch (...) {
        UtilLog::sistema("!!!!!!!!!!");
        UtilLog::sistema("Exceção Desconhecida");
        UtilLog::sistema("!!!!!!!!!!");
    }

    delete(jogo);

    return 0;
}
//Construtor

//Construtor
Jogo::Jogo(int argc, char * argv[]):GAT(argc,argv)
{
}

//Destrutor
Jogo::~Jogo() 
{
    delete(david);
    delete(controle);
}
//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
void Jogo::inicializarRecursos() 
{
//configurando modo de vídeo
    frameworkGBF->setTitulo("FZPong","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen());
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_ON);
    //carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("personagem","data//imagem//sprites.png");
    GSIBManager->carregar("background","data//imagem//background.png");

    //carregando fontes
    frameworkGBF->writeSystem->carregar("menu",frameworkGBF->getPath()+"data//fonte//kiloton.png");
    frameworkGBF->writeSystem->carregar("texto",frameworkGBF->getPath()+"data//fonte//kiloton_18.png");


//carregando audio - efeitos
    frameworkGBF->soundSystem->fxManager->carregar("ponto","data//som//ponto.wav");
    frameworkGBF->soundSystem->fxManager->carregar("ping","data//som//ping.wav");
    frameworkGBF->soundSystem->fxManager->carregar("iniciando","data//som//iniciando.wav");
    frameworkGBF->soundSystem->fxManager->carregar("gameover","data//som//gameover.wav");
    frameworkGBF->soundSystem->fxManager->carregar("raquete","data//som//raquete.wav");
    frameworkGBF->soundSystem->fxManager->carregar("vitoria","data//som//applause.ogg");
    frameworkGBF->soundSystem->musicManager->carregar("musica","data//som//404_nemo.ogg");
    frameworkGBF->soundSystem->musicManager->carregar("menu","data//som//apes_r-jonny_ho.ogg");

//Configura volume dos efeitos
    frameworkGBF->soundSystem->fxManager->setVolume("ping",100);
    frameworkGBF->soundSystem->fxManager->setVolume("raquete",110);
    frameworkGBF->soundSystem->fxManager->setVolume("ponto",128);
    frameworkGBF->soundSystem->fxManager->setVolume("iniciando",60);
    frameworkGBF->soundSystem->fxManager->setVolume("gameover",80);
    frameworkGBF->soundSystem->fxManager->setVolume("vitoria",80);
    frameworkGBF->soundSystem->musicManager->setVolume("musica",20);
    frameworkGBF->soundSystem->musicManager->setVolume("menu",30);
//configura limites para som estereo
    frameworkGBF->soundSystem->fxManager->setLimite(0,640);


    //Idioma
    frameworkGBF->writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF->writeSystem->uiTexto->detectarIdioma();

    SpriteFactory * spriteFactory = NULL;

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("background"));
    FrameLayer * background = spriteFactory->criarFrameLayer(0, 0,640,480);
    background->setFrame(0,0,640,480);
    background->setTiles(1,1);
    background->setPixelTile(640,480);
    background->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("background",background);
    delete(spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("personagem"));
    david=spriteFactory->criarSpriteItem(30,21,90,68,1,1);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterfaceMenuTextoTransparente(frameworkGBF->inputSystem);
    uiMenuPrincipal->centralizarTela(640,120,HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(60);
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_1","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_2","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_3","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_4","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_5","menu"));

    controle = new Controle();
}
void Jogo::menuPrincipal() 
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    uiMenuPrincipal->executar();


    switch(uiMenuPrincipal->confirmarSelecao())
    {
        case 0:
                setMenuSobre();
            break;
        case 1:
                setJogo();
            break;
        case 2:
                setMenuCredito();
            break;
        case 3:
                setMenuAjuda();
            break;
        case 4:
                setSair();
            break;
    }
}
void Jogo::menuAjuda() 
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<9;i++){
        sprintf(textoFormatado,"tela_ajuda_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",20,80+(30*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("menu", 252, 20,"titulo_ajuda");


    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuCredito() 
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<6;i++){
        sprintf(textoFormatado,"tela_credito_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",20,140+(30*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("menu", 240, 20,"titulo_credito");

    david->desenhar(280,60);

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    } else {
        if (frameworkGBF->inputSystem->teclado->isKey(SDLK_t)){
            controle->ativarDemo(true);
            setJogo();
        } else if (frameworkGBF->inputSystem->teclado->isKey(SDLK_f)){
            controle->ativarDemo(false);
        }
    }
}
void Jogo::menuSobre() 
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<10;i++){
        sprintf(textoFormatado,"tela_sobre_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",20,80+(30*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("menu", 252, 20,"titulo_sobre");


    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::jogoNovo() 
{
    frameworkGBF->soundSystem->musicManager->playInfinity("musica");
    controle->iniciar();
    setJogoFaseCarregar();
}
void Jogo::jogoExecutando() 
{
    if (controle->isGameOver()){
        frameworkGBF->soundSystem->fxManager->play("gameover");
        setJogoGameOver();
    } else if (controle->isSetFinalizado()){
        setJogoFaseFinalizada();
    } else {
        controle->executar(frameworkGBF->inputSystem);
    }
}
void Jogo::jogoPause() 
{
    setMenu();
}
void Jogo::jogoFaseCarregar() 
{
//    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    controle->display();
    frameworkGBF->writeSystem->escreverLocalizado("menu" ,100,80,"fase_carregar");

    //frameworkGBF->writeSystem->escrever("texto" ,60,80,"%02d",controle->getNumeroSet());

    if (isTempoEspera()){
        setJogoExecutando();
        controle->iniciarSet();
    }
}
void Jogo::jogoFaseFinalizada() 
{
    setJogoFaseCarregar();
}
void Jogo::jogoGameOver() 
{
    char textoFormatado[30];
    controle->display();

    for (int i=0; i<2;i++){
        sprintf(textoFormatado,"tela_gameover_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",20,80+(30*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("menu", 210, 40,"titulo_gameover");


    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenu();
        }
    }
}
void Jogo::jogoZerado() 
{
    char textoFormatado[30];
    controle->display();

    for (int i=0; i<2;i++){
        sprintf(textoFormatado,"tela_zerado_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",20,80+(30*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("menu", 190, 40,"titulo_zerado");


    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenu();
        }
    }
}
bool Jogo::gatilhoJogoFaseCarregar() 
{
    bool continua = true;

    if (controle->isFinalizado()){
        frameworkGBF->soundSystem->fxManager->play("vitoria");
        setJogoZerado();
        continua = false;
    } else {
        frameworkGBF->soundSystem->fxManager->play("iniciando");
        controle->prepararSet();
    }
    return continua;
}
void Jogo::gatilhoMenuPrincipal() 
{
    frameworkGBF->soundSystem->musicManager->playInfinity("menu");
}
bool Jogo::desenharBotaoEnter() 
{
    bool desenhe = isTempoEspera();

    if (desenhe){
        frameworkGBF->writeSystem->escreverLocalizado("menu",20,420,"botao_enter");
    }

    return desenhe;
}
