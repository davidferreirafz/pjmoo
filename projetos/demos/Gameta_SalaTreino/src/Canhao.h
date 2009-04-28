#ifndef CANHAO_H
#define CANHAO_H

#include <GBF/SpriteItem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/CronometroDecrescente.h>

class Canhao
{
    public:
        Canhao(int x, int y);
        virtual ~Canhao();
        void desenhar();
        void acao();
    protected:
        GBF::Imagem::Sprite::SpriteItem * fumaca;
        GBF::Imagem::Sprite::SpriteItem * bala;
        GBF::Ponto ponto;
        int xBala;
    private:
        GBF::Kernel::Timer::CronometroDecrescente tempo;
};

#endif // CANHAO_H