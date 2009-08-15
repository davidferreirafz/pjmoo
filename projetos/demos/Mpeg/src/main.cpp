 #include <stdio.h>
 #include <stdlib.h>

         #include  <SDL/SDL.h>
         #include  <SDL/SDL_syswm.h>
         #include  <smpeg/smpeg.h>

 // Logo abaixo estão as prototipações das
 // funções que inicializam a SDL e a SMPEG
 // respectivamente.
 // A inicialização da SDL consiste na criação d
 // uma janela (superfície) onde será exibido o
 // video. A inicialização da SMPEG deﬁne qual o
 //  arquivo de vídeo que será exibido e em que
 // superfície da SDL.
 // Então por que não juntar as duas em uma
 // única função? Pode ser interessante que na
 // ocorrência de um evento, por exemplo um
 // clique de mouse, você queira trocar
 // rapidamente o vídeo que está sendo exibido
 // por outro, como naqueles jogos de tiroteio

SMPEG * inicializa_smpeg (char * arquivo_video, SDL_Surface * tela);
SDL_Surface * inicializa_sdl();
// O programa principal basicamente inicia a
// exibição do vídeo e aguarda pela ocorrência
// de um evento de mouse ou teclado.
int main (int argc, char *argv[])
{
        // Essa é uma estrutura de dados da
        // biblioteca SMPEG que faz referência
        // à um arquivo de vídeo no formato
        // MPEG.
        SMPEG *mpeg;
        // Essa é uma estrutura de dados da
        // biblioteca SDL que armazena conjuntos
        // de pixels. É por meio dela que é
        // possível desenhar, plotar e extrair
        // ﬁguras de um aplicativo que utiliza a
        // SDL. Nesse exemplo essa estrutura
        // será usada para exibir o nosso vídeo.

         SDL_Surface *tela;
         // Estrutura que contem informações do
         // vídeo.
         SMPEG_Info info;
         SDL_Event evento;
         int sair,frame, x, y,pause;
         float razao_x, razao_y;
         mpeg = NULL;
         tela = NULL;
         sair = 0;
         pause = 0;
         razao_x = 1;
         razao_y = 1;
         //if (argc == 1 || argc > 2)
         //{
         //        printf ("\nParametro incorreto.\n");
         //         exit (1);
         //}
         if ((tela = inicializa_sdl()) == NULL)
         {
                 exit (1);
         }
         if ((mpeg = inicializa_smpeg ("/home/desenvolvimento/pjmoo/projetos/demos/Gameta_SalaTreino/bin/dukitan.mpg", tela)) == NULL)
         {
                 exit (1);
         }
         SMPEG_play (mpeg);
         // Enquanto sair for falso faça...
         while (sair == 0)
         {
                 // SDL aguarda por um evento.
                 SDL_WaitEvent (&evento);
                 switch (evento.type)
                  {
                  // Caso o evento seja um clique
                  // do mouse...
                 case SDL_MOUSEBUTTONDOWN:
                         // A coordenada do
                         // clique e o frame do
                         // vídeo são impressos
                         // no terminal.
                         // Caso o mouse tenha
                         // dois ou três botões,
                         // é possível tratá-los
                         // separadamente.
                         SMPEG_getinfo (mpeg, &info);
                         x = (int) (evento.button.x * razao_x);
                         y = (int) (evento.button.y * razao_y);
                         frame = info.current_frame;
                         printf ("%d %d %d\n", frame, x, y);
                         break;
                 // Caso o evento seja uma tecla
                 // pressionada...
                 case SDL_KEYDOWN:
                         // Se a tecla for “ESC”
                         // então saia do loop.
                         if (evento.key.keysym.sym == SDLK_ESCAPE)
                                   sair = 1;
                         // Se a tecla for
                         // “espaço” então toque
                         // ou pause o video.
                         else if (evento.key.keysym.sym == SDLK_SPACE)
                         {
                                   if (pause)
                                   {
                                             SMPEG_play (mpeg);
                                             pause = 0;
                                   }
                                   else
                                   {
                                             SMPEG_pause (mpeg);
                                             pause = 1;
                                   }
                                              }
                            break;
                  case SDL_QUIT:
                            sair = 1;
                            break;
                   default:
                            break;
                   }
                   // Se o vídeo acabou...
                   if (SMPEG_status (mpeg) == SMPEG_STOPPED && pause == 0)
                            // Saia do loop.
                            sair = 1;
          }
          // Finalização do vídeo:
          SMPEG_stop (mpeg);
          // Libera o ponteiro
          SMPEG_delete (mpeg);
          // Finalização da SDL:
          SDL_Quit ();
          return (0);
 }
 SMPEG * inicializa_smpeg (char * arquivo_video, SDL_Surface * tela)
 {
          // Nosso arquivo de vídeo.
          SMPEG * mpeg = NULL;
          // O ponteiro SMPEG é apontado para o
          // arquivo de vídeo passado como
          // parâmetro do programa.
          if ((mpeg = SMPEG_new (arquivo_video, NULL, 1)) == NULL)
          {
                  return NULL;
          }
          // Esta função deﬁne em qual superfície
          // da SDL o vídeo será exibido.
          SMPEG_setdisplay(mpeg, tela, NULL,  NULL);
          if (SMPEG_error(mpeg) != NULL)
          {
                  return NULL;
         }
         // O parâmetro ‘1’ habilita a saída de  vídeo.
          SMPEG_enablevideo(mpeg, 1);
          if (SMPEG_error(mpeg) != NULL)
          {
                  return NULL;
          }
          // O parâmetro ‘1’ habilita a saída
          // de áudio.
          SMPEG_enableaudio(mpeg, 1);
          if (SMPEG_error(mpeg) != NULL)
          {
                  return NULL;
          }
          return mpeg;
 }
 SDL_Surface * inicializa_sdl ()
 {
    // Nossa janela de exibição.
    SDL_Surface * tela = NULL;

    // Inicializa o sistema de vídeo da SDL.
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        return NULL;
    }
    // Inicializa o sistema de áudio da SDL.
    if (SDL_Init (SDL_INIT_AUDIO) < 0)
    {
        return NULL;
    }

    // Os parâmetros determinam,
    // respectivamente, que a janela não
    // exibirá decorações, será armazenada
    // na memória de vídeo e exibida
    // em tela-cheia.
    if ((tela = SDL_SetVideoMode (320, 220, 16, SDL_HWSURFACE)) == NULL)
    {
        return NULL;
    }
    return tela;
 }



