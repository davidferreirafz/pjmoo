
#include "Placar.h"

Placar::Placar()
{
    statusPlayer = new StatusPlayer();
    statusPC     = new StatusPC();
    statusTempo  = new StatusTempo();

	cronometroRound.setTempoOriginal(60);

    zerar();
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

//* Pontos do PC
int Placar::getPontosPC()
{
	return pontos.pc;
}
//* Pontos do Jogador
int Placar::getPontosPlayer()
{
	return pontos.player;
}

void Placar::adicionarPontoPC()
{
	pontos.pc++;
}
void Placar::adicionarPontoPlayer()
{
	pontos.player++;
}
void Placar::zerar()
{
	pontos.pc      = 0;
	pontos.player  = 0;

    cronometroRound.setResetar();
}
void Placar::desenhar()
{
    statusPlayer->desenhar(pontos.player,rand()%10);
    statusPC->desenhar(pontos.pc,rand()%10);
    statusTempo->desenhar(cronometroRound.getTempo());
}
bool Placar::isPlayerGanhou()
{
    return (pontos.player>pontos.pc);
}
bool Placar::isPCGanhou()
{
    return (pontos.player<pontos.pc);
}
void Placar::processarTempo()
{
    cronometroRound.processar();
}
bool Placar::isTempoTerminou()
{
    return cronometroRound.isTerminou();
}
