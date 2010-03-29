
#include "LutadorAbstract.h"

//Construtor

//Construtor
LutadorAbstract::LutadorAbstract()
{
    GBF::Image::SpriteFactory  *spriteFactory = new GBF::Image::SpriteFactory("personagem");

    addMainSprite(spriteFactory->createSpriteCharacter(0,0,153,76,2,8));
    delete(spriteFactory);

    getMainSprite()->setQtdDirecoes(2);

    luvaesquerda = new LuvaEsquerda();
    luvadireita  = new LuvaDireita();

    point.x = 0;
    point.y = 0;
    energia = 100;

    if (particleManager==NULL){
        particleManager = ParticleSystem::PSManager::getInstance();
    }

    resetar();
}

//Destrutor

//Destrutor
LutadorAbstract::~LutadorAbstract(){
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

void LutadorAbstract::setRingue(GBF::Area ringue)
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
void LutadorAbstract::draw()
{
    checklimites();
    Character::draw();
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
    getMainSprite()->setDirection(GBF::Image::Sprite::DR_CIMA);
}
//O lutador está na olhando pra baixo

//O lutador está na olhando pra baixo
void LutadorAbstract::olharBaixo()
{
	cabeca->setBaixo();
	luvaesquerda->setBaixo();
	luvadireita->setBaixo();
    getMainSprite()->setDirection(GBF::Image::Sprite::DR_BAIXO);
}
GBF::Point LutadorAbstract::getPosicao()
{
	return point;
}
void LutadorAbstract::setPosicao(int x, int y)
{
    Character::setPoint(x,y);
	luvaesquerda->setPosicao(x,y);
	luvadireita->setPosicao(x,y);
	cabeca->setPosicao(x,y);
}
GBF::Area LutadorAbstract::getArea()
{
    GBF::Area area;

    area.top=point.y;
    area.left=point.x;

    GBF::Dimension d = getDimension();

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
        GBF::Point posicao = getPoint();

		if (getMainSprite()->getDirection()==GBF::Image::Sprite::DR_CIMA){
			posicao.y+=8;
		}else {
			posicao.y-=8;
		}

		setPoint(point.x,point.y);
	}

	checklimites();

	return retorno;
}
bool LutadorAbstract::levouSoco(LuvaAbstract * luva)
{
    bool levou = false;

    if (delay.action<=0){
        delay.action=2;

        levou=cabeca->isColisao(luva->getArea());

        if (levou){
            GBF::Point pntCabeca = cabeca->getPosicao();
            GBF::Image::Sprite::Direcao olhando = getMainSprite()->getDirection();

            pntCabeca.x+=22;

            if (olhando!=GBF::Image::Sprite::DR_CIMA){
                pntCabeca.y+=53;
                andarCima(8);
            } else {
                andarBaixo(8);
            }

            int analiseRingue = int(ringue.right*0.3);

            if (point.x<analiseRingue){
                andarDireita(6);
            } else if (point.x>(ringue.right-analiseRingue)){
                andarEsquerda(6);
            } else {
                if (rand()%2==0){
                    andarDireita(6);
                } else {
                    andarEsquerda(6);
                }
            }

            energia--;

            EfeitoSangue *sangue = new EfeitoSangue();
            sangue->create(pntCabeca.x,pntCabeca.y);

            particleManager->add(sangue);
        }
    } else {
        delay.action--;
    }

    return levou;
}
void LutadorAbstract::mover(GBF::Kernel::Input::InputSystem * input, LutadorAbstract * adversario)
{
    if (!isNocaute()){
        GBF::Point pAnterior = getPoint();

        update(input);
        checklimites();
        if (choqueAdversario(adversario->getArea())){
            setPosicao(pAnterior.x,pAnterior.y);
        }
        visao(adversario->getArea());
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

//Retorna a energia vital do lutador
int LutadorAbstract::getEnergia()
{
    return energia;
}
ParticleSystem::PSManager * LutadorAbstract::particleManager =NULL;

GBF::Area LutadorAbstract::ringue;

bool LutadorAbstract::choqueAdversario(GBF::Area aCorpoAdversario)
{
	GBF::Area aCorpoLcl  = getArea();

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
	GBF::Point posicao     = getPosicao();
	GBF::Dimension dimensao = getDimension();

    if (posicao.x-22<=ringue.left){
        posicao.x=ringue.left+22;
    } else if (posicao.x+dimensao.w+22>=(ringue.right)){
        posicao.x=(ringue.right) - dimensao.w-22;
    }
	if (getMainSprite()->getDirection()==GBF::Image::Sprite::DR_CIMA){
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
void LutadorAbstract::resetar()
{
	delay.action  = 0;
	delay.slotA = 0;
	delay.slotB = 0;

    luvaesquerda->setSoco(false);
    luvadireita->setSoco(false);
}
//Anda para Baixo(Tela)
void LutadorAbstract::andarBaixo()
{
    point.y+=3;
}
//Anda para Cima(Tela)
void LutadorAbstract::andarCima()
{
    point.y-=3;
}
//Anda para Esquerda(Tela)
void LutadorAbstract::andarEsquerda()
{
    point.x-=3;
}
//Anda para Direita(Tela)
void LutadorAbstract::andarDireita()
{
    point.x+=3;
}
//Realiza o soco
void LutadorAbstract::socarDireita(bool soca)
{
    if ((delay.slotB<=0)&&(soca)){
        luvadireita->setSoco(true);
        delay.slotB=10;
    } else {
        delay.slotB--;
        if (delay.slotB<=2){
            luvadireita->setSoco(false);
        }
    }
}
//Realiza o soco
void LutadorAbstract::socarEsquerda(bool soca)
{
    if ((delay.slotA<=0)&&(soca)){
        luvaesquerda->setSoco(true);
        delay.slotA=10;
    } else {
        delay.slotA--;
        if (delay.slotA<=2){
            luvaesquerda->setSoco(false);
        }
    }
}
//Anda para Cima(Tela)
void LutadorAbstract::andarCima(int passos)
{
    for (int i=0; i<passos; i++){
        andarCima();
    }
}
//Anda para Cima(Tela)
void LutadorAbstract::andarBaixo(int passos)
{
    for (int i=0; i<passos; i++){
        andarBaixo();
    }
}
//Anda para Cima(Tela)
void LutadorAbstract::andarDireita(int passos)
{
    for (int i=0; i<passos; i++){
        andarDireita();
    }
}
//Anda para Cima(Tela)
void LutadorAbstract::andarEsquerda(int passos)
{
    for (int i=0; i<passos; i++){
        andarEsquerda();
    }
}
void LutadorAbstract::visao(const GBF::Area & adversario)
{
    (void)adversario;
}
