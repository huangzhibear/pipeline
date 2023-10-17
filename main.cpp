#include <iostream>
#include "coroutine.h"
#include <unistd.h>
#include "base_node.h"
#include "dlib/sqlite/sqlite.h"
#include <dlib/sqlite.h>
#include <iostream>
#include <dlib/sqlite.h>
#include <dlib/matrix.h>
#include <dlib/linker.h>
#include <dlib/array.h>

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
using namespace dlib;

bool table_exists (
    database& db,
    const std::string& tablename
)
{
    // Sometimes you want to just run a query that returns one thing.  In this case, we
    // want to see how many tables are in our database with the given tablename.  The only
    // possible outcomes are 1 or 0 and we can do this by looking in the special
    // sqlite_master table that records such database metadata.  For these kinds of "one
    // result" queries we can use the query_int() method which executes a SQL statement
    // against a database and returns the result as an int.
    return query_int(db, "select count(*) from sqlite_master where name = '"+tablename+"'")==1;
}

int main()
{
    test_node m_node ;
    base_node::fun_start() ;
    database db("./log.db");

    if (!table_exists(db,"people"))
        db.exec("create table people (name, age, data)");

    if (!table_exists(db,"can_bus"))
        db.exec("create table can_bus (name, age, data)");

    statement st(db, "insert into people VALUES(?,?,?)");
    // The data for Davis
    string name = "Davis";
    int age = 32;
    array<long> m ; // some random "data" for Davis
    m.push_back(123);
    m.push_back(123);
    m.push_back(123);
    m.push_back(123);


    // You can bind any of the built in scalar types (e.g. int, float) or std::string and
    // they will go into the table as the appropriate SQL types (e.g. INT, TEXT).  If you
    // try to bind any other object it will be saved as a binary blob if the type has an
    // appropriate void serialize(const T&, std::ostream&) function defined for it.  The
    // matrix has such a serialize function (as do most dlib types) so the bind below saves
    // the matrix as a binary blob.
    st.bind(1, name);
    st.bind(2, age);
    st.bind(3, m);
    st.exec(); // execute the SQL statement.  This does the insert.

    name = "John";
    age = 82;
    st.bind(1, name);
    st.bind(2, age);
    st.bind(3, m);
    st.exec();


    // Now lets print out all the rows in the people table.
    statement st2(db, "select * from people");
    st2.exec();
    // Loop over all the rows obtained by executing the statement with .exec().
    while(st2.move_next())
    {
        string name;
        int age;
         array<long> m  ;
        // Analogously to bind, we can grab the columns straight into C++ types.  Here the
        // matrix is automatically deserialized by calling its deserialize() routine.
        st2.get_column(0, name);
        st2.get_column(1, age);
        st2.get_column(2, m);
        std::cout << name << " " << age  ;

        for(auto & it : m) {
            std::cout << it << " " << age  <<  std::endl;
        }
    }

    return  0 ;

    while (1){
        auto _e = std::make_shared<base_event>(e_type_base) ;
        base_node::fun_send_event(_e);
        usleep(1000);
        printf("-");
    }
    return 0;
}