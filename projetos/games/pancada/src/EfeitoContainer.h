
#ifndef _EFEITOCONTAINER_H
#define _EFEITOCONTAINER_H

#include <deque>
#include "EfeitoAbstract.h"
#include "EfeitoSangue.h"

class EfeitoContainer
{
  protected:
    std::deque<EfeitoAbstract*> lista;


  private:
    static EfeitoContainer * instance;


  public:
    static EfeitoContainer * getInstance();

    //Destrutor 
    virtual ~EfeitoContainer();

    void adicionar(int x, int y, EnumEfeito eEfeito);

    void desenhar();


  protected:
    void removerDesativado();

    void limpar();


  private:
    //Construtor 
    EfeitoContainer();


};
#endif
