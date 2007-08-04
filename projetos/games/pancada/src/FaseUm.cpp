
#include "FaseUm.h"

FaseUm::FaseUm(){

	//Player, jogador humano
	if (lutadorPlayer==NULL){
    	lutadorPlayer = new LutadorPlayer();
    }
	//PC, jogador automático
	if (lutadorPC==NULL){
    	lutadorPC = new LutadorPC();
    }
}

FaseUm::~FaseUm(){


}

void FaseUm::iniciar()
{
    SoundSystem::getInstance()->musicManager->playInfinity("fundo");
    lutadorPC->setPosicao(200,0);
    lutadorPC->olharBaixo();

    lutadorPlayer->setPosicao(200,404);
    lutadorPlayer->olharCima();

    cronometroRound.setResetar();
    cronometroAuxiliar.setResetar();
}
