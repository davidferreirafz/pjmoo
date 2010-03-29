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
    frameworkGBF->setTitle("Pancada","David de Almeida Ferreira");
    frameworkGBF->start(640,480,16,isFullScreen(),GBF::Kernel::FPS::FPS_30);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem","data//imagem//pancada_personagem.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("background","data//imagem//pancada_console.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("interface","data//imagem//pancada_interface.png");


    //carregando fontes
    frameworkGBF->writeSystem->loadFromFile("texto","data//fonte//texto.png");
    frameworkGBF->writeSystem->loadFromFile("menu","data//fonte//army.png");
    frameworkGBF->writeSystem->loadFromFile("kiloton16","data//fonte//kiloton_16.png");
    frameworkGBF->writeSystem->loadFromFile("kiloton24","data//fonte//kiloton_24.png");

//carregando audio - efeitos
//Configura volume dos efeitos

    //Idioma
    frameworkGBF->writeSystem->language->setFileName("msg.txt");
    frameworkGBF->writeSystem->language->autodetect();

//Layers
    GBF::Image::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Image::SpriteFactory("status");

    GBF::Image::Layer::FrameLayer * status = spriteFactory->createFrameLayer(0, 0,96,480);
    status->setFrame(544,0,96,480);
    status->setTiles(1,1);
    status->setPixelTile(96,480);
    status->iniciarRandomico(1);
    GBF::Image::Layer::LayerManager::getInstance()->add("status",status);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("background");
    GBF::Image::Layer::FrameLayer * console = spriteFactory->createFrameLayer(0, 0,64,480);
    console->setFrame(0,0,640,480);
    console->setTiles(10,1);
    console->setPixelTile(64,480);
    console->iniciarOrdenado(10);
    GBF::Image::Layer::LayerManager::getInstance()->add("background",console);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterface::Menu::UIMenuSimple();
    uiMenuPrincipal->center(640,120,UserInterface::HORIZONTAL);
    uiMenuPrincipal->setVerticalSpace(60);
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_1","menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_2","menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_3","menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_4","menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_5","menu"));

    UserInterface::Look::UIBackgroundImage *uiVisualImagem = new UserInterface::Look::UIBackgroundImage();
    uiVisualImagem->setBorderColor(255,0,0);
    uiVisualImagem->setImageType(UserInterface::Look::BACKGROUND_LINES);

    janelaCredito = new UserInterface::Window::UIWindowTitle();
    janelaCredito->setPoint(40,50);
    janelaCredito->setDimension(560,400);
    janelaCredito->text.setFont("texto");
    janelaCredito->text.setKeyText("tela_credito_%02d");
    janelaCredito->title.setFont("menu");
    janelaCredito->title.setKeyText("titulo_credito");
    janelaCredito->setBackground(uiVisualImagem->clone());
    janelaCredito->addButton(new UserInterface::Component::UIButton("menu","botao_enter",SDLK_RETURN));
    janelaCredito->inicializar();

    janelaSobre = new UserInterface::Window::UIWindowTitle();
    janelaSobre->setPoint(40,50);
    janelaSobre->setDimension(560,400);
    janelaSobre->text.setFont("texto");
    janelaSobre->text.setKeyText("tela_sobre_%02d");
    janelaSobre->title.setFont("menu");
    janelaSobre->title.setKeyText("titulo_sobre");
    janelaSobre->setBackground(uiVisualImagem->clone());
    janelaSobre->addButton(new UserInterface::Component::UIButton("menu","botao_enter",SDLK_RETURN));
    janelaSobre->inicializar();

    janelaFaseFinalizada = new UserInterface::Window::UIWindowDialog();
    janelaFaseFinalizada->setPoint(120,140);
    janelaFaseFinalizada->setDimension(400,200);
    janelaFaseFinalizada->text.setFont("texto");
    janelaFaseFinalizada->text.setKeyText("tela_fasefinalizada_%02d");
    janelaFaseFinalizada->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaFaseFinalizada->setBackground(uiVisualImagem->clone());
    janelaFaseFinalizada->inicializar();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPoint(120,140);
    janelaGameOver->setDimension(400,200);
    janelaGameOver->text.setFont("texto");
    janelaGameOver->text.setKeyText("tela_gameover_%02d");
    janelaGameOver->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaGameOver->setBackground(uiVisualImagem->clone());
    janelaGameOver->inicializar();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPoint(120,140);
    janelaZerado->setDimension(400,200);
    janelaZerado->text.setFont("texto");
    janelaZerado->text.setKeyText("tela_zerado_%02d");
    janelaZerado->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaZerado->setBackground(uiVisualImagem->clone());
    janelaZerado->inicializar();


    janelaAjuda = new UserInterface::Window::UIWindowTitle();
    janelaAjuda->setPoint(40,50);
    janelaAjuda->setDimension(560,400);
    janelaAjuda->text.setFont("texto");
    janelaAjuda->text.setKeyText("tela_ajuda_%02d");
    janelaAjuda->title.setFont("menu");
    janelaAjuda->title.setKeyText("titulo_ajuda");
    janelaAjuda->setBackground(uiVisualImagem->clone());
    janelaAjuda->addButton(new UserInterface::Component::UIButton("menu","botao_enter",SDLK_RETURN));
    janelaAjuda->inicializar();

    delete(uiVisualImagem);


    controle.carregar();

    //frameworkGBF->inputSystemCore->isInstance<Jogo>();
}
void Jogo::menuPrincipal()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    uiMenuPrincipal->execute();

    switch(uiMenuPrincipal->confirmSelection())
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
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaAjuda->execute();

    if (janelaAjuda->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuCredito()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaCredito->execute();

    if (janelaCredito->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuSobre()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaSobre->execute();

    if (janelaSobre->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
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
        if ((frameworkGBF->inputSystemCore->inputSystem->keyboard->isKey(SDLK_p))||
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

    janelaFaseFinalizada->execute();

    if (janelaFaseFinalizada->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setJogoFaseCarregar();
    }
}
void Jogo::jogoGameOver()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaGameOver->execute();

    if (janelaGameOver->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenu();
    }
}
void Jogo::jogoZerado()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaZerado->execute();

    if (janelaZerado->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
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
