
#include "UserInterfaceEstiloVisualImagem.h"

UserInterfaceVisualImagem::UserInterfaceVisualImagem() 
{
    if (gsImageBufferManager==NULL){
        gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }
}
UserInterfaceVisualImagem::UserInterfaceVisualImagem(const UserInterfaceVisualImagem & base):UserInterfaceVisual(base) 
{
    background=base.background;
}
UserInterfaceVisualImagem::~UserInterfaceVisualImagem() 
{
    if (background!=NULL){
        delete(background);
    }
}
//Aplica o efeito visual
void UserInterfaceVisualImagem::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    UserInterfaceVisual::aplicar(posicao,dimensao);
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("gbf-window-background"));
    background = spriteFactory->criarFrameLayer(0,0,10,10);
    delete(spriteFactory);

    if (background!=NULL){
        background->setFrame(posicao.x,posicao.y,dimensao.w,dimensao.h);
        background->setTiles((dimensao.w/10),(dimensao.h/10));
        background->setPixelTile(10,10);
        background->iniciarCom(0);
    }
}
//Desenha o EstiloVisual do Componente
void UserInterfaceVisualImagem::desenhar() 
{
    if (background!=NULL){
        background->desenhar();
    }
    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
UserInterfaceVisual * UserInterfaceVisualImagem::clone() 
{
   return new UserInterfaceVisualImagem(*this);
}
//Define o estilo de background a ser utilizado
void UserInterfaceVisualImagem::setTipoBackground(UserInterfaceVisualTipoBackground tipo) 
{
}
GraphicSystemImageBufferManager * UserInterfaceVisualImagem::gsImageBufferManager =NULL;

