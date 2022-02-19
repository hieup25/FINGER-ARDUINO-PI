#include "../include/HttpServer.hpp"
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/http_compat.h>
#include <event2/event_struct.h>
#include <event2/event.h>
#include <event2/event_compat.h>
#include <event2/buffer.h>
#include <event2/buffer_compat.h>
#include <event2/bufferevent_struct.h>
#include <event2/bufferevent_compat.h>
#include <event2/tag.h>
#include <event2/tag_compat.h>
#include "../include/DataStudent.hpp"

std::vector<int> g_check;

struct HttpServer::Impl
{    
    private:
    DataStudent data_student;
    public:
    struct event_base* base = NULL;
    struct evhttp* server = NULL;
    bool startWith(const char **src, const char *dst);
    static void callback(struct evhttp_request* request, void* param);
    const std::string readHeader(struct evhttp_request *request);
    const std::string readContent(struct evhttp_request *request);
    void make_response(struct evhttp_request *request, info_t& info);
    void sendJson(struct evhttp_request *request, int status, json &j);
};

HttpServer::HttpServer() : _impl(new Impl)
{

}
HttpServer::~HttpServer()
{
    if (this->_impl->server != NULL)
    {
        evhttp_free(this->_impl->server);
    }
    if (this->_impl->base != NULL)
    {
        event_base_free(this->_impl->base);
    }
}

void HttpServer::loop()
{
    if (this->_impl->base == NULL)
    {
        this->_impl->base = event_base_new();
    }
    else if (this->_impl->server == NULL)
    {
        this->_impl->server = evhttp_new(this->_impl->base);
        evhttp_set_allowed_methods(this->_impl->server, EVHTTP_REQ_OPTIONS | EVHTTP_REQ_GET);
        evhttp_set_gencb(this->_impl->server, this->_impl->callback, this);

        if (evhttp_bind_socket(this->_impl->server, "0.0.0.0", PORT_SERVER) != 0)
        {
            std::cout << "HTTP Server bind fail" << std::endl;
        }
        else
        {
            std::cout << "HTTP Server Listening on 0.0.0.0:" << PORT_SERVER << std::endl;
        }
    }
    else
    {
        event_base_loop(this->_impl->base, EVLOOP_NONBLOCK);
    }
}
bool HttpServer::Impl::startWith(const char **src, const char *dst)
{
    const char *str = *src;
    size_t len = strlen(dst);
    if (strncmp(str, dst, len) == 0)
    {
        *src = str + len;
        return true;
    }
    else
    {
        return false;
    }
}
const std::string HttpServer::Impl::readHeader(struct evhttp_request *request)
{
    std::string cmdType;
    switch (evhttp_request_get_command(request)) {
    case EVHTTP_REQ_GET: cmdType = "GET"; break;
    case EVHTTP_REQ_POST: cmdType = "POST"; break;
    case EVHTTP_REQ_HEAD: cmdType = "HEAD"; break;
    case EVHTTP_REQ_PUT: cmdType = "PUT"; break;
    case EVHTTP_REQ_DELETE: cmdType = "DELETE"; break;
    case EVHTTP_REQ_OPTIONS: cmdType = "OPTIONS"; break;
    case EVHTTP_REQ_TRACE: cmdType = "TRACE"; break;
    case EVHTTP_REQ_CONNECT: cmdType = "CONNECT"; break;
    case EVHTTP_REQ_PATCH: cmdType = "PATCH"; break;
    default: cmdType = "unknown"; break;
    }
    return cmdType;
}
const std::string HttpServer::Impl::readContent(struct evhttp_request *request)
{
    std::string content;
    struct evbuffer *buffer;
    buffer = evhttp_request_get_input_buffer(request);
    while (evbuffer_get_length(buffer) > 0)
    {
        int n;
        char cbuf[1024];
        n = evbuffer_remove(buffer, cbuf, sizeof(cbuf));
        if (n > 0)
        {
            content += std::string(cbuf, n);
        }
    }
    return content;
}
void HttpServer::Impl::make_response(struct evhttp_request *request, info_t& info)
{
    if (info.status != 200)
    {
        json res;
        res["status"] = "failure";
        res["reason"] = info.mess;
        sendJson(request, info.status, res);
    }
    else
    {
        info.res["status"] = "success";
        sendJson(request, 200, info.res);
    }
}
void HttpServer::Impl::sendJson(struct evhttp_request *request, int status, json &j)
{
    struct evbuffer *buffer;
    std::string content;
    content = j.dump();
    buffer = evbuffer_new();
    evhttp_add_header(request->output_headers, "Content-Type", "application/json");
    evhttp_add_header(request->output_headers, "Content-Length", std::to_string(content.size()).c_str());
    evhttp_add_header (request->output_headers, "Access-Control-Allow-Origin", "*");
    evhttp_add_header (request->output_headers, "Access-Control-Expose-Headers", "X-Transmission-Session-Id");
    evhttp_add_header(request->output_headers, "Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    evhttp_add_header(request->output_headers, "Access-Control-Allow-Headers", "Authorization, Content-Type, X-Transmission-Session-Id");
    evbuffer_add(buffer, content.data(), content.size());
    evhttp_send_reply(request, status, NULL, buffer);
    evbuffer_free(buffer);
}

void HttpServer::Impl::callback(struct evhttp_request *request, void *param)
{
    auto server = static_cast<HttpServer*>(param);
    info_t info_response;
    const char *urisz = evhttp_request_get_uri(request);
    struct evhttp_uri *uri = NULL;
    uri = evhttp_uri_parse(urisz);
    if (uri != NULL)
    {
        const char *path = evhttp_uri_get_path(uri);
        if (server->_impl->startWith(&path, "/getdata"))
        {
            std::string pathStr = path;

            // std::cout << "pathstr: " << pathStr << std::endl;
            if (server->_impl->readHeader(request) == "GET") //GET
            {
                json result;
                auto check = server->_impl->data_student.GetAttendance();
                // // std::vector<std::pair<int, std::string>>
                // std::map<int, std::pair<int, std::string>> m;
                // // std::map<int, int> m;
                // for (auto i = 0; i < check.size(); i++)
                // {
                //     if (check[i].first == 0)
                //     {
                //         m[i] = {0, check[i].second};
                //     }
                //     else
                //     {
                //         m[i] = {1, check[i].second};
                //     }
                // }
                result["data"] = check;
                info_response = {200, "ok", result};
            }
            else if (server->_impl->readHeader(request) == "OPTIONS") //OPTIONS
            {
                json res;
                res["message"] = "ready share data";
                info_response = {200, "", res};
            }
            else
            {
                info_response = {400, "method not support"};
            }
        }
        else
        {
            info_response = {400, "not found"};
        }
        server->_impl->make_response(request, info_response);
    }
    evhttp_uri_free(uri);
}