/*
 *   Gameta <Game - Demo Tech>                                             *
 *   Copyright (C) 2007-2010 by David Ferreira - FZ                        *
 *   davidferreira.fz@gmail.com - http://portal.dukitan.com/fzpong         *
 ***************************************************************************
 *   Este programa é software livre; você pode redistribuí-lo e/ou         *
 *   modificá-lo sob os termos da Licençaa Pública Geral GNU, conforme     *
 *   publicada pela Free Software Foundation; tanto a versão 2 da          *
 *   Licençaa como (a seu critério) qualquer versão mais nova.             *
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
    jogo = new Jogo(argc, argv);

    try {
        jogo->execute();
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what();
    } catch (...) {
        std::cout << "Exception: ";
    }

    delete(jogo);

    return 0;
}
//Construtor
Jogo::Jogo(int argc, char * argv[]): GAT(argc, argv)
{
}
//Destrutor
Jogo::~Jogo()
{
    delete(controle);
    delete(janelaSobre);
    delete(janelaCredito);
    delete(janelaAjuda);
    delete(janelaZerado);
    delete(janelaGameOver);
}

void Jogo::loadResources()
{
    //configurando modo de vídeo
    frameworkGBF->setTitle("Sala Treino", "Gameta & DukItan");
    frameworkGBF->start(304, 224, 16, false, GBF::Kernel::FPS::FPS_30);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(false);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("background", "//data//imagem//background.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("foreground", "//data//imagem//foreground.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_parado",  "//data//imagem//personagem_parado.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_andando", "//data//imagem//personagem_andando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_recuando", "//data//imagem//personagem_recuando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_correndo", "//data//imagem//personagem_correndo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_morrendo", "//data//imagem//personagem_morrendo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_pulando", "//data//imagem//personagem_pulando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_caindo",  "//data//imagem//personagem_caindo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("personagem_impulsionando", "//data//imagem//personagem_impulsionando.png");

    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("bala", "//data//imagem//bala.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("fumaca", "//data//imagem//fumaca.png");

    //carregando fontes
    frameworkGBF->writeSystem->loadFromFile("menu", "data//fonte//Impact.png");
    frameworkGBF->writeSystem->loadFromFile("controle", "data//fonte//bitstream.png");


//carregando audio - efeitos
    //frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("vitoria","data//som//applause.ogg");
    //frameworkGBF->soundSystemCore->soundSystem->musicManager->carregar("musica","data//som//404_nemo.ogg");

//Configura volume dos efeitos
//    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("vitoria",80);
//    frameworkGBF->soundSystemCore->soundSystem->musicManager->setVolume("musica",20);
//configura limites para som estereo
//    frameworkGBF->soundSystemCore->soundSystem->fxManager->setLimite(0,640);


    //Idioma
    frameworkGBF->writeSystem->language->setFileName("msg.txt");
    frameworkGBF->writeSystem->language->autodetect();

    GBF::Image::SpriteFactory * spriteFactory = NULL;
    spriteFactory = new GBF::Image::SpriteFactory("background");

    GBF::Image::Layer::FrameLayer * background = spriteFactory->createFrameLayer(0, 0, 304, 224);
    background->setFrame(0, 0, 304, 224);
    background->setTiles(1, 1);
    background->setPixelTile(304, 224);
    background->iniciarCom(0);
    GBF::Image::Layer::LayerManager::getInstance()->add("background", background);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("foreground");
    GBF::Image::Layer::FrameLayer * foreground = spriteFactory->createFrameLayer(0, 0, 304, 224);
    foreground->setFrame(0, 0, 304, 224);
    foreground->setTiles(1, 1);
    foreground->setPixelTile(304, 224);
    foreground->iniciarCom(0);
    GBF::Image::Layer::LayerManager::getInstance()->add("foreground", foreground);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterface::Menu::UIMenuSolid();
    uiMenuPrincipal->setBorderColor(255, 255, 0);
    uiMenuPrincipal->setBackgroundColor(0, 0, 0);
    uiMenuPrincipal->center(304, 224, UserInterface::CENTRO);
    uiMenuPrincipal->setVerticalSpace(20);
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_1", "menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_2", "menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_3", "menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_4", "menu"));
    uiMenuPrincipal->add(new UserInterface::Menu::UIItemText("menu_5", "menu"));

    UserInterface::Look::UIBackgroundColor *uiVisualImagem = new UserInterface::Look::UIBackgroundColor();
    uiVisualImagem->setBorderColor(255, 255, 0);
    uiVisualImagem->setColor(0, 0, 0);

    janelaAjuda = new UserInterface::Window::UIWindowTitle();
    janelaAjuda->setPoint(10, 16);
    janelaAjuda->setDimension(280, 200);
    janelaAjuda->text.setFont("texto");
    janelaAjuda->text.setKeyText("tela_ajuda_%02d");
    janelaAjuda->title.setFont("menu");
    janelaAjuda->title.setKeyText("titulo_ajuda");
    janelaAjuda->setBackground(uiVisualImagem->clone());
    janelaAjuda->addButton(new UserInterface::Component::UIButton("controle", "botao_enter", SDLK_RETURN));
    janelaAjuda->initialize();

    janelaCredito = new UserInterface::Window::UIWindowTitle();
    janelaCredito->setPoint(10, 16);
    janelaCredito->setDimension(280, 200);
    janelaCredito->text.setFont("texto");
    janelaCredito->text.setKeyText("tela_credito_%02d");
    janelaCredito->title.setFont("menu");
    janelaCredito->title.setKeyText("titulo_credito");
    janelaCredito->setBackground(uiVisualImagem->clone());
    janelaCredito->addButton(new UserInterface::Component::UIButton("controle", "botao_enter", SDLK_RETURN));
    janelaCredito->initialize();

    janelaSobre = new UserInterface::Window::UIWindowTitle();
    janelaSobre->setPoint(10, 16);
    janelaSobre->setDimension(280, 200);
    janelaSobre->text.setFont("texto");
    janelaSobre->text.setKeyText("tela_sobre_%02d");
    janelaSobre->text.setAlignment(UserInterface::Text::TEXT_NORMAL);
    janelaSobre->title.setFont("menu");
    janelaSobre->title.setKeyText("titulo_sobre");
    janelaSobre->setBackground(uiVisualImagem->clone());
    janelaSobre->addButton(new UserInterface::Component::UIButton("controle", "botao_enter", SDLK_RETURN));
    janelaSobre->initialize();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPoint(50, 60);
    janelaGameOver->setDimension(200, 100);
    janelaGameOver->text.setFont("texto");
    janelaGameOver->text.setKeyText("tela_gameover_%02d");
    // janelaGameOver->text.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaGameOver->setBackground(uiVisualImagem->clone());
    janelaGameOver->addButton(new UserInterface::Component::UIButton("controle", "botao_enter", SDLK_RETURN));
    janelaGameOver->initialize();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPoint(120, 140);
    janelaZerado->setDimension(400, 200);
    janelaZerado->text.setFont("texto");
    janelaZerado->text.setKeyText("tela_zerado_%02d");
    janelaZerado->text.setAlignment(UserInterface::Text::TEXT_CENTRAL);
    janelaZerado->setBackground(uiVisualImagem->clone());
    janelaZerado->addButton(new UserInterface::Component::UIButton("controle", "botao_enter", SDLK_RETURN));
    janelaZerado->initialize();

    delete(uiVisualImagem);

    controle = new Controle();
}

void Jogo::screenMain()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    uiMenuPrincipal->execute();


    switch (uiMenuPrincipal->confirmSelection())
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

    if (janelaCredito->isAction(UserInterface::Window::UIWindowDialog::BUTTON_OK)){
        setMenuMain();
    }
}

void Jogo::screenAbout()
{
    GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background")->draw();

    janelaSobre->execute();

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
    if ((controle->isGameOver())){
        setGameOver();
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
    //  controle->display();
    frameworkGBF->writeSystem->writeKeyText("menu" , 10, 80, "fase_carregar");

    if (isFinish()){
        //    controle->iniciarSet();
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

    /* if (controle->isFinalizado()){
         frameworkGBF->soundSystemCore->soundSystem->fxManager->play("vitoria");
         setJogoZerado();
         continua = false;
     } else if (controle->isGameOver()){
         frameworkGBF->soundSystemCore->soundSystem->fxManager->play("gameover");
         setJogoGameOver();
         continua = false;
     } else {
         frameworkGBF->soundSystemCore->soundSystem->fxManager->play("iniciando");
        // controle->prepararSet();
     }*/
    return continua;
}

void Jogo::triggerMain()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("menu");
}

