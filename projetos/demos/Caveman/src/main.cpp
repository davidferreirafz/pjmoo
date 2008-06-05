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

    int mapa[300]={
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     1,2,0,0,1,2,0,0,0,1,2,0,0,0,0,1,2,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,1,3,3,2,0,0,0,0,0,0,1,3,2,0,1,2,0,0,
     0,1,6,6,6,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,3,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,
     4,5,4,4,3,4,3,3,2,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,1,4,5,2,0,0,0,1,3,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,5,
     0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,4,3,5,
     0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1,3,4,3,3,
     5,3,4,5,3,3,4,3,3,5,3,4,4,5,3,5,3,4,5,3
    };


    GBF::Imagem::SpriteFactory * spriteFactory = NULL;
    spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    GBF::Imagem::Layer::FrameLayer * tiles = spriteFactory->criarFrameLayer(0, 0,32,32);
    tiles->setFrame(0,0,640,480);
    tiles->setTiles(20,15);
    tiles->setPixelTile(32,32);
    tiles->carregarMemoria(mapa);

    //GBF::Imagem::Layer::LayerManager::getInstance()->adicionar("tiles",tiles);
    delete(spriteFactory);


    Caveman * personagem = new Caveman();


    personagem->setPosicao(10,384);

    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }

        tiles->desenhar();

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,10,"Demo::Caveman");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,30,"PJMOO - Games Multiplataforma");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,50,"http://davidferreira-fz.blogspot.com");

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,340,30,"by: David Ferreira");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,340,50,"http://pjmoo.sourceforge.net");

        personagem->acao(frameworkGBF.inputSystemCore->inputSystem);

        Colisao::cenario(personagem,tiles);



        personagem->desenhar();


        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
        frameworkGBF.graphicSystemCore->clear();

    }

    delete(personagem);

    return 0;
}
