#include "base_node.h"
#include "base_event.h"
#include "stdio.h"

class test_node : base_node{
public:
    test_node(){
    }
    ~test_node(){
    }
    bool fun_is_recv(std::shared_ptr<base_event> _e) override{
        return true;
    }
    int fun_exec(std::shared_ptr<base_event> _e) override{
        usleep(10);
        printf("size %d\r\n" , m_sub_events.size());
    }
};
int main()
{
    test_node m_node ;
    base_node::fun_start() ;

    while (1){
        auto _e = std::make_shared<base_event>(e_type_base) ;
        base_node::fun_send_event(_e);
        usleep(1000);
        printf("-");
    }
    return 0;
}