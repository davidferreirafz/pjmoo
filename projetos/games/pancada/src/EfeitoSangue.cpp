
#include "EfeitoSangue.h"

GraphicSystemImageBufferManager * EfeitoSangue::gsImageBufferManager;

EfeitoSangue::~EfeitoSangue()
{
//    if (sprite){
//        delete(sprite)
//    }
}
EfeitoSangue::EfeitoSangue()
{
    if (gsImageBufferManager==NULL){
        gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }
}

void EfeitoSangue::executar()
{
    for (int i=lista.size()-1; i>=0; i--){
        if (lista[i]->isAnimacaoFim()){
            delete lista[i];
            lista[i]=NULL;
            lista.erase(lista.begin()+i);
        }
    }
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

