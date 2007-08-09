#include "Status.h"


Placar * Status::placar=NULL;
WriteSystemManager * Status::wsManager = NULL;

Status::Status()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("interface"));

    pontuacao = spriteFactory->criarSpriteItem(0,306,62,44,1,1);

    delete(spriteFactory);

    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }
}

Status::~Status()
{
    if (painel){
        delete(painel);
    }
    if (pontuacao){
        delete(pontuacao);
    }
    placar = NULL;
}

void Status::setPlacar(Placar *placar)
{
    Status::placar=placar;
}

