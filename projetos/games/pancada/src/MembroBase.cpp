
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
	sprite->setDirecao(GBF::Imagem::Sprite::DR_CIMA);
}
void MembroBase::setBaixo()
{
	sprite->setDirecao(GBF::Imagem::Sprite::DR_BAIXO);
}
void MembroBase::setSprite(GBF::Imagem::Sprite::SpritePersonagem * sprite)
{
    this->sprite=sprite;
}
GBF::Area MembroBase::getArea()
{
	GBF::Area a;
	GBF::Dimensao d = sprite->getTamanho();

	a.right  = d.w;
	a.bottom = d.h;
	a.top    = posicao.y;
	a.left   = posicao.x;

	return a;
}
GBF::Ponto MembroBase::getPosicao()
{
	return posicao;
}
void MembroBase::desenhar()
{
	sprite->desenhar(posicao.x,posicao.y);
}
