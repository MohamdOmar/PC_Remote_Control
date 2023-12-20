#include "server.hpp"
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <unistd.h>


void ServerHandler::Init()
{
    //create a socket
    listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening <0)
    {
        std::cerr<<"Can't create a socket! ";       
    }

    //Bind the Socket to IP / port
    
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening , (sockaddr*) &hint , sizeof(hint)) < 0)
    {
        std::cerr<< "Can't bind to IP/port!";
    }

    //Make the socket for listening in
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr<<"Can't listen! ";
    }

}

void ServerHandler::AcceptConnection()
{
    //Accept the call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    clientSocket = accept(listening,
                        (sockaddr*) &client,
                        &clientSize);

    if (clientSocket <0)
    {
        std::cerr<<"Problem with client connecting! ";
    }

    //Close the listening socket 
    close(listening);

    //Get client ip
    memset(host, 0 , NI_MAXHOST);
    memset(svr, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,
                            sizeof(client),
                            host,
                            NI_MAXHOST,
                            svr,
                            NI_MAXSERV,
                            0);

    if (result)
    {
        std::cout << host << "Connected On "<< svr << std::endl;
    }
    else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "Connected on " << ntohs(client.sin_port) << std::endl;
    }

    const char *options = R""""(
Choose from the list below:
1. calculator
2. terminal
3. VScode
4. home
5. firefox
6. camera

)"""";


    send(clientSocket, options, strlen(options), 0);

}

int ServerHandler::ReadData(std::string& GlobalBuffer)
{
    //Clear the buffer
        memset(buf, 0, sizeof(buf));
        //Wait for a message
        bytesRecv = recv(clientSocket, buf, sizeof(buf), 0);
        if (bytesRecv == -1 )
        {
            std::cerr << "There was a connection issue" <<std::endl;
            return -1;
        }
        if (bytesRecv == 0 )
        {
            std::cerr << "The client disconnected" <<std::endl;
            return 0;
        }

        //Display message
        GlobalBuffer = std::string(buf, 0 , bytesRecv);
        std::cout << "Reccived: " << GlobalBuffer << std::endl;
        

        //Resend the data
        send(clientSocket, buf, bytesRecv+1 , 0);

        return bytesRecv;
}

void ServerHandler::SendData(std::string DataToSend)
{
    send(clientSocket, DataToSend.c_str(), DataToSend.size(), 0);
}

void ServerHandler::Close()
{
    close(clientSocket);
}

    