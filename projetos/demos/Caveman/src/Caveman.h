
#ifndef _CAVEMAN_H
#define _CAVEMAN_H



#include <GBF/InputSystem.h>

#include <GBF/SpriteFactory.h>
#include <GBF/FrameLayer.h>
#include "PersonagemAdventure.h"

//Personagem do Jogo
class Caveman : public PersonagemAdventure
{
  public:
    Caveman();
    virtual ~Caveman();

    virtual void acao(GBF::Kernel::Input::InputSystem * input);
    void setParouCair();

  private:
    bool pulando;

	int aceleracao;
	int deslocamento;
	GBF::Ponto saltoVelocidade;


};
#endif
