#ifndef CANHAO_H
#define CANHAO_H

#include <GBF/SpriteItem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/TimerRegressive.h>

#include "InterfaceObjeto.h"

class Canhao : public InterfaceObjeto
{
    public:
        Canhao(int x, int y);
        virtual ~Canhao();
        void draw();
        void update();
        GBF::Area getAreaColisao();
        void desativarBala();
        bool isBala();
        bool isAtivo();
        void setAtivar(bool ativo);
        void setNivel(int nivel);

    protected:
        GBF::Image::Sprite::SpriteItem * fumaca;
        GBF::Image::Sprite::SpriteItem * bala;
        GBF::Point posicao;
        GBF::Point posicaoBala;

    private:
        GBF::Kernel::Timer::TimerRegressive tempo;
        bool ativo;
        bool balaAtiva;
        int velocidade;
        bool ultimoDisparo;

        void inicializar();
};

#endif // CANHAO_H
