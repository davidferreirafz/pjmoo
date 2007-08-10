#include "StatusPlayer.h"


StatusPlayer::StatusPlayer()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(0,0,45,264,1,1);

    delete(spriteFactory);
}

StatusPlayer::~StatusPlayer()
{
    //dtor
}

void StatusPlayer::desenhar(int pontos, int round)
{
    painel->desenhar(0,0);
    pontuacao->desenhar(45,0);
    wsManager->escrever("kiloton16",52,18,"%03d",pontos);
    wsManager->escrever("kiloton16",6,64, "%02d",round);
}

