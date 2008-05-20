//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da
//    Licença como (a seu critério) qualquer versão mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "Jogo.h"

int main(int argc, char * argv[])
{
    GAT::GAT * jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->executar();
    } catch (std::exception& e) {
        //UtilLog::sistema("!!!!!!!!!!");
        //UtilLog::sistema("Exceção: %s",e.what());
        //UtilLog::sistema("!!!!!!!!!!");
    } catch (...) {
        //UtilLog::sistema("!!!!!!!!!!");
        //UtilLog::sistema("Exceção Desconhecida");
        //UtilLog::sistema("!!!!!!!!!!");
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

//Destrutor
Jogo::~Jogo(){
    delete(janelaAjuda);
    delete(janelaCredito);
    delete(janelaSobre);
    delete(janelaGameOver);
    delete(janelaFaseFinalizada);
    delete(janelaZerado);
}

//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..

//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
void Jogo::inicializarRecursos()
{
//configurando modo de vídeo
    frameworkGBF->setTitulo("Pancada","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen());
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem","data//imagem//pancada_personagem.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("background","data//imagem//pancada_console.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("interface","data//imagem//pancada_interface.png");


    //carregando fontes
    frameworkGBF->writeSystem->carregar("texto",frameworkGBF->getPath()+"data//fonte//texto.png");
    frameworkGBF->writeSystem->carregar("menu",frameworkGBF->getPath()+"data//fonte//army.png");
    frameworkGBF->writeSystem->carregar("kiloton16",frameworkGBF->getPath()+"data//fonte//kiloton_16.png");
    frameworkGBF->writeSystem->carregar("kiloton24",frameworkGBF->getPath()+"data//fonte//kiloton_24.png");

//carregando audio - efeitos
//Configura volume dos efeitos

    //Idioma
    frameworkGBF->writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF->writeSystem->idioma->detectarIdioma();

//Layers
    GBF::Imagem::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Imagem::SpriteFactory("status");

    GBF::Imagem::Layer::FrameLayer * status = spriteFactory->criarFrameLayer(0, 0,96,480);
    status->setFrame(544,0,96,480);
    status->setTiles(1,1);
    status->setPixelTile(96,480);
    status->iniciarRandomico(1);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("status",status);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("background");
    GBF::Imagem::Layer::FrameLayer * console = spriteFactory->criarFrameLayer(0, 0,64,480);
    console->setFrame(0,0,640,480);
    console->setTiles(10,1);
    console->setPixelTile(64,480);
    console->iniciarOrdenado(10);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("background",console);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterface::Menu::UIMenuTransparente();
    uiMenuPrincipal->centralizarTela(640,120,UserInterface::HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(60);
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_1","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_2","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_3","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_4","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_5","menu"));

    UserInterface::Visual::UIVisualImagem *uiVisualImagem = new UserInterface::Visual::UIVisualImagem();
    uiVisualImagem->setCorBorda(255,0,0);
    uiVisualImagem->setTipoBackground(UserInterface::Visual::BACKGROUND_LINES);

    janelaCredito = new UserInterface::Window::UIWindowTitulo();
    janelaCredito->setPosicao(40,50);
    janelaCredito->setDimensao(560,400);
    janelaCredito->texto.setFonte("texto");
    janelaCredito->texto.setChaveTexto("tela_credito_%02d");
    janelaCredito->titulo.setFonte("menu");
    janelaCredito->titulo.setChaveTexto("titulo_credito");
    janelaCredito->setVisual(uiVisualImagem->clone());
    janelaCredito->adicionarBotao(new UserInterface::Componente::UIBotao("menu","botao_enter",SDLK_RETURN));
    janelaCredito->inicializar();

    janelaSobre = new UserInterface::Window::UIWindowTitulo();
    janelaSobre->setPosicao(40,50);
    janelaSobre->setDimensao(560,400);
    janelaSobre->texto.setFonte("texto");
    janelaSobre->texto.setChaveTexto("tela_sobre_%02d");
    janelaSobre->titulo.setFonte("menu");
    janelaSobre->titulo.setChaveTexto("titulo_sobre");
    janelaSobre->setVisual(uiVisualImagem->clone());
    janelaSobre->adicionarBotao(new UserInterface::Componente::UIBotao("menu","botao_enter",SDLK_RETURN));
    janelaSobre->inicializar();

    janelaFaseFinalizada = new UserInterface::Window::UIWindowDialog();
    janelaFaseFinalizada->setPosicao(120,140);
    janelaFaseFinalizada->setDimensao(400,200);
    janelaFaseFinalizada->texto.setFonte("texto");
    janelaFaseFinalizada->texto.setChaveTexto("tela_fasefinalizada_%02d");
    janelaFaseFinalizada->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaFaseFinalizada->setVisual(uiVisualImagem->clone());
    janelaFaseFinalizada->inicializar();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPosicao(120,140);
    janelaGameOver->setDimensao(400,200);
    janelaGameOver->texto.setFonte("texto");
    janelaGameOver->texto.setChaveTexto("tela_gameover_%02d");
    janelaGameOver->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaGameOver->setVisual(uiVisualImagem->clone());
    janelaGameOver->inicializar();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPosicao(120,140);
    janelaZerado->setDimensao(400,200);
    janelaZerado->texto.setFonte("texto");
    janelaZerado->texto.setChaveTexto("tela_zerado_%02d");
    janelaZerado->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaZerado->setVisual(uiVisualImagem->clone());
    janelaZerado->inicializar();


    janelaAjuda = new UserInterface::Window::UIWindowTitulo();
    janelaAjuda->setPosicao(40,50);
    janelaAjuda->setDimensao(560,400);
    janelaAjuda->texto.setFonte("texto");
    janelaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    janelaAjuda->titulo.setFonte("menu");
    janelaAjuda->titulo.setChaveTexto("titulo_ajuda");
    janelaAjuda->setVisual(uiVisualImagem->clone());
    janelaAjuda->adicionarBotao(new UserInterface::Componente::UIBotao("menu","botao_enter",SDLK_RETURN));
    janelaAjuda->inicializar();

    delete(uiVisualImagem);


    controle.carregar();

    //frameworkGBF->inputSystemCore->isInstance<Jogo>();
}
void Jogo::menuPrincipal()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

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
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaAjuda->executar();

    if (janelaAjuda->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuCredito()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaCredito->executar();

    if (janelaCredito->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuSobre()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaSobre->executar();

    if (janelaSobre->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}
void Jogo::jogoNovo()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("musica");
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
        controle.executar(frameworkGBF->inputSystemCore->inputSystem);
        if ((frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_p))||
            (frameworkGBF->inputSystemCore->inputSystem->joystick->isButtonC())){
                setJogoPause();
        }
        #ifdef DEBUG
        //Codigo utilizado para avança uma fase
        else if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_n)){
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

    if (janelaFaseFinalizada->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setJogoFaseCarregar();
    }
}
void Jogo::jogoGameOver()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaGameOver->executar();

    if (janelaGameOver->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenu();
    }
}
void Jogo::jogoZerado()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background")->desenhar();

    janelaZerado->executar();

    if (janelaZerado->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
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
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("menu");
}
