////    Pacanda - Based boxing game
////    Copyright (C) 2004-2006 David de Almeida Ferreira
////
////    This is free software; you can redistribute it and/or
////    modify it under the terms of the GNU General Public
////    License as published by the Free Software Foundation; either
////    version 2 of the License, or (at your option) any later version.
////
////    David de Almeida Ferreira (F-Z)
////        davidferreira@uol.com.br or davidferreira.fz@gmail.com
////        http://pjmoo.codigolivre.org.br
////////////////////////////////////////////////////////////////////////

#include "CabecaFactory.h"

CabecaFactory::CabecaFactory()
{
//não implementado
}
CabecaFactory::~CabecaFactory()
{
//não implementado
}
Cabeca * CabecaFactory::criar(TipoLutador tipo)
{
    GraphicSystem      *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory      *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("personagem"));
    SpritePersonagem   *sprite = NULL;

	switch (tipo)
	{
		case Skar:
                sprite=spriteFactory->criarSpritePersonagem(237,231,59,76,2,10);
			break;
		case Cobra:
				sprite=spriteFactory->criarSpritePersonagem(237,154,59,76,2,10);
			break;
		case Punk:
				sprite=spriteFactory->criarSpritePersonagem(237,77,59,76,2,10);
			break;
		case Mascarado:
				sprite=spriteFactory->criarSpritePersonagem(0,154,59,76,2,10);
			break;
		case FZ:
		default:
				sprite=spriteFactory->criarSpritePersonagem(0,77,59,76,2,10);
			break;
	}

	delete(spriteFactory);

    sprite->setQtdDirecoes(2);

    Cabeca *cabeca = new Cabeca();
	cabeca->setSprite(sprite);

	return cabeca;
}
