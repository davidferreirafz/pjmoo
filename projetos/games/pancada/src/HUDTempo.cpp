
#include "HUDTempo.h"

HUDTempo::HUDTempo(){

    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("interface"));

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
