//***************************************************************************
//  UML <Demo - GoF - Designer Patterns>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.wiki.sourceforge.net/GoF
//***************************************************************************
//    Este programa � software livre; voc� pode redistribu�-lo e/ou
//    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a vers�o 2 da 
//    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
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
    frameworkGBF.setTitulo("GoF - Designer Pattern","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","//data//imagem//tiles.png");

//configurando suporte a idiomas
    frameworkGBF.writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF.writeSystem->uiTexto->detectarIdioma();


    Maze * maze;
    MazeGame mazeGame;
    
    StandardMazeBuilder builder;
//    BombedMazeBuilder builder;

    mazeGame.create(builder);

    maze = builder.getMaze();


    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }

        maze->draw();

        //write
        frameworkGBF.writeSystem->escreverLocalizado(WriteSystemManager::defaultFont,10,440,"message");

        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
    }

    delete(maze);

    return 0;
}