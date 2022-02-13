/*
* Create: HieuPV
* Date  : 28/07/21
*/
#include "../include/Interface.hpp"
#include <pthread.h>
#include "../include/HttpServer.hpp"

struct Interface::Impl
{
    bool destroy;
    pthread_t id_thr;
    HttpServer http_server;
    Uart uart;
    static void* serverThread(void* param)
    {
        auto p = static_cast<Impl*>(param);
        while (!p->destroy)
        {
            p->http_server.loop();
            usleep(10000);
        }
        pthread_exit(NULL);
    }
};
Interface::Interface() : _impl(new Impl)
{
    this->_impl->destroy = false;
}
Interface::~Interface()
{

}
void Interface::runForever()
{
    int thr = pthread_create(&this->_impl->id_thr, NULL, this->_impl->serverThread, _impl.get());
    std::cout << "RUN FOREVER CREATE" << ((thr == 0) ? "FINISH" : "FAIL") << std::endl;
    pthread_join(this->_impl->id_thr, NULL);
}
