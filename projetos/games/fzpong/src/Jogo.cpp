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
    GAT::GAT* jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->executar();
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what();
        //UtilLog::sistema("!!!!!!!!!!");
        //UtilLog::sistema("Exceção: %s",e.what());
        //UtilLog::sistema("!!!!!!!!!!");
    } catch (...) {
        std::cout << "Exception: ";
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
Jogo::~Jogo()
{
    delete(david);
    delete(controle);
    delete(janelaSobre);
    delete(janelaCredito);
    delete(janelaAjuda);
    delete(janelaZerado);
    delete(janelaGameOver);
}
//Inicializa os recursos utilizados no jogo.
//Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
void Jogo::inicializarRecursos()
{
//configurando modo de vídeo
    frameworkGBF->setTitulo("FZPong","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen(),GBF::Kernel::FPS::FPS_LIMITADO);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(false);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem","data//imagem//sprites.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("background","data//imagem//background.png");

    //carregando fontes
    frameworkGBF->writeSystem->carregar("menu","data//fonte//kiloton.png");
    frameworkGBF->writeSystem->carregar("texto","data//fonte//kiloton_18.png");
    frameworkGBF->writeSystem->carregar("kiloton10","data//fonte//kiloton_10.png");

//carregando audio - efeitos
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("ponto","data//som//ponto.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("ping","data//som//ping.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("iniciando","data//som//iniciando.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("gameover","data//som//gameover.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("raquete","data//som//raquete.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("vitoria","data//som//applause.ogg");
    frameworkGBF->soundSystemCore->soundSystem->musicManager->carregar("musica","data//som//404_nemo.ogg");
    frameworkGBF->soundSystemCore->soundSystem->musicManager->carregar("menu","data//som//apes_r-jonny_ho.ogg");

//Configura volume dos efeitos
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("ping",100);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("raquete",110);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("ponto",128);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("iniciando",60);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("gameover",80);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("vitoria",80);
    frameworkGBF->soundSystemCore->soundSystem->musicManager->setVolume("musica",20);
    frameworkGBF->soundSystemCore->soundSystem->musicManager->setVolume("menu",30);
//configura limites para som estereo
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setLimite(0,640);


    //Idioma
    frameworkGBF->writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF->writeSystem->idioma->detectarIdioma();

    GBF::Imagem::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Imagem::SpriteFactory("background");

    GBF::Imagem::Layer::FrameLayer * background = spriteFactory->criarFrameLayer(0, 0,640,480);
    background->setFrame(0,0,640,480);
    background->setTiles(1,1);
    background->setPixelTile(640,480);
    background->iniciarRandomico(1);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("background",background);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    david=spriteFactory->criarSpriteItem(30,21,90,68,1,1);
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

    UserInterface::Visual::UIVisualSolido *uiVisualImagem = new UserInterface::Visual::UIVisualSolido();
    uiVisualImagem->setCorBorda(255,255,0);
    uiVisualImagem->setCorFundo(0,0,0);

    janelaAjuda = new UserInterface::Window::UIWindowTitulo();
    janelaAjuda->setPosicao(20,40);
    janelaAjuda->setDimensao(598,400);
    janelaAjuda->texto.setFonte("texto");
    janelaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    janelaAjuda->titulo.setFonte("menu");
    janelaAjuda->titulo.setChaveTexto("titulo_ajuda");
    janelaAjuda->setVisual(uiVisualImagem->clone());
    janelaAjuda->adicionarBotao(new UserInterface::Componente::UIBotao("kiloton10","botao_enter",SDLK_RETURN));
    janelaAjuda->inicializar();

    janelaCredito = new UserInterface::Window::UIWindowTitulo();
    janelaCredito->setPosicao(20,40);
    janelaCredito->setDimensao(598,400);
    janelaCredito->texto.setFonte("texto");
    janelaCredito->texto.setChaveTexto("tela_credito_%02d");
    janelaCredito->titulo.setFonte("menu");
    janelaCredito->titulo.setChaveTexto("titulo_credito");
    janelaCredito->setVisual(uiVisualImagem->clone());
    janelaCredito->adicionarBotao(new UserInterface::Componente::UIBotao("kiloton10","botao_enter",SDLK_RETURN));
    janelaCredito->inicializar();

    janelaSobre = new UserInterface::Window::UIWindowTitulo();
    janelaSobre->setPosicao(20,40);
    janelaSobre->setDimensao(598,400);
    janelaSobre->texto.setFonte("texto");
    janelaSobre->texto.setChaveTexto("tela_sobre_%02d");
    janelaSobre->titulo.setFonte("menu");
    janelaSobre->titulo.setChaveTexto("titulo_sobre");
    janelaSobre->setVisual(uiVisualImagem->clone());
    janelaSobre->adicionarBotao(new UserInterface::Componente::UIBotao("kiloton10","botao_enter",SDLK_RETURN));
    janelaSobre->inicializar();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPosicao(120,140);
    janelaGameOver->setDimensao(400,200);
    janelaGameOver->texto.setFonte("texto");
    janelaGameOver->texto.setChaveTexto("tela_gameover_%02d");
    janelaGameOver->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaGameOver->setVisual(uiVisualImagem->clone());
    janelaGameOver->adicionarBotao(new UserInterface::Componente::UIBotao("kiloton10","botao_enter",SDLK_RETURN));
    janelaGameOver->inicializar();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPosicao(120,140);
    janelaZerado->setDimensao(400,200);
    janelaZerado->texto.setFonte("texto");
    janelaZerado->texto.setChaveTexto("tela_zerado_%02d");
    janelaZerado->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaZerado->setVisual(uiVisualImagem->clone());
    janelaZerado->adicionarBotao(new UserInterface::Componente::UIBotao("kiloton10","botao_enter",SDLK_RETURN));
    janelaZerado->inicializar();

    delete(uiVisualImagem);

    controle = new Controle();
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

    david->desenhar(280,280);

    if (janelaCredito->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    } else {
        if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_t)){
            controle->ativarDemo(true);
            setJogo();
        } else if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_f)){
            controle->ativarDemo(false);
        }
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
    controle->iniciar();
    setJogoFaseCarregar();
}
void Jogo::jogoExecutando()
{
    if ((controle->isGameOver())||(controle->isSetFinalizado())){
        setJogoFaseFinalizada();
    } else {
        controle->executar(frameworkGBF->inputSystemCore->inputSystem);
    }
}
void Jogo::jogoPause()
{
    setMenu();
}
void Jogo::jogoFaseCarregar()
{
    controle->display();
    frameworkGBF->writeSystem->escreverLocalizado("menu" ,100,80,"fase_carregar");

    if (isTempoEspera()){
        controle->iniciarSet();
        setJogoExecutando();
    }
}
void Jogo::jogoFaseFinalizada()
{
    setJogoFaseCarregar();
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
    bool continua = true;

    if (controle->isFinalizado()){
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("vitoria");
        setJogoZerado();
        continua = false;
    } else if (controle->isGameOver()){
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("gameover");
        setJogoGameOver();
        continua = false;
    } else {
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("iniciando");
        controle->prepararSet();
    }
    return continua;
}
void Jogo::gatilhoMenuPrincipal()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("menu");
}
bool Jogo::desenharBotaoEnter()
{
    bool desenhe = isTempoEspera();

    if (desenhe){
        frameworkGBF->writeSystem->escreverLocalizado("menu",20,420,"botao_enter");
    }

    return desenhe;
}
