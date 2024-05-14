#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;
    while (strcmp(buff, "chiusura") != 0) {
        bzero(buff, sizeof(buff));
        printf("1. inserire\n"
               "2. cancella\n"
               "3. stampare\n"
               "4. modifica\n"
               "5. chiusura\n"
               "Inserisci il comando: ");
        scanf("%s", buff);
        if (strcmp(buff, "inserire") == 0) {
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            printf("Inserisci il nome : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            printf("Inserisci il numero : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
        } else if (strcmp(buff, "cancella") == 0) {

        } else if (strcmp(buff, "stampare") == 0) {
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            printf("Contatti : %s\n", buff);
        }

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
