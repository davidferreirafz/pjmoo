///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#ifndef _CONTROLE_H
#define _CONTROLE_H

#include <GBF/InputSystem.h>

#include "Placar.h"
#include "Bola.h"
#include "Raquete.h"
#include "CPU.h"
#include <GBF/FrameLayer.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/FrameLayerManager.h>


class Jogador;

class Controle
{
  public:
    Controle();

    virtual ~Controle();

    void iniciar();

    void iniciarSet();

    void prepararSet();

    void executar(InputSystem * input);

    bool isGameOver();

    bool isFinalizado();

    //Verifica se o set foi finalizado
    bool isSetFinalizado();

    int getNumeroSet();

    void display();

    //Ativar demonstração do jogo
    void ativarDemo(bool ativo);


  protected:
    void juiz();

    void setFinalizado();


  private:
    Placar placar;

    Bola bola;

    Raquete * raqueteJogador;

    CPU * raqueteCPU;

    FrameLayer * cenario;

    WriteSystemManager * wsManager;

    //Diferença para o fim da partida
    static int DIFERENCA_FIM_PARTIDA;

    //Diferença para determinar fim da prorrogação
    static int DIFERENCA_FIM_PRORROGACAO;

    //Limite para contar a prorrogação
    static int LIMITE_PARA_PRORROGACAO;

    //Diferença de sets para determinar o ganhador
    static int DIFERENCA_SET_VITORIA;

};
#endif
