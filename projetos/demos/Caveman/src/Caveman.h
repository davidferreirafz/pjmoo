
#ifndef _KANGOO_H
#define _KANGOO_H

#include <GBF/Personagem.h>

#include <GBF/InputSystem.h>

#include <GBF/SpriteFactory.h>
#include <GBF/FrameLayer.h>

//Personagem do Jogo
class Caveman : public Personagem::Personagem
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
