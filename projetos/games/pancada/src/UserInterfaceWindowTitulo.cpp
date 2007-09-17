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

#include "UserInterfaceWindowTitulo.h"

UserInterfaceWindowTitulo::UserInterfaceWindowTitulo() 
{
    titulo.setAlinhamento(TEXTO_CENTRALIZADO);
}
UserInterfaceWindowTitulo::~UserInterfaceWindowTitulo() 
{
}
void UserInterfaceWindowTitulo::desenharConteudo() 
{
    UserInterfaceWindow::desenharConteudo();

    int posicaoTextoHorizontal = 0;

    if (titulo.getAlinhamento()==TEXTO_CENTRALIZADO){
        int auxiliar = wsManager->getLarguraLinha(titulo.getFonte(),titulo.getChaveTexto());
        posicaoTextoHorizontal=int (posicao.x+(dimensao.w/2)-(auxiliar/2));
    } else {
        posicaoTextoHorizontal = posicao.x+titulo.getDimensaoLetra().w;
    }

    wsManager->escreverLocalizado(titulo.getFonte(),posicaoTextoHorizontal,posicao.y,titulo.getChaveTexto());

}
//Inicializa as configurações da caixa de texto
void UserInterfaceWindowTitulo::inicializar() 
{
    UserInterfaceWindow::inicializar();
    titulo.setDimensaoLetra(wsManager->getFonte(titulo.getFonte())->getDimensao());
    espacoAntesTexto=int(titulo.getDimensaoLetra().h*titulo.ENTRELINHA_UMA_MEIA);
}
