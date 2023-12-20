#include "server.hpp"
#include "executer.hpp"
#include <cstdlib>
#include <string.h>
#include <string>


std::string GlobalBuffer;


int main() {

    ServerHandler socket(54000);
    Command executer;
    socket.Init();
    socket.AcceptConnection();
    

    while (true)
    {
        GlobalBuffer.clear();
        int receivedBytes = socket.ReadData(GlobalBuffer);
        if ( receivedBytes== -1 || receivedBytes == 0)
        {
            break;
        }
        // std::cout << "GlobalBuffer : " << GlobalBuffer<< std::endl;
        // std::cout << " Length = "<< GlobalBuffer.length() << std::endl;
        
        //Remove white_spaces
        executer.trim(GlobalBuffer);
        // std::cout << " Length = "<< GlobalBuffer.length() << std::endl;
        
        executer.command_execute(GlobalBuffer);


    }

    return 0;
}