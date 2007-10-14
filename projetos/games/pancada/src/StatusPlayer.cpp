
#include "StatusPlayer.h"

//Construtor

//Construtor
StatusPlayer::StatusPlayer(){

    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(0,0,45,264,1,1);

    delete(spriteFactory);
}

//Destrutor

//Destrutor
StatusPlayer::~StatusPlayer(){

}

//Desenha a barra de informações do jogador

//Desenha a barra de informações do jogador
void StatusPlayer::desenhar(int pontos, int round, int energia) 
{
    painel->desenhar(0,0);
    pontuacao->desenhar(45,0);

    int barraEnergia=int((energia*83)/100);

    for (int se=0;se<barraEnergia;se++){
        statusEnergia->desenhar(7,253-(2*se));
    }

    wsManager->escrever("kiloton16",52,18,"%03d",pontos);
    wsManager->escrever("kiloton16",6,64, "%02d",round);
}
