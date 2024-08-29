#include "config/config.h"
#include "router/router.h"
#include "balancer/balancer.h"
#include "service/service.h"
#include <iostream>


int main(void) {
    nlohmann::json cfg = config::init_config("config.json");
    service::init_service(cfg);
    balancer::init_balancer(service::list);
    router::init_router(cfg["proxy_server"]["ip"],cfg["proxy_server"]["port"]);
    getchar();

    return 0;
}