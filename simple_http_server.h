#ifndef SIMPLE_HTTP_SERVER_H
#define SIMPLE_HTTP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4433
#define BUFFER_SIZE 1024

// Sunucu ve istemci işlemleriyle ilgili fonksiyonlar

// İstemciye dosya içeriğini gönderir
void send_file_content(int client_socket, const char *filepath);

// İstemci bağlantısını yönetir (HTTP isteğini işler ve yanıt verir)
void handle_client(int client_socket);

// İstemci bağlantısını işlemek için iş parçacığı fonksiyonu
void *client_handler(void *socket_desc);

#endif // SIMPLE_HTTP_SERVER_H
