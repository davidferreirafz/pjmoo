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
#ifndef _RAQUETE_H
#define _RAQUETE_H

#include "Objeto.h"
#include <GBF/GBF_define.h>

#include "Bola.h"
#include <GBF/PersonagemAbstract.h>


enum Lado {
  //Lado direito da Tela
  LADO_DIREITO =1,
  //Lado esquerdo da Tela
  LADO_ESQUERDO =0
};
class Raquete : public Objeto
{
  public:
    //Construtor
    Raquete();

    //Destrutor
    virtual ~Raquete();

    //Inicia raquete
    virtual void iniciar();

    //Posiciona Raquete
    void preparar();

    virtual Ponto saque() = 0;

    static void setBola(Bola * bola);

    void setLado(Lado valor);

    virtual bool isColisao(PersonagemAbstract * personagem);


  protected:
    Lado lado;

    int getVelocidade();

    void setVelocidade(int valor);

    void subir();

    void descer();

    bool isBateuParede();

    Bola getVisaoBola();

    void adaptarVelocidade();


  private:
    int velocidade;

    static Bola * visaoBola;

};
#endif
