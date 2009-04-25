#ifndef _COLISAO_H
#define _COLISAO_H

#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include <GBF/Personagem.h>
#include <GBF/FrameLayer.h>


#include "PersonagemAdventure.h"

struct Regiao
{
    GBF::Ponto posicao;
    GBF::Dimensao dimensao;
};




class Colisao
{
  public:
    static bool box(Regiao a, Regiao b);

    static void cenario(PersonagemAdventure * personagem,GBF::Imagem::Layer::FrameLayer * layer);

  protected:
    static GBF::Ponto calcularInicio(Regiao regiao,GBF::Dimensao tile);
    static GBF::Ponto calcularFim(Regiao regiao,GBF::Dimensao tile);
    static bool brick(int indice);
};


#endif
