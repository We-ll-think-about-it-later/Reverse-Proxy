#include "service.h"


namespace service {
    void init_service(nlohmann::json& cfg){
        for(const auto& [service_name,service_list] : cfg["micro_service"].items()){
            std::list<std::pair<std::string,int32_t>> list;
            for(const auto& server : service_list)
                list.push_back(std::make_pair(server["ip"].get<std::string>(),server["port"].get<int32_t>()));
            service::list[service_name] = list;
        }
    }
}