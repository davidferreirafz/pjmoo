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

FaseAbstract::FaseAbstract()
{
    particleManager = ParticleSystem::PSManager::getInstance();
    particleManager->limpar();

    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("tiles");

    tiles   = spriteFactory->criarFrameLayer(0, 319,  32, 32);
    moldura = spriteFactory->criarFrameLayer(0, 352, 160,160);

    delete (spriteFactory);

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


	soundSystem = GBF::Kernel::Sound::SoundSystem::getInstance();
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
    soundSystem = NULL;
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
    moldura->setFrame(480,0,160,480);
    moldura->setTiles(1,3);
    moldura->setPixelTile(160,160);
    moldura->iniciarOrdenado(3);
}
void FaseAbstract::armazenar()
{
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("tiles",tiles);
    GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("moldura",moldura);
    SpaceObject::setArea(tiles->getArea());
}
void FaseAbstract::carregar()
{
    definir();
    configurar();
    armazenar();
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
    ListSpaceInimigo   *listSpaceInimigo   = ListSpaceInimigo::getInstance();
    ListSpaceObstaculo *listSpaceObstaculo = ListSpaceObstaculo::getInstance();
    ListTiroJogador    *listTiroJogador    = ListTiroJogador::getInstance();
    ListTiroInimigo    *listTiroInimigo    = ListTiroInimigo::getInstance();
    ListItem           *listItem           = ListItem::getInstance();

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
    tiles->camera.runUp(nave->getVelocidade());
    tiles->desenhar();

    if (ultimoQuadro==false){
        if (tiles->camera.isTop()){
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
void FaseAbstract::desenharPainel()
{
	moldura->desenhar();
    status->desenharStatus(nave->getVelocidade(),nave->getEscudo(),nave->getTorpedo());
    status->desenharInformacoes(placar->getPontos(),tiles->getTotalScrollVertical(),tiles->getDistanciaScrollVertical());
}



