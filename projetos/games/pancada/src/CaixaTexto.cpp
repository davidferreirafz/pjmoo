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

#include "CaixaTexto.h"

const float Texto::ENTRELINHA_SIMPLES =1.0;

const float Texto::ENTRELINHA_UMA_MEIA =1.5;

const float Texto::ENTRELINHA_DUPLA =2.0;

//Construtor
Texto::Texto()
{
    entreLinhas=ENTRELINHA_UMA_MEIA;
}
//Destrutor
Texto::~Texto()
{
}
void Texto::setFonte(std::string fonte)
{
    this->fonte=fonte;

//    dimensaoLetra=wsManager->getFonte(fonte)->getDimensao();
//    espacoEntreLinhas=int(dimensaoLetra.w*estiloEntreLinhas);
}
void Texto::setChaveTexto(std::string chaveTexto)
{
    this->chaveTexto=chaveTexto;
}
std::string Texto::getFonte()
{
    return fonte;
}
std::string Texto::getChaveTexto()
{
    return chaveTexto;
}
void Texto::setDimensaoLetra(const Dimensao & dimensao)
{
    dimensaoLetra=dimensao;
    espacoEntreLinhas=int(dimensaoLetra.w*entreLinhas);
}
Dimensao Texto::getDimensaoLetra()
{
    return dimensaoLetra;
}
//Informa o Estilo de entrelinhas a ser utilizado
void Texto::setEntreLinha(float estiloEntreLinhas)
{
    if ((estiloEntreLinhas==ENTRELINHA_SIMPLES)||(estiloEntreLinhas==ENTRELINHA_UMA_MEIA)||
       (estiloEntreLinhas==ENTRELINHA_DUPLA)){
        entreLinhas=estiloEntreLinhas;
    }
}
//Retorna em pixel o espaçamento entre as linhas
int Texto::getEspacoEntreLinhas()
{
    return espacoEntreLinhas;
}
//Construtor
CaixaTexto::CaixaTexto()
{
    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }

    if (uiTexto==NULL){
        uiTexto = UserInterfaceTexto::getInstance();
    }

    espacoAntesTexto=0;
    textoAlinhamento=TEXTO_NORMAL;

}
//Destrutor
CaixaTexto::~CaixaTexto()
{
}
void CaixaTexto::executar()
{
    int numeroLinha=1;
    char textoChave[30];
    bool continuar = false;
    int posicaoTextoVertical   = posicao.y+espacoAntesTexto;
    int posicaoTextoHorizontal = 0;
    int auxiliar=0;

    desenharBackground();

    do {
        sprintf(textoChave,texto.getChaveTexto().c_str(),numeroLinha);

        continuar=uiTexto->isChaveTexto(textoChave);

        if (continuar){

            if (textoAlinhamento==TEXTO_CENTRALIZADO){
                auxiliar = wsManager->getLarguraLinha(texto.getFonte(),textoChave);
                posicaoTextoHorizontal=int (posicao.x+(dimensao.w/2)-(auxiliar/2));
            } else {
                posicaoTextoHorizontal = posicao.x+texto.getDimensaoLetra().w;
            }

            wsManager->escreverLocalizado(texto.getFonte(),posicaoTextoHorizontal,posicaoTextoVertical,textoChave);
            posicaoTextoVertical=posicao.y+espacoAntesTexto+(texto.getEspacoEntreLinhas()*numeroLinha);
            numeroLinha++;

        } else {
            break;
        }

    } while(true);
}
//Posicação da Caixa na tela
void CaixaTexto::setPosicao(int x, int y)
{
    posicao.x=x;
    posicao.y=y;
}
void CaixaTexto::setDimensao(int largura, int altura)
{
    dimensao.w=largura;
    dimensao.h=altura;
}
//Informa como deve ser o alinhamento do texto
void CaixaTexto::setTextoAlinhamento(TextoAlinhamento alinhamento)
{
    textoAlinhamento=alinhamento;
}
//Inicializa as configurações da caixa de texto
void CaixaTexto::inicializar()
{
    texto.setDimensaoLetra(wsManager->getFonte(texto.getFonte())->getDimensao());
    if (estiloVisual!=NULL){
        estiloVisual->aplicar(posicao,dimensao);
    }
}
WriteSystemManager * CaixaTexto::wsManager =NULL;

//Desenha o background da caixa de texto
void CaixaTexto::desenharBackground()
{
//    if (background!=NULL){
//        background->desenhar();
//    }

//    gsGFX->setColor(20,20,20);
//    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
    if (estiloVisual!=NULL){
        estiloVisual->desenhar(posicao,dimensao);
    }
}
//EstiloVisual a ser Aplicado no Componente
void CaixaTexto::setEstiloVisual(UserInterfaceEstiloVisual * estilo)
{
    estiloVisual=estilo;
}
