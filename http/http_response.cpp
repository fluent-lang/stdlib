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

#include "http_response.hpp"
#include <map>

using namespace std;

HttpResponse::HttpResponse(
    MessageEncoding message_encoding,
    string message,
    string status_detail,
    map<string, string> headers,
    int status_code
) :
    message_encoding(message_encoding),
    message(message),
    status_detail(status_detail),
    headers(headers),
    status_code(status_code) {}

string HttpResponse::get_message(const char* file, int line) {
    return message;
}

MessageEncoding HttpResponse::get_message_encoding(const char* file, int line) {
    return message_encoding;
}

int HttpResponse::get_status_code(const char* file, int line) {
    return status_code;
}

string HttpResponse::get_status_detail(const char* file, int line) {
    return status_detail;
}

map<string, string> HttpResponse::get_headers(const char* file, int line) {
    return headers;
}