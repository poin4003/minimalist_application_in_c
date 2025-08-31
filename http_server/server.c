#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 10);

    printf("Server listening on: http://localhost:8080\n");
    fflush(stdout);

    while (true) {
        int clientfd = accept(sockfd, NULL, NULL);

        char buffer[1024] = {0};
        ssize_t n = read(clientfd, buffer, sizeof(buffer) - 1);
        if (n <= 0) { close(clientfd); continue; }

        char* file_request = buffer + 5;           
        char* sp = strchr(file_request, ' ');
        if (sp) *sp = '\0';                    

        char response[1024] = {0};
        const char* metadata = "HTTP/1.0 200 OK\r\n"
                               "Content-Type: text/html\r\n\r\n";
        memcpy(response, metadata, strlen(metadata));

        if (file_request[0] == '\0' || strncmp(file_request, "index.html", 10) == 0) {
            FILE* f = fopen("/resource/index.html", "r");
            if (f) {
                fread(response + strlen(metadata), 1,
                      sizeof(response) - strlen(metadata) - 1, f);
                fclose(f);
            } else {
                const char* err = "No page found";
                memcpy(response + strlen(metadata), err, strlen(err));
            }
        } else {
            const char* err = "No page found";
            memcpy(response + strlen(metadata), err, strlen(err));
        }

        write(clientfd, response, strlen(response));
        close(clientfd);
    }

    close(sockfd);
}
