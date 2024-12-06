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

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <map>
#include "message_encoding.h"
#include "../lang/string.hpp"

class HttpResponse {
    private:
        MessageEncoding message_encoding;
        String message;
        String status_detail;
        std::map<String, String> headers;
        int status_code;
    
    public:
        HttpResponse(
            MessageEncoding message_encoding,
            const char* message,
            const char* status_detail,
            std::map<String, String> headers,
            int status_code
        );

        String get_message();
        MessageEncoding get_message_encoding();
        int get_status_code();
        String get_status_detail();
        std::map<String, String> get_headers();
};

#endif
