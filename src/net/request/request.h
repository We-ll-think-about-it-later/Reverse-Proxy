#ifndef PROXY_REQUEST_H
#define PROXY_REQUEST_H
#include <string>
#include "../../components/json/json.hpp"
namespace net {
    namespace request {
        enum class Methods {
            GET,
            POST,
            DELETE,
            NONE
        };

        class Respone {
        public:
            Respone(std::string data,int32_t code)
                : m_code(code),m_data(data), m_data_all(init_data(data)) {}

            Respone(){}
        public:
            std::string get_dump_data(){return this->m_data_all;}
            std::string get_data(){return this->m_data;}
            int32_t get_code(){return  this->m_code;}

        private:
            std::string init_data(std::string data) {
                nlohmann::json object = {
                        {"Error",data},
                };
                return object.dump();
            }
        private:
            int32_t m_code;
            std::string m_data;
            std::string m_data_all;
        };

        class Request {
        public:
            Request(std::string buffer){
                this->m_data = this->init_data(buffer);
                this->m_address = this->init_address(buffer);
                this->m_method = this->init_method(buffer);
            }
            Request(){}
        public:
            std::string get_data(){return this->m_data;}

            std::string get_address(){return this->m_address;}

            request::Methods get_method(){return this->m_method;}

            bool is_dump(){
                try {
                    nlohmann::json::parse(this->m_data);
                    return true;
                } catch(...){
                    return false;
                }
            }

        private:
            std::string init_data(std::string data){
                for(auto it = data.begin(); it != data.end();it++){
                    if(*it != '[' && *it != '{')
                        continue;
                    return std::string(it,data.end());
                }
                return "";
            }
            std::string init_address(std::string data){
                std::string buffer;
                bool isParsed = false;
                for(const auto& v : data) {
                    if(v == '/')
                        isParsed = true;

                    if(isParsed){
                        if(v == 'H' && *(&v + 3) == 'P' || v == ' ')
                            break;
                        buffer.push_back(v);
                    }
                }
                return  buffer;
            }

            Methods init_method(std::string data){
                std::string method;
                for(const auto& v : data) {
                    if(v == '\\')
                        break;
                    method.push_back(v);
                }

                switch (method[0]) {
                    case  'G':
                        return  Methods::GET;
                    case  'P':
                        return  Methods::POST;
                    case  'D':
                        return  Methods::DELETE;
                }
                return  Methods::NONE;
            }

        private:
            Methods m_method;
            std::string m_address;
            std::string m_data;
        };


        std::string new_request(Methods method,std::string ip,int32_t port,std::string address,std::string data);
    }
}
#endif //PROXY_REQUEST_H
