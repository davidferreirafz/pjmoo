
#ifndef _CAVEMAN_H
#define _CAVEMAN_H



#include <GBF/InputSystem.h>

#include <GBF/SpriteFactory.h>
#include <GBF/FrameLayer.h>
#include <GBF/CronometroDecrescente.h>
#include <GBF/Personagem.h>

enum Estado{
    PARADO,
    ANDANDO,
    RECUO,
    AVANCO,
    MORRENDO,
    PULANDO,
    CAINDO,
    IMPULSO
};

struct Altura{
    int a;
    int b;
    int c;
    int corrente;
};

//Personagem do Jogo
class Jogador : public Personagem::Personagem
{
  public:
    Jogador();
    virtual ~Jogador();

    virtual void acao(GBF::Kernel::Input::InputSystem * input);
    void desenhar();
  private:

    Estado estado;
    std::string getAliasSprite();
	Altura alturaPulo;

};
#endif
