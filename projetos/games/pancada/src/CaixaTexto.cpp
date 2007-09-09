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

const float CaixaTexto::ESTILO_LINHA_SIMPLES =1.0;

const float CaixaTexto::ESTILO_LINHA_UMA_MEIA =1.5;

const float CaixaTexto::ESTILO_LINHA_DUPLA =2.0;

//Construtor
CaixaTexto::CaixaTexto() 
{
    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }

    if (uiTexto==NULL){
        uiTexto = UserInterfaceTexto::getInstance();
    }

    if (gsImageBufferManager==NULL){
        gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }

    if (gsGFX==NULL){
        gsGFX = GraphicSystemGFX::getInstance();
    }

    estiloEntreLinhas=ESTILO_LINHA_UMA_MEIA;
    espacoAntesTexto=0;
    textoAlinhamento=TEXTO_NORMAL;

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("gbf-window-background"));
    background = spriteFactory->criarFrameLayer(0,0,10,10);
    delete(spriteFactory);
}
//Destrutor
CaixaTexto::~CaixaTexto() 
{
    if (background!=NULL){
        delete(background);
    }
}
void CaixaTexto::executar() 
{
    int numeroLinha=1;
    char textoChave[30];
    bool continuar = false;
    int posicaoTextoVertical   = posicao.y+espacoAntesTexto;
    int posicaoTextoHorizontal = posicao.x+dimensaoLetra.w;
    int auxiliar=0;

    desenharBackground();

    do {
        sprintf(textoChave,chaveTextoLocalizado.c_str(),numeroLinha);

        continuar=uiTexto->isChaveTexto(textoChave);

        if (continuar){

            if (textoAlinhamento==TEXTO_CENTRALIZADO){
                auxiliar = wsManager->getLarguraLinha(fonte,textoChave);
                posicaoTextoHorizontal=int (posicao.x+(dimensao.w/2)-(auxiliar/2));
            } else {
                posicaoTextoHorizontal = posicao.x+dimensaoLetra.w;
            }

            wsManager->escreverLocalizado(fonte,posicaoTextoHorizontal,posicaoTextoVertical,textoChave);
            posicaoTextoVertical=posicao.y+espacoAntesTexto+(espacoEntreLinhas*numeroLinha);
            numeroLinha++;

        } else {
            break;
        }

    } while(true);
}
//Informa o tipo de fonte a ser utilizado
void CaixaTexto::setFonte(std::string fonte) 
{
    this->fonte=fonte;

    dimensaoLetra=wsManager->getFonte(fonte)->getDimensao();

    espacoEntreLinhas=int(dimensaoLetra.w*estiloEntreLinhas);
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
void CaixaTexto::setChaveTextoLocalizado(std::string chaveTexto) 
{
    chaveTextoLocalizado=chaveTexto;
}
//Informa como deve ser o alinhamento do texto
void CaixaTexto::setTextoAlinhamento(TextoAlinhamento alinhamento) 
{
    textoAlinhamento=alinhamento;
}
//Inicializa as configurações da caixa de texto
void CaixaTexto::inicializar() 
{
    if (background!=NULL){
        background->setFrame(posicao.x,posicao.y,dimensao.w,dimensao.h);
        background->setTiles((dimensao.w/10),(dimensao.h/10));
        background->setPixelTile(10,10);
        background->iniciarOrdenado(0);
    }
}
WriteSystemManager * CaixaTexto::wsManager =NULL;

GraphicSystemImageBufferManager * CaixaTexto::gsImageBufferManager =NULL;

//Desenha o background da caixa de texto
void CaixaTexto::desenharBackground() 
{
    if (background!=NULL){
        background->desenhar();
    }

    gsGFX->setColor(20,20,20);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
GraphicSystemGFX * CaixaTexto::gsGFX =NULL;

