
#include<cppinterface.h>
#pragma warning (disable : 4996)


short // echoes a short
EchoShort(short x // number to be echoed
           )
{
    return x;
}

#include<xlw/xlw.h>
#include<xlw/XlOpenClose.h>


void my_open_func()
{
    std::cerr << "Thanks for opening me" << std::endl;
}



void my_close_func()
{
    std::cerr << "Bye-Bye ..see you next time!" << std::endl;
}


extern "C"
{
    int __declspec(dllexport) func()
    {
        xlw::XlfServices.Commands.Alert("Thanks for calling the menu item");
        return 0;
    }
}
xlw::XLRegistration::XLCommandRegistrationHelper theItem("func","func","comment","File","func");