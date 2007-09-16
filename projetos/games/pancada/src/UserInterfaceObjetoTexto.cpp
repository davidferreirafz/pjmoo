///***************************************************************************
// *   Pancada <Game - Boxing Clone>                                         *
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

#include "UserInterfaceObjetoTexto.h"

const float UserInterfaceObjetoTexto::ENTRELINHA_SIMPLES =1.0;

const float UserInterfaceObjetoTexto::ENTRELINHA_UMA_MEIA =1.5;

const float UserInterfaceObjetoTexto::ENTRELINHA_DUPLA =2.0;

//Construtor
UserInterfaceObjetoTexto::UserInterfaceObjetoTexto() 
{
    entreLinhas=ENTRELINHA_UMA_MEIA;
}
//Destrutor
UserInterfaceObjetoTexto::~UserInterfaceObjetoTexto() 
{
}
void UserInterfaceObjetoTexto::setFonte(std::string fonte) 
{
    this->fonte=fonte;

//    dimensaoLetra=wsManager->getFonte(fonte)->getDimensao();
//    espacoEntreLinhas=int(dimensaoLetra.w*estiloEntreLinhas);
}
std::string UserInterfaceObjetoTexto::getFonte() 
{
    return fonte;
}
void UserInterfaceObjetoTexto::setChaveTexto(std::string chaveTexto) 
{
    this->chaveTexto=chaveTexto;
}
std::string UserInterfaceObjetoTexto::getChaveTexto() 
{
    return chaveTexto;
}
void UserInterfaceObjetoTexto::setDimensaoLetra(const Dimensao & dimensao) 
{
    dimensaoLetra=dimensao;
    espacoEntreLinhas=int(dimensaoLetra.w*entreLinhas);
}
Dimensao UserInterfaceObjetoTexto::getDimensaoLetra() 
{
    return dimensaoLetra;
}
//Informa o Estilo de entrelinhas a ser utilizado
void UserInterfaceObjetoTexto::setEntreLinha(float estiloEntreLinhas) 
{
    if ((estiloEntreLinhas==ENTRELINHA_SIMPLES)||(estiloEntreLinhas==ENTRELINHA_UMA_MEIA)||
       (estiloEntreLinhas==ENTRELINHA_DUPLA)){
        entreLinhas=estiloEntreLinhas;
    }
}
//Retorna em pixel o espa�amento entre as linhas
int UserInterfaceObjetoTexto::getEspacoEntreLinhas() 
{
    return espacoEntreLinhas;
}
//Configura o Alinhamento do Texto
void UserInterfaceObjetoTexto::setAlinhamento(UserInterfaceTextoAlinhamento alinhamento) 
{
    this->alinhamento=alinhamento;
}
//Retorna o alinhamento utilizado
UserInterfaceTextoAlinhamento UserInterfaceObjetoTexto::getAlinhamento() 
{
    return alinhamento;
}
