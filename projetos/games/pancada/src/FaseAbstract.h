//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net 
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da 
//    Licença como (a seu critério) qualquer versão mais nova.
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
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H

#include "LutadorAbstract.h"
#include "Placar.h"
#include "Round.h"
#include "StatusTempo.h"
#include "StatusPC.h"
#include "StatusPlayer.h"
#include <GBF/InputSystem.h>

#include <GBF/FrameLayer.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/TimerSystemCronometroDecrescente.h>

#include <GBF/ParticleSystemManager.h>

#include <GBF/FrameLayerManager.h>

#include "LutadorPlayer.h"
#include "LutadorPC.h"
#include <GBF/SoundSystem.h>


class FaseAbstract
{
  protected:
    LutadorAbstract * lutadorPC;

    LutadorAbstract * lutadorPlayer;

    Placar placar;

    Round round;

    StatusTempo statusTempo;

    StatusPC statusPC;

    StatusPlayer statusPlayer;


  private:
    // so para virar de costas corretamente
    void ordenacao();


  public:
    //Destrutor
    FaseAbstract();

    //Construtor
    virtual ~FaseAbstract();

    //* Inicia a fase
    virtual void iniciar() = 0;

    bool isGameOver();

    bool isFaseFinalizada();

    bool isFimRound();

    bool isNocaute();

    bool isProximoRound();

    void proximoRound();

    int getRound();

    void executar(InputSystem * input);

    void primeiroRound();

    void desenhar();

    void setTotalRound(int total);


  protected:
    FrameLayer * ringue;

    static WriteSystemManager * wsManager;

    TimerSystemCronometroDecrescente cronometroAuxiliar;

    static ParticleSystemManager * particleManager;

};
#endif
