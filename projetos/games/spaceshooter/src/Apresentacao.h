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
#ifndef _APRESENTACAO_H_
#define _APRESENTACAO_H_

#include <GBF/WriteSystemManager.h>
#include <GBF/WriteSystemFontDefault.h>
#include <GBF/FrameLayerManager.h>
#include <GBF/TimerSystemCronometroDecrescente.h>
#include <GBF/GraphicSystemGFX.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>


// Classe para criação da apresentação inicial do jogo
class Apresentacao
{
public:
	virtual ~Apresentacao();
	Apresentacao();
    bool executar();

    void preTela();

	void tela01();
	void tela02();
	void tela03();
	void tela04();
	void tela05();
	void tela06();
	void tela07();
	void tela08();
	void tela09();
	void reset();


protected:
    WriteSystemManager* wsManager;
    FrameLayerManager*  flManager;
    GraphicSystemGFX*   gsGFX;
    int numeroTela;
    TimerSystemCronometroDecrescente tempo;

    SpriteItem* zangoesBorg;
    SpriteItem* terra;
    SpriteItem* babyBorg;
    SpriteItem* logoInimigos;
    SpriteItem* naveDefiant;
    SpriteItem* naveEsquemas;
    SpriteItem* batalha;
    SpriteItem* naveBorg;
    SpriteItem* david;
};

#endif


