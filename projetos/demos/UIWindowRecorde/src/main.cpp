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
    GBF::GBFramework frameworkGBF;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitulo("UIWindowRecorde","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_LIMITADO);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","//data//imagem//tiles.png");

    frameworkGBF.writeSystem->carregar("nisemegaeu","//data//fonte//nisemegaeu.png");
    frameworkGBF.writeSystem->carregar("texto","//data//fonte//ds9_computer.png");
    frameworkGBF.writeSystem->carregar("recorde","//data//fonte//recorde.png");
    frameworkGBF.writeSystem->carregar("nisemega_extra","//data//fonte//nisemegaeu.png");

    frameworkGBF.writeSystem->getFonte("recorde")->setDimensao(24,24);


//configurando suporte a idiomas
    frameworkGBF.writeSystem->idioma->setArquivo("msg.txt");
    frameworkGBF.writeSystem->idioma->detectarIdioma();


    UserInterface::Visual::UIVisualImagem *uiVisualTransparente = new UserInterface::Visual::UIVisualImagem();
    uiVisualTransparente->setCorBorda(255,255,0);
    uiVisualTransparente->setTipoBackground(UserInterface::Visual::BACKGROUND_LINES_BLACK);


    UserInterface::Visual::UIVisualSolido *uiVisualSolido = new UserInterface::Visual::UIVisualSolido();
    uiVisualSolido->setCorBorda(164,164,164);
    uiVisualSolido->setCorFundo(0,0,0);


    RankingSystem::RSRecorde recorde;
    recorde.inicializar();
    strcpy(recorde.nome,"          \0");
    strcpy(recorde.nome,"\0");
    recorde.pontos  = 90805041;
    recorde.fase    = 0;


    UIWindowRecorde * janelaRecordeNovo;

    janelaRecordeNovo = new UIWindowRecorde();
    janelaRecordeNovo->setPosicao(100,100);
    janelaRecordeNovo->setDimensao(500,330);
    janelaRecordeNovo->setVisual(uiVisualTransparente->clone());
    janelaRecordeNovo->setVisualComponentes(uiVisualSolido);
    janelaRecordeNovo->setFonteTitulo("recorde");
    janelaRecordeNovo->setFonteEdit("texto","nisemega_extra");
    janelaRecordeNovo->setFonteTecladoVirtual("recorde","texto");

    janelaRecordeNovo->setRecorde(recorde);
    janelaRecordeNovo->inicializar();

    //delete(uiVisualSolido);
    delete(uiVisualTransparente);

    while(true) {

        if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
        }

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,10,"Demo::UIWindowRecorde - Criando Componentes GUI");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,30,"PJMOO - Games Multiplataforma");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,50,"http://davidferreira-fz.blogspot.com");

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,190,400,"by: David Ferreira");
        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,190,426,"http://pjmoo.sourceforge.net");

        janelaRecordeNovo->executar();

        if (janelaRecordeNovo->isAcao(UIWindowRecorde::BOTAO_SALVAR)){
            //executa algo
            frameworkGBF.graphicSystemCore->clear();
        }


        //realiza refresh, fps, flip
        frameworkGBF.atualizar();
        frameworkGBF.graphicSystemCore->clear();

        frameworkGBF.graphicSystemCore->graphicSystem->gfx->setColor(50,10,100);
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->circuloPreenchido(300,200,200);

        frameworkGBF.graphicSystemCore->graphicSystem->gfx->setColor(10,100,50);
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->circuloPreenchido(100,70,100);

        frameworkGBF.graphicSystemCore->graphicSystem->gfx->setColor(10,100,50);
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->circuloPreenchido(300,400,120);
    }

    delete(janelaRecordeNovo);

    return 0;
}
