#ifndef CANHAO_H
#define CANHAO_H

#include <GBF/SpriteItem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/CronometroDecrescente.h>

#include "InterfaceObjeto.h"

class Canhao : public InterfaceObjeto
{
    public:
        Canhao(int x, int y);
        virtual ~Canhao();
        void desenhar();
        void acao();
        Regiao getAreaColisao();
    protected:
        GBF::Imagem::Sprite::SpriteItem * fumaca;
        GBF::Imagem::Sprite::SpriteItem * bala;
        GBF::Ponto posicao;
        GBF::Ponto posicaoBala;
    private:
        GBF::Kernel::Timer::CronometroDecrescente tempo;
};

#endif // CANHAO_H
