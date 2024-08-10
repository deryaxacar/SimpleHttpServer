#ifndef SIMPLE_HTTP_SERVER_H
#define SIMPLE_HTTP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4433
#define BUFFER_SIZE 1024

// Sunucu ve istemci işlemleriyle ilgili fonksiyonlar

// İstemci bağlantısını yönetir (SSL isteğini işler ve yanıt verir)
void handle_client(SSL *ssl);  // SSL tipi kullanıldı

// İstemci bağlantısını işlemek için iş parçacığı fonksiyonu
void *client_handler(void *socket_desc);

// SSL konfigürasyonu ve diğer fonksiyonlar
void init_openssl();
void cleanup_openssl();
SSL_CTX *create_context();
void configure_context(SSL_CTX *ctx);
void get_users(SSL *ssl);
void handle_feedback(SSL *ssl, const char *data);

#endif // SIMPLE_HTTP_SERVER_H
