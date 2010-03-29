#ifndef JOGADOR_H
#define JOGADOR_H

#include <GBF/Character.h>
#include <GBF/SpriteFactory.h>
#include <GBF/InputSystem.h>

class Jogador : public Character::Character
{
    public:
        Jogador();
        virtual ~Jogador();

        void update(GBF::Kernel::Input::InputSystem * input);
    protected:
    private:
};

#endif // JOGADOR_H
