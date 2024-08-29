#include "../service.h"
#include <iostream>

namespace service {
    namespace auth {
        net::request::Respone service_login(model::auth::LoginData data){
            try {
                nlohmann::json object = {
                        {"data",{
                                {"login",data.data.login},
                                {"password",data.data.password}
                        }},
                        {"session_key",data.session_key}
                };

                for(auto pair : service::list["auth"]){
                    int32_t count = 0;
                    while(count < 3){
                        try {
                            std::string respone = net::request::new_request(net::request::Methods::GET,pair.first,pair.second,"/auth/login",object.dump());
                            nlohmann::json::parse(respone);
                            return {
                                respone,
                                200
                            };
                        } catch(...) {
                            count++;
                            continue;
                        }
                    }
                }
                return {
                        "Error request #2",
                        404
                };
            } catch(...){
                return {
                     "Error request #1",
                    404
                };
            }
        }


        net::request::Respone service_registration(model::auth::RegistrationData data){
            try {
                nlohmann::json object {
                    {"member",{
                            {"name",data.member.name},
                            {"surname",data.member.surname},
                            {"username",data.member.username},
                            {"age",data.member.age}
                    }},
                    {"data",{
                        {"login",data.data.login},
                        {"password",data.data.password}
                    }},
                    {"email",data.email},
                    {"session_key",data.session_key}
                };

                for(auto pair : service::list["auth"]){
                    int32_t count = 0;
                    while(count < 3){
                        try {
                            std::string respone = net::request::new_request(net::request::Methods::POST,pair.first,pair.second,"/auth/register",object.dump());
                            nlohmann::json::parse(respone);
                            return {
                                    respone,
                                    200
                            };
                        } catch(...) {
                            count++;
                            continue;
                        }
                    }
                }


            } catch(...){
                return {
                   "Error request #1",
                   404
                };
            }
        }

    }
}