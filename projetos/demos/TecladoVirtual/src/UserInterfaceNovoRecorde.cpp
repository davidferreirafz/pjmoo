
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

    tempoEspera.setTempoOriginal(1);
    tempoEspera.setUnidade(TEMPO_CENTESIMO);
    tempoEspera.setResetar();

    tempoBlink.setTempoOriginal(0);
    tempoBlink.setUnidade(TEMPO_CENTESIMO);
    tempoBlink.setResetar();

    showErro = false;
}
UserInterfaceNovoRecorde::~UserInterfaceNovoRecorde()
{
//não implementado
}
//Desenha o botão de ação da janela
void UserInterfaceNovoRecorde::desenharControles()
{
    graphicSystem->gfx->setColor(255,255,0);
    int letra=0;
    int espacoHorizontal = fonteTeclado.dimensao.w + int(fonteTeclado.dimensao.w / 4);
    int espacoVertical   = fonteTeclado.dimensao.h + int(fonteTeclado.dimensao.h / 4);

    Ponto tecla;
    tecla.x=caixaPosicao.x + (fonteTeclado.dimensao.w/4);
    tecla.y=caixaPosicao.y;

    Ponto cursor;
    cursor.x=caixaPosicao.x + (fonteTeclado.dimensao.w * 0.2);
    cursor.y=caixaPosicao.y + (fonteTeclado.dimensao.h * 0.1);

    Dimensao cursorDimensao;
    cursorDimensao.w=fonteTeclado.dimensao.w;
    cursorDimensao.h=fonteTeclado.dimensao.h;

    //Painel do teclado
    for (int l=0;l<5;l++){
        for (int c=0;c<10;c++){
            wsManager->escrever(fonteTeclado.nome, tecla.x +(espacoHorizontal*c),tecla.y+(espacoVertical*l),"%c",miniTeclado[letra]);

            //Desenhando cursor da selecao de tecla
            if ((tecladoSelecao==letra)&&(tempoBlink.getTempo()%2==0)){
                graphicSystem->gfx->retangulo(cursor.x+(espacoHorizontal*c),cursor.y+(espacoVertical*l),cursorDimensao.w,cursorDimensao.h);
            }
            letra++;
        }
    }

    tecla.x=caixaPosicao.x + (10 * (fonteTeclado.dimensao.w + fonteTeclado.dimensao.w*0.3));
    tecla.y=caixaPosicao.y + caixaTeclado.h - (totalTeclasControle * fonteControle.dimensao.h);

    //Painel das teclas de controles
    for (int ic=totalTeclasControle-1;ic>=0;ic--){
        wsManager->escreverLocalizado(fonteControle.nome, tecla.x,tecla.y+(fonteControle.dimensao.h*ic),tecladoControle[ic].c_str());
    }

    cursor.x=tecla.x - int(fonteControle.dimensao.w*0.25);
    cursor.y=tecla.y;

    cursorDimensao.w=tamanhoMaiorTeclaControle + (fonteControle.dimensao.w*0.5);
    cursorDimensao.h=fonteControle.dimensao.h;

    //Desenhando cursor das teclas de controle
    if (tempoBlink.getTempo()%2==0){
        if (tecladoSelecao>=totalTeclasTeclado){
            int t=tecladoSelecao-totalTeclasTeclado;
            graphicSystem->gfx->retangulo(cursor.x,cursor.y+(fonteControle.dimensao.h*t),cursorDimensao.w,cursorDimensao.h);
        }
    }
}
void UserInterfaceNovoRecorde::desenharBackground()
{
    UserInterfaceWindow::desenharBackground();

    int auxLargura=caixaTeclado.w+tamanhoMaiorTeclaControle+(fonteLabel.dimensao.w);

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(caixaPosicao.x,caixaPosicao.y,auxLargura,caixaTeclado.h);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(caixaPosicao.x,caixaPosicao.y,auxLargura,caixaTeclado.h);
}


//Desenha o conteudo da janela
void UserInterfaceNovoRecorde::desenharConteudo()
{
    int posicaoTextoVertical   = posicao.y;

    //escrevendo titulo centralizado
    Ponto titulo;
    int tamanho = wsManager->getLarguraLinha(fonteTitulo.nome,"GBF_UIRecorde_title");
    titulo.x=posicao.x+(dimensao.w/2)-(tamanho/2);
    titulo.y=posicao.y;

    wsManager->escreverLocalizado(fonteTitulo.nome,titulo.x,titulo.y,"GBF_UIRecorde_title");

    //escrevendo label (Jogador - Pontos)
    Ponto labelPlayer;
    Ponto labelPontos;

    labelPlayer.x=posicao.x+fonteLabel.dimensao.w*2;
    labelPlayer.y=titulo.y+(fonteTitulo.dimensao.h*1.5);
    labelPontos.x=(posicao.x+(dimensao.w)/2)+fonteLabel.dimensao.w*2;
    labelPontos.y=labelPlayer.y;

    wsManager->escreverLocalizado(fonteLabel.nome, labelPlayer.x,labelPlayer.y,"GBF_UIRecorde_title_player");
    wsManager->escreverLocalizado(fonteLabel.nome, labelPontos.x,labelPontos.y,"GBF_UIRecorde_title_points");

    //escrevendo campos (Jogador - Pontos)
    Ponto campoNome;
    Ponto campoPontos;

    campoNome.x=posicao.x+fonteCampo.dimensao.w;
    campoNome.y=labelPlayer.y+(fonteCampo.dimensao.h*2.8);
    campoPontos.x=(posicao.x+(dimensao.w)/2)+fonteCampo.dimensao.w;
    campoPontos.y=campoNome.y;


    Dimensao campo;
    Ponto campoPosicao;

    campo.h=fonteCampo.dimensao.h*1.8;
    campo.w=dimensao.w;
    campoPosicao.x=posicao.x+2;
    campoPosicao.y=campoNome.y-(campo.h/2)+(fonteCampo.dimensao.h/2);

    graphicSystem->gfx->setColor(0,0,0);
    graphicSystem->gfx->retanguloPreenchido(campoPosicao.x,campoPosicao.y,campo.w-4,campo.h);
    graphicSystem->gfx->setColor(206,101,99);
    graphicSystem->gfx->retangulo(campoPosicao.x,campoPosicao.y,campo.w-4,campo.h);

    wsManager->escrever(fonteCampo.nome, campoNome.x,  campoNome.y,"%s"  ,recorde.nome);
    wsManager->escrever(fonteCampo.nome, campoPontos.x,campoPontos.y,"%08d",recorde.pontos);

/////////////////

    posicaoTextoVertical=posicaoTextoVertical+(fonteTitulo.dimensao.h*1.5);

    int auxPlayerX = posicao.x+fonteLabel.dimensao.w*2;

    int auxPointsX = wsManager->getLarguraLinha(fonteLabel.nome,"GBF_UIRecorde_title_points");
    auxPointsX=int (posicao.x+(dimensao.w/2)) + fonteLabel.dimensao.w*2;


    //escrevendo campo
    posicaoTextoVertical=posicaoTextoVertical+(fonteLabel.dimensao.h*1.5);

    auxPlayerX-=fonteCampo.dimensao.w;
    auxPointsX-=fonteCampo.dimensao.w;








    //desenhando cursor
    if (tempoBlink.getTempo()%2!=0){
        graphicSystem->gfx->setColor(250,250,250);
        graphicSystem->gfx->retanguloPreenchido(auxPlayerX+(fonteCampo.dimensao.w*nomePosicao),posicaoTextoVertical+fonteCampo.dimensao.h,fonteCampo.dimensao.w,2);
    }

    if (showErro){
        wsManager->escreverLocalizado(fonteLabel.nome, caixaPosicao.x,caixaPosicao.y+caixaTeclado.h,"GBF_UIRecorde_warning");
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
    fonteTeclado.nome=fonte;
    fonteTeclado.dimensao=wsManager->getFonte(fonteTeclado.nome)->getDimensao();

    caixaTeclado.w=10 * (fonteTeclado.dimensao.w + int(fonteTeclado.dimensao.w/4));
    caixaTeclado.h=5  * (fonteTeclado.dimensao.h + int(fonteTeclado.dimensao.h/4));

    caixaPosicao.x=posicao.x + (fonteTeclado.dimensao.h*1.50);
    caixaPosicao.y=posicao.y+dimensao.h-caixaTeclado.h-fonteTeclado.dimensao.h*1.50;
}

void UserInterfaceNovoRecorde::setFonteTitulo(std::string fonte)
{
    fonteTitulo.nome=fonte;
    fonteTitulo.dimensao=wsManager->getFonte(fonteTitulo.nome)->getDimensao();
}
//Define a fonte a ser usada pelo label
void UserInterfaceNovoRecorde::setFonteLabel(std::string fonte)
{
    fonteLabel.nome=fonte;
    fonteLabel.dimensao=wsManager->getFonte(fonteLabel.nome)->getDimensao();
}
void UserInterfaceNovoRecorde::setFonteCampo(std::string fonte)
{
    fonteCampo.nome=fonte;
    fonteCampo.dimensao=wsManager->getFonte(fonteCampo.nome)->getDimensao();
}
//Define a fonte a ser usada pelo label
void UserInterfaceNovoRecorde::setFonteControle(std::string fonte)
{
    fonteControle.nome=fonte;
    fonteControle.dimensao=wsManager->getFonte(fonteControle.nome)->getDimensao();

    tamanhoMaiorTeclaControle  = 0;
    unsigned int tmp=0;
    for (unsigned int i=0; i<totalTeclasControle;i++){
        tmp = wsManager->getLarguraLinha(fonteControle.nome,tecladoControle[i].c_str());
        if (tmp>tamanhoMaiorTeclaControle){
            tamanhoMaiorTeclaControle=tmp;
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
    tempoEspera.setResetar();
}

//Gerencia o controle do cursor (navegação) e as opções selecionadas
bool UserInterfaceNovoRecorde::isAcao(int tipoAcao)
{
    bool salva = false;
    tempoEspera.processar();
    tempoBlink.processar();

    if (tempoEspera.isTerminou()){
        navegar();
        if(confirmarSelecao()==tipoAcao)
        {
            salva=true;
        }
    }

    return salva;
}

//Efetua as ações de acordo com a posição do cursor
int UserInterfaceNovoRecorde::confirmarSelecao()
{
    int opcao = false;
    if ((inputSystem->teclado->isKey(SDLK_RETURN)) || (inputSystem->joystick->isButtonA())){

        showErro=false;

        if ((tecladoSelecao>=0)&&(tecladoSelecao<totalTeclasTeclado)){
            recorde.nome[nomePosicao]=miniTeclado[tecladoSelecao];
            nomePosicao++;
        } else if (tecladoSelecao==totalTeclasTeclado){//controle voltar
            nomePosicao--;
        } else if (tecladoSelecao==totalTeclasTeclado+1){//controle avancar
            nomePosicao++;
        } else if (tecladoSelecao==totalTeclasTeclado+2){//controle salvar
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

    return opcao;
}
//Efetua o controle sobre a navegação do cursor
void UserInterfaceNovoRecorde::navegar()
{
    if ((inputSystem->teclado->isKey(SDLK_LEFT))||(inputSystem->joystick->isAxeLeft())){
            tecladoSelecao--;
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_RIGHT))||(inputSystem->joystick->isAxeRight())){
            tecladoSelecao++;
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_DOWN))||(inputSystem->joystick->isAxeDown())){
            if (tecladoSelecao<40){
                tecladoSelecao+=10;
            } else {//if (tecladoSelecao>=totalTeclasTeclado){
                tecladoSelecao++;
            }
            tempoEspera.setResetar();
    } else if ((inputSystem->teclado->isKey(SDLK_UP))||(inputSystem->joystick->isAxeUp())){
            if ((tecladoSelecao>=10)&&(tecladoSelecao<totalTeclasTeclado)){
                tecladoSelecao-=10;
            } else {
                tecladoSelecao--;
            }
            tempoEspera.setResetar();
    }

    if (tecladoSelecao<0){
        tecladoSelecao=0;
    } else if (tecladoSelecao>totalTeclas-1){
        tecladoSelecao=totalTeclas-1;
    }
}

