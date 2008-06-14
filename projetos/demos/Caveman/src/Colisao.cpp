
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


void Colisao::cenario(PersonagemAdventure * personagem, GBF::Imagem::Layer::FrameLayer * layer)
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

    GBF::Ponto celulaInicial = Colisao::calcularInicio(regiao,tile);
    //celulaInicial.x = regiao.posicao.x/tile.w;
    //celulaInicial.y = regiao.posicao.y/tile.h;

    GBF::Ponto celulaFinal = Colisao::calcularFim(regiao,tile);
    //celulaFinal.x = ((regiao.posicao.x+regiao.dimensao.w)/tile.w);
    //celulaFinal.y = ((regiao.posicao.y+regiao.dimensao.h)/tile.h);

    std::cout << "--- ---" <<std::endl;
    std::cout << " Personagem (E):"<< regiao.posicao.x <<","<< regiao.posicao.y << " cel(I): "<< celulaInicial.x <<"," << celulaInicial.y << " cel(F): "<< celulaFinal.x <<"," << celulaFinal.y <<std::endl;
    std::cout << "--- ---" <<std::endl;

    if ((celulaInicial.x >=0)&&(celulaInicial.y >=0)&&(celulaFinal.x<tela.w)&&(celulaFinal.y<tela.h)){

        for (int linha = celulaInicial.y; linha <= celulaFinal.y; linha++){
            for (int coluna = celulaInicial.x; coluna <=celulaFinal.x; coluna++){

                indice = (coluna < tela.w) ? coluna : coluna - tela.w;
                indice+= (linha < tela.h) ? linha * tela.w : (linha - tela.h) * tela.w;

                std::cout << " | " <<indice;

                if (layer->getTipoImagem(indice)>0){
                    regiaoTile.posicao.x = coluna * tile.w;
                    regiaoTile.posicao.y = linha * tile.h;

                    if (box(regiaoTile,regiao)){
                        //std::cout << " Colisao:" << indice << std::endl;

                        //if (linha==celulaInicial.y){
                        int xm = regiao.posicao.x+(regiao.dimensao.w*0.5);

                        if ((linha==celulaInicial.y)&&(coluna==int(xm/32))){
                            if ((regiao.posicao.y<=regiaoTile.posicao.y+regiaoTile.dimensao.h)&&
                            //evitar descer dos bricks - verificar
                            (regiao.posicao.y+regiao.dimensao.h>=regiaoTile.posicao.y)){
                            //(regiao.posicao.y>=regiaoTile.posicao.y+(regiaoTile.dimensao.h*0.5))){
                                std::cout << " Colisao- TET: " << indice;
                                regiao.posicao.y=regiaoTile.posicao.y+regiaoTile.dimensao.h;
                            }
                        } else if ((linha==celulaFinal.y)&&(coluna==int(xm/32))){
                            if ((regiao.posicao.y+regiao.dimensao.h >= regiaoTile.posicao.y)&&
                                //evitar subir em bricks maior que a cintura do personagem
                                (regiao.posicao.y+(regiao.dimensao.h*0.5)<=regiaoTile.posicao.y+(regiaoTile.dimensao.h*0.5))
                                ){
                                std::cout << " Colisao- CHA: " << indice;
                                regiao.posicao.y=regiaoTile.posicao.y-regiao.dimensao.h;
                                personagem->setParouCair();
                            }
                        } else if(linha==celulaFinal.y-1){
                            if ((regiao.posicao.x<=regiaoTile.posicao.x+regiaoTile.dimensao.w)&&
                                (regiao.posicao.x>=regiaoTile.posicao.x+(regiaoTile.dimensao.w*0.5))){
                                    std::cout << " Colisao- ESQ: " << indice;
                                    regiao.posicao.x=regiaoTile.posicao.x+regiaoTile.dimensao.w;
                            } else
                            //colisao direita
                            if ((regiao.posicao.x+regiao.dimensao.w>=regiaoTile.posicao.x)&&
                                (regiao.posicao.x+regiao.dimensao.w<=regiaoTile.posicao.x+(regiaoTile.dimensao.w*0.5))){
                                    std::cout << " Colisao- DIR: " << indice;
                                    regiao.posicao.x=regiaoTile.posicao.x-regiao.dimensao.w;
                                /*int tipo=layer->getTipoColisao(indice);
                                if (tipo==2){
                                    //regiao.posicao.x=regiaoTile.posicao.x-regiao.dimensao.w;
                                    //std::cout << " Colisao Tipo: " << tipo;
                                //efeito de subir as escadas se o bick for de um tipo especifico
                                    //regiao.posicao.x=regiaoTile.posicao.x-(regiaoTile.dimensao.w*0.8);
                                    //regiao.posicao.y=regiaoTile.posicao.y-regiao.dimensao.h;
                                } else {
                                    regiao.posicao.x=regiaoTile.posicao.x-regiao.dimensao.w;
                                }*/

                            }
                        }
                    }
                }
            }
        }
    }

    personagem->setPosicao(regiao.posicao.x,regiao.posicao.y);
    std::cout << " "<<std::endl;
    std::cout << " Personagem (S):"<< regiao.posicao.x <<","<< regiao.posicao.y<<std::endl;
}


GBF::Ponto Colisao::calcularInicio(Regiao regiao,GBF::Dimensao tile)
{
    GBF::Ponto ponto;

    ponto.x = regiao.posicao.x/tile.w;
    ponto.y = regiao.posicao.y/tile.h;

    return ponto;
}
GBF::Ponto Colisao::calcularFim(Regiao regiao,GBF::Dimensao tile)
{
    GBF::Ponto ponto;

    ponto.x = ((regiao.posicao.x+regiao.dimensao.w)/tile.w);
    ponto.y = ((regiao.posicao.y+regiao.dimensao.h)/tile.h);

    return ponto;
}

