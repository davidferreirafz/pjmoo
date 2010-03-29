
#include "Placar.h"

void Placar::calcular()
{
    if (pontos.player>pontos.pc){
        round.player++;
    } else if (pontos.pc>pontos.player){
        round.pc++;
    }
}
//Construtor

//Construtor
Placar::Placar(){
    cronometroRound.setInitialTime(30);
}

//Destrutor

//Destrutor
Placar::~Placar(){
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
    cronometroRound.setReset();
}
void Placar::adicionarPontoPC()
{
	pontos.pc++;
}
void Placar::adicionarPontoPlayer()
{
	pontos.player++;
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
bool Placar::isTempoTerminou()
{
    return cronometroRound.isFinish();
}
void Placar::processarTempo()
{
    cronometroRound.update();

    if (isTempoTerminou()){
        calcular();
    }
}
//Retorna a pontuação do Computador

//Retorna a pontuação do Computador
int Placar::getPontosPC()
{
    return pontos.pc;
}
//Retorna pontuação do Jogador

//Retorna pontuação do Jogador
int Placar::getPontosPlayer()
{
    return pontos.player;
}
//Retorna a quantidade de rounds que o Computador Ganhou

//Retorna a quantidade de rounds que o Computador Ganhou
int Placar::getRoundsPC()
{
    return round.pc;
}
//Retorna a quantidade de rounds que o Jogador Ganhou

//Retorna a quantidade de rounds que o Jogador Ganhou
int Placar::getRoundsPlayer()
{
    return round.player;
}
//Retorna o tempo restante para terminar o round

//Retorna o tempo restante para terminar o round
int Placar::getRoundTempo()
{
    return cronometroRound.getTime();
}
