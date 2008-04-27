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
#include "ItemAbstract.h"


ItemAbstract::ItemAbstract()
{
    bonus = 1;
}
ItemAbstract::~ItemAbstract()
{
	//sprite=NULL;
    if (path){
        delete (path);
        path = NULL;
    }
}
void ItemAbstract::acao(InputSystem* INPUT)
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
void ItemAbstract::selecionarPosicao()
{
    Dimensao dimensao = getDimensao();
    setPosicao(area.left+(rand()%((area.right-dimensao.w)-area.left)),area.top-dimensao.h);
}
int ItemAbstract::getBonus()
{
    return bonus;
}
void ItemAbstract::choque(int forca)
{
    forca=0;
}

