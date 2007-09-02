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

void StatusPlayer::desenhar(int pontos, int round, int energia)
{
    painel->desenhar(0,0);
    pontuacao->desenhar(45,0);

    for (int se=0;((se<energia)&&(se<83));se++){
        statusEnergia->desenhar(7,253-(2*se));
	}

    wsManager->escrever("kiloton16",52,18,"%03d",pontos);
    wsManager->escrever("kiloton16",6,64, "%02d",round);
}

