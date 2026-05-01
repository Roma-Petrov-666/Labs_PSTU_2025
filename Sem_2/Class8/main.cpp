#include <iostream>

#include "Dialog.h"

int main() {
    std::cout << "Событийно-управляемая программа." << std::endl;
    std::cout << "Команды: m<размер>  +  -  s  ?<номер>  q" << std::endl;
    Dialog D;
    D.Execute();
	
    return 0;
}