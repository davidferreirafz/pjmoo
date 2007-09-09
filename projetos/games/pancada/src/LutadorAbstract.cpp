
#include "LutadorAbstract.h"

Area LutadorAbstract::ringue;

ParticleSystemManager * LutadorAbstract::particleManager;

void LutadorAbstract::resetar()
{
	delay.acao  = 0;
	delay.tiroA = 0;
	delay.tiroB = 0;

    luvaesquerda->setSoco(false);
    luvadireita->setSoco(false);
}
//Construtor
LutadorAbstract::LutadorAbstract()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,153,76,2,8));
    delete(spriteFactory);

    getSpritePrincipal()->setQtdDirecoes(2);

	luvaesquerda = new LuvaEsquerda();
	luvadireita  = new LuvaDireita();

	posicao.x = 0;
	posicao.y = 0;

    energia = 10;


    if (particleManager==NULL){
        particleManager = ParticleSystemManager::getInstance();
    }


    resetar();
}
//Destrutor
LutadorAbstract::~LutadorAbstract()
{
    if (cabeca){
	    delete(cabeca);
	}
    if (luvaesquerda){
	    delete(luvaesquerda);
    }
    if (luvadireita){
	    delete(luvadireita);
	}
}
void LutadorAbstract::setRingue(Area ringue)

{
    ringue.left   +=10;
	ringue.top    +=20;
	ringue.right  -=10;
	ringue.bottom -=20;

    LutadorAbstract::ringue=ringue;
}
void LutadorAbstract::iniciar(int x, int y)
{
    resetar();

    setPosicao(x,y);

    if (y>=200){
        olharCima();
    } else {
        olharBaixo();
    }
}
//Desenha na tela

//Desenha na tela
void LutadorAbstract::desenhar()
{
    checklimites();
    PersonagemControlado::desenhar();
	cabeca->desenhar();
	luvaesquerda->desenhar();
	luvadireita->desenhar();
}
//O lutador está na olhando pra cima

//O lutador está na olhando pra cima
void LutadorAbstract::olharCima()
{
	cabeca->setCima();
	luvaesquerda->setCima();
	luvadireita->setCima();
    getSpritePrincipal()->setDirecao(DR_CIMA);
}
//O lutador está na olhando pra baixo

//O lutador está na olhando pra baixo
void LutadorAbstract::olharBaixo()
{
	cabeca->setBaixo();
	luvaesquerda->setBaixo();
	luvadireita->setBaixo();
    getSpritePrincipal()->setDirecao(DR_BAIXO);
}
Ponto LutadorAbstract::getPosicao()
{
	return posicao;
}
void LutadorAbstract::setPosicao(int x, int y)
{
    PersonagemAbstract::setPosicao(x,y);
	luvaesquerda->setPosicao(x,y);
	luvadireita->setPosicao(x,y);
	cabeca->setPosicao(x,y);
}
Area LutadorAbstract::getArea()
{
    Area area;

    area.top=posicao.y;
    area.left=posicao.x;

    Dimensao d = getDimensao();

    area.bottom=d.h;
    area.right=d.w;

    return area;
}
bool LutadorAbstract::socouAdversario(LutadorAbstract * adversario)
{
	bool retorno =  false;

	if ((luvaesquerda->isSoco()) && (adversario->levouSoco(luvaesquerda))){
        retorno = true;
	} else if ((luvadireita->isSoco()) && (adversario->levouSoco(luvadireita))){
		retorno = true;
	}

	if (retorno){
        Ponto posicao = getPosicao();

		if (getSpritePrincipal()->getDirecao()==DR_CIMA){
			posicao.y+=8;
		}else {
			posicao.y-=8;
		}

		setPosicao(posicao.x,posicao.y);
	}

	checklimites();

	return retorno;
}
bool LutadorAbstract::levouSoco(LuvaAbstract * luva)
{
	bool levou = false;

	if (delay.acao<=0){
		delay.acao=2;

		levou=cabeca->isColisao(luva->getArea());

		if (levou){
			Ponto pntCabeca = cabeca->getPosicao();
			Ponto posicao = getPosicao();

			DIRECAO olhando = getSpritePrincipal()->getDirecao();

            pntCabeca.x+=22;

			if (olhando!=DR_CIMA){
				pntCabeca.y+=53;
				posicao.y-=20;
			} else {
				posicao.y+=20;
			}

            if (luva->isLuvaEsquerda()){
                posicao.x-=20;
            } else {
                posicao.x+=20;
            }

			energia--;
			setPosicao(posicao.x,posicao.y);

            EfeitoSangue *sangue = new EfeitoSangue();
            sangue->criar(pntCabeca.x,pntCabeca.y);

            particleManager->adicionar(sangue);
		}
	} else {
        delay.acao--;
	}

	return levou;
}
void LutadorAbstract::mover(InputSystem * input, LutadorAbstract * adversario)
{
    if (!isNocaute()){
        Ponto pAnterior = getPosicao();

        acao(input);
        checklimites();
        if (choqueAdversario(adversario->getArea())){
            setPosicao(pAnterior.x,pAnterior.y);
        }
    }
}
bool LutadorAbstract::isNocaute()
{
    bool caiu = false;

    if (energia<=0){
        caiu = true;
    }

    return caiu;
}
//Retorna a energia vital do lutador
int LutadorAbstract::getEnergia()
{
    return energia;
}
bool LutadorAbstract::choqueAdversario(Area aCorpoAdversario)
{
	Area aCorpoLcl  = getArea();

	if ((aCorpoLcl.left + aCorpoLcl.right  >= aCorpoAdversario.left)&&
		(aCorpoLcl.left                    <= aCorpoAdversario.left + aCorpoAdversario.right)&&
		(aCorpoLcl.top  + aCorpoLcl.bottom >= aCorpoAdversario.top) &&
		(aCorpoLcl.top                     <= aCorpoAdversario.top + aCorpoAdversario.bottom)){
		return true;
	} else {
		return false;
	}
}
//checka com limites do ringue

//checka com limites do ringue
void LutadorAbstract::checklimites()
{
	Ponto posicao     = getPosicao();
	Dimensao dimensao = getDimensao();

    if (posicao.x-22<=ringue.left){
        posicao.x=ringue.left+22;
    } else if (posicao.x+dimensao.w+22>=(ringue.right)){
        posicao.x=(ringue.right) - dimensao.w-22;
    }
	if (getSpritePrincipal()->getDirecao()==DR_CIMA){
	    if (posicao.y-32<=ringue.top){
	        posicao.y=ringue.top+32;
	    } else if (posicao.y+dimensao.h-32>=(ringue.bottom)){
	        posicao.y=(ringue.bottom) - dimensao.h+32;
	    }
	} else {
	    if (posicao.y+32<=ringue.top){
	        posicao.y=ringue.top-32;
	    } else if (posicao.y+dimensao.h+32>=(ringue.bottom)){
	        posicao.y=(ringue.bottom) - dimensao.h-32;
	    }
	}

	setPosicao(posicao.x,posicao.y);
}
