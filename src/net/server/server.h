#ifndef PROXY_SERVER_H
#define PROXY_SERVER_H
#include <thread>
#include <functional>
#include <string>
#include <unordered_map>

#include "../../components/boost/include/boost/asio.hpp"
#include "../request/request.h"
#include "../../logger/logger.h"
namespace  net {
    namespace server {
        class Server {
        public:
            std::thread m_thread;
            std::unordered_map<std::string,std::pair<request::Methods,std::function<request::Respone(std::string)>>> m_map_handler;

            boost::asio::ip::tcp::endpoint m_point;
            boost::asio::io_service  m_service;
        public:
            Server(boost::asio::ip::tcp::endpoint point)
                : m_thread(&Server::handler_server,this), m_point(point) {}
        public:
            void run(){
                logger::log.push("RUN SERVER");
                this->m_thread.join();
            }

            void append_handler(std::string name_handler,request::Methods meth,std::function<request::Respone(std::string)> func);

        private:
            void write_data(boost::asio::ip::tcp::socket& socket,request::Respone respone);
            void write_data_error(boost::asio::ip::tcp::socket& socket,request::Respone respone);

            void handler_server();
            void handler_request(boost::asio::ip::tcp::socket& socket);
        };
    }
}
#endif //PROXY_SERVER_H
