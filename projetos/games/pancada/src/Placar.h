
#ifndef _PLACAR_H
#define _PLACAR_H

#include <GBF/TopSystemRecorde.h>


class Placar
{
  protected:
    int pontosPC;

    int pontosPlayer;

    int pontosRecorde;

    TopSystemRecorde registroAtual;


  public:
    Placar();

    virtual ~Placar();

    //* Pontos do PC
    int getPontosPC();

    //* Pontos do Jogador
    int getPontosPlayer();

    //* Soma dos pontos do lutador 
    int getPontosRecorde();

    void adicionarPontoPC();

    void adicionarPontoPlayer();


  protected:
    void zerar();


};
#endif
