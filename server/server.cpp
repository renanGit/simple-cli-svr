#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        printf("socket got -1\n");
        exit(-1);
    }

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(3000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        printf("bind got -1\n");
        close(serverSocket);
        exit(-1);
    }

    // listening to the assigned socket
    if (listen(serverSocket, /*max pending connections*/1) == -1)
    {
        printf("listen got -1\n");
        close(serverSocket);
        exit(-1);
    }
    printf("Listening on port 3000...\n");

    // accepting connection request
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1)
    {
        printf("accept get -1\n");
        close(clientSocket);
        close(serverSocket);
        exit(-1);
    }

    // recieving data
    char buffer[1024] = { 0 };
    const char* exit = "exit";
    while (true)
    {
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        std::cout << "Message from client: [" << buffer << "]" << std::endl;
        if (memcmp(buffer, exit, 4) == 0)
        {
            write(clientSocket, "Exitting", 8);
            break;
        }
        int bytesWritten = write(clientSocket, "GOOD", 4);
        
        if (bytesWritten <= -1)
        {
            printf("write failed\n");
        }

        memset(buffer, 0, bytesRead);
    }

    printf("server shutting down\n");
    // closing the socket.
    close(serverSocket);
    close(clientSocket);

    return 0;
}