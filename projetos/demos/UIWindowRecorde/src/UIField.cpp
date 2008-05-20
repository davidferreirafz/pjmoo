#include "UIField.h"

UIField::UIField()
{
    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(GBF::Kernel::Timer::TEMPO_DECIMO);
    tempoBlink.setResetar();

    cursor.show=false;
    indice=0;

    visual=NULL;
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

    dimensao.w=(length*fonteCampo.dimensao.w)+(fonteCampo.dimensao.w*0.2);
    dimensao.h=(fonteCampo.dimensao.h)*1.6;
}
//Estilo Visual a ser Aplicado no Componente
void UIField::setVisual(UserInterface::Visual::UIVisual * visual)
{
    this->visual=visual;
}
void UIField::atualizar()
{
    tempoBlink.processar();

    fonteLabel.posicao.x=posicao.x;
    fonteLabel.posicao.y=posicao.y;

    fonteCampo.posicao.x=posicao.x+(fonteCampo.dimensao.w*0.2);
    fonteCampo.posicao.y=fonteLabel.posicao.y+(fonteLabel.dimensao.h*1.2)+1;

    cursor.posicao.x=fonteCampo.posicao.x + (indice * fonteCampo.dimensao.w);
    cursor.posicao.y=fonteCampo.posicao.y+fonteCampo.dimensao.h;

    if (visual!=NULL){
        GBF::Dimensao d  = dimensao;

        GBF::Ponto  p  = posicao;
               p.y= fonteLabel.posicao.y+(fonteLabel.dimensao.h*1.2)-1;

        visual->aplicar(p,dimensao);
    }
}
void UIField::desenhar()
{
    desenharBackground();

    desenharConteudo();

    desenharForeground();
}
void UIField::desenharBackground()
{
    //escrevendo label (Jogador - Pontos)
    wsManager->escreverLocalizado(fonteLabel.nome, fonteLabel.posicao.x, fonteLabel.posicao.y,label);

    if (visual!=NULL){
        visual->desenhar();
    }
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

