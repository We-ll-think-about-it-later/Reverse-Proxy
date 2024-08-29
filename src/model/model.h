#ifndef PROXY_MODEL_H
#define PROXY_MODEL_H

#include <cstdint>
#include <string>
namespace model {
    namespace entity {
        class Member {
        public:
            std::string name;
            std::string surname;
            std::string username;
            int16_t  age;

            Member(std::string name,std::string surname,std::string username,int16_t age)
                : name(name), surname(surname), username(username), age(age) {}
            Member() {}
        };
    }

    namespace auth {

        struct Credentials {
            std::string login;
            std::string password;
            Credentials(std::string login,std::string password)
                : login(login), password(password) {}

            Credentials() {}
        };
        struct LoginData {
            Credentials data;
            std::string session_key;
            LoginData(Credentials data,std::string key)
                : data(data),session_key(key) {}
            LoginData() {}

        };
        struct RegistrationData {
             entity::Member member;
             Credentials data;
             std::string email;
             std::string session_key;
             RegistrationData(entity::Member mem,Credentials data,std::string email,std::string key)
                : member(mem), data(data), email(email),session_key(key) {}
             RegistrationData(){}
        };
    }
}



#endif //PROXY_MODEL_H
