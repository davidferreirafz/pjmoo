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
#ifndef _CPU_H
#define _CPU_H

#include "Raquete.h"
#include <GBF/InputSystem.h>

#include <GBF/GBF.h>

#include <GBF/Character.h>

#include "define.h"
#include <GBF/ImageBase.h>

#include "Util.h"
#include <GBF/GFX.h>

class CPU : public Raquete
{
  public:
    CPU();

    virtual ~CPU();

    void update(GBF::Kernel::Input::InputSystem * input);

    GBF::Point saque();

    bool isColisao(Character::Character * personagem);

    //Inicia raquete
    virtual void iniciar();

    //Desenha o sprite principal do personagem
    virtual void draw();


  private:
    void iniciarVisao();

    void aumentarVisao();

    Decisao pensar(GBF::Area visao, GBF::Area areaVisaoBola);

    int raioVisao;

    Efeito efeito;
};
#endif
