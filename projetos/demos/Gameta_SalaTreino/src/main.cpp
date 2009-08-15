/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <GBF/GBFramework.h>
#include <GBF/SpriteFactory.h>
#include <vector>
#include <iostream>

#include "Jogador.h"
#include "Canhao.h"

#define TOTAL_CANHAO 4

/**********************************************************************/
/* AeroTarget - Cap01 - Código do Artigo Desenvolvimento de Jogos     */
/*                        com  Software Livre                         */
/**********************************************************************/
int main(int argc, char* argv[])
{
    GBF::GBFramework frameworkGBF;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitulo("Gameta - 01","GBFramework & - Gameta");
    frameworkGBF.iniciar(304,224,16,false,GBF::Kernel::FPS::FPS_LIMITADO);
    frameworkGBF.inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("background","//data//imagem//background.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("foreground","//data//imagem//foreground.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_parado",  "//data//imagem//personagem_parado.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_andando", "//data//imagem//personagem_andando.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_recuando","//data//imagem//personagem_recuando.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_correndo","//data//imagem//personagem_correndo.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_morrendo","//data//imagem//personagem_morrendo.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_pulando", "//data//imagem//personagem_pulando.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_caindo",  "//data//imagem//personagem_caindo.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("personagem_impulsionando","//data//imagem//personagem_impulsionando.png");

    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("bala","//data//imagem//bala.png");
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->carregar("fumaca","//data//imagem//fumaca.png");

    GBF::Imagem::SpriteFactory * spriteFactory = NULL;
    spriteFactory = new GBF::Imagem::SpriteFactory("background");

    GBF::Imagem::Layer::FrameLayer * background = spriteFactory->criarFrameLayer(0, 0,304,224);
    background->setFrame(0,0,304,224);
    background->setTiles(1,1);
    background->setPixelTile(304,224);
    background->iniciarCom(0);

    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("foreground");
    GBF::Imagem::Layer::FrameLayer * foreground = spriteFactory->criarFrameLayer(0, 0,304,224);
    foreground->setFrame(0,0,304,224);
    foreground->setTiles(1,1);
    foreground->setPixelTile(304,224);
    foreground->iniciarCom(0);

    delete(spriteFactory);

    Jogador * jogador = new Jogador();
    Canhao * canhao[TOTAL_CANHAO];

    for (int i=0; i<TOTAL_CANHAO; i++){
        canhao[i]=new Canhao(276,36+((2+i)*30));
    }

	while (true) {
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
            break;
		}

		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_1)){
			canhao[0]->ativar();
		}
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_2)){
			canhao[1]->ativar();
		}
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_3)){
			canhao[2]->ativar();
		}
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_4)){
			canhao[3]->ativar();
		}
		if (frameworkGBF.inputSystemCore->inputSystem->teclado->isKey(SDLK_DELETE)){
            for (int i=0; i<TOTAL_CANHAO; i++){
                canhao[i]->desativar();
            }
		}

        frameworkGBF.writeSystem->escrever(GBF::Kernel::Write::WriteManager::defaultFont,10,460,"Gameta - Desafio");

        for (int i=0; i<TOTAL_CANHAO; i++){
            if(canhao[i]->isAtivo()){
                canhao[i]->acao();
            }
        }
        jogador->acao(frameworkGBF.inputSystemCore->inputSystem);

        for (int i=0; i<TOTAL_CANHAO; i++){
            if ((canhao[i]->isBala())&&(jogador->colidiu(canhao[i]->getAreaColisao()))){
                jogador->setBateu();
                canhao[i]->desativarBala();
                break;
            }
        }

        background->desenhar();
        jogador->desenhar();
        for (int i=0; i<TOTAL_CANHAO; i++){
            canhao[i]->desenhar();
        }

        int barra = 10 * jogador->getVida();
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->setColor(255,255,0);
        frameworkGBF.graphicSystemCore->graphicSystem->gfx->retanguloPreenchido(16,5,barra,7);

        foreground->desenhar();
		//realiza refresh, fps, flip
		frameworkGBF.atualizar();
		frameworkGBF.graphicSystemCore->clear();
	}

    delete(jogador);
    delete(background);
    delete(foreground);
    for (int i=0; i<TOTAL_CANHAO; i++){
        delete(canhao[i]);
    }


	return 0;
}

