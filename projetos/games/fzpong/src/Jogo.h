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
#ifndef _JOGO_H
#define _JOGO_H

#include "Controle.h"
#include <GBF/SpriteItem.h>

#include <GBF/GAT.h>

#include <GBF/UserInterfaceMenuTextoTransparente.h>

#include <GBF/UserInterfaceMenuItemTexto.h>

#include <GBF/UserInterfaceWindowTitulo.h>

#include <GBF/UserInterfaceWindow.h>

#include <GBF/UserInterfaceMenuItemTexto.h>

#include <GBF/UserInterfaceVisualSolido.h>

class Jogo : public GAT
{
  public:
    int main(int argc, char * argv[]);

    //Construtor
    Jogo(int argc, char * argv[]);

    //Destrutor
    virtual ~Jogo();


  protected:
    //Inicializa os recursos utilizados no jogo.
    //Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
    void inicializarRecursos();

    void menuPrincipal();

    void menuAjuda();

    void menuCredito();

    void menuSobre();

    void jogoNovo();

    void jogoExecutando();

    void jogoPause();

    void jogoFaseCarregar();

    void jogoFaseFinalizada();

    void jogoGameOver();

    void jogoZerado();

    bool gatilhoJogoFaseCarregar();

    void gatilhoMenuPrincipal();


  private:
    bool desenharBotaoEnter();

    Controle * controle;

    SpriteItem * david;

    UserInterfaceWindowTitulo * janelaSobre;

    UserInterfaceWindowTitulo * janelaCredito;

    UserInterfaceWindowTitulo * janelaAjuda;

    UserInterfaceWindow * janelaZerado;

    UserInterfaceWindow * janelaGameOver;
};
#endif
