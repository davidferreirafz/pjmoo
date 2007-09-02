
#include "FaseAbstract.h"

WriteSystemManager * FaseAbstract::wsManager;
ParticleSystemManager * FaseAbstract::particleManager;

FaseAbstract::FaseAbstract()
{
	//informa tempo por round
	cronometroAuxiliar.setTempoOriginal(6);

	lutadorPlayer = NULL;
	lutadorPC     = NULL;
	ringue        = FrameLayerManager::getInstance()->getFrameLayer("ringue");

    eRound=ROUND_NULL;

    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }

    if (particleManager==NULL){
        particleManager = ParticleSystemManager::getInstance();
    }

    Area areaRingue;
    areaRingue.top    =  34;
    areaRingue.bottom = 469;
    areaRingue.left   =  28;
    areaRingue.right  = 611;

	LutadorAbstract::setRingue(areaRingue);

    primeiroRound();
}
FaseAbstract::~FaseAbstract()
{
    if (lutadorPlayer){
    	delete(lutadorPlayer);
    }
    if (lutadorPC){
    	delete(lutadorPC);
    }
    if (ringue){
	    ringue=NULL;
    }
}
bool FaseAbstract::isGameOver()
{
    bool perdeu = false;

    if (((lutadorPlayer->isNocaute())&&(cronometroAuxiliar.isTerminou())) ||
       ((round.isUltimo()) && (placar.isTempoTerminou()) && (placar.isPCGanhou()))){
        perdeu = true;
    }

    return perdeu;
}
bool FaseAbstract::isFaseFinalizada()
{
    bool finalizou = false;

    if (((lutadorPC->isNocaute())&&(cronometroAuxiliar.isTerminou())) ||
       ((round.isUltimo()) && (placar.isTempoTerminou()) && (placar.isPlayerGanhou()))){
        finalizou = true;
    }

    return finalizou;
}
bool FaseAbstract::isFimRound()
{
    if (placar.isTempoTerminou()){
        return true;
    } else {
        return false;
    }
}
bool FaseAbstract::isProximoRound()
{
    //mecanismo para evitar empate em numero de rounds
    bool proximo = true;

    if ((round.isUltimo())&&((placar.isPlayerGanhou())||(placar.isPCGanhou()))){
        proximo = false;
    }
   // return proximo;
   //return (!round.isUltimo());
}
void FaseAbstract::primeiroRound()
{
    round.setPrimeiro();
    placar.iniciar();
    cronometroAuxiliar.setResetar();
}
void FaseAbstract::proximoRound()
{
    if (!round.isUltimo()){
//    if ((!round.isUltimo())||
//    ((round.isUltimo())&&((!placar.isPlayerGanhou())&&(!placar.isPCGanhou())))
//    ){
        round.proximo();
		placar.iniciarRound();
    } else if (round.isUltimo()){

        if ((!placar.isPlayerGanhou())||(!placar.isPCGanhou())){
            round.proximo();
            placar.iniciarRound();
        }
    }
}
int FaseAbstract::getRound()
{
	return int(round.get());
}
void FaseAbstract::executar(InputSystem * input)
{
    //Movimenta os lutadores
	lutadorPlayer->mover(input,lutadorPC);
	lutadorPC->mover(input,lutadorPlayer);
	//coloca um de frente pro outro, escolher nome melhor
	ordenacao();

	//Verifica socos e contagem de pontos
	if (lutadorPlayer->socouAdversario(lutadorPC)){
		placar.adicionarPontoPlayer();
	}
	if (lutadorPC->socouAdversario(lutadorPlayer)){
		placar.adicionarPontoPC();
	}
    //executa o cronometro
    placar.processarTempo();
    particleManager->executar();
}
void FaseAbstract::desenhar()
{
    ringue->desenhar();

	//desenha lutadores
	lutadorPlayer->desenhar();
	lutadorPC->desenhar();

	//desenha efeitos especiais
	particleManager->desenhar();

    placar.desenhar();
}
// so para virar de costas corretamente
void FaseAbstract::ordenacao()
{
	Ponto pc     = lutadorPC->getPosicao();
	Ponto player = lutadorPlayer->getPosicao();

	if (player.y <= pc.y){
		lutadorPlayer->olharBaixo();
		lutadorPC->olharCima();
	} else {
		lutadorPlayer->olharCima();
		lutadorPC->olharBaixo();
	}
}

bool FaseAbstract::isNocaute()
{
    bool nocaute = false;

    if ((lutadorPlayer->isNocaute())||(lutadorPC->isNocaute())){
        nocaute = true;
        cronometroAuxiliar.processar();
    }

    return nocaute;
}
