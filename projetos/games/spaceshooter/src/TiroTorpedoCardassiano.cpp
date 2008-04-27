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
#include "TiroTorpedoCardassiano.h"

TiroTorpedoCardassiano::TiroTorpedoCardassiano(int X, int Y,TorpedoCardassiano tiro)
{
    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("armas"));
    if (adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(29,34,14,14,2,4))){
        setPosicao(X,Y);
        setTiro(tiro);
    }
    delete (spriteFactory);
}
TiroTorpedoCardassiano::~TiroTorpedoCardassiano()
{
}
void TiroTorpedoCardassiano::setTiro(TorpedoCardassiano tiro)
{
    switch(tiro){
        case UP:
    		path = new PathUp();
            break;
        case LEFT:
            path = new PathLeft();
            break;
        case RIGHT:
    		path = new PathRight();
            break;
        case DOWN:
    		path = new PathDown();
            break;
    }
}
