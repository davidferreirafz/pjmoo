#ifndef _JOGADOR_H
#define _JOGADOR_H

#include <GBF/InputSystem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/FrameLayer.h>
#include <GBF/TimerRegressive.h>
#include "Lutador.h"

//Personagem do Jogo
class Jogador : public Lutador
{
    public:
        Jogador();
        virtual ~Jogador();
        void draw();
        GBF::Area getAreaColisao();
        bool colidiu(GBF::Area b);
        void inicializar();

    protected:
        virtual void limites();
        virtual std::string getSpriteNome(Estado estado);

    private:
        GBF::Point ajustar();

};
#endif
