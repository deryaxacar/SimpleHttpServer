#include "simple_http_server.h"

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl() {
    EVP_cleanup();
}

SSL_CTX *create_context() {
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

void configure_context(SSL_CTX *ctx) {
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void get_users(SSL *ssl) {
    const char *response = "[{\"id\": 1, \"name\": \"Alice\"}, {\"id\": 2, \"name\": \"Bob\"}]";
    char http_response[BUFFER_SIZE];

    sprintf(http_response, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n%s", response);
    SSL_write(ssl, http_response, strlen(http_response));
}

void handle_feedback(SSL *ssl, const char *data) {
    char name[50], feedback[200];

    // URL kodlamasını çöz
    char *decoded_data = malloc(strlen(data) + 1);
    if (!decoded_data) {
        perror("Unable to allocate memory");
        return;
    }
    strcpy(decoded_data, data);
    for (int i = 0; decoded_data[i]; i++) {
        if (decoded_data[i] == '+') {
            decoded_data[i] = ' ';
        }
        if (decoded_data[i] == '%') {
            int value;
            sscanf(decoded_data + i + 1, "%2x", &value);
            decoded_data[i] = (char)value;
            memmove(decoded_data + i + 1, decoded_data + i + 3, strlen(decoded_data) - i - 2);
        }
    }

    sscanf(decoded_data, "name=%49[^&]&feedback=%199[^\n]", name, feedback);

    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Thank you for your feedback!</h1><p>Name: %s</p><p>Feedback: %s</p></body></html>\n", name, feedback);
    SSL_write(ssl, response, strlen(response));

    free(decoded_data);
}

void handle_client(SSL *ssl) {
    char buffer[BUFFER_SIZE];

    // SSL bağlantısını başlat
    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return;
    }

    // İstemciden veri oku
    int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    if (bytes <= 0) {
        ERR_print_errors_fp(stderr);
        return;
    }
    buffer[bytes] = 0;  // Null terminator ekle
    printf("Received: %s\n", buffer);

    // Geri bildirim verilerini işle
    if (strstr(buffer, "POST /feedback") != NULL) {
        handle_feedback(ssl, buffer);
    } else if (strstr(buffer, "GET /users") != NULL) {
        get_users(ssl);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>\n";
        SSL_write(ssl, response, strlen(response));
    }

    // Bağlantıyı kapat
    SSL_shutdown(ssl);
}

int main() {
    int server_fd;
    struct sockaddr_in addr;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();
    configure_context(ctx);

    // Socket oluştur
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    // Bağlan
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        SSL *ssl;
        int client_fd;

        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("Unable to accept");
            continue; // Hata durumunda döngüye devam et
        }

        printf("Connection accepted\n");

        // SSL nesnesini oluştur
        ssl = SSL_new(ctx);
        if (!ssl) {
            perror("Unable to create SSL");
            close(client_fd);
            continue; // Hata durumunda döngüye devam et
        }

        SSL_set_fd(ssl, client_fd);
        handle_client(ssl);

        SSL_free(ssl);
        close(client_fd);
    }

    // Temizlik yap
    close(server_fd);
    SSL_CTX_free(ctx);
    cleanup_openssl();

    return 0;
}