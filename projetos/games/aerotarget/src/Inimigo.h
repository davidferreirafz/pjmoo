#ifndef INIMIGO_H
#define INIMIGO_H

#include <GBF/Personagem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/InputSystem.h>

class Inimigo : public Personagem::Personagem
{
    public:
        Inimigo();
        virtual ~Inimigo();
        void acao(GBF::Kernel::Input::InputSystem * input);
    protected:
    private:
        void iniciar();
        int velocidade;
};

#endif // INIMIGO_H
