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

using namespace std;

HttpRequest::HttpRequest(
    MessageEncoding message_encoding,
    string body,
    string origin,
    string path,
    string method,
    map<string, string> headers
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

string HttpRequest::get_body() {
    return body;
}

string HttpRequest::get_origin() {
    return origin;
}

string HttpRequest::get_path() {
    return path;
}

string HttpRequest::get_method() {
    return method;
}

map<string, string> HttpRequest::get_headers() {
    return headers;
}