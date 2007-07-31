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

#include "LuvaAbstract.h"

//Construtor 
LuvaAbstract::LuvaAbstract() 
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory    *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem")); 

    sprite=spriteFactory->criarSpritePersonagem(0,231,76,84,1,1);   
    sprite->setQtdDirecoes(2);
        
	delete(spriteFactory);


	setSoco(false);
}
//Destrutor 
LuvaAbstract::~LuvaAbstract() 
{
}
void LuvaAbstract::setSoco(bool soco) 
{
	this->soco=soco;
}
bool LuvaAbstract::isSoco() 
{
	return soco;
}
bool LuvaAbstract::isLuvaDireita() 
{
	if (eLuva==LUVA_DIREITA){
		return true;
	} else {
		return false;
	}
}
bool LuvaAbstract::isLuvaEsquerda() 
{
	if (eLuva==LUVA_ESQUERDA){
		return true;
	} else {
		return false;
	}
}
