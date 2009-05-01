
#ifndef _JOGADOR_H
#define _JOGADOR_H



#include <GBF/InputSystem.h>

#include <GBF/SpriteFactory.h>
#include <GBF/FrameLayer.h>
#include <GBF/CronometroDecrescente.h>
#include "Lutador.h"




//Personagem do Jogo
class Jogador : public Lutador
{
  public:
    Jogador();
    virtual ~Jogador();
    void desenhar();
    Regiao getAreaColisao();
    bool colidiu(Regiao b);
  private:
    GBF::Ponto ajustar();

  protected:
    virtual void limites();
    virtual std::string getSpriteNome(Estado estado);

};
#endif
