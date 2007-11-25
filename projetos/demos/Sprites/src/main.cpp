//***************************************************************************
//  UML <Demo - GoF - Designer Patterns>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.wiki.sourceforge.net/GoF
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da
//    Licença como (a seu critério) qualquer versão mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "main.h"

int main(int argc, char * argv[])
{
    GBF frameworkGBF;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitulo("Sprites","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem","//data//imagem//sprite_lutador.png");

//configurando suporte a idiomas
    frameworkGBF.writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF.writeSystem->uiTexto->detectarIdioma();

    SpritePersonagem *personagem[6];


    SpriteFactory * spriteFactory = new SpriteFactory(frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->getImageBuffer("personagem"));
    personagem[0] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,1);
    personagem[1] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,2);
    personagem[2] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,8);
    personagem[3] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,15);
    personagem[4] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,30);
    personagem[5] = spriteFactory->criarSpritePersonagem(0,0,160,160,5,60);

    delete(spriteFactory);

    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }

        personagem[0]->desenhar( 50,50);
        personagem[1]->desenhar(230,50);
        personagem[2]->desenhar(430,50);

        personagem[3]->desenhar( 50,290);
        personagem[4]->desenhar(230,290);
        personagem[5]->desenhar(430,290);

        //write
        frameworkGBF.writeSystem->escreverLocalizado(WriteSystemManager::defaultFont,10,440,"message");

        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
        frameworkGBF.graphicSystemCore->clear();
    }

    delete(personagem[0]);
    delete(personagem[1]);
    delete(personagem[2]);
    delete(personagem[3]);
    delete(personagem[4]);
    delete(personagem[5]);

    return 0;
}
