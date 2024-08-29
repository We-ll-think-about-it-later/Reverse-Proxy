#ifndef PROXY_SERVICE_H
#define PROXY_SERVICE_H
#include <string>
#include <list>

#include "../model/model.h"
#include "../net/request/request.h"


namespace service {
    namespace auth {
        net::request::Respone service_login(model::auth::LoginData data);
        net::request::Respone service_registration(model::auth::RegistrationData data);
    }
    inline std::unordered_map<std::string,std::list<std::pair<std::string,int32_t >>> list;
    void init_service(nlohmann::json& cfg);
}

#endif //PROXY_SERVICE_H
