
#include "MembroBase.h"

MembroBase::MembroBase(){
	posicao.x=0;
	posicao.y=0;
	
    sprite=NULL;
}

MembroBase::~MembroBase(){
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
