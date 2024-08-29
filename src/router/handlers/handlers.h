#ifndef PROXY_HANDLERS_H
#define PROXY_HANDLERS_H
#include "../../net/request/request.h"

namespace handler {
    namespace auth {
        net::request::Respone HandlerLogin(std::string data);
        net::request::Respone HandlerRegistration(std::string data);
    }
}
#endif //PROXY_HANDLERS_H
