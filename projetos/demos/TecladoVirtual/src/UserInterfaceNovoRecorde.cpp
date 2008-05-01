
#include "UserInterfaceNovoRecorde.h"

const int UserInterfaceNovoRecorde::BOTAO_SALVAR=200;

UserInterfaceNovoRecorde::UserInterfaceNovoRecorde()
{
    //Para não esquecer:
    //As Soluções mais simples, são as que melhor funcionam :P
    strcpy(miniTeclado,"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 _+-$%*,.:[]!=");

    tecladoControle[0]="GBF_UIRecorde_button_back";
    tecladoControle[1]="GBF_UIRecorde_button_next";
    tecladoControle[2]="GBF_UIRecorde_button_save";

    totalTeclasTeclado  = strlen(miniTeclado);
    totalTeclasControle = 3;

    totalTeclas    = totalTeclasTeclado+totalTeclasControle;
    nomePosicao    = 0;
    tecladoSelecao = 0;
    posicao.x      = 0;
    posicao.y      = 0;

    tempoNavegacao.setTempoOriginal(1);
    tempoNavegacao.setUnidade(TEMPO_CENTESIMO);
    tempoNavegacao.setResetar();

    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
    tempoBlink.setResetar();
}
UserInterfaceNovoRecorde::~UserInterfaceNovoRecorde()
{
//não implementado
}
//Desenha o botão de ação da janela
void UserInterfaceNovoRecorde::desenharBotao()
{
    graphicSystem->gfx->setColor(255,255,0);
    int letra=0;
    int espacoHorizontal = dimensaoFonteTeclado.w + int(dimensaoFonteTeclado.w / 4);
    int espacoVertical   = dimensaoFonteTeclado.h + int(dimensaoFonteTeclado.h / 4);

    Ponto tecla;
    tecla.x=caixaPosicao.x + (dimensaoFonteTeclado.w/4);
    tecla.y=caixaPosicao.y;

    Ponto cursor;
    cursor.x=caixaPosicao.x + (dimensaoFonteTeclado.w * 0.2);
    cursor.y=caixaPosicao.y + (dimensaoFonteTeclado.h * 0.1);

    Dimensao cursorDimensao;
    cursorDimensao.w=dimensaoFonteTeclado.w;
    cursorDimensao.h=dimensaoFonteTeclado.h;

    //Painel do teclado
    for (int l=0;l<5;l++){
        for (int c=0;c<10;c++){
            wsManager->escrever(fonteTeclado, tecla.x +(espacoHorizontal*c),tecla.y+(espacoVertical*l),"%c",miniTeclado[letra]);

            //Desenhando cursor da selecao de tecla
            if ((tecladoSelecao==letra)&&(tempoBlink.getTempo()%2==0)){
                graphicSystem->gfx->retangulo(cursor.x+(espacoHorizontal*c),cursor.y+(espacoVertical*l),cursorDimensao.w,cursorDimensao.h);
            }
            letra++;
        }
    }

    tecla.x=caixaPosicao.x + (10 * (dimensaoFonteTeclado.w + dimensaoFonteTeclado.w*0.3));
    tecla.y=caixaPosicao.y + caixaTeclado.h - (totalTeclasControle * dimensaoFonteControle.h);

    //Painel das teclas de controles
    for (int ic=totalTeclasControle-1;ic>=0;ic--){
        wsManager->escreverLocalizado(fonteControle, tecla.x,tecla.y+(dimensaoFonteControle.h*ic),tecladoControle[ic].c_str());
    }

    cursor.x=tecla.x - int(dimensaoFonteControle.w*0.25);
    cursor.y=tecla.y;

    cursorDimensao.w=tamanhoMaiorTeclaControle + (dimensaoFonteControle.w*0.5);
    cursorDimensao.h=dimensaoFonteControle.h;

    //Desenhando cursor das teclas de controle
    if (tempoBlink.getTempo()%2==0){
        if (tecladoSelecao>=totalTeclasTeclado){
            int t=tecladoSelecao-totalTeclasTeclado;
            graphicSystem->gfx->retangulo(cursor.x,cursor.y+(dimensaoFonteControle.h*t),cursorDimensao.w,cursorDimensao.h);
        }
    }
}
void UserInterfaceNovoRecorde::desenharBackground()
{
    UserInterfaceWindow::desenharBackground();

    int auxLargura=caixaTeclado.w+tamanhoMaiorTeclaControle+(dimensaoFonteLabel.w);

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(caixaPosicao.x,caixaPosicao.y,auxLargura,caixaTeclado.h);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(caixaPosicao.x,caixaPosicao.y,auxLargura,caixaTeclado.h);
}


//Desenha o conteudo da janela
void UserInterfaceNovoRecorde::desenharConteudo()
{
    int posicaoTextoHorizontal = 0;
    int posicaoTextoVertical   = posicao.y;

    //escrevendo titulo centralizado
    int media = wsManager->getLarguraLinha(fonteTitulo,"GBF_UIRecorde_title");
    posicaoTextoHorizontal=int (posicao.x+(dimensao.w/2)-(media/2));

    wsManager->escreverLocalizado(fonteTitulo,posicaoTextoHorizontal,posicaoTextoVertical,"GBF_UIRecorde_title");

    //escrevendo label
    posicaoTextoVertical=posicaoTextoVertical+(dimensaoFonteTitulo.h*1.5);

    int auxPlayerX = posicao.x+dimensaoFonteLabel.w*2;

    int auxPointsX = wsManager->getLarguraLinha(fonteLabel,"GBF_UIRecorde_title_points");
    auxPointsX=int (posicao.x+(dimensao.w/2)) + dimensaoFonteLabel.w*2;

    wsManager->escreverLocalizado(fonteLabel, auxPlayerX,posicaoTextoVertical,"GBF_UIRecorde_title_player");
    wsManager->escreverLocalizado(fonteLabel, auxPointsX,posicaoTextoVertical,"GBF_UIRecorde_title_points");

    //escrevendo campo
    posicaoTextoVertical=posicaoTextoVertical+(dimensaoFonteLabel.h*1.5);

    auxPlayerX-=dimensaoFonteCampo.w;
    auxPointsX-=dimensaoFonteCampo.w;

    wsManager->escrever(fonteCampo, auxPlayerX, posicaoTextoVertical,"%s"  ,recorde.nome);
    wsManager->escrever(fonteCampo, auxPointsX, posicaoTextoVertical,"%08d",recorde.pontos);

    //desenhando cursor
    if (tempoBlink.getTempo()%2!=0){
        graphicSystem->gfx->setColor(250,250,250);
        graphicSystem->gfx->retanguloPreenchido(auxPlayerX+(dimensaoFonteCampo.w*nomePosicao),posicaoTextoVertical+dimensaoFonteCampo.h,dimensaoFonteCampo.w,2);
    }
}

//Inicializa as configurações da caixa de texto
void UserInterfaceNovoRecorde::inicializar()
{
    UserInterfaceWindow::inicializar();
}


//Define a fonte a ser usada pelo teclado virtual
void UserInterfaceNovoRecorde::setFonteTeclado(std::string fonte)
{
    fonteTeclado=fonte;
    dimensaoFonteTeclado=wsManager->getFonte(fonteTeclado)->getDimensao();

    caixaTeclado.w=10 * (dimensaoFonteTeclado.w + int(dimensaoFonteTeclado.w/4));
    caixaTeclado.h=5  * (dimensaoFonteTeclado.h + int(dimensaoFonteTeclado.h/4));

    caixaPosicao.x=posicao.x + (dimensaoFonteTeclado.h*1.50);
    caixaPosicao.y=posicao.y+dimensao.h-caixaTeclado.h-dimensaoFonteTeclado.h*1.50;
}

void UserInterfaceNovoRecorde::setFonteTitulo(std::string fonte)
{
    fonteTitulo=fonte;
    dimensaoFonteTitulo=wsManager->getFonte(fonteTitulo)->getDimensao();
}
//Define a fonte a ser usada pelo label
void UserInterfaceNovoRecorde::setFonteLabel(std::string fonte)
{
    fonteLabel=fonte;
    dimensaoFonteLabel=wsManager->getFonte(fonteLabel)->getDimensao();
}
void UserInterfaceNovoRecorde::setFonteCampo(std::string fonte)
{
    fonteCampo=fonte;
    dimensaoFonteCampo=wsManager->getFonte(fonteCampo)->getDimensao();
}
//Define a fonte a ser usada pelo label
void UserInterfaceNovoRecorde::setFonteControle(std::string fonte)
{
    fonteControle=fonte;
    dimensaoFonteControle=wsManager->getFonte(fonteControle)->getDimensao();

    tamanhoMaiorTeclaControle  = 0;
    for (unsigned int i=0; i<totalTeclasControle;i++){
        if (tecladoControle[i].length()>tamanhoMaiorTeclaControle){
            tamanhoMaiorTeclaControle=wsManager->getLarguraLinha(fonteControle,tecladoControle[i].c_str());
        }
    }
}

//Retorna o TopSystemRecorde
TopSystemRecorde UserInterfaceNovoRecorde::getRecorde()
{
    return recorde;
}
//Atribui um TopSystemRecorde para complementar os dados
void UserInterfaceNovoRecorde::setRecorde(TopSystemRecorde recorde)
{
    this->recorde  = recorde;
    nomePosicao    = 0;
    tecladoSelecao = 0;
    tempoBlink.setResetar();
    tempoNavegacao.setResetar();
}

//Gerencia o controle do cursor (navegação) e as opções selecionadas
bool UserInterfaceNovoRecorde::isAcao(int tipoAcao)
{
    bool salva = false;
    tempoNavegacao.processar();
    tempoBlink.processar();

    if (tempoNavegacao.isTerminou()){
        navegar();
        if(confirmar()==tipoAcao)
        {
            salva=true;
        }

    }

    return salva;
}

//Efetua as ações de acordo com a posição do cursor
int UserInterfaceNovoRecorde::confirmar()
{
    int opcao = false;
    if ((inputSystem->teclado->isKey(SDLK_RETURN)) || (inputSystem->joystick->isButtonA())){
        if ((tecladoSelecao>=0)&&(tecladoSelecao<totalTeclasTeclado)){
            recorde.nome[nomePosicao]=miniTeclado[tecladoSelecao];
            nomePosicao++;
        } else if (tecladoSelecao==totalTeclasTeclado){//controle voltar
            nomePosicao--;
        } else if (tecladoSelecao==totalTeclasTeclado+1){//controle avancar
            nomePosicao++;
        } else if (tecladoSelecao==totalTeclasTeclado+2){//controle salvar
            if (recorde.nome[0]!=' '){
                opcao=BOTAO_SALVAR;
            }
        }
        tempoNavegacao.setResetar();
    }

    if (nomePosicao<0){
        nomePosicao=0;
    } else if (nomePosicao>9){
        nomePosicao=9;
    }

    return opcao;
}
//Efetua o controle sobre a navegação do cursor
void UserInterfaceNovoRecorde::navegar()
{
    if ((inputSystem->teclado->isKey(SDLK_LEFT))||(inputSystem->joystick->isAxeLeft())){
            tecladoSelecao--;
            tempoNavegacao.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_RIGHT))||(inputSystem->joystick->isAxeRight())){
            tecladoSelecao++;
            tempoNavegacao.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_DOWN))||(inputSystem->joystick->isAxeDown())){
            if (tecladoSelecao<40){
                tecladoSelecao+=10;
            } else {//if (tecladoSelecao>=totalTeclasTeclado){
                tecladoSelecao++;
            }
            tempoNavegacao.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_UP))||(inputSystem->joystick->isAxeUp())){
            if ((tecladoSelecao>=10)&&(tecladoSelecao<totalTeclasTeclado)){
                tecladoSelecao-=10;
            } else {
                tecladoSelecao--;
            }
            tempoNavegacao.setResetar();
    }

    if (tecladoSelecao<0){
        tecladoSelecao=0;
    } else if (tecladoSelecao>totalTeclas-1){
        tecladoSelecao=totalTeclas-1;
    }
}

