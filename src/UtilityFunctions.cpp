#include "UtilityFunctions.h"


void UtilityFunctions::clearScreen() {

    std::this_thread::sleep_for(std::chrono::seconds(1));

#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}