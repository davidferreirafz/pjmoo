#ifndef _COLISAO_H
#define _COLISAO_H

#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include <GBF/Personagem.h>
#include <GBF/FrameLayer.h>


#include "Caveman.h"

struct Regiao
{
    GBF::Ponto posicao;
    GBF::Dimensao dimensao;
};




class Colisao
{
  public:
    static bool box(Regiao a, Regiao b);

    static void cenario(Caveman * personagem,GBF::Imagem::Layer::FrameLayer * layer);
};


#endif
