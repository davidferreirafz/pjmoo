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
#include "FaseUm.h"


FaseUm::FaseUm()
{
    zona    = "fase_1_zona";
    missao  = "fase_1_missao";
    inimigo = "fase_1_inimigo";

    areaZona.left   =  59;
    areaZona.top    = 324;
    areaZona.bottom =  22;
    areaZona.right  = 518;

    wsManager = GBF::Kernel::Write::WriteManager::getInstance();

	tempoDica.setTempoOriginal(0);
	tempoDica.setUnidade(GBF::Kernel::Timer::TEMPO_SEGUNDO);
    tempoDica.setResetar();

    dicaSelecao=1;

}
FaseUm::~FaseUm()
{
//Classe FaseAbstract remove o som da 'fase'
}
void FaseUm::configurar()
{
    tiles->setFrame(0,0,480,480);
    tiles->setTiles(15,180);
    tiles->setPixelTile(32,32);
    tiles->iniciarRandomico(4);
    //tiles->iniciarArquivo(getPath()+"//data//mapa//tiles.fl");

    soundSystem->musicManager->carregar("fase","data//som//001.ogg");
}
void FaseUm::iniciar()
{
    tiles->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(12);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = true;
    ListSpaceObstaculo::OBSTACULO_MINA     = true;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    soundSystem->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::AUXILIAR);
}
void FaseUm::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
}
void FaseUm::condicaoNavegandoFase()
{
    char textoFormatado[30];
    tempoDica.processar();

    if (tempoDica.getTempo()>5){
        dicaSelecao++;
        if (dicaSelecao>18){
            dicaSelecao=1;
        }
        tempoDica.setResetar();
    }

    sprintf(textoFormatado,"dica_%02d",dicaSelecao);

    wsManager->escreverLocalizado("texto", 0,440,"msg_dica");
    wsManager->escreverLocalizado("texto",16,460,textoFormatado);
}
void FaseUm::ganchoUltimoQuadro()
{
    wsManager->escreverLocalizado("texto",100,460,"msg_continue_avancado");
}
bool FaseUm::isTerminou()
{
    if ((tiles->camera.isTop())&&(nave->getPosicao().y==0)){
        return true;
    } else {
        return false;
    }
}
std::string FaseUm::getMissaoCompleta()
{
	return "Fase 1";
}
