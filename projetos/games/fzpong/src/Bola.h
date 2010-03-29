///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
// *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
// *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
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
#ifndef _BOLA_H
#define _BOLA_H

#include "Objeto.h"
#include <GBF/GBF.h>

#include <GBF/InputSystem.h>

#include <GBF/Character.h>

#include <GBF/ImageBufferManager.h>

#include <GBF/SpriteFactory.h>

#include <GBF/GraphicSystem.h>

struct Velocidade
{
    float x;

    float y;

};
class Bola : public Objeto
{
  public:
    Bola();

    virtual ~Bola();

    void iniciar();

    void iniciar(GBF::Point saque);

    void continuar();

    void update(GBF::Kernel::Input::InputSystem * input);

    bool isColisao(Character::Character * personagem);

    int getVelocidade();


  private:
    //Corrigir a posi��o da bola ap�s colidir com uma raquete, evitando que a bola seja desenha dentro/ap�s a raquete
    void corrigirEixoX(Character::Character * personagem);

    void elevarGrauDificuldade();

    void checkarVelocidade();

    int batidaParede;

    Velocidade velocidade;

    Velocidade velocidadeGradativa;

};
#endif
