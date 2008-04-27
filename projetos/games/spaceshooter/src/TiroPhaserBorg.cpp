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
#include "TiroPhaserBorg.h"

TiroPhaserBorg::TiroPhaserBorg(int X, int Y,PhaserBorg tiro)
{
    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("armas"));
    if (adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(58,34,14,14,2,2))){
        setPosicao(X,Y);
        setTiro(tiro);
    }
    delete (spriteFactory);
}
TiroPhaserBorg::~TiroPhaserBorg()
{
}
void TiroPhaserBorg::setTiro(PhaserBorg tiro)
{
    switch(tiro){
        case UP:
    		path = new PathUp();
            break;
        case DOWN:
    		path = new PathDown();
            break;
        case LEFT:
            path = new PathLeft();
            break;
        case RIGHT:
    		path = new PathRight();
            break;
    }
}
