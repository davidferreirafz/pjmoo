
#include "FaseAbstract.h"

WriteSystemManager * FaseAbstract::wsManager;

FaseAbstract::FaseAbstract()
{
	//informa tempo por round
	cronometroRound.setTempoOriginal(10);
	cronometroAuxiliar.setTempoOriginal(6);

	lutadorPlayer = NULL;
	lutadorPC     = NULL;
	ringue        = FrameLayerManager::getInstance()->getFrameLayer("ringue");
	status        = FrameLayerManager::getInstance()->getFrameLayer("status");

    eRound=ROUND_NULL;

    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }

	LutadorAbstract::setRingue(ringue->getArea());

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
    if (status){
        status=NULL;
    }
}
bool FaseAbstract::isGameOver()
{
    bool perdeu = false;
/*
    if ((eRound==ROUND_TRES)&&(cronometroRound.isTerminou())&&
        (placar.getPontosPlayer()<=placar.getPontosPC())){
        perdeu = true;
    }
*/
    if (((lutadorPlayer->isNocaute())&&(cronometroAuxiliar.isTerminou())) ||
       ((eRound==ROUND_TRES) && (cronometroRound.isTerminou()) && (placar.getPontosPlayer()<=placar.getPontosPC()))){
        perdeu = true;
    }

    return perdeu;
}
bool FaseAbstract::isFaseFinalizada()
{
    bool finalizou = false;
/*    if ((eRound==ROUND_TRES)&&(cronometroRound.isTerminou())&&
        (placar.getPontosPlayer()>placar.getPontosPC())){
        finalizou = true;
    }*/

    if (((lutadorPC->isNocaute())&&(cronometroAuxiliar.isTerminou())) ||
       ((eRound==ROUND_TRES) && (cronometroRound.isTerminou()) && (placar.getPontosPlayer()>placar.getPontosPC()))){
        finalizou = true;
    }

    return finalizou;
}
bool FaseAbstract::isFimRound()
{
    if (cronometroRound.isTerminou()){
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
}
void FaseAbstract::proximoRound()
{
	if (eRound!=ROUND_TRES){
		if (eRound==ROUND_UM){
			eRound=ROUND_DOIS;
		} else {
			eRound=ROUND_TRES;
		}
	}
}
//Retorna o valor do tempo
int FaseAbstract::getTempo()
{
    return cronometroRound.getTempo();
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
    cronometroRound.processar();
}
void FaseAbstract::desenhar()
{
    ringue->desenhar();
    status->desenhar();
	//desenha lutadores
	lutadorPlayer->desenhar();
	lutadorPC->desenhar();


    wsManager->escrever(WriteSystemFontDefault::pumpdemi,542,34,"TEMPO");
    wsManager->escrever(WriteSystemFontDefault::pumpdemi,572,62,"%02d",getTempo());
    //Lutador - PC
    wsManager->escrever(WriteSystemFontDefault::pumpdemi,542,110,"CPU");
    wsManager->escrever(WriteSystemFontDefault::pumpdemi,572,138,"%03d",placar.getPontosPC());
    //Lutador - Player
    wsManager->escrever(WriteSystemFontDefault::pumpdemi,542,168,"Player");
    wsManager->escrever(WriteSystemFontDefault::pumpdemi,572,198,"%03d",placar.getPontosPlayer());

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
