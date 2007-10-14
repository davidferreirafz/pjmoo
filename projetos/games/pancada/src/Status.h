
#ifndef _HUDABSTRACT_H
#define _HUDABSTRACT_H

#include <GBF/SpriteItem.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/GraphicSystem.h>

#include <GBF/SpriteFactory.h>


class HUDAbstract
{
  public:
    HUDAbstract();

    virtual ~HUDAbstract();


  protected:
    SpriteItem * painel;

    static WriteSystemManager * wsManager;

};
#endif
