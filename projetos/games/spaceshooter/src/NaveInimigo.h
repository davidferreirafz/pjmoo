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
#ifndef _NAVEINIMIGO_H
#define _NAVEINIMIGO_H


#include <GBF/ParticleSystemManager.h>

#include "NaveAbstract.h"
#include "PathFactory.h"
#include "PathStrategy.h"
#include "ListTiroInimigo.h"
#include "EfeitoExplosao.h"


class NaveInimigo : public NaveAbstract
{
public:
    /** Construtor */
    NaveInimigo();
    /** Destrutor */
    virtual ~NaveInimigo();
    virtual void acao(InputSystem* INPUT=NULL);
    /** Desenha a nave na tela*/
    virtual void desenhar();
    /** Seta se a nave esta viva(ou seja, se não foi destruida) */
    virtual void setVivo(bool VALOR);
	static void setListTiro(ListTiroInimigo* list);
	virtual void choque(int forca);
	virtual int tipoClasse();

protected:
    /** Objeto que armazena os tiros da nave*/
	static ListTiroInimigo* listTiro;
	/** Objeto que move a nave*/
	PathStrategy *path;
	/** Direção para onde a nave esta indo*/
    DIRECAO direcao;
    /** Checa Status das armas*/
    void checarArma();
    /** Efetua verificação para disparar Phaser*/
    virtual void prepararPhaser();
    /** Efetua verificação para disparar Torpedo*/
    virtual void prepararTorpedo();
    /** Seleciona posicao inicial da nave*/
    void selecionarPosicao();
    /** Muda caminho para um randomico */
    void caminho();
    /** Muda caminho para uma determinada direção */
    void caminho(DIRECAO dir);
    /** Referencia ao gerenciador de particulas*/
    static ParticleSystemManager* particleManager;
private:

};

#endif
