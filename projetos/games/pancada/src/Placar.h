
#ifndef _PLACAR_H
#define _PLACAR_H

#include <GBF/TimerSystemCronometroDecrescente.h>


#include "Status.h"
#include "StatusPlayer.h"
#include "StatusPC.h"
#include "StatusTempo.h"

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
    ContagemPontos pontos;
    ContagemRound round;
    TimerSystemCronometroDecrescente cronometroRound;

    Status *statusPlayer;
    Status *statusPC;
    StatusTempo *statusTempo;

  public:
    Placar();

    virtual ~Placar();

    void iniciar();
    void iniciarRound();

    // Pontos do PC
    int getPontosPC();

    // Pontos do Jogador
    int getPontosPlayer();

    void adicionarPontoPC();

    void adicionarPontoPlayer();

    void desenhar();

    bool isPlayerGanhou();
    bool isPCGanhou();

    void processarTempo();
    bool isTempoTerminou();

  protected:



};
#endif
