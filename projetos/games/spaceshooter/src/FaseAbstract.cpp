/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
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
#include "FaseAbstract.h"
#include "NaveAliado.h"

Sistema FaseAbstract::sistemaNaveBackup;
GBF::Imagem::Layer::FrameLayer   * FaseAbstract::tileStatus      = NULL;
GBF::Imagem::Layer::FrameLayer   * FaseAbstract::tileMensagem    = NULL;
GBF::Kernel::Write::WriteManager * FaseAbstract::writeManager    = NULL;
ParticleSystem::PSManager        * FaseAbstract::particleManager = NULL;

FaseAbstract::FaseAbstract()
{
    GBF::Imagem::SpriteFactory  * spriteFactory = NULL;

    if (tileStatus==NULL){
        spriteFactory = new GBF::Imagem::SpriteFactory("painel");
        tileStatus    = spriteFactory->criarFrameLayer(0, 0, 160, 480);

        delete(spriteFactory);

        tileStatus->setFrame(480,0,160,480);
        tileStatus->setTiles(1,1);
        tileStatus->setPixelTile(160,480);
        tileStatus->iniciarCom(0);
    }

    spriteFactory = new GBF::Imagem::SpriteFactory("tilemap");

    tileSpace = spriteFactory->criarFrameLayer(0, 0, 32, 32);

    if (tileMensagem==NULL){
        tileMensagem = spriteFactory->criarFrameLayer(0, 0, 32, 32);

        tileMensagem->setFrame(0,448,480,32);
        tileMensagem->setTiles(15,1);
        tileMensagem->setPixelTile(32,32);
        tileMensagem->iniciarCom(12);
    }

    delete(spriteFactory);


    if (writeManager==NULL) {
        writeManager = GBF::Kernel::Write::WriteManager::getInstance();
    }

    if (particleManager==NULL){
        particleManager = ParticleSystem::PSManager::getInstance();
    }
    particleManager->limpar();

    zona    = ">Desconhecida>";
    missao  = ">Desconhecida>";
    inimigo = ">Desconhecidos>";

    areaZona.left   =70;
    areaZona.top    =327;
    areaZona.bottom =0;
    areaZona.right  =0;

    //default
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    placar = Placar::getInstance();
    status = InterfaceStatus::getInstance();


    ultimoQuadro = false;
    restaurar    = false;
    nave         = NULL;

	status->inicializar();
}
FaseAbstract::~FaseAbstract()
{
    soundSystem->musicManager->stop("fase");
    soundSystem->musicManager->apagar("fase");

    if (nave){
        sistemaNaveBackup = nave->getSistema();
        delete(nave);
        nave = NULL;
    }

    //Como são Singletons não devem ser deletados por essa classe
    placar      = NULL;
    status      = NULL;

    listSpaceInimigo   = NULL;
    listSpaceObstaculo = NULL;
    listTiroJogador    = NULL;
    listTiroInimigo    = NULL;
    listItem           = NULL;

    if (tileSpace!=NULL){
        delete(tileSpace);
    }
}
void FaseAbstract::restaurarNave()
{
    if (restaurar){
        nave->setSistema(sistemaNaveBackup);
        restaurar=false;
    }
}
void FaseAbstract::checkRestaurar()
{
    restaurar=true;
}
void FaseAbstract::definir()
{
    /*tileStatus->setFrame(480,0,160,480);
    tileStatus->setTiles(1,1);
    tileStatus->setPixelTile(160,480);
    tileStatus->iniciarCom(0);*/

    /*tileMensagem->setFrame(0,448,480,32);
    tileMensagem->setTiles(15,1);
    tileMensagem->setPixelTile(32,32);
    tileMensagem->iniciarCom(12);*/
}
void FaseAbstract::armazenar()
{
    //GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("tileSpace",tileSpace);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("tileStatus",tileStatus);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("tileMensagem",tileMensagem);


    SpaceObject::setArea(tileSpace->getArea());
    PathStrategy::setArea(tileSpace->getArea());
}
void FaseAbstract::carregar()
{
    definir();
    configurar();
    armazenar();

    listSpaceInimigo   = ListSpaceInimigo::getInstance();
    listSpaceObstaculo = ListSpaceObstaculo::getInstance();
    listTiroJogador    = ListTiroJogador::getInstance();
    listTiroInimigo    = ListTiroInimigo::getInstance();
    listItem           = ListItem::getInstance();
}
bool FaseAbstract::isPerdeu()
{
    if (nave->getEscudo()<0){
        return true;
    } else {
        return false;
    }
}
void FaseAbstract::executar(GBF::Kernel::Input::InputSystem * input)
{
    desenharCenario();

    //Ação Principal - movimentação
    listSpaceInimigo->acao(NULL);
    listSpaceObstaculo->acao(NULL);
    listTiroJogador->acao(NULL);
    listTiroInimigo->acao(NULL);
    listItem->acao(NULL);
    //ListSpaceObstaculoNeutro::getInstance()->acao();

    //Só realiza operações com a nave caso ela ainda esteja 'ativa'
    if (nave->getEscudo()>=0) {
        //Ação Principal - movimentação
        nave->acao(input);

    //Colisões
        //tiro do jogador
        listTiroJogador->colisao(listSpaceObstaculo);
        listTiroJogador->colisao(listSpaceInimigo);
        //tiro do inimigo
        listTiroInimigo->colisao(listSpaceObstaculo);
        listTiroInimigo->colisao(nave);
        //jogador bate
        listSpaceObstaculo->colisao(nave);
        listSpaceInimigo->colisao(nave);
        ObstaculoAbstract::setVelocidadeBase(nave->getVelocidade());
        nave->colisao(ListItem::getInstance());

        //NOTA 25/07/2008 : processamento das listas consome muito processamento, ver
        //como otimizar
    }

    //Alguns procedimentos realizados para se desenhar
    //trocando o metodo de executar para desenhar
    listTiroInimigo->desenhar();
    listTiroJogador->desenhar();
    listSpaceObstaculo->desenhar();
    listSpaceInimigo->desenhar();
    listItem->desenhar();

    particleManager->executar();
    particleManager->desenhar();

    //ListSpaceObstaculoNeutro::getInstance()->executar();


    //Desenha a nave do jogador
	nave->desenhar();

    //Desenha Painel (status)
    desenharPainel();
}
std::string FaseAbstract::getZona()
{
    return zona;
}
std::string FaseAbstract::getMissao()
{
    return missao;
}
std::string FaseAbstract::getInimigo()
{
    return inimigo;
}
GBF::Area  FaseAbstract::getAreaZona()
{
    return areaZona;
}
ArsenalStatus FaseAbstract::getArsenalStatus()
{
	ArsenalStatus arsenal;

	arsenal.escudo     = nave->getEscudo();
	arsenal.arma       = nave->getTorpedo();
	arsenal.velocidade = nave->getVelocidade();

	return arsenal;
}
//TODO: criar mecanismo para velocidade apenas da fase, nao
//ligado diretamente com velocidade da nave
void FaseAbstract::desenharCenario()
{
    tileSpace->camera.runUp(nave->getVelocidade()*0.5);
    tileSpace->desenhar();

    if (ultimoQuadro==false){
        if (tileSpace->camera.isTop()){
            ultimoQuadro=true;
            condicaoUnicaUltimoQuadro();
        } else {
            condicaoNavegandoFase();
        }
    } else {
        ganchoUltimoQuadro();
    }
}
void FaseAbstract::ganchoUltimoQuadro()
{
}
void FaseAbstract::hookMensagens()
{
}
void FaseAbstract::hookMensagemFinal()
{
    writeManager->escreverLocalizado("texto",0,458,"msg_continue_avancado");
}
void FaseAbstract::exibirMensagem()
{
    if (!ultimoQuadro){
        hookMensagens();
    } else {
        hookMensagemFinal();
    }
}
void FaseAbstract::desenharPainel()
{
	tileStatus->desenhar();
    status->desenharStatus(nave->getVelocidade(),nave->getEscudo(),nave->getTorpedo(),nave->isPhaserRecarregar(),nave->isTorpedoRecarregar());
    status->desenharInformacoes(placar->getPontos(),0,0);

    tileMensagem->desenhar();
    exibirMensagem();
}
bool FaseAbstract::isTerminou()
{
    if ((tileSpace->camera.isTop())&&(nave->getPosicao().y==0)){
        return true;
    } else {
        return false;
    }
}


