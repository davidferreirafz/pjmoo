#include "UITecladoVirtual.h"

UITecladoVirtual::UITecladoVirtual()
{
    posicao.x = 0;
    posicao.y = 0;
    selecao   = 0;

    tempoEspera.setTempoOriginal(1);
    tempoEspera.setUnidade(TEMPO_CENTESIMO);
    tempoEspera.setResetar();

    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
    tempoBlink.setResetar();
}
UITecladoVirtual::~UITecladoVirtual()
{
}
//Define a fonte a ser usada pelo teclado virtual
void UITecladoVirtual::setFonteTeclado(std::string fonte)
{
    fonteTeclado.nome=fonte;
    fonteTeclado.dimensao=wsManager->getFonte(fonteTeclado.nome)->getDimensao();

    dimensao.w=10 * (fonteTeclado.dimensao.w + int(fonteTeclado.dimensao.w/4));
    dimensao.h=5  * (fonteTeclado.dimensao.h + int(fonteTeclado.dimensao.h/4));
}
//Define a fonte a ser usada pelo label
void UITecladoVirtual::setFonteControle(std::string fonte)
{
    fonteControle.nome=fonte;
    fonteControle.dimensao=wsManager->getFonte(fonteControle.nome)->getDimensao();

    tamanhoControle  = 0;
    int tmp=0;
    for (int i=0; i<getTotalControle();i++){
        tmp = wsManager->getLarguraLinha(fonteControle.nome,controle[i].c_str());
        if (tmp>getTamanhoControle()){
            tamanhoControle=tmp;
        }
    }
}
//Estilo Visual a ser Aplicado no Componente
void UITecladoVirtual::setVisual(UserInterfaceVisual * visual)
{
    this->visual=visual;
}
int UITecladoVirtual::getTotalCaracter()
{
    return strlen(caracter);
}
int UITecladoVirtual::getTotalControle()
{
    return 3;
}
int UITecladoVirtual::getTotalTeclas()
{
    return getTotalCaracter()+getTotalControle();
}

int UITecladoVirtual::getTamanhoControle()
{
   return tamanhoControle;
}
void UITecladoVirtual::setCaracter(std::string caracteres)
{
    strcpy(caracter,caracteres.c_str());
}
void UITecladoVirtual::setControle(int index, std::string texto)
{
    controle[index]=texto;
}
Dimensao UITecladoVirtual::getDimensao()
{
    return dimensao;
}
void UITecladoVirtual::atualizar()
{
    tempoEspera.processar();
    tempoBlink.processar();

    if (tempoEspera.isTerminou()){
        navegar();
    }

    if (visual!=NULL){
        Dimensao d  = dimensao;

        d.w=dimensao.w+getTamanhoControle()+(fonteTeclado.dimensao.w);
  //  int auxLargura=dimensao.w+getTamanhoControle()+(fonteTeclado.dimensao.w);


//    graphicSystem->gfx->retanguloPreenchido(posicao.x,posicao.y,auxLargura,dimensao.h);
//    graphicSystem->gfx->retangulo(posicao.x,posicao.y,auxLargura,dimensao.h);

        visual->aplicar(posicao,d);
    }
}
void UITecladoVirtual::desenhar()
{
    desenharBackground();
    desenharConteudo();
}
//Efetua o controle sobre a navegação do cursor
void UITecladoVirtual::navegar()
{
    if ((inputSystem->teclado->isKey(SDLK_LEFT))||(inputSystem->joystick->isAxeLeft())){
            selecao--;
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_RIGHT))||(inputSystem->joystick->isAxeRight())){
            selecao++;
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_DOWN))||(inputSystem->joystick->isAxeDown())){
            if (selecao<40){
                selecao+=10;
            } else {//if (selecao>=teclado.getTotalTeclas()){
                selecao++;
            }
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_UP))||(inputSystem->joystick->isAxeUp())){
            if ((selecao>=10)&&(selecao<getTotalCaracter())){
                selecao-=10;
            } else {
                selecao--;
            }
            tempoEspera.setResetar();
    }

    if (selecao<0){
        selecao=0;
    } else if (selecao>getTotalTeclas()-1){
        selecao=getTotalTeclas()-1;
    }
}

char UITecladoVirtual::getCaracter()
{
    return caracter[selecao];
}
int UITecladoVirtual::getIndex()
{
    return selecao;
}
void UITecladoVirtual::desenharBackground()
{
    //desenhando caixa do teclado
/*    int auxLargura=dimensao.w+getTamanhoControle()+(fonteTeclado.dimensao.w);

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(posicao.x,posicao.y,auxLargura,dimensao.h);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(posicao.x,posicao.y,auxLargura,dimensao.h);
*/
    if (visual!=NULL){
        visual->desenhar();
    }

    graphicSystem->gfx->setColor(255,255,0);

    int letra=0;

    Ponto tecla;
    tecla.x=posicao.x + (fonteTeclado.dimensao.w/4);
    tecla.y=posicao.y;

    Ponto cursor;
    cursor.x=posicao.x + (fonteTeclado.dimensao.w * 0.2);
    cursor.y=posicao.y + (fonteTeclado.dimensao.h * 0.1);

    Dimensao cursorDimensao;
    cursorDimensao.w=fonteTeclado.dimensao.w;
    cursorDimensao.h=fonteTeclado.dimensao.h;

    int espacoHorizontal = fonteTeclado.dimensao.w + int(fonteTeclado.dimensao.w / 4);
    int espacoVertical   = fonteTeclado.dimensao.h + int(fonteTeclado.dimensao.h / 4);

    //Painel do teclado
    for (int l=0;l<5;l++){
        for (int c=0;c<10;c++){
            wsManager->escrever(fonteTeclado.nome, tecla.x +(espacoHorizontal*c),tecla.y+(espacoVertical*l),"%c",caracter[letra]);

            //Desenhando cursor da selecao de tecla
            if ((selecao==letra)&&(tempoBlink.getTempo()%2==0)){
                graphicSystem->gfx->retangulo(cursor.x+(espacoHorizontal*c),cursor.y+(espacoVertical*l),cursorDimensao.w,cursorDimensao.h);
            }
            letra++;
        }
    }
}

void UITecladoVirtual::desenharConteudo()
{
    graphicSystem->gfx->setColor(255,255,0);

    Ponto tecla;
    tecla.x=posicao.x + (fonteTeclado.dimensao.w/4);
    tecla.y=posicao.y;

    tecla.x=posicao.x + (10 * (fonteTeclado.dimensao.w + fonteTeclado.dimensao.w*0.3));
    tecla.y=posicao.y + dimensao.h - (getTotalControle() * fonteControle.dimensao.h);

    Ponto cursor;
    cursor.x=tecla.x - int(fonteControle.dimensao.w*0.25);
    cursor.y=tecla.y;

    Dimensao cursorDimensao;
    cursorDimensao.w=getTamanhoControle() + (fonteControle.dimensao.w*0.5);
    cursorDimensao.h=fonteControle.dimensao.h;

   //Painel das teclas de controles
    for (int ic=getTotalControle()-1;ic>=0;ic--){
        wsManager->escreverLocalizado(fonteControle.nome, tecla.x,tecla.y+(fonteControle.dimensao.h*ic),controle[ic].c_str());
    }

    //Desenhando cursor das teclas de controle
    if (tempoBlink.getTempo()%2==0){
        if (selecao>=getTotalCaracter()){
            int t=selecao-getTotalCaracter();
            graphicSystem->gfx->retangulo(cursor.x,cursor.y+(fonteControle.dimensao.h*t),cursorDimensao.w,cursorDimensao.h);
        }
    }
}
