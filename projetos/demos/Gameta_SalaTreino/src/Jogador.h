
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

struct AlturaPulo{
    int super;
    int normal;
    int fraco;
    int corrente;
};

enum TipoPulo
{
    FRACO,
    NORMAL,
    SUPER
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
	AlturaPulo alturaPulo;

    GBF::Ponto ajustar();
    void onPular(TipoPulo tipo);
    void acaoPular();
    void onMorrer();
    void acaoCair();
    void onImpulso();
    void acaoImpulso();
    void acaoCorrer();
    void acaoAndar(int passo);
    void acaoRecuar();
};
#endif
