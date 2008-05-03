#include "UITextField.h"

UITextField::UITextField()
{

}
UITextField::~UITextField()
{
    //dtor
}
void UITextField::setValue(std::string value)
{
    this->value=value;
}
void UITextField::desenharConteudo()
{
    wsManager->escrever(fonteCampo.nome, fonteCampo.posicao.x, fonteCampo.posicao.y,"%s"  ,value.c_str());
}


