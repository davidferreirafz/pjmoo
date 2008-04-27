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
    /** Verifica colisão de uma lista com outra lista de objetos (SOBREESCRITO)*/
    void colisao(ListPersonagemAbstract* objeto); 
    /** Verifica colisão de uma lista com apenas um objeto (SOBREESCRITO)*/
    void colisao(PersonagemAbstract* objeto);
    
protected:
    /** Construtor */
    ListTiroInimigo();
    /** Instancia da classe (SINGLETON)*/
    static ListTiroInimigo* instance;

private:

};

#endif
