#ifndef DEF_RTSP_HEAD_H
#define DEF_RTSP_HEAD_H

#include <wfrest/json.hpp>
#include <unistd.h>
#include <linux/can.h>

#define  def_gd4_cmd_size       (6)
#define  def_uart_buff_size     (64) //串口数据 缓冲区大小

#define DEF_APP_BUFFER_SIZE     (10*1024)    // for incoming requests, and outgoing responses
#define PARAM_STRING_MAX        200
#define MAX_HOSTNAME_LEN        256

#define DEF_THREAD_COUNT        (8) //
#define DEF_EVENT_SIZE          (512)

#define DEF_LOG        0
#define DEF_CAN0       1
#define DEF_CAN1       2

#define DEF_CONFIG_FILE        "/ns.json"
#define DEF_CONFIG_DIR         "/opt/conf"

#define def_pop_event           (-6)
#define def_not_exit            (-5)
#define def_exit                (-4)
#define def_unusing             (-3)
#define def_using               (-2)
#define def_init                (-1)
#define def_done                (0)
#define def_not_done            (1)

#define def_bus_ok              (2)
#define def_bus_err             (3)

#define def_open                (2)
#define def_close               (3)

#define def_ok                  (def_done)
#define def_ng                  (def_not_done)

#define def_used                (def_done)
#define def_unused              (def_not_done)

#define def_running             (def_not_done)
#define def_star                (def_not_done)
#define def_stop                (def_done)

#define def_io_txt              (0)
#define def_io_bin              (1)

// 配置参数  描述 组
#define  def_config_web_server_ip           ("webserver_ip")
#define  def_config_web_server_ip_def_val   ("192.168.200.120")

#define  def_config_lift_org           ("lift_org")
#define  def_config_lift_org_def_val   ("0")

#define  def_event_size (32)

#define  def_navi_ip            ("navi_ip")
#define  def_navi_ip_def_val    ("192.168.200.121")

#define  def_mqtt_name          ("mqtt_name")
#define  def_mqtt_name_def_val  ("hank_hzx")

#define  def_mqtt_port          ("mqtt_port")
#define  def_mqtt_port_def_val  ("1883")

#define  def_mqtt_port          ("mqtt_port")
#define  def_mqtt_port_def_val  ("1883")

// 模式描述 组
#define  def_mode_manual        (1)
#define  def_mode_auto          (0)
#define  ISAPI_STATUS_LEN       (4096*4)


//vcu OD 描述
#define  def_VCU_WD_cmd (0X23)
#define  def_VCU_RD_cmd (0X43)
#define  def_VCU_OK_cmd (0X60)
#define  def_VCU_NG_cmd (0X80)

const  int  Io_Cmd_ID         = 0x18C4D7D0 ;
const  int  Ctrl_Fb_ID        = 0x18C4D1EF ; // 状态回馈 0x18C4D1EF
const  int  Bms_Fb_ID         = 0x18C4E1EF ;
const  int  Bms_Flag_Fb_ID    = 0x18C4E2EF ;

const  int  RECV_VCU_OD_ID    = 0x18C4E6EF ;
const  int  SEND_VCU_OD_ID    = 0x18C4E5EF ;

//canopen 描述

//SDO CMD
#define  def_sdo_w1   0x2F
#define  def_sdo_w2   0x2B
#define  def_sdo_w4   0x23
#define  def_sdo_rd   0x40

#define  def_null  (-1)
#define  def_r     (0)
#define  def_w     (1)
#define  def_rw    (2)

#define  def_u8    (0)
#define  def_u16   (1)
#define  def_u24   (3)
#define  def_u32   (4)

#define  def_node_stat_boot_up          (0)
#define  def_node_stat_stoped           (4)
#define  def_node_stat_opertional       (5)
#define  def_node_stat_pre_opertional   (0x7f)

//canopen 描述
// lift 电机 模式
#define  def_mode_NOP  (0) // 空空 无效
#define  def_mode_POS  (1) // 位置 模式
#define  def_mode_VEL  (3) // 速度 模式
#define  def_mode_TOR  (4) // 电流 模式
#define  def_mode_SYNC (8) // 同步 模式
// lift 电机 模式

enum e_log_type {
    e_log_info    = 0 ,
    e_log_warning     ,
    e_log_error       ,
    e_log_last
};

enum e_event_type
{
    e_type_base = 0             ,

    e_type_exit                 ,
    e_type_log                  ,

    e_type_send_log             ,
    e_type_recv_log             ,

    e_type_modbus_error         ,
    e_type_modbus_update        ,
    e_type_pos_and_ptz_update   ,
    e_type_result_update        ,

    // 建图 事件
    e_type_start_creat_map      ,
    e_type_start_creat_map_done ,
    e_type_stop_creat_map       ,
    e_type_stop_creat_map_done  ,
    // 建图 事件

    // 设置 速度事件
    e_type_set_speed            ,

    //切换模式事件
    e_type_switch_mode          ,
    e_type_switch_mode_done     ,

    e_type_run_info_update      ,

// 升降杆 动作
    e_type_lift_run_update          ,

    e_type_lift_goto_org            , //ok
    e_type_lift_goto_org_done       , //ok

    e_type_lift_goto                , //ok
    e_type_lift_goto_done           , //ok

    e_type_lift_high_update         ,
    e_type_lift_high_update_done    ,
    e_type_lift_speed_update        ,
    e_type_lift_speed_update_done   ,

    e_type_lift_set_speed       ,
    e_type_lift_set_speed_done  ,

    e_type_lift_up              ,
    e_type_lift_up_done         ,

    e_type_lift_down            ,
    e_type_lift_down_done       ,

    e_type_lift_stop            ,
    e_type_lift_stop_done       ,

    e_type_lift_exit            ,
    e_type_lift_motor_fault     ,

// 升降杆 动作

// 云台 动作
    e_type_ptz_ping             , //
    e_type_ptz_set_speed        , //
    e_type_ptz_set_speed_done   , //

    e_type_ptz_op_light             , // ok
    e_type_ptz_op_light_ack         , // ok

    e_type_ptz_op_wiper             , // ok
    e_type_ptz_op_wiper_ack         , // ok

    e_type_ptz_goto             , // ok
    e_type_ptz_goto_done        , // ok

    e_type_ptz_get_pos          , // ok
    e_type_ptz_get_pos_done     , // ok

    e_type_ptz_fire_detect      , // ok
    e_type_ptz_fire_detect_done , // ok

    e_type_ptz_up        ,
    e_type_ptz_down      ,
    e_type_ptz_left      ,
    e_type_ptz_right     ,

    e_type_ptz_af_up     ,
    e_type_ptz_af_down   ,

    e_type_ptz_zoom_up      ,
    e_type_ptz_zoom_down    ,

    e_type_ptz_reset_done   ,
    e_type_ptz_reset        ,

    e_type_ptz_rq_goto_done  ,
    e_type_ptz_rq_goto       ,

    e_type_ptz_stop          ,
    e_type_ptz_update_stat   ,
// 云台 动作

// VLC 动作
    e_type_vlc_take_photo_      ,
    e_type_vlc_hk_take_photo    ,
    e_type_vlc_take_photo_done  ,
// VLC 动作

// IRC 动作
    e_type_irc_take_photo_      ,
    e_type_irc_take_photo_done  ,
// IRC 动作

// SENSOR 动作
    e_type_sensor_collect      , //传感器采集
    e_type_sensor_collect_done , //传感器采集

// SENSOR 动作

// button 动作
    e_type_button_update_stat  , // button
    e_type_button_control      , // button
    e_type_button_control_done , // button

// button 动作

// audio 动作
    e_type_audio_updata_flag       , //

    e_type_audio_collect           , //
    e_type_audio_collect_done      , //

    e_type_audio_detect             , //
    e_type_audio_detect_done        , //

    e_type_audio_msg                 , //
    e_type_audio_msg_tr              , //
    e_type_audio_ws_dat              , //
    e_type_audio_player_inner_pcm_dat, //
    e_type_audio_zmq_pcm_dat, //
// audio 动作

// wireless charge 动作
    e_type_charge_check                   ,
    e_type_charge_check_ack               ,

    e_type_charge_start                   ,
    e_type_charge_start_ack               ,

    e_type_charge_stop                    ,
    e_type_charge_stop_ack                ,

    e_type_charge_stat                    ,
    e_type_charge_stat_ack                ,

// wireless charge 动作

// can frame  event 动作
    e_type_recv_can                       ,
    e_type_send_can                       ,
    e_type_send_can_error                 ,

    e_type_vcu_recv_can                   ,
    e_type_vcu_send_can                   ,

    e_type_vcu_get_IO_stat                ,
    e_type_vcu_get_IO_stat_ack            ,

    e_type_vcu_set_IO_stat                ,
    e_type_vcu_set_IO_stat_ack            ,
// can frame  event 动作

// nvai mqtt  event
    e_type_recv_nvai_mqtt  , //接收mqtt 转发到 navi
    e_type_send_nvai_mqtt  , //navi发送 mqtt 数据

    e_type_mqtt_sub         , //订阅 事件
    e_type_mqtt_pub         , //发布 事件
    e_type_mqtt_recv        , //接收 事件

// nvai mqtt  event

// nvai   event
    e_type_nvai_goto                      ,
    e_type_nvai_goto_ack                  ,

// nvai   event

// GD4   event
    e_type_GD4_START_READ                   ,
    e_type_GD4_RESULT                       ,
// GD4   event

// button   event
    e_type_button_z_enable           ,
    e_type_button_z_enable_ack       ,

    e_type_button_z_disable          ,
    e_type_button_z_disable_ack      ,

    e_type_button_z_up               ,
    e_type_button_z_up_ack           ,

    e_type_button_z_down             ,
    e_type_button_z_down_ack         ,

    e_type_button_z_stop             ,
    e_type_button_z_stop_ack         ,

    e_type_button_z_goto             ,
    e_type_button_z_goto_ack         ,

    e_type_button_z_get_pos          ,
    e_type_button_z_get_pos_ack      ,

    e_type_button_z_goto_org         ,
    e_type_button_z_goto_org_ack     ,

// button   event

// untils   event
    e_type_untils_red_open            ,
    e_type_untils_red_open_ack        ,

    e_type_untils_red_close           ,
    e_type_untils_red_close_ack       ,

    e_type_untils_red_blink           ,
    e_type_untils_red_blink_ack       ,

    e_type_untils_yellow_open         ,
    e_type_untils_yellow_open_ack     ,

    e_type_untils_yellow_close        ,
    e_type_untils_yellow_close_ack    ,

    e_type_untils_yellow_blink        ,
    e_type_untils_yellow_blink_ack    ,
//-----------------------------------------------------//
    e_type_untils_fill_open           ,
    e_type_untils_fill_open_ack       ,

    e_type_untils_fill_close          ,
    e_type_untils_fill_close_ack      ,

    e_type_untils_io_ctrl_radar       ,
    e_type_untils_io_ctrl_radar_ack   ,

    e_type_untils_io_ptz_hs           ,
    e_type_untils_io_ptz_hs_ack       ,

    e_type_untils_stop_tp_smoke       ,
    e_type_untils_stop_tp_smoke_ack   ,

    e_type_untils_all_close           ,
    e_type_untils_all_close_ack       ,

    e_type_untils_get_dev_stat        ,
    e_type_untils_get_dev_stat_ack    ,

    e_type_untils_voice_broadcast     ,
    e_type_untils_voice_broadcast_ack ,

    e_type_untils_voice_tip           ,
    e_type_untils_voice_tip_ack       ,

// untils   event

    e_type_last
};

struct  ptz_move_val{

    int     m_stat  ;
    double  m_l_value ;
    double  m_v_value ;
    double  m_af_value ;
    double  m_zoom_value ;
};

struct  roi{

    double  m_x ;
    double  m_y ;
    double  m_w ;
    double  m_h ;
};

struct  point{
    double  m_x ;
    double  m_y ;
    double  m_z ;
};

struct db_run_info {

    int m_dat_time ;

    double m_pose_x;
    double m_pose_y;
    double m_pose_z;

    double m_rpy_r;
    double m_rpy_p;
    double m_rpy_y;

    int m_ptz_h;
    int m_ptz_v;
    int m_ptz_z;
    int m_ptz_f;

};

struct run_info {

    double m_battery ;
    double m_pos_x;
    double m_pos_y;
    double m_pos_z;

    double m_a_r;
    double m_a_p;
    double m_a_y;

    double m_speed ;

    int m_ptz_h;
    int m_ptz_v;
    int m_ptz_z;
    int m_ptz_f;

};

struct audio_g711{
    unsigned char m_buff [160];
};

struct audio_pcm{
    unsigned char m_buff [320];
};

struct audio_aac{
    int m_aac_size ;
    unsigned char m_buff [1024*2];
};

struct audio_ws{
    int m_size ;
    unsigned char m_buff [1024*1024];
};

#define def_d_step  (100) // 毫米 缩放倍数

#define  msleep(val) usleep(1000*val)


#define TOPIC_MAP           ("/map/property/current_map")
#define TOPIC_POSE          ("/localization/pose")
#define TOPIC_ARRIVE        ("/task/target/event/arrive")
#define TOPIC_CODE          ("/diagnose/property/code")
#define TOPIC_START         ("/navigation/stack/action/start")
#define TOPIC_START_REPLY   ("/navigation/stack/action/start/reply")
#define TOPIC_STOP          ("/navigation/stack/action/stop")
#define TOPIC_STOP_REPLY    ("/navigation/stack/action/stop/reply")
#define TOPIC_RESTART_REPLY ("/navigation/stack/action/restart/reply")
#define TOPIC_PAUSE_REPLY   ("/task/procedure/action/pause/reply")
#define TOPIC_RESUME_REPLY  ("/task/procedure/action/resume/reply")
#define TOPIC_CANCEL_REPLY  ("/task/procedure/action/cancel/reply")
#define TOPIC_GOTO_REPLY    ("/task/target/action/goto/reply")
#define TOPIC_RESTART       ("/navigation/stack/action/restart")
#define TOPIC_PAUSE         ("/task/procedure/action/pause")
#define TOPIC_RESUME        ("/task/procedure/action/resume")
#define TOPIC_CANCEL        ("/task/procedure/action/cancel")
#define TOPIC_GOTO          ("/task/target/action/goto")

#define check_charge              ("/check_charge")
#define check_charge_ack          ("/check_charge_ack")

#define start_charge              ("/start_charge")
#define start_charge_ack          ("/start_charge_ack")

#define stop_charge               ("/stop_charge")
#define stop_charge_ack           ("/stop_charge_ack")

#define charge_stat               ("/charge_stat")


struct topic_item{
    std::string topic ;
    int    qos   ;
};

/*****************
 * VCU info
 */

#pragma pack(push)
#pragma pack(1)

struct Io_Cmd {
    unsigned char   lamp_control_mode   : 1  ;
    unsigned char   secure_parking      : 1  ;
    unsigned char   rev1                : 6  ;

    unsigned char  red_light            : 1  ;
    unsigned char  blue_light           : 1  ;
    unsigned char  turn_light           : 2  ;
    unsigned char  green_light          : 1  ;
    unsigned char  rev2                 : 1  ;
    unsigned char  fog_light            : 1  ;
    unsigned char  rev3                 : 1  ;

    unsigned char  speaker              : 1  ;
    unsigned char  rev4                 : 7  ;

    unsigned char  rev5                      ;
    unsigned char  rev6                      ;
    unsigned char  rev7                      ;
    unsigned char  rev8                      ;

    unsigned char  rev9                 : 4  ;
    unsigned char  live_count            : 4  ;

    unsigned char  bcc                   : 8  ;
};

struct Ctrl_Fb {
    unsigned char   gear       : 4  ;
    short           line_v     : 16 ; // 0.001 m/s
    short           angle_v    : 16 ; // 0.01  o/s'
    unsigned char   rev        : 8  ;
    unsigned char   live_count : 4  ;
    unsigned char   bcc        : 8  ;
};

struct Bms_Fb {

    unsigned short voltage              : 16 ;
    signed short   current              : 16 ;
    unsigned short remaining_charge     : 16 ;

    unsigned char  rev1                 : 4  ;
    unsigned char live_count            : 4  ;

    unsigned char bcc                   : 8  ;
};

struct Bms_Flag_Fb {

    unsigned char  remaining_charge_ratio  : 8 ;

    unsigned char  monomic_overpressure         : 1 ;
    unsigned char  monomer_undervoltage         : 1 ;
    unsigned char  overall_overpressure         : 1 ;
    unsigned char  overall_undervoltage         : 1 ;
    unsigned char  charging_overwarm            : 1 ;
    unsigned char  charging_low_temperature     : 1 ;
    unsigned char  overtemperature_discharge    : 1 ;
    unsigned char  low_temperature_discharge    : 1 ;

    unsigned char  charging_overcurrent         : 1 ;
    unsigned char  discharge_overcurrent        : 1 ;
    unsigned char  short_circuit                : 1 ;
    unsigned char  IC_error                     : 1 ;
    unsigned char  software_locks_MOS           : 1 ;
    unsigned char  charging_flag_bit            : 1 ;
    unsigned char  rev0                         : 2 ;

    unsigned char  rev1                         : 8 ;

    unsigned short  max_temperature             : 12 ;
    unsigned short  rev2                        : 4;

    unsigned char   rev3                        : 4  ;
    unsigned char   live_count                  : 4  ;

    unsigned char bcc                           : 8  ;
};

union vcu_raw_to_struct{
    unsigned char  date [8]     ;
    Io_Cmd       m_io_cmd       ;
    Ctrl_Fb      m_ctrl_fb      ;
    Bms_Fb       m_bms_fb       ;
    Bms_Flag_Fb  m_bms_flag_fb  ;
};

#pragma pack(pop)

struct chanle_info{
    int chanle ;
    int val ;
    int op_stat ;
};


#define  def_val_init   (-1)
#define  def_stat_init  (0)
#define  def_stat_ok    (1)
#define  def_stat_ng    (2)

struct can_open_context{

    int m_idx ;
    int s_idx  ;
    int m_cmd  ;
    int m_stat ;

    can_open_context( int i_m_idx  , int i_s_idx , int cmd ){
        m_idx   = i_m_idx;
        s_idx   = i_s_idx ;
        m_cmd   = cmd ;
        m_stat  = def_stat_init ;
    }

    // send ! update
    // recv ! update

    void fun_update( can_frame & fr ){

        if(
            (fr.data[0] == 0x2f) ||
                (fr.data[0] == 0x2b) ||
                (fr.data[0] == 0x27) ||
                (fr.data[0] == 0x23) ||
                (fr.data[0] == 0x40)
            ){
            m_stat  = def_stat_init ;
        }

        if(
            (fr.data[0] == 0x60) ||
                (fr.data[0] == 0x4f) ||
                (fr.data[0] == 0x4b) ||
                (fr.data[0] == 0x47) ||
                (fr.data[0] == 0x43)
            ){
            m_stat  = def_stat_ok ;
        }

        if(fr.data[0] == 0x80){
            m_stat  = def_stat_ng ;
        }
    }
};



#endif // DEF_RTSP_HEAD_H
