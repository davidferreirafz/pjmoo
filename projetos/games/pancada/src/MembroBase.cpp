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

#include "MembroBase.h"

MembroBase::MembroBase() 
{
	posicao.x=0;
	posicao.y=0;
	
    sprite=NULL;
}
MembroBase::~MembroBase() 
{
	if (sprite!=NULL){
		delete(sprite);
	}
}
void MembroBase::setCima() 
{
	sprite->setDirecao(DR_CIMA);
}
void MembroBase::setBaixo() 
{
	sprite->setDirecao(DR_BAIXO);
}
void MembroBase::setSprite(SpritePersonagem * sprite) 
{
    this->sprite=sprite;
}
Area MembroBase::getArea() 
{
	Area a;
	Dimensao d = sprite->getTamanho();
	
	a.right  = d.w;
	a.bottom = d.h;
	a.top    = posicao.y;
	a.left   = posicao.x;
	
	return a;
}
Ponto MembroBase::getPosicao() 
{
	return posicao;
}
void MembroBase::desenhar() 
{
	sprite->desenhar(posicao.x,posicao.y);
}
