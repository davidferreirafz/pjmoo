
#include "Colisao.h"


bool Colisao::box(Regiao a, Regiao b)
{
    if ((a.posicao.x + a.dimensao.w >= b.posicao.x)&&
        (a.posicao.x <= b.posicao.x + b.dimensao.w)&&
        (a.posicao.y + a.dimensao.h >= b.posicao.y)&&
        (a.posicao.y <= b.posicao.y + b.dimensao.h)){
            return true;
    } else {
        return false;
    }
}



void Colisao::cenario(Caveman * personagem, GBF::Imagem::Layer::FrameLayer * layer)
{
    GBF::Dimensao tile; tile.w = 32; tile.h = 32;
    GBF::Dimensao tela; tela.w = 20; tela.h = 15;
    int indice = 0;

    Regiao regiaoTile;
    regiaoTile.dimensao.w = tile.w;
    regiaoTile.dimensao.h = tile.h;

    Regiao regiao;
    regiao.posicao  = personagem->getPosicao();
    regiao.dimensao = personagem->getDimensao();

    GBF::Ponto celulaInicial;
    celulaInicial.x = regiao.posicao.x/tile.w;
    celulaInicial.y = regiao.posicao.y/tile.h;

    GBF::Ponto celulaFinal;
    celulaFinal.x = ((regiao.posicao.x+regiao.dimensao.w)/tile.w);
    celulaFinal.y = ((regiao.posicao.y+regiao.dimensao.h)/tile.h);


    if ((celulaInicial.x >=0)&&(celulaInicial.y >=0)&&(celulaFinal.x<tela.w)&&(celulaFinal.y<tela.h)){

        for (int coluna = celulaInicial.x; coluna <=celulaFinal.x; coluna++){

            for (int linha = celulaInicial.y; linha <= celulaFinal.y; linha++){
                //std::cout << " X:" << iX << " Y:" << iY;
                indice = (coluna < tela.w) ? coluna : coluna - tela.w;
                indice+= (linha < tela.h) ? linha * tela.w : (linha - tela.h) * tela.w;

                if (layer->existe(indice)){
                    regiaoTile.posicao.x = coluna * tile.w;
                    regiaoTile.posicao.y = linha * tile.h;

                    if (box(regiaoTile,regiao)){
                        //std::cout << "Colisao:" << indice;
                        //colisao com o chao
                        if ((regiao.posicao.y+regiao.dimensao.h >= regiaoTile.posicao.y)&&
                            //evitar subir em bricks maior que a cintura do personagem
                            (regiao.posicao.y+(regiao.dimensao.h/2)<=regiaoTile.posicao.y)){
                            //std::cout << " Colisao - chao";
                            regiao.posicao.y=regiaoTile.posicao.y-regiao.dimensao.h;
                            personagem->setParouCair();
                        } else
                        //colisao com o teto
                        if ((regiao.posicao.y<=regiaoTile.posicao.y+regiaoTile.dimensao.h)&&
                            //evitar descer dos bricks
                            (regiao.posicao.y>=regiaoTile.posicao.y+(regiaoTile.dimensao.h/2))){
                            //std::cout << " Colisao - teto";
                            regiao.posicao.y=regiaoTile.posicao.y+regiaoTile.dimensao.h;
                        } else
                        //colisao esquerda
                        if ((regiao.posicao.x<=regiaoTile.posicao.x+regiaoTile.dimensao.w)&&
                            (regiao.posicao.x>=regiaoTile.posicao.x+(regiaoTile.dimensao.w/2))){
                            //std::cout << " Colisao - esquerda";
                            regiao.posicao.x=regiaoTile.posicao.x+regiaoTile.dimensao.w;
                        } else
                        //colisao direita
                        if ((regiao.posicao.x+regiao.dimensao.w>=regiaoTile.posicao.x)&&
                            (regiao.posicao.x+regiao.dimensao.w<=regiaoTile.posicao.x+(regiaoTile.dimensao.w/2))){
                            //std::cout << " Colisao - direita";
                            regiao.posicao.x=regiaoTile.posicao.x-regiao.dimensao.w;
                        }
                    }
                }
            }
        }
    }

    personagem->setPosicao(regiao.posicao.x,regiao.posicao.y);
}
