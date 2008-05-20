#ifndef UIFIELD_H
#define UIFIELD_H

#include <GBF/UIComponente.h>
#include <GBF/GraphicSystemUtility.h>
#include <GBF/CronometroCrescente.h>
#include <GBF/UIVisual.h>

#include "UI.h"

class UIField: public UserInterface::UIComponente , public GBF::Kernel::Graphic::GraphicSystemUtility
{
  public:
    UIField();
    virtual ~UIField();

    void setLabel(std::string label);

    //Define a fonte a ser usada pelo label
    void setFonteLabel(std::string fonte);
    //Define a fonte a ser usada pelo Campo
    void setFonteCampo(std::string fonte);

    void maxLength(int length);
    void showCursor(bool show);
    void setCursorPosicao(int posicao);
    void setVisual(UserInterface::Visual::UIVisual * visual);

  protected:

    UIFonteExtendida fonteLabel;
    UIFonteExtendida fonteCampo;

    UICursor cursor;

    //Posicao do cursor no campo
    int indice;

    //Desenha o conteudo da janela
    void desenharBackground();
    virtual void desenharConteudo()=0;
    void desenharForeground();

    void atualizar();
    void desenhar();

    GBF::Kernel::Timer::CronometroCrescente tempoBlink;

    UserInterface::Visual::UIVisual * visual;

  private:
    std::string label;
    int length;
};

#endif // UITEXTFIELD_H
