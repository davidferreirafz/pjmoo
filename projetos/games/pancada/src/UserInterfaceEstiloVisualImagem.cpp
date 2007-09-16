
#include "UserInterfaceEstiloVisualImagem.h"

UserInterfaceEstiloVisualImagem::UserInterfaceEstiloVisualImagem() 
{
    if (gsImageBufferManager==NULL){
        gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }
}
UserInterfaceEstiloVisualImagem::UserInterfaceEstiloVisualImagem(const UserInterfaceEstiloVisualImagem & base):UserInterfaceEstiloVisual(base) 
{
    background=base.background;
}
UserInterfaceEstiloVisualImagem::~UserInterfaceEstiloVisualImagem() 
{
    if (background!=NULL){
        delete(background);
    }
}
//Aplica o efeito visual
void UserInterfaceEstiloVisualImagem::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    UserInterfaceEstiloVisual::aplicar(posicao,dimensao);
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("gbf-window-background"));
    background = spriteFactory->criarFrameLayer(0,0,10,10);
    delete(spriteFactory);

    if (background!=NULL){
        background->setFrame(posicao.x,posicao.y,dimensao.w,dimensao.h);
        background->setTiles((dimensao.w/10),(dimensao.h/10));
        background->setPixelTile(10,10);
        background->iniciarOrdenado(0);
    }
}
//Desenha o EstiloVisual do Componente
void UserInterfaceEstiloVisualImagem::desenhar() 
{
    if (background!=NULL){
        background->desenhar();
    }
    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
GraphicSystemImageBufferManager * UserInterfaceEstiloVisualImagem::gsImageBufferManager =NULL;

UserInterfaceEstiloVisual * UserInterfaceEstiloVisualImagem::clone() 
{
   return new UserInterfaceEstiloVisualImagem(*this);
}
