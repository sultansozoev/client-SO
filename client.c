#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    while (strcmp(buff, "chiusura") != 0) {
        bzero(buff, sizeof(buff));
        printf("Comandi disponibili:\n"
               "1. inserire\n"
               "2. cancella\n"
               "3. stampare\n"
               "4. modifica\n"
               "5. chiusura\n"
               "6. registrare\n"
               "7. accedere\n"
               "Inserisci il comando: ");
        scanf("%s", buff);
        if (strcmp(buff, "inserire") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            printf("Inserisci il nome : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contact already exists") == 0) {
                printf("Contact already exists\n");
                continue;
            } else {
                printf("Inserisci il numero : ");
                scanf("%s", buff);
                write(sockfd, buff, sizeof(buff));
            }
        } else if (strcmp(buff, "cancella") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            bzero(buff, sizeof(buff));
            printf("Inserisci il nome : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contatto non trovato") == 0) {
                printf("Contatto non trovato\n");
            } else if (strcmp(buff, "Contatto trovato") == 0) {
                printf("Contatto trovato e cancellato\n");
            }
        } else if (strcmp(buff, "stampare") == 0) {
            write(sockfd, buff, sizeof(buff));
            printf("Contatti:\n");
            read(sockfd, buff, sizeof(buff));
            printf("%s\n", buff);
        } else if (strcmp(buff, "modifica") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            bzero(buff, sizeof(buff));
            printf("Inserisci il nome : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            printf("Inserisci il nuovo numero : ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contatto non trovato") == 0) {
                printf("Contatto non trovato\n");
            } else if (strcmp(buff, "Contatto trovato") == 0) {
                printf("Contatto trovato e modificato\n");
            }
        } else if (strcmp(buff, "registrare") == 0) {
            write(sockfd, buff, sizeof(buff));
            printf("Enter username: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            printf("Enter password: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Username already exists") == 0) {
                printf("Username already exists\n");
            } else if (strcmp(buff, "User registered successfully") == 0) {
                printf("User registered successfully\n");
            }
        } else if(strcmp(buff, "accedere") == 0) {
            write(sockfd, buff, sizeof(buff));
            printf("Enter username: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            printf("Enter password: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "User authenticated successfully") == 0) {
                printf("User authenticated successfully\n");
            } else if (strcmp(buff, "Authentication failed") == 0) {
                printf("Authentication failed\n");
            }
        } else if (strcmp(buff, "chiusura") == 0) {
            write(sockfd, buff, sizeof(buff));
            break;
        }
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    func(sockfd);
    close(sockfd);
}