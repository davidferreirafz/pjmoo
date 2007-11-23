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

    Maze * aMaze = new Maze();

    Room* r1 = new Room(1);
    Room* r2 = new Room(2);

    Door* theDoor = new Door(r1,r2);

    aMaze->addRoom(r1,0,0);
    aMaze->addRoom(r2,2,0);


    r1->setSide(North, new Wall);
    r1->setSide(East, theDoor);
    r1->setSide(South, new Wall);
    r1->setSide(West, new Wall);

    r2->setSide(North, new Wall);
    r2->setSide(East, new Wall);
    r2->setSide(South, new Wall);
    r2->setSide(West, new Wall);
//    r2->setSide(West, theDoor);




    while(true) {
        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }
        aMaze->draw();
        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
    }

    delete(aMaze);
    return 0;
}
