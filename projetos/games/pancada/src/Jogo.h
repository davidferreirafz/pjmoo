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
#ifndef _JOGO_H
#define _JOGO_H

#include "Controle.h"
#include <GBF/GAT.h>

#include <GBF/UIWindowTitle.h>

#include <GBF/UIWindow.h>

#include <GBF/UIMenuSimple.h>

#include <GBF/UIItemText.h>

#include <GBF/UIBackgroundImage.h>


class Jogo : public GAT::GAT
{
  public:
    int main(int argc, char * argv[]);

    //Construtor
    Jogo(int argc, char * argv[]);

    //Destrutor
    virtual ~Jogo();


  protected:
    //Inicializa os recursos utilizados no jogo.
    //Ex.: Imagens, sons, fontes, configura��o do modo gr�fico e etc..
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
    Controle controle;


  protected:
    UserInterface::Window::UIWindowTitle * janelaSobre;

    UserInterface::Window::UIWindowTitle * janelaCredito;

    UserInterface::Window::UIWindowTitle * janelaAjuda;

    UserInterface::Window::UIWindowDialog * janelaZerado;

    UserInterface::Window::UIWindowDialog * janelaGameOver;

    UserInterface::Window::UIWindowDialog * janelaFaseFinalizada;

};
#endif
