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
#ifndef _CPU_H
#define _CPU_H

#include "Raquete.h"
#include <GBF/InputSystem.h>

#include <GBF/GBF_define.h>

#include <GBF/PersonagemAbstract.h>

#include "define.h"
#include <GBF/GraphicSystemImage.h>

#include "Util.h"
#include <GBF/GraphicSystemGFX.h>


class CPU : public Raquete
{
  public:
    CPU();

    virtual ~CPU();

    void acao(InputSystem * input);

    Ponto saque();

    bool isColisao(PersonagemAbstract * personagem);

    //Inicia raquete
    virtual void iniciar();

    //Desenha o sprite principal do personagem
    virtual void desenhar();


  private:
    void iniciarVisao();

    void aumentarVisao();

    Decisao pensar(Area visao, Area areaVisaoBola);

    int raioVisao;

    Efeito efeito;

};
#endif
