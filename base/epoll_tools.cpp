#include "epoll_tools.h"

epoll_tools::epoll_tools()
{
    //只需要监听一个描述符——标准输入
    epoll_fd = epoll_create(1);
}


epoll_tools::~epoll_tools()
{

}


int epoll_tools::fun_add_socket(int fd )
{
    //ev用于reg事件
    epoll_event ev ;
    ev.data.fd = fd;
    // 监听读状态同时设置ET模式
    ev.events  = EPOLLIN;
    //注册epoll事件
    return epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}


int epoll_tools::fun_del_socket(int fd)
{
    // ev 用于del事件
    epoll_event ev ;
    ev.data.fd = fd;
    ev.events  = EPOLLIN;
    //注册epoll事件
    return epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev);
}

int epoll_tools::fun_wait(epoll_event *events,
                          int maxevents, int timeout)
{
    return epoll_wait( epoll_fd  ,
                       events    ,
                       maxevents ,
                       timeout   );
}

