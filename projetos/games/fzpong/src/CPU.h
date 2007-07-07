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

#include <GBF/PersonagemAbstract.h>

#include <GBF/GBF_define.h>

#include "define.h"

class CPU : public Raquete
{
  public:
    CPU();

    virtual ~CPU();

    void acao(InputSystem * input);

    void iniciar();

    bool isColisao(PersonagemAbstract * personagem);

    Ponto saque();

    void iniciarVisao();

    void aumentarVisao();


  private:
    int raioVisao;

    Efeito efeito;

};
#endif
