#ifndef PERSONAGEMADVENTURE_H
#define PERSONAGEMADVENTURE_H

#include <GBF/Personagem.h>

class PersonagemAdventure : public Personagem::Personagem
{
 public:
    PersonagemAdventure();
    virtual ~PersonagemAdventure();

    virtual void setPisouChao() = 0;
    virtual void setBateuCabeca() = 0;
    bool isDireita();
    bool isEsquerda();
 protected:
 private:
};

#endif // PERSONAGEMADVENTURE_H
