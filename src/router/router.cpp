#include "router.h"
#include "handlers/handlers.h"
#include "../net/server/server.h"

namespace router {
    void init_router(std::string ip,uint_least16_t port){
        net::server::Server server({boost::asio::ip::make_address(ip),port});
        server.append_handler("/auth/login",net::request::Methods::GET,handler::auth::HandlerLogin);
        server.append_handler("/auth/register",net::request::Methods::POST,handler::auth::HandlerRegistration);
        server.run();
    }
}