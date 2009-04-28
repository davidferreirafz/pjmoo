#include "Canhao.h"

Canhao::Canhao(int x, int y)
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("fumaca");
    fumaca=spriteFactory->criarSpriteItem(0,0,69,63,7,1);
    fumaca->animacao.setAutomatico(true);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("bala");
    bala=spriteFactory->criarSpriteItem(0,0,24,20,0,0);
    bala->animacao.setAutomatico(true);
    delete(spriteFactory);

    ponto.x=x;
    ponto.y=y;
    xBala=x-10;

    bala->setPosicao(xBala,y);
    fumaca->setPosicao(x,y);
    tempo.setTempoOriginal(2+(2*rand()%10));
    tempo.setUnidade(GBF::Kernel::Timer::TEMPO_SEGUNDO);
    tempo.setResetar();
}

Canhao::~Canhao()
{
   delete(fumaca);
   delete(bala);
}

void Canhao::acao()
{
    tempo.processar();

    if(tempo.isTerminou()){
        xBala-=6;
        if (xBala<0){
            xBala=ponto.x-10;
            fumaca->animacao.setInicio();
            tempo.setResetar();
        }
    }
}

void Canhao::desenhar()
{
    if(tempo.isTerminou()){
        bala->desenhar(xBala,ponto.y+1);
        if (!fumaca->animacao.isFim()){
            fumaca->desenhar(ponto.x-30,ponto.y-20);
        }
    }
}
