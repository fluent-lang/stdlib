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

#include "http_request.hpp"
#include "../lang/string.hpp"

using namespace std;

HttpRequest::HttpRequest(
    MessageEncoding message_encoding,
    String body,
    String origin,
    String path,
    String method,
    map<String, String> headers
) : 
    message_encoding(message_encoding),
    body(body),
    origin(origin),
    path(path),
    method(method),
    headers(headers) {}

MessageEncoding HttpRequest::get_message_encoding() {
    return message_encoding;
}

String HttpRequest::get_body() {
    return body;
}

String HttpRequest::get_origin() {
    return origin;
}

String HttpRequest::get_path() {
    return path;
}

String HttpRequest::get_method() {
    return method;
}

map<String, String> HttpRequest::get_headers() {
    return headers;
}