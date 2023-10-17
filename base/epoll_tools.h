#ifndef EPOLL_TOOLS_H
#define EPOLL_TOOLS_H

#include <sys/epoll.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>//close函数
#include <fcntl.h>//设置非阻塞

class epoll_tools {
    int epoll_fd;
public:
    epoll_tools();

    ~epoll_tools();


    int fun_add_socket(int fd);

    int fun_del_socket(int fd);

    int fun_wait(struct epoll_event *events,
                 int maxevents,
                 int timeout);

};

#endif // EPOLL_TOOLS_H
