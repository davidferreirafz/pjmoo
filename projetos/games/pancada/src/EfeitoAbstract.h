
#ifndef _EFEITOABSTRACT_H
#define _EFEITOABSTRACT_H

#include <GBF/SpritePersonagem.h>


class EfeitoAbstract
{
  protected:
    SpritePersonagem * sprite;

    Ponto posicao;

    bool ativo;

    void verificar();


  public:
    //* Construtor 
    EfeitoAbstract();

    //* Destrutor 
    virtual ~EfeitoAbstract();

    virtual void setPosicao(int x, int y);

    virtual void desenhar();

    bool isAtivo();

    void setAtivo(bool ativo);


};
#endif
