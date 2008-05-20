
#include "LutadorPC.h"

LutadorPC::LutadorPC(TipoLutador tipo)
{
	CabecaFactory cFactory;
	cabeca = cFactory.criar(tipo);
	olharBaixo();
}
LutadorPC::~LutadorPC()
{

}
void LutadorPC::acao(GBF::Kernel::Input::InputSystem * input)
{
    //Movimenta��o
    (void)input;

    //Controle de Socos - Soco Esquerdo
    socarEsquerda(true);
    //Controle de Socos - Soco Direito
    socarDireita(true);
}
void LutadorPC::visao(const GBF::Area & adversario)
{
    float qx, qy, qr; //para guardar o quadrado de x, y e raio
    GBF::Area visao = getArea();

    //quadrado da dist�ncia em x
    qx = std::pow(float((adversario.left + adversario.right/2) - (visao.left + visao.right/2)), 2);
    //quadrado da dist�ncia em y
    qy = std::pow(float((adversario.top + adversario.bottom/2) - (visao.top  + visao.bottom/2)), 2);
    //quadrado da soma dos raios
    qr = std::pow(float(300), 2);


    if (qx + qy <= qr){
        if (visao.left<adversario.left){
            andarDireita();
        } else if (visao.left>adversario.left){
            andarEsquerda();
        }
    }
}
