#ifndef _UITECLADOVIRTUAL_H
#define _UITECLADOVIRTUAL_H


#include <GBF/UIComponente.h>
#include <GBF/InputSystemUtility.h>
#include <GBF/GraphicSystemUtility.h>
#include <GBF/CronometroDecrescente.h>
#include <GBF/CronometroCrescente.h>
#include <GBF/UIVisual.h>

#include "UI.h"

class UITecladoVirtual: public UserInterface::UIComponente , public GBF::Kernel::Input::InputSystemUtility, public GBF::Kernel::Graphic::GraphicSystemUtility
{
  private:
    //Efetua o controle sobre a navegação do cursor
    void navegar();
    GBF::Cor::RGB corCursor;

  protected:
    //Armazena a letras do teclado
    char caracter[50];
    std::string controle[3];

    GBF::Kernel::Timer::CronometroDecrescente  tempoEspera;
    GBF::Kernel::Timer::CronometroCrescente tempoBlink;
    UIFonteReferencia fonteTeclado;
    UIFonteReferencia fonteControle;
    int selecao;

    int tamanhoControle;

    UserInterface::Visual::UIVisual* visual;

    void desenharBackground();
    void desenharConteudo();

    void atualizar();
    void desenhar();


  public:
    UITecladoVirtual();
    virtual ~UITecladoVirtual();

    int getTotalCaracter();
    int getTotalControle();
    int getTotalTeclas();
    int getTamanhoControle();
    void setCaracter(std::string caracteres);
    void setControle(int index, std::string texto);

    GBF::Dimensao getDimensao();

    char getCaracter();
    int getIndex();

    //Define a fonte a ser usada pelo Controle
    void setFonteControle(std::string fonte);
    //Define a fonte a ser usada pelo teclado virtual
    void setFonteTeclado(std::string fonte);

    void setVisual(UserInterface::Visual::UIVisual * visual);
    void setCorCursor(const GBF::Cor::CorPaleta & r, const GBF::Cor::CorPaleta & g, const GBF::Cor::CorPaleta & b);
};

#endif
