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

#include "UserInterfaceWindow.h"

const int UserInterfaceWindow::BOTAO_OK =1;

//Construtor
UserInterfaceWindow::UserInterfaceWindow()
{
    espacoAntesTexto=0;
    textoAlinhamento=TEXTO_NORMAL;

    tempoEspera.setTempoOriginal(1);
    tempoEspera.setUnidade(TEMPO_MEIO);
    tempoEspera.setResetar();
}
//Destrutor
UserInterfaceWindow::~UserInterfaceWindow()
{
    if (visual!=NULL){
        delete(visual);
    }
    if (botao!=NULL){
        delete(botao);
    }
}
//Configura o dispositivo de Input
void UserInterfaceWindow::setInputSystem(InputSystem * input)
{
    UserInterfaceWindow::input=input;
}
void UserInterfaceWindow::executar()
{
    tempoEspera.processar();

    desenharBackground();

    desenharConteudo();

    desenharBotao();
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
void UserInterfaceWindow::adicionarBotao(UserInterfaceBotao * novoBotao)
{
    botao=novoBotao;
}
int UserInterfaceWindow::confirmarSelecao()
{
    int selecionado = -1;

    if (((input->teclado->isKey(botao->getTecla()))||(input->joystick->isButtonA()))&&
        (tempoEspera.isTerminou())){
        tempoEspera.setResetar();
        selecionado=BOTAO_OK;
    }

    return selecionado;
}
//Retorna se o Botão informado foi acionado
bool UserInterfaceWindow::isBotao(int tipoBotao)
{
    if (confirmarSelecao()==tipoBotao){
        return true;
    } else {
        return false;
    }
}
//Desenha o background da caixa de texto
void UserInterfaceWindow::desenharBackground()
{
    if (visual!=NULL){
        visual->desenhar();
    }
}
//Desenha o conteudo da janela
void UserInterfaceWindow::desenharConteudo()
{
    int numeroLinha=1;
    bool continuar = false;
    char textoChave[30];

    int posicaoTextoVertical   = posicao.y+espacoAntesTexto;
    int posicaoTextoHorizontal = 0;
    int auxiliar=0;

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
//Desenha o botão de ação da janela
void UserInterfaceWindow::desenharBotao()
{
    if ((botao!=NULL)&&(tempoEspera.isTerminou())){
        Ponto pontoAux = posicao;
        pontoAux.y = posicao.y+dimensao.h;
        pontoAux.x = posicao.x+dimensao.w;
        botao->desenhar(pontoAux);
    }
}
InputSystem * UserInterfaceWindow::input =NULL;

