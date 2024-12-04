/*
    These files are part of the Surf's standard library.
    They're bundled with the main program by the compiler
    which is then converted to machine code.

    -----
    License notice:

    This code is released under the GNU GPL v3 license.
    The code is provided as is without any warranty
    Copyright (c) 2024 Rodrigo R. & all Surf contributors
*/

#include "http_server.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "http_response.hpp"
#include "http_request.hpp"
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include <arpa/inet.h>
#include <optional>

using namespace std;

Result<bool, GenericErr> create_http_server(int port, HttpResponse (*callback)(HttpRequest)) {
    int server_fd, new_socket;
    struct sockaddr_in address, client_address;
    int addrlen = sizeof(address);
    socklen_t client_addrlen = sizeof(client_address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        return Result(false, optional<GenericErr>(GenericErr("Socket creation failed")));
    }

    // Setup server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port); // Use the 'port' argument instead of hardcoding 8080

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        return Result(false, optional<GenericErr>(GenericErr("Bind failed")));
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        return Result(false, optional<GenericErr>(GenericErr("Listen failed")));
    }

    // Accept connections
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&client_address, &client_addrlen)) < 0) {
            // Accept connection failed, continue without crashing
            continue;
        }

        // Extract client's IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

        // Read the raw request data
        char buffer[30000] = {0};
        int valread = recv(new_socket, buffer, 30000, 0);
        if (valread < 0) {
            perror("Read failed");
            close(new_socket);
            continue;
        }

        // Parse the HTTP request
        istringstream request_stream(buffer);
        string line;
        getline(request_stream, line);
        istringstream request_line(line);
        string method, path, version;

        request_line >> method >> path >> version;

        map<string, string> headers;
        while (getline(request_stream, line) && line != "\r") {
            istringstream header_line(line);
            string key, value;
            getline(header_line, key, ':');
            getline(header_line, value);
            headers[key] = value;
        }

        string body;
        if (headers.find("Content-Length") != headers.end()) {
            int content_length = stoi(headers["Content-Length"]);
            body.resize(content_length);
            request_stream.read(&body[0], content_length);
        }

        MessageEncoding message_encoding = MessageEncoding::TEXT;

        if (headers.find("Content-Type") != headers.end()) {
            if (headers["Content-Type"] == "application/json") {
                message_encoding = MessageEncoding::JSON;
            }
        }

        // Create a new HttpRequest to send the callback
        HttpRequest request(
            message_encoding,
            body,
            client_ip,
            path,
            method,
            headers
        );

        // Use the callback to generate a response
        HttpResponse response = callback(request);

        string response_str = "HTTP/1.1 ";

        response_str += to_string(response.get_status_code()) + " " + response.get_status_detail() + "\n";

        for (auto const& [key, val] : response.get_headers()) {
            response_str += key + ": " + val + "\n";
        }

        response_str += "\n" + response.get_message();

        send(new_socket, response_str.c_str(), response_str.size(), 0);

        // Close the socket
        close(new_socket);
    }

    return Result<bool, GenericErr>(true, nullopt);
}