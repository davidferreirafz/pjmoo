
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
    void setPisouChao();
    void setBateuCabeca();
  private:
    bool pulando;
    bool caindo;


	int aceleracao;
	int deslocamento;
	GBF::Ponto saltoVelocidade;
	GBF::Ponto inicioSalto;



};
#endif
