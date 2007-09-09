
#include "HUDTempo.h"

HUDTempo::HUDTempo(){

    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(0,265,92,40,1,1);

    delete(spriteFactory);
}

HUDTempo::~HUDTempo(){

    //dtor
}

void HUDTempo::desenhar(int tempo) 
{
    painel->desenhar(274,0);
    wsManager->escrever("kiloton24",298,11,"%02d",tempo);
}
