/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa � um software livre; voc� pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licen�a P�blica Geral (GPL) GNU      *
 *   como publicada pela Funda��o do Software Livre (FSF); na vers�o 2 da  *
 *   Licen�a.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _NAVEABSTRACT_H
#define _NAVEABSTRACT_H

#include <GBF/GBF.h>
#include <GBF/LayerManager.h>
#include <GBF/SoundSystem.h>
#include <GBF/Personagem.h>

#include "TiroAbstract.h"
#include "SpaceObject.h"

enum EnumVelocidadeDobra
{
    VELOCIDADE_DOBRA_01 = 1,
    VELOCIDADE_DOBRA_02 = 2,
    VELOCIDADE_DOBRA_03 = 3,
    VELOCIDADE_DOBRA_04 = 4,
    VELOCIDADE_DOBRA_05 = 5,
    VELOCIDADE_DOBRA_06 = 6,
    VELOCIDADE_DOBRA_07 = 7,
    VELOCIDADE_DOBRA_08 = 8,
    VELOCIDADE_DOBRA_09 = 9
};

struct Sistema
{
    struct Escudo
    {
        int maximo;
        int atual;
    };

    struct Arma
    {
        int torpedo;
        int phaser;
        int plasma;
    };

    struct Velocidade
    {
        EnumVelocidadeDobra eMaxima;
        EnumVelocidadeDobra eAtual;
        EnumVelocidadeDobra eDisponivel;
    };

    Arma arma;
    Escudo escudo;
    Velocidade velocidade;

};

class NaveAbstract : public SpaceObject
{
public:
    NaveAbstract();
    virtual ~NaveAbstract();
    /* Pega o Valor do Escudo */
    int getEscudo();
    int getTorpedo();
    int getPhaser();
    int getPlasma();
    /** Retorna a velocidade atual*/
    int getVelocidade();


	static void setVelocidadeBase(int velocidadeBase);

	Sistema getSistema();
	void setSistema(Sistema sistema);

protected:
    int getVelocidadeBase();
    virtual void checarArma()=0;
    virtual void dispararPhaser()=0;
    virtual void dispararTorpedo()=0;
    virtual void prepararPhaser()=0;
    virtual void prepararTorpedo()=0;
    virtual void selecionarPosicao()=0;

    ::Personagem::TypeDelay espera;

    Sistema sistema;
	static GBF::Kernel::Sound::SoundSystem * soundSystem;

private:
	static int velocidadeBase;

};

#endif
