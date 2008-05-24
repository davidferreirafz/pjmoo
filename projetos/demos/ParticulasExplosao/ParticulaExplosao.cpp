/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include <GBF/GBFramework.h>
#include "SystemColor.h"

#define NUMERO 200

int raioAlcance = 50;
int raioOrigemX = 0;
int raioOrigemY = 0;

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

    raioOrigemX=origemX;
    raioOrigemY=origemY;

    for (int i=0; i<NUMERO; i++){
        velocidade = ((float)(rand()%9000)/1000);
        angulo     = ((float)(rand()%6280)/1000);
        sistema[i].posicao.x    = raioOrigemX;
        sistema[i].posicao.y    = raioOrigemY;
        sistema[i].velocidade.x = velocidade * cos(angulo);
        sistema[i].velocidade.y = velocidade * sin(angulo);
        sistema[i].energia      = rand()%(raioAlcance*2);
        sistema[i].ativa        = true;
        sistema[i].cor.h = 60;
        sistema[i].cor.s = 1.0;
        sistema[i].cor.v = 1.0;
    }
}
void atualizarEfeito()
{
    float qx, qy, qr;
    qr = pow(float(raioAlcance), 2); //quadrado da soma dos raios

    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            sistema[i].posicao.x  += sistema[i].velocidade.x;
            sistema[i].posicao.y  += sistema[i].velocidade.y;
            sistema[i].energia--;

            qx = pow(float(raioOrigemX-sistema[i].posicao.x), 2); //quadrado da distância em x
            qy = pow(float(raioOrigemY-sistema[i].posicao.y), 2); //quadrado da distância em y

            if ((sistema[i].energia<0)||(qx + qy >= qr)){
                sistema[i].ativa = false;
            } else {
                sistema[i].cor.h -=5;
	            if (sistema[i].cor.h<0){
					sistema[i].cor.h=0;
					sistema[i].cor.v-=0.01;
					if (sistema[i].cor.v<0){
						sistema[i].cor.v=0;
					}
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
    frameworkGBF->setTitulo("GBF :: Particula Explosao","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,false,GBF::Kernel::FPS::FPS_LIMITADO);
    frameworkGBF->inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

	while(true) {
		if (frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}

		if ((frameworkGBF->inputSystemCore->inputSystem->teclado->isKey(SDLK_RETURN))&&(isTerminouEfeito())){
			criarEfeito(320,240);
		}

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
