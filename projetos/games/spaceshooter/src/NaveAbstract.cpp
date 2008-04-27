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
#include "NaveAbstract.h"


SoundSystem* NaveAbstract::soundSystem=NULL;
int NaveAbstract::velocidadeBase=0;
void NaveAbstract::setVelocidadeBase(int velocidadeBase)
{
    NaveAbstract::velocidadeBase=velocidadeBase;
}	
NaveAbstract::NaveAbstract()
{
    espera.tiroA = 30;
    espera.tiroB = 30;
    espera.tiroC = 30;
    espera.tiroD = 30;

    sistema.escudo.maximo = 0;
    sistema.escudo.atual  = 0;

    sistema.arma.phaser  = 0;
    sistema.arma.plasma  = 0;
    sistema.arma.torpedo = 0;

    sistema.velocidade.eMaxima  = VELOCIDADE_DOBRA_01;
    sistema.velocidade.eAtual   = VELOCIDADE_DOBRA_01;
    
    sistema.velocidade.eDisponivel = sistema.velocidade.eAtual;

	if (!soundSystem){
		soundSystem = SoundSystem::getInstance();    
	}
}
NaveAbstract::~NaveAbstract()
{

}
int NaveAbstract::getEscudo()
{
    return sistema.escudo.atual;
}
int NaveAbstract::getTorpedo()
{
    return sistema.arma.torpedo;
}
int NaveAbstract::getPhaser()
{
    return sistema.arma.phaser;
}
int NaveAbstract::getPlasma()
{
    return sistema.arma.plasma;
}
int  NaveAbstract::getVelocidade()
{
    return sistema.velocidade.eAtual;
}
int NaveAbstract::getVelocidadeBase()
{
    return velocidadeBase;
}
Sistema NaveAbstract::getSistema()
{
    return sistema;
}
void NaveAbstract::setSistema(Sistema sistema)
{
    if (this->sistema.escudo.atual<sistema.escudo.atual){
        this->sistema.escudo.atual=sistema.escudo.atual;
    }
    if (this->sistema.arma.torpedo<sistema.arma.torpedo){
        this->sistema.arma.torpedo=sistema.arma.torpedo;
    }
    if (this->sistema.velocidade.eDisponivel<sistema.velocidade.eDisponivel){
        this->sistema.velocidade.eDisponivel=sistema.velocidade.eDisponivel;
        this->sistema.velocidade.eAtual=sistema.velocidade.eAtual;
    }        
}




