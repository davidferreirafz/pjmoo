/***************************************************************************
*   Copyright (C) 2005-2007 by David Ferreira                             *
*   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
*   http://pjmoo.codigolivre.org.br                                       *
*       http://davidferreira.fz.googlepages.com                           *
*                                                                         *
*   Este programa é um software livre; você pode redistribui-lo e/ou      *
*   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
*   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
*   Licença.                                                              *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/
#include "Apresentacao.h"

Apresentacao::Apresentacao()
{
    wsManager  = WriteSystemManager::getInstance();
    flManager  = FrameLayerManager::getInstance();
    gsGFX      = GraphicSystemGFX::getInstance();
    numeroTela = 1;
    tempo.setTempoOriginal(6);
    tempo.setUnidade(TEMPO_SEGUNDO);
    tempo.setResetar();

    SpriteFactory * spriteFactory = new SpriteFactory(GraphicSystemImageBufferManager::getInstance()->getImageBuffer("abertura"));

    zangoesBorg  = spriteFactory->criarSpriteItem(139,0,140,80,1,1);
    terra        = spriteFactory->criarSpriteItem(280,0,142,141,1,1);
    babyBorg     = spriteFactory->criarSpriteItem(423,0,88,88,1,1);
    logoInimigos = spriteFactory->criarSpriteItem(339,142,173,179,1,1);
    naveDefiant  = spriteFactory->criarSpriteItem(139,81,139,85,1,1);
    naveEsquemas = spriteFactory->criarSpriteItem(285,375,227,137,1,1);
    batalha      = spriteFactory->criarSpriteItem(0,167,297,126,1,1);
    naveBorg     = spriteFactory->criarSpriteItem(0,294,150,114,1,1);
    david        = spriteFactory->criarSpriteItem(298,142,40,63,1,1);

    delete(spriteFactory);
}

Apresentacao::~Apresentacao()
{
    delete (zangoesBorg);
    delete (terra);
    delete (babyBorg);
    delete (logoInimigos);
    delete (naveDefiant);
    delete (naveEsquemas);
    delete (batalha);
    delete (naveBorg);
    delete (david);
}

bool Apresentacao::executar()
{
    bool menuPrincipal = false;

    tempo.processar();

    switch(numeroTela){
        case 1:
                tela01();
            break;
        case 2:
                tela02();
            break;
        case 3:
                tela03();
            break;
        case 4:
                tela04();
            break;
        case 5:
                tela05();
            break;
        case 6:
                tela06();
            break;
        case 7:
                tela07();
            break;
        case 8:
                tela08();
            break;
        case 9:
                tela09();
            break;
    }

    if(tempo.getTempo()<=0){
        preTela();
    }

    return menuPrincipal;
}
void Apresentacao::preTela()
{
    numeroTela++;
    switch(numeroTela)
    {
        case 9:
                tempo.setTempoOriginal(36);
            break;
        case 8:
        case 7:
        case 4:
                tempo.setTempoOriginal(15);
            break;
        case 6:
        case 5:
        case 3:
        case 2:
                tempo.setTempoOriginal(10);
            break;
        case 1:
        default:
                tempo.setTempoOriginal(6);
                numeroTela=1;
            break;
    }
    tempo.setResetar();
}
void Apresentacao::reset()
{
    numeroTela=1;
}

void Apresentacao::tela01()
{
    flManager->getFrameLayer("startrek")->desenhar();

    wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,150,200,"tela_01_1");
    wsManager->escreverLocalizado(WriteSystemFontDefault::console, 380,410,"tela_01_2");
    wsManager->escreverLocalizado(WriteSystemFontDefault::console, 382,430,"tela_01_3");
    wsManager->escreverLocalizado(WriteSystemFontDefault::console, 382,450,"tela_01_4");
}
void Apresentacao::tela02()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,290);

    for (int i=0; i<6;i++){
        sprintf(textoFormatado,"tela_02_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,100,100+(30*i),textoFormatado);
    }
    babyBorg->desenhar(440,140);
    naveDefiant->desenhar(150,280);
}
void Apresentacao::tela03()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,300);

    for (int i=0; i<5;i++){
        sprintf(textoFormatado,"tela_03_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,120,100+(30*i),textoFormatado);
    }
    terra->desenhar(420,100);
    naveBorg->desenhar(180,260);

}
void Apresentacao::tela04()
{
    char textoFormatado[30];
     flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,300);

    for (int i=0; i<8;i++){
        sprintf(textoFormatado,"tela_04_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,60,100+(30*i),textoFormatado);
    }
    zangoesBorg->desenhar(400,280);
}
void Apresentacao::tela05()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,290);

    for (int i=0; i<6;i++){
        sprintf(textoFormatado,"tela_05_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,60,100+(30*i),textoFormatado);
    }

    terra->desenhar(350,230);
}
void Apresentacao::tela06()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,290);

    for (int i=0; i<7;i++){
        sprintf(textoFormatado,"tela_06_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,80,100+(30*i),textoFormatado);
    }

    logoInimigos->desenhar(360,190);
}
void Apresentacao::tela07()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,290);

    for (int i=0; i<7;i++){
        sprintf(textoFormatado,"tela_07_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,30,100+(30*i),textoFormatado);
    }

    naveEsquemas->desenhar(380,180);
}
void Apresentacao::tela08()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,90,640,290);

    for (int i=0; i<8;i++){
        sprintf(textoFormatado,"tela_08_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::pumpdemi,30,100+(30*i),textoFormatado);
    }
    batalha->desenhar(320,200);
}
void Apresentacao::tela09()
{
    char textoFormatado[30];
    flManager->getFrameLayer("startrek")->desenhar();

    gsGFX->setColor(0,0,0);
    gsGFX->retanguloPreenchido(0,70,640,400);

    for (int i=0; i<19;i++){
        sprintf(textoFormatado,"tela_09_%d",(1)+i);
        wsManager->escreverLocalizado(WriteSystemFontDefault::console,90,76+(20*i),textoFormatado);
    }

    david->desenhar(580,400);
}




