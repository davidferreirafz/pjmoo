#ifndef UITEXTFIELD_H
#define UITEXTFIELD_H

#include <GBF/UserInterfaceComponente.h>
#include <GBF/GraphicSystemUtility.h>
#include <GBF/TimerSystemCronometroCrescente.h>

#include "UI.h"

class UITextField: public UserInterfaceComponente , public GraphicSystemUtility
{
  public:
    UITextField();
    virtual ~UITextField();

    void executar();
    void setLabel(std::string label);
    void setValue(std::string value);
    void setPosicao(int x, int y);

    //Define a fonte a ser usada pelo label
    void setFonteLabel(std::string fonte);
    //Define a fonte a ser usada pelo Campo
    void setFonteCampo(std::string fonte);

    void maxLength(int length);

    Dimensao getDimensao();

    void showCursor(bool show);
    void setCursorPosicao(int posicao);

  protected:
    Ponto posicao;
    Dimensao dimensao;

    UIFonteReferencia fonteLabel;
    UIFonteExtendida fonteCampo;

    UICursor cursor;

    //Posicao do cursor no campo
    int indice;

    //Desenha o conteudo da janela
    void desenharBackground();
    void desenharConteudo();
    void desenharControles();
    void update();

    TimerSystemCronometroCrescente tempoBlink;

  private:
    std::string label;
    std::string value;
    int length;

};

#endif // UITEXTFIELD_H
