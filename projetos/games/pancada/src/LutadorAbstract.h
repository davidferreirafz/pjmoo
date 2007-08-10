////    Pacanda - Based boxing game
////    Copyright (C) 2004-2006 David de Almeida Ferreira
////
////    This is free software; you can redistribute it and/or
////    modify it under the terms of the GNU General Public
////    License as published by the Free Software Foundation; either
////    version 2 of the License, or (at your option) any later version.
////
////    David de Almeida Ferreira (F-Z)
////        davidferreira@uol.com.br or davidferreira.fz@gmail.com
////        http://pjmoo.codigolivre.org.br
////////////////////////////////////////////////////////////////////////

#ifndef _LUTADORABSTRACT_H
#define _LUTADORABSTRACT_H

#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/PersonagemControlado.h>

#include <GBF/SpriteFactory.h>

#include "EfeitoContainer.h"
#include "CabecaFactory.h"
#include "Cabeca.h"
#include "LuvaEsquerda.h"
#include "LuvaDireita.h"
#include "LuvaAbstract.h"
#include <GBF/InputSystem.h>


class LutadorAbstract : public PersonagemControlado
{
  private:
    int energia;
    void resetar();

  protected:
    static Area ringue;

    Dimensao dimensao;

    Cabeca * cabeca;

    LuvaEsquerda * luvaesquerda;

    LuvaDireita * luvadireita;


  public:
    //Construtor
    LutadorAbstract();

    //Destrutor
    virtual ~LutadorAbstract();

    void iniciar(int x, int y);
    //Desenha na tela
    virtual void desenhar();

    //O lutador está na olhando pra cima
    void olharCima();

    //O lutador está na olhando pra baixo
    void olharBaixo();

    Ponto getPosicao();

    virtual void setPosicao(int x, int y);

    static void setRingue(Area ringue);

    Area getArea();


  protected:
    //checka com limites do ringue
    void checklimites();

    bool choqueAdversario(Area aCorpoAdversario);


  public:
    bool socouAdversario(LutadorAbstract * adversario);

    bool levouSoco(LuvaAbstract * luva);

    void mover(InputSystem * input, LutadorAbstract * adversario);

    bool isNocaute();


};
#endif
