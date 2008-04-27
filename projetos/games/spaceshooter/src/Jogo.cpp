/***************************************************************************
 *   Copyright (C) 2005-2007 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa é um software livre; você pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
 *   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
 *   Licença.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "Jogo.h"

Jogo::Jogo(int argc, char* argv[]):GAT(argc,argv)
{
    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
}
Jogo::~Jogo()
{
    if (iconeGlobal){
        delete(iconeGlobal);
    }
    if (iconeLocal){
        delete(iconeLocal);
    }
    if (banner){
        delete(banner);
    }
    if (videoApresentacao){
        delete(videoApresentacao);
    }
    if (uiMenuIdioma){
        delete(uiMenuIdioma);
    }
}
void Jogo::apresentacao()
{
    videoApresentacao->executar();
    if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
        || (frameworkGBF->inputSystem->joystick->isButtonA())){
            setMenu();
    }
}
void Jogo::gatilhoMenuPrincipal()
{
    frameworkGBF->soundSystem->musicManager->playInfinity("fundo_menu");
}
void Jogo::menuPrincipal()
{
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();
    showTitulo();
    showSubTitulo();
    showInfo();

    if (uiMenuPrincipal->executar()){
        tempoInativo.setResetar();
    }

    switch(uiMenuPrincipal->confirmarSelecao())
    {
        case 0:
                setTopGaleria();
            break;
        case 1:
                setJogo();
            break;
        case 2:
                setMenuAjuda();
            break;
        case 3:
                setMenuSobre();
            break;
        case 4:
                setMenuCredito();
            break;
        case 5:
                setMenuConfiguracao();
            break;
        case 6:
                setSair();
            break;
    }

    videoApresentacao->reset();
}

//
//  GATMaquinaEstadoMenu
//
////////////////////////////////////////////////
void Jogo::menuSobre()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<8;i++){
        sprintf(textoFormatado,"tela_sobre_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,80+(20*i),textoFormatado);
    }
    frameworkGBF->writeSystem->escreverLocalizado("tech", 252, 50,"titulo_sobre");

    banner->desenhar(90,390);


    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuAjuda()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<9;i++){
        sprintf(textoFormatado,"tela_ajuda_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,80+(20*i),textoFormatado);
    }

    frameworkGBF->writeSystem->escreverLocalizado("tech", 252, 50,"titulo_ajuda");

    banner->desenhar(90,390);

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
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<13;i++){
        sprintf(textoFormatado,"tela_credito_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",70,80+(20*i),textoFormatado);
    }

    frameworkGBF->writeSystem->escreverLocalizado("tech", 226, 50,"titulo_credito");

    banner->desenhar(90,390);

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))||
            (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenuPrincipal();
        }
    }
}
void Jogo::menuConfiguracao()
{
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();
    showTitulo();
    showSubTitulo();
    showInfo();

    uiMenuIdioma->executar();

    switch(uiMenuIdioma->confirmarSelecao())
    {
        case 0:
                frameworkGBF->writeSystem->uiTexto->setIdioma("en");
                setMenuPrincipal();
            break;
        case 1:
                frameworkGBF->writeSystem->uiTexto->setIdioma("br");
                setMenuPrincipal();
            break;
        case 2:
                frameworkGBF->writeSystem->uiTexto->setIdioma("es");
                setMenuPrincipal();
            break;
    }
}
//
//  GATMaquinaEstadoTopGaleria
//
////////////////////////////////////////////////
bool Jogo::gatilhoTopGaleriaExibir()
{
    return tsGaleria->carregar();
}
void Jogo::topGaleriaExibir()
{
    TopSystemRecorde recorde;

    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    frameworkGBF->graphicSystem->gsGFX->setColor(0,0,0);
    frameworkGBF->graphicSystem->gsGFX->retanguloPreenchido(53,50,529,284);
    frameworkGBF->graphicSystem->gsGFX->setColor(206,101,99);
    frameworkGBF->graphicSystem->gsGFX->retangulo(53,50,529,284);

    for (int i=0; i<10;i++){
		recorde=tsGaleria->getRecorde(i);

        if (recorde.tipo[0]=='G'){
            iconeGlobal->desenhar(60,72+(26*i));
        } else {
            iconeLocal->desenhar(60,72+(26*i));
        }

        frameworkGBF->writeSystem->escrever("recorde",  90, 70+(26*i),"%s",recorde.nome);
        frameworkGBF->writeSystem->escrever("recorde", 340, 70+(26*i),"%08d",recorde.pontos);
    }

    frameworkGBF->writeSystem->escreverLocalizado("recorde", 226, 20,"tela_top_recorde_1");
    frameworkGBF->writeSystem->escreverLocalizado("tech", 90,45,"tela_top_recorde_2");
    frameworkGBF->writeSystem->escreverLocalizado("tech",340,45,"tela_top_recorde_3");

    showAvisoRecorde();

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setMenu();
        }
    }
}
bool Jogo::gatilhoTopGaleriaNovo()
{
    bool continua = false;

    TopSystemRecorde recorde = controle.novoRecorde();
    if (!tsGaleria->pesquisar(recorde)){
        if(recorde.pontos>tsGaleria->getRecorde(9).pontos){
            uiRecordeNovo->setRecorde(recorde);
            continua=true;
        }
    }
    if (!continua){
        setTopGaleria();
    }

    return continua;
}
void Jogo::topGaleriaNovo()
{
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    frameworkGBF->writeSystem->escreverLocalizado("recorde", 226,20,"tela_top_recorde_1");
    frameworkGBF->writeSystem->escreverLocalizado("tech",    100,60,"tela_top_recorde_2");
    frameworkGBF->writeSystem->escreverLocalizado("tech",    350,60,"tela_top_recorde_3");

    showAvisoRecorde();

    uiRecordeNovo->desenhar();
    if (uiRecordeNovo->controle()){
        setTopGaleriaSalvar();
    }
}
void Jogo::topGaleriaSalvar() {

    if ((tsGaleria)&&(uiRecordeNovo)){
         if (tsGaleria->adicionar(uiRecordeNovo->getRecorde())){
            tsGaleria->salvar();
         }
    }
    setTopGaleriaExibir();
}

//
//  GATMaquinaEstadoJogo
//
////////////////////////////////////////////////

/** Jogo em Execução */
void Jogo::jogoExecutando()
{
    if (controle.isGameOver()){
        setJogoGameOver();
    } else if (controle.isFaseFinalizada()){
        setJogoFaseFinalizada();
    } else {
        controle.jogoExecutando(frameworkGBF->inputSystem);
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
/** Novo Jogo */
void Jogo::jogoNovo()
{
    frameworkGBF->soundSystem->musicManager->stop("fundo_menu");
    controle.novoJogo();
    setJogoFaseCarregar();
}
bool Jogo::gatilhoJogoFaseCarregar()
{
    bool continua = controle.carregarFase();

    if(!continua){
        setJogoZerado();
    } else {
        tempoBlink.setResetar();
    }

    return continua;
}
void Jogo::jogoFaseCarregar()
{
    tempoBlink.processar();

    Area area = controle.getFaseAreaZona();

    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();
    FrameLayerManager::getInstance()->getFrameLayer("mapa")->desenhar();

    frameworkGBF->writeSystem->escreverLocalizadoSubChave("tech" ,60,394,"tela_fase_zona",controle.getZona());
    frameworkGBF->writeSystem->escreverLocalizadoSubChave("tech" ,60,420,"tela_fase_missao",controle.getMissao());
    frameworkGBF->writeSystem->escreverLocalizadoSubChave("tech" ,60,446,"tela_fase_alerta",controle.getInimigo());

    if (tempoBlink.getTempo()%2==0){
        frameworkGBF->graphicSystem->gsGFX->setColor(0,128,0);
    } else {
        frameworkGBF->graphicSystem->gsGFX->setColor(0,255,0);
    }

    frameworkGBF->graphicSystem->gsGFX->retangulo(area.left,area.top,area.right,area.bottom);

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                controle.inicializarFase();
                setJogoExecutando();
        }
    }

}
void Jogo::jogoPause()
{
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    banner->desenhar(90,390);

    frameworkGBF->writeSystem->escreverLocalizado("tech",230,60,"tela_pause_01");

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
               setJogoExecutando();
        }
    }
}
bool Jogo::gatilhoJogoFaseFinalizada()
{
    controle.faseFinalizada();

    return true;
}
void Jogo::jogoFaseFinalizada()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<1;i++){
        sprintf(textoFormatado,"fase_finalizada_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",230,60+(18*i),textoFormatado);
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
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<5;i++){
        sprintf(textoFormatado,"tela_derrota_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",100,80+(18*i),textoFormatado);
    }

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setTopGaleria();
                setTopGaleriaNovo();
        }
    }
}
void Jogo::jogoZerado()
{
    char textoFormatado[30];
    FrameLayerManager::getInstance()->getFrameLayer("console")->desenhar();

    desenharGUI();
    showTitulo();

    for (int i=0; i<9;i++){
        sprintf(textoFormatado,"tela_vitoria_%02d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",100,80+(18*i),textoFormatado);
    }

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystem->joystick->isButtonA())){
                setTopGaleria();
                setTopGaleriaNovo();
        }
    }
}


/** Carregar arquivos de recursos */
void Jogo::inicializarRecursos()
{
    frameworkGBF->setTitulo("GBF :: SpaceShooter : Trek's","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,isFullScreen());
    //Ativando GRAB_ON para evitar mudança de tela durante o jogo no Gnome (Desktop para o GNU/Linux)
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_ON);
    //frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);

    tsGaleria->setArquivo("data//etc//toprecord.top");
    tsGaleria->setAssinatura(ASSINATURA_JOGO_NOME,ASSINATURA_JOGO_SIGLA,ASSINATURA_JOGO_VERSAO);


//carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("personagem","data//imagem//spaceshooter_personagem.png");
    GSIBManager->carregar("tiles","data//imagem//spaceshooter_tiles.png");
    GSIBManager->carregar("armas","data//imagem//spaceshooter_armas.png");
    GSIBManager->carregar("console","data//imagem//spaceshooter_console.png");
    GSIBManager->carregar("mapa","data//imagem//spaceshooter_mapa.png");
    GSIBManager->carregar("startrek","data//imagem//startrek.jpg");
    GSIBManager->carregar("abertura","data//imagem//spaceshooter_abertura.png");

    frameworkGBF->writeSystem->carregar("recorde",frameworkGBF->getPath()+"data//kernel//fonte//recorde.png");
    frameworkGBF->writeSystem->carregar("tech",frameworkGBF->getPath()+"data//kernel//fonte//nisemega.png");
    frameworkGBF->writeSystem->carregar("status",frameworkGBF->getPath()+"data//kernel//fonte//nisemega.png");
    frameworkGBF->writeSystem->carregar("texto",frameworkGBF->getPath()+"data//kernel//fonte//texto_arial.png");

    frameworkGBF->writeSystem->getFonte("tech")->setDimensao(18,18);
    frameworkGBF->writeSystem->getFonte("status")->setDimensao(16,16);
    frameworkGBF->writeSystem->getFonte("recorde")->setDimensao(24,24);
    //frameworkGBF->writeSystem->getFonte("texto")->setDimensao(16,16);

    frameworkGBF->writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF->writeSystem->uiTexto->detectarIdioma();

//carregando audio - efeitos
    frameworkGBF->soundSystem->fxManager->carregar("tiro","data//som//laser.wav");
    frameworkGBF->soundSystem->fxManager->carregar("explosao","data//som//explosao.wav");
    frameworkGBF->soundSystem->fxManager->carregar("alerta","data//som//redalert.ogg");
    frameworkGBF->soundSystem->musicManager->carregar("fundo_menu","data//som//01-wheremyheart.ogg");

//Configura volume dos efeitos
    frameworkGBF->soundSystem->fxManager->setVolume("tiro",20);
    frameworkGBF->soundSystem->fxManager->setVolume("explosao",40);
    frameworkGBF->soundSystem->fxManager->setVolume("alerta",30);
    frameworkGBF->soundSystem->fxManager->setLimite(0,480);
//toca musica de fundo
    frameworkGBF->soundSystem->musicManager->playInfinity("fundo_menu");

    SpriteFactory * spriteFactory = NULL;

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("console"));
    FrameLayer * console = spriteFactory->criarFrameLayer(0, 0,640,480);
    console->setFrame(0,0,640,480);
    console->setTiles(1,1);
    console->setPixelTile(640,480);
    console->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("console",console);
    delete(spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("mapa"));
    FrameLayer * mapa = spriteFactory->criarFrameLayer(0, 0,530,333);
    mapa->setFrame(53,18,530,333);
    mapa->setTiles(1,1);
    mapa->setPixelTile(530,333);
    mapa->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("mapa",mapa);
    delete(spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("startrek"));
    FrameLayer * startrek = spriteFactory->criarFrameLayer(0, 0,640,480);
    startrek->setFrame(0,0,640,480);
    startrek->setTiles(1,1);
    startrek->setPixelTile(640,480);
    startrek->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("startrek",startrek);
    delete(spriteFactory);

    videoApresentacao = new Apresentacao();

    uiMenuPrincipal = new UserInterfaceMenuTexto(frameworkGBF->inputSystem);
    uiMenuPrincipal->centralizarTela(640,90,HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(30);
    uiMenuPrincipal->setCorFundo(0,0,0);
    uiMenuPrincipal->setCorBorda(206,101,99);
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_1","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_2","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_3","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_4","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_5","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_6","tech"));
    uiMenuPrincipal->adicionar(new UserInterfaceMenuItemTexto("menu_7","tech"));

    uiMenuIdioma = new UserInterfaceMenuTexto(frameworkGBF->inputSystem);
    uiMenuIdioma->centralizarTela(640,480,CENTRO);
    uiMenuIdioma->setEspacoVertical(30);
    uiMenuIdioma->setCorFundo(0,0,0);
    uiMenuIdioma->setCorBorda(206,101,99);
    uiMenuIdioma->adicionar(new UserInterfaceMenuItemTexto("menu_idioma_en","tech"));
    uiMenuIdioma->adicionar(new UserInterfaceMenuItemTexto("menu_idioma_br","tech"));
    uiMenuIdioma->adicionar(new UserInterfaceMenuItemTexto("menu_idioma_es","tech"));

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("tiles"));
    iconeGlobal   = spriteFactory->criarSpriteItem(304,46,24,24,1,1);
    iconeLocal    = spriteFactory->criarSpriteItem(329,46,24,24,1,1);
    banner        = spriteFactory->criarSpriteItem(0,160,512,89,1,1);

    delete(spriteFactory);

    uiRecordeNovo = new UserInterfaceRecorde();
    uiRecordeNovo->setInput(frameworkGBF->inputSystem);
    uiRecordeNovo->setWriteManager(frameworkGBF->writeSystem);
    uiRecordeNovo->setGFX(frameworkGBF->graphicSystem->gsGFX);
    uiRecordeNovo->setFonteLabel("tech");
    uiRecordeNovo->setFonteTeclado("recorde");
    uiRecordeNovo->setPosicao(80,130);
}
void Jogo::desenharGUI()
{
    frameworkGBF->graphicSystem->gsGFX->setColor(0,0,0);
    frameworkGBF->graphicSystem->gsGFX->retanguloPreenchido(53,50,529,290);
    frameworkGBF->graphicSystem->gsGFX->setColor(206,101,99);
    frameworkGBF->graphicSystem->gsGFX->retangulo(53,50,529,290);
}
bool Jogo::desenharBotaoEnter()
{
    bool desenhe = isTempoEspera();

    if (desenhe){
        frameworkGBF->graphicSystem->gsGFX->setColor(0,0,0);
        frameworkGBF->graphicSystem->gsGFX->retanguloPreenchido(504,369,115,14);
        frameworkGBF->writeSystem->escreverLocalizado("tech",500,360,"botao_enter");
    }
    return desenhe;
}
void Jogo::showAvisoRecorde()
{
    char textoFormatado[30];

    for (int i=0; i<3;i++){
        sprintf(textoFormatado,"top_recorde_aviso_%d",(1)+i);
        frameworkGBF->writeSystem->escreverLocalizado("texto",60,390+(18*i),textoFormatado);
    }
}
void Jogo::showInfo()
{
    frameworkGBF->writeSystem->escreverLocalizado("texto",180,390,"tela_info_1");
    frameworkGBF->writeSystem->escreverLocalizado("texto",206,420,"tela_info_2");
    frameworkGBF->writeSystem->escreverLocalizado("texto",246,450,"tela_info_3");
}
void Jogo::showTitulo()
{
    frameworkGBF->writeSystem->escreverLocalizado("recorde",160,20,"tela_titulo");
}
void Jogo::showSubTitulo()
{
    frameworkGBF->writeSystem->escreverLocalizado("texto",270,50,"tela_subtitulo");
}



