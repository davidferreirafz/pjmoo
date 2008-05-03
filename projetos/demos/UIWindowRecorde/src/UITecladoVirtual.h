#ifndef _UITECLADOVIRTUAL_H
#define _UITECLADOVIRTUAL_H


#include <GBF/UserInterfaceComponente.h>
#include <GBF/InputSystemUtility.h>
#include <GBF/GraphicSystemUtility.h>
#include <GBF/TimerSystemCronometroDecrescente.h>
#include <GBF/TimerSystemCronometroCrescente.h>

#include "UI.h"

class UITecladoVirtual: public UserInterfaceComponente , public InputSystemUtility, public GraphicSystemUtility
{
  private:
    //Efetua o controle sobre a navegação do cursor
    void navegar();

  protected:
    //Armazena a letras do teclado
    char caracter[50];
    std::string controle[3];

    TimerSystemCronometroDecrescente  tempoEspera;
    TimerSystemCronometroCrescente tempoBlink;
    UIFonteReferencia fonteTeclado;
    UIFonteReferencia fonteControle;
    int selecao;

    int tamanhoControle;


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

    Dimensao getDimensao();

    char getCaracter();
    int getIndex();

    //Define a fonte a ser usada pelo Controle
    void setFonteControle(std::string fonte);
    //Define a fonte a ser usada pelo teclado virtual
    void setFonteTeclado(std::string fonte);
};

#endif
