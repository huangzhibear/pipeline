#include "base_node.h"
#include "base/environment.h"

std::vector < base_node * > base_node::s_nodes                      = {}    ;
std::thread                 base_node::m_thread[DEF_THREAD_COUNT]           ;
BS::thread_pool             base_node::m_pool(32)                           ;

base_node::base_node() {

    std::lock_guard lg(m_mutex) ;
    s_nodes.push_back(this);
    m_sub_thread = std::thread( &base_node::fun_sub_dowork ,this);
}

base_node::~base_node() {

    if( m_sub_thread.joinable()){
        m_sub_thread.join();
    }

    for(auto & it : m_thread)  {
        if( it.joinable()){
            it.join();
        }
    }
}

int base_node::fun_start() {

    for(auto & i : m_thread)  {
        i = std::thread ( &base_node::fun_dowork );
    }
    return 0;
}

std::condition_variable base_node::m_cond ;
std::mutex  base_node::m_mutex            ;
std::list < std::shared_ptr<base_event> >  base_node::m_events = {} ;

int base_node::fun_dowork() {
    while (DEF_ENV->m_flag == def_running) {
        std::unique_lock uniq(m_mutex);
        while (m_events.empty())  {
            m_cond.wait( uniq ) ;//
        }
        std::shared_ptr<base_event>  _e =  m_events.front()  ;
        if( _e !=  nullptr ) {
            for( auto  & it  :  s_nodes ){
                if(it->fun_is_recv( _e )) {
                    it->fun_dispatcher_event( _e );
//                    auto fun = std::bind( &base_node::fun_exec ,it , _e  );
//                    m_pool.push_task(fun );
                }
            }
            if( _e->m_type == e_type_exit){
                break;
            }
        }
        m_events.pop_front() ;
    }
}

bool base_node::fun_is_recv( std::shared_ptr<base_event>  _e) {
    return false;
}

int base_node::fun_exec( std::shared_ptr<base_event>  _e) {
    return 0;
}

int base_node::fun_send_event( std::shared_ptr<base_event> _e) {

    std::lock_guard lg(m_mutex) ;
    m_events.push_back(_e);
    m_cond.notify_one();
    return m_events.size();
}

int base_node::fun_dispatcher_event(std::shared_ptr<base_event> _e) {
    std::lock_guard lg(m_sub_mutex) ;

    m_sub_events.push_back(_e);
    m_sub_cond.notify_one();

    return m_sub_events.size();
}

int base_node::fun_sub_dowork() {

    std::shared_ptr<base_event>  _e = nullptr ;
    int ret_val = def_ok ;
    while (DEF_ENV->m_flag == def_running) {
        {
            std::unique_lock uniq(m_sub_mutex);
            while (m_sub_events.empty())  {
                m_sub_cond.wait( uniq ) ;//
            }
            _e = m_sub_events.front()  ;
        }
        if( _e !=  nullptr ) {
            if( _e->m_type == e_type_exit){
                break;
            }
            ret_val = fun_exec(_e);
            _e = nullptr ;
        }
        if( ret_val == def_pop_event ){
            m_sub_events.pop_front() ;
        }
    }
}