cmake_minimum_required(VERSION 3.29)
project(proxy)

set(CMAKE_CXX_STANDARD 17)
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/components/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.84.0 REQUIRED COMPONENTS system filesystem)

add_executable(proxy
        src/main.cpp
        src/config/config.h
        src/logger/logger.h
        src/logger/logger.cpp
        src/net/server/server.h
        src/net/server/server.cpp

        src/net/request/request.h
        src/net/request/request.cpp
#        src/router/router.h
#        src/router/router.cpp
#        src/router/handlers/handlers.h
#        src/router/handlers/auth/auth.cpp
#        src/model/model.h
#        src/net/request/request.cpp
#        src/service/service.h
#        src/service/auth/auth.cpp
#        src/service/service.cpp
        src/balancer/balancer.h
        src/balancer/balancer.cpp
        src/router/router.h
        src/router/router.cpp
        src/router/handlers/handlers.h
        src/router/handlers/auth/auth.cpp
        src/service/service.h
        src/service/service.cpp
        src/service/auth/auth.cpp
)

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
endif()