/*
 *   Gameta <Game - Demo Tech>                                             *
 *   Copyright (C) 2007-2010 by David Ferreira - FZ                        *
 *   davidferreira.fz@gmail.com - http://portal.dukitan.com/fzpong         *
 ***************************************************************************
 *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
 *   modific�-lo sob os termos da Licen�aa P�blica Geral GNU, conforme     *
 *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
 *   Licen�aa como (a seu crit�rio) qualquer vers�o mais nova.             *
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
#include <GBF/SpriteFactory.h>

#include <GBF/GAT.h>

#include <GBF/UIMenuSimple.h>

#include <GBF/UIItemText.h>

#include <GBF/UIWindowTitle.h>

#include <GBF/UIWindowDialog.h>



#include <GBF/UIBackgroundColor.h>

SDL_Surface * pScreen;


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
        void loadResources();

        void screenMain();

        void screenHelp();

        void screenCredit();

        void screenAbout();

        void actionNewGame();

        void actionOnGame();

        void screenGamePause();

        void screenLoadStage();

        void screenFinishStage();

        void screenGameOver();

        void screenGameFinish();

        bool triggerLoadStage();

        void triggerMain();


    private:

        Controle * controle;

        UserInterface::Window::UIWindowTitle * janelaSobre;

        UserInterface::Window::UIWindowTitle * janelaCredito;

        UserInterface::Window::UIWindowTitle * janelaAjuda;

        UserInterface::Window::UIWindowDialog * janelaZerado;

        UserInterface::Window::UIWindowDialog * janelaGameOver;

};
#endif
