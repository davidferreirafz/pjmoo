
#ifndef _USERINTERFACENOVORECORDE_H
#define _USERINTERFACENOVORECORDE_H

#include <GBF/UserInterfaceWindow.h>

#include <GBF/TopSystemRecorde.h>
#include <GBF/WriteSystemManager.h>
#include <GBF/GraphicSystemGFX.h>
#include <GBF/TimerSystemCronometroDecrescente.h>
#include <GBF/TimerSystemCronometroCrescente.h>
#include <GBF/GBF_define.h>
#include <string>

#include <GBF/GraphicSystemUtility.h>


#include "UI.h"
#include "UITecladoVirtual.h"
#include "UITextField.h"


class UIWindowRecorde : public UserInterfaceWindow, public GraphicSystemUtility
{

  private:
    UIFonteExtendida fonteTitulo;

    UITecladoVirtual teclado;
    UITextField textNome;
    UITextField textPonto;

    int nomePosicao;

    TopSystemRecorde recorde;

    bool showErro;

  protected:
    //Desenha o bot�o de a��o da janela
    void desenharControles();

    //Desenha o conteudo da janela
    void desenharConteudo();

    void desenharBackground();

    //Efetua as a��es de acordo com a posi��o do cursor
    int confirmarSelecao();



  public:

    static const int BOTAO_SALVAR;

    //Inicializa as configura��es da caixa de texto
    virtual void inicializar();
    UIWindowRecorde();
    //Destrutor
    ~UIWindowRecorde();


    //Define a fonte a ser usada pelo Titulo
    void setFonteTitulo(std::string fonte);
    void setFonteTecladoVirtual(std::string fonteTeclado, std::string fonteControle);
    void setFonteEdit(std::string fonteLabel, std::string fonteValue);
///////////////////


  public:
    //Retorna o TopSystemRecorde
    TopSystemRecorde getRecorde();

    //Atribui um TopSystemRecorde para complementar os dados
    void setRecorde(TopSystemRecorde recorde);

    //Gerencia o controle do cursor (navega��o) e as op��es selecionadas
    bool isAcao(int tipoAcao);

};
#endif
