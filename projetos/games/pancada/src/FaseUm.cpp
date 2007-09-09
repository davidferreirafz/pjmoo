
#include "FaseUm.h"

FaseUm::FaseUm()
{
	//Player, jogador humano
	if (lutadorPlayer==NULL){
    	lutadorPlayer = new LutadorPlayer();
    }
	//PC, jogador automático
	if (lutadorPC==NULL){
    	lutadorPC = new LutadorPC();
    }

    round.setMaximo(3);
}

FaseUm::~FaseUm()
{

}

void FaseUm::iniciar()
{
    SoundSystem::getInstance()->musicManager->playInfinity("fundo");

    lutadorPC->iniciar(243,20);
    lutadorPlayer->iniciar(243,404);

//    cronometroRound.setResetar();
    cronometroAuxiliar.setResetar();
}
