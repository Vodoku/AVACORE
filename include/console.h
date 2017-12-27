#ifndef CONSOLE_H 
#define CONSOLE_H 

#include <iostream> 
using std::string;
using std::cout; 
using std::cin; 
#include <sstream> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <map> 

class Console 
{
    public: 
        static int const FLAG_WARNING = OutputStatus.WARNING; 
        static int const 
        Console(void); 
       ~Console(void); 

        bool running(void) const;

        void pause(void); 
        void exit(void);

    private: 
        // Types of output 
        enum OutputStatus
        {
            WARNING = 0, 
            NORMAL  = 1, 
            ERROR   = 2
        }

    private: 
        bool m_running; 

};

#endif // CONSOLE_H 