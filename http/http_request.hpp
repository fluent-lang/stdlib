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

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <map>
#include "message_encoding.h"

class HttpRequest {
    private:
        MessageEncoding message_encoding;
        std::string body;
        std::string origin;
        std::string path;
        std::string method;
        std::map<std::string, std::string> headers;

    public:
        HttpRequest(
            MessageEncoding message_encoding,
            std::string body,
            std::string origin,
            std::string path,
            std::string method,
            std::map<std::string, std::string> headers
        );

        MessageEncoding get_message_encoding(const char* file, int line);
        std::string get_body(const char* file, int line);
        std::string get_origin(const char* file, int line);
        std::string get_path(const char* file, int line);
        std::string get_method(const char* file, int line);
        std::map<std::string, std::string> get_headers(const char* file, int line);
};

#endif
