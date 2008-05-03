#include "UITextField.h"

UITextField::UITextField()
{
    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
    tempoBlink.setResetar();

    cursor.show=true;
    indice=0;
}

UITextField::~UITextField()
{
    //dtor
}

void UITextField::setLabel(std::string label)
{
    this->label=label;
}
void UITextField::setValue(std::string value)
{
    this->value=value;
}
void UITextField::setPosicao(int x, int y)
{
    posicao.x=x;
    posicao.y=y;
}
void UITextField::maxLength(int length)
{
    this->length=length;
}
Dimensao UITextField::getDimensao()
{
    return dimensao;
}
void UITextField::showCursor(bool show)
{
    cursor.show=show;
    tempoBlink.setResetar();
}
void UITextField::setCursorPosicao(int posicao)
{
    indice=posicao;
}
//Define a fonte a ser usada pelo label
void UITextField::setFonteLabel(std::string fonte)
{
    fonteLabel.nome=fonte;
    fonteLabel.dimensao=wsManager->getFonte(fonteLabel.nome)->getDimensao();
}
void UITextField::setFonteCampo(std::string fonte)
{
    fonteCampo.nome=fonte;
    fonteCampo.dimensao=wsManager->getFonte(fonteCampo.nome)->getDimensao();

    dimensao.h=fonteCampo.dimensao.h;
    dimensao.w=length*fonteCampo.dimensao.w;
}

void UITextField::executar()
{
    update();

    desenharBackground();

    desenharConteudo();

    desenharControles();

    tempoBlink.processar();
}

void UITextField::desenharBackground()
{
    //desenhando campo
    int pY=posicao.y+(fonteLabel.dimensao.h*1.2);
    int dH=fonteLabel.dimensao.h*1.2;

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(posicao.x,pY,dimensao.w,dH);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(posicao.x,pY,dimensao.w,dH);
}

void UITextField::update()
{
    fonteCampo.posicao.x=posicao.x;
    fonteCampo.posicao.y=posicao.y+(fonteLabel.dimensao.h*1.5);

    cursor.posicao.x=fonteCampo.posicao.x + (indice * fonteCampo.dimensao.w);
    cursor.posicao.y=fonteCampo.posicao.y+fonteCampo.dimensao.h;
}

void UITextField::desenharConteudo()
{
    //escrevendo label (Jogador - Pontos)
    wsManager->escreverLocalizado(fonteLabel.nome, posicao.x,posicao.y,label);

    wsManager->escrever(fonteCampo.nome, fonteCampo.posicao.x, fonteCampo.posicao.y,"%s"  ,value.c_str());

    //escrevendo campos (Jogador - Pontos)
//    wsManager->escrever(fonteCampo.nome, fonteCampo.p1.x, fonteCampo.p1.y,"%s"  ,recorde.nome);
//    wsManager->escrever(fonteCampo.nome, fonteCampo.p2.x, fonteCampo.p2.y,"%08d",recorde.pontos);

}

void UITextField::desenharControles()
{
    //desenhando cursor
    if (cursor.show){
        if (tempoBlink.getTempo()%2!=0){
            graphicSystem->gfx->setColor(250,250,250);
            graphicSystem->gfx->retanguloPreenchido(cursor.posicao.x,cursor.posicao.y,fonteCampo.dimensao.w,2);
        }
    }
}

