#ifndef PROXY_CONFIG_H
#define PROXY_CONFIG_H
#include <filesystem>
#include <fstream>
#include <string>
#include "../components/json/json.hpp"
namespace config {
    inline nlohmann::json init_config(const char* path_str){
        std::filesystem::path file(path_str);
        if(!std::filesystem::exists(file))
            throw std::runtime_error("NO CONFIG FILE");

        std::ifstream stream(file.string());
        std::string buffer,cur;

        while(std::getline(stream,buffer))
            cur += buffer + '\n';

        try {
            return  nlohmann::json::parse(cur);
        } catch(std::exception& err) {
            throw std::runtime_error(err.what());
        }
    }
}
#endif //PROXY_CONFIG_H
