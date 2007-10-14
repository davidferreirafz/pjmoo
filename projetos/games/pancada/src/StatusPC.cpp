
#include "StatusPC.h"

//Construtor

//Construtor
StatusPC::StatusPC(){
    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(45,0,45,264,1,1);

    delete(spriteFactory);
}

//Destrutor

//Destrutor
StatusPC::~StatusPC(){

    //dtor
}

//Desenha a barra de informações do PC

//Desenha a barra de informações do PC
void StatusPC::desenhar(int pontos, int round, int energia) 
{
    painel->desenhar(595,0);
    pontuacao->desenhar(534,0);

    int barraEnergia=int((energia*83)/100);

    for (int se=0;se<barraEnergia;se++){
        statusEnergia->desenhar(621,253-(2*se));
    }

    wsManager->escrever("kiloton16",541,18,"%03d",pontos);
    wsManager->escrever("kiloton16",602,64,"%02d",round);
}
