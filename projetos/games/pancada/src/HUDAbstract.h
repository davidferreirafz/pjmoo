#ifndef HUDABSTRACT_H
#define HUDABSTRACT_H

#include <GBF/WriteSystemManager.h>
#include <GBF/SpriteItem.h>

class HUDAbstract
{
    public:
        HUDAbstract();
        virtual ~HUDAbstract();

    protected:
            static WriteSystemManager * wsManager;
            SpriteItem * painel;

    private:
};



#endif // HUDABSTRACT_H
