<div align="center">
  <h1>My Simple HTTP Server</h1> <img src="" alt="http Logo" width="80"></br></br>
</div>

---

### Project Description

This project is a **simple HTTPS server** developed using the C programming language. The server establishes secure connections using SSL/TLS and handles HTTP requests from clients to serve responses. The project includes core functionalities such as serving static files, handling user feedback, and providing data in JSON format via a simple API.

The goal of the project is to gain a better understanding of web development processes and enhance networking skills in C. The server allows users to securely access content via web browsers and communicates using basic HTTP protocol. It is powered by the OpenSSL library to implement SSL/TLS protocols and serves as a foundational example for C-based applications.

---

### Features

- **Secure Connection**: Ensures secure communication using SSL/TLS connections established with OpenSSL. This is essential for maintaining data integrity and confidentiality.
  
- **Static File Serving**: Ability to serve HTML, CSS, and JavaScript files to clients, laying the groundwork for dynamic content delivery.
  
- **Client Feedback Handling**: Processes feedback from users and returns appropriate responses. This enhances user interaction and responsiveness of web applications.
  
- **Simple API**: Serves user data in JSON format, making it easier for developers to interact with the server.
  
- **Easy Setup**: Straightforward setup and launch steps allow users to get the project up and running quickly.

---

### Requirements

To run the project, the following dependencies are required:

- **C Compiler**: GCC or any other C compiler.
- **OpenSSL Library**: Required to use SSL/TLS protocols.
- **pthread Library**: For multi-threading support.

---

### Installation Steps

1. **Clone the Repository**

First, clone the project from GitHub:
```bash
git clone https://github.com/your_username/simple-http-server.git
cd simple-http-server

```

2. **Install Dependencies**

Install OpenSSL and other necessary libraries. On Ubuntu:
```bash
sudo apt-get update
sudo apt-get install libssl-dev
```

3. **Generate SSL Certificate**

To generate the required SSL/TLS certificate and private key:
```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt
```

This command will prompt you for some information (country, state, organization, etc.). After completing, `server.crt` and `server.key` files will be created.

4. **Compile the Project**

Compile the server using the following command:
```bash
gcc -o https_server https_server.c -lssl -lcrypto -lpthread
```

This will generate an executable named `https_server`.

---

### Usage

**1. Start the Server**

Run the server with:
```bash
sudo ./https_server
```
By default, the server listens on port 4433. You should see a message like:
"Listening on port 4433..."

2. **Test in Browser**

`https://localhost:4433`
You may encounter a security warning—this is expected since you're using a self-signed certificate. Proceed to continue and you should see the server homepage.

3. **Send Feedback**

Fill out the feedback form on the homepage to submit input to the server. Once submitted, the server will process the data and respond with a confirmation message.

4. **View Users**

To see user data in JSON format, visit: `https://localhost:4433/users`

---

### Project Structure

- `https_server.c`: Main server logic, handles SSL connections, HTTP requests, and responses.
- `simple_http_server.h`: Header file with function and variable declarations used across the project.
- `server.crt`: SSL certificate file.
- `server.key`: SSL private key file.
- `index.html`: Homepage served by the server.
- `styles.css`: Styling for the homepage.
- `script.js`: JavaScript file for homepage interactions.

---

<div align="center">
  <b>2023 | Created by Derya ACAR</b>
</div>
