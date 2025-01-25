#include <include.h>
#include <ShellAPI.h>
#include <tchar.h>

int main() {
    SetConsoleTitleA("Minecraft Name Checker");
    int length;
    int option; 
    std::cout << " Enter the length: ";
    std::cin >> length;
    std::cout << " 1. Random" << std::endl;
    std::cout << " Enter Option: "; 
    std::cin >> option; 

    switch (option)
    {
    case 1:
        checker.checkRandom(length);
        break;
    }
}