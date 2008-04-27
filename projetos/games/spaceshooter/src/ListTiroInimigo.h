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
#ifndef _LISTTIROINIMIGO_H
#define _LISTTIROINIMIGO_H

#include "ListTiroAbstract.h"
#include "SpaceObject.h"


class ListTiroInimigo : public ListTiroAbstract
{
public:
    /** Destrutor */
    virtual ~ListTiroInimigo();
    /** Retorna a instancia da classe*/
    static ListTiroInimigo* getInstance();
    /** Verifica colis�o de uma lista com outra lista de objetos (SOBREESCRITO)*/
    void colisao(ListPersonagemAbstract* objeto); 
    /** Verifica colis�o de uma lista com apenas um objeto (SOBREESCRITO)*/
    void colisao(PersonagemAbstract* objeto);
    
protected:
    /** Construtor */
    ListTiroInimigo();
    /** Instancia da classe (SINGLETON)*/
    static ListTiroInimigo* instance;

private:

};

#endif
