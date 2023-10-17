#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>

#include <spdlog/spdlog.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/common.h>
#include <spdlog/async.h>

#include "../base_event.h"
#include "../def_head.h"

#define DEF_ENV (environment::get_instance())
#define SPLOG(  TAG, logs)  do{ DEF_ENV->splog( TAG , logs, __FILE__, __LINE__ , __func__  , DEF_LOG  ); }while(0)
#define SPCAN0( TAG, logs) do { DEF_ENV->splog( TAG , logs, __FILE__, __LINE__ , __func__  , DEF_CAN0 ); } while(0)
#define SPCAN1( TAG, logs) do { DEF_ENV->splog( TAG , logs, __FILE__, __LINE__ , __func__  , DEF_CAN1 ); } while(0)

class environment {

    environment() {
        func_init_log() ;
        m_flag = def_running;
        m_step_sleep_ms = 1000;
        std::string  res ;
    }

public:

    void func_init_log() {

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_color(spdlog::level::info, console_sink->green);
        console_sink->set_color(spdlog::level::warn, console_sink->yellow);
        console_sink->set_color(spdlog::level::err, console_sink->red_bold);
        console_sink->set_level(spdlog::level::trace);
        auto console_logger = std::make_shared<spdlog::logger>("console", console_sink);
        spdlog::register_logger(console_logger);
        {
            const size_t maxFileSize = 5 * 1024 * 1024;
            const size_t maxFiles = 20;  // 保留最近的3个文件
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log/all.log", maxFileSize, maxFiles);
            file_sink->set_level(spdlog::level::trace);
            auto file_logger = std::make_shared<spdlog::logger>("all_log", file_sink);
            spdlog::register_logger(file_logger);
        }
        {
            const size_t maxFileSize = 5 * 1024 * 1024;
            const size_t maxFiles = 20;  // 保留最近的3个文件
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log/can0.log", maxFileSize, maxFiles);
            file_sink->set_level(spdlog::level::trace);
            auto file_logger = std::make_shared<spdlog::logger>("can0", file_sink);
            spdlog::register_logger(file_logger);
        }
        {
            const size_t maxFileSize = 5 * 1024 * 1024;
            const size_t maxFiles = 20;  // 保留最近的3个文件
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log/can1.log", maxFileSize, maxFiles);
            file_sink->set_level(spdlog::level::trace);
            auto file_logger = std::make_shared<spdlog::logger>("can1", file_sink);
            spdlog::register_logger(file_logger);
        }
    }

    inline void splog(
        const std::string &tag,
        const std::string &info,
        const std::string &file ,
        int line  ,
        const std::string & _func ,
        int type
    ) {
        std::string log = fmt::format("({}:{}:{}) \n \t\t-->{}\n",
                                      tag ,  line,_func,
                                      info
        );
        if( type == DEF_LOG ){

            spdlog::get("console")->info(log);
            spdlog::get("console")->flush();

            spdlog::get("all_log")->info(log);
            spdlog::get("all_log")->flush();
        }
        else if( type == DEF_CAN0  ){
            spdlog::get("can0")->info(log);
            spdlog::get("can0")->flush();
        }
        else if( type == DEF_CAN1  ){
            spdlog::get("can1")->info(log);
            spdlog::get("can1")->flush();
        }
    }

    bool m_dev_stat;
    std::string m_dev_did;
    std::string m_dev_pid;
    std::string m_dev_addr;

    std::string m_win_server_addr = "192.168.1.230";
    unsigned short m_win_server_port = 18080;

    ~environment() {

    };

    int m_flag;
    int m_step_sleep_ms;

    static environment *get_instance() {
        static environment env;
        return &env;
    }

    void fun_msleep(int val = 1000) {
        usleep(val * 1000);
    }

    void fun_step_msleep() {
        fun_msleep(m_step_sleep_ms);
    }

    void fun_mkdirs(const char *dir_path) {

    }

    void fun_make_dir(const char *dir) {
        std::string cmd ;
        cmd = std::string("mkdir ")  + std::string(dir) + std::string(" -p " ) ;
        system(cmd.c_str() );
    }

};


#endif // ENVIRONMENT_H
