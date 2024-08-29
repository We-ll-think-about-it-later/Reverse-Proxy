#include "server.h"
#include <iostream>

namespace  net {
    namespace  server {
        void Server::append_handler(std::string name_handler,request::Methods meth,std::function<request::Respone(std::string)> func){
            this->m_map_handler[name_handler] = std::make_pair(meth,func);
        }

        void Server::write_data(boost::asio::ip::tcp::socket& socket,request::Respone respone){
            std::string data = {
                    "HTTP/1.1 200 OK \r\n"
                    "Content-Type: application/json; charset=utf-8\r\n"
                    "Content-Length: " + std::to_string(respone.get_data().size()) + "\r\n\r\n"
            };
            socket.write_some(boost::asio::buffer(data + respone.get_data()));
        }

        void Server::write_data_error(boost::asio::ip::tcp::socket& socket,request::Respone respone){
            std::string data = {
                    "HTTP/1.1 404 BadRequest \r\n"
                    "Content-Type: application/json; charset=utf-8\r\n"
                    "Content-Length: " + std::to_string(respone.get_dump_data().size()) + "\r\n\r\n"
            };
            socket.write_some(boost::asio::buffer(data + respone.get_dump_data()));
        }

        void Server::handler_request(boost::asio::ip::tcp::socket& socket){
            request::Request req;
            {
                char buffer[5500 * sizeof(int32_t )];
                int32_t size = socket.read_some(boost::asio::buffer(buffer));
                req = std::string(buffer,size);
            }
            auto it = this->m_map_handler.find(req.get_address());
            if(it == this->m_map_handler.end()){
                this->write_data_error(socket,{
                    "Invalid address",
                    404
                });
                socket.close();
                return;
            }
            std::pair pair = it->second;
            if(pair.first !=req.get_method()){
                this->write_data_error(socket,{
                        "Invalid method",
                        404
                });
                socket.close();
                return;
            }
            if(!req.is_dump()){
                this->write_data_error(socket,{
                        "Invalid data",
                        404
                });
                socket.close();
                return;
            }
            request::Respone respone = pair.second(req.get_data());
            if(respone.get_code() != 200)
                this->write_data_error(socket,respone);
            else
                this->write_data(socket,respone);

            socket.close();
        }

        void Server::handler_server() {
            boost::asio::ip::tcp::acceptor acceptor(m_service, this->m_point);
            while (true) {
                boost::asio::ip::tcp::socket socket(m_service);
                acceptor.accept(socket);

                std::thread th([this, socket = std::move(socket)]() mutable {
                    this->handler_request(socket);
                });
                th.detach();
            }
        }

    }
}