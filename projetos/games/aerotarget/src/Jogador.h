#ifndef JOGADOR_H
#define JOGADOR_H

#include <GBF/Personagem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/InputSystem.h>

class Jogador : public Personagem::Personagem
{
    public:
        Jogador();
        virtual ~Jogador();

        void acao(GBF::Kernel::Input::InputSystem * input);
    protected:
    private:
};

#endif // JOGADOR_H
