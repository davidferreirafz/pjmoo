/***************************************************************************
 *   Copyright (C) 2005-2009 by David Ferreira                             *
 *   davidferreira@uol.com.br - http://pjmoo.sourceforge.net               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <GBF/GBFramework.h>
#include <GBF/SpriteFactory.h>
#include <vector>
#include <iostream>




/*****************************************************************************/
/* Programa criado para os sorteios no 3° Fórum Cearense de Software Livre   */
/* Fórum Cearense de Software Livre, Outubro de 2006 Fortaleza/Ceará/Brasil  */
/*****************************************************************************/
int main(int argc, char* argv[])
{
    int totalParticipantes = 30;

    if ((argc>1)&&(strcmp(argv[1], "--total")==0)){
        totalParticipantes=atoi(argv[2]);
    }

    GBF::GBFramework frameworkGBF;

	GBF::Ponto ponto;
	bool mover = false;

	ponto.x=550;
	ponto.y=600;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitulo("GBF :: Sorteio - III FCSL","David Ferreira");
    frameworkGBF.iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_LIMITADO);
    frameworkGBF.inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);


    frameworkGBF.writeSystem->carregar("bfa","//data//fonte//bfa.png");
    frameworkGBF.writeSystem->carregar("arial","//data//fonte//arial.png");
    frameworkGBF.writeSystem->carregar("console","//data//fonte//console.png");

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("figuras","//data//imagem//figuras.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("logo","//data//imagem//logo.png");

    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("figuras");

    GBF::Imagem::Sprite::SpritePersonagem *superTux = spriteFactory->criarSpritePersonagem(0,0,300,276,0,0);
    GBF::Imagem::Sprite::SpriteItem       *tux      = spriteFactory->criarSpriteItem(300,0,200,196,2,20);
    GBF::Imagem::Layer::FrameLayer        *tiles    = spriteFactory->criarFrameLayer(0,276,32,32);

    GBF::Imagem::Sprite::SpriteItem *onda[3];
    onda[0] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);
    onda[1] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);
    onda[2] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);
    delete (spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("logo");

    GBF::Imagem::Sprite::SpriteItem *logo  = spriteFactory->criarSpriteItem(0,0,640,288,0,0);
    delete (spriteFactory);

    tiles->setFrame(0,288,640,192);
    tiles->setTiles(32,32);
    tiles->setPixelTile(20,6);
    tiles->iniciarRandomico(1);

    tux->animacao.setAutomatico(true);
    onda[0]->animacao.setAutomatico(true);
    onda[1]->animacao.setAutomatico(true);
    onda[2]->animacao.setAutomatico(true);

	int numero = 0;
	bool ativo = false;

	while(true) {
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}
		//Inicia a rolagem de numeros
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_SPACE)){
			ativo = true;
			mover = false;
            ponto.x = 350;
            ponto.y = 600;
		}
		//Para a rolagem revelando o numero sorteado
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_RETURN)){
			mover = true;
		}
		//Gera numero para sorterio
		if (ativo) {
			numero = (rand()%totalParticipantes) + 1;
		}
		//desenha a tela de fundo
		tiles->desenhar();
        logo->desenhar(0,0);
        tux->desenhar(20,80);
        onda[0]->desenhar(486,235);
        onda[1]->desenhar(524,235);
        onda[2]->desenhar(563,235);

        if (mover){
            ponto.x-=2;
            ponto.y-=8;

            if (ponto.y<=230){
                ativo = false;
            }
            if ((ponto.x<0)||(ponto.y<-280)){
                mover = false;
            }
        }

	    frameworkGBF.writeSystem->escrever("console",5,450,"Use a [spacebar] para iniciar e [enter] para selecionar.");

        frameworkGBF.writeSystem->escrever("bfa",300,300,"%03d",numero);

		//se sorteio rolando, exibe a msg abaixo
		if (ativo){
		    frameworkGBF.writeSystem->escrever("arial",310,340,"Sorteando...");
		} else if (numero>0){
			frameworkGBF.writeSystem->escrever("arial",310,340,"Sorteado!!!");
		}

        superTux->desenhar(ponto.x,ponto.y);
		//realiza refresh, fps, flip
		frameworkGBF.atualizar();
	}

    delete(logo);
    delete(superTux);
    delete(tux);
    delete(tiles);
    delete(onda[0]);    delete(onda[1]);    delete(onda[2]);

	return 0;
}

