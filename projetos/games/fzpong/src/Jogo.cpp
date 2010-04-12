/*
 *   FZPong <Game - Pong Clone>                                            *
 *   Copyright (C) 2007-2010 by David Ferreira - FZ                        *
 *   davidferreira.fz@gmail.com - http://portal.dukitan.com/fzpong         *
 ***************************************************************************
 *   Este programa é software livre; você pode redistribuí-lo e/ou         *
 *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
 *   publicada pela Free Software Foundation; tanto a versão 2 da          *
 *   Licença como (a seu critério) qualquer versão mais nova.              *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "Jogo.h"

int main(int argc, char * argv[])
{
    GAT::GAT* jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->execute();
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
void Jogo::loadResources()
{
//configurando modo de vídeo
    frameworkGBF->setTitle("FZPong","David de Almeida Ferreira");
    frameworkGBF->start(640,480,16,isFullScreen(),GBF::Kernel::FPS::FPS_30);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(false);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem","data//imagem//sprites.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("background","data//imagem//background.png");

    //carregando fontes
    frameworkGBF->writeSystem->loadFromFile("menu","data//fonte//kiloton.png");
    frameworkGBF->writeSystem->loadFromFile("texto","data//fonte//kiloton_18.png");
    frameworkGBF->writeSystem->loadFromFile("kiloton10","data//fonte//kiloton_10.png");

//carregando audio - efeitos
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("ponto","data//som//ponto.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("ping","data//som//ping.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("iniciando","data//som//iniciando.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("gameover","data//som//gameover.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("raquete","data//som//raquete.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->loadFromFile("vitoria","data//som//applause.ogg");
    frameworkGBF->soundSystemCore->soundSystem->musicManager->loadFromFile("musica","data//som//404_nemo.ogg");
    frameworkGBF->soundSystemCore->soundSystem->musicManager->loadFromFile("menu","data//som//apes_r-jonny_ho.ogg");

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
    frameworkGBF->writeSystem->language->setFileName("msg.txt");
    frameworkGBF->writeSystem->language->autodetect();

    GBF::Image::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Image::SpriteFactory("background");

    GBF::Image::Layer::FrameLayer * background = spriteFactory->createFrameLayer(0, 0,640,480);
    background->setFrame(0,0,640,480);
    background->setTiles(1,1);
    background->setPixelTile(640,480);
    background->iniciarRandomico(1);
    GBF::Image::Layer::LayerManager::getInstance()->add("background",background);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem");
    david=spriteFactory->createSpriteItem(30,21,90,68,1,1);
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

    UserInterface::Look::UIBackgroundColor *uiVisualImagem = new UserInterface::Look::UIBackgroundColor();
    uiVisualImagem->setBorderColor(255,255,0);
    uiVisualImagem->setColor(0,0,0);

    janelaAjuda = new UserInterface::Window::UIWindowTitle();
    janelaAjuda->setPoint(20,40);
    janelaAjuda->setDimension(598,400);
    janelaAjuda->text.setFont("texto");
    janelaAjuda->text.setKeyText("tela_ajuda_%02d");
    janelaAjuda->title.setFont("menu");
    janelaAjuda->title.setKeyText("titulo_ajuda");
    janelaAjuda->setBackground(uiVisualImagem->clone());
    janelaAjuda->addButton(new UserInterface::Component::UIButton("kiloton10","botao_enter",SDLK_RETURN));
    janelaAjuda->initialize();

    janelaCredito = new UserInterface::Window::UIWindowTitle();
    janelaCredito->setPoint(20,40);
    janelaCredito->setDimension(598,400);
    janelaCredito->text.setFont("texto");
    janelaCredito->text.setKeyText("tela_credito_%02d");
    janelaCredito->title.setFont("menu");
    janelaCredito->title.setKeyText("titulo_credito");
    janelaCredito->setBackground(uiVisualImagem->clone());
    janelaCredito->addButton(new UserInterface::Component::UIButton("kiloton10","botao_enter",SDLK_RETURN));
    janelaCredito->initialize();

    janelaSobre = new UserInterface::Window::UIWindowTitle();
    janelaSobre->setPoint(20,40);
    janelaSobre->setDimension(598,400);
    janelaSobre->text.setFont("texto");
    janelaSobre->text.setKeyText("tela_sobre_%02d");
    janelaSobre->title.setFont("menu");
    janelaSobre->title.setKeyText("titulo_sobre");
    janelaSobre->setBackground(uiVisualImagem->clone());
    janelaSobre->addButton(new UserInterface::Component::UIButton("kiloton10","botao_enter",SDLK_RETURN));
    janelaSobre->initialize();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPoint(120,140);
    janelaGameOver->setDimension(400,200);
    janelaGameOver->text.setFont("texto");
    janelaGameOver->text.setKeyText("tela_gameover_%02d");
    janelaGameOver->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaGameOver->setBackground(uiVisualImagem->clone());
    janelaGameOver->addButton(new UserInterface::Component::UIButton("kiloton10","botao_enter",SDLK_RETURN));
    janelaGameOver->initialize();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPoint(120,140);
    janelaZerado->setDimension(400,200);
    janelaZerado->text.setFont("texto");
    janelaZerado->text.setKeyText("tela_zerado_%02d");
    janelaZerado->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaZerado->setBackground(uiVisualImagem->clone());
    janelaZerado->addButton(new UserInterface::Component::UIButton("kiloton10","botao_enter",SDLK_RETURN));
    janelaZerado->initialize();

    delete(uiVisualImagem);

    controle = new Controle();
}
void Jogo::screenMain()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    uiMenuPrincipal->execute();


    switch(uiMenuPrincipal->confirmSelection())
    {
        case 0:
                setMenuAbout();
            break;
        case 1:
                setGame();
            break;
        case 2:
                setMenuCredit();
            break;
        case 3:
                setMenuHelp();
            break;
        case 4:
                setQuit();
            break;
    }
}
void Jogo::screenHelp()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaAjuda->execute();

    if (janelaAjuda->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuMain();
    }
}
void Jogo::screenCredit()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaCredito->execute();

    david->draw(280,280);

    if (janelaCredito->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuMain();
    } else {
        if (frameworkGBF->inputSystemCore->inputSystem->keyboard->isKey(SDLK_t)){
            controle->ativarDemo(true);
            setGame();
        } else if (frameworkGBF->inputSystemCore->inputSystem->keyboard->isKey(SDLK_f)){
            controle->ativarDemo(false);
        }
    }
}
void Jogo::screenAbout()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaSobre->execute();

    frameworkGBF->writeSystem->write(26,410,"Build: %s (%s)",AutoVersion::FULLVERSION_STRING,AutoVersion::STATUS);
    frameworkGBF->writeSystem->write(26,424,"SVN Revision: %s SVN Date: %s",AutoVersion::SVN_REVISION,AutoVersion::SVN_DATE);

    if (janelaSobre->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuMain();
    }
}
void Jogo::actionNewGame()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("musica");
    controle->iniciar();
    setLoadStage();
}
void Jogo::actionOnGame()
{
    if ((controle->isGameOver())||(controle->isSetFinalizado())){
        setFinishStage();
    } else {
        controle->executar(frameworkGBF->inputSystemCore->inputSystem);
    }
}
void Jogo::screenGamePause()
{
    setMenu();
}
void Jogo::screenLoadStage()
{
    controle->display();
    frameworkGBF->writeSystem->writeKeyText("menu" ,100,80,"fase_carregar");

    if (isFinish()){
        controle->iniciarSet();
        setOnGame();
    }
}
void Jogo::screenFinishStage()
{
    setLoadStage();
}
void Jogo::screenGameOver()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaGameOver->execute();

    if (janelaGameOver->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenu();
    }
}
void Jogo::screenGameFinish()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaZerado->execute();

    if (janelaZerado->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenu();
    }
}
bool Jogo::triggerLoadStage()
{
    bool continua = true;

    if (controle->isFinalizado()){
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("vitoria");
        setGameFinish();
        continua = false;
    } else if (controle->isGameOver()){
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("gameover");
        setGameOver();
        continua = false;
    } else {
        frameworkGBF->soundSystemCore->soundSystem->fxManager->play("iniciando");
        controle->prepararSet();
    }
    return continua;
}
void Jogo::triggerMain()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("menu");
}
bool Jogo::desenharBotaoEnter()
{
    bool desenhe = isFinish();

    if (desenhe){
        frameworkGBF->writeSystem->writeKeyText("menu",20,420,"botao_enter");
    }

    return desenhe;
}
