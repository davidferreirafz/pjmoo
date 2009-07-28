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
#include "FaseSete.h"

FaseSete::FaseSete()
{
	delay.acao  = 10;
	delay.tiroA = 10;

    zona    = "fase_7_zona";
    missao  = "fase_7_missao";
    inimigo = "fase_7_inimigo";

    areaZona.left   =  59;
    areaZona.top    =  22;
    areaZona.bottom =  50;
    areaZona.right  = 518;

    matouChefe = false;
}
FaseSete::~FaseSete()
{
//Classe FaseAbstract remove o som da 'fase'
    soundSystem->fxManager->apagar("borgmsg");
    soundSystem->musicManager->stop("chefe");
    soundSystem->musicManager->apagar("chefe");
    soundSystem->musicManager->stop("final");
    soundSystem->musicManager->apagar("final");
    GBF::Kernel::Graphic::GraphicSystem::getInstance()->imageBufferManager->apagar("personagem_borg");
}
void FaseSete::configurar()
{
    tileSpace->setFrame(0,0,480,448);
    tileSpace->setTiles(15,60);
    tileSpace->setPixelTile(32,32);
    tileSpace->iniciarRandomico(8);

    GBF::Kernel::Graphic::GraphicSystem  *graphicSystem = GBF::Kernel::Graphic::GraphicSystem::getInstance();
    graphicSystem->imageBufferManager->carregar("personagem_borg","data//imagem//spaceshooter_borg.png");

    soundSystem->musicManager->carregar("fase","data//som//007.ogg");
    soundSystem->musicManager->carregar("chefe","data//som//007-01.ogg");
    soundSystem->musicManager->carregar("final","data//som//final.ogg");
    soundSystem->fxManager->carregar("borgmsg","data//som//borgmsg.ogg");
    soundSystem->fxManager->setVolume("borgmsg",40);
}
void FaseSete::iniciar()
{
    tileSpace->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(10);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = true;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = true;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    soundSystem->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::ENTERPRISE_E);
}
void FaseSete::condicaoNavegandoFase()
{
    delay.acao--;
    if (delay.acao<=0){
        delay.acao=100;
        ListSpaceInimigo::getInstance()->adicionar(new NaveMiniBorg());
    }
}
void FaseSete::condicaoUnicaUltimoQuadro()
{
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    soundSystem->musicManager->playInfinity("chefe");
    ListSpaceInimigo::getInstance()->adicionar(new NaveBorg());
}
bool FaseSete::isTerminou()
{
	bool terminou = false;

	if ((tileSpace->camera.isTop())&&(ListSpaceInimigo::getInstance()->size()==0)){
		if (nave->getPosicao().y==0){
            terminou=true;
		} else {
			//criação do efeito de fogos de artificio
            if (particleManager->size()<4) {
                ParticleSystem::PSEfeitoEsferico* efeito  = new EfeitoFogosDeArtificio();
                efeito->setQuantidade(200);
                efeito->setRaio(400);
                efeito->criar(rand()%480,rand()%480);
                particleManager->adicionar(efeito);
            } else if (matouChefe==false){
                matouChefe=true;
                soundSystem->musicManager->playInfinity("final");
            }
		}
	}
	return terminou;
}
void FaseSete::hookMensagemFinal()
{
    if (matouChefe){
        writeManager->escreverLocalizado("texto",0,458,"msg_continue_avancado");
    }
}
std::string FaseSete::getMissaoCompleta()
{
	return "Fase 7";
}
