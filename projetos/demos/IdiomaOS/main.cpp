#include <iostream>

#include <windows.h>


int main()
{
    int id = GetUserDefaultLangID();
    int tmp = id & 0x3ff;
    
	std::cout << "IdiomaOS" << std::endl;
	std::cout << "#:>" << id << ":"<< tmp << " ";
	std::string idioma = "";
	
    switch(tmp){
        case 22:
            idioma="Portugues";
            break;
        case 10:
            idioma="Espanhol";
            break;
        case 9:
        default:        
            idioma="Ingles";
            break;
    }
	
	std::cout << idioma << std::endl;

	return 0;
}
