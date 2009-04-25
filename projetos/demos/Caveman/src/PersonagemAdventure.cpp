#include "PersonagemAdventure.h"

PersonagemAdventure::PersonagemAdventure()
{
}

PersonagemAdventure::~PersonagemAdventure()
{
}

bool PersonagemAdventure::isDireita()
{
    if (getSpritePrincipal()->getDirecao()==GBF::Imagem::Sprite::DR_DIREITA){
        return true;
    } else {
        return false;
    }
}
bool PersonagemAdventure::isEsquerda()
{
    if (getSpritePrincipal()->getDirecao()==GBF::Imagem::Sprite::DR_ESQUERDA){
        return true;
    } else {
        return false;
    }
}
