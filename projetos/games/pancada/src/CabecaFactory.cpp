
#include "CabecaFactory.h"

CabecaFactory::CabecaFactory(){
//não implementado
}

CabecaFactory::~CabecaFactory(){
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
