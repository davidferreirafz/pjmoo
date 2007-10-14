
#include "HUDLutador.h"

//Construtor

//Construtor
HUDLutador::HUDLutador(){

    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("interface"));

    pontuacao     = spriteFactory->criarSpriteItem(0,306,62,44,1,1);
    statusEnergia = spriteFactory->criarSpriteItem(63,306,12,2,1,1);

    delete(spriteFactory);

}

//Destrutor

//Destrutor
HUDLutador::~HUDLutador(){
    if (pontuacao){
        delete(pontuacao);
    }
}

