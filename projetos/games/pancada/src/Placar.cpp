
#include "Placar.h"

Placar::Placar()
{
    statusPlayer = new StatusPlayer();
    statusPC = new StatusPC();
    statusTempo = new StatusTempo();

	cronometroRound.setTempoOriginal(6);
}
Placar::~Placar()
{
    if (statusPlayer){
        delete(statusPlayer);
    }
    if (statusPC){
        delete(statusPC);
    }
    if (statusTempo){
        delete(statusTempo);
    }
}

void Placar::adicionarPontoPC()
{
	pontos.pc++;
}
void Placar::adicionarPontoPlayer()
{
	pontos.player++;
}
void Placar::desenhar()
{
    statusPlayer->desenhar(pontos.player,round.player,100);
    statusPC->desenhar(pontos.pc,round.pc,60);
    statusTempo->desenhar(cronometroRound.getTempo());
}
bool Placar::isPlayerGanhou()
{
    if (round.player>round.pc){
        return true;
    } else {
        return false;
    }
}
bool Placar::isPCGanhou()
{
    if (round.pc>round.player){
        return true;
    } else {
        return false;
    }
}
void Placar::processarTempo()
{
    cronometroRound.processar();

    if (isTempoTerminou()){
        calcular();
    }
}
bool Placar::isTempoTerminou()
{
    return cronometroRound.isTerminou();
}
void Placar::iniciar()
{
	round.pc      = 0;
	round.player  = 0;
    iniciarRound();
}
void Placar::iniciarRound()
{
	pontos.pc      = 0;
	pontos.player  = 0;
    cronometroRound.setResetar();
}
void Placar::calcular()
{
    if (pontos.player>pontos.pc){
        round.player++;
    } else if (pontos.pc>pontos.player){
        round.pc++;
    }
}

