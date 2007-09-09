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

#include "CaixaTextoTitulo.h"

CaixaTextoTitulo::CaixaTextoTitulo() 
{
    tituloAlinhamento=TEXTO_CENTRALIZADO;
}
CaixaTextoTitulo::~CaixaTextoTitulo() 
{
}
void CaixaTextoTitulo::executar() 
{
    int posicaoTextoHorizontal = 0;

    CaixaTexto::executar();

    if (tituloAlinhamento==TEXTO_CENTRALIZADO){
        int auxiliar = wsManager->getLarguraLinha(fonteTitulo,chaveTituloLocalizado);
        posicaoTextoHorizontal=int (posicao.x+(dimensao.w/2)-(auxiliar/2));
    } else {
        posicaoTextoHorizontal = posicao.x+dimensaoLetra.w;
    }

    wsManager->escreverLocalizado(fonteTitulo,posicaoTextoHorizontal,posicao.y,chaveTituloLocalizado);
}
//Informa o tipo de fonte a ser utilizado
void CaixaTextoTitulo::setFonteTitulo(std::string fonte) 
{
    this->fonteTitulo=fonte;
    dimensaoLetraTitulo=wsManager->getFonte(fonte)->getDimensao();
    espacoAntesTexto=int(dimensaoLetraTitulo.h*ESTILO_LINHA_UMA_MEIA);
}
void CaixaTextoTitulo::setChaveTituloLocalizado(std::string chaveTitulo) 
{
    chaveTituloLocalizado=chaveTitulo;
}
//Informa como deve ser o alinhamento do texto
void CaixaTextoTitulo::setTituloAlinhamento(TextoAlinhamento alinhamento) 
{
    textoAlinhamento=alinhamento;
}
