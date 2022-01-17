/*
* Create: HieuPV
* Date  : 28/07/21
*/
#pragma once
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <memory>
#include "json.hpp"

#define PORT_SERVER 4000
struct info_t{
    int status;
    std::string mess;
    json res;
};
class HttpServer 
{
    public:
        HttpServer();
        ~HttpServer();
        void loop();
    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
        // volatile bool relax;
        bool adjust;
        uint32_t n_time_relax; 
};