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

#ifndef _CAIXATEXTO_H
#define _CAIXATEXTO_H

#include <string>

#include <GBF/GBF_define.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/UserInterfaceTexto.h>

#include <GBF/FrameLayer.h>

#include <GBF/SpriteFactory.h>

#include <GBF/GraphicSystemGFX.h>


enum TextoAlinhamento {
  //Texto Alinhado a esquerda
  TEXTO_NORMAL =0,
  //Texto Alinhado ao Centro (Centralizado)
  TEXTO_CENTRALIZADO =1
};
class CaixaTexto
{
  protected:
    static const float ESTILO_LINHA_SIMPLES;

    static const float ESTILO_LINHA_UMA_MEIA;

    static const float ESTILO_LINHA_DUPLA;


  public:
    //Construtor
    CaixaTexto();

    //Destrutor
    virtual ~CaixaTexto();

    virtual void executar();

    //Informa o tipo de fonte a ser utilizado
    void setFonte(std::string fonte);

    //Posica��o da Caixa na tela
    void setPosicao(int x, int y);

    void setDimensao(int largura, int altura);

    void setChaveTextoLocalizado(std::string chaveTexto);

    //Informa como deve ser o alinhamento do texto
    void setTextoAlinhamento(TextoAlinhamento alinhamento);

    //Inicializa as configura��es da caixa de texto
    void inicializar();


  protected:
    Dimensao dimensao;

    Ponto posicao;

    std::string fonte;

    //Espa�amento entre linhas
    int espacoEntreLinhas;

    //Chave de localiza��o do texto para utilizar recursos de tradu��o(localiza��o)
    std::string chaveTextoLocalizado;

    float estiloEntreLinhas;

    //Espa�o que deve ser dado antes da primeira linha
    int espacoAntesTexto;

    static WriteSystemManager * wsManager;

    static GraphicSystemImageBufferManager * gsImageBufferManager;

    UserInterfaceTexto * uiTexto;

    //Maior dimens�o poss�vel de um caracter com o tipo de fonte utilizado
    
    Dimensao dimensaoLetra;

    TextoAlinhamento textoAlinhamento;

    //Layer de fundo da caixa de texto
    FrameLayer * background;

    //Desenha o background da caixa de texto
    void desenharBackground();

    static GraphicSystemGFX * gsGFX;

};
#endif
