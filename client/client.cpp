#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h> 

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Cannot create socket" << std::endl;
        return 1;
    }

    struct hostent* host = gethostbyname("udp-echo-server");
    if (host == nullptr) {
        std::cerr << "Error: Cannot resolve hostname 'udp-echo-server'" << std::endl;
        close(sockfd);
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    memcpy(&serverAddr.sin_addr, host->h_addr, host->h_length);

    std::cout << "UDP Echo Client" << std::endl;
    std::cout << "Server: udp-echo-server:8080" << std::endl;
    std::cout << "Type 'exit' to quit" << std::endl;
    std::cout << "================================" << std::endl;

    while (true) {
        std::cout << "Message: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "exit") == 0) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        sendto(sockfd, buffer, strlen(buffer), 0,
            (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        struct sockaddr_in fromAddr;
        socklen_t fromLen = sizeof(fromAddr);

        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
            (struct sockaddr*)&fromAddr, &fromLen);

        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "Response: " << buffer << std::endl;
        }
        std::cout << "================================" << std::endl;
    }

    close(sockfd);
    return 0;
}
