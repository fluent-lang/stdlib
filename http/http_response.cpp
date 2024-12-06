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
#include "message_encoding.h"

using namespace std;

HttpResponse::HttpResponse(
    MessageEncoding message_encoding,
    const char* message,
    const char* status_detail,
    map<String, String> headers,
    int status_code
) :
    message_encoding(message_encoding),
    message(String(message)),
    status_detail(String(status_detail)),
    headers(headers),
    status_code(status_code) {}

String HttpResponse::get_message() {
    return message;
}

MessageEncoding HttpResponse::get_message_encoding() {
    return message_encoding;
}

int HttpResponse::get_status_code() {
    return status_code;
}

String HttpResponse::get_status_detail() {
    return status_detail;
}

map<String, String> HttpResponse::get_headers() {
    return headers;
}