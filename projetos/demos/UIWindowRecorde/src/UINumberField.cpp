#include "UINumberField.h"

UINumberField::UINumberField()
{
    //ctor
}

UINumberField::~UINumberField()
{
    //dtor
}
void UINumberField::setValue(unsigned int value)
{
    this->value=value;
}
void UINumberField::desenharConteudo()
{
    wsManager->escrever(fonteCampo.nome, fonteCampo.posicao.x, fonteCampo.posicao.y,"%08d",value);
}
