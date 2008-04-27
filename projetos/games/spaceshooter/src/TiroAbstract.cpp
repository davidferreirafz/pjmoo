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
#include "TiroAbstract.h"

GraphicSystemImageBufferManager * TiroAbstract::gsImageBufferManager = NULL;
TiroAbstract::TiroAbstract()
{
	//Potencia do Tiro, deve ser configurada em classes herdeiras
	potencia   = POTENCIA_NULL;
	//Velocidade do Tiro, deve ser configurada em classes herdeiras
	velocidade = VELOCIDADE_NULL;

	if (gsImageBufferManager==NULL){
	    gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }
}
TiroAbstract::~TiroAbstract()
{
    if (path!=NULL){
        delete(path);
    }
}
int TiroAbstract::getPotencia()
{
    return potencia;
}
void TiroAbstract::acao(InputSystem* INPUT)
{
    if (isAtivo()){
        if (isVivo()){
            if (path->mover(velocidade,&posicao,getDimensao())){
                setAtivo(false);
            }
        } else {
            setAtivo(false);
        }
    }
}

