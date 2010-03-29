
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
	sprite->setDirection(GBF::Image::Sprite::DR_CIMA);
}
void MembroBase::setBaixo()
{
	sprite->setDirection(GBF::Image::Sprite::DR_BAIXO);
}
void MembroBase::setSprite(GBF::Image::Sprite::SpriteCharacter * sprite)
{
    this->sprite=sprite;
}
GBF::Area MembroBase::getArea()
{
	GBF::Area a;
	GBF::Dimension d = sprite->getTamanho();

	a.right  = d.w;
	a.bottom = d.h;
	a.top    = posicao.y;
	a.left   = posicao.x;

	return a;
}
GBF::Point MembroBase::getPosicao()
{
	return posicao;
}
void MembroBase::desenhar()
{
	sprite->draw(posicao.x,posicao.y);
}
