///***************************************************************************
// *   Pancada <Game - Pong Clone>                                           *
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
Jogo::Jogo(int argc, char * argv[]):GAT(argc,argv)
{
}

//Destrutor
Jogo::~Jogo()
{

}
//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
void Jogo::inicializarRecursos()
{
//configurando modo de vídeo
    frameworkGBF->setTitulo("Pancada","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen());
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_ON);
    //carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("personagem","data//imagem//pancada_personagem.png");
    GSIBManager->carregar("background","data//imagem//pancada_console.png");
    GSIBManager->carregar("status","data//imagem//pancada_status.png");
    GSIBManager->carregar("ringue","data//imagem//pancada_ringue_01.png");

    //carregando fontes
    frameworkGBF->writeSystem->carregar("texto",frameworkGBF->getPath()+"data//fonte//texto.png");
    frameworkGBF->writeSystem->carregar("menu",frameworkGBF->getPath()+"data//fonte//army.png");


//carregando audio - efeitos
//Configura volume dos efeitos


    //Idioma
    frameworkGBF->writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF->writeSystem->uiTexto->detectarIdioma();

//Layers
    SpriteFactory * spriteFactory = NULL;

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("status"));
    FrameLayer * status = spriteFactory->criarFrameLayer(0, 0,96,480);
    status->setFrame(544,0,96,480);
    status->setTiles(1,1);
    status->setPixelTile(96,480);
    status->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("status",status);
    delete(spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("ringue"));
    FrameLayer * ringue = spriteFactory->criarFrameLayer(0, 0,544,480);
    ringue->setFrame(0,0,544,480);
    ringue->setTiles(1,1);
    ringue->setPixelTile(544,480);
    ringue->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("ringue",ringue);
    delete(spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("background"));
    FrameLayer * console = spriteFactory->criarFrameLayer(0, 0,640,480);
    console->setFrame(0,0,640,480);
    console->setTiles(1,1);
    console->setPixelTile(640,480);
    console->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("background",console);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterfaceMenuTextoTransparente(frameworkGBF->inputSystem);
    uiMenuPrincipal->centralizarTela(500,120,HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(60);
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_1","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_2","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_3","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_4","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_5","menu"));

    controle.carregar();
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

    for (int i=0; i<11;i++){
        sprintf(textoFormatado,"tela_ajuda_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

    frameworkGBF->writeSystem->escreverLocalizado("menu", 220, 88,"titulo_ajuda");

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

    for (int i=0; i<11;i++){
        sprintf(textoFormatado,"tela_credito_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

    frameworkGBF->writeSystem->escreverLocalizado("menu", 220, 88,"titulo_credito");

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))||
            (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuSobre()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<11;i++){
        sprintf(textoFormatado,"tela_sobre_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

    frameworkGBF->writeSystem->escreverLocalizado("menu", 220, 88,"titulo_sobre");

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
    controle.iniciar();
    setJogoFaseCarregar();
}
void Jogo::jogoExecutando()
{
    if (controle.isGameOver()){
        setJogoGameOver();
    } else if (controle.isFaseFinalizada()){
        setJogoFaseFinalizada();
    } else {
        controle.executar(frameworkGBF->inputSystem);
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_p))||
            (frameworkGBF->inputSystem->joystick->isButtonC())){
                setJogoPause();
        }
        #ifdef DEBUG
        //Codigo utilizado para avança uma fase
        else if (frameworkGBF->inputSystem->teclado->isKey(SDLK_n)){
                setJogoFaseCarregar();
        }
        #endif
    }
}
void Jogo::jogoPause()
{
    setMenu();
}
void Jogo::jogoFaseCarregar()
{
    setJogoExecutando();
}
void Jogo::jogoFaseFinalizada()
{
    char textoFormatado[30];
    controle.desenhar();

    for (int i=0; i<7;i++){
        sprintf(textoFormatado,"tela_fasefinalizada_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setJogoFaseCarregar();
        }
    }
}
void Jogo::jogoGameOver()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<6;i++){
        sprintf(textoFormatado,"tela_gameover_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

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
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    for (int i=0; i<8;i++){
        sprintf(textoFormatado,"tela_zerado_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,120+(26*i),textoFormatado);
    }

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenu();
        }
    }
}
bool Jogo::gatilhoJogoFaseCarregar()
{
    bool continua = controle.carregarFase();

    if(!continua){
        setJogoZerado();
        //frameworkGBF->soundSystem->fxManager->play("iniciando");
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
