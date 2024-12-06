#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "http_response.hpp"
#include "http_request.hpp"
#include "http_server.hpp"
#include "../lang/result.hpp"
#include "../lang/err.hpp"

Result<bool, GenericErr> create_http_server(int port, HttpResponse (*callback)(HttpRequest));

#endif