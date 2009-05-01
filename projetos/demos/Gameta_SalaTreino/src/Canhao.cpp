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

    posicao.x=x;
    posicao.y=y;

    posicaoBala=posicao;
    posicaoBala.x=posicao.x-10;
    posicaoBala.y=posicao.y+1;

    bala->setPosicao(posicaoBala);
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
        posicaoBala.x-=6;
        if (posicaoBala.x<0){
            posicaoBala.x=posicao.x-10;
            posicaoBala.y=posicao.y+1;
            fumaca->animacao.setInicio();
            tempo.setResetar();
        }
    }
}
void Canhao::desenhar()
{
    if(tempo.isTerminou()){
        bala->desenhar(posicaoBala.x,posicaoBala.y);
        if (!fumaca->animacao.isFim()){
            fumaca->desenhar(posicao.x-30,posicao.y-20);
        }

        Regiao r= getAreaColisao();

        gsGFX->setColor(255,0,0);
        gsGFX->retangulo(r.posicao.x,r.posicao.y,r.dimensao.w,r.dimensao.h);
    }
}
Regiao Canhao::getAreaColisao()
{
    Regiao regiao;

    regiao.posicao.x=1;   regiao.posicao.y=1;
    regiao.dimensao.w=22;  regiao.dimensao.h=15;

    ////////////
    regiao.posicao.x=posicaoBala.x+regiao.posicao.x;
    regiao.posicao.y=posicaoBala.y+regiao.posicao.y;

    return regiao;
}
