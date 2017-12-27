#include <iostream> 
#include <string> 

#include "config.h"

#ifdef QT5_PACKAGES_FOUND
#include <QApplication> 
#include "window.h" 
#endif // QT5_PACKAGES_FOUND 

int main(int argc, char *argv[]) 
{
#ifdef QT5_PACKAGES_FOUND 

#else // QT_PACKAGES_FOUND 
    std::cout << "Hello program!" << std::endl; 
    return 0; 
#endif // QT_PACKAGES_FOUND 
}