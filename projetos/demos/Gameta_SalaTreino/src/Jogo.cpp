///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2009 by David Ferreira - FZ                             *
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
    } catch (...) {
        std::cout << "Exception: ";
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
    Mix_HookMusic(NULL, NULL);
    SMPEG_stop(mpeg);
    SMPEG_delete(mpeg);

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
    frameworkGBF->setTitulo("Sala Treino","Gameta & DukItan");
    frameworkGBF->iniciar(304,224,16,false,GBF::Kernel::FPS::FPS_LIMITADO);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(false);

    //carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("background","//data//imagem//background.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("foreground","//data//imagem//foreground.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_parado",  "//data//imagem//personagem_parado.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_andando", "//data//imagem//personagem_andando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_recuando","//data//imagem//personagem_recuando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_correndo","//data//imagem//personagem_correndo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_morrendo","//data//imagem//personagem_morrendo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_pulando", "//data//imagem//personagem_pulando.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_caindo",  "//data//imagem//personagem_caindo.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_impulsionando","//data//imagem//personagem_impulsionando.png");

    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("bala","//data//imagem//bala.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("fumaca","//data//imagem//fumaca.png");

    //carregando fontes
    frameworkGBF->writeSystem->carregar("menu","data//fonte//Impact.png");
    frameworkGBF->writeSystem->carregar("controle","data//fonte//bitstream.png");


//carregando audio - efeitos
    //frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("vitoria","data//som//applause.ogg");
    //frameworkGBF->soundSystemCore->soundSystem->musicManager->carregar("musica","data//som//404_nemo.ogg");

//Configura volume dos efeitos
//    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("vitoria",80);
//    frameworkGBF->soundSystemCore->soundSystem->musicManager->setVolume("musica",20);
//configura limites para som estereo
//    frameworkGBF->soundSystemCore->soundSystem->fxManager->setLimite(0,640);


    //Idioma
    frameworkGBF->writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF->writeSystem->idioma->detectarIdioma();

    GBF::Imagem::SpriteFactory * spriteFactory = NULL;
    spriteFactory = new GBF::Imagem::SpriteFactory("background");

    GBF::Imagem::Layer::FrameLayer * background = spriteFactory->criarFrameLayer(0, 0,304,224);
    background->setFrame(0,0,304,224);
    background->setTiles(1,1);
    background->setPixelTile(304,224);
    background->iniciarCom(0);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("background",background);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("foreground");
    GBF::Imagem::Layer::FrameLayer * foreground = spriteFactory->criarFrameLayer(0, 0,304,224);
    foreground->setFrame(0,0,304,224);
    foreground->setTiles(1,1);
    foreground->setPixelTile(304,224);
    foreground->iniciarCom(0);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("foreground",foreground);
    delete(spriteFactory);

    //Menu
    uiMenuPrincipal = new UserInterface::Menu::UIMenu();
    uiMenuPrincipal->setCorBorda(255,255,0);
    uiMenuPrincipal->setCorFundo(0,0,0);
    uiMenuPrincipal->centralizarTela(304,224,UserInterface::CENTRO);
    uiMenuPrincipal->setEspacoVertical(20);
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_1","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_2","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_3","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_4","menu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_5","menu"));

    UserInterface::Visual::UIVisualSolido *uiVisualImagem = new UserInterface::Visual::UIVisualSolido();
    uiVisualImagem->setCorBorda(255,255,0);
    uiVisualImagem->setCorFundo(0,0,0);

    janelaAjuda = new UserInterface::Window::UIWindowTitulo();
    janelaAjuda->setPosicao(10,16);
    janelaAjuda->setDimensao(280,200);
    janelaAjuda->texto.setFonte("texto");
    janelaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    janelaAjuda->titulo.setFonte("menu");
    janelaAjuda->titulo.setChaveTexto("titulo_ajuda");
    janelaAjuda->setVisual(uiVisualImagem->clone());
    janelaAjuda->adicionarBotao(new UserInterface::Componente::UIBotao("controle","botao_enter",SDLK_RETURN));
    janelaAjuda->inicializar();

    janelaCredito = new UserInterface::Window::UIWindowTitulo();
    janelaCredito->setPosicao(10,16);
    janelaCredito->setDimensao(280,200);
    janelaCredito->texto.setFonte("texto");
    janelaCredito->texto.setChaveTexto("tela_credito_%02d");
    janelaCredito->titulo.setFonte("menu");
    janelaCredito->titulo.setChaveTexto("titulo_credito");
    janelaCredito->setVisual(uiVisualImagem->clone());
    janelaCredito->adicionarBotao(new UserInterface::Componente::UIBotao("controle","botao_enter",SDLK_RETURN));
    janelaCredito->inicializar();

    janelaSobre = new UserInterface::Window::UIWindowTitulo();
    janelaSobre->setPosicao(10,16);
    janelaSobre->setDimensao(280,200);
    janelaSobre->texto.setFonte("texto");
    janelaSobre->texto.setChaveTexto("tela_sobre_%02d");
    janelaSobre->texto.setAlinhamento(UserInterface::Texto::TEXTO_NORMAL);
    janelaSobre->titulo.setFonte("menu");
    janelaSobre->titulo.setChaveTexto("titulo_sobre");
    janelaSobre->setVisual(uiVisualImagem->clone());
    janelaSobre->adicionarBotao(new UserInterface::Componente::UIBotao("controle","botao_enter",SDLK_RETURN));
    janelaSobre->inicializar();

    janelaGameOver = new UserInterface::Window::UIWindowDialog();
    janelaGameOver->setPosicao(50,60);
    janelaGameOver->setDimensao(200,100);
    janelaGameOver->texto.setFonte("texto");
    janelaGameOver->texto.setChaveTexto("tela_gameover_%02d");
   // janelaGameOver->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaGameOver->setVisual(uiVisualImagem->clone());
    janelaGameOver->adicionarBotao(new UserInterface::Componente::UIBotao("controle","botao_enter",SDLK_RETURN));
    janelaGameOver->inicializar();

    janelaZerado = new UserInterface::Window::UIWindowDialog();
    janelaZerado->setPosicao(120,140);
    janelaZerado->setDimensao(400,200);
    janelaZerado->texto.setFonte("texto");
    janelaZerado->texto.setChaveTexto("tela_zerado_%02d");
    janelaZerado->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janelaZerado->setVisual(uiVisualImagem->clone());
    janelaZerado->adicionarBotao(new UserInterface::Componente::UIBotao("controle","botao_enter",SDLK_RETURN));
    janelaZerado->inicializar();

    delete(uiVisualImagem);

    controle = new Controle();


////
    std::cout << "Carregando MPEG" <<std::endl;

    if ((mpeg = SMPEG_new ("/home/desenvolvimento/pjmoo/projetos/demos/Gameta_SalaTreino/bin/dukitan.mpg", NULL, 1)) != NULL)
    {
        std::cout << "achou" << std::endl;

        SDL_Surface * sTemp = SDL_CreateRGBSurface(SDL_HWSURFACE, 304, 224, 16, 0, 0, 0, 0);

        sVideo = SDL_DisplayFormat(sTemp);
        pScreen = frameworkGBF->graphicSystemCore->gsScreen->getScreen();


        SMPEG_setdisplay(mpeg, sVideo, NULL,  NULL);
        SMPEG_enablevideo(mpeg, 1);

        SDL_AudioSpec audiofmt;
        Uint16 format;
        int freq, channels;
        Mix_QuerySpec(&freq, &format, &channels);
        audiofmt.format = format;
        audiofmt.freq = freq;
        audiofmt.channels = channels;
        SMPEG_actualSpec(mpeg, &audiofmt);
        Mix_HookMusic(SMPEG_playAudioSDL, mpeg);
        SMPEG_enableaudio(mpeg, 1);
        SMPEG_setvolume(mpeg,100);
        //SMPEG_setdisplayregion(mpeg, 0, 0, 200,200 );

        //SMPEG_play(mpeg);
       // SMPEG_getinfo(mpeg,&videoInfo);
       // SDL_Delay(2000000);
        delete(sTemp);
    } else{
        std::cout << "nao achou" << std::endl;
    }


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
    controle->iniciar();
    setJogoFaseCarregar();
}
void Jogo::jogoExecutando()
{
    if ((controle->isGameOver())){
      setJogoGameOver();
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
  //  controle->display();
    frameworkGBF->writeSystem->escreverLocalizado("menu" ,10,80,"fase_carregar");

    if (isTempoEspera()){
    //    controle->iniciarSet();
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
void Jogo::apresentacao()
{
    static int frame = 0;

    SMPEG_renderFrame(mpeg,(frame++));
    SMPEG_getinfo(mpeg,&videoInfo);

    //std::cout << " mpeg: "<< mpeg. <<std::endl;
    std::cout << " Frame: "<< videoInfo.current_frame <<std::endl;
    std::cout << " Tempo: " << videoInfo.current_time << " Total: " << videoInfo.total_time <<std::endl;
    std::cout << " audio: " << videoInfo.audio_current_frame << " - af:" << videoInfo.audio_current_frame <<std::endl;

    SDL_BlitSurface(sVideo, NULL, pScreen, NULL);
    //Uint8 u = videoInfo.audio_current_frame;
    //SMPEG_playAudioSDL(mpeg,&u,1024);

}
/*
void updateMPEGFrame(SDL_Surface * buffer, Sint32 x, Sint32 y, Uint32 w, Uint32 h)
{



   SDL_BlitSurface(buffer, NULL, pScreen, NULL);
   SDL_Flip(pScreen);
}
*/

