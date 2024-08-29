#include "../handlers.h"
#include "../../../service/service.h"
#include "../../../model/model.h"


namespace handler {
    namespace auth {
        net::request::Respone HandlerLogin(std::string data){
            try {
                nlohmann::json object = nlohmann::json::parse(data);
                model::auth::LoginData login_data = {
                    {
                        object["data"]["login"],
                        object["data"]["password"]
                    },
                    object["session_key"]
                };

                if(login_data.data.password.empty() || login_data.data.login.empty() || login_data.session_key.empty()){
                    return {
                            "Invalid data #2",
                            404
                    };
                }
                return service::auth::service_login(login_data);
            } catch(...) {
                return {
                        "Invalid data #1",
                    404
                };
            }
        }

        net::request::Respone HandlerRegistration(std::string data){
            try {
                nlohmann::json object = nlohmann::json::parse(data);
                model::auth::RegistrationData registration_data = {
                        {
                            object["member"]["name"],
                            object["member"]["surname"],
                            object["member"]["username"],
                            object["member"]["age"]
                        },{
                            object["data"]["login"],
                            object["data"]["password"]
                        },
                        object["email"],
                        object["session_key"]
                };
                bool is_valid_data = registration_data.data.login.empty() ||
                        registration_data.data.password.empty() ||
                        registration_data.email.empty();

                bool is_valid_member = registration_data.member.username.empty() ||
                        registration_data.member.name.empty() ||
                        registration_data.member.age <= 14 ||
                        registration_data.member.surname.empty();

                if(is_valid_data || is_valid_member || registration_data.session_key.empty()){
                    return {
                            "Invalid data #2",
                            404
                    };
                }
                return service::auth::service_registration(registration_data);
            } catch (...) {
                return {
                    "Invalid data #1",
                    404
                };
            }
        }
    }
}