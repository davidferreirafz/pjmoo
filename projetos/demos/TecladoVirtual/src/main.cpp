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
    frameworkGBF.setTitulo("TecladoVirtual","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","//data//imagem//tiles.png");

    frameworkGBF.writeSystem->carregar("nisemegaeu",frameworkGBF.getPath()+"data//fonte//nisemegaeu.png");
    frameworkGBF.writeSystem->carregar("texto",frameworkGBF.getPath()+"data//fonte//ds9_computer.png");
    frameworkGBF.writeSystem->carregar("recorde",frameworkGBF.getPath()+"data//fonte//recorde.png");
    frameworkGBF.writeSystem->carregar("nisemega_extra",frameworkGBF.getPath()+"data//fonte//nisemegaeu.png");

    frameworkGBF.writeSystem->getFonte("recorde")->setDimensao(24,24);


//configurando suporte a idiomas
    frameworkGBF.writeSystem->uiTexto->setArquivo("msg.txt");
    frameworkGBF.writeSystem->uiTexto->detectarIdioma();


    UserInterfaceVisualSolido *uiVisualImagem = new UserInterfaceVisualSolido();
    uiVisualImagem->setCorBorda(255,255,0);
    uiVisualImagem->setCorFundo(0,0,0);

    UserInterfaceVisualImagem *uiVisualTransparente = new UserInterfaceVisualImagem();
    uiVisualTransparente->setCorBorda(255,255,0);
    uiVisualTransparente->setTipoBackground(BACKGROUND_LINES_BLACK);



    TopSystemRecorde recorde;
    recorde.inicializar();
    strcpy(recorde.nome,"          \0");
    strcpy(recorde.nome,"\0");
    recorde.pontos  = 0;
    recorde.fase    = 0;


    UserInterfaceNovoRecorde * janelaRecordeNovo;

    janelaRecordeNovo = new UserInterfaceNovoRecorde();
    janelaRecordeNovo->setPosicao(100,100);
    janelaRecordeNovo->setDimensao(500,330);
    janelaRecordeNovo->setVisual(uiVisualTransparente->clone());
    janelaRecordeNovo->setFonteTitulo("recorde");
    janelaRecordeNovo->setFonteLabel("texto");
    janelaRecordeNovo->setFonteCampo("nisemega_extra");
    janelaRecordeNovo->setFonteTeclado("recorde");
    janelaRecordeNovo->setFonteControle("texto");

    janelaRecordeNovo->setRecorde(recorde);
    janelaRecordeNovo->inicializar();

    delete(uiVisualImagem);
    delete(uiVisualTransparente);

    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }


        janelaRecordeNovo->executar();

        if (janelaRecordeNovo->isAcao(UserInterfaceNovoRecorde::BOTAO_SALVAR)){
            //executa algo
            frameworkGBF.graphicSystemCore->clear();
        }


        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
        frameworkGBF.graphicSystemCore->clear();
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->circuloPreenchido(300,200,200);
    }

    delete(janelaRecordeNovo);

    return 0;
}
