
#include "FaseAbstract.h"

WriteSystemManager * FaseAbstract::wsManager;

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
       ((eRound==ROUND_TRES) && (placar.isTempoTerminou()) && (placar.isPCGanhou()))){
        perdeu = true;
    }

    return perdeu;
}
bool FaseAbstract::isFaseFinalizada()
{
    bool finalizou = false;

    if (((lutadorPC->isNocaute())&&(cronometroAuxiliar.isTerminou())) ||
       ((eRound==ROUND_TRES) && (placar.isTempoTerminou()) && (placar.isPlayerGanhou()))){
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
	if (eRound!=ROUND_TRES){
		return true;
	} else {
		return false;
	}
}
void FaseAbstract::primeiroRound()
{
    eRound=ROUND_UM;
    placar.iniciar();
    cronometroAuxiliar.setResetar();
}
void FaseAbstract::proximoRound()
{
	if (eRound!=ROUND_TRES){
		if (eRound==ROUND_UM){
			eRound=ROUND_DOIS;
		} else {
			eRound=ROUND_TRES;
		}
		placar.iniciarRound();
	}
}
int FaseAbstract::getRound()
{
	return int(eRound);
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
}
void FaseAbstract::desenhar()
{
    ringue->desenhar();

	//desenha lutadores
	lutadorPlayer->desenhar();
	lutadorPC->desenhar();
    placar.desenhar();
    //-- falha ao desenhar

	//desenha efeitos especiais
	EfeitoContainer::getInstance()->desenhar();

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
