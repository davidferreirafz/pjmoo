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

#ifndef _USERINTERFACEOBJETOTEXTO_H
#define _USERINTERFACEOBJETOTEXTO_H

#include <string>

#include <GBF/GBF_define.h>


enum UserInterfaceTextoAlinhamento {
  //Texto Alinhado a esquerda
  TEXTO_NORMAL =0,
  //Texto Alinhado ao Centro (Centralizado)
  TEXTO_CENTRALIZADO =1
};
class UserInterfaceObjetoTexto
{
  public:
    static const float ENTRELINHA_SIMPLES;

    static const float ENTRELINHA_UMA_MEIA;

    static const float ENTRELINHA_DUPLA;


  protected:
    float entreLinhas;

    std::string fonte;

    std::string chaveTexto;

    //Espa�amento entre linhas
    int espacoEntreLinhas;


  public:
    //Construtor
    UserInterfaceObjetoTexto();

    //Destrutor
    ~UserInterfaceObjetoTexto();

    void setFonte(std::string fonte);

    std::string getFonte();

    void setChaveTexto(std::string chaveTexto);

    std::string getChaveTexto();

    void setDimensaoLetra(const Dimensao & dimensao);

    Dimensao getDimensaoLetra();

    //Informa o Estilo de entrelinhas a ser utilizado
    void setEntreLinha(float estiloEntreLinhas);

    //Retorna em pixel o espa�amento entre as linhas
    int getEspacoEntreLinhas();

    //Configura o Alinhamento do Texto
    void setAlinhamento(UserInterfaceTextoAlinhamento alinhamento);

    //Retorna o alinhamento utilizado
    UserInterfaceTextoAlinhamento getAlinhamento();


  protected:
    Dimensao dimensaoLetra;

    UserInterfaceTextoAlinhamento alinhamento;

};
#endif
