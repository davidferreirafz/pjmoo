#include "StatusPC.h"


StatusPC::StatusPC()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(45,0,45,264,1,1);

    delete(spriteFactory);
}

StatusPC::~StatusPC()
{
    //dtor
}

void StatusPC::desenhar(int pontos, int round)
{
    painel->desenhar(595,0);
    pontuacao->desenhar(534,0);
    wsManager->escrever("kiloton16",541,18,"%03d",pontos);
    wsManager->escrever("kiloton16",602,64, "%02d",round);
}

