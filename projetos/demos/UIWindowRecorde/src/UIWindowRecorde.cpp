
#include "UIWindowRecorde.h"

const int UIWindowRecorde::BOTAO_SALVAR=200;

UIWindowRecorde::UIWindowRecorde()
{
    teclado.setCaracter("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 _+-$%*,.:[]!=");
    teclado.setControle(0,"GBF_UIRecorde_button_back");
    teclado.setControle(1,"GBF_UIRecorde_button_next");
    teclado.setControle(2,"GBF_UIRecorde_button_save");

    textNome.setLabel("GBF_UIRecorde_title_player");
    textNome.maxLength(10);

    textPonto.setLabel("GBF_UIRecorde_title_points");
    textPonto.maxLength(8);
    textPonto.setValue("12344321");

    nomePosicao     = 0;
    posicao.x       = 0;
    posicao.y       = 0;

    tempoEspera.setTempoOriginal(1);
    tempoEspera.setUnidade(TEMPO_CENTESIMO);
    tempoEspera.setResetar();

    showErro = false;
}
UIWindowRecorde::~UIWindowRecorde()
{
//n�o implementado
}
//Desenha o bot�o de a��o da janela
void UIWindowRecorde::desenharControles()
{
    teclado.executar();
    textNome.executar();
    textPonto.executar();
}
void UIWindowRecorde::desenharBackground()
{
    //desenhando a janela
    UserInterfaceWindow::desenharBackground();
}


//Desenha o conteudo da janela
void UIWindowRecorde::desenharConteudo()
{
    //escrevendo titulo centralizado
    wsManager->escreverLocalizado(fonteTitulo.nome,fonteTitulo.posicao.x,fonteTitulo.posicao.y,"GBF_UIRecorde_title");

    textNome.setValue(recorde.nome);
    if (showErro){
//        wsManager->escreverLocalizado(fonteLabel.nome, teclado.posicao.x,teclado.posicao.y+teclado.dimensao.h,"GBF_UIRecorde_warning");
    }
}

//Inicializa as configura��es da caixa de texto
void UIWindowRecorde::inicializar()
{
    UserInterfaceWindow::inicializar();

    Dimensao d = teclado.getDimensao();

    int pX=(posicao.x+dimensao.w)/2-(d.w/2);
    int pY=(posicao.y+dimensao.h)/2;

    teclado.setPosicao(pX,pY);

    pX=posicao.x+fonteTitulo.dimensao.h;
    pY=posicao.y+(fonteTitulo.dimensao.h*1.5);

    textNome.setPosicao(pX,pY);

    pX=posicao.x+dimensao.w - textPonto.getDimensao().w - fonteTitulo.dimensao.h;

    textPonto.setPosicao(pX,pY);

}
void UIWindowRecorde::setFonteTitulo(std::string fonte)
{
    fonteTitulo.nome=fonte;
    fonteTitulo.dimensao=wsManager->getFonte(fonteTitulo.nome)->getDimensao();

    int tamanho = wsManager->getLarguraLinha(fonteTitulo.nome,"GBF_UIRecorde_title");
    fonteTitulo.posicao.x=posicao.x+(dimensao.w/2)-(tamanho/2);
    fonteTitulo.posicao.y=posicao.y;
}
void UIWindowRecorde::setFonteTecladoVirtual(std::string fonteTeclado, std::string fonteControle)
{
    teclado.setFonteTeclado(fonteTeclado);
    teclado.setFonteControle(fonteControle);
}
void UIWindowRecorde::setFonteEdit(std::string fonteLabel, std::string fonteValue)
{
    textNome.setFonteLabel(fonteLabel);
    textNome.setFonteCampo(fonteValue);

    textPonto.setFonteLabel(fonteLabel);
    textPonto.setFonteCampo(fonteValue);
    textPonto.showCursor(false);
}






//Retorna o TopSystemRecorde
TopSystemRecorde UIWindowRecorde::getRecorde()
{
    return recorde;
}
//Atribui um TopSystemRecorde para complementar os dados
void UIWindowRecorde::setRecorde(TopSystemRecorde recorde)
{
    this->recorde  = recorde;
    nomePosicao    = 0;
    tempoEspera.setResetar();
}

//Gerencia o controle do cursor (navega��o) e as op��es selecionadas
bool UIWindowRecorde::isAcao(int tipoAcao)
{
    bool salva = false;
    tempoEspera.processar();

    if (tempoEspera.isTerminou()){
        if(confirmarSelecao()==tipoAcao)
        {
            salva=true;
        }
    }

    return salva;
}

//Efetua as a��es de acordo com a posi��o do cursor
int UIWindowRecorde::confirmarSelecao()
{
    int opcao = false;
    if ((inputSystem->teclado->isKey(SDLK_RETURN)) || (inputSystem->joystick->isButtonA())){

        showErro=false;

        int selecao = teclado.getIndex();

        if ((selecao>=0)&&(selecao<teclado.getTotalCaracter())){
            recorde.nome[nomePosicao]=teclado.getCaracter();
            nomePosicao++;
        } else if (selecao==teclado.getTotalCaracter()){//controle voltar
            nomePosicao--;
        } else if (selecao==teclado.getTotalCaracter()+1){//controle avancar
            nomePosicao++;
        } else if (selecao==teclado.getTotalCaracter()+2){//controle salvar
            //if (recorde.nome[0]!=' '){
            if (strlen(recorde.nome)>1){
                opcao=BOTAO_SALVAR;
            } else {
                showErro=true;
            }
        }
        tempoEspera.setResetar();
    }

    if (nomePosicao<0){
        nomePosicao=0;
    } else if (nomePosicao>9){
        nomePosicao=9;
    }

    textNome.setCursorPosicao(nomePosicao);

    return opcao;
}


