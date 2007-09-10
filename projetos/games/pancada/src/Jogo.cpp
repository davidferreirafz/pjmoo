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
    delete(caixaAjuda);
    delete(caixaCredito);
    delete(caixaSobre);
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
    GSIBManager->carregar("gbf-window-background","data//kernel//imagem//window-background-chess.png");

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


    UserInterfaceEstiloVisualSolido *uieVisual = new UserInterfaceEstiloVisualSolido();
    uieVisual->setCorBorda(255,0,0);
    uieVisual->setCorFundo(100,200,100);


    UserInterfaceEstiloVisualImagem *uieVisualImagem = new UserInterfaceEstiloVisualImagem();
    uieVisualImagem->setCorBorda(255,0,0);



    caixaAjuda = new CaixaTextoTitulo();
    caixaAjuda->setPosicao(40,50);
    caixaAjuda->setDimensao(560,400);
    caixaAjuda->texto.setFonte("texto");
    caixaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    caixaAjuda->titulo.setFonte("menu");
    caixaAjuda->titulo.setChaveTexto("titulo_ajuda");
    caixaAjuda->setEstiloVisual(uieVisual);
    caixaAjuda->inicializar();

    caixaCredito = new CaixaTextoTitulo();
    caixaCredito->setPosicao(40,50);
    caixaCredito->setDimensao(560,400);
    caixaCredito->texto.setFonte("texto");
    caixaCredito->texto.setChaveTexto("tela_credito_%02d");
    caixaCredito->titulo.setFonte("menu");
    caixaCredito->titulo.setChaveTexto("titulo_credito");
    caixaCredito->setEstiloVisual(uieVisual);
    caixaCredito->inicializar();

    caixaSobre = new CaixaTextoTitulo();
    caixaSobre->setPosicao(40,50);
    caixaSobre->setDimensao(560,400);
    caixaSobre->texto.setFonte("texto");
    caixaSobre->texto.setChaveTexto("tela_sobre_%02d");
    caixaSobre->titulo.setFonte("menu");
    caixaSobre->titulo.setChaveTexto("titulo_sobre");
    caixaSobre->setEstiloVisual(uieVisualImagem);
    caixaSobre->inicializar();

    caixaFaseFinalizada = new CaixaTexto();
    caixaFaseFinalizada->setPosicao(120,140);
    caixaFaseFinalizada->setDimensao(400,200);
    caixaFaseFinalizada->texto.setFonte("texto");
    caixaFaseFinalizada->texto.setChaveTexto("tela_fasefinalizada_%02d");
    caixaFaseFinalizada->setTextoAlinhamento(TEXTO_CENTRALIZADO);
    caixaFaseFinalizada->setEstiloVisual(uieVisualImagem);
    caixaFaseFinalizada->inicializar();

    caixaGameOver = new CaixaTexto();
    caixaGameOver->setPosicao(120,140);
    caixaGameOver->setDimensao(400,200);
    caixaGameOver->texto.setFonte("texto");
    caixaGameOver->texto.setChaveTexto("tela_gameover_%02d");
    caixaGameOver->setTextoAlinhamento(TEXTO_CENTRALIZADO);
    caixaGameOver->setEstiloVisual(uieVisual);
    caixaGameOver->inicializar();

    caixaZerado = new CaixaTexto();
    caixaZerado->setPosicao(120,140);
    caixaZerado->setDimensao(400,200);
    caixaZerado->texto.setFonte("texto");
    caixaZerado->texto.setChaveTexto("tela_zerado_%02d");
    caixaZerado->setTextoAlinhamento(TEXTO_CENTRALIZADO);
    caixaZerado->setEstiloVisual(uieVisual);
    caixaZerado->inicializar();

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

    caixaAjuda->executar();

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuCredito()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    caixaCredito->executar();

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))||
            (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuSobre()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    caixaSobre->executar();

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
    controle.desenhar();

    caixaFaseFinalizada->executar();

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setJogoFaseCarregar();
        }
    }
}
void Jogo::jogoGameOver()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    caixaGameOver->executar();

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenu();
        }
    }
}
void Jogo::jogoZerado()
{
    FrameLayerManager::getInstance()->getFrameLayer("background")->desenhar();

    caixaZerado->executar();

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
