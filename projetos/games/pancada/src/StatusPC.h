#ifndef STATUSPC_H
#define STATUSPC_H

#include "Status.h"


class StatusPC : public Status
{
    public:
        StatusPC();
        virtual ~StatusPC();
        void desenhar(int pontos, int round, int energia);
    protected:
    private:
};



#endif // STATUSPC_H
