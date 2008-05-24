/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include <GBF/GBFramework.h>

#include "SystemColor.h"

#define NUMERO 5000

float ambienteVento     = 0;
float ambienteGravidade = 0.098;

int quedaMaxima  = 200;
int quedaOrigemY = 0;
int quedaLargura = 100;


struct Particula
{
    GBF::PontoVirtual posicao;
    GBF::PontoVirtual velocidade;
    GBF::PontoVirtual posicaoAntiga;
    int energia;
    bool ativa;
    HSV cor;
};

Particula sistema[NUMERO];


void criarEfeito(int origemX, int origemY)
{
    float angulo, velocidade;
	quedaOrigemY=origemY;

    for (int i=0; i<NUMERO; i++){
		if (sistema[i].ativa==false){
	        velocidade = ((float)(rand()%2000)/1000);
	        angulo     = ((float)(rand()%6280)/1000);
	        sistema[i].posicao.x    = origemX +(rand()%quedaLargura);
	        sistema[i].posicao.y    = quedaOrigemY;
	        sistema[i].velocidade.x = (velocidade/8) * cos(angulo);
	        sistema[i].velocidade.y = velocidade * sin(angulo);
	        sistema[i].energia      = quedaMaxima;
	        sistema[i].ativa        = true;
	        sistema[i].cor.h = 240;
	        sistema[i].cor.s = 1.0;
	        sistema[i].cor.v = 1.0;

			if (sistema[i].velocidade.y > 0){
				sistema[i].velocidade.y *= -1;
			}
		}
    }
}
void atualizarEfeito()
{
	int final = quedaOrigemY+quedaMaxima;
	int inicioCor = final - (int(final/5)*3);

    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            sistema[i].posicao.x  += sistema[i].velocidade.x;
            sistema[i].posicao.y  += sistema[i].velocidade.y;
            sistema[i].velocidade.x  += ambienteVento;
            sistema[i].velocidade.y  += ambienteGravidade;
            sistema[i].energia--;

            if ((sistema[i].energia<0)||(sistema[i].posicao.y>final)){
                sistema[i].ativa = false;
                sistema[i].energia = 0;
            } else if (sistema[i].posicao.y>inicioCor){
	            sistema[i].cor.s -= 0.02;
	            if (sistema[i].cor.s<0.20){
					sistema[i].cor.s=0.20;
				}
			}
        }
    }
}

void desenharEfeito()
{
    static GBF::Kernel::Graphic::GraphicSystem * graphicSystem = GBF::Kernel::Graphic::GraphicSystem::getInstance();

    graphicSystem->gfx->setColor(255,255,255);
    graphicSystem->gfx->travar();
    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
			RGB tcor = SystemColor::forRGB(sistema[i].cor);
            graphicSystem->gfx->setColor(tcor.r,tcor.g,tcor.b);
            graphicSystem->gfx->putPixel(int(sistema[i].posicao.x),int(sistema[i].posicao.y));
        }
    }
    graphicSystem->gfx->setColor(0,255,0);
    graphicSystem->gfx->linha(0,300,640,300);
    graphicSystem->gfx->destravar();
}

bool isTerminouEfeito()
{
    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            return false;
        }
    }
    return true;
}


//////////////////////////////////////////////
// Entry point
int main(int argc, char *argv[])
{
	GBF::GBFramework * frameworkGBF = new GBF::GBFramework();

    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF :: Particula - Queda d'agua","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_CONTADOR);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);
    frameworkGBF->setFPS(false);

	while(true) {

		if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}
		if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_g)){
			ambienteGravidade+=0.1;
        }
		if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_v)){
			ambienteVento+=0.1;
		}

		//if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_p))&&(isTerminouEfeito())){
        //if (isTerminouEfeito()){
			criarEfeito(200,100);
		//}

        desenharEfeito();
        atualizarEfeito();
		frameworkGBF->atualizar();
		frameworkGBF->graphicSystemCore->clear();


	}

    if (frameworkGBF){
        delete(frameworkGBF);
    }

	return 0;
}
