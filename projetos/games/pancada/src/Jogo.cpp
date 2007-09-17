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
    delete(janelaAjuda);
    delete(janelaCredito);
    delete(janelaSobre);
    delete(janelaGameOver);
    delete(janelaFaseFinalizada);
    delete(janelaZerado);
}
//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
void Jogo::inicializarRecursos()
{
//configurando modo de vídeo
    frameworkGBF->setTitulo("Pancada","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen());
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);
    //carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("personagem","data//imagem//pancada_personagem.png");
    GSIBManager->carregar("background","data//imagem//pancada_console.png");
    GSIBManager->carregar("interface","data//imagem//pancada_interface.png");
    GSIBManager->carregar("ringue","data//imagem//pancada_ringue_01.png");
    GSIBManager->carregar("gbf-window-background","data//kernel//imagem//window-background.png");

    //carregando fontes
    frameworkGBF->writeSystem->carregar("texto",frameworkGBF->getPath()+"data//fonte//texto.png");
    frameworkGBF->writeSystem->carregar("menu",frameworkGBF->getPath()+"data//fonte//army.png");
    frameworkGBF->writeSystem->carregar("kiloton16",frameworkGBF->getPath()+"data//fonte//kiloton_16.png");
    frameworkGBF->writeSystem->carregar("kiloton24",frameworkGBF->getPath()+"data//fonte//kiloton_24.png");


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

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("background"));
    FrameLayer * ringue = spriteFactory->criarFrameLayer(0, 0,640,480);
    ringue->setFrame(0,0,640,480);
    ringue->setTiles(1,1);
    ringue->setPixelTile(640,480);
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
    uiMenuPrincipal->centralizarTela(640,120,HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(60);
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_1","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_2","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_3","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_4","menu"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_5","menu"));


    UserInterfaceVisualSolido * uiVisualSolido = new UserInterfaceVisualSolido();
    uiVisualSolido->setCorBorda(255,0,0);
    uiVisualSolido->setCorFundo(100,200,100);


    UserInterfaceVisualImagem *uiVisualImagem = new UserInterfaceVisualImagem();
    uiVisualImagem->setCorBorda(255,0,0);


    janelaCredito = new UserInterfaceWindowTitulo();
    janelaCredito->setPosicao(40,50);
    janelaCredito->setDimensao(560,400);
    janelaCredito->texto.setFonte("texto");
    janelaCredito->texto.setChaveTexto("tela_credito_%02d");
    janelaCredito->titulo.setFonte("menu");
    janelaCredito->titulo.setChaveTexto("titulo_credito");
    janelaCredito->setVisual(uiVisualSolido->clone());
    janelaCredito->adicionarBotao(new UserInterfaceBotao("menu","botao_enter"));
    janelaCredito->inicializar();

    janelaSobre = new UserInterfaceWindowTitulo();
    janelaSobre->setPosicao(40,50);
    janelaSobre->setDimensao(560,400);
    janelaSobre->texto.setFonte("texto");
    janelaSobre->texto.setChaveTexto("tela_sobre_%02d");
    janelaSobre->titulo.setFonte("menu");
    janelaSobre->titulo.setChaveTexto("titulo_sobre");
    janelaSobre->setVisual(uiVisualImagem->clone());
    janelaSobre->adicionarBotao(new UserInterfaceBotao("menu","botao_enter"));
    janelaSobre->inicializar();

    janelaFaseFinalizada = new UserInterfaceWindow();
    janelaFaseFinalizada->setPosicao(120,140);
    janelaFaseFinalizada->setDimensao(400,200);
    janelaFaseFinalizada->texto.setFonte("texto");
    janelaFaseFinalizada->texto.setChaveTexto("tela_fasefinalizada_%02d");
    janelaFaseFinalizada->texto.setAlinhamento(TEXTO_CENTRALIZADO);
    janelaFaseFinalizada->setVisual(uiVisualImagem->clone());
    janelaFaseFinalizada->inicializar();

    janelaGameOver = new UserInterfaceWindow();
    janelaGameOver->setPosicao(120,140);
    janelaGameOver->setDimensao(400,200);
    janelaGameOver->texto.setFonte("texto");
    janelaGameOver->texto.setChaveTexto("tela_gameover_%02d");
    janelaGameOver->texto.setAlinhamento(TEXTO_CENTRALIZADO);
    janelaGameOver->setVisual(uiVisualSolido->clone());
    janelaGameOver->inicializar();

    janelaZerado = new UserInterfaceWindow();
    janelaZerado->setPosicao(120,140);
    janelaZerado->setDimensao(400,200);
    janelaZerado->texto.setFonte("texto");
    janelaZerado->texto.setChaveTexto("tela_zerado_%02d");
    janelaZerado->texto.setAlinhamento(TEXTO_CENTRALIZADO);
    janelaZerado->setVisual(uiVisualSolido->clone());
    janelaZerado->inicializar();


    janelaAjuda = new UserInterfaceWindowTitulo();
    janelaAjuda->setPosicao(40,50);
    janelaAjuda->setDimensao(560,400);
    janelaAjuda->texto.setFonte("texto");
    janelaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    janelaAjuda->titulo.setFonte("menu");
    janelaAjuda->titulo.setChaveTexto("titulo_ajuda");
    janelaAjuda->setVisual(uiVisualSolido->clone());
    janelaAjuda->adicionarBotao(new UserInterfaceBotao("menu","botao_enter"));
//    janelaAjuda->setKey(SDLK_RETURN);
//    janelaAjuda->setJoyButton()
    janelaAjuda->inicializar();


    //remover depois, colocar embutido no framework
    UserInterfaceWindow::setInputSystem(frameworkGBF->inputSystem);

    delete(uiVisualSolido);
    delete(uiVisualImagem);

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
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaAjuda->executar();

    if (janelaAjuda->confirmarSelecao()==1){
        setMenuPrincipal();
    }
}
void Jogo::menuCredito()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaCredito->executar();

    if (janelaCredito->confirmarSelecao()==1){
        setMenuPrincipal();
    }
}
void Jogo::menuSobre()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaSobre->executar();

    if (janelaSobre->confirmarSelecao()==1){
        setMenuPrincipal();
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
    controle.desenhar();

    janelaFaseFinalizada->executar();

    if (janelaFaseFinalizada->confirmarSelecao()==1){
        setJogoFaseCarregar();
    }
}
void Jogo::jogoGameOver()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaGameOver->executar();

    if (janelaGameOver->confirmarSelecao()==1){
        setMenu();
    }
}
void Jogo::jogoZerado()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaZerado->executar();

    if (janelaZerado->confirmarSelecao()==1){
        setMenu();
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

