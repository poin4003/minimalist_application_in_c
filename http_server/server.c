// #include <sys/socket.h>
// #include <sys/sendfile.h>
// #include <netinet/in.h>
// #include <string.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>

// void main() {
//     printf("Server is on: http://locahost:8080");
//     int s = socket(AF_INET, SOCK_STREAM, 0);
//     struct sockaddr_in addr = {
//         AF_INET,
//         0x901f,
//         0
//     };
//     bind(s, (struct sockaddr *)&addr, sizeof(addr));

//     listen(s, 10);

//     int client_fd = accept(s, 0, 0);

//     char buffer[256] = {0};

//     recv(client_fd, buffer, 256, 0);

//     // GET /file.html ....
//     char* f = buffer + 5;
//     *strchr(f, ' ') = 0;

//     char file_path[512] = "./resource/";
//     strncat(file_path, f, sizeof(file_path) - strlen(file_path) - 1);

//     printf("Serving file: %s\n", file_path);

//     int open_fd = open(file_path, O_RDONLY);

//     sendfile(client_fd, open_fd, 0, 256);
//     close(open_fd);
//     close(client_fd);
//     close(s);
// }


#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // Cần cho exit()

void main() {
    printf("Server is starting...\n");
    
    // 1. Tạo socket và KIỂM TRA LỖI
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket() failed"); // In ra lỗi cụ thể
        exit(EXIT_FAILURE);       // Và thoát chương trình
    }

    // Sử dụng cách khởi tạo rõ ràng và đúng chuẩn hơn
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY // Lắng nghe trên mọi địa chỉ IP
    };

    // 2. Bind socket và KIỂM TRA LỖI
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind() failed");
        close(s); // Nhớ đóng socket trước khi thoát
        exit(EXIT_FAILURE);
    }

    // 3. Listen và KIỂM TRA LỖI
    if (listen(s, 10) < 0) {
        perror("listen() failed");
        close(s);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on: http://localhost:8080\n");

    // 4. Accept và KIỂM TRA LỖI
    int client_fd = accept(s, 0, 0);
    if (client_fd < 0) {
        perror("accept() failed");
        close(s);
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Phần xử lý file giữ nguyên như cũ
    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);
    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    char file_path[512] = "./resource/";
    strncat(file_path, f, sizeof(file_path) - strlen(file_path) - 1);
    printf("Serving file: %s\n", file_path);
    int open_fd = open(file_path, O_RDONLY);
    sendfile(client_fd, open_fd, 0, 256); // Vẫn còn vấn đề header và kích thước file ở đây
    
    close(open_fd);
    close(client_fd);
    close(s);
}

