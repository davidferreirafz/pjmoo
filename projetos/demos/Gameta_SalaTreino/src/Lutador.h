#ifndef LUTADOR_H
#define LUTADOR_H

#include <GBF/Personagem.h>
#include "InterfaceObjeto.h"
#include <cmath>

enum Estado{
    PARADO,
    ANDANDO_FRENTE,
    ANDANDO_TRAS,
    RECUANDO,
    CORRENDO,
    PULANDO,
    CAINDO,
    IMPULSIONANDO,
    ATERRISANDO,
    MORRENDO
};

enum Pulo
{
    FRACO,
    NORMAL,
    SUPER
};

struct AlturaPulo{
    int super;
    int normal;
    int fraco;
    int corrente;
};



class Lutador: public Personagem::Personagem, public InterfaceObjeto
{
    public:
        Lutador();
        virtual ~Lutador();
        virtual void acao(GBF::Kernel::Input::InputSystem * input);
        void setBateu();
        int getVida();
    protected:
        void doRecuando();
        void doCorrendo();
        void doCaindo();
        void doAterrisando();
        void doAndandoFrente();
        void doAndandoTras();
        void doImpulsionando();
        void doPulando();
        void doParado();
        void doMorrendo();
        virtual void limites()=0;

        void ifRecuando();
        void ifCorrendo();
        void ifAndandoFrente();
        void ifAndandoTras();
        void ifImpulsionando();
        void ifMorrendo();
        void ifPulando();
        void ifCaindo();
        void ifAterrisando();

        virtual std::string getSpriteNome();
        virtual std::string getSpriteNome(Estado estado)=0;

        void setEstado(Estado estado);

        AlturaPulo alturaPulo;
        Estado estado;
        Pulo pulo;
        int vida;
        float aceleracao;
    private:
        GBF::Kernel::Input::InputSystem * input;
};

#endif // LUTADOR_H
