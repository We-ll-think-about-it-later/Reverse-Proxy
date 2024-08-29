#include "logger.h"
#include <iostream>
#include <fstream>

namespace logger {
    logger::logger() {
        this->m_thread = std::thread(&logger::handler,this);
        if(!std::filesystem::exists("log")){
            std::filesystem::path dir("log");
            std::filesystem::create_directory(dir);
        }

    }
    void logger::push_log(std::string data){
        std::string buffer_file;
        {
            if(std::filesystem::exists(this->file_log)){
                std::ifstream file(this->file_log.string());
                std::string line;
                while(std::getline(file,line))
                    buffer_file += line + '\n';
            }
        }

        std::ofstream  file(this->file_log.string());
        file << buffer_file +("[LOG] - > " +  data) << std::endl;
        file.close();

    }
    void logger::handler() {
        while(true){
            std::lock_guard<std::mutex> lock(m_mutex);
            if(!this->m_last_message.empty()){
                this->push_log(this->m_last_message);
                std::cout << this->m_last_message << std::endl;
                this->m_last_message.clear();
            }
            std::this_thread::sleep_for(std::chrono::microseconds(300));
        }
    }
}