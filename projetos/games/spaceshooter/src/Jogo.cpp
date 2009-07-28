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

int main(int argc, char * argv[])
{
    GAT::GAT* jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->executar();
    } catch (std::exception& e) {
       // UtilLog::sistema("!!!!!!!!!!");
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
Jogo::Jogo(int argc, char* argv[]):GAT(argc,argv)
{
    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(GBF::Kernel::Timer::TEMPO_DECIMO);
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
    if (janelaSobre){
        delete(janelaSobre);
    }
    if (janelaCredito){
        delete(janelaCredito);
    }
    if (janelaAjuda){
        delete(janelaAjuda);
    }
    if (janelaRecorde){
        delete(janelaRecorde);
    }
}
void Jogo::apresentacao()
{
    videoApresentacao->executar();
    if ((frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_RETURN))
        || (frameworkGBF->inputSystemCore->inputSystem->joystick->isButtonA())){
            setMenu();
    }
}
void Jogo::gatilhoMenuPrincipal()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("fundo_menu");
}
void Jogo::menuPrincipal()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    showTitulo();
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

void Jogo::menuConfiguracao()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    showTitulo();
    showInfo();

    uiMenuIdioma->executar();

    switch(uiMenuIdioma->confirmarSelecao())
    {
        case 0:
                frameworkGBF->writeSystem->idioma->setIdioma("en");
                setMenuPrincipal();
            break;
        case 1:
                frameworkGBF->writeSystem->idioma->setIdioma("br");
                setMenuPrincipal();
            break;
        case 2:
                frameworkGBF->writeSystem->idioma->setIdioma("es");
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
    return recordeManager->carregar();
}
void Jogo::topGaleriaExibir()
{
    RankingSystem::RSRecorde recorde;

    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janelaRecorde->executar();

    for (int i=0; i<10;i++){
		recorde=recordeManager->getRecorde(i);

        if (recorde.tipo[0]=='G'){
            iconeGlobal->desenhar(60,72+(26*i));
        } else {
            iconeLocal->desenhar(60,72+(26*i));
        }

        frameworkGBF->writeSystem->escrever("recorde",  90, 62+(26*i),"%s",recorde.nome);
        frameworkGBF->writeSystem->escrever("recorde", 340, 62+(26*i),"%08d",recorde.pontos);
    }

    frameworkGBF->writeSystem->escreverLocalizado("nisemega_extra", 90,56,"tela_top_recorde_2");
    frameworkGBF->writeSystem->escreverLocalizado("nisemega_extra",340,56,"tela_top_recorde_3");

    if (janelaRecorde->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenu();
    }
}
bool Jogo::gatilhoTopGaleriaNovo()
{
    bool continua = false;

    RankingSystem::RSRecorde recorde = controle.novoRecorde();

    if (!recordeManager->pesquisar(recorde)){
        if(recorde.pontos>recordeManager->getRecorde(9).pontos){
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
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    uiRecordeNovo->executar();

    if (uiRecordeNovo->isAcao(UserInterface::Window::UIWindowRecorde::BOTAO_SALVAR)){
        setTopGaleriaSalvar();
    }
}
void Jogo::topGaleriaSalvar()
{
    if ((recordeManager)&&(uiRecordeNovo)){
        if (recordeManager->adicionar(uiRecordeNovo->getRecorde())){
            recordeManager->salvar();
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
        controle.jogoExecutando(frameworkGBF->inputSystemCore->inputSystem);
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
/** Novo Jogo */
void Jogo::jogoNovo()
{
    frameworkGBF->soundSystemCore->soundSystem->musicManager->stop("fundo_menu");
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

    GBF::Area area = controle.getFaseAreaZona();

    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("mapa")->desenhar();

    frameworkGBF->writeSystem->escreverLocalizadoSubChave("texto" ,60,394,"tela_fase_zona",controle.getZona());
    frameworkGBF->writeSystem->escreverLocalizadoSubChave("texto" ,60,420,"tela_fase_missao",controle.getMissao());
    frameworkGBF->writeSystem->escreverLocalizadoSubChave("texto" ,60,446,"tela_fase_alerta",controle.getInimigo());

    if (tempoBlink.getTempo()%2==0){
        frameworkGBF->graphicSystemCore->graphicSystem->gfx->setColor(0,128,0);
    } else {
        frameworkGBF->graphicSystemCore->graphicSystem->gfx->setColor(0,255,0);
    }

    frameworkGBF->graphicSystemCore->graphicSystem->gfx->retangulo(area.left,area.top,area.right,area.bottom);

    if (desenharBotaoEnter()){
        if ((frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_RETURN))
            || (frameworkGBF->inputSystemCore->inputSystem->joystick->isButtonA())){
                controle.inicializarFase();
                setJogoExecutando();
        }
    }

}
void Jogo::jogoPause()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janela->titulo.setChaveTexto("titulo_pause");
    janela->texto.setChaveTexto("tela_pause_%02d");
    janela->executar();

    banner->desenhar(90,390);

    if (janela->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setJogoExecutando();
    }
}
bool Jogo::gatilhoJogoFaseFinalizada()
{
    controle.faseFinalizada();

    return true;
}
void Jogo::jogoFaseFinalizada()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janela->titulo.setChaveTexto("titulo_fase_finalizada");
    janela->texto.setChaveTexto("fase_finalizada_%02d");
    janela->executar();

    if (janela->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setJogoFaseCarregar();
    }
}
void Jogo::jogoGameOver()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janela->titulo.setChaveTexto("titulo_gameover");
    janela->texto.setChaveTexto("tela_derrota_%02d");
    janela->executar();

    if (janela->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setTopGaleria();
        setTopGaleriaNovo();
    }
}
void Jogo::jogoZerado()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janela->titulo.setChaveTexto("titulo_vitoria");
    janela->texto.setChaveTexto("tela_vitoria_%02d");
    janela->executar();

    if (janela->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setTopGaleria();
        setTopGaleriaNovo();
    }
}


/** Carregar arquivos de recursos */
void Jogo::inicializarRecursos()
{
    frameworkGBF->setTitulo("GBF :: SpaceShooter : Trek's","DukItan Software");
    frameworkGBF->iniciar(640,480,16,isFullScreen(),GBF::Kernel::FPS::FPS_LIMITADO);
    //Ativando GRAB_ON para evitar mudança de tela durante o
    // jogo no Gnome (Desktop para o GNU/Linux)
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

    frameworkGBF->setFPS(true);
    recordeManager->setArquivo("data//etc//toprecord.top");
    recordeManager->setAssinatura(ASSINATURA_JOGO_NOME,ASSINATURA_JOGO_SIGLA,ASSINATURA_JOGO_VERSAO);


//carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem","data//imagem//spaceshooter_personagem.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("tilemap","data//imagem//tilemap_01.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("painel","data//imagem//tile_painel.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("armas","data//imagem//spaceshooter_armas.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("console","data//imagem//spaceshooter_console.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("mapa","data//imagem//spaceshooter_mapa.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("startrek","data//imagem//startrek.jpg");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("abertura","data//imagem//spaceshooter_abertura.png");
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","data//imagem//spaceshooter_tiles.png");


    frameworkGBF->writeSystem->carregar("nisemegaeu","data//fonte//nisemegaeu.png");
    frameworkGBF->writeSystem->carregar("texto","data//fonte//ds9_computer.png");
    frameworkGBF->writeSystem->carregar("recorde","data//fonte//recorde.png");
    frameworkGBF->writeSystem->carregar("nisemega_extra","data//fonte//nisemegaeu.png");
    frameworkGBF->writeSystem->carregar("status","data//fonte//nisemega.png");

    frameworkGBF->writeSystem->getFonte("recorde")->setDimensao(24,24);
    frameworkGBF->writeSystem->getFonte("status")->setDimensao(16,16);

    frameworkGBF->writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF->writeSystem->idioma->detectarIdioma();

//carregando audio - efeitos
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("tiro","data//som//laser.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("explosao","data//som//explosao.wav");
    frameworkGBF->soundSystemCore->soundSystem->fxManager->carregar("alerta","data//som//redalert.ogg");
    frameworkGBF->soundSystemCore->soundSystem->musicManager->carregar("fundo_menu","data//som//01-wheremyheart.ogg");

//Configura volume dos efeitos
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("tiro",20);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("explosao",40);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setVolume("alerta",30);
    frameworkGBF->soundSystemCore->soundSystem->fxManager->setLimite(0,480);

//toca musica de fundo
    frameworkGBF->soundSystemCore->soundSystem->musicManager->playInfinity("fundo_menu");

    GBF::Imagem::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Imagem::SpriteFactory("console");
    GBF::Imagem::Layer::FrameLayer * console = spriteFactory->criarFrameLayer(0, 0,640,480);
    console->setFrame(0,0,640,480);
    console->setTiles(1,1);
    console->setPixelTile(640,480);
    console->iniciarRandomico(1);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("console",console);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("mapa");
    GBF::Imagem::Layer::FrameLayer * mapa = spriteFactory->criarFrameLayer(0, 0,530,333);
    mapa->setFrame(53,18,530,333);
    mapa->setTiles(1,1);
    mapa->setPixelTile(530,333);
    mapa->iniciarRandomico(1);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("mapa",mapa);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("startrek");
    GBF::Imagem::Layer::FrameLayer * startrek = spriteFactory->criarFrameLayer(0, 0,640,480);
    startrek->setFrame(0,0,640,480);
    startrek->setTiles(1,1);
    startrek->setPixelTile(640,480);
    startrek->iniciarRandomico(1);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("startrek",startrek);
    delete(spriteFactory);

    videoApresentacao = new Apresentacao();

    //Menu
    uiMenuPrincipal = new UserInterface::Menu::UIMenu();
    uiMenuPrincipal->centralizarTela(640,90,UserInterface::HORIZONTAL);
    uiMenuPrincipal->setEspacoVertical(30);
    uiMenuPrincipal->setCorFundo(0,0,0);
    uiMenuPrincipal->setCorBorda(206,101,99);
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_1","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_2","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_3","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_4","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_5","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_6","nisemegaeu"));
    uiMenuPrincipal->adicionar(new UserInterface::Menu::UIItemTexto("menu_7","nisemegaeu"));

    uiMenuIdioma = new UserInterface::Menu::UIMenu();
    uiMenuIdioma->centralizarTela(640,480,UserInterface::CENTRO);
    uiMenuIdioma->setEspacoVertical(30);
    uiMenuIdioma->setCorFundo(0,0,0);
    uiMenuIdioma->setCorBorda(206,101,99);
    uiMenuIdioma->adicionar(new UserInterface::Menu::UIItemTexto("menu_idioma_en","nisemegaeu"));
    uiMenuIdioma->adicionar(new UserInterface::Menu::UIItemTexto("menu_idioma_br","nisemegaeu"));
    uiMenuIdioma->adicionar(new UserInterface::Menu::UIItemTexto("menu_idioma_es","nisemegaeu"));

    spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    iconeGlobal   = spriteFactory->criarSpriteItem(12,34,24,24,1,1);
    iconeLocal    = spriteFactory->criarSpriteItem(37,34,24,24,1,1);
    banner        = spriteFactory->criarSpriteItem( 0,59,512,89,1,1);

    delete(spriteFactory);


    UserInterface::Visual::UIVisualSolido *uiVisualSolido = new UserInterface::Visual::UIVisualSolido();
    uiVisualSolido->setCorBorda(255,255,0);
    uiVisualSolido->setCorFundo(0,0,0);

    UserInterface::Visual::UIVisualImagem *uiVisualTransparente = new UserInterface::Visual::UIVisualImagem();
    uiVisualTransparente->setCorBorda(255,255,0);
    uiVisualTransparente->setTipoBackground(UserInterface::Visual::BACKGROUND_LINES_BLACK);

    janelaAjuda = new UserInterface::Window::UIWindowTitulo();
    janelaAjuda->setPosicao(53,19);
    janelaAjuda->setDimensao(529,327);
    janelaAjuda->texto.setFonte("texto");
    janelaAjuda->texto.setChaveTexto("tela_ajuda_%02d");
    janelaAjuda->titulo.setFonte("recorde");
    janelaAjuda->titulo.setChaveTexto("titulo_ajuda");
    janelaAjuda->setVisual(uiVisualSolido->clone());
    janelaAjuda->adicionarBotao(new UserInterface::Componente::UIBotao("nisemega_extra","botao_enter",SDLK_RETURN));
    janelaAjuda->inicializar();

    janelaCredito = new UserInterface::Window::UIWindowTitulo();
    janelaCredito->setPosicao(53,19);
    janelaCredito->setDimensao(529,327);
    janelaCredito->texto.setFonte("texto");
    janelaCredito->texto.setChaveTexto("tela_credito_%02d");
    janelaCredito->titulo.setFonte("recorde");
    janelaCredito->titulo.setChaveTexto("titulo_credito");
    janelaCredito->setVisual(uiVisualSolido->clone());
    janelaCredito->adicionarBotao(new UserInterface::Componente::UIBotao("nisemega_extra","botao_enter",SDLK_RETURN));
    janelaCredito->inicializar();

    janelaSobre = new UserInterface::Window::UIWindowTitulo();
    janelaSobre->setPosicao(53,19);
    janelaSobre->setDimensao(529,327);
    janelaSobre->texto.setFonte("texto");
    janelaSobre->texto.setChaveTexto("tela_sobre_%02d");
    janelaSobre->titulo.setFonte("recorde");
    janelaSobre->titulo.setChaveTexto("titulo_sobre");
    janelaSobre->setVisual(uiVisualSolido->clone());
    janelaSobre->adicionarBotao(new UserInterface::Componente::UIBotao("nisemega_extra","botao_enter",SDLK_RETURN));
    janelaSobre->inicializar();

    janelaRecorde = new UserInterface::Window::UIWindowTitulo();
    janelaRecorde->setPosicao(53,19);
    janelaRecorde->setDimensao(529,327);
    janelaRecorde->titulo.setFonte("recorde");
    janelaRecorde->titulo.setChaveTexto("tela_top_recorde_1");
    janelaRecorde->setVisual(uiVisualSolido->clone());
    janelaRecorde->adicionarBotao(new UserInterface::Componente::UIBotao("nisemega_extra","botao_enter",SDLK_RETURN));
    janelaRecorde->inicializar();

    janela = new UserInterface::Window::UIWindowTitulo();
    janela->setPosicao(53,90);
    janela->setDimensao(529,230);
    janela->titulo.setFonte("recorde");
    janela->titulo.setChaveTexto("titulo_pause");
    janela->texto.setFonte("texto");
    janela->texto.setChaveTexto("tela_ajuda_%02d");
    janela->texto.setAlinhamento(UserInterface::Texto::TEXTO_CENTRALIZADO);
    janela->setVisual(uiVisualTransparente->clone());
    janela->adicionarBotao(new UserInterface::Componente::UIBotao("nisemega_extra","botao_enter",SDLK_RETURN));
    janela->inicializar();

    uiRecordeNovo = new UserInterface::Window::UIWindowRecorde();
    uiRecordeNovo->setPosicao(70,80);
    uiRecordeNovo->setDimensao(480,260);
    uiRecordeNovo->setVisual(uiVisualTransparente->clone());
    uiRecordeNovo->setVisualComponentes(uiVisualSolido);//Clonar para usar
    uiRecordeNovo->setFonteTitulo("recorde");
    uiRecordeNovo->setFonteEdit("texto","nisemega_extra");
    uiRecordeNovo->setFonteTecladoVirtual("recorde","texto");
    uiRecordeNovo->inicializar();

    delete(uiVisualTransparente);
//    delete(uiVisualSolido);
}
void Jogo::showInfo()
{
    frameworkGBF->writeSystem->escreverLocalizado("texto",180,390,"tela_info_1");
    frameworkGBF->writeSystem->escreverLocalizado("texto",180,420,"tela_info_2");
    frameworkGBF->writeSystem->escreverLocalizado("texto",180,450,"tela_info_3");
}
void Jogo::showTitulo()
{
    frameworkGBF->writeSystem->escreverLocalizado("texto",270,50,"tela_subtitulo");
}
void Jogo::menuAjuda()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janelaAjuda->executar();
    banner->desenhar(90,390);

    if (janelaAjuda->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuCredito()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janelaCredito->executar();
    banner->desenhar(90,390);

    if (janelaCredito->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}
void Jogo::menuSobre()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("console")->desenhar();

    janelaSobre->executar();
    banner->desenhar(90,390);

    if (janelaSobre->isAcao(UserInterface::Window::UIWindowDialog::BOTAO_OK)){
        setMenuPrincipal();
    }
}

bool Jogo::desenharBotaoEnter()
{
    bool desenhe = isTempoEspera();

    if (desenhe){
        frameworkGBF->graphicSystemCore->graphicSystem->gfx->setColor(0,0,0);
        frameworkGBF->graphicSystemCore->graphicSystem->gfx->retanguloPreenchido(504,369,136,14);
        frameworkGBF->writeSystem->escreverLocalizado("nisemega_extra",500,372,"botao_enter");
    }
    return desenhe;
}

