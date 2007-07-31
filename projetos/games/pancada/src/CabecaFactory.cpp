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
Cabeca * CabecaFactory::criar(int tipo) 
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory    *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    SpritePersonagem *sprite = NULL;

	switch (tipo)
	{
		case 5:
                sprite=spriteFactory->criarSpritePersonagem(237,231,59,76,2,10);
			break;	
		case 4:
				sprite=spriteFactory->criarSpritePersonagem(237,154,59,76,2,10);
			break;	
		case 3:
				sprite=spriteFactory->criarSpritePersonagem(0,154,59,76,2,10);
			break;		
		case 2:
				sprite=spriteFactory->criarSpritePersonagem(237,77,59,76,2,10);
			break;
		case 1: 
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
