
#include "EfeitoSangue.h"

EfeitoSangue::~EfeitoSangue()
{
//não implementado
}
EfeitoSangue::EfeitoSangue()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    sprite=spriteFactory->criarSpritePersonagem(77,474,22,23,6,2);
	sprite->setAutomatico(true);
}

