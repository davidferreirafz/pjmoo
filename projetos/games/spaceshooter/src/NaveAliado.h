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
#ifndef _NAVEALIADO_H
#define _NAVEALIADO_H

#include "ListTiroJogador.h"
#include "TiroPhaserFE.h"
#include "TiroPlasmaFE.h"
#include "TiroTorpedoFE.h"


#include "NaveAbstract.h"


class NaveAliado : public NaveAbstract
{
public:
    NaveAliado();
    virtual ~NaveAliado();
	static void setListTiro(ListTiroJogador* list);

    void acao(GBF::Kernel::Input::InputSystem * input=NULL);
    void desenhar();
    void setVivo(bool VALOR);
    void colisao(ListItem* listItem);
	void choque(int forca);
protected:
	static ListTiroJogador* listTiro;

    void limite();
    void selecionarPosicao();

private:
    bool atingido;
    int contagemChoque;

    void aumentarVelocidadeDobra();
    void reduzirVelocidadeDobra();
};

#endif





