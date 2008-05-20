
#ifndef _USERINTERFACENOVORECORDE_H
#define _USERINTERFACENOVORECORDE_H

#include <GBF/UIWindow.h>

#include <GBF/RSRecorde.h>
#include <GBF/WriteManager.h>
#include <GBF/GFX.h>
#include <GBF/CronometroDecrescente.h>
#include <GBF/CronometroCrescente.h>
#include <GBF/GBF.h>
#include <string>

#include <GBF/GraphicSystemUtility.h>
#include <GBF/UIVisualSolido.h>

#include "UI.h"
#include "UITecladoVirtual.h"
#include "UITextField.h"
#include "UINumberField.h"


class UIWindowRecorde : public UserInterface::Window::UIWindow
{

  private:
    UIFonteExtendida fonteTitulo;
    UIFonteExtendida fonteAviso;

    UITecladoVirtual teclado;
    UITextField textNome;
    UINumberField textPonto;

    int nomePosicao;

    RankingSystem::RSRecorde recorde;

    bool showErro;

    UserInterface::Visual::UIVisualSolido * uiVisualComponentes;

  protected:
    void atualizar();
    //Desenha o botão de ação da janela
    void desenharForeground();

    //Desenha o conteudo da janela
    void desenharConteudo();

    //Efetua as ações de acordo com a posição do cursor
    int confirmarSelecao();



  public:

    static const int BOTAO_SALVAR;

    //Inicializa as configurações da caixa de texto
    virtual void inicializar();
    UIWindowRecorde();
    //Destrutor
    ~UIWindowRecorde();

    //Estilo Visual a ser Aplicado no Componente
    void setVisualComponentes(UserInterface::Visual::UIVisualSolido * visual);


    //Define a fonte a ser usada pelo Titulo
    void setFonteTitulo(std::string fonte);
    void setFonteTecladoVirtual(std::string fonteTeclado, std::string fonteControle);
    void setFonteEdit(std::string fonteLabel, std::string fonteValue);
///////////////////


  public:
    //Retorna o TopSystemRecorde
    RankingSystem::RSRecorde getRecorde();

    //Atribui um TopSystemRecorde para complementar os dados
    void setRecorde(RankingSystem::RSRecorde recorde);

    //Gerencia o controle do cursor (navegação) e as opções selecionadas
    bool isAcao(int tipoAcao);

};
#endif
