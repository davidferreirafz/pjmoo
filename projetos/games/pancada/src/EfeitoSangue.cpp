
#include "EfeitoSangue.h"


EfeitoSangue::~EfeitoSangue()
{

}
EfeitoSangue::EfeitoSangue()
{

}

void EfeitoSangue::executar()
{

}

void EfeitoSangue::criar(int x, int y)
{
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));

    SpritePersonagem *sprite=spriteFactory->criarSpritePersonagem(474,77,22,23,6,2);
	sprite->setAutomatico(true);
    sprite->setPosicao(x,y);

    lista.push_back(sprite);

	delete(spriteFactory);
}

