#include "../include/commands.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void func(int sockfd)
{
    char buff[MAX];
    while (strcmp(buff, "close") != 0) {
        bzero(buff, sizeof(buff));
        printf("Commands:\n"
               "1. login\n"
               "2. register\n"
               "3. add\n"
               "4. modify\n"
               "5. delete\n"
               "6. print\n"
               "7. close\n"
               "Enter the command: ");
        scanf("%s", buff);
        if (strcmp(buff, "add") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            printf("Enter name: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contact already exists") == 0) {
                printf("Contact already exists\n");
                continue;
            } else {
                printf("Enter number : ");
                scanf("%s", buff);
                write(sockfd, buff, sizeof(buff));
            }
        } else if (strcmp(buff, "delete") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            bzero(buff, sizeof(buff));
            printf("Enter name: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contact not found") == 0) {
                printf("Contact not found\n");
            } else if (strcmp(buff, "Contact deleted") == 0) {
                printf("Contact deleted\n");
            }
        } else if (strcmp(buff, "print") == 0) {
            write(sockfd, buff, sizeof(buff));
            printf("Contacts:\n");
            read(sockfd, buff, sizeof(buff));
            printf("%s\n", buff);
        } else if (strcmp(buff, "modify") == 0) {
            write(sockfd, buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Authentication required") == 0) {
                printf("Authentication required\n");
                continue;
            }
            bzero(buff, sizeof(buff));
            printf("Enter name: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            printf("Enter new number: ");
            scanf("%s", buff);
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            read(sockfd, buff, sizeof(buff));
            if (strcmp(buff, "Contact not found") == 0) {
                printf("Contact not found\n");
            } else if (strcmp(buff, "Contact modified") == 0) {
                printf("Contact modified\n");
            }
        } else if (strcmp(buff, "register") == 0) {
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
        } else if(strcmp(buff, "login") == 0) {
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
        } else if (strcmp(buff, "close") == 0) {
            write(sockfd, buff, sizeof(buff));
            break;
        }
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}