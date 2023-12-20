    #include <array>
    #include <iostream>
    #include <netinet/in.h>
    #include <ostream>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <string>


class ServerHandler
{
    public:
        ServerHandler(){}
        ServerHandler(int port) :port(port) {}
        

        void Init();

        void AcceptConnection();

        int ReadData(std::string& GlobalBuffer);

        void SendData(std::string DataToSend);

        void Close();
    

    private:
        int listening;
        sockaddr_in hint ;
        int port;
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);
        char host[NI_MAXHOST];
        char svr[NI_MAXSERV];
        int clientSocket ;
        char buf[4096];
        int bytesRecv ;
};