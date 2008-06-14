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
    GBF::GBFramework frameworkGBF;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitulo("Personagem","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_LIMITADO);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","//data//imagem//tiles.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem","//data//imagem//personagem.png");

//configurando suporte a idiomas
    frameworkGBF.writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF.writeSystem->idioma->detectarIdioma();


    Caveman * personagem = new Caveman();
    Cenario * cenario = new Cenario();

    personagem->setPosicao(32,384);

    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }

        cenario->desenhar();

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,0,"Demo::Caveman - PJMOO - Games Multiplataforma - http://pjmoo.sourceforge.net");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,6,450,"by: David Ferreira - http://davidferreira-fz.blogspot.com");

        personagem->acao(frameworkGBF.inputSystemCore->inputSystem);

        cenario->executar(personagem);

        personagem->desenhar();


        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
        frameworkGBF.graphicSystemCore->clear();

    }

    delete(personagem);
    //delete(cenario);

    return 0;
}
