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
#ifndef _LISTTIROJOGADOR_H
#define _LISTTIROJOGADOR_H

#include <GBF/PSEfeitoEsferico.h>
#include <GBF/PSManager.h>

#include "ListTiroAbstract.h"
#include "SpaceObject.h"
#include "Placar.h"
#include "EfeitoExplosao.h"

class ListTiroJogador : public ListTiroAbstract
{
public:
    /** Destrutor */
    virtual ~ListTiroJogador();
    /** Retorna a instancia da classe*/
    static ListTiroJogador* getInstance();
    /** Verifica colis�o de uma lista com outra lista de objetos (SOBREESCRITO)*/
    void colisao(Personagem::ListPersonagem* objeto);
    /** Verifica colis�o de uma lista com apenas um objeto (SOBREESCRITO)*/
    void colisao(Personagem::Personagem* objeto);

protected:
    /** Construtor */
    ListTiroJogador();
	/** Instancia da classe (SINGLETON)*/
    static ListTiroJogador* instance;
    /** Referencia ao gerenciador de particulas*/
    static ParticleSystem::PSManager* particleManager;

private:
    /** Referencia ao objeto singleton Placar */
    Placar *placar;

};

#endif
