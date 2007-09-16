///***************************************************************************
// *   Pancada <Game - Boxing Clone>                                         *
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

#ifndef _USERINTERFACEWINDOW_H
#define _USERINTERFACEWINDOW_H

#include "UserInterfaceVisual.h"
#include <GBF/GBF_define.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/UserInterfaceTexto.h>

#include "UserInterfaceObjetoTexto.h"

class UserInterfaceWindow
{
  public:
    //Construtor
    UserInterfaceWindow();

    //Destrutor
    virtual ~UserInterfaceWindow();

    virtual void executar();

    //Posicação da Caixa na tela
    void setPosicao(int x, int y);

    void setDimensao(int largura, int altura);

    //Inicializa as configurações da caixa de texto
    virtual void inicializar();

    //Estilo Visual a ser Aplicado no Componente
    void setVisual(UserInterfaceVisual * visual);


  protected:
    Dimensao dimensao;

    Ponto posicao;

    //Espaço que deve ser dado antes da primeira linha
    int espacoAntesTexto;

    static WriteSystemManager * wsManager;

    UserInterfaceTexto * uiTexto;

    UserInterfaceTextoAlinhamento textoAlinhamento;

    //Desenha o background da caixa de texto
    void desenharBackground();


  public:
    UserInterfaceObjetoTexto texto;


  protected:
    //EstiloVIsual a ser Aplicado no componente
    UserInterfaceVisual * visual;

};
#endif
