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
void UserInterfaceObjetoTexto::setChaveTexto(std::string chaveTexto) 
{
    this->chaveTexto=chaveTexto;
}
std::string UserInterfaceObjetoTexto::getFonte() 
{
    return fonte;
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
//Retorna em pixel o espaçamento entre as linhas
int UserInterfaceObjetoTexto::getEspacoEntreLinhas() 
{
    return espacoEntreLinhas;
}
//Construtor
UserInterfaceWindow::UserInterfaceWindow() 
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
UserInterfaceWindow::~UserInterfaceWindow() 
{
    if (visual!=NULL){
        delete(visual);
    }
}
void UserInterfaceWindow::executar() 
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
void UserInterfaceWindow::setPosicao(int x, int y) 
{
    posicao.x=x;
    posicao.y=y;
}
void UserInterfaceWindow::setDimensao(int largura, int altura) 
{
    dimensao.w=largura;
    dimensao.h=altura;
}
//Informa como deve ser o alinhamento do texto
void UserInterfaceWindow::setTextoAlinhamento(UserInterfaceTextoAlinhamento alinhamento) 
{
    textoAlinhamento=alinhamento;
}
//Inicializa as configurações da caixa de texto
void UserInterfaceWindow::inicializar() 
{
    texto.setDimensaoLetra(wsManager->getFonte(texto.getFonte())->getDimensao());
    if (visual!=NULL){
        visual->aplicar(posicao,dimensao);
    }
}
//Estilo Visual a ser Aplicado no Componente
void UserInterfaceWindow::setVisual(UserInterfaceVisual * visual) 
{
    this->visual=visual;
}
WriteSystemManager * UserInterfaceWindow::wsManager =NULL;

//Desenha o background da caixa de texto
void UserInterfaceWindow::desenharBackground() 
{
//    if (background!=NULL){
//        background->desenhar();
//    }

//    gsGFX->setColor(20,20,20);
//    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
    if (visual!=NULL){
        visual->desenhar();
    }
}
