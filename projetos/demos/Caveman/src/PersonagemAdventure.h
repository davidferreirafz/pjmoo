#ifndef PERSONAGEMADVENTURE_H
#define PERSONAGEMADVENTURE_H

#include <GBF/Personagem.h>

class PersonagemAdventure : public Personagem::Personagem
{
 public:
    PersonagemAdventure();
    virtual ~PersonagemAdventure();

    virtual void setParouCair() = 0;
 protected:
 private:
};

#endif // PERSONAGEMADVENTURE_H
