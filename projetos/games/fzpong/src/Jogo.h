/*
 *   FZPong <Game - Pong Clone>                                            *
 *   Copyright (C) 2007-2010 by David Ferreira - FZ                        *
 *   davidferreira.fz@gmail.com - http://portal.dukitan.com/fzpong         *
 ***************************************************************************
 *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
 *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
 *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
 *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _JOGO_H
#define _JOGO_H

#include "Controle.h"
#include <GBF/SpriteItem.h>

#include <GBF/GAT.h>

#include <GBF/UIMenuSimple.h>

#include <GBF/UIItemText.h>

#include <GBF/UIWindowTitle.h>

#include <GBF/UIWindowDialog.h>



#include <GBF/UIBackgroundColor.h>

class Jogo : public GAT::GAT
{
  public:
    int main(int argc, char * argv[]);

    /** Construtor */
    Jogo(int argc, char * argv[]);

    /** Destrutor */
    virtual ~Jogo();


  protected:

    void loadResources();

    void screenMain();

    void screenHelp();

    void screenCredit();

    void screenAbout();

    void actionNewGame();

    void screenGameFinish();

    void screenGameOver();

    void screenFinishStage();

    void screenLoadStage();

    void screenGamePause();

    void actionOnGame();

    bool triggerLoadStage();

    void triggerMain();


  private:
    bool desenharBotaoEnter();

    Controle * controle;

    GBF::Image::Sprite::SpriteItem * david;

    UserInterface::Window::UIWindowTitle * janelaSobre;

    UserInterface::Window::UIWindowTitle * janelaCredito;

    UserInterface::Window::UIWindowTitle * janelaAjuda;

    UserInterface::Window::UIWindowDialog * janelaZerado;

    UserInterface::Window::UIWindowDialog * janelaGameOver;
};
#endif
