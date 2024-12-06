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

#include "../lang/string.hpp"
#include <map>
#include "message_encoding.h"

class HttpRequest {
    private:
        MessageEncoding message_encoding;
        String body;
        String origin;
        String path;
        String method;
        std::map<String, String> headers;

    public:
        HttpRequest(
            MessageEncoding message_encoding,
            String body,
            String origin,
            String path,
            String method,
            std::map<String, String> headers
        );

        MessageEncoding get_message_encoding();
        String get_body();
        String get_origin();
        String get_path();
        String get_method();
        std::map<String, String> get_headers();
};

#endif
