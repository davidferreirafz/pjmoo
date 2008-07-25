/***************************************************************************
 *   Copyright (C) 2006 by David Ferreira                                  *
 *   davidferreira@uol.com.br - http://pjmoo.codigolivre.org.br            *
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


int main(int argc, char* argv[])
{

	GBF::GBFramework *frameworkGBF = new GBF::GBFramework();

    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF::Teste Scrolling","David Ferreira");
    frameworkGBF->iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_CONTADOR);
    //Ativando GRAB_ON para evitar mudança de tela durante o
    // jogo no Gnome (Desktop para o GNU/Linux)
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(true);

//carregando imagens
    frameworkGBF->graphicSystemCore->graphicSystem->imageBufferManager->carregar("tiles","data//imagem//tilemap_01.png");


    GBF::Imagem::SpriteFactory * spriteFactory = NULL;

    spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    GBF::Imagem::Layer::FrameLayer * tiles = spriteFactory->criarFrameLayer(0, 0,32,32);
    tiles->setFrame(0,0,640,480);
    tiles->setTiles(20,30);
    tiles->setPixelTile(32,32);
    tiles->iniciarOrdenado(4);
    tiles->camera.setBottom();
    delete(spriteFactory);

    GBF::Ponto ponto;

    bool descer = tiles->camera.isTop();

	while(true) {
		if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}

		//desenha a tela de fundo
		tiles->desenhar();
        tiles->camera.show();

        /*if (descer){
			tiles->camera.runDown(1);
			if (tiles->camera.isBottom()){
			    descer=false;
            }
        } else {
			tiles->camera.runUp(1);
			if (tiles->camera.isTop()){
			    descer=true;
            }
        }*/
        ponto=tiles->camera.getPosicao();

		frameworkGBF->writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,0,100,"x:%d y:%d",ponto.x,ponto.y);

		//realiza refresh, fps, flip
		frameworkGBF->atualizar();
	}
    if (frameworkGBF){
//        delete(tiles);
        delete(frameworkGBF);
    }
	return 0;
}

