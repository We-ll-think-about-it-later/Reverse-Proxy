#include "balancer.h"
#include "../net/request/request.h"
#include <iostream>
namespace balancer {
    void TrafficBalancer::traffic_handler(std::list<std::pair<std::string, int32_t>>& list) {
        while (!list.empty()) {
            for (auto it = list.begin(); it != list.end(); ) {
                int32_t count = 0;
                std::cout << "Trying to connect to server: " << it->first << ":" << it->second << std::endl;
                while (count < 3) {
                    try {
                        std::string response = net::request::new_request(
                                net::request::Methods::GET, it->first, it->second, "/", "");
                        nlohmann::json::parse(response);
                        std::cout << "Server responded successfully: " << it->first << ":" << it->second << std::endl;
                        break;

                    } catch (...) {
                        count++;
                        std::cout << "Attempt " << count << " failed for server: " << it->first << ":" << it->second << std::endl;
                        if (count == 3) {
                            std::cout << "Removing server due to 3 failed attempts: " << it->first << ":" << it->second << std::endl;
                        }
                    }
                }
                if (count == 3) {
                    it = list.erase(it);
                } else {
                    ++it;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }

        throw std::runtime_error("All servers have been removed from the list.");
    }

    void init_balancer(std::unordered_map<std::string,std::list<std::pair<std::string,int32_t >>>& list){
        for(const auto& service  : list){
            TrafficBalancer balancer = {
                    service.second
            };
        }
    }
}