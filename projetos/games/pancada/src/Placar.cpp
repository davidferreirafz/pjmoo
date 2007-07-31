
#include "Placar.h"

Placar::Placar() 
{
    zerar();
}
Placar::~Placar(){

}

//* Pontos do PC
int Placar::getPontosPC() 
{

	return pontosPC;
}
//* Pontos do Jogador
int Placar::getPontosPlayer() 
{

	return pontosPlayer;
}
//* Soma dos pontos do lutador 
int Placar::getPontosRecorde() 
{
	return 0;//pontosRecorde;
}
void Placar::adicionarPontoPC() 
{

	pontosPC++;
}
void Placar::adicionarPontoPlayer() 
{

	pontosPlayer++;
}
void Placar::zerar() 
{
	pontosPC      = 0;
	pontosPlayer  = 0;
	//pontosRecorde = 0;	
}
