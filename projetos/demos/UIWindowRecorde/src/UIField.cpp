#include "UIField.h"

UIField::UIField()
{
    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
    tempoBlink.setResetar();

    cursor.show=false;
    indice=0;
}

UIField::~UIField()
{
    //dtor
}

void UIField::setLabel(std::string label)
{
    this->label=label;
}

void UIField::maxLength(int length)
{
    this->length=length;
}
void UIField::showCursor(bool show)
{
    cursor.show=show;
    tempoBlink.setResetar();
}
void UIField::setCursorPosicao(int posicao)
{
    indice=posicao;
}
//Define a fonte a ser usada pelo label
void UIField::setFonteLabel(std::string fonte)
{
    fonteLabel.nome=fonte;
    fonteLabel.dimensao=wsManager->getFonte(fonteLabel.nome)->getDimensao();
}
void UIField::setFonteCampo(std::string fonte)
{
    fonteCampo.nome=fonte;
    fonteCampo.dimensao=wsManager->getFonte(fonteCampo.nome)->getDimensao();

    dimensao.h=fonteCampo.dimensao.h;
    dimensao.w=length*fonteCampo.dimensao.w;
}
void UIField::atualizar()
{
    tempoBlink.processar();

    fonteCampo.posicao.x=posicao.x;
    fonteCampo.posicao.y=posicao.y+(fonteLabel.dimensao.h*1.5);

    cursor.posicao.x=fonteCampo.posicao.x + (indice * fonteCampo.dimensao.w);
    cursor.posicao.y=fonteCampo.posicao.y+fonteCampo.dimensao.h;
}
void UIField::desenhar()
{
    desenharBackground();

    desenharConteudo();

    desenharForeground();
}
void UIField::desenharBackground()
{
    //desenhando campo
    int pY=posicao.y+(fonteLabel.dimensao.h*1.2);
    int dH=fonteLabel.dimensao.h*1.2;

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(posicao.x,pY,dimensao.w,dH);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(posicao.x,pY,dimensao.w,dH);

    //escrevendo label (Jogador - Pontos)
    wsManager->escreverLocalizado(fonteLabel.nome, posicao.x,posicao.y,label);
}
void UIField::desenharForeground()
{
    //desenhando cursor
    if (cursor.show){
        if (tempoBlink.getTempo()%2!=0){
            graphicSystem->gfx->setColor(250,250,250);
            graphicSystem->gfx->retanguloPreenchido(cursor.posicao.x,cursor.posicao.y,fonteCampo.dimensao.w,2);
        }
    }
}

