//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
//***************************************************************************
//    Este programa � software livre; voc� pode redistribu�-lo e/ou
//    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a vers�o 2 da
//    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "CabecaFactory.h"

CabecaFactory::CabecaFactory(){
//n�o implementado
}

CabecaFactory::~CabecaFactory(){
//n�o implementado
}

Cabeca * CabecaFactory::criar(TipoLutador tipo)
{
    GBF::Image::SpriteFactory * spriteFactory = new GBF::Image::SpriteFactory("personagem");
    GBF::Image::Sprite::SpriteCharacter * sprite = NULL;

	switch (tipo)
	{
		case Skar:
                sprite=spriteFactory->createSpriteCharacter(237,231,59,76,2,10);
			break;
		case Cobra:
				sprite=spriteFactory->createSpriteCharacter(237,154,59,76,2,10);
			break;
		case Punk:
				sprite=spriteFactory->createSpriteCharacter(237,77,59,76,2,10);
			break;
		case Mascarado:
				sprite=spriteFactory->createSpriteCharacter(0,154,59,76,2,10);
			break;
		case FZ:
		default:
				sprite=spriteFactory->createSpriteCharacter(0,77,59,76,2,10);
			break;
	}

	delete(spriteFactory);

    sprite->setQtdDirecoes(2);

    Cabeca *cabeca = new Cabeca();
	cabeca->setSprite(sprite);

	return cabeca;
}
