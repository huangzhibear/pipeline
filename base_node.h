#ifndef BASE_NODE_H
#define BASE_NODE_H

#include "base/epoll_tools.h"

#include <thread>
#include <list>
#include <vector>
#include <mutex>
#include <functional>
#include <condition_variable>

#include "def_head.h"
#include "base/BS_thread_pool.hpp"
#include "base_event.h"

//定义 回调
using exec_handle = std::function<int ( std::shared_ptr<base_event> )> ;

class base_node {

public:
    std::unordered_map < int , exec_handle  > m_mapping ;

    static BS::thread_pool m_pool ;

    static std::vector < base_node * >  s_nodes;
    static std::thread m_thread[ DEF_THREAD_COUNT ] ;

    base_node();
    virtual ~base_node();

    static int fun_start();
    static int fun_dowork();


    static std::condition_variable m_cond ;
    static std::mutex  m_mutex ;
    static std::list < std::shared_ptr<base_event> >  m_events ;

    virtual bool fun_is_recv    ( std::shared_ptr<base_event> _e ) ;// 是否接收该类型的数据
    virtual int  fun_exec       ( std::shared_ptr<base_event> _e ) ;
    static  int  fun_send_event ( std::shared_ptr<base_event> _e ) ;


    std::thread m_sub_thread ;
    int fun_sub_dowork()  ;
    std::condition_variable m_sub_cond ;
    std::mutex  m_sub_mutex ;
    std::list < std::shared_ptr<base_event> >  m_sub_events ;
    int  fun_dispatcher_event ( std::shared_ptr<base_event> _e ) ;
};


#endif // BASE_NODE_H
