/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: Time.h
*
* 功能说明: 
* 修改说明:
*******************************************************************************/
#ifndef _UART_H_
#define _UART_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define iUART_TXBUF_SIZE        32
#define iUART_RXBUF_SIZE        32

#define mUART_BYTE_TX(x)        {TX0REG=(x);while(T0MCLR == 0);}

#define iUART_S_M               0x50

#define UART_RX_PIN             PF2
#define UART_TX_PIN             PF3

//----------------------------------------------
// 主->从
//
#define iUART_CMD_RSP_0         0x61
#define iUART_CMD_RSP_1         0x0D
#define iUART_CMD_RSP_2         0x0A

//----------------------------------------------
// 主->从
//
#define iUART_CMD_STDK          0xA1
#define iUART_CMD_EXK           0xA2
#define iUART_CMD_MMK           0xA3
#define iUART_CMD_SYS           0xA4
#define iUART_CMD_FN            0xA5
#define iUART_CMD_CTRL          0xA6
//{
    #define iCMD_INVALID        0x00
    #define iCTRL_CMD_OFF       0x10
    #define iCTRL_CMD_IDLE      0x11
    #define iCTRL_CMD_24G       0x30
    #define iCTRL_CMD_BT0       0x31
    #define iCTRL_CMD_BT1       0x32
    #define iCTRL_CMD_BT2       0x33
    #define iCTRL_CMD_BT3       0x34
    #define iCTRL_CMD_BT4       0x35
    #define iCTRL_CMD_CONN      0x51
    #define iCTRL_CMD_CLEAR     0x52
    #define iCTRL_CMD_BAT_INFO  0x53
    #define iCTRL_CMD_FLASH_R   0x54

    #define iCTRL_CMD_FCC_24G   0x80
    #define iCTRL_CMD_FCC_BLE   0x81
    #define iCTRL_CMD_FCC       0x82
    #define iCTRL_CMD_WAKEUP    0x00
//}
#define iUART_CMD_LED           0xA7

#define iUART_CMD_MOUSE         0xA8
#define iUART_CMD_BT_INFO       0xA9
#define iUART_CMD_BAT_VALUE     0xAA
#define iUART_CMD_FLASH_W       0xAB
#define iUART_CMD_VID_PID       0xAD
#define iUART_CMD_NULL          0x00

//----------------------------------------------
// 从->主
//
#define iUART_CMD_FLASH_DAT     0x59
#define iRSP_CMD_DIS_CONN       0x5A
//{
    #define iDIS_CONN_TIME_OUT  0x08         // 超时断线
    #define iDIS_CONN_SLEEP     0x13         // 主机睡眠
    #define iDIS_CONN_SELF      0x16         // 主动断线
//}
#define iUART_CMD_BT_RSP        0x5B
//{
    #define iRSP_CMD_OUT_CONN   0x30
    #define iRSP_CMD_INTO_CONN  0x31
    #define iRSP_CMD_CONN_OK    0x32
    #define iRSP_CMD_SWITCH_OK  0x34
    #define iRSP_CMD_INVAILD    0x42
//}
#define iUART_CMD_BAT_INFO      0x5C
#define iUART_CMD_WHEEL         0x5D
#define iUART_CMD_LED_OFF       0x5E
//----------------------------------------------
// 命令长度
//
#define iUART_LENGHT_STDK       9
#define iUART_LENGHT_EX         16
#define iUART_LENGHT_MMK        3
#define iUART_LENGHT_SYS        2
#define iUART_LENGHT_FN         2
#define iUART_LENGHT_MOUSE      6
#define iUART_LENGHT_BT_INFO    18
#define iUART_LENGHT_CTRL       2
#define iUART_LENGHT_LED        6
#define iUART_LENGHT_FLASH_W    17
#define iUART_LENGHT_VID_PID    5

//----------------------------------------------
//配置常量定义区
//
#define iUART_TX_IDLE           0x00
#define iUART_TX_ING            0x01
#define iUART_TX_OK             0xFE
#define iUART_TX_ERR            0xFF
#define iUART_RETX_COUNT        3

//----------------------------------------------
//配置常量定义区
//
#define iCMD_TX_BEGIN           0x00
#define iCMD_IDLE               0x00
#define iCMD_TX_ING             0x01
#define iCMD_RX_ING             0x03
#define iCMD_RSP_ERR            0xFE
#define iCMD_RSP_OK             0xFF
#define iCMD_RSP_END            0xFF
//----------------------------------------------
// 串口命令索引
//
#define iCMD_STD                0
#define iCMD_BT_INFO            1
#define iCMD_DEVICE_SWITCH      2
#define iCMD_FLASH_W            3
#define iCMD_BAT_UPDATE         4
#define iCMD_KB_DATA            5

//=============================================================================;
// 外部定义内部引用区
//=============================================================================;

//=============================================================================;
// 外部寄存器引用                                                              
//

//=============================================================================;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部引用区
//=============================================================================;
extern USBD_U8                  uuart_ctrl;
//{
    #define uart_ctrl           uuart_ctrl.u8

    #define bbat_power_up       uuart_ctrl.BIT.b6
    #define bkb_tx_busy         uuart_ctrl.BIT.b5
    #define bwakeup_en          uuart_ctrl.BIT.b4
    #define bretey_count        uuart_ctrl.BIT.b3
    #define buart_ready         uuart_ctrl.BIT.b2
    #define buart_rsp_ok        uuart_ctrl.BIT.b1
    #define buart_rx_ok         uuart_ctrl.BIT.b0
//}
extern USBD_U16                 utx_cmd_flag;
//{
    #define tx_cmd_flag         utx_cmd_flag.u16

    #define bdevice_bt_vid_pid  utx_cmd_flag.BIT.b12 // VID PID

    #define bdevice_bt_info_ok  utx_cmd_flag.BIT.b11
    #define bom6621d_disconn_sleep utx_cmd_flag.BIT.b10
    #define bom6621d_flash_r    utx_cmd_flag.BIT.b9
    #define bom6621d_flash_w    utx_cmd_flag.BIT.b8

    #define bbat_updata         utx_cmd_flag.BIT.b7 // 获取电量
    #define bdevice_switch      utx_cmd_flag.BIT.b6 // 设备切换
    #define bdevice_conn        utx_cmd_flag.BIT.b5 // 无线配对
    #define bdevice_clear       utx_cmd_flag.BIT.b4 // 清除配对

    #define bbat_info_updata    utx_cmd_flag.BIT.b3 // 电量更新
    #define bom6621d_led_updata utx_cmd_flag.BIT.b2 // led状态更新
    #define bdevice_bat_info    utx_cmd_flag.BIT.b1 // 电量信息
    #define bdevice_bt_info     utx_cmd_flag.BIT.b0 // 蓝牙信息
//}

extern USBD_U8                  uom6621d_status;
//{
    #define om6621d_status      uom6621d_status.u8

    #define bbat_check_err      uom6621d_status.BIT.b7 //
    #define buart_flash_ok      uom6621d_status.BIT.b6 //
    #define bom6621d_sync_ing   uom6621d_status.BIT.b5 //
    #define bom6621d_led_off    uom6621d_status.BIT.b4 //
    #define bom6621d_conn_ok    uom6621d_status.BIT.b3 // 0:断开连接；1:连接成功
    #define bom6621d_conning    uom6621d_status.BIT.b2 // 进入对码状态
    #define bom6621d_switch_ok  uom6621d_status.BIT.b1 // 设备切换成功
    #define bom6621d_standby    uom6621d_status.BIT.b0
//}

extern unsigned char            device_type;
extern unsigned char            device_type_bak;

extern unsigned char            uart_tx_delay;
extern unsigned char            uart_rx_delay;
extern unsigned char            rx_r_index;
extern unsigned char            uart_tick_count;
extern unsigned char            uart_cmd_delay;

extern unsigned char            bat_power_value;
extern unsigned char            bat_value_ble;
extern unsigned char            device_conn_index;
extern unsigned char            data_tx_delay_count;
extern unsigned char            conn_time_count;

extern unsigned char            uart_rx_buff[];
extern unsigned char            cmd_tx_index;
extern unsigned char            om6621d_flash_dat[];
//extern unsigned char            wheel_data_6621d;

//=============================================================================;
// 寄存器引用                                                              
//

//=============================================================================;
// 函数引用
//
extern void uart_init(void);
extern void cmd_tx_init(void);
extern void uart_invalid(void);

extern void uart_process(void);
extern void uart_rx_decode(void);
extern unsigned char om6621d_led_ctrl(void);
extern void om6621d_bt_device_info(void);
extern void om6621d_device_switch(void);
extern void get_bat_value(void);
extern void off_bt_led(void);

#endif
