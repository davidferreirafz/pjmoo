
#ifndef _JOGO_H
#define _JOGO_H

#include "Controle.h"
#include <GBF/GAT.h>

#include <GBF/UserInterfaceWindowTitulo.h>

#include <GBF/UserInterfaceWindow.h>

#include <GBF/UserInterfaceMenuTextoTransparente.h>

#include <GBF/UserInterfaceMenuItemTexto.h>

#include <GBF/UserInterfaceVisualImagem.h>


//#include "UserInterfaceVisual.h"
//#include "UserInterfaceVisualSolido.h"
class Jogo : public GAT
{
  public:
    int main(int argc, char * argv[]);

    //Construtor
    Jogo(int argc, char * argv[]);

    //Destrutor
    virtual ~Jogo();


  protected:
    //Inicializa os recursos utilizados no jogo.
    //Ex.: Imagens, sons, fontes, configuração do modo gráfico e etc..
    void inicializarRecursos();

    void menuPrincipal();

    void menuAjuda();

    void menuCredito();

    void menuSobre();

    void jogoNovo();

    void jogoExecutando();

    void jogoPause();

    void jogoFaseCarregar();

    void jogoFaseFinalizada();

    void jogoGameOver();

    void jogoZerado();

    bool gatilhoJogoFaseCarregar();

    void gatilhoMenuPrincipal();


  private:
    Controle controle;


  protected:
    UserInterfaceWindowTitulo * janelaSobre;

    UserInterfaceWindowTitulo * janelaCredito;

    UserInterfaceWindowTitulo * janelaAjuda;

    UserInterfaceWindow * janelaZerado;

    UserInterfaceWindow * janelaGameOver;

    UserInterfaceWindow * janelaFaseFinalizada;

};
#endif
