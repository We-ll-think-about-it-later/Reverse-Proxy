#ifndef PROXY_LOGGER_H
#define PROXY_LOGGER_H
#include <thread>
#include <string>
#include <mutex>
#include <filesystem>
namespace logger {
    class logger {
    public:
        logger();
    public:
        void push(std::string message){
            std::lock_guard<std::mutex> lock(m_mutex);
            this->m_last_message = message;
        }
    private:
        void init(){
            this->m_thread.detach();
        }
        void push_log(std::string data);
        void handler();

    private:
        std::filesystem::path file_log = "log/log.txt";
        std::thread m_thread;
        std::string m_last_message;
        std::mutex m_mutex;

    };

    inline logger log;
}
#endif
