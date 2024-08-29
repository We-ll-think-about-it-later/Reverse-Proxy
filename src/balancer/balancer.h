#ifndef PROXY_BALANCER_H
#define PROXY_BALANCER_H
#include <map>
#include <list>
#include <string>
#include <thread>
#include "../components/json/json.hpp"


namespace balancer {
    class TrafficBalancer {
    public:
        TrafficBalancer(std::list<std::pair<std::string,int32_t >> list){
            std::thread th([this,list = std::move(list) ]() mutable {
                this->traffic_handler(list);
            });
            th.detach();
        }
    private:
        void traffic_handler(std::list<std::pair<std::string,int32_t >>& list);
    };
    void init_balancer(std::unordered_map<std::string,std::list<std::pair<std::string,int32_t >>>& list);
}
#endif //PROXY_BALANCER_H
