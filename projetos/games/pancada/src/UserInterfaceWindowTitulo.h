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

#ifndef _CAIXATEXTOTITULO_H
#define _CAIXATEXTOTITULO_H

#include "CaixaTexto.h"

class UserInterfaceWindowTitulo : public UserInterfaceWindow
{
  public:
    UserInterfaceWindowTitulo();

    virtual ~UserInterfaceWindowTitulo();

    //Informa como deve ser o alinhamento do texto
    void setTituloAlinhamento(UserInterfaceTextoAlinhamento alinhamento);

    void executar();

    //Inicializa as configurações da caixa de texto
    virtual void inicializar();

    UserInterfaceObjetoTexto titulo;


  protected:
    //Alinhamento do Titulo
    UserInterfaceTextoAlinhamento tituloAlinhamento;

};
#endif
