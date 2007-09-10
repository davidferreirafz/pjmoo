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

#ifndef _CAIXATEXTO_H
#define _CAIXATEXTO_H

#include <string>

#include <GBF/GBF_define.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/UserInterfaceTexto.h>

#include "UserInterfaceEstiloVisual.h"

enum TextoAlinhamento {
  //Texto Alinhado a esquerda
  TEXTO_NORMAL =0,
  //Texto Alinhado ao Centro (Centralizado)
  TEXTO_CENTRALIZADO =1
};
class Texto
{
  public:
    static const float ENTRELINHA_SIMPLES;

    static const float ENTRELINHA_UMA_MEIA;

    static const float ENTRELINHA_DUPLA;


  protected:
    float entreLinhas;

    std::string fonte;

    std::string chaveTexto;

    //Espaçamento entre linhas
    int espacoEntreLinhas;


  public:
    //Construtor
    Texto();

    //Destrutor
    ~Texto();

    void setFonte(std::string fonte);

    void setChaveTexto(std::string chaveTexto);

    std::string getFonte();

    std::string getChaveTexto();


  protected:
    Dimensao dimensaoLetra;


  public:
    void setDimensaoLetra(const Dimensao & dimensao);

    Dimensao getDimensaoLetra();

    //Informa o Estilo de entrelinhas a ser utilizado
    void setEntreLinha(float estiloEntreLinhas);

    //Retorna em pixel o espaçamento entre as linhas
    int getEspacoEntreLinhas();

};
class CaixaTexto
{
  public:
    //Construtor
    CaixaTexto();

    //Destrutor
    virtual ~CaixaTexto();

    virtual void executar();

    //Posicação da Caixa na tela
    void setPosicao(int x, int y);

    void setDimensao(int largura, int altura);

    //Informa como deve ser o alinhamento do texto
    void setTextoAlinhamento(TextoAlinhamento alinhamento);

    //Inicializa as configurações da caixa de texto
    virtual void inicializar();


  protected:
    Dimensao dimensao;

    Ponto posicao;

    //Espaço que deve ser dado antes da primeira linha
    int espacoAntesTexto;

    static WriteSystemManager * wsManager;

    UserInterfaceTexto * uiTexto;

    TextoAlinhamento textoAlinhamento;

    //Desenha o background da caixa de texto
    void desenharBackground();


  public:
    Texto texto;


  protected:
    //EstiloVIsual a ser Aplicado no componente
    UserInterfaceEstiloVisual * estiloVisual;


  public:
    //EstiloVisual a ser Aplicado no Componente
    void setEstiloVisual(UserInterfaceEstiloVisual * estilo);

};
#endif
