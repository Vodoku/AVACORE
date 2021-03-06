#include "config.h"

#ifdef QT5_PACKAGES_FOUND
#include <QApplication> 
#include "window.h" 
#else // QT5_PACKAGES_FOUND
#include "console.h"
#endif // QT5_PACKAGES_FOUND 

int main(int argc, char *argv[]) 
{
#ifdef QT5_PACKAGES_FOUND 
    // If user has defined QT Packages to be included 
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication application; 
    QWidget widget; 
    widget.show(); 
    return application.exec(); 
#else // QT_PACKAGES_FOUND 
    Console console; 
    while(console.running()) 
    {

    }
    return 0; 
#endif // QT_PACKAGES_FOUND 
}