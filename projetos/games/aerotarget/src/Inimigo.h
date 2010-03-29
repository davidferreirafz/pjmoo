#ifndef INIMIGO_H
#define INIMIGO_H

#include <GBF/Character.h>
#include <GBF/SpriteFactory.h>
#include <GBF/InputSystem.h>

class Inimigo : public Character::Character
{
    public:
        Inimigo();
        virtual ~Inimigo();
        void update(GBF::Kernel::Input::InputSystem * input);
    protected:
    private:
        void iniciar();
        int velocidade;
};

#endif // INIMIGO_H
