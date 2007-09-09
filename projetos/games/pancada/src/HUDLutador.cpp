
#include "HUDLutador.h"

//Construtor
HUDLutador::HUDLutador(){

    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("interface"));

    pontuacao     = spriteFactory->criarSpriteItem(0,306,62,44,1,1);
    statusEnergia = spriteFactory->criarSpriteItem(63,306,12,2,1,1);

    delete(spriteFactory);

}

//Destrutor
HUDLutador::~HUDLutador(){
    if (pontuacao){
        delete(pontuacao);
    }
}

