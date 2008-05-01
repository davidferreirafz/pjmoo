
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

class UserInterfaceNovoRecorde : public UserInterfaceWindow, public GraphicSystemUtility
{

  private:
    std::string fonteTitulo;
    std::string fonteLabel;
    std::string fonteCampo;
    std::string fonteTeclado;
    std::string fonteControle;

    Dimensao dimensaoFonteTitulo;
    Dimensao dimensaoFonteLabel;
    Dimensao dimensaoFonteCampo;
    Dimensao dimensaoFonteTeclado;
    Dimensao dimensaoFonteControle;
    Dimensao caixaTeclado;

    int totalTeclasTeclado;
    int totalTeclas;
    unsigned int totalTeclasControle;
    unsigned int tamanhoMaiorTeclaControle;
    int tecladoSelecao;

    std::string tecladoControle[3];
    //Armazena a letras do teclado
    char miniTeclado[50];

    int nomePosicao;

    TopSystemRecorde recorde;

  protected:
    //Desenha o botão de ação da janela
    void desenharBotao();

    //Desenha o conteudo da janela
    void desenharConteudo();

    void desenharBackground();


    Ponto caixaPosicao;

  public:

    static const int BOTAO_SALVAR;

    //Inicializa as configurações da caixa de texto
    virtual void inicializar();

    UserInterfaceNovoRecorde();
    //Destrutor
    ~UserInterfaceNovoRecorde();

    //Define a fonte a ser usada pelo teclado virtual
    void setFonteTeclado(std::string fonte);

    //Define a fonte a ser usada pelo label
    void setFonteLabel(std::string fonte);

    //Define a fonte a ser usada pelo Controle
    void setFonteControle(std::string fonte);

    //Define a fonte a ser usada pelo Titulo
    void setFonteTitulo(std::string fonte);

    //Define a fonte a ser usada pelo Campo
    void setFonteCampo(std::string fonte);

///////////////////

  protected:
    //Efetua as ações de acordo com a posição do cursor
    int confirmar();

    //Efetua o controle sobre a navegação do cursor
    void navegar();
  private:
    TimerSystemCronometroDecrescente tempoNavegacao;

    TimerSystemCronometroCrescente tempoBlink;
  public:
    //Retorna o TopSystemRecorde
    TopSystemRecorde getRecorde();

    //Atribui um TopSystemRecorde para complementar os dados
    void setRecorde(TopSystemRecorde recorde);

    //Gerencia o controle do cursor (navegação) e as opções selecionadas
    bool isAcao(int tipoAcao);

};
#endif
