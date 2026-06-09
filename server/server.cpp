#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    socklen_t addrLen = sizeof(clientAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Cannot create socket" << std::endl;
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Cannot bind socket" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "UDP Echo Server running on port 8080" << std::endl;

    while (true) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
            (struct sockaddr*)&clientAddr, &addrLen);

        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            sendto(sockfd, buffer, n, 0,
                (struct sockaddr*)&clientAddr, addrLen);
        }
    }

    close(sockfd);
    return 0;
}