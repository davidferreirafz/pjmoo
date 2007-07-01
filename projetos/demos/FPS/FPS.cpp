/*
 FPS - Controle de Animação

    fps->maximo     = 30; //define a quantidade máxima de quadros por segundo que a aplicação pode desenhar



*/


#include <cstdlib>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint8* pTecla = NULL;
SDL_Surface* tela   = NULL;

struct FonteBitmap
{
    SDL_Surface* imagem;
};


struct Personagem
{
    int x, y;
    int w, h;
    int frameMaximo;
    int frameAtual;
    int frameRateMaximo;
    int frameRateAtual;
    SDL_Surface* imagem;
};

struct FPS
{
    double frameStart;
    int    maximo;
};

//
//
//
////////////////////////////////////////////////////////////////////////////////
void iniciarSDL(std::string titulo)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Nao foi possivel inicializar SDL %s",SDL_GetError());
		exit(-1);
    } else {
        tela=SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    	if (tela) {
            SDL_WM_SetCaption(titulo.c_str(),NULL);
    	} else {
    		printf("Couldn't set 640x480 video mode: %s\n",SDL_GetError());
    		exit(-2);
        }
    }
}
//Finaliza a SDL
void finalizarSDL()
{
    SDL_Quit();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void atualizarInput()
{
    static SDL_Event event;
    SDL_PollEvent(&event);
    pTecla = SDL_GetKeyState(NULL);
}
bool isTecla(SDLKey tecla)
{
   if (pTecla[tecla]){
		return true;
   } else {
		return false;
   }
}
//
//
//
// TRATAMENTO DE IMAGENS
////////////////////////////////////////////////////////////////////////////////
void carregarImagem(Personagem *personagem,std::string caminho, int altura, int largura, int totalQuadro, int frameRate)
{
    personagem->imagem = IMG_Load(caminho.c_str());

    personagem->h=altura;
    personagem->w=largura;
    personagem->frameMaximo=totalQuadro;
    personagem->frameAtual=0;
    personagem->frameRateMaximo=frameRate;
    personagem->frameRateAtual=0;

    if (!personagem->imagem){
    		printf("Não foi possível carregar imagem%s\n",SDL_GetError());
    		exit(-3);
    }
}
void desalocarImagem(Personagem *personagem)
{
    if (personagem->imagem){
        SDL_FreeSurface (personagem->imagem);
    }
}
void desenharImagem(Personagem *personagem)
{
    SDL_Rect area;
    SDL_Rect posicao;

    area.x=(personagem->frameAtual*personagem->w);
    area.y=0;
    area.w=personagem->w;
    area.h=personagem->h;

    posicao.x=personagem->x;
    posicao.y=personagem->y;


    SDL_BlitSurface(personagem->imagem, &area , tela, &posicao);

    personagem->frameRateAtual++;

    if (personagem->frameRateAtual>personagem->frameRateMaximo){
        personagem->frameAtual++;
        if (personagem->frameAtual>personagem->frameMaximo){
            personagem->frameAtual=0;
        }
        personagem->frameRateAtual=0;
    }


}
void ativarTransparencia(Personagem *personagem,Uint8 R, Uint8 G, Uint8 B)
{
    SDL_SetColorKey(personagem->imagem,SDL_SRCCOLORKEY,SDL_MapRGB(personagem->imagem->format,R,G,B));
}
//
//
//
// FPS - Rotinas para controlar a velocidade da aplicacao
////////////////////////////////////////////////////////////////////////////////
//Chamado apenas quando se inicia o programa
void iniciarFPS(FPS* fps)
{
    fps->maximo     = 30; //maximo de quadros que a aplicação vai desenhar
	fps->frameStart = SDL_GetTicks();
}
//Deve ser chamado a cada iteração
void processarFPS(FPS* fps)
{
    while( (SDL_GetTicks() - fps->frameStart) < 1000 / fps->maximo )
    {
        //wait...
        //se tempo atual menos o tempo inicial for menor que
        // 1000/30, faz com que entre em espera
        //até que se complete o tempo
    }

    fps->frameStart = SDL_GetTicks();
}
//
//
//
// Programa Principal
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    bool continuarLoop = true;

    iniciarSDL("FPS - Controle da animacao");

    FPS fps;
    iniciarFPS(&fps);


    Personagem lutador;
    lutador.x=200;
    lutador.y=200;
    carregarImagem(&lutador,"sprite_lutador.png",160,160,4,2);


    while(continuarLoop) {
//INPUT
        atualizarInput();

        if (isTecla(SDLK_ESCAPE)){
            continuarLoop = false;
        }

//OUTPUT
        SDL_FillRect(tela, NULL, 0);
        desenharImagem(&lutador);


        SDL_Flip(tela);
        processarFPS(&fps);
    }

    desalocarImagem(&lutador);

    finalizarSDL();

    return 0;
}
