#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include "request.h"
#include <signal.h>
namespace net {
    namespace request {
        std::string new_request(Methods method,std::string ip,int32_t port ,std::string address,std::string data){
            signal(SIGPIPE, SIG_IGN);
            sockaddr_in in_address;
            in_address.sin_family = AF_INET;
            in_address.sin_port = htons(port);
            in_address.sin_addr.s_addr = inet_addr(ip.c_str());

            int sock = socket(AF_INET,SOCK_STREAM,0);
            int conn = connect(sock,(sockaddr*)&in_address,sizeof(in_address));

            std::string request_buffer;
            {
                switch (method) {
                    case Methods::GET: {
                        request_buffer += "GET";
                        break;
                    }

                    case Methods::POST: {
                        request_buffer += "POST";
                        break;
                    }

                    case Methods::DELETE: {
                        request_buffer += "DELETE";
                        break;
                    }
                }

                request_buffer += " " + address + " HTTP/1.1\r\n"
                                  "Host: " + ip + ":" + std::to_string(port) + "\r\n"
                                  "Content-Type: application/json; charset=utf-8\r\n"
                                  "Content-Length: " + std::to_string(data.size()) + "\r\n\r\n"
                                  + data;

            }
            send(sock,request_buffer.data(),request_buffer.size(),0);
            std::string respone_buffer;
            {
                char buffer[5500];
                int32_t size = recv(sock,buffer,sizeof(buffer),0);
                respone_buffer.assign(buffer,size);
            }

            std::cout<< respone_buffer << std::endl;
            for(auto it = respone_buffer.begin(); it != respone_buffer.end();it++){
                if(*it != '{' && *it != '[')
                    continue;
                respone_buffer = std::string(it,respone_buffer.end());
                break;
            }
            close(sock);
            return  respone_buffer;
        }
    }
}