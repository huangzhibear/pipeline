#ifndef EVENT_H
#define EVENT_H

#include "def_head.h"
#include <stdio.h>

class base_event {

public:
    e_event_type m_type ;
    int          m_stat ;
    explicit base_event(e_event_type  type)
    {
        m_type = type ;
        m_stat = def_not_done ;
       //  printf(" creat event type %d \r\n" , type ) ;
    }
    virtual ~base_event() = default;
};


#endif // EVENT_H
