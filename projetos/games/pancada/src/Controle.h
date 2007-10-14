//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net 
//***************************************************************************
//    Este programa � software livre; voc� pode redistribu�-lo e/ou
//    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a vers�o 2 da 
//    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or 
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,                                       
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#ifndef _CONTROLE_H
#define _CONTROLE_H

#include "FaseAbstract.h"
#include <GBF/InputSystem.h>

#include <GBF/SpriteItem.h>

#include <GBF/TimerSystemCronometroDecrescente.h>

#include "FaseFactory.h"

class Controle
{
  private:
    int faseNumero;

    FaseAbstract * fase;


  public:
    //Construtor
    Controle();

    //Destrutor
    virtual ~Controle();

    void iniciar();

    bool carregarFase();

    void mudarFase();

    bool isGameOver();

    bool isFaseFinalizada();

    void executar(InputSystem * input);

    void desenhar();

    void carregar();


  protected:
    SpriteItem * fight;

    TimerSystemCronometroDecrescente tempoEspera;

};
#endif
