
#ifndef _PLACAR_H
#define _PLACAR_H

#include <GBF/TimerSystemCronometroDecrescente.h>


struct ContagemPontos
{
    int player;

    int pc;

};
struct ContagemRound
{
    int player;

    int pc;

};
class Placar
{
  private:
    TimerSystemCronometroDecrescente cronometroRound;

    ContagemPontos pontos;

    ContagemRound round;

    void calcular();


  public:
    //Construtor
    Placar();

    //Destrutor
    virtual ~Placar();

    void iniciar();

    void iniciarRound();

    void adicionarPontoPC();

    void adicionarPontoPlayer();

    bool isPlayerGanhou();

    bool isPCGanhou();

    bool isTempoTerminou();

    void processarTempo();

    //Retorna a pontuação do Computador
    int getPontosPC();

    //Retorna pontuação do Jogador
    int getPontosPlayer();

    //Retorna a quantidade de rounds que o Computador Ganhou
    int getRoundsPC();

    //Retorna a quantidade de rounds que o Jogador Ganhou
    int getRoundsPlayer();

    //Retorna o tempo restante para terminar o round
    int getRoundTempo();

};
#endif
