/***************************************************************************
 *   Copyright (C) 2006 by David Ferreira                                  *
 *   davidferreira@uol.com.br - http://pjmoo.codigolivre.org.br            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/***************************************************************************/
/* Declaração - Includes                                                   */
/***************************************************************************/
#include <GBF/GBFramework.h>
#include <GBF/ImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <vector>
#include <iostream>
#include <fstream>



class TextoTraducao
{
public:
    void carregar(std::string arquivo);
    std::string getTexto(std::string chave);
    std::string getProximoTexto();
    int size();
private:
    std::map<std::string,std::string> texto;
    void processar(char *info);
    std::map<std::string,std::string>::iterator it;
};

int TextoTraducao::size()
{
	return texto.size();
}
std::string TextoTraducao::getProximoTexto()
{
   // if (it==NULL){
   if (it.isEmpty()){
        it=texto.begin();
    } else {
        it++;
    }
    if (it==texto.end()){
        it=texto.begin();
    }
    return std::string((*it).second);

}
std::string TextoTraducao::getTexto(std::string chave)
{
    return texto[chave];
}
void TextoTraducao::carregar(std::string arquivo)
{
    char str[256];
    std::fstream arquivoTexto(arquivo.c_str(),std::ios::in);

    if (arquivoTexto!=NULL){
        while(!arquivoTexto.eof()){
            arquivoTexto.getline(str,256);
            processar(str);
        }
        arquivoTexto.close();
    }
}
void TextoTraducao::processar(char * info)
{
    int i=0;
    std::string linha = info;

    for (i=0;i<linha.length();i++){
        if (linha[0]=='#'){
            break;
        } else if (linha[i]=='=') {
            break;
        }
    }
    if (i>0){
        texto[linha.substr(0,i)]=linha.substr(i+1,linha.length());
    }
}



int main(int argc, char* argv[])
{

	GBFramework *frameworkGBF = new GBF();

    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF::Teste Scrolling","David Ferreira");
    frameworkGBF->iniciar(640,480,32,false);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);


//carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("tiles","//data//imagem//tilemap_01.png");

    SpriteFactory * spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("tiles"));

    FrameLayer *tiles = spriteFactory->criarFrameLayer(0,0,32,32);

    delete (spriteFactory);

    tiles->setFrame(0,0,640,480);
    tiles->setTiles(20,15);
    tiles->setPixelTile(32,32);
    tiles->iniciarOrdenado(4);
    tiles->camera.setTop();

////////////

    TextoTraducao texto;
    texto.carregar("msg_br.txt");

//////////

    int contador=0;
	while(true) {
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}

		//desenha a tela de fundo
		tiles->desenhar();

        for (int i=0; i<texto.size(); i++){
           frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::pumpdemi,0,i*30,"%s",texto.getProximoTexto().c_str());
        }

        frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::pumpdemi,100,400,"%s",texto.getTexto("texto005").c_str());
		//realiza refresh, fps, flip
		frameworkGBF->atualizar();
	}
    if (frameworkGBF){
        delete(tiles);
        delete(frameworkGBF);
    }
	return 0;
}

