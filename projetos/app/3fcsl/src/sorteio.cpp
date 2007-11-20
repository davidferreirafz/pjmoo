/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
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
#include <GBF/GBF.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/PersonagemAutomatico.h>
#include <vector>
#include <iostream>




/*****************************************************************************/
/* Programa criado para os sorteios no 3° Fórum Cearense de Software Livre   */
/* Fórum Cearense de Software Livre, Outubro de 2006 Fortaleza/Ceará/Brasil  */
/*****************************************************************************/
int main(int argc, char* argv[])
{
    int totalParticipantes = 60 ;

    if ((argc>1)&&(strcmp(argv[1], "--total")==0)){
        totalParticipantes=atoi(argv[2]);
    }

	GBF *frameworkGBF = new GBF();

	Ponto ponto;
	bool mover = false;

	ponto.x=550;
	ponto.y=600;

    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF :: Sorteio - III FCSL","David Ferreira");
    frameworkGBF->iniciar(640,480,16,true);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);


    frameworkGBF->writeSystem->carregar("bfa",frameworkGBF->getPath()+"//data//kernel//fonte//bfa.png");

//carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("figuras","//data//imagem//figuras.png");
    GSIBManager->carregar("logo","//data//imagem//logo.png");
    GSIBManager->carregar("onda","//data//imagem//ondas.png");

    SpriteFactory *spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("figuras"));

    SpritePersonagem *superTux = spriteFactory->criarSpritePersonagem(0,0,300,276,0,0);
    SpriteItem       *tux      = spriteFactory->criarSpriteItem(300,0,200,196,2,20);
    FrameLayer       *tiles    = spriteFactory->criarFrameLayer(0,276,32,32);

    SpriteItem       *onda[3];
                onda[0] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);
                onda[1] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);
                onda[2] = spriteFactory->criarSpriteItem(539,267,40,40,4,20);

    delete (spriteFactory);

    spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("logo"));
    SpriteItem *logo  = spriteFactory->criarSpriteItem(0,0,640,288,0,0);
    delete (spriteFactory);

    tiles->setFrame(0,288,640,192);
    tiles->setTiles(32,32);
    tiles->setPixelTile(20,6);
    tiles->iniciarRandomico(1);
    FrameLayerManager::getInstance()->adicionar("tiles",tiles);

    tux->setAutomatico(true);
    onda[0]->setAutomatico(true);
    onda[1]->setAutomatico(true);
    onda[2]->setAutomatico(true);


	int numero = 0;
	bool ativo = false;

	while(true) {
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}
		//Inicia a rolagem de numeros
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_SPACE)){
			ativo = true;
			mover = false;
            ponto.x = 350;
            ponto.y = 600;
		}
		//Para a rolagem revelando o numero sorteado
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_RETURN)){
			//ativo = false;
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

	    frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::console,5,450,"Use a [spacebar] para iniciar e [enter] para selecionar.");

        frameworkGBF->writeSystem->escrever("bfa",300,300,"%03d",numero);

		//se sorteio rolando, exibe a msg abaixo
		if (ativo){
		    frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::arial,310,340,"Sorteando...");
		} else if (numero>0){
			frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::arial,310,340,"Sorteado!!!");
		}

        superTux->desenhar(ponto.x,ponto.y);
		//realiza refresh, fps, flip
		frameworkGBF->atualizar();
	}

    if (frameworkGBF){
        delete(logo);
        delete(superTux);
        delete(tux);
        delete(onda[0]);
        delete(onda[1]);
        delete(onda[2]);
        delete(frameworkGBF);
    }
	return 0;
}

